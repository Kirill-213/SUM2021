/* FILE NAME: rnd.h
 * PROGRAMMER: KV6
 * DATE: 25.06.2021
 * PURPOSE: 3D animation rendering declaration module.
 */

#ifndef __rnd_h_
#define __rnd_h_

#define GLEW_STATIC
#include <glew.h>


#include "res/rndres.h"


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

/* Primitive type */
typedef enum tagkv6PRIM_TYPE
{
  KV6_RND_PRIM_TRIMESH,  /* Triangle mesh - array of triangles */
  KV6_RND_PRIM_TRISTRIP, /* Triangle strip - array of stripped triangles */
  KV6_RND_PRIM_LINES,    /* Line segments (by 2 points) */
  KV6_RND_PRIM_POINTS,   /* Array of points */
} kv6PRIM_TYPE;

/* Primitive representation type */
typedef struct tagkv6PRIM
{
  kv6VERTEX *V;
  kv6PRIM_TYPE Type; /* Primitive type */
  INT
    VA,              /* Vertex array Id */
    VBuf,            /* Vertex buffer Id */
    IBuf;            /* Index buffer Id (if 0 - use only vertex buffer) */
  INT NumOfElements; /* Number of indices/vecrtices */

  INT MtlNo; /* Material number in material array */

  MATR Trans;   /* Additional transformation matrix */
} kv6PRIM;

/* Primitive collection data type */
typedef struct tagkv6PRIMS
{
  INT NumOfPrims; /* Number of primitives in array */
  kv6PRIM *Prims; /* Array of primitives */
  MATR Trans;     /* Common transformation matrix */
} kv6PRIMS;


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

extern VEC 
  KV6_RndCamLoc,
  KV6_RndCamRight,
  KV6_RndCamAt,
  KV6_RndCamDir,
  KV6_RndCamUp;


/* Render base functions */
VOID KV6_RndInit( HWND hWnd );
VOID KV6_RndClose( VOID );
VOID KV6_RndCopyFrame( VOID );
VOID KV6_RndProjSet( VOID );
VOID KV6_RndCamSet( VEC Loc, VEC At, VEC Up );


/* RndPrimFree */
VOID KV6_RndPrimFree( kv6PRIM *Pr );
/* RndPrimDraw */
VOID KV6_RndPrimDraw( kv6PRIM *Pr, MATR World );
/* RndPrimCreate */
VOID KV6_RndPrimCreate( kv6PRIM *Pr, kv6PRIM_TYPE Type, kv6VERTEX *V, INT NumOfV, INT *I, INT NumOfI );

/* RndPrimLoad */
BOOL KV6_RndPrimLoad( kv6PRIM *Pr, CHAR *FileName );


/* RndStart */
VOID KV6_RndStart( VOID );
/* RndEnd */
VOID KV6_RndEnd( VOID );
/* RndResize */
VOID KV6_RndResize( INT W, INT H );
/* RndPrimCreateGrid */
VOID KV6_RndPrimCreateGrid( kv6PRIM *Pr, INT Grid_W, INT Grid_H, kv6VERTEX *V );
/* RndPrimCreatePlane */
VOID KV6_RndPrimCreatePlane( kv6VERTEX *Pr, VEC P, VEC Du, VEC Dv, INT SplitW, INT SplitH );


/* RndShadersInit */
VOID KV6_RndShadersInit( VOID );
/* RndShadersClose */
VOID KV6_RndShadersClose( VOID );
/* RndShadersUpdate */
VOID KV6_RndShadersUpdate( VOID );
/* RndShdFree */
VOID KV6_RndShdFree( INT ProgId );
/* RndShdLoad */
INT KV6_RndShdLoad( CHAR *FileNamePrefix );
/* RndShaderAdd */
INT KV6_RndShaderAdd( CHAR *FileNamePrefix );
/* RndLoadTextFromFile */
CHAR * KV6_RndLoadTextFromFile( CHAR *FileName );
/* RndShdLog */
VOID KV6_RndShdLog( CHAR *FileNamePrefix, CHAR *ShaderName, CHAR *Text );

/* RndPrimsCreate */
BOOL KV6_RndPrimsCreate( kv6PRIMS *Prs, INT NumOfPrims );
/* RndPrimsFree */
VOID KV6_RndPrimsFree( kv6PRIMS *Prs );
/* RndPrimsDraw */
VOID KV6_RndPrimsDraw( kv6PRIMS *Prs, MATR World );
/* RndPrimsLoady */
BOOL KV6_RndPrimsLoad( kv6PRIMS *Prs, CHAR *FileName );


#endif /* __rnd_h_ */

/* END OF 'rnd.h' FILE */