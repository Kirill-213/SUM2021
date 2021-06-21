/* FILE NAME: input.c
 * PROGRAMMER: KV6
 * DATE: 21.06.2021
 * PURPOSE: Integration multimedia data.
 */

#include <anim.h>

/* AnimKeyboardInit */
static VOID KV6_AnimKeyboardInit( VOID )
{
  for (i = 0; i < 256; i++)
  {
    Keys[i] = 0;
    KeysClick[i] = 0;
    KeysOld[i] = 0;
  }
}/* End of 'AnimKeyboardInit' function */

/* UnitResponse */
static VOID KV6_AnimKeyboardResponse( VOID )
{
  INT i;

  GetKeyBoardState(Keys);
  for (i = 0; i < 256; i++)
  {
    Keys[i] >>= 7;
    KeysClick[i] = Keys[i] && !KeysOld[i];
  }
  memcpy(KeysOld, Keys, 256);
}/* End of 'UnitResponse' function */


/* END OF 'input.c' FILE */