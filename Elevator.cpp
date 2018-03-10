#include "Elevator.h"
#include <iostream>
void Elevator::GoIn(int n) {
	this->m_Number += n;
}
void Elevator::GoOut(int n) {
	this->m_Number -= n;
}
void Elevator::GoUp() {
	std::cout << "当前电梯位于第" << m_Floor << "层！！" << std::endl;
	this->m_Floor++;

}
void Elevator::GoDown() {
	std::cout << "当前电梯位于第" << m_Floor << "层！！" << std::endl;
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