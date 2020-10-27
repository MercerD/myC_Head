/*
 * fft_ld.c
 *
 */

#include "fft_ld.h"

/*----------------------ȫ�ֱ�������-------------------------*/

cp W_N[N];
cp xL[2][N];

/*----------------------�����Ǻ�������-------------------------*/

/* ��ת����
 * @����  ���ú��������ֵĶ�������_rλ��ת
 * @����1 ����Ҫ����ת������a
 * @����2 ����_rλΪ�������з�ת
 * @����ֵ������a��_rλΪ�������з�ת�Ľ��
 * @ע��  ����Ҫע������������Լ���Ӧ�ķ�Χ
 */
int BR(int a, int _r)
{
	int b = 0;
	for (int i = 0;i < _r - 1;i++)
	{
		b += (a & 0x1);
		a = a >> 1;
		b = b << 1;
	}
	b += (a & 0x1);
	return b;
}
/* doubleתcp
 * @����  �� �ú�����double����תΪ�鲿Ϊ0�ĸ���
 * @����1 ����Ҫ��ת��������a
 * @����ֵ������aת���Ľ��
 * @ע��  ����Ҫע������������Լ���Ӧ�ķ�Χ
 */
cp double2cp(double a)
{
	cp com;
	com._Val[0] = a;
	com._Val[1] = 0;
	return com;
}
/* �����ӷ�
 * @����  ���ú����������������
 * @����1 ������a
 * @����2 ������b
 * @����ֵ��a��b�ĺ���
 * @ע��  ����Ҫע������������Լ���Ӧ�ķ�Χ
 */
cp add_I(cp a, cp b)
{
	cp com;
	com._Val[0] = a._Val[0] + b._Val[0];
	com._Val[1] = a._Val[1] + b._Val[1];
	return com;
}
/* ��������
 * @����  ���ú����������������
 * @����1 ��������a
 * @����2 ������b
 * @����ֵ��a��b�Ĳ�
 * @ע��  ����Ҫע������������Լ���Ӧ�ķ�Χ
 */
cp sub_I(cp a, cp b)
{
	cp com;
	com._Val[0] = a._Val[0] - b._Val[0];
	com._Val[1] = a._Val[1] - b._Val[1];
	return com;
}
/* �����˷�
 * @����  ���ú����������������
 * @����1 ������a
 * @����2 ������b
 * @����ֵ��a��b�ĺͻ�
 * @ע��  ����Ҫע������������Լ���Ӧ�ķ�Χ
 */
cp mul_I(cp a, cp b)
{
	cp com;
	com._Val[0] = a._Val[0] * b._Val[0] - a._Val[1] * b._Val[1];
	com._Val[1] = a._Val[1] * b._Val[0] + a._Val[0] * b._Val[1];
	return com;
}
/* ��������
 * @����  ���ú������������й�������
 * @����1 ����Ҫ����Ĳ���a
 * @����ֵ��a�Ĺ����
 * @ע��  ����Ҫע������������Լ���Ӧ�ķ�Χ
 */
cp con_I(cp a)
{
	cp com;
	com._Val[0] = a._Val[0];
	com._Val[1] = -a._Val[1];
	return com;
}
/* �����η�
 * @����  ���ú������������дη�����
 * @����1 ������a
 * @����2 ������b
 * @����ֵ��a��b�η�
 * @ע��  ����Ҫע������������Լ���Ӧ�ķ�Χ
 */
cp pow_I(cp a, int b)
{
	cp temp = a;
	cp ii;
	ii._Val[0] = 1, ii._Val[1] = 0;
	if (b != 1)
		for (int i = 0;i < b - 1;i++)
		{
			a = mul_I(a, temp);
		}
	else if (b == 0)
		return ii;
	return a;
}
/* ��ʼ����ת����Wn
 * @����  ���ú�������ת����Wn��ʼ��
 * @����1 ����Ҫ����fft��λ��N
 * @����ֵ���޷���ֵ
 * @ע��  ����Ҫע������������Լ���Ӧ�ķ�Χ
 */
void fft_init()
{
	cp ii;
	cp Wn;
	ii._Val[0] = 0, ii._Val[1] = 1;
	Wn = add_I(double2cp(cos(-2 * pi / (double)N)), mul_I(ii, double2cp(sin(-2 * pi / (double)N))));
	for (int i = 0; i < N; i++)
	{
		W_N[i] = pow_I(Wn, i);
	}
}
/* fft����
 * @����  ���ú����������NλԪ�ؽ���fft�任
 * @����1 �����ձ任��Ԫ�ص�����
 * @����2 ����Ҫ����fft��NλԪ��
 * @����ֵ������Nλ����fft�������Ԫ��
 * @ע��  ����Ҫע�������λ��N
 */
void fft(cp *X, double *x)
{
	int L;
	/*��ʼ����FFT�㷨*/
	//��ʼ�����ݣ�������һ��ԭʼ���ݵ�x0
	for (int i = 0;i < N;i++)
	{
		xL[0][i]._Val[0] = x[i];
	}
	/*�������㣬�˴�Ϊ�����㷨*/
	for (L = 1;L <= r;L++)
	{
		/*��L�ε�������*/
		int N_two_L = N / (2 << (L - 1)), r_L = r - L;//���ｫN/(pow(2, L))���һ����ʱ�ĳ����������������
		int K_L = 0;//�±���Ʊ���
		int _K_L = K_L + N_two_L;//���Ե��±�
		int L_2 = L % 2;
		for (;K_L < N; )
		{
			//numberΪ�����ԡ�����
			for (int number = 0;number < N_two_L;number++)
			{
				_K_L = K_L + N_two_L;
				xL[L_2][K_L] = add_I(xL[!L_2][K_L], mul_I(xL[!L_2][_K_L], W_N[BR(K_L >> r_L, r)]));
				xL[L_2][_K_L] = sub_I(xL[!L_2][K_L], mul_I(xL[!L_2][_K_L], W_N[BR(K_L >> r_L, r)]));
				K_L++;
			}
			K_L += N_two_L;
		}
	}
	for (int i = 0;i < N;i++)//����
	{
		//X[i] = xL[r - 1][i];//��ԭʼ���ݸ���
		X[BR(i, r)] = xL[L % 2][i];//����
	}
}

/* ������ʾ
 * @����  ���ú��������ӡ������
 * @����1 ������a
 * @����ֵ���޷���ֵ
 * @ע��  ��ֻ�ܵ��������һ�����������ж�������Ŷ
 */
void printf_I(_C_double_complex a)
{
	if (a._Val[1] < 0)
		printf("%f%f", a._Val[0], a._Val[1]);
	else
		printf("%f+%f", a._Val[0], a._Val[1]);
}