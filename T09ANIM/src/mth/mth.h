/* FILE NAME : mth.h
 * PROGRAMMER: KV6
 * DATE      : 15.06.2021 
 * PURPOSE   : 3D math implementation module.
 */

#ifndef __mth_h_
#define __mth_h_

#include <windows.h>

#include <math.h>

#define PI 3.14159265358979323846
#define Degree2Radian(a) D2R(a)
#define MatrMulMatr3(A, B, C) MatrMulMatr(MatrMulMatr(A, B), C)
#define SetVec1(A) VecSet1(A)
#define VecAddVec3(A, B, C) VecAddVec(VecAddVec(A, B), C);
#define MatrMulMatr4(A, B, C, D) MatrMulMatr(MatrMulMatr3(A, B, C), D)
#define MatrMulMatr5(A, B, C, D, E) MatrMulMatr(MatrMulMatr4(A, B, C, D), E)
#define MatrMulMatr6(A, B, C, D, E, F) MatrMulMatr(MatrMulMatr5(A, B, C, D, E), F)

#define UnitMatrix \
{                  \
  {                \
    {1, 0, 0, 0},  \
    {0, 1, 0, 0},  \
    {0, 0, 1, 0},  \
    {0, 0, 0, 1}   \
  }                \
}

/* Base float point types */
typedef DOUBLE DBL;
typedef FLOAT FLT;

/* Vector type */
typedef struct tagVEC
{
  FLT X, Y, Z; /* Coordinates */
} VEC;

/* Vector 2D type */
typedef struct tagVEC2
{
  FLT X, Y; /* Coordinates */
} VEC2;

/* Vector 4D type */
typedef struct tagVEC4
{
  FLT X, Y, Z, W; /* Coordinates */
} VEC4;

/* Matrix type */
typedef struct tagMATR
{
  FLT M[4][4];
} MATR;

__inline FLT D2R( FLT A )
{
  return (FLT)((A) * (PI / 180.0));
}

/* Vector setting function.
 * ARGUMENTS:
 *   - Coordinates:
 *       FLT X, Y, Z;
 * RETURNS:
 *   (VEC) Vector
*/
__inline VEC VecSet( FLT X, FLT Y, FLT Z )
{
  VEC v = {X, Y, Z};

  return v;
} /* End of 'VecSet' function */

/* Vector 2 setting function.
 * ARGUMENTS:
 *   - Coordinates:
 *       FLT X, Y;
 * RETURNS:
 *   (VEC2) Vector
*/
__inline VEC2 Vec2Set( FLT X, FLT Y )
{
  VEC2 v = {X, Y};

  return v;
} /* End of 'VecSet' function */

/* Vector setting function.
 * ARGUMENTS:
 *   - Coordinates:
 *       FLT X, Y, Z;
 * RETURNS:
 *   (VEC) Vector
*/
__inline VEC4 Vec4Set( FLT X, FLT Y, FLT Z, FLT W )
{
  VEC4 v = {X, Y, Z, W};

  return v;
} /* End of 'VecSet' function */

/* Vector setting by 1 parameter function.
 * ARGUMENTS:
 *   - Coordinates (1):
 *       FLT A;
 * RETURNS:
 *   (VEC) Vector
*/
__inline VEC VecSet1( FLT A )
{
  return VecSet(A, A, A);
} /* End of 'VecSet' function */

/* Two vectors summarizing function.
 * ARGUMENTS:
 *   - Vectors:
 *       VEC V1, VEC V2;
 * RETURNS:
 *   (VEC) Vector sum
*/
__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} /* End of 'VecAddVec' function */

/* Two vectors subtrackting function.
 * ARGUMENTS:
 *   - Vectors:
 *       VEC V1, VEC V2;
 * RETURNS:
 *   (VEC) Result vector
*/
__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
} /* End of 'VecSubVec' function */

/* Vector multiply number function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC V1;
 *   - Number:
 *       FLT N;
 * RETURNS:
 *   (VEC) Result vector
*/
__inline VEC VecMulNum( VEC V1, FLT N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
} /* End of 'VecMulNum' function */

/* Vector divide number function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC V1;
 *   - Number:
 *       FLT N;
 * RETURNS:
 *   (VEC) Result vector
*/
__inline VEC VecDivNum( VEC V1, FLT N )
{
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
} /* End of 'VecDivNum' function */

/* Vector negative function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC V;
 * RETURNS:
 *   (VEC) Result vector
*/
__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
} /* End of 'VecNeg' function */

/* Two vectors dot multiply function.
 * ARGUMENTS:
 *   - Vectors:
 *       VEC V1, VEC V2;
 * RETURNS:
 *   (FLT) Result of multiplying
*/
__inline FLT VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
} /* End of 'VecDotVec' function */

/* Two vectors cross multiply function.
 * ARGUMENTS:
 *   - Vectors:
 *       VEC V1, VEC V2;
 * RETURNS:
 *   (VEC) Result vector
*/
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
} /* End of 'VecCrossVec' function */

/* Vector len in pow2 function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC V;
 * RETURNS:
 *   (FLT) Result len
*/
__inline FLT VecLen2( VEC V )
{
  return VecDotVec(V, V);
} /* End of 'VecLen2' function */

/* Vector len function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC V;
 * RETURNS:
 *   (FLT) Result len
*/
__inline FLT VecLen( VEC V )
{
  FLT len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return len;
  return sqrtf(len);
} /* End of 'VecLen' function */

/* Vector normalizing function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC V;
 * RETURNS:
 *   (VEC) Normalized vector
*/
__inline VEC VecNormalize( VEC V )
{
  FLT len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return V;
  return VecDivNum(V, sqrtf(len));
} /* End of 'VecNormalize' function */

/* Vector multiply matrix function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC V;
 *   - Matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) result vector;
*/
__inline VEC VecMulMatr( VEC V, MATR M )
{
  FLT w = V.X * M.M[0][3] + V.Y * M.M[1][3] + V.Z * M.M[2][3] + M.M[3][3];

  return VecSet((V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0] + M.M[3][0]) / w, 
                (V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1] + M.M[3][1]) / w,
                (V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2] + M.M[3][2]) / w);
} /* End of 'VecMulMatr' function */

/* Point transformation function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC V;
 *   - Transformation matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) Result vector;
*/
__inline VEC PointTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0] + M.M[3][0], 
                V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1] + M.M[3][1],
                V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2] + M.M[3][2]);
} /* Enf of 'PointTransform' function */

/* Vector transformation function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC V;
 *   - Transformation matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) Result vector;
*/
__inline VEC VectorTransform( VEC V, MATR M )
{
  return VecMulMatr(V, M);
} /* Enf of 'VectorTransform' function */

/* Matrix 4x4 setting function.
 * ARGUMENTS:
 *   - First line parameters: 
 *       FLT A11, A12, A13, A14;
 *   - Second line parameters: 
 *       FLT A21, A22, A23, A24;
 *   - Third line parameters: 
 *       FLT A31, A32, A33, A34;
 *   - Fourth line parameters: 
 *       FLT A41, A42, A43, A44;
 * RETURNS:
 *   (MATR) Matrix.
*/
__inline MATR MatrSet( FLT A11, FLT A12, FLT A13, FLT A14,
                       FLT A21, FLT A22, FLT A23, FLT A24,
                       FLT A31, FLT A32, FLT A33, FLT A34,
                       FLT A41, FLT A42, FLT A43, FLT A44)
{
  MATR r =
  {
    {
      {A11, A12, A13, A14},
      {A21, A22, A23, A24},
      {A31, A32, A33, A34},
      {A41, A42, A43, A44}
    }
  };

  return r;
} /* End of 'MatrSet' function */

/* Matrix identity function.
 * ARGUMENTS:
 *   - (VOID) None.
 * RETURNS:
 *   (MATR) Matr identity.
*/
__inline MATR MatrIdentity( VOID )
{
  MATR I = UnitMatrix;
  return I;
} /* End of 'MatrIdentity' function */

/* Matr translate function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC T;
 * RETURNS:
 *   (MATR) Matr translated.
*/
__inline MATR MatrTranslate( VEC T )
{
  MATR m = UnitMatrix;

  m.M[3][0] = T.X;
  m.M[3][1] = T.Y;
  m.M[3][2] = T.Z;
  return m;
} /* End of 'MatrTranslate' function */

/* Matr rotate around vector function.
 * ARGUMENTS:
 *   - Angle in degrees:
 *       FLT AngleInDegree;
 *   - Vector:
 *       VEC V;
 * RETURNS:
 *   (MATR) Rotated matrix.
*/
__inline MATR MatrRotate( FLT AngleInDegree, VEC V )
{
  FLT a = D2R(AngleInDegree), s = (FLT)sin(a), c = (FLT)cos(a);
  VEC A = VecNormalize(V);
  MATR m =
  {
    {
      {c + A.X * A.X * (1 - c), A.X * A.Y * (1 - c) + A.Z * s, A.X * A.Z * (1 - c) - A.Y * s,0},
      {A.Y * A.X * (1 - c) - A.Z * s, c + A.Y * A.Y * (1 - c), A.Y * A.Z * (1 - c) + A.X * s, 0},
      {A.Z * A.X * (1 - c) + A.Y * s, A.Z * A.Y * (1 - c) - A.X * s, c + A.Z * A.Z * (1 - c) , 0},
      {0, 0, 0, 1}
    }  
  };

  return m;
} /* End of 'MatrRotate' function */

/* Matrix rotate around Y axis function.
 * ARGUMENTS:
 *   - Angle in degrees:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) Rotated matrix.
*/
__inline MATR MatrRotateY( FLT AngleInDegree )
{
  FLT a = D2R(AngleInDegree), s = (FLT)sin(a), c = (FLT)cos(a);
  MATR m =
  {
    {
      {c, 0, -s, 0},
      {0, 1, 0, 0},
      {s, 0, c, 0},
      {0, 0, 0, 1}
    }  
  };

  return m;
} /* End of 'MatrRotateY' function */

/* Matrix rotate around Z axis function.
 * ARGUMENTS:
 *   - Angle in degrees:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) Rotated matrix.
*/
__inline MATR MatrRotateZ( FLT AngleInDegree )
{
  FLT a = D2R(AngleInDegree), s = (FLT)sin(a), c = (FLT)cos(a);
  MATR m =
  {
    {
      {c, s, 0, 0},
      {-s, c, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    }  
  };

  return m;
} /* End of 'MatrRotateZ' function */

/* Matrix rotate around X axis function.
 * ARGUMENTS:
 *   - Angle in degrees:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) Rotated matrix.
*/
__inline MATR MatrRotateX( FLT AngleInDegree )
{
  FLT a = D2R(AngleInDegree), s = (FLT)sin(a), c = (FLT)cos(a);
  MATR m =
  {
    {
      {1, 0, 0, 0},
      {0, c, s, 0},
      {0, -s, c, 0},
      {0, 0, 0, 1}
    }  
  };

  return m;
} /* End of 'MatrRotateX' function */

/* Matrix multiply matrix function.
 * ARGUMENTS:
 *   - Matrixes to multiply:
 *       MATR M1, M2;
 * RETURNS:
 *   (MATR) Result matrix.
*/
__inline MATR MatrMulMatr( MATR M1, MATR M2 ) 
{
  MATR r = {{{0}}};

  r.M[0][0] = M1.M[0][0] * M2.M[0][0] + 
              M1.M[0][1] * M2.M[1][0] +
              M1.M[0][2] * M2.M[2][0] +
              M1.M[0][3] * M2.M[3][0];

  r.M[0][1] = M1.M[0][0] * M2.M[0][1] + 
              M1.M[0][1] * M2.M[1][1] +
              M1.M[0][2] * M2.M[2][1] +
              M1.M[0][3] * M2.M[3][1];

  r.M[0][2] = M1.M[0][0] * M2.M[0][2] + 
              M1.M[0][1] * M2.M[1][2] +
              M1.M[0][2] * M2.M[2][2] +
              M1.M[0][3] * M2.M[3][2];
  
  r.M[0][3] = M1.M[0][0] * M2.M[0][3] + 
              M1.M[0][1] * M2.M[1][3] +
              M1.M[0][2] * M2.M[2][3] +
              M1.M[0][3] * M2.M[3][3];

  r.M[1][0] = M1.M[1][0] * M2.M[0][0] + 
              M1.M[1][1] * M2.M[1][0] +
              M1.M[1][2] * M2.M[2][0] +
              M1.M[1][3] * M2.M[3][0];

  r.M[1][1] = M1.M[1][0] * M2.M[0][1] + 
              M1.M[1][1] * M2.M[1][1] +
              M1.M[1][2] * M2.M[2][1] +
              M1.M[1][3] * M2.M[3][1];

  r.M[1][2] = M1.M[1][0] * M2.M[0][2] + 
              M1.M[1][1] * M2.M[1][2] +
              M1.M[1][2] * M2.M[2][2] +
              M1.M[1][3] * M2.M[3][2];

  r.M[1][3] = M1.M[1][0] * M2.M[0][3] + 
              M1.M[1][1] * M2.M[1][3] +
              M1.M[1][2] * M2.M[2][3] +
              M1.M[1][3] * M2.M[3][3];

  r.M[2][0] = M1.M[2][0] * M2.M[0][0] + 
              M1.M[2][1] * M2.M[1][0] +
              M1.M[2][2] * M2.M[2][0] +
              M1.M[2][3] * M2.M[3][0];

  r.M[2][1] = M1.M[2][0] * M2.M[0][1] + 
              M1.M[2][1] * M2.M[1][1] +
              M1.M[2][2] * M2.M[2][1] +
              M1.M[2][3] * M2.M[3][1];

  r.M[2][2] = M1.M[2][0] * M2.M[0][2] + 
              M1.M[2][1] * M2.M[1][2] +
              M1.M[2][2] * M2.M[2][2] +
              M1.M[2][3] * M2.M[3][2];

  r.M[2][3] = M1.M[2][0] * M2.M[0][3] + 
              M1.M[2][1] * M2.M[1][3] +
              M1.M[2][2] * M2.M[2][3] +
              M1.M[2][3] * M2.M[3][3];

  r.M[3][0] = M1.M[3][0] * M2.M[0][0] + 
              M1.M[3][1] * M2.M[1][0] +
              M1.M[3][2] * M2.M[2][0] +
              M1.M[3][3] * M2.M[3][0];

  r.M[3][1] = M1.M[3][0] * M2.M[0][1] + 
              M1.M[3][1] * M2.M[1][1] +
              M1.M[3][2] * M2.M[2][1] +
              M1.M[3][3] * M2.M[3][1];

  r.M[3][2] = M1.M[3][0] * M2.M[0][2] + 
              M1.M[3][1] * M2.M[1][2] +
              M1.M[3][2] * M2.M[2][2] +
              M1.M[3][3] * M2.M[3][2];

  r.M[3][3] = M1.M[3][0] * M2.M[0][3] + 
              M1.M[3][1] * M2.M[1][3] +
              M1.M[3][2] * M2.M[2][3] +
              M1.M[3][3] * M2.M[3][3];
 
  return r;
} /* End of 'MatrMulMatr' function */

/* Matrix transpose function.
 * ARGUMENTS:
 *   - Matrix to transpose:
 *       MATR M;
 * RETURNS:
 *   (MATR) Transposed matrix.
*/
__inline MATR MatrTranspose( MATR M )
{
  MATR r = {{{0}}};

  r.M[0][0] = M.M[0][0];
  r.M[1][1] = M.M[1][1];
  r.M[2][2] = M.M[2][2];
  r.M[3][3] = M.M[3][3];

  r.M[1][0] = M.M[0][1];
  r.M[2][0] = M.M[0][2];
  r.M[3][0] = M.M[0][3];

  r.M[1][1] = M.M[1][1];
  r.M[2][1] = M.M[1][2];
  r.M[3][1] = M.M[1][3];

  r.M[1][2] = M.M[2][1];
  r.M[2][2] = M.M[2][2];
  r.M[3][2] = M.M[2][3];

  r.M[1][3] = M.M[3][1];
  r.M[2][3] = M.M[3][2];
  r.M[3][3] = M.M[3][3];

  return r;
} /* End of 'MatrTranspose' function */

/* Matrix 3x3 determinant.
 * ARGUMENTS:
 *   - First line parameters:
 *       FLT A11, A12, A13;
 *   - Second line parameters:
 *       FLT A21, A22, A23;
 *   - Third line parameters:
 *       FLT A31, A32, A33;
 * RETURNS:
 *   (FLT) Determinant;
*/
__inline FLT MatrDeterm3x3( FLT A11, FLT A12, FLT A13,
                   FLT A21, FLT A22, FLT A23,
                   FLT A31, FLT A32, FLT A33 )
{
  return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
         A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
} /* End of 'MatrDeterm3x3(' function */

/* Matrix 4x4 determinant finder.
 * ARGUMENTS:
 *   - Matrix:
 *       MATR M;
 * RETURNS:
 *   (FLT) Determinant;
*/
__inline FLT MatrDeterm( MATR M )
{
  return
    M.M[0][0] * MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                               M.M[2][1], M.M[2][2], M.M[2][3],
                               M.M[3][1], M.M[3][2], M.M[3][3]) -
    M.M[0][1] * MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                               M.M[2][0], M.M[2][2], M.M[2][3],
                               M.M[3][0], M.M[3][2], M.M[3][3]) +
    M.M[0][2] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                               M.M[2][0], M.M[2][1], M.M[2][3],
                               M.M[3][0], M.M[3][1], M.M[3][3]) -
    M.M[0][3] * MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                               M.M[2][0], M.M[2][1], M.M[2][2],
                               M.M[3][0], M.M[3][1], M.M[3][2]);
} /* End of 'MatrDeterm' function */

/* Inversed matrix function.
 * ARGUMENTS:
 *   - Matrix to inverse:
 *       MATR M;
 * RETURNS:
 *   (MATR) Inversed matrix.
*/
__inline MATR MatrInverse( MATR M )
{
  FLT det = MatrDeterm(M);
  MATR r;

  if (det == 0)
    return MatrIdentity();

  /* Build adjoint matrix */
  r.M[0][0] =
    +MatrDeterm3x3(M.M[1][1], M.M[1][2], M.M[1][3],
                   M.M[2][1], M.M[2][2], M.M[2][3],
                   M.M[3][1], M.M[3][2], M.M[3][3]) / det;
  r.M[1][0] =
    -MatrDeterm3x3(M.M[1][0], M.M[1][2], M.M[1][3],
                   M.M[2][0], M.M[2][2], M.M[2][3],
                   M.M[3][0], M.M[3][2], M.M[3][3]) / det;
  r.M[2][0] =
    +MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][3],
                   M.M[2][0], M.M[2][1], M.M[2][3],
                   M.M[3][0], M.M[3][1], M.M[3][3]) / det;
  r.M[3][0] =
    -MatrDeterm3x3(M.M[1][0], M.M[1][1], M.M[1][2],
                   M.M[2][0], M.M[2][1], M.M[2][2],
                   M.M[3][0], M.M[3][1], M.M[3][2]) / det;

  r.M[0][1] =
    -MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                   M.M[2][1], M.M[2][2], M.M[2][3],
                   M.M[3][1], M.M[3][2], M.M[3][3]) / det;
  r.M[1][1] =
    +MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                   M.M[2][0], M.M[2][2], M.M[2][3],
                   M.M[3][0], M.M[3][2], M.M[3][3]) / det;
  r.M[2][1] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                   M.M[2][0], M.M[2][1], M.M[2][3],
                   M.M[3][0], M.M[3][1], M.M[3][3]) / det;
  r.M[3][1] =
    +MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                   M.M[2][0], M.M[2][1], M.M[2][2],
                   M.M[3][0], M.M[3][1], M.M[3][2]) / det;


  r.M[0][2] =
    +MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                   M.M[1][1], M.M[1][2], M.M[1][3],
                   M.M[3][1], M.M[3][2], M.M[3][3]) / det;
  r.M[1][2] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                   M.M[1][0], M.M[1][2], M.M[1][3],
                   M.M[3][0], M.M[3][2], M.M[3][3]) / det;
  r.M[2][2] =
    +MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                   M.M[1][0], M.M[1][1], M.M[1][3],
                   M.M[3][0], M.M[3][1], M.M[3][3]) / det;
  r.M[3][2] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                   M.M[1][0], M.M[1][1], M.M[1][2],
                   M.M[3][0], M.M[3][1], M.M[3][2]) / det;

  r.M[0][3] =
    -MatrDeterm3x3(M.M[0][1], M.M[0][2], M.M[0][3],
                   M.M[1][1], M.M[1][2], M.M[1][3],
                   M.M[2][1], M.M[2][2], M.M[2][3]) / det;
  r.M[1][3] =
    +MatrDeterm3x3(M.M[0][0], M.M[0][2], M.M[0][3],
                   M.M[1][0], M.M[1][2], M.M[1][3],
                   M.M[2][0], M.M[2][2], M.M[2][3]) / det;
  r.M[2][3] =
    -MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][3],
                   M.M[1][0], M.M[1][1], M.M[1][3],
                   M.M[2][0], M.M[2][1], M.M[2][3]) / det;
  r.M[3][3] =
    +MatrDeterm3x3(M.M[0][0], M.M[0][1], M.M[0][2],
                   M.M[1][0], M.M[1][1], M.M[1][2],
                   M.M[2][0], M.M[2][1], M.M[2][2]) / det;

  return r;
} /* End of 'MatrInverse' function */

/* Matrix scale function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC S;
 * RETURNS:
 *   (MATR) Matrix.
*/
__inline MATR MatrScale( VEC S )
{
  return MatrSet(S.X, 0, 0, 0,
                 0, S.Y, 0, 0,
                 0, 0, S.Y, 0,
                 0, 0, 0, 1);
} /* End of 'MatrScale' function */

/* Matrix look-at viewer setup function.
 * ARGUMENTS:
 *   - viewer position, look-at point, approximate up direction:
 *       VEC Loc, At, Up1;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecNormalize(VecCrossVec(Right, Dir));

  return MatrSet(Right.X, Up.X, -Dir.X, 0,
                 Right.Y, Up.Y, -Dir.Y, 0,
                 Right.Z, Up.Z, -Dir.Z, 0,
                 -VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1);
} /* End of 'MatrView' function */


/* Matrix frustum (view) function.
 * ARGUMENTS:
 *   - Window borders:
 *       FLT Left, Right, Bottom, Top;
 *   - View borders:
 *       FLT Near, Far;
 * RETURNS:
 *   (MATR) Result matrix.
*/
__inline MATR MatrFrustum( FLT Left, FLT Right, 
                       FLT Bottom, FLT Top, 
                       FLT Near, FLT Far )
{
  return MatrSet(2 * Near / (Right - Left), 0, 0, 0, 
                 0, 2 * Near / (Top - Bottom), 0, 0, 
                 (Right + Left) / (Right - Left), (Top + Bottom) / (Top - Bottom), 
                 -(Far + Near) / (Far - Near), -1, 
                 0, 0, -2 * Near * Far / (Far -  Near), 0);
} /* End of 'MatrFrustum' function */


#endif /* __mth_h_ */

/* END OF 'mth.h' FILE */