#pragma once
const  int MaxNumber = 13;
enum condition {Opening, Opened, Closing, Closed, Waiting, Up, Down,Decelerate};
class Elevator {
	int m_Floor;//电梯所在层
	int m_Number;//载重人数
	condition m_Status;
public:
	~Elevator() {}
	Elevator(int floor=1,int number=0,condition con=Waiting):m_Floor(floor),m_Number(number), m_Status(con){}
	Elevator(const Elevator&elevator) = delete;
	void GoIn(int n);
	void GoOut(int n);
	void GoUp();
	void GoDown();
	condition getCondition();
	void setCondition(condition con);
	int getfloor();
	int getNumber();
	bool IsFull();
};