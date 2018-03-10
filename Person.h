#pragma once
#include <iostream>
#include <Windows.h>
#include <time.h>
using namespace std;
extern time_t StartTime;
class Person {
	int m_id;
	int m_StartFloor;
	int m_EndFloor;
	int m_maxWaitTime;
	time_t m_StartTime;
public:
	inline int getId() {
		return m_id;
	}
	inline int getStartFloor() {
		return m_StartFloor;
	}
	inline int getEndFloor() {
		return m_EndFloor;
	}
	inline int getMaxTime() {
		return m_maxWaitTime;
	}
	inline time_t getStartTime() {
		return m_StartTime;
	}
	~Person() {}
	Person(int id,int startFloor,int endFloor,int maxWaitTime,time_t Starttime) :m_id(id),m_StartFloor(startFloor),m_EndFloor(endFloor), m_maxWaitTime(maxWaitTime),m_StartTime(Starttime) {}
	Person() {}
	Person(const Person&per) {
		this->m_id = per.m_id;
		this->m_maxWaitTime = per.m_maxWaitTime;
		this->m_EndFloor = per.m_EndFloor;
		this->m_StartFloor = per.m_StartFloor;
		this->m_StartTime = per.m_StartTime;
	}
	friend ostream& operator<<(ostream&out,const Person& per) {
		out << "id" << per.m_id << "所在楼层:  " << per.m_StartFloor << "   目标楼层:  " << per.m_EndFloor << "   最大等待时间" << per.m_maxWaitTime << "   开始等待时间在" << difftime(per.m_StartTime,StartTime) << "秒以后" << endl;
		return out;
	}
};


