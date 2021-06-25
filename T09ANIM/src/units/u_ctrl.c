/* FILE NAME: u_cow.c
 * PROGRAMMER: KV6
 * DATE: 25.06.2021
 * PURPOSE: multimedia module
 */

#include <stdio.h>
#include "units.h"


/* typedef kv6INIT_ctrl */
typedef struct tagkv6UNIT_ctrl
{
  UNIT_BASE_FIELDS;
  DBL AngleSpeed;
  VEC CamLoc, CamDir, CamDist;
  VEC At;
  VEC Dir;
  VEC Right;
  INT Speed;

} kv6UNIT_ctrl;

/* Cow unit initialization function
 * ARGUMENTS:
 *   - self-pointer to unit object
 *      kv6UNIT_BALL *Uni;
 *   - animation context:
 *      kv6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KV6_UnitInit( kv6UNIT_ctrl *Uni, kv6ANIM *Ani )
{

  Uni->CamLoc = VecSet(0, 3, 10);
  Uni->Speed = 15;
  Uni->AngleSpeed = 15;
  Uni->At = VecSet1(0);
  Uni->Dir = VecNormalize(VecSubVec(Uni->At, Uni->CamLoc));
  Uni->Right = VecNormalize(VecCrossVec(Uni->Dir, VecSet(0, 1, 0)));

}/* End of 'KV6_UnitInit' function */


/* Cow unit inter frame events handle function
 * ARGUMENTS:
 *   - self-pointer to unit object
 *      kv6UNIT_BALL *Uni;
 *   - animation context:
 *      kv6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KV6_UnitResponse( kv6UNIT_ctrl *Uni, kv6ANIM *Ani )
{

  /* wasd */

  if (Ani->Keys['S'] || Ani->Keys['W'])
  {
    Uni->CamLoc = VecAddVec(Uni->CamLoc, VecMulNum(Uni->Dir, Ani->GlobalDeltaTime * Uni->Speed * (Ani->Keys['W'] - Ani->Keys['S'])));
    Uni->At = VecAddVec(Uni->At, VecMulNum(Uni->Dir, Ani->GlobalDeltaTime * Uni->Speed * (Ani->Keys['W'] - Ani->Keys['S'])));
  }
  if (Ani->Keys['A'] || Ani->Keys['D'])
    Uni->CamLoc = VecAddVec(Uni->CamLoc, VecMulNum(Uni->Right, Ani->GlobalDeltaTime * Uni->Speed * (Ani->Keys['D'] - Ani->Keys['A'])));

  /* mouse */

  if (Ani->Mdz)
    Uni->CamLoc = VecAddVec(Uni->CamLoc, VecMulNum(Uni->Dir, Ani->GlobalDeltaTime * Uni->Speed * Ani->Mdz * 0.03));

  if (Ani->Keys[VK_LBUTTON])
    Uni->CamLoc = PointTransform(Uni->CamLoc, MatrRotateY(-Ani->Keys[VK_LBUTTON] * Ani->GlobalDeltaTime * Uni->AngleSpeed * Ani->Mdx * 30));

  if (Ani->Keys[VK_RBUTTON])
    Uni->CamLoc = PointTransform(Uni->CamLoc, MatrRotateX(-Ani->Keys[VK_RBUTTON] * Ani->GlobalDeltaTime * Uni->AngleSpeed * Ani->Mdy * 30));


  /* arrows */

  if (Ani->Keys[VK_DOWN] || Ani->Keys[VK_UP])
  {
    Uni->CamLoc.Y += Ani->GlobalDeltaTime * Uni->Speed * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]);
    Uni->At.Y += Ani->GlobalDeltaTime * Uni->Speed * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]);
  }
  if (Ani->Keys[VK_RIGHT] || Ani->Keys[VK_LEFT])
  {
    Uni->CamLoc = VecAddVec(Uni->CamLoc, VecMulNum(Uni->Right, (Ani->Keys[VK_RIGHT] - Ani->Keys[VK_LEFT]) * 10 * Ani->GlobalDeltaTime));
    Uni->At = VecAddVec(Uni->At, VecMulNum(Uni->Right, (Ani->Keys[VK_RIGHT] - Ani->Keys[VK_LEFT]) * 10 * Ani->GlobalDeltaTime));
  }

  Uni->Dir = VecNormalize(VecSubVec(Uni->At, Uni->CamLoc));
  Uni->Right = VecNormalize(VecCrossVec(Uni->Dir, VecSet(0, 1, 0)));
  KV6_RndCamLoc = Uni->CamLoc;
  KV6_RndCamRight = Uni->Right;
  KV6_RndCamAt = Uni->At;
  KV6_RndCamDir = Uni->Dir;
  KV6_RndCamUp = VecSet(0, 1, 0);

}/* End of 'KV6_UnitResponse' function */


/* KV6_UnitClose */
static VOID KV6_UnitClose( kv6UNIT_ctrl *Uni, kv6ANIM *Ani )
{
} /* End of 'KV6_UnitResponse' function */


/* KV6_UnitRender */
static VOID KV6_UnitRender( kv6UNIT_ctrl *Uni, kv6ANIM *Ani )
{
  KV6_RndCamSet(Uni->CamLoc, Uni->At, VecSet(0, 1, 0));
}/* End of 'KV6_UnitRender' function */


/* KV6_UnitCreateCtrl */
kv6UNIT * KV6_UnitCreateCtrl( VOID )
{
  kv6UNIT *Uni;

  if ((Uni = KV6_AnimUnitCreate(sizeof(kv6UNIT_ctrl))) == NULL)
    return NULL;
  
  /* Setup unit methods */
  Uni->Init = (VOID *)KV6_UnitInit;
  Uni->Response = (VOID *)KV6_UnitResponse;
  Uni->Render = (VOID *)KV6_UnitRender;
  Uni->Close = (VOID *)KV6_UnitClose;

  return Uni;
}/* End of 'KV6_UnitCreateCtrl' function */
