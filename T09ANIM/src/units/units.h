/* FILE NAME: units.c
 * PROGRAMMER: KV6
 * DATE: 21.06.2021
 * PURPOSE: 3D animation primitive handle module.
 */

#include "../anim/anim.h"

/* UNITS */
/* KV6_Unit */
VOID KV6_Unit( kv6UNIT *Uni, kv6ANIM *Ani );

/* KV6_AnimUnitCreate */
kv6UNIT * KV6_AnimUnitCreate( INT Size );

/* KV6_UnitCreateCow */
kv6UNIT * KV6_UnitCreateCow( VOID );

/* KV6_UnitCreateCtrl */
kv6UNIT * KV6_UnitCreateCtrl( VOID );

/* UnitCreatePlate */
kv6UNIT * KV6_UnitCreatePlane( VOID );

VEC 
  KV6_RndCamLoc,
  KV6_RndCamRight,
  KV6_RndCamAt, 
  KV6_RndCamDir,
  KV6_RndCamUp;

/* END OF 'units.c' FILE */