/* FILE NAME: anim.h
 * PROGRAMMER: KV6
 * DATE: 21.06.2021
 * PURPOSE: 3D animation primitive handle module.
 */

#ifndef __anim_h_
#define __anim_h_

#include "rnd/rnd.h"


#define KV6_MAX_UNITS 3000

/* typedef */
typedef struct tagkv6UNIT kv6UNIT;
typedef struct tagkv6ANIM kv6ANIM;

#define UNIT_BASE_FIELDS \
  VOID (*Init)( kv6UNIT *Uni, kv6ANIM *Ani );      \
  VOID (*Close)( kv6UNIT *Uni, kv6ANIM *Ani );     \
  VOID (*Response)( kv6UNIT *Uni, kv6ANIM *Ani );  \
  VOID (*Render)( kv6UNIT *Uni, kv6ANIM *Ani )

/* global mouse data */
INT KV6_MouseWheel;

/* Animation context representation type */
struct tagkv6ANIM
{
  HWND hWnd;
  INT W, H;

  kv6UNIT *Units[KV6_MAX_UNITS];
  INT NumOfUnits;

  /* Timer data */
  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL
    IsPause;                     /* Pause flag */

  /* Mouse data */
  INT
    Mx, My, Mz, Mdx, Mdy, Mdz;

  /* Keyboard data */
  BYTE 
    Keys[256],
    KeysOld[256],
    KeysClick[256];

};

/* struct tagUNIT */
struct tagkv6UNIT
{
  UNIT_BASE_FIELDS;
};

extern kv6ANIM KV6_Anim;

/* AnimClose */
VOID KV6_AnimClose( VOID );
/* KV6_AnimExit */
VOID KV6_AnimExit( VOID );
/* AnimInit */
VOID KV6_AnimInit( HWND hWnd );
/* AnimRender */
VOID KV6_AnimRender( VOID );
/* AnimunitAdd */
VOID KV6_AnimAddUnit( kv6UNIT *Uni );
/* AnimCopyFrame */
VOID KV6_AnimCopyFrame( HDC hDC );
/* AnimResize */
VOID KV6_AnimResize( INT W, INT H );
/* FlipFullScreen */
VOID KV6_AnimFlipFullScreen( VOID );
/* AnimUnitCreate */
kv6UNIT * KV6_AnimUnitCreate( INT Size );
/* KV6_AnimFlipFullScreen */
VOID KV6_AnimFlipFullScreen( VOID );


/* KV6_AnimInputResponse */
VOID KV6_AnimInputResponse( VOID );
/* KV6_AnimInputInit */
VOID KV6_AnimInputInit( VOID );


/* TimerInit */
VOID KV6_TimerInit( VOID );
/* TimerResponse */
VOID KV6_TimerResponse( VOID );



#endif /* __anim_h_ */

/* END OF 'anim.h' FILE */