-= 22.06.2021 =-
::11:30
Вершинные буфера (Vertex Buffer Object - VBO)
Vertex Buffer Object (VBO)

VBO – "ПРИМИТИВ В ВИДЕОПАМЯТИ"

Новое в хранении примитивов – геометрические данные (и другие атрибуты) вершин и массив индексов (если они есть) храним в видеокарте.
Компоненты примитива: массив вершин и массив индексов

1.Хранение вершин

тип хранения вершин – vg4VERTEX (все типы FLT)

/* Структура хранения данных о вершине */
typedef struct tagvg4VERTEX
{
  VEC P;   /* позиция */
  VEC2 T;  /* текстурная координата */
  VEC N;   /* нормаль */
  VEC4 C;  /* Цвет (r,g,b,a) */
} vg4VERTEX;

/* Новые геометрические типы Структура хранения данных о вершине (+MTH.H) */
typedef struct tagVEC2
{
  FLT X, Y;
} VEC2;

typedef struct tagVEC4
{
  FLT X, Y, Z, W;
} VEC4;

VEC4 Vec4Set( FLT A, FLT B, FLT C, FLT D );
VEC4 Vec4Set1( FLT A );
VEC2 Vec2Set( FLT A, FLT B );
VEC2 Vec2Set1( FLT A );

2.Передача вершин в видеопамять

общая концепция GPU:













?
сама передача в GPU:









Для каждого примитива:

для работы необходимы - массив вершин и буфер вершин (OpenGL):
                        vertex array     vertex buffer
                       (описание данных)  (сами данные)
                            кто где           VERTEX

массив вершин - VertexArray - связка посылаемых данных сверху вниз (layout).
буфер вешин - VertexBuffer - массив данных, отсылаемых в видеокарту.

инициализационный этап

INT VA, VBuf;  -- храним в структуре примитива

glGenBuffers(1, &VBuf);
glGenVertexArrays(1, &VA);

/* делаем активным массив вершин */
glBindVertexArray(VA);

заносим данные в буфер вершин:

/* делаем активным буфер */
glBindBuffer(GL_ARRAY_BUFFER, VBuf);
/* сливаем данные (NumOfV - количество вершин, V - массив вершин) */
glBufferData(GL_ARRAY_BUFFER, sizeof(vg4VERTEX) * NumOfV, V, GL_STATIC_DRAW);

указываем в массиве вершин буфер и какие данные содержит:

/* присоединяем к массиву вершин буфер с данными (если еще не делали) */
glBindBuffer(GL_ARRAY_BUFFER, VBuf);

/*                    layout (номер атрибута),
 *                       количество компонент,
 *                          тип,
 *                                   надо ли нормировать,
 *                                       размер в байтах одного элемента буфера (stride),
 *                                                  смещение в байтах до начала данных */
glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(vg4VERTEX),
                      (VOID *)0); /* позиция P */
glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(vg4VERTEX),
                      (VOID *)sizeof(VEC)); /* текстурные координаты T */
glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(vg4VERTEX),
                      (VOID *)(sizeof(VEC) + sizeof(VEC2))); /* нормаль N */
glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(vg4VERTEX),
                      (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2))); /* цвет C */

/* включаем нужные аттрибуты (layout) */
glEnableVertexAttribArray(0);
glEnableVertexAttribArray(1);
glEnableVertexAttribArray(2);
glEnableVertexAttribArray(3);

/* выключили массив вершин */
glBindVertexArray(0);

удаление

/* делаем активным массив вершин */
glBindVertexArray(VA);
/* "отцепляем" буфер */
glBindBuffer(GL_ARRAY_BUFFER, 0);
glDeleteBuffers(1, &VBuf);
/* делаем неактивным массив вершин */
glBindVertexArray(0);
glDeleteVertexArrays(1, &VA);

Отрисовка:

/* делаем активным массив вершин */
glBindVertexArray(VA);
/* отрисовка */
glDrawArrays(GL_TRIANGLES, 0, NumOfV);
/* выключили массив вершин */
glBindVertexArray(0);

3.Передача массива индексов в видеопамять

Индексы:

инициализационный этап

INT IBuf;
. . .
glGenBuffers(1, &IBuf);

заносим данные в буфер индексов:

/* делаем активным буфер */
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
/* сливаем данные (NumOfI - количество индексов, I - массив индексов) */ 
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NumOfI, I, GL_STATIC_DRAW);

удаление

glDeleteBuffers(1, &IBuf);

Отрисовка:

/* делаем активным массив вершин */
glBindVertexArray(VA);
/* делаем активным массив индексов */
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
/* отрисовка */
glDrawElements(GL_TRIANGLES, NumOfI, GL_UNSIGNED_INT, NULL);
/* выключили массив вершин */
glBindVertexArray(0);
/* выключили массив индексов */
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



Изменения в проекте:

MTH.H + VEC2 VEC4
vg4VERTEX +T N C
VG4_RndPrim: Create Free Draw Load, ***Sphere ...

типовой фрагмент создания примитива (из геометрии)

  INT noofv, noofi, size;
  vg4VERTEX *V;
  INT *Ind;

  memset(Pr, 0, sizeof(vg4PRIM));

  noofv = . . .;
  noofi = . . .;
  size = sizeof(vg4VERTEX) * noofv + sizeof(INT) * noofi;

  if ((V = malloc(size)) == NULL)
    return FALSE;
  Ind = (INT *)(V + noofv);
. . . заполнили массивы V и Ind

  VG4_RndPrimCreate(Pr, V, noofv, Ind, noofi);
  free(V);
