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
  KV6_RndPrimLoad(&Uni->Pr, "BIN/MODELS/cow.obj");
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
  Uni->Cow = MatrMulMatr(Uni->Cow, MatrRotate(Ani->DeltaTime * 500 * (Ani->Keys['A'] - Ani->Keys['D']), VecSet(1, 0, 0)));
  Uni->Dir = VectorTransform(Uni->Dir, MatrRotate(Ani->DeltaTime * 100 * (Ani->Keys['A'] - Ani->Keys['D']), VecSet(1, 0, 0)));
  Uni->Pos = VecAddVec(Uni->Pos, VecMulNum(Uni->Dir, Ani->DeltaTime * 10 *(Ani->Keys['W'] - Ani->Keys['S'])));
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
  ///KV6_RndPrimDraw(&Uni->Pr, Uni->Cow);  MatrRotate(Ani->Time * 30, VecSet(1, 1, 0)));
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

  if ((Uni = (kv6UNIT *)KV6_AnimUnitCreate(sizeof(kv6UNIT_COW))) == NULL)
    return NULL;
  
  /* Setup unit methods */
  Uni->Init = (VOID *)KV6_UnitInit;
  Uni->Response = (VOID *)KV6_UnitResponse;
  Uni->Render = (VOID *)KV6_UnitRender;
  Uni->Close = (VOID *)KV6_UnitClose;

  return Uni;
}/* End of 'KV6_UnitCreateCow' function */
