/* FILE NAME: timer.c
 * PROGRAMMER: KV6
 * DATE: 16.06.2021
 * PURPOSE: TIMER.c
*/

#include <time.h>
#include "globe.h"

static LONG         /* время начала программы */
  StartTime,
  OldTime,          /* время предыдущего кадра */
  PauseTime,        /* время простоя в паузе */
  OldFPSTime,       /* время предыдущего */
  FrameCount;       /* счетчик кадров для FPS */

/* timer init */
VOID GLB_TimerInit( VOID ) 
{
  StartTime = OldTime = OldFPSTime = clock();
  FrameCount = 0;
  GLB_IsPause = FALSE;
}/* End of 'GLB_TimerInit' function */

/* timer response */
VOID GLB_TimerResponse( VOID )
{
  LONG t = clock();

  if (!GLB_IsPause)
  {
    GLB_Time = (DOUBLE)(t - PauseTime - StartTime) / CLOCKS_PER_SEC;
    GLB_DeltaTime = (DOUBLE)(t - OldTime) / CLOCKS_PER_SEC;
  }
  else
  {
    PauseTime += t - OldTime;
    GLB_DeltaTime = 0;
  }
  FrameCount++;
  if (t - OldFPSTime > CLOCKS_PER_SEC)
  {
    GLB_FPS = FrameCount / ((DOUBLE)(t - OldFPSTime) / CLOCKS_PER_SEC);
    OldFPSTime = t;
    FrameCount = 0;
  }
  OldTime = t;
}/* End of 'GLB_TimerResponse' function */


