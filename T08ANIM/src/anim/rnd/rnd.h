/* FILE NAME: rnd.h
 * PROGRAMMER: KV6
 * DATE: 17.06.2021
 * PURPOSE: 3D animation rendering declaration module.
 */

#ifndef __rnd_h_
#define __rnd_h_

#include "../../def.h"

extern HWND KV6_hRndWnd;        /* Work window handle */
extern HDC KV6_hRndDCFrame;     /* Work window memory device context  */
extern HBITMAP KV6_hRndBmFrame; /* Work window background bitmap handle */
extern INT KV6_RndFrameW, KV6_RndFrameH; /* Work window size */

extern DBL
  KV6_RndProjSize,   /* Project plane fit square */
  KV6_RndProjDist,  /* Distance to project plane from viewer (near) */
  KV6_RndProjFarClip;  /* Distance to project far clip plane (far) */

extern MATR
  KV6_RndMatrView, /* View coordinate system matrix */
  KV6_RndMatrProj, /* Projection coordinate system matrix */
  KV6_RndMatrVP;   /* Stored (View * Proj) matrix */

/* vertex representation type */
typedef struct tagkv6VERTEX
{
  VEC P;
} kv6VERTEX;

/* primitive representation type */
typedef struct tagkv6PRIM
{
  kv6VERTEX *V;
  INT NumOfV;

  INT *I;
  INT NumOfI;

  MATR Trans;
} kv6PRIM;

/* Render base functions */
VOID KV6_RndInit( HWND hWnd );
VOID KV6_RndClose( VOID );
VOID KV6_RndCopyFrame( HDC hDC );
VOID KV6_RndProjSet( VOID );
VOID KV6_RndCamSet( VEC Loc, VEC At, VEC Up );

/* Render primitive functions */
VOID KV6_RndPrimFree( kv6PRIM *Pr );
VOID KV6_RndPrimDraw( kv6PRIM *Pr, MATR World );
BOOL KV6_RndPrimCreate( kv6PRIM *Pr, INT NoofV, INT NoofI );

/* Load Primitive from ile */
BOOL KV6_RndPrimLoad( kv6PRIM *Pr, CHAR *FileName );

/* Render start / end */
VOID KV6_RndStart( VOID );
VOID KV6_RndEnd( VOID );

#endif /* __rnd_h_ */

/* END OF 'rnd.h' FILE */