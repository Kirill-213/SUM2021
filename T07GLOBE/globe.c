/* FILE NAME: globe.c
 * PROGRAMMER: KV6
 * DATE: 15.06.2021
 * PURPOSE: Globe.c
*/

#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "globe.h"

/* Globe geometry data */
VEC Geom[GRID_H][GRID_W];

static INT WinW, WinH;

/* Power */
static DBL Power( DBL X, DBL Y )
{
  if (X > 0)
    return -pow(-X, Y);
  return pow(X, Y);
}/* End of 'Power' function */

/* Globe Set */
VOID GlobeSet( INT W, INT H, DBL R )
{
  INT i, j;
  DBL phi, theta;

  /* Store window save */
  WinW = W;
  WinH = H;
  
  /* Fill geometry array with sphere */
  for (i = 0, theta = 0; i < GRID_H; i++, theta += pi / (GRID_H - 1))
    for (j = 0, phi = 0; j < GRID_W; j++, phi += 2 * pi / (GRID_W - 1))
    {
      static DBL a = 0.5, b = 0.8;

      Geom[i][j].X = R * Power(sin(theta), a) * Power(sin(phi), b);
      Geom[i][j].Y = R * Power(cos(theta), a);
      Geom[i][j].Z = R * Power(sin(theta), a) * Power(cos(phi), b);
    }
} /* End of 'GlobeSet' function */

/* GlobeDraw */
VOID GlobeDraw( HDC hDC )
{
  INT k, i, j, r = WinW < WinH ? WinW : WinH, s = 1, c = 1;
  DBL t = GLB_Time;
  MATR WorldMatr;
  static POINT pnts[GRID_H][GRID_W];
 
  WorldMatr = MatrMulMatr4(MatrScale(VecSet(1, 1, 1)),
                           MatrRotateZ(45 * GLB_TIME), 
                           MatrRotate(90 * GLB_TIME, VecSet(1)),
                           MatrTranslate(VecSet(c, s, 0)));

  WorldMatr = MatrMulMatr(WorldMatr,
                          MatrView(VecSet(3, 0, 0),                              
                                   VecSet(0, 0 ,0),
                                   VecSet(0, 1, 0));
  ProjDist = size;
  Wp = Hp = size;
  if (WINw > WINh)
    Wp *= (DBL)Ws / Hs;
  else
    Hp *= (DBL)Hs / Ws;

  /* project all points */
  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
    {
      VEC p = Geom[i][j];

      /* point transformation */
      p = RotateZ(p, t * 30);
      p = RotateY(p, t * 18);
      p.Y += fabs(0.6 * sin(2 * t));

      /* point projection */
      pnts[i][j].x = WinW / 2 + p.X * r * 0.6;
      pnts[i][j].y = WinH / 2 - p.Y * r * 0.6;
    }

  /* by facets */
  srand(50);
  for (k = 1; k < 2; k++)
  {
    if (k == 0)
    {
      SelectObject(hDC, GetStockObject(DC_PEN));
      SelectObject(hDC, GetStockObject(DC_BRUSH));
      SetDCPenColor(hDC, RGB(180, 180, 180));
      SetDCBrushColor(hDC, RGB(200, 200, 200));
    }
    else
    {
      SelectObject(hDC, GetStockObject(DC_PEN));
      SelectObject(hDC, GetStockObject(NULL_BRUSH));
      SetDCPenColor(hDC, RGB(0, 0, 0));
      SelectObject(hDC, GetStockObject(DC_BRUSH));
    }

    for (i = 0; i < GRID_H - 1; i++)
      for (j = 0; j < GRID_W - 1; j++)
      {
        POINT pts[4];
        INT coef;
         
        pts[0] = pnts[i][j];
        pts[1] = pnts[i][j + 1];
        pts[2] = pnts[i + 1][j + 1];
        pts[3] = pnts[i + 1][j];

        SetDCBrushColor(hDC, RGB(rand(), rand(), rand()));

        coef = (pts[0].x - pts[1].x) * (pts[0].y + pts[1].y) + 
            (pts[1].x - pts[2].x) * (pts[1].y + pts[2].y) + 
            (pts[2].x - pts[3].x) * (pts[2].y + pts[3].y) + 
            (pts[3].x - pts[0].x) * (pts[3].y + pts[0].y);
        
        if (coef <= 0 && k == 0 || coef >= 0 && k == 1)
          continue;

        Polygon(hDC, pts, 4);
      }
   }
} /* End of 'GlobeDraw' function */

/* rotate Z */
VEC RotateZ( VEC V, DBL Angle )
{
  DBL a = Angle * pi / 180, si = sin(a), co = cos(a);
  VEC r;

  r.X = V.X * co - V.Y * si;
  r.Y = V.X * si + V.Y * co;
  r.Z = V.Z;  
  return r;
}/* End of 'rotate Z' */

/* rotate Y */
VEC RotateY( VEC V, DBL Angle )
{
  DBL a = Angle * pi / 180, si = sin(a), co = cos(a);
  VEC r;

  r.Z = V.Z * co - V.X * si;
  r.X = V.Z * si + V.X * co;
  r.Y = V.Y;  
  return r;
}/* End of 'rotate Y' */

#if 0
  /* draw all points */
  for (i = 0; i < GRID_H; i++)
    for (j = 0; j < GRID_W; j++)
      Ellipse(hDC, pnts[i][j].x - s, pnts[i][j].y - s, pnts[i][j].x + s, pnts[i][j].y + s);
 
  /* draw by horizontal lines */
  for (i = 0; i < GRID_H; i++)
  {
    MoveToEx(hDC, pnts[i][0].x, pnts[i][0].y, NULL);
      for (j = 1; j < GRID_W; j++)
        LineTo(hDC, pnts[i][j].x, pnts[i][j].y);
  }
 
  /* draw by vertical lines */
  for (j = 1; j < GRID_W; j++)
  {
    MoveToEx(hDC, pnts[0][j].x, pnts[0][j].y, NULL);
    for (i = 0; i < GRID_H; i++)
        LineTo(hDC, pnts[i][j].x, pnts[i][j].y);
  }
#endif 

