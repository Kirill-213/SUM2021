#include <windows.h>

#define WND_CLASS_NAME "My own window class"

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, 
                               WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLin, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  /* заполняем структуру класса окна */
  wc.style = 0;                             /* стили окна */
  wc.cbClsExtra = 0;                        /* дополнительно оличесвто байт для класса */
  wc.cbWndExtra = 0;                        /* дополнительно оличесвто байт для окна */
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;  /* Фоновый цвет - выбранный в системе */
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

LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, 
                               WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hDC;
  HPEN hPen, hOldPen;
  INT x, y;
  POINT pt;

  static INT w, h;

  switch (Msg)
  {
  case WM_SIZE:

    w = LOWORD(lParam);
    h = HIWORD(lParam);
    return 0;

  case WM_CREATE:
    SetTimer(hWnd, 47, 5, NULL);
    return 0;
 /*   
  case WM_TIMER:
    hDC = GetDC(hWnd);
    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);

    hPen = CreatePen(PS_SOLID, 5, RGB(0,255,255));
    hOldPen = SelectObject(hDC, hPen);

    Ellipse(hDC, pt.x - 20, pt.y - 20, pt.x, pt.y);
    MoveToEx(hDC, w/2, h/2, NULL);
    LineTo(hDC, pt.x - 10, pt.y - 10);
    
    SelectObject(hDC, hOldPen);
    DeleteObject(hPen);
    ReleaseDC(hWnd, hDC);
    return 0;
  */
  case WM_LBUTTONDOWN:

    x = LOWORD(lParam);
    y = HIWORD(lParam);

    hDC = GetDC(hWnd);

    MoveToEx(hDC, w / 2, h / 2, NULL);
    LineTo(hDC, x, y);
    ReleaseDC(hWnd, hDC);
    return 0;
 
  case WM_PAINT:

    hDC = BeginPaint(hWnd, &ps);

    hPen = CreatePen(PS_SOLID, 2, RGB(255,0 ,0));
    hOldPen = SelectObject(hDC, hPen);
    
    Ellipse(hDC,100,100, 300, 300);
    EndPaint(hWnd, &ps);

    return 0;

  case WM_DESTROY:

    PostQuitMessage(30);
 
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
}
