::16:47
Animation system
Макет анимации
Animation system
OS	Animation	Application	Render3D
WinMain:
- регистрация класса
  окна
- создание окна
- цикл сообщений
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
инициализация

AnimClose();
деинициализация

AnimResize(W, H);
изменение размера кадра

AnimCopyFrame(hDC);
копирование кадра

AnimRender();
построение кадра
(опрос устройств ввода,
обновление таймера,
опрос всех элементов анимации и вызов у них функции Response, очистка кадра и вызов у всех функций анимации Render)


+контекст анимации
ANIM Anim;


	массив элементов анимации
UNIT:
[

  Init(Anim);
   инициализация

  Close(Anim);
   деинициализация

  Response(Anim);
отклик элемента анимации на смену кадра (обработка клавиатуры, таймера и т.п.)

  Render(Anim);
отрисовка элемента анимации

]

в каждую функцию элемента анимации приходит параметр - Anim - текущий контекст
(параметры) анимации:
  - клавиатура
  - мышь
  - джойстик
  - таймер
  - параметры ввода (...)
  - параметры визуализации (hDC, ... )	
RndInit(hWnd);

RndClose();

RndResize(W, H);

RndStart();

RndEnd();

RndCopyFrame(hDC);

-----------

RndPrim:
  Create/Load/Free/Draw


Как сделать элементы анимации с разным поведением?

1.разное поведение - 
  - указатели на функции Init, Close, Response, Render в структуре UNIT

первое приближение:

typedef struct tagUNIT UNIT;
struct tagUNIT
{
  VOID (*Init)( UNIT *Uni, ANIM *Ani );
  VOID (*Close)( UNIT *Uni, ANIM *Ani );
  VOID (*Response)( UNIT *Uni, ANIM *Ani );
  VOID (*Render)( UNIT *Uni, ANIM *Ani );
};

т.е. в анимации хранится массив указателей на элементы анимации (в Anim):

#define MAX_UNITS 3000
UNIT *Units[MAX_UNITS];
INT NumOfUnits;
----------------------
добавление:
UNIT *Uni = UnitCreateCow();

Anim.Units[NumOfUnits] = Uni;
Uni->Init(Uni, &Anim);
  или
Anim.Unit[NumOfUnits]->Init(Anim.Unit[NumOfUnits], &Anim);

Anim.NumOfUnits++;


в AnimRender у анимации (например, для отрисовки):

  RndStart();
  for (i = 0; i < Anim.NumOfUnits; i++)
    Anim.Units[i]->Render(Anim.Units[i], &Anim);
  RndEnd();

!!! Основной принцип ООП: данные управляют собственным поведением !!!

Все написанное выше являет собой реализацию полиморфоного поведения.

Принципы ООП:
- ИНКАПСУЛЯЦИЯ (incapsulation) - сокрытие данных
- НАСЛЕДОВАНИЕ (iheritance) - включение полей одних структур - в другие
- ПОЛИМОРФИЗМ (polymorph, override) - различное поведение наследуемых функций

2.как сделать данные (элементы анимации) разного размера?

Все объекты анимации (UNIT – "юнит") хранятся как указатели в общем массиве.

Так как начало всех объектов анимации содержит одинаковые поля – при доступе к каждому из объектов система будеи иметь возможность вызвать любую функцию из базовых 4-х.

Для доступа из функции к дополнительным значениям – в каждую передается указатель на саму структуру объекта анимации.


UNIT *Units[MAX_UNITS]:





				












!!! Т.е. каждая функция UNIT-а должна еще получать указатель  на самого себя
(self-pointer, в Си++ это решено служебным словом this).


базовый тип:

в define запишем все базовые поля элемента анимации:
#define UNIT_BASE_FIELDS \
  VOID (*Init)( UNIT *Uni, ANIM *Ani );      \
  VOID (*Close)( UNIT *Uni, ANIM *Ani );     \
  VOID (*Response)( UNIT *Uni, ANIM *Ani );  \
  VOID (*Render)( UNIT *Uni, ANIM *Ani )

базовый тип:

typedef struct tagUNIT UNIT;
struct tagUNIT
{
  UNIT_BASE_FIELDS;
};

производный тип – примеры:

typedef struct tagUNIT_COW UNIT_COW;
struct tagUNIT_COW
{
  UNIT_BASE_FIELDS;
  PRIM Cow;
  VEC Pos;
};

Реализуем функцию добавления объекта анимации:

VOID AnimUnitAdd( UNIT *Uni )
{
  if (Anim.NumOfUnits < MAX_UNITS)
    Anim.Unit[Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &Anim);

}

Вызов в WinMain:
  . . .
  AnimUnitAdd(UnitCowCreate());
  . . .

Реализация объектов анимации:
Реализация обработки объектов анимации:
anim/unit.c:
-- функции обработки по умолчанию (UnitInit, UnitClose, UnitResponse, UnitRender)
   (функции - "заглушки") - нужны для начальной инициализации любого объекта анимации


?
!!! наши типы: vg4ANIM vg4UNIT
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

-- функция создания объекта:

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

-- пример своего объекта анимации:

src/units/units.h -- сюда заносим прототипы создания всех "наших" "юнитов"
                     (в нем #include "../anim/anim.h")
src/units/u_bball.c – bounce ball

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


РЕАЛИЗАЦИЯ:

src/def.h
  MemHandle
  (DBL FLT --> MTH.H)
  UINT64 INT64           --> unsigned __int64, __int64

src/win/main.c - WinMain + WinFunc (работа с WinAPI)

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


+ VG4_Anim - глобальная переменная - структура контекста анимации типа vg4ANIM:



vg4ANIM VG4_Anim;
src/anim/anim.h
  -- типы:
  vg4UNIT
  vg4ANIM
  -- прототипы функций
  ***
  extern vg4ANIM VG4_Anim;

  --> + #include "rnd/rnd.h"

typedef struct tagvg4UNIT vg4UNIT;
typedef struct tagvg4ANIM
{
  HWND hWnd;                     - окно
  HDC hDC;                       - контекст в памяти 
  INT W, H;                      - размер окна


  vg4UNIT *Units[VG4_MAX_UNITS]; - массив объектов анимации
  INT NumOfUnits;                - текущее количество объектов анимации

  + все пользовательские данные от таймера и системы ввода

} vg4ANIM;

struct tagvg4UNIT
. . .

src/units/units.h
+ #include "../anim/anim.h"

-- функции-конструкторы примеров:
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
