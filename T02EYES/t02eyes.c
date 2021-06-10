#include <windows.h>
#include <math.h>

#define WND_CLASS_NAME "My own window class"

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, 
                               WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLin, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  /* заполняем структуру класса окна */
  wc.style = 0;                             
  wc.cbClsExtra = 0;                        
  wc.cbWndExtra = 0;                        
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;  
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_ERROR);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  /* регистрация коасса в системе */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK | MB_ICONERROR);
    return 0;
  }

  /* создать окно */
  hWnd = 
    CreateWindow(WND_CLASS_NAME,
      "Title",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT,
      NULL,
      NULL,
      hInstance,
      NULL);
 
  /* показать и перерисовать окно */
  ShowWindow(hWnd, ShowCmd);
  UpdateWindow(hWnd);

  /* цикл обработки сообщений */
  while(GetMessage(&msg, NULL, 0, 0))
    DispatchMessage(&msg);
    return 0;
}

/* Draw Eyes */
VOID DrawEyes( HDC hDC, INT X, INT Y, INT R, INT R1, INT Mx, INT My )
{
  INT dx, dy;
  HPEN hPen, hOldPen;
  DOUBLE kp, len = sqrt((Mx - X) * (Mx - X) + (My - Y) * (My - Y));
  
  hPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 0));
  hOldPen = SelectObject(hDC, hPen);
  Ellipse(hDC, X - R, Y - R, X + R, Y + R);
  DeleteObject(hPen);

  if (R- R1 < len)
  {
    kp = (R - R1) / len;
    dx = (INT)(kp * (Mx - X) + X);
    dy = (INT)(kp * (My - Y) + Y);
    Ellipse(hDC, dx - R1, dy - R1, dx + R1, dy + R1);
  }
  else
  { 
    Ellipse(hDC, Mx - R1, My - R1, Mx + R1, My + R1);  
  }
}

/* MyindowFunc */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, 
                               WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hDC;
  POINT pt;
  HPEN hPen;
  static HDC hDCFrame;
  static INT w, h;
  static HDC hMemDC;
  static HBITMAP hBm;

  switch (Msg)
  {
  /* SIZE */
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, w, h);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;

  /* CREATE TIMER */
  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    SetTimer(hWnd, 47, 20, NULL);
    return 0;
    
  /* TIMER */
  case WM_TIMER:
    hDC = GetDC(hWnd);
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
    DrawEyes(hDC, w/2, h/2, 200, 80, pt.x, pt.y);
    Rectangle(hDCFrame, 0, 0, w, h);
    SelectObject(hDCFrame, GetStockObject(DC_PEN));
    DeleteObject(hPen);
    InvalidateRect(hWnd, NULL, 0);
    return 0;

  /* PAINT */
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);

    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;    

    /* DESTROY */
  case WM_DESTROY:
    if (hBm != NULL)
      DeleteObject(hBm);
    KillTimer(hWnd, 45);
    PostQuitMessage(30);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
