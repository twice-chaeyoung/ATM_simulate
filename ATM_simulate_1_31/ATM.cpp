#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ATM_head.h"
const int MIN_PER_HR = 60;
Item temp;
int number_of_ATM = 0;
long customers = 0;
int cycle = 0;   //ʱ������

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

	cout << "������ATM��������:";
	while (cin >> number_of_ATM) {
		cout << "��������е����������";
		int qs;
		cin >> qs;
		Queue * line = new Queue[number_of_ATM];   //�������飨����new������

		cout << "�����������ʱ����";
		int hours;
		cin >> hours;
		long cyclelimit = MIN_PER_HR * hours;

		cout << "������ÿСʱATM����ƽ������������";
		double perhour;
		cin >> perhour;
		double min_per_cust;
		min_per_cust = MIN_PER_HR / perhour;

		customers = 0;
		long turnaways = 0;
		long served = 0;
		long sum_line = 0;
		long line_wait = 0;
		int * wait_time = new int[number_of_ATM];    //�ȴ�ʱ�����飨����new������
		
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
					wait_time[i] = temp.ptime();   //����ʱ��
					line_wait += cycle - temp.when();    //�������ʱ���ȥ������е�ʱ��
					served++;
				}
				if (wait_time[i] > 0)
					wait_time[i]--;
				sum_line += line[i].queuecount();
			}
		}

		if (customers > 0) {
			cout << "������������" << customers << endl;
			cout << "������������" << served << endl;
			cout << "��ֹ����������" << turnaways << endl;
			cout.precision(2);
			cout.setf(ios_base::fixed, ios_base::floatfield);
			cout << "ƽ��ÿ̨ATM��ǰ���г��ȣ�" << (double)sum_line / cyclelimit / number_of_ATM << endl;
			cout << "ƽ���ȴ�ʱ�䣺" << (double)line_wait / served << endl;
		}
		else
			cout << "���˷��ʣ�" << endl;
		delete[] wait_time;
		delete[] line;
		cout << endl;
		cout << "������ATM��������:";
	}

	cout << "���Խ�����" << endl;
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