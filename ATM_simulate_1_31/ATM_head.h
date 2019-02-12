#pragma once
class Customer
{
	long arrive;
	int processtime;
public:
	Customer() { arrive = processtime = 0; }
	void set(long when);
	long when() const { return arrive; }
	int ptime() const { return processtime; }
};

typedef Customer Item;

class Queue
{
	struct Node { Item item; struct Node * next; };
	enum { Q_SIZE = 10 };
	Node * front;   //指向最前一个节点
	Node * rear;   //指向当前节点
	int items;    //队列中的节点数量
	const int qsize;   //队列的最大节点数量
	Queue(const Queue & q) : qsize(0) { };   //封闭复制接口
	Queue & operator= (const Queue & q) { return *this; }   //封闭赋值接口
public:
	Queue(int qs = Q_SIZE);
	~Queue();
	bool isempty() const;
	bool isfull() const;
	int queuecount() const;
	bool enqueue(const Item & item);   //进队
	bool dequeue(Item & item);   //出队
};
