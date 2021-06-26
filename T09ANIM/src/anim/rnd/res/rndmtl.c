/* FILE NAME: rndmtl.c
 * PROGRAMMER: KV6
 * DATE: 26.06.2021
 * PURPOSE: Material module
 */

#include "../rnd.h"

kv6MATERIAL KV6_RndMaterials[KV6_MAX_MATERIALS];
INT KV6_RndMaterialsSize;

/* RndMtlAdd */
INT KV6_RndMtlAdd( kv6MATERIAL *Mtl )
{
  if (KV6_RndMaterialsSize >= KV6_MAX_MATERIALS)
    return 0;
  KV6_RndMaterials[KV6_RndMaterialsSize] = *Mtl;
  return KV6_RndMaterialsSize++;
} /* End of 'KV6_RndMtlAdd' function */


/* RndMtlInit */
VOID KV6_RndMtlInit( VOID )
{
  INT i;
  kv6MATERIAL mtl = {{0}};

  strcpy(mtl.Name, "DEFAULT");
  mtl.Ka = VecSet1(0.1);
  mtl.Kd = VecSet1(1);
  mtl.Ks = VecSet1(0.0);
  mtl.Ph = 30;
  mtl.Trans = 1;
  mtl.ShdNo = 0;
  for (i = 0; i < 8; i++)
    mtl.Tex[i] = -1;

  KV6_RndMaterialsSize = 0;
  KV6_RndMtlAdd(&mtl);
} /* End of 'KV6_RndMtlInit' function */


/* RndMtlClose */
VOID KV6_RndMtlClose( VOID )
{
  KV6_RndMaterialsSize = 0;
} /* End of 'KV6_RndMtlClose' function */


/* Get default material function */
kv6MATERIAL KV6_RndMtlGetDeg( VOID )
{
  return KV6_RndMaterials[0];
} /* End of 'KV6_RndMtlGetDef' function */


/* Get material pointer function */
kv6MATERIAL * KV6_RndMtlGet( INT MtlNo )
{
  if (MtlNo < 0 || MtlNo >= KV6_RndMaterialsSize)
    MtlNo = 0;
  return &KV6_RndMaterials[MtlNo];
} /* End of 'KV6_RndMtlGet' function */


/* RndMtlApply */
INT KV6_RndMtlApply( INT MtlNo )
{
  INT prg, loc, i;
  kv6MATERIAL *mtl;

  /* Set material pointer */
  mtl = KV6_RndMtlGet(MtlNo);

  /* Set shader program Id */
  prg = mtl->ShdNo;
  if (prg < 0 || prg >= KV6_RndShadersSize)
    prg = 0;
  prg = KV6_RndShaders[prg].ProgId;

  glUseProgram(prg);
  /* Set shading parameters */
  if ((loc = glGetUniformLocation(prg, "Ka")) != -1)
    glUniform3fv(loc, 1, &mtl->Ka.X);
  if ((loc = glGetUniformLocation(prg, "Kd")) != -1)
    glUniform3fv(loc, 1, &mtl->Kd.X);
  if ((loc = glGetUniformLocation(prg, "Ks")) != -1)
    glUniform3fv(loc, 1, &mtl->Ks.X);
  if ((loc = glGetUniformLocation(prg, "Ph")) != -1)
    glUniform1f(loc, mtl->Ph);
  if ((loc = glGetUniformLocation(prg, "Trans")) != -1)
    glUniform1f(loc, mtl->Trans);

  /* Set textures */
  for (i = 0; i < 8; i++)
  {
    CHAR tname[] = "IsTexture0";  /* --> shader: uniform bool IsTexture2; */

    tname[9] = '0' + i;
    if (mtl->Tex[i] != -1)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, KV6_RndTextures[mtl->Tex[i]].TexId);
    }
    if ((loc = glGetUniformLocation(prg, tname)) != -1)
      glUniform1i(loc, mtl->Tex[i] != -1);
  }
  return prg;
} /* End of 'KV6_RndMtlApply' function */


/* RndMtlFree */
VOID KV6_RndMtlFree( INT MtlNo )
{
} /* End of 'KV6_RndMtlFree' function */

/* END OF 'rndmtl.c' FILE */