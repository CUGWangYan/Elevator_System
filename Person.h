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
		out << "id" << per.m_id << "����¥��:  " << per.m_StartFloor << "   Ŀ��¥��:  " << per.m_EndFloor << "   ���ȴ�ʱ��" << per.m_maxWaitTime << "   ��ʼ�ȴ�ʱ����" << difftime(per.m_StartTime,StartTime) << "���Ժ�" << endl;
		return out;
	}
};


