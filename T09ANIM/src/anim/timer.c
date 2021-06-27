/* FILE NAME: timer.c
 * PROGRAMMER: KV6
 * DATE: 25.06.2021
 * PURPOSE: 3D animation project.
 *          Timer handle functions.
 */

#include "anim.h"

/* Local timer data */
static UINT64
  StartTime,    /* Start program time */
  OldTime,      /* Previous frame time */
  OldTimeFPS,   /* Old time FPS measurement */
  PauseTime,    /* Time during pause period */
  TimePerSec,   /* Timer resolution */
  FrameCounter; /* Frames counter */

/* KV6_TimerInit */
VOID KV6_TimerInit( VOID )
{
  LARGE_INTEGER t;
  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  KV6_Anim.IsPause = FALSE;
  KV6_Anim.FPS = 30.0;
  PauseTime = 0;

}/* End of 'KV6_TimerInit' function */

/* KV6_TimerResponse */
VOID KV6_TimerResponse( VOID )
{

  LARGE_INTEGER t;
  ///CHAR Buf[100];

  QueryPerformanceCounter(&t);
  /* Global time */
  KV6_Anim.GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  KV6_Anim.GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;
  /* Time with pause */
  if (KV6_Anim.IsPause)
  {
    KV6_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    KV6_Anim.DeltaTime = KV6_Anim.GlobalDeltaTime;
    KV6_Anim.Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    KV6_Anim.FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;

    FrameCounter = 0;

    /*sprintf(Buf, "FPS: %.2lf", KV6_Anim.FPS);   
    SetWindowText(KV6_Anim.hWnd, Buf);           */
  }
  OldTime = t.QuadPart;

}/* End of 'KV6_TimerResponse' function */


/* END OF 'timer.c' FILE */