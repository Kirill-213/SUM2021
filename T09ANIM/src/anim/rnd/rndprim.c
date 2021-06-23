/* FILE NAME: rndprim.c
 * PROGRAMMER: KV6
 * DATE: 21.06.2021
 * PURPOSE: 3D animation primitive handle module.
 */
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "rnd.h"

#if 0
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
#endif

/* KV6_RndPrimCreate */ 
VOID KV6_RndPrimCreate( kv6PRIM *Pr, kv6VERTEX *V, INT NumOfV, INT *I, INT NumOfI )
{
  memset(Pr, 0, sizeof(kv6PRIM));   /* <-- <string.h> */

  if (V != NULL && NumOfV != 0)
  {
    glGenBuffers(1, &Pr->VBuf);
    glGenVertexArrays(1, &Pr->VA);

    glBindVertexArray(Pr->VA);
    glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kv6VERTEX) * NumOfV, V, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(kv6VERTEX),
                          (VOID *)0); /* position */
    glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(kv6VERTEX),
                          (VOID *)sizeof(VEC)); /* texture coordinates */
    glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(kv6VERTEX),
                          (VOID *)(sizeof(VEC) + sizeof(VEC2))); /* normal */
    glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(kv6VERTEX),
                          (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2))); /* color */

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glBindVertexArray(0);
  }

  if (I != NULL && NumOfI != 0)
  {
    glGenBuffers(1, &Pr->IBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NumOfI, I, GL_STATIC_DRAW);
    Pr->NumOfElements = NumOfI;
  }
  else
    Pr->NumOfElements = NumOfV;
  Pr->Trans = MatrIdentity();
}
/* End of 'KV6_RndPrimCreate' function */


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

  /* Send matrix to OpenGL /v.1.0 */
  glLoadMatrixf(wvp.A[0]);
  
  glBindVertexArray(Pr->VA);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
  glDrawElements(GL_TRIANGLES, Pr->NumOfElements, GL_UNSIGNED_INT, NULL);
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}/* End of  'KV6_PrimDraw' function */

/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       kv6PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL KV6_RndPrimLoad( kv6PRIM *Pr, CHAR *FileName )
{
  FILE *F;
  INT i, nv = 0, nind = 0, size;
  kv6VERTEX *V;
  INT *Ind;
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
        if (isspace((UCHAR)Buf[i - 1]) && !isspace((UCHAR)Buf[i]))
          n++;
      nind += (n - 2) * 3;
    }
  }

  size = sizeof(kv6VERTEX) * nv + sizeof(INT) * nind;
  if ((V = malloc(size)) == NULL)
    return FALSE;
  Ind = (INT *)(V + nv);
  memset(V, 0, size);

  /* Load primitive */
  rewind(F);
  nv = 0;
  nind = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;
      VEC4 c = {100, 220, 60, 1};

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      V[nv].C = c;
      V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0, n0, n1, nc;

      for (i = 1; Buf[i] != 0; i++)
        if (isspace((UCHAR)Buf[i - 1]) && !isspace((UCHAR)Buf[i]))
        {
          sscanf(Buf + i, "%i", &nc);
          if (nc < 0)
            nc = nv + nc;
          else
            nc--;

          if (n == 0)
            n0 = nc;
          else if (n == 1)
            n1 = nc;
          else
          {
            Ind[nind++] = n0;
            Ind[nind++] = n1;
            Ind[nind++] = nc;
            n1 = nc;
          }
          n++;
        }
    }
  }
  fclose(F);
  KV6_RndPrimCreate(Pr, V, nv, Ind, nind);
  free(V);
  return TRUE;
} /* End of 'KV6_RndPrimLoad' function */


#if 0
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
#endif

/* KV6_RndPrimCreateGrid */
VOID KV6_RndPrimCreateGrid( kv6PRIM *Pr, INT Grid_W, INT Grid_H, kv6VERTEX *V )
{
  INT i, j, k;
  INT *Ind;

  if ((Ind = malloc(sizeof(INT) * (Grid_W - 1) * (Grid_H - 1) * 6)) == NULL)
    return;

  for (k = 0, i = 0; i < Grid_H - 1; i++)
    for (j = 0; j < Grid_W - 1; j++)
    {
      Ind[k++] = i * Grid_W + j;
      Ind[k++] = i * Grid_W + j + 1;
      Ind[k++] = (i + 1) * Grid_W + j;

      Ind[k++] = (i + 1) * Grid_W + j;
      Ind[k++] = i * Grid_W + j + 1;
      Ind[k++] = (i + 1) * Grid_W + j + 1;
    }

  KV6_RndPrimCreate(Pr, V, Grid_W * Grid_H , Ind, (Grid_W - 1) * (Grid_H - 1) * 6);
  free(Ind);
}/* End of 'KV6_RndPrimCreateGrid' function */


/* KV6_RndPrimCreatePlane */
/*
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
}
*/
/* KV6_RndPrimCreatePlane */

/* END OF 'rndprim.c' FILE */