/* FILE NAME: u_cow.c
 * PROGRAMMER: KV6
 * DATE: 21.06.2021
 * PURPOSE:
 */

#include <stdio.h>
#include "units.h"
///#include "../anim/anim.h"

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
  Uni->Speed = 100;
  Uni->AngleSpeed = 100;
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
    if (Ani->Keys['S'] || Ani->Keys['W'])
  {
    Uni->CamLoc = VecAddVec(Uni->CamLoc, VecMulNum(Uni->Dir, Ani->GlobalDeltaTime * Uni->Speed * (Ani->Keys['W'] - Ani->Keys['S'])));
    Uni->At = VecAddVec(Uni->At, VecMulNum(Uni->Dir, Ani->GlobalDeltaTime * Uni->Speed * (Ani->Keys['W'] - Ani->Keys['S'])));
  }
  if (Ani->Keys['A'] || Ani->Keys['D'])
    Uni->CamLoc = VecAddVec(Uni->CamLoc, VecMulNum(Uni->Right, Ani->GlobalDeltaTime * Uni->Speed * (Ani->Keys['D'] - Ani->Keys['A'])));

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


/* Unit cow creation function
 * ARGUMENTS: None.
 * RETURNS:
 *   (kv6UNIT *) pointer to created unit
  */
kv6UNIT * KV6_UnitCreateCtrl( VOID )
{
  kv6UNIT *Uni;

  if ((Uni = (kv6UNIT *)KV6_AnimUnitCreate(sizeof(kv6UNIT_ctrl))) == NULL)
    return NULL;
  
  /* Setup unit methods */
  Uni->Init = (VOID *)KV6_UnitInit;
  Uni->Response = (VOID *)KV6_UnitResponse;
  Uni->Render = (VOID *)KV6_UnitRender;
  Uni->Close = (VOID *)KV6_UnitClose;

  return Uni;
}/* End of 'KV6_UnitCreateCtrl' function */
