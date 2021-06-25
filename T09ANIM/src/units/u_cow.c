/* FILE NAME: u_cow.c
 * PROGRAMMER: KV6
 * DATE: 21.06.2021
 * PURPOSE:
 */

#include <time.h>
#include "units.h"

/* typedef kv6UNIT_COW */
typedef struct
{
  UNIT_BASE_FIELDS;
  kv6PRIM Pr;
  MATR Cow;
  VEC Dir;
  VEC Pos;
} kv6UNIT_COW;

/* Cow unit initialization function
 * ARGUMENTS:
 *   - self-pointer to unit object
 *      kv6UNIT_BALL *Uni;
 *   - animation context:
 *      kv6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KV6_UnitInit( kv6UNIT_COW *Uni, kv6ANIM *Ani )
{
  KV6_RndPrimLoad(&Uni->Pr, "BIN/MODELS/Alfa_Romeo.obj");
  Uni->Pos = VecSet1(0);
  Uni->Dir = VecSet(5, 0, 0);
  Uni->Cow = MatrMulMatr(MatrScale(VecSet1(0.4)), MatrTranslate(VecSet(-0.6, -0.5, 0)));
}/* End of 'KV6_UnitInit' function */

/* Cow unit inter frame events handle function
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
  KV6_RndPrimDraw(&Uni->Pr, MatrMulMatr(Uni->Cow, MatrTranslate(Uni->Pos))); 
}/* End of 'KV6_UnitRender' function */


/* Bounce ball unit render function
 * ARGUMENTS:
 *   - self-pointer to unit object
 *      kv6UNIT_BALL *Uni;
 *   - animation context:
 *      kv6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KV6_UnitClose( kv6UNIT_COW * Uni, kv6ANIM *Ani )
{
  KV6_RndPrimFree(&Uni->Pr);
}/* End of 'KV6_UnitClose' function */


/* Unit ball creation function
 * ARGUMENTS: None.
 * RETURNS:
 *   (kv6UNIT *) pointer to created unit
 */
kv6UNIT * KV6_UnitCreateCow( VOID )
{
  kv6UNIT *Uni;

  if ((Uni = KV6_AnimUnitCreate(sizeof(kv6UNIT_COW))) == NULL)
    return NULL;
  
  /* Setup unit methods */
  Uni->Init = (VOID *)KV6_UnitInit;
  Uni->Response = (VOID *)KV6_UnitResponse;
  Uni->Render = (VOID *)KV6_UnitRender;
  Uni->Close = (VOID *)KV6_UnitClose;

  return Uni;
}/* End of 'KV6_UnitCreateCow' function */

/* END OF 'u_cow.c' FILE */