/* FILE NAME: rndshd.c
 * PROGRAMMER: KV6
 * DATE: 25.06.2021
 * PURPOSE: 3D animation rendering declaration module.
 */

#include <stdio.h>
#include <string.h>

#include "../rnd.h"


/* Shadre stock array and it size */
kv6SHADER KV6_RndShaders[KV6_MAX_SHADERS];
INT KV6_RndShadersSize;


/* RndShdLog */
VOID KV6_RndShdLog( CHAR *FileNamePrefix, CHAR *ShaderName, CHAR *Text )
{
  FILE *F;

  if ((F = fopen("BIN/SHADERS/shd{30}kv6.log", "a")) == NULL)
    return;
  fprintf(F, "%s : %s\n%s\n\n", FileNamePrefix, ShaderName, Text);
  fclose(F);
} /* End of 'KV6_RndLoadTextFromFile' function */


/* RndLoadTextFromFile */
CHAR * KV6_RndLoadTextFromFile( CHAR *FileName )
{
  FILE *F;
  INT flen;
  CHAR *txt;

  if ((F = fopen(FileName, "rb")) == NULL)
    return NULL;

  /* Measure file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);

  /* Allocate memory */
  if ((txt = malloc(flen + 1)) == NULL)
  {
    fclose(F);
    return NULL;
  }
  /* Load text */
  rewind(F);
  memset(txt, 0, flen + 1);
  fread(txt, 1, flen, F);

  fclose(F);
  return txt;
} /* End of 'KV6_RndLoadTextFromFile' function */


/* RndShdLoad */
INT KV6_RndShdLoad( CHAR *FileNamePrefix )
{
  struct
  {
    CHAR *Name; /* Shader name (e.g. "VERT") */
    INT Type;   /* Shader type (e.g. GL_VERTEX_SHADER) */
    INT Id;     /* Obtained shader Id from OpenGL */
  } shd[] =
  {
    {"VERT", GL_VERTEX_SHADER, 0},
    {"FRAG", GL_FRAGMENT_SHADER, 0},
  };
  INT NoofS = sizeof(shd) / sizeof(shd[0]), i, prg, res;
  CHAR *txt;
  BOOL is_ok = TRUE;
  static CHAR Buf[1000];

  /* Load shader */
  for (i = 0; i < NoofS; i++)
  {
    /* Build shader name */
    sprintf(Buf, "BIN/SHADERS/%s/%s.GLSL", FileNamePrefix, shd[i].Name);

    /* Load shader text from file */
    txt = KV6_RndLoadTextFromFile(Buf);
    if (txt == NULL)
    {
      KV6_RndShdLog(FileNamePrefix, shd[i].Name, "Error load file");
      is_ok = FALSE;
      break;
    }

    /* Create shader */
    if ((shd[i].Id = glCreateShader(shd[i].Type)) == 0)
    {
      KV6_RndShdLog(FileNamePrefix, shd[i].Name, "Error create shader");
      is_ok = FALSE;
      break;
    }

    /* Attach text to shader */
    glShaderSource(shd[i].Id, 1, &txt, NULL);
    free(txt);

    /* Compile shader */
    glCompileShader(shd[i].Id);

    /* Handle errors */
    glGetShaderiv(shd[i].Id, GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      glGetShaderInfoLog(shd[i].Id, sizeof(Buf), &res, Buf);
      KV6_RndShdLog(FileNamePrefix, shd[i].Name, Buf);
      is_ok = FALSE;
      break;
    }
  }

  /* Create program */
  if (is_ok)
    if ((prg = glCreateProgram()) == 0)
    {
      KV6_RndShdLog(FileNamePrefix, "PROG", "Error create program");
      is_ok = FALSE;
    }
    else
    {
      /* Attach shaders to program */
      for (i = 0; i < NoofS; i++)
        if (shd[i].Id != 0)
          glAttachShader(prg, shd[i].Id);
      /* Link program */
      glLinkProgram(prg);
      glGetProgramiv(prg, GL_LINK_STATUS, &res);
      if (res != 1)
      {
        glGetProgramInfoLog(prg, sizeof(Buf), &res, Buf);
        KV6_RndShdLog(FileNamePrefix, "PROG", Buf);
        is_ok = FALSE;
      }
    }

  /* Handle errors */
  if (!is_ok)
  {
    /* Delete all shaders */
    for (i = 0; i < NoofS; i++)
      if (shd[i].Id != 0)
      {
        if (prg != 0)
          glDetachShader(prg, shd[i].Id);
        glDeleteShader(shd[i].Id);
      }
    /* Delete program */
    if (prg != 0)
      glDeleteProgram(prg);
    prg = 0;
  }
  return prg;
} /* End of 'KV6_RndShdLoad' function */


/* RndShdFree */
VOID KV6_RndShdFree( INT ProgId )
{
  INT shds[5], n, i;

  if (ProgId == 0 || !glIsProgram(ProgId))
    return;
  glGetAttachedShaders(ProgId, 5, &n, shds);
  for (i = 0; i < n; i++)
    if (glIsShader(shds[i]))
    {
      glDetachShader(ProgId, shds[i]);
      glDeleteShader(shds[i]);
    }
    glDeleteProgram(ProgId);
} /* End of 'KV6_RndShdLoad' function */


/* RndShadersInit */
VOID KV6_RndShadersInit( VOID )
{
  KV6_RndShadersSize = 0;
  KV6_RndShaderAdd("DEFAULT");
} /* End of 'KV6_RndShadersInit' function */


/* RndShadersClose */
VOID KV6_RndShadersClose( VOID )
{
  INT i;

  for (i = 0; i < KV6_RndShadersSize; i++)
    KV6_RndShdFree(KV6_RndShaders[i].ProgId);
  KV6_RndShadersSize = 0;
} /* End of 'KV6_RndShadersInit' function */


/* RndShaderAdd */
INT KV6_RndShaderAdd( CHAR *FileNamePrefix )
{
  INT i;

  for (i = 0; i < KV6_RndShadersSize; i++)
    if (strcmp(FileNamePrefix, KV6_RndShaders[i].Name) == 0)
      return i;
  if (KV6_RndShadersSize >= KV6_MAX_SHADERS)
    return 0;
  strncpy(KV6_RndShaders[KV6_RndShadersSize].Name, FileNamePrefix, KV6_STR_MAX - 1);
  KV6_RndShaders[KV6_RndShadersSize].ProgId = KV6_RndShdLoad(FileNamePrefix);
  return KV6_RndShadersSize++;
} /* End of 'KV6_RndShadersAdd' function */


/* RndShadersUpdate */
VOID KV6_RndShadersUpdate( VOID )
{
  INT i;

  for (i = 0; i < KV6_RndShadersSize; i++)
  {
    KV6_RndShdFree(KV6_RndShaders[i].ProgId);
    KV6_RndShaders[i].ProgId = KV6_RndShdLoad(KV6_RndShaders[i].Name);
  }
} /* End of 'KV6_RndShadersUpdate' function */


/* END OF 'rndshd.c' FILE */