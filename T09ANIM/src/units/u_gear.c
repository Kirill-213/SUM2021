/* FILE NAME : u_gear.c
 * PROGRAMMER: KV6
 * DATE : 27.06.2021
 * PURPOSE : Createswsasdasdasd texture unit
 */

#include <stdio.h>

#include "units.h"

typedef struct tagKV6UNIT_Gear
{
  UNIT_BASE_FIELDS;
  kv6PRIMS Gear;
  FLT AngleToRotY;
  VEC Pos;
  INT TexNo;
} kv6UNIT_Gear;

/* Cow unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       KV6UNIT_Gear *Uni;
 *   - animation context:
 *       KV6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KV6_UnitInit( kv6UNIT_Gear *Uni, kv6ANIM *Ani )
{
  KV6_RndPrimsLoad(&Uni->Gear, "BIN/MODELS/BTR.g3dm");
} /* End of 'KV6_UnitInit' function */

/* Cow unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       KV6UNIT_COW *Uni;
 *   - animation context:
 *       KV6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KV6_UnitResponse( kv6UNIT_Gear *Uni, kv6ANIM *Ani )
{
} /* End of 'KV6_UnitResponse' function */

/* Cow unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       KV6UNIT_Gear *Uni;
 *   - animation context:
 *       KV6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KV6_UnitClose( kv6UNIT_Gear *Uni, kv6ANIM *Ani )
{
  KV6_RndPrimsFree(&Uni->Gear);
} /* End of 'KV6_UnitResponse' function */

/* Cow unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       KV6UNIT_COW *Uni;
 *   - animation context:
 *       KV6ANIM *Ani;
 * RETURNS: None.
 */
static VOID KV6_UnitRender( kv6UNIT_Gear *Uni, kv6ANIM *Ani )
{
  KV6_RndPrimsDraw(&Uni->Gear, MatrMulMatr3(MatrScale(VecSet1(0.1)), MatrRotateY(0), MatrTranslate(VecSet(0, 0, 0))));
} /* End of 'KV6_UnitRender' function */

/* Unit cow creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (KV6UNIT *) pointer to created unit.
 */
kv6UNIT * KV6_UnitCreateGear( VOID )
{
  kv6UNIT *Uni;

  if ((Uni = (kv6UNIT *)KV6_AnimUnitCreate(sizeof(kv6UNIT_Gear))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)KV6_UnitInit;
  Uni->Response = (VOID *)KV6_UnitResponse;
  Uni->Render = (VOID *)KV6_UnitRender;
  Uni->Close = (VOID *)KV6_UnitClose;

  return Uni;
} /* End of 'KV6_UnitCreateGear' function */


/* END OF 'u_gear.c' FUNCTION */