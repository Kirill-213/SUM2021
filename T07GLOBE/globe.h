/* FILE NAME: globe.h
 * PROGRAMMER: KV6
 * DATE: 15.06.2021
 * PURPOSE: Globe.h
*/

#ifndef __globe_h_
#define __globe_h_

#include <windows.h>
#include "timer.h"
#include "mth.h"

#define GRID_H 40
#define GRID_W 40
#define pi 3.14159265359
  
#pragma warning(disable: 4244)

VOID GlobeSet( INT W, INT H, DBL R );
VOID GlobeDraw( HDC hDC );
VEC RotateZ( VEC V, DBL Angle );
VEC RotateY( VEC V, DBL Angle );

#endif
