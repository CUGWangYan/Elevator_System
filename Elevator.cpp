#include "Elevator.h"
#include <iostream>
void Elevator::GoIn(int n) {
	this->m_Number += n;
}
void Elevator::GoOut(int n) {
	this->m_Number -= n;
}
void Elevator::GoUp() {
	std::cout << "��ǰ����λ�ڵ�" << m_Floor << "�㣡��" << std::endl;
	this->m_Floor++;

}
void Elevator::GoDown() {
	std::cout << "��ǰ����λ�ڵ�" << m_Floor << "�㣡��" << std::endl;
	this->m_Floor--;

}
condition Elevator::getCondition() {
	return m_Status;
}
void Elevator::setCondition(condition con) {
	this->m_Status = con;
}
int Elevator::getfloor() {
	return m_Floor;
}
int Elevator::getNumber() {
	return m_Number;
}
bool Elevator::IsFull() {
	if (m_Number <= MaxNumber) return false;
	else return true;
}