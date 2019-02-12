#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ATM_head.h"
const int MIN_PER_HR = 60;
Item temp;
int number_of_ATM = 0;
long customers = 0;
int cycle = 0;   //时间序列

bool newcustomer(double x);
bool all_line_full(const Queue * q);
void enqueue_of_ATM(Queue * q);

int main()
{
	using std::cin;
	using std::cout;
	using std::endl;
	using std::ios_base;
	std::srand(std::time(0));

	cout << "请输入ATM机的数量:";
	while (cin >> number_of_ATM) {
		cout << "请输入队列的最大容量：";
		int qs;
		cin >> qs;
		Queue * line = new Queue[number_of_ATM];   //队列数组（采用new建立）

		cout << "请输入测试总时长：";
		int hours;
		cin >> hours;
		long cyclelimit = MIN_PER_HR * hours;

		cout << "请输入每小时ATM机的平均访问人数：";
		double perhour;
		cin >> perhour;
		double min_per_cust;
		min_per_cust = MIN_PER_HR / perhour;

		customers = 0;
		long turnaways = 0;
		long served = 0;
		long sum_line = 0;
		long line_wait = 0;
		int * wait_time = new int[number_of_ATM];    //等待时间数组（采用new建立）
		
		for (cycle = 0; cycle < cyclelimit; cycle++) {
			if (newcustomer(min_per_cust)) {
				if (all_line_full(line))
					turnaways++;
				else {
					enqueue_of_ATM(line);
				}
			}
			for (int i = 0; i < number_of_ATM; i++) {
				if (wait_time[i] <= 0 && !line[i].isempty()) {
					line[i].dequeue(temp);
					wait_time[i] = temp.ptime();   //交易时间
					line_wait += cycle - temp.when();    //到达队首时间减去进入队列的时间
					served++;
				}
				if (wait_time[i] > 0)
					wait_time[i]--;
				sum_line += line[i].queuecount();
			}
		}

		if (customers > 0) {
			cout << "接收总人数：" << customers << endl;
			cout << "服务总人数：" << served << endl;
			cout << "禁止进入人数：" << turnaways << endl;
			cout.precision(2);
			cout.setf(ios_base::fixed, ios_base::floatfield);
			cout << "平均每台ATM机前队列长度：" << (double)sum_line / cyclelimit / number_of_ATM << endl;
			cout << "平均等待时间：" << (double)line_wait / served << endl;
		}
		else
			cout << "无人访问！" << endl;
		delete[] wait_time;
		delete[] line;
		cout << endl;
		cout << "请输入ATM机的数量:";
	}

	cout << "测试结束。" << endl;
	system("pause");
	return 0;
}

bool newcustomer(double x)
{
	return (std::rand() * x / RAND_MAX < 1);
}

bool all_line_full(const Queue * q)
{
	for (int i = 0; i < number_of_ATM; i++) {
		if (!q[i].isfull())
			return false;
	}
	return true;
}

void enqueue_of_ATM(Queue * q)
{
	int Qmin = 0;
	for (int i = 0; i < number_of_ATM - 1; i++) {
		if (q[i].queuecount() < q[i + 1].queuecount())
			Qmin = i;
	}
	customers++;
	temp.set(cycle);
	q[Qmin].enqueue(temp);
}