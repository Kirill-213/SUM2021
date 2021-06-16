/* FILE NAME: timer.h
 * PROGRAMMER: KV6
 * DATE: 16.06.2021
 * PURPOSE: TIMER.h
*/

#ifndef __timer_h_
#define __timer_h_

#include <windows.h>

DOUBLE 
  GLB_Time,        /* ����� ����� � ��������*/
  GLB_DeltaTime,   /* ����������� ����� � �������� */
  GLB_FPS;         /* ���������� ������ � ������� */

BOOL GLB_IsPause;  /* ���� �����	������������� ���������� (� "�����"-"������"): */

VOID GLB_TimerInit( VOID );
VOID GLB_TimerResponse( VOID );

#endif

