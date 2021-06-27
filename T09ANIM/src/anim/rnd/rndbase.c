/* FILE NAME : rndbase.c
 * PROGRAMMER: kv6
 * DATE      : 21.06.2021 
 * PURPOSE   : WinAPI Animation startup module
 */
#include "../anim.h"


/* Render initialization function.
 * ARGUMENTS:
 *   - Working window:
 *       HWND hWnd;
 * RETURNS:
 *   (VOID) None.
*/
VOID KV6_RndInit( HWND hWnd )
{
  INT i, nums;
  PIXELFORMATDESCRIPTOR pfd = {0};
  HGLRC hRC;
  INT PixelAttribs[] =
  {
    WGL_DRAW_TO_WINDOW_ARB, TRUE,
    WGL_SUPPORT_OPENGL_ARB, TRUE,
    WGL_DOUBLE_BUFFER_ARB, TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 32,
    0
  };
  INT ContextAttribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
                                  /* WGL_CONTEXT_CORE_PROFILE_BIT_ARB, */
    0
  };

  KV6_hRndWnd = hWnd;
  KV6_hRndDC = GetDC(hWnd);

  /* OpenGL init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(KV6_hRndDC, &pfd);
  DescribePixelFormat(KV6_hRndDC, i, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
  SetPixelFormat(KV6_hRndDC, i, &pfd);

  /* OpenGL init: setup rendering context */
  KV6_hRndGLRC = wglCreateContext(KV6_hRndDC);
  wglMakeCurrent(KV6_hRndDC, KV6_hRndGLRC);

  /* Initializing GLEW library */
  if (glewInit() != GLEW_OK)
  {
    MessageBox(KV6_hRndWnd, "Error extensions initializing", "Error",
      MB_ICONERROR | MB_OK);
    exit(0);
  }

  if (!(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
  {
    MessageBox(KV6_hRndWnd, "Error: no shaders support", "Error", MB_ICONERROR | MB_OK);
    exit(0);
  }

  /* Enable a new OpenGL profile support */
  wglChoosePixelFormatARB(KV6_hRndDC, PixelAttribs, NULL, 1, &i, &nums);
  hRC = wglCreateContextAttribsARB(KV6_hRndDC, NULL, ContextAttribs);

  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(KV6_hRndGLRC);

  KV6_hRndGLRC = hRC;
  wglMakeCurrent(KV6_hRndDC, KV6_hRndGLRC);

  /* Set default OpenGL parameters */
  glEnable(GL_DEPTH_TEST);
  wglSwapIntervalEXT(0);

  KV6_RndShadersInit();
  KV6_RndTexturesInit();
  KV6_RndMtlInit();


  KV6_RndProjSize = 0.1;
  KV6_RndProjDist = KV6_RndProjSize;
  KV6_RndProjFarClip = 300;
  KV6_RndFrameH = 300;
  KV6_RndFrameW = 300;

  KV6_RndCamSet(VecSet(0, 3, 5), VecSet1(0), VecSet(0, 1, 0));
} /* End of 'KV6_RndInit' function */

/* Render closing function.
 * ARGUMENTS:
 *   (VOID) None.
 * RETURNS:
 *   (VOID) None.
*/
VOID KV6_RndClose( VOID )
{
  KV6_RndShadersClose();
  KV6_RndTexturesClose();
  KV6_RndMtlClose();
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(KV6_hRndGLRC);
  ReleaseDC(KV6_hRndWnd, KV6_hRndDC);
} /* End of 'KV6_RndClose' function */

/* Render projection setting function.
 * ARGUMENTS:
 *   (VOID) None.
 * RETURNS:
 *   (VOID) None.
*/
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
} /* End of 'KV6_RndProjSet' function */

/* Render camera setting function.
 * ARGUMENTS:
 *   - Location pos:
 *       VEC Loc;
 *   - Looking at pos:
 *       VEC At;
 *   - Up vec:
 *       VEC Up;
 * RETURNS:
 *   (VOID) None.
*/
VOID KV6_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  KV6_RndCamLoc = Loc;
  KV6_RndMatrView = MatrView(Loc, At, Up);
  KV6_RndMatrVP = MatrMulMatr(KV6_RndMatrView, KV6_RndMatrProj);
} /* End of 'KV6_RndCamSet' function */

/* Render resizing function.
 * ARGUMENTS:
 *   - Window size:
 *       INT W, H;
 * RETURNS:
 *   (VOID) None.
*/
VOID KV6_RndResize( INT W, INT H )
{
  glViewport(0, 0, W, H);

  /* Saving size */
  KV6_RndFrameW = W;
  KV6_RndFrameH = H;

  /* Projection recounting */
  KV6_RndProjSet();
} /* End of 'KV6_RndResize' function */

/* Render frame copying function.
 * ARGUMENTS:
 *   - Device context:
 *       HDC hDC;
 * RETURNS:
 *   (VOID) None.
*/
VOID KV6_RndCopyFrame( VOID )
{
  SwapBuffers(KV6_hRndDC);
} /* End of 'KV6_RndCopyFrame' function */

/* Render starting function.
 * ARGUMENTS:
 *   (VOID) None.
 * RETURNS:
 *   (VOID) None.
*/
VOID KV6_RndStart( VOID )
{
  static DBL dt;
  
  dt += KV6_Anim.GlobalDeltaTime;
  if (dt > 2)
  {
    dt = 0;
    KV6_RndShadersUpdate();
  }

  glClearColor(0.2, 0.8, 0.2, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
} /* End of 'KV6_RndStart' function */

/* Render closing function.
 * ARGUMENTS:
 *   (VOID) None.
 * RETURNS:
 *   (VOID) None.
*/
VOID KV6_RndEnd( VOID )
{
  glFinish();
} /* End of 'KV6_RndStart' function */


/* END OF 'rndbase.c' FILE */