������������� � �������� ��������
������ ������������� ��������� �� GLSL

������� ��������:
!!! ����������:
������� ����� ��������� �������� ������������� � ��������� ���������� � ���������� ���������:
/bin/shaders/default/
  vert.glsl
  frag.glsl
/bin/shaders/land/
  vert.glsl
  frag.glsl
/bin/shaders/sphere/
  vert.glsl
  geom.glsl
  frag.glsl

������ default:
vert.glsl
// ������ ����� ������� (3.3)
#version 330

// ��� ���� ��������
layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexCoord;
layout(location = 2) in vec3 InNormal;
layout(location = 3) in vec4 InColor;

// ���������� ���������� (������������ ������: World * View * Proj)
uniform mat4 MatrWVP;

// �������� ��������� (varying)
out vec4 DrawColor;

void main( void )
{
  gl_Position = MatrWVP * vec4(InPosition, 1);
  DrawColor = InColor;
}

frag.glsl
// ������ ����� ������� (3.3)
#version 330

// �������� ��������� - ���� ���������
layout(location = 0) out vec4 OutColor;

// ������� ��������� (varying)
in vec4 DrawColor;

void main( void )
{
  OutColor = DrawColor;
}

�������� ��������
  "BIN/SHADERS/" + FileNamePrefix + "vert.glsl"
  load text + create vertex shader
  compile
  "BIN/SHADERS/" + FileNamePrefix + "frag.glsl"
  load text + create fragment shader
  compile

  create program
  attach shaders
  link
  --> ProgId � ������������� ����� ��������� ���������

����������� ��� ���������
  MATR wvp = MatrMulMatr(World, MatrMulMatr(VG4_RndMatrView, VG4_RndMatrProj));
  INT ProgId = VG4_RndShaders[0].ProgId;
  INT loc;

  glUseProgram(ProgId);

  if ((loc = glGetUniformLocation(ProgId, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, wvp.A[0]);
  if ((loc = glGetUniformLocation(ProgId, "Time")) != -1)
    glUniform1f(loc, VG4_Anim.Time);
. . .
  glUseProgram(0);




/* FILE NAME: rndshd.c
 * PROGRAMMER: VG4
 * DATE: 23.06.2021
 * PURPOSE: 3D animation rendering shader handle functions module.
 */

#include <stdio.h>
#include <string.h>

#include "../rnd.h"

/***
 * Base shaders functions
 ***/

/* Save log to file function.
 * ARGUMENTS:
 *   - shader prefix:
 *       CHAR *FileNamePrefix;
 *   - shader name:
 *       CHAR *ShaderName;
 *   - error text:
 *       CHAR *Text;
 * RETURNS: None.
 */
VOID VG4_RndShdLog( CHAR *FileNamePrefix, CHAR *ShaderName, CHAR *Text )
{
  FILE *F;

  if ((F = fopen("BIN/SHADERS/shd{30}vg4.log", "a")) == NULL)
    return;
  fprintf(F, "%s : %s\n%s\n\n", FileNamePrefix, ShaderName, Text);
  fclose(F);
} /* End of 'VG4_RndLoadTextFromFile' function */

/* Load shader text from file function.
 * ARGUMENTS:
 *   - text file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (CHAR *) load text.
 */
CHAR * VG4_RndLoadTextFromFile( CHAR *FileName )
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
} /* End of 'VG4_RndLoadTextFromFile' function */

/* Load shader program function.
 * ARGUMENTS:
 *   - shader folder prefix (in 'BIN/SHADERS/***'):
 *       CHAR *FileNamePrefix;
 * RETUNS:
 *   (INT) load shader program Id.
 */
INT VG4_RndShdLoad( CHAR *FileNamePrefix )
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
    txt = VG4_RndLoadTextFromFile(Buf);
    if (txt == NULL)
    {
      VG4_RndShdLog(FileNamePrefix, shd[i].Name, "Error load file");
      is_ok = FALSE;
      break;
    }

    /* Create shader */
    if ((shd[i].Id = glCreateShader(shd[i].Type)) == 0)
    {
      VG4_RndShdLog(FileNamePrefix, shd[i].Name, "Error create shader");
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
      VG4_RndShdLog(FileNamePrefix, shd[i].Name, Buf);
      is_ok = FALSE;
      break;
    }
  }

  /* Create program */
  if (is_ok)
    if ((prg = glCreateProgram()) == 0)
    {
      VG4_RndShdLog(FileNamePrefix, "PROG", "Error create program");
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
        VG4_RndShdLog(FileNamePrefix, "PROG", Buf);
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
} /* End of 'VG4_RndShdLoad' function */

/* Delete shader program function.
 * ARGUMENTS:
 *   - shader program Id:
 *       INT ProgId;
 * RETUNS: None.
 */
VOID VG4_RndShdFree( INT ProgId )
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
} /* End of 'VG4_RndShdLoad' function */

/***
 * Shaders stock functions
 ***/

/* Shadre stock array and it size */
vg4SHADER VG4_RndShaders[VG4_MAX_SHADERS];
INT VG4_RndShadersSize;

/* Shader stock initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID VG4_RndShadersInit( VOID )
{
  VG4_RndShadersSize = 0;
  VG4_RndShaderAdd("DEFAULT");
} /* End of 'VG4_RndShadersInit' function */

/* Shader stock deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID VG4_RndShadersClose( VOID )
{
  INT i;

  for (i = 0; i < VG4_RndShadersSize; i++)
    VG4_RndShdFree(VG4_RndShaders[i].ProgId);
  VG4_RndShadersSize = 0;
} /* End of 'VG4_RndShadersInit' function */

/* Shader add to stock function.
 * ARGUMENTS:
 *   - shader folder prefix:
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (INT) shader number in stock.
 */
INT VG4_RndShaderAdd( CHAR *FileNamePrefix )
{
  INT i;

  for (i = 0; i < VG4_RndShadersSize; i++)
    if (strcmp(FileNamePrefix, VG4_RndShaders[i].Name) == 0)
      return i;
  if (VG4_RndShadersSize >= VG4_MAX_SHADERS)
    return 0;
  strncpy(VG4_RndShaders[VG4_RndShadersSize].Name, FileNamePrefix, VG4_STR_MAX - 1);
  VG4_RndShaders[VG4_RndShadersSize].ProgId = VG4_RndShdLoad(FileNamePrefix);
  return VG4_RndShadersSize++;
} /* End of 'VG4_RndShadersAdd' function */

/* Shader stock update function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID VG4_RndShadersUpdate( VOID )
{
  INT i;

  for (i = 0; i < VG4_RndShadersSize; i++)
  {
    VG4_RndShdFree(VG4_RndShaders[i].ProgId);
    VG4_RndShaders[i].ProgId = VG4_RndShdLoad(VG4_RndShaders[i].Name);
  }
} /* End of 'VG4_RndShadersUpdate' function */

/* END OF 'rndshd.c' FILE */
