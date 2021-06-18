::16:47
Animation system
����� ��������
Animation system
OS	Animation	Application	Render3D
WinMain:
- ����������� ������
  ����
- �������� ����
- ���� ���������
   while (GetMessage(...))
      DispatchMessage(...);


WinFunc:
WM_GETMINMAXINFO:
  . . .
WM_CREATE:
  . . .
WM_SIZE:
  . . .
WM_TIMER:
  . . .
WM_ERASEBKGND:
  . . .
WM_PAINT:
  . . .
WM_DESTROY:
  . . .
	


AnimInit(hWnd);
�������������

AnimClose();
���������������

AnimResize(W, H);
��������� ������� �����

AnimCopyFrame(hDC);
����������� �����

AnimRender();
���������� �����
(����� ��������� �����,
���������� �������,
����� ���� ��������� �������� � ����� � ��� ������� Response, ������� ����� � ����� � ���� ������� �������� Render)


+�������� ��������
ANIM Anim;


	������ ��������� ��������
UNIT:
[

  Init(Anim);
   �������������

  Close(Anim);
   ���������������

  Response(Anim);
������ �������� �������� �� ����� ����� (��������� ����������, ������� � �.�.)

  Render(Anim);
��������� �������� ��������

]

� ������ ������� �������� �������� �������� �������� - Anim - ������� ��������
(���������) ��������:
  - ����������
  - ����
  - ��������
  - ������
  - ��������� ����� (...)
  - ��������� ������������ (hDC, ... )	
RndInit(hWnd);

RndClose();

RndResize(W, H);

RndStart();

RndEnd();

RndCopyFrame(hDC);

-----------

RndPrim:
  Create/Load/Free/Draw


��� ������� �������� �������� � ������ ����������?

1.������ ��������� - 
  - ��������� �� ������� Init, Close, Response, Render � ��������� UNIT

������ �����������:

typedef struct tagUNIT UNIT;
struct tagUNIT
{
  VOID (*Init)( UNIT *Uni, ANIM *Ani );
  VOID (*Close)( UNIT *Uni, ANIM *Ani );
  VOID (*Response)( UNIT *Uni, ANIM *Ani );
  VOID (*Render)( UNIT *Uni, ANIM *Ani );
};

�.�. � �������� �������� ������ ���������� �� �������� �������� (� Anim):

#define MAX_UNITS 3000
UNIT *Units[MAX_UNITS];
INT NumOfUnits;
----------------------
����������:
UNIT *Uni = UnitCreateCow();

Anim.Units[NumOfUnits] = Uni;
Uni->Init(Uni, &Anim);
  ���
Anim.Unit[NumOfUnits]->Init(Anim.Unit[NumOfUnits], &Anim);

Anim.NumOfUnits++;


� AnimRender � �������� (��������, ��� ���������):

  RndStart();
  for (i = 0; i < Anim.NumOfUnits; i++)
    Anim.Units[i]->Render(Anim.Units[i], &Anim);
  RndEnd();

!!! �������� ������� ���: ������ ��������� ����������� ���������� !!!

��� ���������� ���� ������ ����� ���������� ������������� ���������.

�������� ���:
- ������������ (incapsulation) - �������� ������
- ������������ (iheritance) - ��������� ����� ����� �������� - � ������
- ����������� (polymorph, override) - ��������� ��������� ����������� �������

2.��� ������� ������ (�������� ��������) ������� �������?

��� ������� �������� (UNIT � "����") �������� ��� ��������� � ����� �������.

��� ��� ������ ���� �������� �������� �������� ���������� ���� � ��� ������� � ������� �� �������� ������� ����� ����� ����������� ������� ����� ������� �� ������� 4-�.

��� ������� �� ������� � �������������� ��������� � � ������ ���������� ��������� �� ���� ��������� ������� ��������.


UNIT *Units[MAX_UNITS]:





				












!!! �.�. ������ ������� UNIT-� ������ ��� �������� ���������  �� ������ ����
(self-pointer, � ��++ ��� ������ ��������� ������ this).


������� ���:

� define ������� ��� ������� ���� �������� ��������:
#define UNIT_BASE_FIELDS \
  VOID (*Init)( UNIT *Uni, ANIM *Ani );      \
  VOID (*Close)( UNIT *Uni, ANIM *Ani );     \
  VOID (*Response)( UNIT *Uni, ANIM *Ani );  \
  VOID (*Render)( UNIT *Uni, ANIM *Ani )

������� ���:

typedef struct tagUNIT UNIT;
struct tagUNIT
{
  UNIT_BASE_FIELDS;
};

����������� ��� � �������:

typedef struct tagUNIT_COW UNIT_COW;
struct tagUNIT_COW
{
  UNIT_BASE_FIELDS;
  PRIM Cow;
  VEC Pos;
};

��������� ������� ���������� ������� ��������:

VOID AnimUnitAdd( UNIT *Uni )
{
  if (Anim.NumOfUnits < MAX_UNITS)
    Anim.Unit[Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &Anim);

}

����� � WinMain:
  . . .
  AnimUnitAdd(UnitCowCreate());
  . . .

���������� �������� ��������:
���������� ��������� �������� ��������:
anim/unit.c:
-- ������� ��������� �� ��������� (UnitInit, UnitClose, UnitResponse, UnitRender)
   (������� - "��������") - ����� ��� ��������� ������������� ������ ������� ��������


?
!!! ���� ����: vg4ANIM vg4UNIT
/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID VG4_UnitInit( vg4UNIT *Uni, vg4ANIM *Ani )
{
} /* End of 'VG4_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID VG4_UnitClose( vg4UNIT *Uni, vg4ANIM *Ani )
{
} /* End of 'VG4_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID VG4_UnitResponse( vg4UNIT *Uni, vg4ANIM *Ani );
{
} /* End of 'VG4_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID VG4_UnitRender( vg4UNIT *Uni, vg4ANIM *Ani )
{
} /* End of 'VG4_UnitRender' function */

-- ������� �������� �������:

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (vg4UNIT *) pointer to created unit.
 */
vg4UNIT * VG4_AnimUnitCreate( INT Size )
{
  vg4UNIT *Uni;


  /* Memory allocation */
  if (Size < sizeof(vg4UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);

  /* Setup unit methods */
  Uni->Init = VG4_UnitInit;
  Uni->Close = VG4_UnitClose;
  Uni->Response = VG4_UnitResponse;
  Uni->Render = VG4_UnitRender;

  return Uni;
} /* End of 'VG4_AnimUnitCreate' function */

-- ������ ������ ������� ��������:

src/units/units.h -- ���� ������� ��������� �������� ���� "�����" "������"
                     (� ��� #include "../anim/anim.h")
src/units/u_bball.c � bounce ball

#include "units.h"

typedef struct
{
  VG4_UNIT_BASE_FIELDS;
  VEC Pos;
} vg4UNIT_BALL;

/* Bounce ball unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT_BALL *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID VG4_UnitInit( vg4UNIT_BALL *Uni, vg4ANIM *Ani )
{
  Uni->Pos = VecSet(0, 1, 0);
} /* End of 'VG4_UnitInit' function */

/* Bounce ball unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT_BALL *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID VG4_UnitResponse( vg4UNIT_BALL *Uni, vg4ANIM *Ani );
{
  Uni->Pos.X += Ani->DeltaTime * 2.5;
} /* End of 'VG4_UnitResponse' function */

/* Bounce ball unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT_BALL *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID VG4_UnitRender( vg4UNIT_BALL *Uni, vg4ANIM *Ani )
{
  DrawSphere(Uni->Pos, 3);
} /* End of 'VG4_UnitRender' function */

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (vg4UNIT *) pointer to created unit.
 */
vg4UNIT * VG4_UnitCreateBall( VOID )
{
  vg4UNIT *Uni;

  if ((Uni = (vg4UNIT_BALL *)VG4_AnimUnitCreate(sizeof(vg4UNIT_BALL))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)VG4_UnitInit;
  Uni->Response = (VOID *)VG4_UnitResponse;
  Uni->Render = (VOID *)VG4_UnitRender;

  return Uni;
} /* End of 'VG4_UnitCreateBall' function */


����������:

src/def.h
  MemHandle
  (DBL FLT --> MTH.H)
  UINT64 INT64           --> unsigned __int64, __int64

src/win/main.c - WinMain + WinFunc (������ � WinAPI)

src/anim/anim.c
  VG4_Anim***
  VG4_AnimInit( HWND hWnd );
  VG4_AnimClose( VOID );
  VG4_AnimResize( INT W, INT H );
  VG4_AnimCopyFrame( HDC hDC );
  VG4_AnimRender( VOID );
  VG4_AnimAddUnit( vg4UNIT *Uni );
  VG4_AnimFlipFullScreen( VOID );
  VG4_AnimExit( VOID );


+ VG4_Anim - ���������� ���������� - ��������� ��������� �������� ���� vg4ANIM:



vg4ANIM VG4_Anim;
src/anim/anim.h
  -- ����:
  vg4UNIT
  vg4ANIM
  -- ��������� �������
  ***
  extern vg4ANIM VG4_Anim;

  --> + #include "rnd/rnd.h"

typedef struct tagvg4UNIT vg4UNIT;
typedef struct tagvg4ANIM
{
  HWND hWnd;                     - ����
  HDC hDC;                       - �������� � ������ 
  INT W, H;                      - ������ ����


  vg4UNIT *Units[VG4_MAX_UNITS]; - ������ �������� ��������
  INT NumOfUnits;                - ������� ���������� �������� ��������

  + ��� ���������������� ������ �� ������� � ������� �����

} vg4ANIM;

struct tagvg4UNIT
. . .

src/units/units.h
+ #include "../anim/anim.h"

-- �������-������������ ��������:
/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (vg4UNIT *) pointer to created unit.
 */
vg4UNIT * VG4_UnitCreateBall( VOID );
. . .

src/win/main.c
#include "../units/units.h"
WinMain:
  . . .
  VG4_AnimUnitAdd(VG4_UnitCreateBall());
  . . .

   --> Project\Source Files\Units\
src/units/u_bball.c #include "units.h"
src/units/u_cow.c   #include "units.h"
src/units/u_ctrl.c  #include "units.h"


VG4_AnimInit:
  VG4_Anim.hWnd = hWnd;
  VG4_RndInit(hWnd);
  VG4_Anim.hDC = VG4_hRndDCFrame;


VG4_AnimClose:
  for (i = 0; i < VG4_Anim.NumOfUnits; i++)
  {
    VG4_Anim.Units[i]->Close(VG4_Anim.Units[i], &VG4_Anim);
    free(VG4_Anim.Units[i]);
    VG4_Anim.Units[i] = NULL;
  }
  VG4_Anim.NumOfUnits = 0;
  VG4_RndClose();

VG4_AnimResize:
  VG4_Anim.W = W;
  VG4_Anim.H = H;
  VG4_RndResize(W, H);
  . . .

VG4_AnimCopyFrame:
  VG4_RndCopyFrame(hDC);

VG4_AnimRender:
  . . . timer, keyboard, mouse, joystick . . .

  for (i = 0; i < VG4_Anim.NumOfUnits; i++)
    VG4_Anim.Units[i]->Response(VG4_Anim.Units[i], &VG4_Anim);

  VG4_RndStart();
  for (i = 0; i < VG4_Anim.NumOfUnits; i++)
    VG4_Anim.Units[i]->Render(VG4_Anim.Units[i], &VG4_Anim);
  VG4_RndEnd();

MTH->Rnd-> ::: +Anim
