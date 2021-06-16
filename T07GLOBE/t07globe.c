/* FILE NAME: t07globe.c
 * PROGRAMMER: KV6
 * DATE: 15.06.2021
 * PURPOSE: Main
*/

#include <stdio.h>
#include <windows.h>
#include "globe.h"

#define WND_CLASS_NAME "MNN"

typedef DOUBLE DBL;

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd)
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  /**/
  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.lpszMenuName = NULL;
  wc.lpfnWndProc = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;
  

  /**/
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
  return 0;
  }
  
  /**/
  hWnd =
  CreateWindow(WND_CLASS_NAME,
  "SPHERE",
  WS_OVERLAPPEDWINDOW,
  CW_USEDEFAULT, CW_USEDEFAULT,
  CW_USEDEFAULT, CW_USEDEFAULT,
  NULL,
  NULL,
  hInstance,
  NULL);

  /**/
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);
  /* message loop */
  while ( TRUE )
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    else
      SendMessage(hWnd, WM_TIMER, 47, 0);
 
  return 30;
}

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  static HDC hDCFrame;
  static INT w, h;
  static HBITMAP hBm;
  static CHAR Buf[100];

  switch (Msg)
  {
    /* create */
    case WM_CREATE:
      SetTimer(hWnd, 47, 1, NULL);
      hDC = GetDC(hWnd);
      hDCFrame = CreateCompatibleDC(hDC);
      ReleaseDC(hWnd, hDC);
      hBm = NULL;

      GLB_TimerInit();
      return 0;

    /* size */
    case WM_SIZE:
      h = HIWORD(lParam);
      w = LOWORD(lParam);

      if (hBm != NULL)
        DeleteObject(hBm);
      hDC = GetDC(hWnd);
      hBm = CreateCompatibleBitmap(hDC, w, h);
      ReleaseDC(hWnd, hDC);
      SelectObject(hDCFrame, hBm);
      
      /* globe set */
      GlobeSet(w, h, 0.5);

      SendMessage(hWnd, WM_TIMER, 0, 0);
      return 0;

    /* timer */
    case WM_TIMER:

      GLB_TimerResponse();

      /* clear background */
      SelectObject(hDCFrame, GetStockObject(GRAY_BRUSH));
      SelectObject(hDCFrame, GetStockObject(NULL_PEN));
      Rectangle(hDCFrame, 0, 0, w + 1, h + 1);

      SelectObject(hDCFrame, GetStockObject(BLACK_PEN));
      SelectObject(hDCFrame, GetStockObject(WHITE_BRUSH));
      
      /* globe daraw */
      GlobeDraw(hDCFrame);

      /* output FPS */
      SetBkMode(hDCFrame, TRANSPARENT);
      SetTextColor(hDCFrame, RGB(200, 200, 50));
      TextOut(hDCFrame, 8, 8, Buf, sprintf(Buf, "FPS: %.3f", GLB_FPS));

      /*InvalidateRect(hWnd, NULL, FALSE);*/
      hDC = GetDC(hWnd);
      BitBlt(hDC, 0, 0, w, h, hDCFrame, 0, 0, SRCCOPY);
      ReleaseDC(hWnd, hDC);
      return 0;

    /* paint */
    case WM_PAINT:
      hDC = BeginPaint(hWnd, &ps);
      BitBlt(hDC, 0, 0, w, h, hDCFrame, 0, 0, SRCCOPY);
      EndPaint(hWnd, &ps);
      return 0;

    /* keydown */
    case WM_KEYDOWN:
      if (wParam == VK_ESCAPE)
        SendMessage(hWnd, WM_CLOSE, 0, 0);
      else if (wParam != 'P') /* ctrl */
        GLB_IsPause = ! GLB_IsPause;
      return 0;
     
    /* destroy */
    case WM_DESTROY:
      if (hBm != NULL)
        DeleteObject(hBm);
      PostQuitMessage(45);
      KillTimer(hWnd, 30);
      return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
 