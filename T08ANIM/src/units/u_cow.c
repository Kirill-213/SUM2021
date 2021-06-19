/* FILE NAME: u_cow.c
 * PROGRAMMER: KV6
 * DATE: 19.06.2021
 * PURPOSE:
 */

#include <time.h>

#include "units.h"

/* typedef kv6UNIT_BALL */
typedef struct
{
  UNIT_BASE_FIELDS;
  kv6PRIM Cow;
  VEC Pos;
} kv6UNIT_COW;

/* Bounce ball unit initialization function
 * ARGUMENTS:
 *   - self-pointer to unit object
 *      kv6UNIT_BALL *Uni;
 *   - animation context:
 *      kv6ANIM *Ani;
 * RETURNS: None.
  */
static VOID KV6_UnitInit( kv6UNIT_COW *Uni, kv6ANIM *Ani )
{
  KV6_RndPrimLoad(&Uni->Cow, "Harley.obj");
}/* End of 'KV6_UnitInit' function */


/* Bounce ball unit inter frame events handle function
 * ARGUMENTS:
 *   - self-pointer to unit object
 *      kv6UNIT_BALL *Uni;
 *   - animation context:
 *      kv6ANIM *Ani;
 * RETURNS: None.
  */
static VOID KV6_UnitResponse( kv6UNIT_COW *Uni, kv6ANIM *Ani )
{
}/* End of 'KV6_UnitResponse' function */


/* Bounce ball unit render function
 * ARGUMENTS:
 *   - self-pointer to unit object
 *      kv6UNIT_BALL *Uni;
 *   - animation context:
 *      kv6ANIM *Ani;
 * RETURNS: None.
  */
static VOID KV6_UnitRender( kv6UNIT_COW *Uni, kv6ANIM *Ani )
{
  KV6_RndPrimDraw(&Uni->Cow, MatrMulMatr3(MatrScale(VecSet1(0.1)), MatrRotateZ(180), MatrRotateX(10)));
}/* End of 'KV6_UnitRender' function */


/* Unit ball creation function
 * ARGUMENTS: None.
 * RETURNS:
 *   (kv6UNIT *) pointer to created unit
  */
kv6UNIT * KV6_UnitCreateCow( VOID )
{
  kv6UNIT *Uni;

  if ((Uni = (kv6UNIT *)KV6_AnimUnitCreate(sizeof(kv6UNIT_COW))) == NULL)
    return NULL;
  
  /* Setup unit methods */
  Uni->Init = (VOID *)KV6_UnitInit;
  Uni->Response = (VOID *)KV6_UnitResponse;
  Uni->Render = (VOID *)KV6_UnitRender;

  return Uni;
}/* End of 'KV6_UnitCreateCow' function */

