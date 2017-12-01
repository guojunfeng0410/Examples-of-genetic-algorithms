/*
	inspired by sjyan:https://www.zhihu.com/question/23293449
*/
#include "stdafx.h"
#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;
class Individual
{
public:
	int chromosome;
	double fit;

};
bool comp(Individual a, Individual b);
int decide_chromosome_size(double num);
void crossover(int a, int b, int &c, int &d,int len,double mutate_rate);
void mutate(int &a, const int chromosome_size, const double mutate_rate);
double get_fit(double chromosome, const int chromosome_size, const double bound[]);
int main()
{
	const double bound[2] = { 0.0,9.0},cross_rate=0.6, mutate_rate=1;
	const int N = 100,//种群大小
		iteration=10,//种族代数
		accuracy=4;//解的精度为小数点后几位
	int chromosome_size=decide_chromosome_size((bound[1]-bound[0])*pow(10,accuracy));
	Individual individual[N];
	//初始化种群
	for (int i = 0; i < N;)
	{
		individual[i].chromosome = (rand() << 2 % ((int)pow(2, chromosome_size) + 1));//随机化二进制编码
		individual[i].fit = get_fit(individual[i].chromosome, chromosome_size,bound);
		if (individual[i].fit < 10) i++;
	}
	sort(individual, individual + N, comp);
	cout << " " << individual[0].chromosome << " " << individual[0].fit << endl;
	for(int i=0; i<iteration;i++)
	{
		//if(i%1000==0)
		//cout << i << " " << individual[0].chromosome << " " << individual[0].fit << endl;
		//for (int j = 0; j < N;j++)cout << i << " " << individual[j].chromosome << " " << individual[j].fit << endl;
		int start = 0, end = N - 1, mid = N >> 1;
		for (; start <= end; start++)
		{
			if (rand() % 100 > cross_rate * 100) continue;
			int other = rand() % N;
			while (other == start||other > end) other = rand() % N;;
			crossover(individual[start].chromosome, individual[other].chromosome,
				individual[end].chromosome, individual[end - 1].chromosome, 
				chromosome_size,mutate_rate);
			end -= 2;
		}
		for (; end < N; end++) individual[end].fit = get_fit(individual[end].chromosome, chromosome_size, bound);
		sort(individual, individual + N, comp);
	}
	cout << " " << individual[0].chromosome << " " << individual[0].fit << endl;
	int a;
	cin >> a;
    return 0;
}
int decide_chromosome_size(double num)
{
	int size = 1;
	int a=2, b=((int) num)+1;
	while (a < b)
	{
		a=a << 1;
		size++;
	}
	return size;
}
double get_fit(double chromosome, const int chromosome_size, const double bound[])
{
	double x = chromosome / pow(2, chromosome_size)*(bound[1] - bound[0]);
	double y =x + 10 * sin(5 * x) + 7 * cos(4 * x);
	return y;
}
bool comp(Individual a, Individual b)
{
	return a.fit > b.fit;
}
void crossover(int a, int b,int &e,int &f, int len,double mutate_rate)
{
	int d =0, c = 0;
	int position = rand() % (len-2) + 1;
	for (int i =len; i >= 0; --i)
	{
		//if (i>= 5&& i<=8 || i >= 13 && i <= 16) {
		if(i<position)
		{
			if ((a >> i) & 1)
				c += 1 << i;
			if ((b >> i) & 1)
				d += 1 << i;
		}
		else
		{
			if ((b >> i) & 1)
				c += 1 << i;
			if ((a >> i) & 1)
				d += 1 << i;
		}
	}
	//cout << a << " " << b << " " << c << " " << d;
	mutate(c, len, mutate_rate);
	mutate(d, len, mutate_rate);
	//cout << " "<<c << " " << d << endl;
	e = c; f = d;
	
}
void mutate(int &a,const int chromosome_size,const double mutate_rate)
{
	int rate = mutate_rate * 100;
	if(rand()%100<rate)
	{
		int position = rand() % chromosome_size;
		if (a >> position & 1)
		{
			a -= 1 << position;
		}
		else a += 1 << position;
	}
	
}