/* FILE NAME: anim.h
 * PROGRAMMER: KV6
 * DATE: 19.06.2021
 * PURPOSE: 3D animation primitive handle module.
 */

#ifndef __anim_h_
#define __anim_h_

#include "rnd/rnd.h"

#define KV6_MAX_UNITS 3000

#define UNIT_BASE_FIELDS \
  VOID (*Init)( kv6UNIT *Uni, kv6ANIM *Ani );      \
  VOID (*Close)( kv6UNIT *Uni, kv6ANIM *Ani );     \
  VOID (*Response)( kv6UNIT *Uni, kv6ANIM *Ani );  \
  VOID (*Render)( kv6UNIT *Uni, kv6ANIM *Ani )

/* typedef */
typedef struct tagkv6UNIT kv6UNIT;
typedef struct tagkv6ANIM
{
  HWND hWnd;
  HDC hDC;
  INT W, H;

  kv6UNIT *Units[KV6_MAX_UNITS];
  INT NumOfUnits;

} kv6ANIM;

/* struct tagUNIT */
struct tagkv6UNIT
{
  UNIT_BASE_FIELDS;
};


/* AnimClose */
VOID KV6_AnimClose( VOID );

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

#endif /* __anim_h_ */

/* END OF 'anim.h' FILE */