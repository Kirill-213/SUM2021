/* FILE NAME: main.c
 * PROGRAMMER: KV6
 * DATE: 17.06.2021
 * PURPOSE: 3D animation startup module.
 */

#include "../anim/rnd/rnd.h"

/* Window class name */
#define KV6_WND_CLASS_NAME "My Window Class Name"

/* Forward declaration */
LRESULT CALLBACK KV6_WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT CmdShow )
{
  HWND hWnd;
  MSG msg;
  WNDCLASS wc;

  SetDbgMemHooks();

  /* Fill window class structure */
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.hInstance = hInstance;
  wc.lpszClassName = KV6_WND_CLASS_NAME;
  wc.lpszMenuName = NULL;
  wc.lpfnWndProc = KV6_WinFunc;

  /* Register window class */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "Error", MB_OK | MB_ICONERROR);
    return 0;
  }

  hWnd =
  CreateWindow(KV6_WND_CLASS_NAME,
  "KV6_HUSTLE_MODE",
  WS_OVERLAPPEDWINDOW,
  CW_USEDEFAULT, CW_USEDEFAULT,
  CW_USEDEFAULT, CW_USEDEFAULT,
  NULL,
  NULL,
  hInstance,
  NULL);

  ShowWindow(hWnd, CmdShow);

  /* Message loop */
  while (GetMessage(&msg, NULL, 0, 0))
    DispatchMessage(&msg);

  return 30;
} /* End of 'WinMain' function */

/* Window handle function.
 * ARGUMENTS:
 *   - window handle:
 *      HWND hWnd;
 *   - message type (see WM_***):
 *      UINT Msg;
 *   - message 'word' parameter:
 *      WPARAM wParam;
 *   - message 'long' parameter:
 *      LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message depende return value.
 */
LRESULT CALLBACK KV6_WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  DBL t = clock() / 1000.0;
  static kv6PRIM PrF;

  switch (Msg)
  {
  /* create */
  case WM_CREATE:
    SetTimer(hWnd, 47, 1, NULL);
    KV6_RndInit(hWnd);
    KV6_RndPrimLoad(&PrF, "Harley.obj");
    return 0;

  /* size */
  case WM_SIZE:
    KV6_RndResize(LOWORD(lParam),
                  HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 47, 0);
    return 0;

  /* timer */
  case WM_TIMER:
    KV6_RndStart();

    KV6_RndCamSet(VecSet(100 * sint(t), 120, 100 * cos(t)), VecSet(0, 55, 0), VecSet(0, 1, 0));
    KV6_RndPrimDraw(&PrF, MatrMulMatrMatrRotateY(-90), MatrScale(VecSet1(0.5)));
    
    KV6_RndEnd();
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;

  /* paint */
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    KV6_RndCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;

  /* destroy */
  case WM_DESTROY:
    KV6_RndPrimFree(&PrF);
    KV6_RndClose();
    KillTimer(hWnd, 30);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    return 0;

  /* erase */
  case WM_ERASEBKGND:
    return 1;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'KV6_WinFunc' function */

/* END OF 'pattern.c' FILE */