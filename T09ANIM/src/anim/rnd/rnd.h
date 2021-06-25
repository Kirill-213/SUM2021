/* FILE NAME: rnd.h
 * PROGRAMMER: KV6
 * DATE: 21.06.2021
 * PURPOSE: 3D animation rendering declaration module.
 */

#ifndef __rnd_h_
#define __rnd_h_

#define GLEW_STATIC
#include <glew.h>

#include "../../def.h"

#include <wglew.h>
#include <gl/wglext.h>

#pragma comment(lib, "opengl32")

#define KV6_MAX_SHADERS 30
#define KV6_STR_MAX 300

/* vertex representation type */
typedef struct tagkv6VERTEX
{
  VEC P;   /* position */
  VEC2 T;  /* texture cord */
  VEC N;   /* normal */
  VEC4 C;  /* color(r, g, b, a) */

} kv6VERTEX;

extern HWND KV6_hRndWnd;        /* Work window handle */
extern HGLRC KV6_hRndGLRC;               /* Open GL render devic context */
extern HDC KV6_hRndDC;     /* Work window memory device context  */
extern INT KV6_RndFrameW, KV6_RndFrameH; /* Work window size */

extern DBL
  KV6_RndProjSize,   /* Project plane fit square */
  KV6_RndProjDist,  /* Distance to project plane from viewer (near) */
  KV6_RndProjFarClip;  /* Distance to project far clip plane (far) */

extern MATR
  KV6_RndMatrView, /* View coordinate system matrix */
  KV6_RndMatrProj, /* Projection coordinate system matrix */
  KV6_RndMatrVP;   /* Stored (View * Proj) matrix */

/* primitive representation type */
typedef struct tagkv6PRIM
{
  kv6VERTEX *V;

  INT VA;
  INT VBuf;
  INT IBuf;

  INT NumOfElements;

  MATR Trans; /* Additional transformation matrix */
} kv6PRIM;


/* shader struct */
typedef struct tagkv6SHADER
{
  INT ProgId;
  CHAR Name[KV6_STR_MAX];
} kv6SHADER;

/* Shadre stock array and it size */
extern kv6SHADER KV6_RndShaders[KV6_MAX_SHADERS];
extern INT KV6_RndShadersSize;



/* Render base functions */
VOID KV6_RndInit( HWND hWnd );
VOID KV6_RndClose( VOID );
VOID KV6_RndCopyFrame( HDC hDC );
VOID KV6_RndProjSet( VOID );
VOID KV6_RndCamSet( VEC Loc, VEC At, VEC Up );

/* Render primitive functions */
VOID KV6_RndPrimFree( kv6PRIM *Pr );
VOID KV6_RndPrimDraw( kv6PRIM *Pr, MATR World );
//BOOL KV6_RndPrimCreate( kv6PRIM *Pr, INT NoofV, INT NoofI );
VOID KV6_RndPrimCreate( kv6PRIM *Pr, kv6VERTEX *V, INT NumOfV, INT *I, INT NumOfI );

/* Load Primitive from ile */
BOOL KV6_RndPrimLoad( kv6PRIM *Pr, CHAR *FileName );

/* Render start / end */
VOID KV6_RndStart( VOID );
VOID KV6_RndEnd( VOID );

/* KV6_RndResize */
VOID KV6_RndResize( INT W, INT H );

/* KV6_RndPrimCreateGrid */
VOID KV6_RndPrimCreateGrid( kv6PRIM *Pr, INT Grid_W, INT Grid_H, kv6VERTEX *V );
/* KV6_RndPrimCreatePlane */
VOID KV6_RndPrimCreatePlane( kv6VERTEX *Pr, VEC P, VEC Du, VEC Dv, INT SplitW, INT SplitH );



/* KV6_RndShadersInit */
VOID KV6_RndShadersInit( VOID );

/* KV6_RndShadersClose */
VOID KV6_RndShadersClose( VOID );

/* KV6_RndShadersUpdate */
VOID KV6_RndShadersUpdate( VOID );

/* KV6_RndShdFree */
VOID KV6_RndShdFree( INT ProgId );

/* KV6_RndShdLoad */
INT KV6_RndShdLoad( CHAR *FileNamePrefix );

/* KV6_RndShaderAdd */
INT KV6_RndShaderAdd( CHAR *FileNamePrefix );

/* KV6_RndLoadTextFromFile */
CHAR * KV6_RndLoadTextFromFile( CHAR *FileName );

/* KV6_RndShdLog */
VOID KV6_RndShdLog( CHAR *FileNamePrefix, CHAR *ShaderName, CHAR *Text );


#endif /* __rnd_h_ */

/* END OF 'rnd.h' FILE */