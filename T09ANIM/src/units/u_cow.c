/* FILE NAME: u_cow.c
 * PROGRAMMER: KV6
 * DATE: 25.06.2021
 * PURPOSE: Create cow unit
 */

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


/* KV6_UnitInit */
static VOID KV6_UnitInit( kv6UNIT_COW *Uni, kv6ANIM *Ani )
{
  KV6_RndPrimLoad(&Uni->Pr, "BIN/MODELS/Alfa_Romeo.obj");
  Uni->Pos = VecSet1(0);
  Uni->Dir = VecSet(5, 0, 0);
  Uni->Cow = MatrMulMatr(MatrScale(VecSet1(0.4)), MatrTranslate(VecSet(-0.6, -0.5, 0)));
}/* End of 'KV6_UnitInit' function */


/* KV6_UnitResponse */
static VOID KV6_UnitResponse( kv6UNIT_COW *Uni, kv6ANIM *Ani )
{
}/* End of 'KV6_UnitResponse' function */


/* KV6_UnitRender */
static VOID KV6_UnitRender( kv6UNIT_COW *Uni, kv6ANIM *Ani )
{
  KV6_RndPrimDraw(&Uni->Pr, MatrMulMatr3(Uni->Cow, MatrTranslate(Uni->Pos), MatrRotateX(-90)));
  ///KV6_RndPrimDraw(&Uni->Pr, MatrMulMatr4(Uni->Cow, MatrRotateZ(180 * sin(Ani->Time * 0.5)), MatrRotateY(180 * sin(Ani->Time * 0.5)), MatrRotateX(180 * sin(Ani->Time * 0.5))));
}/* End of 'KV6_UnitRender' function */


/* KV6_UnitClose */
static VOID KV6_UnitClose( kv6UNIT_COW * Uni, kv6ANIM *Ani )
{
  KV6_RndPrimFree(&Uni->Pr);
}/* End of 'KV6_UnitClose' function */


/* KV6_UnitCreateCow */
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