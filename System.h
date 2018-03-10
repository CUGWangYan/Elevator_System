#pragma once
#include "List.h"
#include "Person.h"
#include "Elevator.h"
const int t = 30;//单位时间
const int testTime = 40 * t;
const int openDoor = 20 * t;
const int closeDoor = 20 * t;
const int InorOutTime = 25 * t;
const int Accelerate = 15 * t;
const int WaitTime = 300 * t;
const int GoUpTime = 51 * t;
const int GoDownTime = 61 * t;
const int UpDecelerate = 14 * t;
const int DownDecelerate = 23 * t;
class System {
	List<Person> OutList;//电梯外面人的链表
	List<Person> InList;//电梯里面的人的链表
	Elevator ele;
public:
	void Initialize();//初始化函数
	bool StandBy();//等候命令的函数
	void SetDirection(int floor);
	bool GoIn();
	bool GoOut(); //仅判断是个有人在当前楼层出去
	void Out(); //真的将能出去的人在链表中删除
	void In(); //真的将能进去的人在链表中删除
	bool Arrive();
	void GoUp();
	void GoDown();
	void OpenDoor();
	void Run(); //电梯调度运行函数
	void BeyondToleration();
};