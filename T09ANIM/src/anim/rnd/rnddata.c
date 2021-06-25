/* FILE NAME: rnddata.c
 * PROGRAMMER: KV6
 * DATE: 25.06.2021
 * PURPOSE: 3D animation rendering data module.
 */

#include "rnd.h"

/* Global rendering data */
HWND KV6_hRndWnd;                 /* Work window handle */
HGLRC KV6_hRndGLRC;               /* Open GL render devic context */
HDC KV6_hRndDC;                   /* Work window memory device context  */
INT KV6_RndFrameW, KV6_RndFrameH; /* Work window size */

DBL
  KV6_RndProjSize = 0.1,  /* Project plane fit square */
  KV6_RndProjDist = 0.1,  /* Distance to project plane from viewer (near) */
  KV6_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */

MATR
  KV6_RndMatrView, /* View coordinate system matrix */
  KV6_RndMatrProj, /* Projection coordinate system matrix */
  KV6_RndMatrVP;   /* Stored (View * Proj) matrix */

