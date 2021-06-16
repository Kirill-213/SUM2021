/* FILE NAME: timer.h
 * PROGRAMMER: KV6
 * DATE: 16.06.2021
 * PURPOSE: TIMER.h
*/

#ifndef __timer_h_
#define __timer_h_

#include <windows.h>

DOUBLE 
  GLB_Time,        /* общее время в секундах*/
  GLB_DeltaTime,   /* межкадровое время в секундах */
  GLB_FPS;         /* количество кадров в секунду */

BOOL GLB_IsPause;  /* флаг паузы	дополнительно запоминаем (в "тиках"-"клоках"): */

VOID GLB_TimerInit( VOID );
VOID GLB_TimerResponse( VOID );

#endif

