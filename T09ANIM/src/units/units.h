/* FILE NAME: units.c
 * PROGRAMMER: KV6
 * DATE: 21.06.2021
 * PURPOSE: 3D animation primitive handle module.
 */

#include "../anim/anim.h"

/* Unit initialization function.
 * ARGUMENTS:
 *    -self-pointer to unit object:
 *       kv6UNIT *Uni;
 *    -animation context:
 *       kv6ANIM *Ani;
 * RETURNS: None
*/
VOID KV6_UnitInit( kv6UNIT *Uni, kv6ANIM *Ani );

/* Unit deinitialization function.
 * ARGUMENTS:
 *    -self-pointer to unit object:
 *       kv6UNIT *Uni;
 *    -animation context:
 *       kv6ANIM *Ani;
 * RETURNS: None
 */
VOID KV6_UnitClose( kv6UNIT *Uni, kv6ANIM *Ani );


/* Unit inter frame events handle fucntion.
 * ARGUMENTS:
 *    -self-pointer to unit object:
 *       kv6UNIT *Uni;
 *    -animation context:
 *       kv6ANIM *Ani;
 * RETURNS: None
 */
VOID KV6_UnitResponse( kv6UNIT *Uni, kv6ANIM *Ani );

/* Unit render function.
 * ARGUMENTS:
 *    -self-pointer to unit object:
 *       kv6UNIT *Uni;
 *    -animation context:
 *       kv6ANIM *Ani;
 * RETURNS: None
 */
VOID KV6_UnitRenser( kv6UNIT *Uni, kv6ANIM *Ani );

/* Unit deinitialization function.
 * ARGUMENTS:
 *    -self-pointer to unit object:
 *       kv6UNIT *Uni;
 *    -animation context:
 *       kv6ANIM *Ani;
 * RETURNS: None
 */
VOID KV6_Unit( kv6UNIT *Uni, kv6ANIM *Ani );

/* Unit creation function
 * ARGUMENTS:
 *    -unit structure size in bytes
 *       INT Size;
 * RETURNS:
 *   (kv6UNIT *) pointer to created unit
 */
kv6UNIT * KV6_AnimUnitCreate( INT Size );

/* Unit ball creation function
 * ARGUMENTS: None.
 * RETURNS:
 *   (kv6UNIT *) pointer to created unit
  */
kv6UNIT * KV6_UnitCreateCow( VOID );

/* END OF 'units.c' FILE */