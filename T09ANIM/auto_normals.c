::16:00
��� �����������:

� ��� ����:
-- ������ ������   VERTEX V[]{P, T, N, C}
-- ������ �������� INT Ind[]

���������� �������� � ��������� ������:
-- ������ ���� ������ ��������
    for (i = 0; i < NumOfV; i++)
      V[i].N = VecSet(0, 0, 0);
-- ��������� ��� ������������ (�� ��������)
   -- �� ���� ������ ������ ������� � ������������� � ����������� (���������)
   -- � ������� ������ ����� ������������ ��������� ����������� ������� (�.�. ������� ������ ����� � ����� ���� ������� ������� � �� �������������)
    for (i = 0; i < NumOfI; i += 3)
    {
      VEC
        p0 = V[Ind[i]].P,
        p1 = V[Ind[i + 1]].P,
        p2 = V[Ind[i + 2]].P,
        N = VecNormalize(VecCrossVec(VecSubVec(p1, p0), VecSubVec(p2, p0)));

      V[Ind[i]].N = VecAddVec(V[Ind[i]].N, N); /* VecAddVecEq(&V[Ind[i]].N, N); */
      V[Ind[i + 1]].N = VecAddVec(V[Ind[i + 1]].N, N);
      V[Ind[i + 2]].N = VecAddVec(V[Ind[i + 2]].N, N);
    }

-- ��������� �� ���� ������ � ��������� ��� �������
    for (i = 0; i < NumOfV; i++)
      V[i].N = VecNormalize(V[i].N);

Fake illuminaion:







nl = VecDotVec(V[i].N, L);
if (nl < 0.1)
  nl = 0.1;
V[i].C = Vec4Set(r * nl, g * nl, b * nl, 1);

