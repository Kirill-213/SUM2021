/* FILE NAME: input.c
 * PROGRAMMER: KV6
 * DATE: 21.06.2021
 * PURPOSE: Integration multimedia data.
 */

#include "anim.h"

/* AnimKeyboardInit */
static VOID KV6_AnimKeyboardInit( VOID )
{
  INT i;

  for (i = 0; i < 256; i++)
  {
    KV6_Anim.Keys[i] = 0;
    KV6_Anim.KeysClick[i] = 0;
    KV6_Anim.KeysOld[i] = 0;
  }
}/* End of 'AnimKeyboardInit' function */


/* UnitResponse */
static VOID KV6_AnimKeyboardResponse( VOID )
{
  INT i;

  GetKeyboardState(KV6_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    KV6_Anim.Keys[i] >>= 7;
    KV6_Anim.KeysClick[i] = KV6_Anim.Keys[i] && !KV6_Anim.KeysOld[i];
  }
  memcpy(KV6_Anim.KeysOld, KV6_Anim.Keys, 256);
}/* End of 'UnitResponse' function */


/* KV6_AnimInputInit */
VOID KV6_AnimInputInit( VOID )
{
  KV6_AnimKeyboardInit();
}/* KV6_AnimInputInit */


/* KV6_AnimInputResponse */
VOID KV6_AnimInputResponse( VOID )
{
  KV6_AnimKeyboardResponse();
}/* KV6_AnimInputResponse */


/* END OF 'input.c' FILE */