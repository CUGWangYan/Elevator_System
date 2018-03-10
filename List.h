#pragma once
#include <iostream>
#include <assert.h>
#include <string>
using namespace std;
template <class T>
struct Node {
	Node<T>* link;
	T m_data;

	Node(const T&x) :m_data(x), link(nullptr) {}
};
template<class T>
class List {
	Node<T>* m_head;
public:
	List() :m_head(nullptr){}
	List(const List<T>&s){
		if (s.m_head == nullptr) return;
		else {
			Node<T>*cur(s.m_head);
			while (cur) {
				PushBack(cur->m_data);
				cur = cur->link;
			}
		}
	}
	~List() { clear(); }
	void clear() {
		Node<T> *cur = m_head;
		while (cur) {
			Node<T>*next = cur->link;
			delete cur;
			cur = next;
		}
		m_head =  nullptr;
	}
	bool IsEmpty() {
		if (this->m_head==nullptr)
			return true;
		else return false;
	}
	bool IsFull() {
		return false;
	}
	void Display() {
		Node<T>*cur = m_head;
		while (cur) {
			cout << cur->m_data << "  ";
				cur = cur->link;
		}
		cout << endl;
	}
	int Size() {
		int count = 0;
		Node<T>*cur = m_head;
		while (cur) {
			count++;
			cur = cur->link;
		}
		return count;
	}
	void PushBack(const T&x) {
		if (m_head == nullptr) { m_head = new Node<T>(x); }
		else {
			Node<T>*cur=m_head;
			while (cur->link != nullptr) cur = cur->link;
			Node<T>*temp = new Node<T>(x);
			cur->link = temp;
		}
	}
	Node<T>* Find(T x) {
		if (m_head == nullptr)return nullptr;
		else {
			Node<T>*cur(m_head);
			while (cur != nullptr) {
				if (cur->m_data == x) {
					break;
				}
				cur = cur->link;
			}
			return cur;
		}
	}
	void Insert(Node<T>*pos, T x) {
		assert(pos);
		if (pos == m_head) {
			PushFront(x);
		}
		else {
			Node<T>*temp = new Node<T>(x);
			Node<T>*cur = m_head;
			while (cur->link != pos) { cur = cur->link; }
			temp->link = pos;
			cur->link = temp;
		}
	}
	void Destroy() {
		if (m_head == nullptr) { m_head = nullptr; }
		else {
			Node<T>* cur(m_head);
			while (cur != nullptr) {
				cur = cur->link;
				delete m_head;
				m_head = cur;
			}
			m_head = nullptr;
		}
	}
	void Erase(Node<T>*pos) {
		assert(pos);
		if (pos == m_head) {
			m_head = m_head->link;
			delete pos;
		}
		else {
			Node<T>*cur(m_head);
			while (cur->link != pos) {
				cur = cur->link;
			}
			cur->link = pos->link;
			delete pos;
			pos = nullptr;
		}
	}
	void Erase(int i) {//////////下标从1开始??
		Node<T>*del, *cur;
		if (i <= 1) { del = m_head; m_head = m_head->link; }
		else {
			cur = m_head;
			for (int k = 1; k < i - 1; k++) {
				if (cur == nullptr) break;
				else cur = cur->link;
			}
			if (cur == nullptr || cur->link == nullptr) return;
			del = cur->link;
			cur->link = del->link;
		}
		delete del;
		return;
	}
	T GetData(int i) {
		Node<T>*cur = m_head;
		for (int k = 1; k < i; k++) {
			cur = cur->link;
		}
		return cur->m_data;
	}
};