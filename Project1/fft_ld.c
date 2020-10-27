/*
 * fft_ld.c
 *
 */

#include "fft_ld.h"

/*----------------------全局变量定义-------------------------*/

cp W_N[N];
cp xL[2][N];

/*----------------------以下是函数定义-------------------------*/

/* 反转函数
 * @功能  ：该函数将数字的二进制以_r位反转
 * @参数1 ：需要被反转的数字a
 * @参数2 ：以_r位为基础进行翻转
 * @返回值：参数a以_r位为基础进行翻转的结果
 * @注意  ：需要注意参数的类型以及对应的范围
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
/* double转cp
 * @功能  ： 该函数将double类型转为虚部为0的复数
 * @参数1 ：需要被转换的数字a
 * @返回值：参数a转化的结果
 * @注意  ：需要注意参数的类型以及对应的范围
 */
cp double2cp(double a)
{
	cp com;
	com._Val[0] = a;
	com._Val[1] = 0;
	return com;
}
/* 复数加法
 * @功能  ：该函数将两个复数相加
 * @参数1 ：加数a
 * @参数2 ：加数b
 * @返回值：a和b的和数
 * @注意  ：需要注意参数的类型以及对应的范围
 */
cp add_I(cp a, cp b)
{
	cp com;
	com._Val[0] = a._Val[0] + b._Val[0];
	com._Val[1] = a._Val[1] + b._Val[1];
	return com;
}
/* 复数减法
 * @功能  ：该函数将两个复数相减
 * @参数1 ：被减数a
 * @参数2 ：减数b
 * @返回值：a和b的差
 * @注意  ：需要注意参数的类型以及对应的范围
 */
cp sub_I(cp a, cp b)
{
	cp com;
	com._Val[0] = a._Val[0] - b._Val[0];
	com._Val[1] = a._Val[1] - b._Val[1];
	return com;
}
/* 复数乘法
 * @功能  ：该函数将两个复数相乘
 * @参数1 ：乘数a
 * @参数2 ：乘数b
 * @返回值：a和b的和积
 * @注意  ：需要注意参数的类型以及对应的范围
 */
cp mul_I(cp a, cp b)
{
	cp com;
	com._Val[0] = a._Val[0] * b._Val[0] - a._Val[1] * b._Val[1];
	com._Val[1] = a._Val[1] * b._Val[0] + a._Val[0] * b._Val[1];
	return com;
}
/* 复数共轭
 * @功能  ：该函数将复数进行共轭运算
 * @参数1 ：需要共轭的参数a
 * @返回值：a的共轭复数
 * @注意  ：需要注意参数的类型以及对应的范围
 */
cp con_I(cp a)
{
	cp com;
	com._Val[0] = a._Val[0];
	com._Val[1] = -a._Val[1];
	return com;
}
/* 复数次方
 * @功能  ：该函数将复数进行次方运算
 * @参数1 ：复数a
 * @参数2 ：次数b
 * @返回值：a的b次方
 * @注意  ：需要注意参数的类型以及对应的范围
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
/* 初始化旋转因子Wn
 * @功能  ：该函数将旋转因子Wn初始化
 * @参数1 ：需要进行fft的位数N
 * @返回值：无返回值
 * @注意  ：需要注意参数的类型以及对应的范围
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
/* fft运算
 * @功能  ：该函数将输入的N位元素进行fft变换
 * @参数1 ：接收变换后元素的数组
 * @参数2 ：需要进行fft的N位元素
 * @返回值：返回N位经过fft处理后的元素
 * @注意  ：需要注意参数的位数N
 */
void fft(cp *X, double *x)
{
	int L;
	/*开始进行FFT算法*/
	//初始化数据，即复制一份原始数据到x0
	for (int i = 0;i < N;i++)
	{
		xL[0][i]._Val[0] = x[i];
	}
	/*迭代计算，此处为核心算法*/
	for (L = 1;L <= r;L++)
	{
		/*第L次迭代计算*/
		int N_two_L = N / (2 << (L - 1)), r_L = r - L;//这里将N/(pow(2, L))变成一个暂时的常量，避免冗余计算
		int K_L = 0;//下标控制变量
		int _K_L = K_L + N_two_L;//结点对的下标
		int L_2 = L % 2;
		for (;K_L < N; )
		{
			//number为“结点对”个数
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
	for (int i = 0;i < N;i++)//整序
	{
		//X[i] = xL[r - 1][i];//将原始数据复制
		X[BR(i, r)] = xL[L % 2][i];//整序
	}
}

/* 复数显示
 * @功能  ：该函数方便打印出复数
 * @参数1 ：复数a
 * @返回值：无返回值
 * @注意  ：只能单纯的输出一个复数，换行都不带的哦
 */
void printf_I(_C_double_complex a)
{
	if (a._Val[1] < 0)
		printf("%f%f", a._Val[0], a._Val[1]);
	else
		printf("%f+%f", a._Val[0], a._Val[1]);
}