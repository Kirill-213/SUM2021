/* FILE NAME: units.h
 * PROGRAMMER: KV6
 * DATE: 25.06.2021
 * PURPOSE: 3D animation primitive handle module.
 */


#include "../anim/anim.h"
                              

/* KV6_AnimUnitCreate */
kv6UNIT * KV6_AnimUnitCreate( INT Size );
/* KV6_UnitCreateCow */
kv6UNIT * KV6_UnitCreateCow( VOID );
/* KV6_UnitCreateCtrl */
kv6UNIT * KV6_UnitCreateCtrl( VOID );
/* UnitCreateTexPrim */
kv6UNIT * KV6_UnitCreateTexPrim( VOID );
/*UnitCreateGear */
kv6UNIT * KV6_UnitCreateGear( VOID );


/* END OF 'units.h' FILE */