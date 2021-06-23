/* FILE NAME: u_plane.c
 * PROGRAMMER: KV6
 * DATE: 22.06.2021
 * PURPOSE: Create plane for scene
 */

#include "units.h"

/* typedef kv6INIT_plate */
typedef struct tagkv6UNIT_plane
{
  UNIT_BASE_FIELDS;
  kv6PRIM Plane;
  VEC Pos;

} kv6UNIT_PLANE;

/* KV6_UnitInit */
static VOID KV6_UnitInit( kv6UNIT_PLANE *Uni, kv6ANIM *Ani )
{
  KV6_RndPrimCreatePlane(&Uni->Plane, VecSet(-2, 0, -2), VecSet(10, 0, 0), VecSet(0, 0, 10), 8, 8);
}/* End of 'KV6_UnitInit' function */

/* KV6_UnitResponse */
///static VOID KV6_UnitResponse( kv6UNIT_PLANE *Uni, kv6ANIM *Ani )
///{

///}/* KV6_UnitResponse */

/* KV6_UnitClose */
static VOID KV6_UnitClose( kv6UNIT_PLANE * Uni, kv6ANIM *Ani )
{
  KV6_RndPrimFree(&Uni->Plane);
}/* End of function */

/* KV6_UnitRender */
static VOID KV6_UnitRender( kv6UNIT_PLANE * Uni, kv6ANIM *Ani )
{
  KV6_RndPrimDraw(&Uni->Plane, MatrIdentity());
}/* End of 'KV6_UnitRender' function */

/* KV6_UnitCreatePlate */
kv6UNIT * KV6_UnitCreatePlane( VOID )
{
  kv6UNIT *Uni;

  if ((Uni = (kv6UNIT *)KV6_AnimUnitCreate(sizeof(kv6UNIT_PLANE))) == NULL)
    return NULL;
  
  /* Setup unit methods */
  Uni->Init = (VOID *)KV6_UnitInit;
///  Uni->Response = (VOID *)KV6_UnitResponse;
  Uni->Render = (VOID *)KV6_UnitRender;
  Uni->Close = (VOID *)KV6_UnitClose;

  return Uni;
}/* End of 'KV6_UnitCreatePlate' function */


/* END OF 'u_plane.c' FILE */