-= 22.06.2021 =-
::11:30
��������� ������ (Vertex Buffer Object - VBO)
Vertex Buffer Object (VBO)

VBO � "�������� � �����������"

����� � �������� ���������� � �������������� ������ (� ������ ��������) ������ � ������ �������� (���� ��� ����) ������ � ����������.
���������� ���������: ������ ������ � ������ ��������

1.�������� ������

��� �������� ������ � vg4VERTEX (��� ���� FLT)

/* ��������� �������� ������ � ������� */
typedef struct tagvg4VERTEX
{
  VEC P;   /* ������� */
  VEC2 T;  /* ���������� ���������� */
  VEC N;   /* ������� */
  VEC4 C;  /* ���� (r,g,b,a) */
} vg4VERTEX;

/* ����� �������������� ���� ��������� �������� ������ � ������� (+MTH.H) */
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

2.�������� ������ � �����������

����� ��������� GPU:













?
���� �������� � GPU:









��� ������� ���������:

��� ������ ���������� - ������ ������ � ����� ������ (OpenGL):
                        vertex array     vertex buffer
                       (�������� ������)  (���� ������)
                            ��� ���           VERTEX

������ ������ - VertexArray - ������ ���������� ������ ������ ���� (layout).
����� ����� - VertexBuffer - ������ ������, ���������� � ����������.

����������������� ����

INT VA, VBuf;  -- ������ � ��������� ���������

glGenBuffers(1, &VBuf);
glGenVertexArrays(1, &VA);

/* ������ �������� ������ ������ */
glBindVertexArray(VA);

������� ������ � ����� ������:

/* ������ �������� ����� */
glBindBuffer(GL_ARRAY_BUFFER, VBuf);
/* ������� ������ (NumOfV - ���������� ������, V - ������ ������) */
glBufferData(GL_ARRAY_BUFFER, sizeof(vg4VERTEX) * NumOfV, V, GL_STATIC_DRAW);

��������� � ������� ������ ����� � ����� ������ ��������:

/* ������������ � ������� ������ ����� � ������� (���� ��� �� ������) */
glBindBuffer(GL_ARRAY_BUFFER, VBuf);

/*                    layout (����� ��������),
 *                       ���������� ���������,
 *                          ���,
 *                                   ���� �� �����������,
 *                                       ������ � ������ ������ �������� ������ (stride),
 *                                                  �������� � ������ �� ������ ������ */
glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(vg4VERTEX),
                      (VOID *)0); /* ������� P */
glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(vg4VERTEX),
                      (VOID *)sizeof(VEC)); /* ���������� ���������� T */
glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(vg4VERTEX),
                      (VOID *)(sizeof(VEC) + sizeof(VEC2))); /* ������� N */
glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(vg4VERTEX),
                      (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2))); /* ���� C */

/* �������� ������ ��������� (layout) */
glEnableVertexAttribArray(0);
glEnableVertexAttribArray(1);
glEnableVertexAttribArray(2);
glEnableVertexAttribArray(3);

/* ��������� ������ ������ */
glBindVertexArray(0);

��������

/* ������ �������� ������ ������ */
glBindVertexArray(VA);
/* "���������" ����� */
glBindBuffer(GL_ARRAY_BUFFER, 0);
glDeleteBuffers(1, &VBuf);
/* ������ ���������� ������ ������ */
glBindVertexArray(0);
glDeleteVertexArrays(1, &VA);

���������:

/* ������ �������� ������ ������ */
glBindVertexArray(VA);
/* ��������� */
glDrawArrays(GL_TRIANGLES, 0, NumOfV);
/* ��������� ������ ������ */
glBindVertexArray(0);

3.�������� ������� �������� � �����������

�������:

����������������� ����

INT IBuf;
. . .
glGenBuffers(1, &IBuf);

������� ������ � ����� ��������:

/* ������ �������� ����� */
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
/* ������� ������ (NumOfI - ���������� ��������, I - ������ ��������) */ 
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NumOfI, I, GL_STATIC_DRAW);

��������

glDeleteBuffers(1, &IBuf);

���������:

/* ������ �������� ������ ������ */
glBindVertexArray(VA);
/* ������ �������� ������ �������� */
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
/* ��������� */
glDrawElements(GL_TRIANGLES, NumOfI, GL_UNSIGNED_INT, NULL);
/* ��������� ������ ������ */
glBindVertexArray(0);
/* ��������� ������ �������� */
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



��������� � �������:

MTH.H + VEC2 VEC4
vg4VERTEX +T N C
VG4_RndPrim: Create Free Draw Load, ***Sphere ...

������� �������� �������� ��������� (�� ���������)

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
. . . ��������� ������� V � Ind

  VG4_RndPrimCreate(Pr, V, noofv, Ind, noofi);
  free(V);
