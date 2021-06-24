/* FILE NAME: u_cow.c
 * PROGRAMMER: KV6
 * DATE: 21.06.2021
 * PURPOSE:
 */

#include <time.h>
#include "../anim/anim.h"

/* typedef kv6INIT_ctrl */
typedef struct tagkv6UNIT_ctrl
{
  UNIT_BASE_FIELDS;
  DBL Speed;
  VEC CamLoc, CamDir, CamDist;

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
  Uni->CamLoc = VecSet(0, 0, 30);
  Uni->CamDir = VecSet(0, 1, 0);
  Uni->Speed  = 10;
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
  Uni->
    Uni->RotY += Ani->GlobalDeltaTime * (-0.8 * 30 * Ani->Keys[VK_LBUTTON] * Ani->Mx + 3 * 0.47 * (Ani->) );

    KV6_RndCamSet(PointTransform(VecSetjh));
}/* End of 'KV6_UnitResponse' function */


/* Bounce ball unit render function
 * ARGUMENTS:
 *   - self-pointer to unit object
 *      kv6UNIT_BALL *Uni;
 *   - animation context:
 *      kv6ANIM *Ani;
 * RETURNS: None.
  */
static VOID KV6_UnitRender( VOID )
{
}/* End of 'KV6_UnitRender' function */


/* Unit ball creation function
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

  return Uni;
}/* End of 'KV6_UnitCreateCtrl' function */

