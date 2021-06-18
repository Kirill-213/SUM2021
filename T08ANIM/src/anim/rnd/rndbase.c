/* FILE NAME: rndbase.c
 * PROGRAMMER: KV6
 * DATE: 17.06.2021
 * PURPOSE: 3D animation rendering function module.
 */

#include "rnd.h"

/* KV6_RndInit */
VOID KV6_RndInit( HWND hWnd )
{

  HDC hDC;

  KV6_hRndWnd = hWnd;
  KV6_hRndBmFrame = NULL;

  hDC = GetDC(hWnd);
  KV6_hRndDCFrame = CreateCompatibleDC(hDC);
  ReleaseDC(hWnd, hDC);

  /* Render perametrs */
  KV6_RndProjSize = 0.1;
  KV6_RndProjDist = KV6_RndProjSize;
  KV6_RndProjFarClip = 300;
  KV6_RndFrameW = 50;
  KV6_RndFrameH = 50;
  KV6_RndCamSet(VecSet(0, 0, 30), VecSet(0, 0, 0), VecSet(0, 1, 0));
}/* End of 'KV6_RndInit' function */

/* KV6_RndClose */
VOID KV6_RndClose( VOID )
{
  DeleteDC(KV6_hRndDCFrame);
  DeleteObject(KV6_hRndBmFrame);
}/* End of 'KV6_RndClose' function */

/* KV6_RndCopyFrame */
VOID KV6_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, KV6_RndFrameW, KV6_RndFrameH,
  KV6_hRndDCFrame, 0, 0, SRCCOPY);
}/* End of 'KV6_RndCopyFrame' function */

/* KV6_RndProjSet */
VOID KV6_RndProjSet( VOID )
{
  DBL rx, ry;

  rx = ry = KV6_RndProjSize;

  /* Correct aspect ratio */
  if (KV6_RndFrameW > KV6_RndFrameH)
    rx *= (DBL)KV6_RndFrameW / KV6_RndFrameH;
  else
    ry *= (DBL)KV6_RndFrameH / KV6_RndFrameW;

  KV6_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      KV6_RndProjDist, KV6_RndProjFarClip);
  KV6_RndMatrVP = MatrMulMatr(KV6_RndMatrView, KV6_RndMatrProj);
}/* KV6_RndProjSet */

/* KV6_RndCamset */
VOID KV6_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  KV6_RndMatrView = MatrView(Loc, At, Up);
  KV6_RndMatrVP = MatrMulMatr(KV6_RndMatrView, KV6_RndMatrProj);
}/* End of 'KV6_RndCamSet' function */

/* KV6_RndStart */
VOID KV6_RndStart( VOID )
{
  SelectObject(KV6_hRndDCFrame, GetStockObject(GRAY_BRUSH));
  SelectObject(KV6_hRndDCFrame, GetStockObject(NULL_PEN));
  Rectangle(KV6_hRndDCFrame, 0, 0, KV6_RndFrameW + 1, KV6_RndFrameH + 1);

  SelectObject(KV6_hRndDCFrame, GetStockObject(BLACK_PEN));
  SelectObject(KV6_hRndDCFrame, GetStockObject(WHITE_BRUSH));
  SetDCPenColor(KV6_hRndDCFrame, RGB(255, 255, 255));
}/* End of 'KV6_RndStart' function */

/* KV6_RndEnd */
VOID KV6_RndEnd( VOID )
{

}/* End of 'KV6_RndEnd' function */

/* KV6_RndResize */
VOID KV6_RndResize( INT W, INT H )
{
  HDC hDC = GetDC(KV6_hRndWnd);

  if (KV6_hRndBmFrame != NULL)
    DeleteObject(KV6_hRndBmFrame);

  KV6_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(KV6_hRndWnd, hDC);
  SelectObject(KV6_hRndDCFrame, KV6_hRndBmFrame);

  KV6_RndFrameW = W;
  KV6_RndFrameH = H;

  KV6_RndProjSet();
}/* End of 'KV6_RndResize' function */


/* END OF 'rndbase.c' FILE */