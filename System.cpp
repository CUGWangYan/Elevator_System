#include "System.h"
#include <Windows.h>
#include <iostream>
#include <conio.h>
using namespace std;
time_t StartTime;//定义系统开始时间
time_t Now;//系统当前时间
int Wait = 0;//电梯处于等待状态的时间
void System::Initialize() {//初始化函数
	time(&StartTime);
	srand((unsigned)time(NULL));//随机种子
	time(&StartTime);
}
bool System::StandBy() {//等候命令的函数
	if (_kbhit()) {
		char a=getchar();
		getchar();
		int n = int(a - '0');
		cout << "生成了"<<n<<"个人" << endl;
		static int No = 1;
		for (int i = 0; i < n; i++, No++) {
		int startFloor = rand() % 9 + 1;
		int endFloor = rand() % 9 + 1;
		int waitTime = rand() % 60 + 30;
		time(&Now);
		Person per(No, startFloor, endFloor, waitTime, Now);
		OutList.PushBack(per);
		}
		OutList.Display();
		}
	BeyondToleration();//每秒钟检查是否有人等不及了
	Sleep(1000);//设置每一秒钟检查请求一次
	if (ele.getCondition() == Waiting) { Wait++; }
	if (ele.getCondition() == Waiting&&OutList.IsEmpty() == true && InList.IsEmpty() == true) {
		if (Wait > 30)
		{
			cout << "处于等待阶段时间大于30秒回到一楼" << endl;
			//SetDirection(1);//因为电梯里外都没人函数没有停止条件所以不能调用
			while (ele.getfloor() != 1) {
				ele.setCondition(Down);
				ele.GoDown();
				//	cout << difftime(Now, StartTime) << endl;
				cout << "电梯正在下行..." << endl;
				Sleep(GoDownTime);
			}
			cout << "电梯到达本垒层Over" << endl;
			return true;
		}
		else StandBy();
	}
	else {
		Wait = 0;
		Run();
		StandBy();
	}
	return false;
}
void System::SetDirection(int floor) {
	BeyondToleration();
	if (floor > ele.getfloor()) {
		ele.setCondition(Up);
		time(&Now);
		cout << "第" << difftime(Now, StartTime) << "秒电梯开始向上加速" << endl;
		while (ele.getfloor() != floor) {
			ele.GoUp();
			Sleep(GoUpTime);
			time(&Now);
			cout << "第" << difftime(Now, StartTime) << "秒电梯正在上行..." << endl;
		}
		Arrive();
		Sleep(Accelerate);
		return;
	}
	else if (floor < ele.getfloor()) {
		ele.setCondition(Down);
		time(&Now);
		cout << "第" << difftime(Now, StartTime) << "秒电梯开始向下加速" << endl;
		while (ele.getfloor() != floor) {
			ele.GoDown();
			Sleep(GoDownTime);
			time(&Now);
			cout << "第" << difftime(Now, StartTime) << "秒电梯正在下行..." << endl;
		}
		Arrive();
		Sleep(Accelerate);
		return;
	}
	else if (floor == ele.getfloor()) {//缺了arrive（）
		ele.setCondition(Waiting);
		if (GoIn() == true && ele.IsFull() == false)
			In();
		if (GoOut() == true)
			Out();
		if (ele.IsFull() == true) {
			cout << "电梯人满了" << endl;
		}
		return;
	}
}
bool System::GoIn() {
	if (ele.IsFull() == false) {
		if (OutList.IsEmpty() != true) {
			time(&Now);
			for (int i = 0; i < OutList.Size(); i++) {
				if (OutList.GetData(i + 1).getStartTime() > Now) continue;
				else if (OutList.GetData(i + 1).getStartFloor() == ele.getfloor())
					return true;
			}
		}
	}
	return false;
}
bool System::GoOut() {//仅判断是个有人在当前楼层出去
	if (InList.IsEmpty() == false)
		for (int i = 0; i < InList.Size(); i++) {
			if (InList.GetData(i + 1).getEndFloor() == ele.getfloor())
				return true;
		}
	return false;
}
void System::Out() {//真的将能出去的人在链表中删除
	int count = 0;
	condition temp = ele.getCondition();
	for (int i = 0; i < InList.Size(); i++) {
		if (InList.GetData(i + 1).getEndFloor() == ele.getfloor()) {
			InList.Erase(i + 1);
			i--;
			count++;
		}
	}
	ele.setCondition(Opening);
	ele.setCondition(Opened);
	Sleep(InorOutTime*count);
	time(&Now);
	if (count != 0) cout << "第" << difftime(Now, StartTime) << "秒" << count << "名乘客正在出电梯门...." << endl;
	ele.GoOut(count);
	ele.setCondition(Closing);
	ele.setCondition(Closed);
	ele.setCondition(temp);
}
void System::In() {//真的将能进去的人在链表中删除
	if (ele.IsFull() == true) return;
	int count = 0;
	condition temp = ele.getCondition();
	for (int i = 0; i < OutList.Size(); i++) {
		if (OutList.GetData(i + 1).getStartTime() > Now) continue;
		else if (OutList.GetData(i + 1).getStartFloor() == ele.getfloor()) {
			InList.PushBack(OutList.GetData((i + 1)));
			OutList.Erase(i + 1);
			i--;
			count++;
			if (count == 13) {
				cout << "电梯超载" << endl;
				break;
			}
		}
	}
	ele.setCondition(Opening);
	ele.setCondition(Opened);
	Sleep(InorOutTime*count);
	time(&Now);
	ele.setCondition(Closing);
	ele.setCondition(Closed);
	ele.setCondition(temp);
	ele.GoIn(count);
	if (count != 0) cout << "第" << difftime(Now, StartTime) << "秒" << count << "名乘客正在进入电梯门...." << endl;
}
bool System::Arrive() {
	BeyondToleration();
	if (GoIn() == true || GoOut() == true) {
		condition temp = ele.getCondition();
		if (ele.getCondition() == Up) {
			Sleep(UpDecelerate);
			time(&Now);
			cout << "第" << difftime(Now, StartTime) << "秒电梯正在向上减速" << endl;
		}
		if (ele.getCondition() == Down) {
			Sleep(DownDecelerate);
			time(&Now);
			cout << "第" << difftime(Now, StartTime) << "秒电梯正在向下减速" << endl;
		}
		cout << "电梯到达目标楼层:" << ele.getfloor() << endl;
		ele.setCondition(Opening);
		cout << "正在开门..." << endl;
		ele.setCondition(Opened);
		if (GoIn() == true && ele.IsFull() == false)
			In();
		if (GoOut() == true)
			Out();
		ele.setCondition(Closing);
		ele.setCondition(Closed);
		Sleep(closeDoor);
		ele.setCondition(temp);
		time(&Now);
		cout << "第" << difftime(Now, StartTime) << "秒正在关门..." << endl;
		return true;
	}
	else return false;
}
void System::Run() {//电梯调度运行函数
	int near0;
	int near1;
	int near2;
	if (ele.IsFull() == true) {
		int flag;
		int min = 9;
		int NearIn = 12;
		if (InList.IsEmpty() != true) {
			for (int i = 0; i < InList.Size(); i++) {
				flag = abs(InList.GetData(i + 1).getEndFloor() - ele.getfloor());
				if (flag <= min) {
					min = flag;
					NearIn = InList.GetData(i + 1).getEndFloor();
				}
			}
		}
		SetDirection(NearIn);
	}
	if (ele.getCondition() == Closed) {
		if (OutList.IsEmpty() == true && InList.IsEmpty() == true)
			ele.setCondition(Waiting);
		return;
	}
	if (ele.getCondition() == Waiting) {
		int flag;
		int min = 9;
		int NearIn = 12;
		int NearOut = 12;
		if (InList.IsEmpty() != true) {
			for (int i = 0; i < InList.Size(); i++) {
				flag = abs(InList.GetData(i + 1).getEndFloor() - ele.getfloor());
				if (flag <= min) {
					min = flag;
					NearIn = InList.GetData(i + 1).getEndFloor();
				}
			}
		}
		if (OutList.IsEmpty() != true) {
			for (int i = 0; i < OutList.Size(); i++) {
				if (OutList.GetData(i + 1).getStartTime() > Now) continue;
				flag = abs(OutList.GetData(i + 1).getStartFloor() - ele.getfloor());
				if (flag <= min) {
					min = flag;
					NearOut = OutList.GetData(i + 1).getStartFloor();
				}
			}
		}
		near0 = NearOut > NearIn ? NearIn : NearOut;
		if (near0 == 12) {
			ele.setCondition(Waiting);
			near0 = ele.getfloor();
		}
		SetDirection(near0);
	}
	if (ele.getCondition() == Up) {
		int flag;
		int min = 9;
		int UpNearIn = 12;
		int UpNearOut = 12;
		if (InList.IsEmpty() != true) {
			for (int i = 0; i < InList.Size(); i++) {
				flag = InList.GetData(i + 1).getEndFloor() - ele.getfloor();
				if (flag <= min&&flag > 0) {
					min = flag;
					UpNearIn = InList.GetData(i + 1).getEndFloor();
				}
			}
		}
		if (OutList.IsEmpty() != true) {
			for (int i = 0; i < OutList.Size(); i++) {
				if (OutList.GetData(i + 1).getStartTime() > Now) continue;
				flag = OutList.GetData(i + 1).getStartFloor() - ele.getfloor();
				if (flag <= min&&flag >= 0) {
					min = flag;
					UpNearOut = OutList.GetData(i + 1).getStartFloor();
				}
			}
		}
		near1 = UpNearOut > UpNearIn ? UpNearIn : UpNearOut;
		if (near1 == 12) {
			ele.setCondition(Down);
			near1 = ele.getfloor();
		}
		SetDirection(near1);
	}
	else if (ele.getCondition() == Down) {
		int flag;
		int min = 9;
		int DownNearIn = 12;
		int DownNearOut = 12;
		if (InList.IsEmpty() != true) {
			for (int i = 0; i < InList.Size(); i++) {
				flag = ele.getfloor() - InList.GetData(i + 1).getEndFloor();
				if (flag <= min&&flag >= 0) {
					min = flag;
					DownNearIn = InList.GetData(i + 1).getEndFloor();
				}
			}
		}
		if (OutList.IsEmpty() != true) {
			for (int i = 0; i < OutList.Size(); i++) {
				if (OutList.GetData(i + 1).getStartTime() > Now) continue;
				flag = ele.getfloor() - OutList.GetData(i + 1).getStartFloor();
				if (flag <= min&&flag >= 0) {
					min = flag;
					DownNearOut = OutList.GetData(i + 1).getStartFloor();
				}
			}
		}
		near2 = DownNearOut > DownNearIn ? DownNearIn : DownNearOut;
		if (near2 == 12) {
			ele.setCondition(Up);
			near1 = ele.getfloor();
		}
		SetDirection(near2);
	}
}
void System::BeyondToleration() {
	time(&Now);
	double flag = difftime(Now, StartTime);
	if (OutList.IsEmpty() != true) {
		for (int i = 0; i < OutList.Size(); i++) {
			if (OutList.GetData(i + 1).getStartTime() > Now) continue;
			else if (OutList.GetData(i + 1).getMaxTime() < flag - difftime(OutList.GetData(i + 1).getStartTime(), StartTime))
			{
				cout << "第" << OutList.GetData(i + 1).getId() << "人等不及离开了" << endl;
				OutList.Erase(i + 1);
				i--;
			}
		}
	}
}
