/* FILE NAME: u_tex.c
 * PROGRAMMER: KV6
 * DATE: 26.06.2021
 * PURPOSE: texture unit module
 */

#include <stdio.h>
#include "units.h"

typedef struct tagkv6UNIT_TEXPRIM
{
  UNIT_BASE_FIELDS;
  kv6PRIM Pr;           /* Primitive */
  INT TexId;            /* Texture OpenGL Id */
} kv6UNIT_TEXPRIM;

/* KV6_UnitInit */
static VOID KV6_UnitInit( kv6UNIT_TEXPRIM *Uni, kv6ANIM *Ani )
{
    kv6VERTEX V[] =
  {
    {{-10, 0, 0}, {0, 1}, {0, 0, 1}, {1, 1, 1, 1}},
    {{10, 0, 0}, {1, 1}, {0, 0, 1}, {1, 1, 1, 1}},
    {{-10, 20, 0}, {0, 0}, {0, 0, 1}, {1, 1, 1, 1}},
    {{10, 20, 0}, {1, 0}, {0, 0, 1}, {1, 1, 1, 1}},
  };

  FILE *F;

  glGenTextures(1, &Uni->TexId);

  /* open file */
  if ((F = fopen("X:/PICS/gr.G24", "rb")) != NULL)
  {
    INT w = 0, h = 0;
    BYTE *mem;

    /* get w,h from file */
    fread(&w, 2, 1, F);
    fread(&h, 2, 1, F);

    if ((mem = malloc(w * h * 3)) != NULL)
    {
      INT n;

      fread(mem, 3, w * h, F);

      glBindTexture(GL_TEXTURE_2D, Uni->TexId);
      /* glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, mem); */

      n = log(w > h ? w : h) / log(2);
      n = n < 1 ? 1 : n;

      glTexStorage2D(GL_TEXTURE_2D, n, GL_RGB8, w, h);
      glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_BGR, GL_UNSIGNED_BYTE, mem);
      
      glGenerateMipmap(GL_TEXTURE_2D);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

      free(mem);
    }
    fclose(F);
  }
  KV6_RndPrimCreateGrid(&Uni->Pr, 2, 2, V);
}/* End of 'KV6_UnitInit' function */


/* KV6_UnitResponse */
static VOID KV6_UnitResponse( kv6UNIT_TEXPRIM *Uni, kv6ANIM *Ani )
{
  if (Ani->KeysClick['1'])
  {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }
  else if (Ani->KeysClick['2'])
  {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }
  else if (Ani->KeysClick['3'])
  {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  }

}/* End of 'KV6_UnitResponse' function */


/* KV6_UnitRender */
static VOID KV6_UnitRender( kv6UNIT_TEXPRIM *Uni, kv6ANIM *Ani )
{
  glActiveTexture(GL_TEXTURE0 + 1);
  glBindTexture(GL_TEXTURE_2D, Uni->TexId);

  KV6_RndPrimDraw(&Uni->Pr, MatrIdentity());
}/* End of 'KV6_UnitRender' function */


/* KV6_UnitClose */
static VOID KV6_UnitClose( kv6UNIT_TEXPRIM * Uni, kv6ANIM *Ani )
{
  KV6_RndPrimFree(&Uni->Pr);
}/* End of 'KV6_UnitClose' function */


/* KV6_UnitCreateTexPrim */
kv6UNIT * KV6_UnitCreateTexPrim( VOID )
{
  kv6UNIT *Uni;

  if ((Uni = (kv6UNIT *)KV6_AnimUnitCreate(sizeof(kv6UNIT_TEXPRIM))) == NULL)
    return NULL;
  
  /* Setup unit methods */
  Uni->Init = (VOID *)KV6_UnitInit;
  Uni->Response = (VOID *)KV6_UnitResponse;
  Uni->Render = (VOID *)KV6_UnitRender;
  Uni->Close = (VOID *)KV6_UnitClose;

  return Uni;
}/* End of 'KV6_UnitCreateTexPrim' function */

/* END OF 'u_tex.c' FILE */