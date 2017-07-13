
/******************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

/*
mtrl.h
����� ������� ��� ����������
*/

//��������� ������� �� ��������� (��� ����������)
void ClipFar(half curr_z, half far)
{
	clip(far-curr_z);
}

//������� ����� �������� ������� [0,1] �� ��������� ������� ������� � ���������� ���������
half4 GetDepthW(half4 pos, half2 near_far)
{
	half depth = (pos.z + near_far.x)/near_far.y;
	return half4(depth,depth,depth,1);
}

//! debug ������� �������� �������
half4 GetDepthLinearR(half depth, half2 near_far)
{
	return depth;
}

//������� �������� �� ��������� �������� ������� � ���������� ���������
half4 GetDepthDistR(half depth, half2 near_far)
{
	return depth*near_far.y;
}