/* FILE NAME: mth.h
 * PROGRAMMER: KV6
 * DATE: 21.06.2021
 * PURPOSE: Globe.h
*/
#ifndef __mth_h_
#define __mth_h_

#include <math.h>
#include <windows.h>

#define PI 3.14159265358979323846
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)

#define MatrMulMatr3(A, B, C) MatrMulMatr(MatrMulMatr(A, B), C)
#define MatrMulMatr4(A, B, C, D) MatrMulMatr(MatrMulMatr(MatrMulMatr(A, B), C)), D)

/* End of 'MatrMulMatr3' function */


/* typedef */
typedef double DBL;
typedef FLOAT FLT;

/* types for vectors */
typedef struct tagVEC
{
  FLT X, Y, Z;
} VEC;

/* type for matrix */
typedef struct tagMATR
{
  FLT A[4][4];
} MATR;

/* VecSet */
__inline VEC VecSet( FLT X, FLT Y, FLT Z )
{
  VEC v;

  v.X = X;
  v.Y = Y;
  v.Z = Z;
  return v;
}/* End of 'VecSet' function */

 /* VecSet1 */
__inline VEC VecSet1( FLT X )
{
  return VecSet(X, X, X);
}/* End of 'VecSet1' function */

/* VecAddVec */
__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
}/* End of 'VecAddVec' function */

/* VecSubVec */
__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
}/* End of 'VecSubVec' function */

/* VecDotVec */
__inline FLT VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
}/* End of 'VecDotVec' function */

/* VecMulNum */
__inline VEC VecDivNum( VEC V1, FLT N )
{
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
}/* End of 'VecMulNum' function */

/* VecNeg */
__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
}/* End of 'VecNeg' function */

/* VecLen */
__inline FLT VecLen( VEC V )
{
  FLT len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
}/* End of 'VecLen' function */

/* VecLen2 */
__inline FLT VecLen2( VEC V )
{
  return VecDotVec(V, V);
}/* End of 'VecLen2' function */

/* vecNormalize */
__inline VEC VecNormalize( VEC V )
{
  FLT len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return V;
  return VecDivNum(V, sqrt(len));
}/* End of 'VecNormalize' function */

/* VecMulNum */
__inline VEC VecMulNum( VEC V1, FLT N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
}/* End of 'VecMulNum' function */

/* VecCrossVec */
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
}/* VecCrossVec */

/* VecAddVecEq */
__inline VEC VecAddVecEq( VEC *VRes, VEC V2 )
{
  VRes->X += V2.X;
  VRes->Y += V2.Y;
  VRes->Z += V2.Z;
  return *VRes;
}/* End of 'VecAddVecEq' function */

/* UnitMatrix */
static MATR UnitMatrix =
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }
};/* End of 'UnitMatrix' funtion */

/* MatrIndenity */
__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
}/* End of 'MatrIndenity' function */

/* MatrTranslate */
__inline MATR MatrTranslate( VEC T )
{
  MATR m = UnitMatrix;

  m.A[3][0] = T.X;
  m.A[3][1] = T.Y;
  m.A[3][2] = T.Z;
  return m;
}/* End of 'MatrTranslate' function */

/* MatrRotate */
__inline MATR MatrRotate( FLT AngleInDegree, VEC R )
{
  FLT A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  VEC V = VecNormalize(R);
  MATR M =
  {
    {
      {co + V.X * V.X * (1 - co), V.X * V.Y * (1 - co) + V.Z * si,
       V.X * V.Z * (1 - co) + V.Z * si, 0},
      {V.Y * V.X * (1 - co) - V.Z * si, co + V.Y * V.Y * (1 - co),
       V.Y * V.Z * (1 - co) + V.X * si, 0},
      {V.Z * V.X * (1 - co) + V.Y * si, V.Z * V.Y * (1 - co) - V.X * si,
       co + V.Z * V.Z * (1 - co),       0},
      {0, 0, 0, 1}
    }
  };
  return M;
}/* End of 'MatrRotate' funtcion */

/* MatrRotateZ */
__inline MATR MatrRotateZ( FLT AngleInDegree )
{
  FLT A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  MATR M =
  {
    {
      {co, si, 0, 0},
      {-si, co, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    }
  };
  return M;
}/* End of 'MatrRotateZ' funtcion */

/* MatrRotateY */
__inline MATR MatrRotateY( FLT AngleInDegree )
{
  FLT A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  MATR M =
  {
    {
      {co, 0, -si, 0},
      {0, 1, 0, 0},
      {si, 0, co, 0},
      {0, 0, 0, 1}
    }
  };
  return M;
}/* End of 'MatrRotateY' funtcion */

/* MatrRotateX */
__inline MATR MatrRotateX( FLT AngleInDegree )
{
  FLT A = D2R(AngleInDegree), si = sin(A), co = cos(A);
  MATR M =
  {
    {
      {1, 0, 0, 0},
      {0, co, si, 0},
      {0, -si, co, 0},
      {0, 0, 0, 1}
    }
  };
  return M;
}/* End of 'MatrRotateX' funtcion */

/* PointTransform */
__inline VEC PointTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0],
                V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1],
                V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]);
}/* End of 'PointTransform' function */

/* VectorTransform*/
__inline VEC VectorTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0],
                V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1],
                V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2]);
}/* End of 'VectorTransform' function */

/* VecMulMatr */
__inline VEC VecMulMatr( VEC V, MATR M )
{
  FLT w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];
  return VecSet((V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]) / w,
                (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]) / w,
                (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]) / w);
}/* End of 'VecMulMatr' function */

/* MatrMulMatr */
__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  MATR r;
  INT i, j, k;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (r.A[i][j] = 0, k = 0; k < 4; k++)
        r.A[i][j] += M1.A[i][k] * M2.A[k][j];
  return r;
}/* End of 'MatrMulMatr' function */

/* MatrView */
__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecNormalize(VecCrossVec(Right, Dir));
  
  MATR m =
  {
    {
      {Right.X, Up.X, -Dir.X, 0}, {Right.Y, Up.Y, -Dir.Y, 0}, {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };
  return m;
} /* End of 'MatrView' function */

/* MatrScale */
__inline MATR MatrScale( VEC S )
{
  MATR M =
  {
    {
      {S.X, 0, 0, 0},
      {0, S.Y, 0, 0},
      {0, 0, S.Z, 0},
      {0, 0, 0, 1}
    }
  };
  return M;
}/* End of 'MatrScale' function */

/* MatrSet */
__inline MATR MatrSet( FLT A00, FLT A01, FLT A02, FLT A03,
                       FLT A10, FLT A11, FLT A12, FLT A13,
                       FLT A20, FLT A21, FLT A22, FLT A23,
                       FLT A30, FLT A31, FLT A32, FLT A33 )
{
  MATR r =
  {
    {
      {A00, A01, A02, A03},
      {A10, A11, A12, A13},
      {A20, A21, A22, A23},
      {A30, A31, A32, A33}
    }
  };

  return r;
}/* End of 'MatrSet' function */

/* MatrFrustum */
__inline MATR MatrFrustum( FLT Left, FLT Right,
                           FLT Bottom, FLT Top,
                           FLT Near, FLT Far )
{
  return MatrSet(2 * Near / (Right - Left), 0, 0, 0,
                0, 2 * Near / (Top - Bottom), 0, 0,
                (Right + Left) / (Right - Left), (Top + Bottom) / (Top - Bottom),
                -(Far + Near) / ( Far - Near ), -1,
                0, 0, -2 * Near * Far / (Far - Near), 0);
}/* End of 'mth.h' function */

#endif /* __mth_h_ */

/* END OF 'mth.h' FILE */