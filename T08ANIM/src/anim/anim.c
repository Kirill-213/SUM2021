/* FILE NAME: anim.c
 * PROGRAMMER: KV6
 * DATE: 19.06.2021
 * PURPOSE: 3D animation primitive handle module.
 */

#include "anim.h"

/* Global animation data */
kv6ANIM KV6_Anim;

/* KV6_AnimInit */
VOID KV6_AnimInit( HWND hWnd )
{
  KV6_Anim.hWnd = hWnd;
  KV6_RndInit(hWnd);
  KV6_Anim.hDC = KV6_hRndDCFrame;
}/* KV6_AnimInit */

/* KV6_AnimClose */
VOID KV6_AnimClose( VOID )
{
  INT i;
  
  for (i = 0; i < KV6_Anim.NumOfUnits; i++)
  {
    KV6_Anim.Units[i]->Close(KV6_Anim.Units[i], &KV6_Anim);
    free(KV6_Anim.Units[i]);
//    KV6_Anim.Units[i] = NULL;
  }
  KV6_Anim.NumOfUnits = 0;
  KV6_RndClose();
}/* End of '' function */

/* KV6_AnimResize */
VOID KV6_AnimResize( INT W, INT H )
{
  KV6_Anim.W = W;
  KV6_Anim.H = H;
  KV6_RndResize(W, H);
}/* KV6_AnimResize */

/* KV6_AnimCopyFrame */
VOID KV6_AnimCopyFrame( HDC hDC )
{
  KV6_RndCopyFrame(hDC);
}/* End of 'KV6_AnimCopyFrame' function */

/* KV6_AnimRender */
VOID KV6_AnimRender( VOID )
{
  INT i;

  for (i = 0; i < KV6_Anim.NumOfUnits; i++)
    KV6_Anim.Units[i]->Response(KV6_Anim.Units[i], &KV6_Anim);

  KV6_RndStart();
  for (i = 0; i < KV6_Anim.NumOfUnits; i++)
    KV6_Anim.Units[i]->Render(KV6_Anim.Units[i], &KV6_Anim);
  KV6_RndEnd();
}/* End of 'KV6_AnimRender' function */


/* KV6_AnimUnitAdd */
VOID KV6_AnimAddUnit( kv6UNIT *Uni )
{
  if (KV6_Anim.NumOfUnits < KV6_MAX_UNITS)
    KV6_Anim.Units[KV6_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &KV6_Anim);
}/* End of 'KV6_AnimUnitAdd' function */

#if 0
/* KV6_FlipFullScreen */
VOID KV6_AnimFlipFullScreen( VOID )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRC;

  if (!IsFullScreen)
  {
    RECT rc;
    HMONITOR hmon;
    HMONITORINFOEX moninfo;

    /* Saving old window size */
    GetWindowRect(KV6_hRndWnd, &SaveRC);

    hmon = MonitorFromWindow(KV6_hRndWnd, MONITOR_DEFAULTTONEAREST);

    /* Getting monitor info */
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    rc = moninfo.rcMonitor;

    AdjustWindowRect(&rc, GetWindowLong(KV6_hRndWnd, GWL_STYLE), FALSE);

    SetWindowPos(KV6_hRndWnd, HWND_TOP,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top + 201,
      SWP_NOOWNERZORDER);
    IsFullScreen = TRUE;
  }
  else
  {
    SetWindowPos(KV6_hRndWnd, HWND_TOP,
      SaveRC.left, SaveRC.top,
      SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = FALSE;
  }
}/* End of 'KV6_AnimFlipFullScreen' function */
#endif

/* END OF 'anim.c' FILE */