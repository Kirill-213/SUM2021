/* FILE NAME: input.c
 * PROGRAMMER: KV6
 * DATE: 21.06.2021
 * PURPOSE: Integration multimedia data.
 */

#include "anim.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm")

INT KV6_MouseWheel;

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

/* AnimMouseInit */
static VOID KV6_AnimMouseInit( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(KV6_Anim.hWnd, &pt);

  /* screen cord */
  KV6_Anim.Mdx = pt.x - KV6_Anim.Mx;
  KV6_Anim.Mdy = pt.y - KV6_Anim.My;

  /* absolute value */
  KV6_Anim.Mx = pt.x;
  KV6_Anim.My = pt.y;
 
  KV6_MouseWheel = 0;

}/* End of 'AnimMouseInit' function */

/* AnimMouseResponse */
static VOID KV6_AnimMouseResponse( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(KV6_Anim.hWnd, &pt);

  /* screen cord */
  KV6_Anim.Mdx = pt.x - KV6_Anim.Mx;
  KV6_Anim.Mdy = pt.y - KV6_Anim.My;

  /* absolute value */
  KV6_Anim.Mx = pt.x;
  KV6_Anim.My = pt.y;

}/* End of 'AnimMouseResponse' function */


/* KV6_AnimInputInit */
VOID KV6_AnimInputInit( VOID )
{
  KV6_AnimMouseInit();
  KV6_AnimKeyboardInit();
}/* KV6_AnimInputInit */


/* KV6_AnimInputResponse */
VOID KV6_AnimInputResponse( VOID )
{
  KV6_AnimKeyboardResponse();
  KV6_AnimMouseResponse();
}/* KV6_AnimInputResponse */


/* END OF 'input.c' FILE */
