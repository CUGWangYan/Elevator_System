#pragma once
#include "List.h"
#include "Person.h"
#include "Elevator.h"
const int t = 30;//��λʱ��
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
	List<Person> OutList;//���������˵�����
	List<Person> InList;//����������˵�����
	Elevator ele;
public:
	void Initialize();//��ʼ������
	bool StandBy();//�Ⱥ�����ĺ���
	void SetDirection(int floor);
	bool GoIn();
	bool GoOut(); //���ж��Ǹ������ڵ�ǰ¥���ȥ
	void Out(); //��Ľ��ܳ�ȥ������������ɾ��
	void In(); //��Ľ��ܽ�ȥ������������ɾ��
	bool Arrive();
	void GoUp();
	void GoDown();
	void OpenDoor();
	void Run(); //���ݵ������к���
	void BeyondToleration();
};