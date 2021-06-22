 /* FILE NAME: rndprim.c
 * PROGRAMMER: KV6
 * DATE: 21.06.2021
 * PURPOSE: 3D animation primitive handle module.
 */
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "rnd.h"

/* KV6_RndPrimCreate */
BOOL KV6_RndPrimCreate( kv6PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;
  memset(Pr, 0, sizeof(kv6PRIM));
  size = sizeof(kv6VERTEX) * NoofV + sizeof(INT) * NoofI;

  if ((Pr->V = malloc(size)) == NULL)
    return FALSE;
  Pr->I = (INT *)(Pr->V + NoofV);
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;
  Pr->Trans = MatrIdentity();
  memset(Pr->V, 0, size);

  return TRUE;
}/* End of 'KV6_RndPrimCreate' function */

/* KV6_RndPrimFree */
VOID KV6_RndPrimFree( kv6PRIM *Pr )
{
  if (Pr->V != NULL)
    free(Pr->V);
  memset(Pr, 0, sizeof(kv6PRIM));
}/* KV6_PrimFree */

/* KV6_PrimDraw */
VOID KV6_RndPrimDraw( kv6PRIM *Pr, MATR World )
{
  MATR wvp = MatrMulMatr3(Pr->Trans, World, KV6_RndMatrVP);
  INT i;

  /* Send matrix to OpenGL /v.1.0 */
  glLoadMatrixf(wvp.A[0]);
  /*
  glLoadIdentity();
  glScaled(0.1, 0.1, 0.1);
  */

  /* Draw triangles */
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin(GL_TRIANGLES);

  glColor3d(0, 1, 0);
  for (i = 0; i < Pr->NumOfI; i++)
    glVertex3fv(&Pr->V[Pr->I[i]].P.X);
  glEnd();
}/* End of  'KV6_PrimDraw' function */

/* KV6_RndPrimLoad */
BOOL KV6_RndPrimLoad( kv6PRIM *Pr, CHAR *FileName )
{
  FILE *F;
  INT i, nv = 0, nind = 0;
  static CHAR Buf[1000];

  memset(Pr, 0, sizeof(kv6PRIM));
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertexes and indexes */
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0;

      for (i = 1; Buf[i] != 0; i++)
        if (Buf[i - 1] == ' ' && Buf[i] != ' ')
          n++;
      nind += (n - 2) * 3;
    }
  }

  if (!KV6_RndPrimCreate(Pr, nv, nind))
  {
    fclose(F);
    return FALSE;
  }

  /* Load primitive */
  rewind(F);
  nv = 0;
  nind = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      Pr->V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0, n0, n1, nc;

      for (i = 1; Buf[i] != 0; i++)
        if (Buf[i - 1] == ' ' && Buf[i] != ' ')
        {
          sscanf(Buf + i, "%i", &nc);
          nc--;

          if (n == 0)
            n0 = nc;
          else if (n == 1)
            n1 = nc;
          else
          {
            Pr->I[nind++] = n0;
            Pr->I[nind++] = n1;
            Pr->I[nind++] = nc;
            n1 = nc;
          }
          n++;
        }
    }
  }

  fclose(F);
  return TRUE;
} /* End of 'KV6_RndPrimLoad' function */

/* KV6_RndPrimCreatePlane */
VOID KV6_RndPrimCreatePlane( kv6VERTEX *Pr, VEC P, VEC Du, VEC Dv, INT SplitW, INT SplitH )
{
  INT i, j;
  kv6VERTEX *V;

  if ((V = malloc(sizeof(kv6VERTEX) * SplitW * SplitH)) == NULL)
    return;
  
  for (i = 0; i < SplitW; i++)
    for (j = 0; j < SplitH; j++)
      V[i * SplitW + j].P = VecAddVec3(P, VecMulNum(Du, j / (SplitW - 1.0)), VecMulNum(Dv, i / SplitH - 1.0));

  KV6_RndPrimCreateGrid(Pr, SplitW, SplitH, V);
  free(V);
}/* KV6_RndPrimCreatePlane */

/* END OF 'rndprim.c' FILE */