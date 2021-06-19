/* FILE NAME: unit.c
 * PROGRAMMER: KV6
 * DATE: 19.06.2021
 * PURPOSE: 3D animation primitive handle module.
 */

#include "anim.h"

/* Unit initialization function.
 * ARGUMENTS:
 *    -self-pointer to unit object:
 *       kv6UNIT *Uni;
 *    -animation context:
 *       kv6ANIM *Ani;
 * RETURNS: None
*/
static VOID KV6_UnitInit( kv6UNIT *Uni, kv6ANIM *Ani )
{
}/* End of 'KV6_UnitIit' function */


/* Unit deinitialization function.
 * ARGUMENTS:
 *    -self-pointer to unit object:
 *       kv6UNIT *Uni;
 *    -animation context:
 *       kv6ANIM *Ani;
 * RETURNS: None
 */
static VOID KV6_UnitClose( kv6UNIT *Uni, kv6ANIM *Ani )
{
}/* End of 'KV6_UnitResponse' function */


/* Unit inter frame events handle fucntion.
 * ARGUMENTS:
 *    -self-pointer to unit object:
 *       kv6UNIT *Uni;
 *    -animation context:
 *       kv6ANIM *Ani;
 * RETURNS: None
 */
static VOID KV6_UnitResponse( kv6UNIT *Uni, kv6ANIM *Ani )
{
}/* End of 'KV6_UnitResponse' function */


/* Unit render function.
 * ARGUMENTS:
 *    -self-pointer to unit object:
 *       kv6UNIT *Uni;
 *    -animation context:
 *       kv6ANIM *Ani;
 * RETURNS: None
 */
static VOID KV6_UnitRender( kv6UNIT *Uni, kv6ANIM *Ani )
{
}/* End of 'KV6_UnitRender' function */


/* Unit deinitialization function.
 * ARGUMENTS:
 *    -self-pointer to unit object:
 *       kv6UNIT *Uni;
 *    -animation context:
 *       kv6ANIM *Ani;
 * RETURNS: None
 */
static VOID KV6_Unit( kv6UNIT *Uni, kv6ANIM *Ani )
{
}/* End of 'KV6_UnitClose' function */


/* Unit creation function
 * ARGUMENTS:
 *    -unit structure size in bytes
 *       INT Size;
 * RETURNS:
 *   (kv6UNIT *) pointer to created unit
 */
kv6UNIT * KV6_AnimUnitCreate( INT Size )
{
  kv6UNIT *Uni;
  /* Memory allocation */
  if (Size < sizeof(kv6UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);

  /* Setup unit methods */
  Uni->Init = KV6_UnitInit;
  Uni->Close = KV6_UnitClose;
  Uni->Response = KV6_UnitResponse;
  Uni->Render = KV6_UnitRender;

  return Uni;
}/* End of 'KV6_AnimUnitCreate' function */

/* END OF 'unit.' FILE */