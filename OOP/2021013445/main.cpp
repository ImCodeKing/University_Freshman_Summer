/*************************************************************************
【文件名】main.hpp
【功能模块和目的】主函数及窗口函数
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【版权信息】以下代码来源于清华大学范静涛老师原码的修改和封装，
	开发者李昭阳(lizhaoya21@mails.tsinghua.edu.cn)声明放弃对修改部分的任何版权诉求，任何使用者可做出任何修改、用于任何目的
	原文遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明
	https://blog.csdn.net/oHanTanYanYing/article/details/31155985
	https://blog.csdn.net/oHanTanYanYing/article/details/29943973
	CC BY-SA 4.0 是一种许可协议，赋予遵守者两项重要权利：
	一、共享的权利。允许通过任何媒介和任何形式复制、发行作品。
	二、改编的权利。允许二次加工、转换和基于作品进行创作，不限制用途，甚至是商业应用。
【更改记录】
*************************************************************************/
#include <string>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <fstream>
#include <iostream>
#include "Participant.hpp"
#include "ControllerAbstractBase.hpp"
#include "DateTime.hpp"
#include "Tube.hpp"
using namespace std;
//-----------------------------------------------------------------------------

//各窗口函数的预先声明
string LoginMenu(ControllerAbstractBase& Controler);
string SelectIdentityMenu(ControllerAbstractBase& Controler);
string TrivalMenu(ControllerAbstractBase& Controler);
string AdminMenu(ControllerAbstractBase& Controler);
string CollectorMenu(ControllerAbstractBase& Controler);
string RecorderMenu(ControllerAbstractBase& Controler);
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】int main(int argc, char* argv[])
【函数功能】主函数
【参数】argc：提供给主函数的参数个数；argv：参数的字符串数组的指针
【返回值】整型
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
int main(int argc, char* argv[])
{
	ControllerAbstractBase Controler("Participant.txt", "Tube.txt");
	cout << LoginMenu(Controler) << endl;
	return 0;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】string LoginMenu(ControllerAbstractBase& Controler)
【函数功能】登录窗口函数，用于登录时的各类函数的调用
【参数】Controler：业务流程类对象，用于控制核心类
【返回值】字符串
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
string LoginMenu(ControllerAbstractBase& Controler)
{
	string IDNum;
	string Name;
	string Password;
	string Choice = "N";
	RES Res;
	//设置一个无限的循环
	bool InfiniteLoop = true;
	while (InfiniteLoop)
	{
		cout << "------Welcome to Negative is a positive result------" << endl;
		cout << "-----Login------" << endl;
		cout << "Are you a new user? (Y or N)" << endl;
		cin >> Choice;
		while (InfiniteLoop)
		{
			//如果是新用户
			if (Choice == "Y" || Choice == "y")
			{
				cout << "Please register first." << endl;
				cout << "ID Number: ";
				cin >> IDNum;
				cout << "Name: ";
				cin >> Name;
				cout << "Password: ";
				cin >> Password;
				Res = Controler.CreateNewParticipant(IDNum, Name, Password);
				//身份证号不合理（不是18位）
				if (Res == RES::INVALID_ID_NUMBER)
				{
					cout << "Please enter valid ID number." << endl;
					cout << "--------------------" << endl;
					continue;
				}
				//当发现输入的身份证号与一个已经存在的用户匹配时
				else if (Res == RES::IDNUMBER_EXISTED)
				{
					while (InfiniteLoop)
					{
						cout << "ID Number Existed. Login? (Y or N)" << endl;
						Choice.clear();
						cin >> Choice;
						//选择是yes
						if (Choice == "Y" || Choice == "y")
						{
							Res = Controler.Login(IDNum, Password);
							if (Res == RES::WRONG_PASSWORD)
							{
								cout << "Wrong Password. Login failed." << endl;
								break;
							}
							else
							{
								cout << SelectIdentityMenu(Controler) << endl;
								return "--------------------";
							}
						}
						//选择是no
						else if (Choice == "N" || Choice == "n")
						{
							return "Thank you for your use.";
						}
						//不符合规定的选择
						else
						{
							cout << "Unknown choice. Please enter Y or N." << endl;
							cin >> Choice;
						}
					}
				}
				//如果没有在列表中发现匹配的身份证号，则把新建的用户登录
				else
				{
					Res = Controler.Login(IDNum, Password);
					cout << "New participant created. Already login automaticly." << endl;
					cout << SelectIdentityMenu(Controler);
					return "--------------------";
				}
			}
			//如果不是新用户
			else if (Choice == "N" || Choice == "n")
			{
				break;
			}
			else
			{
				cout << "Unknown choice. Please enter Y or N." << endl;
				cin >> Choice;
			}
		}
		cout << "ID Number: ";
		cin >> IDNum;
		cout << "Password: ";
		cin >> Password;
		Res = Controler.Login(IDNum, Password);
		//错误密码
		if (Res == RES::WRONG_PASSWORD)
		{
			cout << "Wrong Password. Login failed." << endl;
			cout << "--------------------" << endl;
			continue;
		}
		//找不到所给定的用户
		else if (Res == RES::NO_USER)
		{
			cout << "No such user. Login failed." << endl;
			cout << "--------------------" << endl;
			continue;
		}
		//加载到选择身份菜单
		else
		{
			cout << SelectIdentityMenu(Controler);
			break;
		}
	}
	return " ";
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】string SelectIdentityMenu(ControllerAbstractBase& Controler)
【函数功能】选择身份窗口函数，用于选择身份时时的各类函数的调用
【参数】Controler：业务流程类对象，用于控制核心类
【返回值】字符串
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
string SelectIdentityMenu(ControllerAbstractBase& Controler)
{
	RES Res;
	bool InfiniteLoop = true;
	while (InfiniteLoop)
	{
		cout << "-----Select Your Identity------" << endl;
		//调用业务流程类挑选身份函数
		Res = Controler.SellectUserType();
		if (Res == RES::PARTICIPANT_LOGINED)
		{
			cout << "Participant Logined." << endl;
			cout << TrivalMenu(Controler);
			break;
		}
		else if (Res == RES::ADMIN_LOGINED)
		{
			cout << "Admin Logined." << endl;
			cout << AdminMenu(Controler);
			break;
		}
		else if (Res == RES::COLLECTOR_LOGINED)
		{
			cout << "Collector Logined." << endl;
			cout << CollectorMenu(Controler);
			break;
		}
		else if (Res == RES::RECORDER_LOGINED)
		{
			cout << "Recorder Logined." << endl;
			cout << RecorderMenu(Controler);
			break;
		}
		else
		{
			cout << "Wrong Idenity." << endl;
		}
	}
	return " ";
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】string TrivalMenu(ControllerAbstractBase& Controler)
【函数功能】普通被试者身份窗口函数，用于身份为普通被试者的各类函数的调用
【参数】Controler：业务流程类对象，用于控制核心类
【返回值】字符串
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
string TrivalMenu(ControllerAbstractBase& Controler)
{
	cout << "-----Participant Menu------" << endl;
	RES Res;
	bool InfiniteLoop = true;
	string Choice;
	string NewPassword;
	//自动展示核酸结果
	Res = Controler.ShowResult();
	if (Res == RES::NO_RECENT_RESULT)
	{
		cout << "No recent result." << endl;
	}
	cout << "--------------------" << endl;
	while (InfiniteLoop)
	{
		cout << "Please select your action." << endl;
		cout << "1. Change password" << endl;
		cout << "2. Delete my account" << endl;
		cout << "3. Change Identity" << endl;
		cout << "4. Log out" << endl;
		cout << "--------------------" << endl;
		cin >> Choice;
		if (Choice == "1")
		{
			cout << "-----Change Password------" << endl;
			cout << "Please insert your new password." << endl;
			cin >> NewPassword;
			cout << "--------------------" << endl;
			Res = Controler.ChangePassword(NewPassword);
			if (Res == RES::PASSWORD_CHANGED)
			{
				cout << "Password changed." << endl;
				cout << "--------------------" << endl;
			}
		}
		else if (Choice == "2")
		{
			cout << "-----Delete My Account------" << endl;
			cout << "Do you really want to delete your account? (Y or N)" << endl;
			cout << "--------------------" << endl;
			cin >> Choice;
			if (Choice == "Y" || Choice == "y")
			{
				try 
				{
					Res = Controler.DeleteMyParticipant();
				}
				catch (exception& e)
				{
					cout << "Error: " << e.what() << endl;
					cout << "--------------------" << endl;
				}
				if (Res == RES::USER_DELETED)
				{
					cout << "User deleted." << endl;
					cout << "--------------------" << endl;
					return "Thank you for your use.";
				}
			}
			else if (Choice == "N" || Choice == "n")
			{
				cout << "Delete action canceled." << endl;
			}
			else
			{
				cout << "Unknown choice. Automaticly canceled the delete action." << endl;
			}
		}
		else if (Choice == "3")
		{
			Res = Controler.ChangeIdentity();
			if (Res == RES::NO_MORE_IDENITY)
			{
				cout << "No more identity to choose." << endl;
				cout << "--------------------" << endl;
			}
			else
			{
				cout << SelectIdentityMenu(Controler);
				return " ";
			}
		}
		else if (Choice == "4")
		{
			break;
		}
		else
		{
			cout << "Unknown choice. Please insert 1, 2, 3 or 4." << endl;
		}
	}
	return "Thank you for your use.";
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】string AdminMenu(ControllerAbstractBase& Controler)
【函数功能】管理员身份窗口函数，用于身份为管理员的各类函数的调用
【参数】Controler：业务流程类对象，用于控制核心类
【返回值】字符串
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
string AdminMenu(ControllerAbstractBase& Controler)
{
	cout << "-----Admin Menu------" << endl;
	RES Res;
	bool InfiniteLoop = true;
	string Choice;
	string TheIDNum;
	while (InfiniteLoop)
	{
		cout << "Please select your action." << endl;
		cout << "1. Add Collector" << endl;
		cout << "2. Add Recorder" << endl;
		cout << "3. Delete Collector" << endl;
		cout << "4. Delete Recorder" << endl;
		cout << "5. Change Identity" << endl;
		cout << "6. Log out" << endl;
		cout << "--------------------" << endl;
		cin >> Choice;
		cout << "--------------------" << endl;
		if (Choice == "1")
		{
			cout << "-----Add Collector------" << endl;
			cout << "Please insert the ID number of the Collector." << endl;
			cin >> TheIDNum;
			cout << "--------------------" << endl;
			Res = Controler.CreateNewCollector(TheIDNum);
			if (Res == RES::NO_RIGHTS_CREATE_COLLECTOR)
			{
				cout << "You have no rights to create new Collector." << endl;
				cout << "--------------------" << endl;
			}
			else if(Res == RES::NO_USER)
			{
				cout << "No such registered participant to create Collector." << endl;
				cout << "--------------------" << endl;
			}
			else if (Res == RES::DUPLICATE_COLLECTOR)
			{
				cout << "The user is already a Collector" << endl;
				cout << "--------------------" << endl;
			}
			else
			{
				cout << "Collector created" << endl;
				cout << "--------------------" << endl;
			}
		}
		else if (Choice == "2")
		{
			cout << "-----Add Recorder------" << endl;
			cout << "Please insert the ID number of the Recorder." << endl;
			cin >> TheIDNum;
			cout << "--------------------" << endl;
			Res = Controler.CreateNewRecorder(TheIDNum);
			if (Res == RES::NO_RIGHTS_CREATE_COLLECTOR)
			{
				cout << "You have no rights to create new Recorder." << endl;
				cout << "--------------------" << endl;
			}
			else if (Res == RES::NO_USER)
			{
				cout << "No such registered participant to create Recorder." << endl;
				cout << "--------------------" << endl;
			}
			else if (Res == RES::DUPLICATE_RECORDER)
			{
				cout << "The user is already a Recorder" << endl;
				cout << "--------------------" << endl;
			}
			else
			{
				cout << "Recorder created" << endl;
				cout << "--------------------" << endl;
			}
		}
		else if (Choice == "3")
		{
			cout << "-----Delete Collector------" << endl;
			cout << "Please insert the ID number of the Collector." << endl;
			cin >> TheIDNum;
			cout << "--------------------" << endl;
			Res = Controler.DeleteCollector(TheIDNum);
			if (Res == RES::NO_RIGHTS_DELETE_COLLECTOR)
			{
				cout << "You have no rights to delete Collector." << endl;
				cout << "--------------------" << endl;
			}
			else if (Res == RES::NO_USER)
			{
				cout << "No such registered Collector to delete." << endl;
				cout << "--------------------" << endl;
			}
			else
			{
				cout << "Collector deleted" << endl;
				cout << "--------------------" << endl;
			}
		}
		else if (Choice == "4")
		{
			cout << "-----Delete Recorder------" << endl;
			cout << "Please insert the ID number of the Recorder." << endl;
			cin >> TheIDNum;
			cout << "--------------------" << endl;
			Res = Controler.DeleteRecorder(TheIDNum);
			if (Res == RES::NO_RIGHTS_DELETE_COLLECTOR)
			{
				cout << "You have no rights to delete Recorder." << endl;
				cout << "--------------------" << endl;
			}
			else if (Res == RES::NO_USER)
			{
				cout << "No such registered Recorder to delete." << endl;
				cout << "--------------------" << endl;
			}
			else
			{
				cout << "Recorder deleted" << endl;
				cout << "--------------------" << endl;
			}
		}
		else if (Choice == "5")
		{
		    cout << SelectIdentityMenu(Controler);
			return " ";
		}
		else if (Choice == "6")
		{
		    break;
		}
		else
		{
			cout << "Unknown choice. Please insert 1, 2, 3, 4, 5 or 6." << endl;
		}
	}
	return "Thank you for your use.";
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】string CollectorMenu(ControllerAbstractBase& Controler)
【函数功能】采集员身份窗口函数，用于身份为采集员的各类函数的调用
【参数】Controler：业务流程类对象，用于控制核心类
【返回值】字符串
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
string CollectorMenu(ControllerAbstractBase& Controler)
{
	cout << "-----Collector Menu------" << endl;
	RES Res;
	bool InfiniteLoop = true;
	string Choice;
	string TheTubeID;
	unsigned int uYear;
	unsigned int uMonth;
	unsigned int uDay;
	unsigned int uHour;
	unsigned int uMinute;
	unsigned int uSecond;
	vector<string> TheParticipantIDList;
	//可以初始化为不为#的任何值
	string Temp = "Not#";
	while (InfiniteLoop)
	{
		cout << "Please select your action." << endl;
		cout << "1. Add new tube" << endl;
		cout << "2. Delete tube" << endl;
		cout << "3. Change Identity" << endl;
		cout << "4. Log out" << endl;
		cout << "--------------------" << endl;
		cin >> Choice;
		if (Choice == "1")
		{
			cout << "-----Add New Tube------" << endl;
			cout << "Please insert the TubeID." << endl;
			cout << "--------------------" << endl;
			cin >> TheTubeID;
			cout << "Please insert the Collection time with YYYY-MM-DD HH:MM:SS" << endl;
			cout << "--------------------" << endl;
			cin >> uYear;
			//缓冲区清空
			getchar();
			cin >> uMonth;
			//缓冲区清空
			getchar();
			cin >> uDay >> uHour;
			//缓冲区清空
			getchar();
			cin >> uMinute;
			//缓冲区清空
			getchar();
			cin >> uSecond;
			cout << "Please insert the Participant list. End with '#'." << endl;
			cout << "--------------------" << endl;
			while (Temp != "#")
			{
				cin >> Temp;
				if (Temp != "#")
				{
					TheParticipantIDList.push_back(Temp);
				}
			}
			//可以为除了#的任何值，为了防止第一遍输入失误，第二遍重新输入直接跳过被试者列表输入阶段
			Temp = "Not#";
			cout << "--------------------" << endl;
			try
			{
				DateTime TheCollectTime(uYear, uMonth, uDay, uHour, uMinute, uSecond);
				bool IsTimeValid = TheCollectTime.IsValidDateTime();
				Res = Controler.AddTube(TheTubeID, TheCollectTime, TheParticipantIDList);
			}
			catch (exception& e)
			{
				cout << "Error: " << e.what() << endl;
				cout << "--------------------" << endl;
				continue;
			}
			if (Res == RES::INVALID_ID_NUMBER)
			{
				cout << "Invalid participant ID number list." << endl;
				cout << "--------------------" << endl;
			}
			else if (Res == RES::INVALID_TUBE_ID)
			{
				cout << "Invalid tube ID number." << endl;
				cout << "--------------------" << endl;
			}
			else if (Res == RES::NO_RIGHTS_ADD_TUBE)
			{
				cout << "You have no rights to add new tube." << endl;
				cout << "--------------------" << endl;
			}
			else if (Res == RES::DATA_NEWED)
			{
				cout << "An existed tube. Data renewed." << endl;
				cout << "--------------------" << endl;
			}
			else if(Res == RES::TUBE_ADDED)
			{
				cout << "Tube added." << endl;
				cout << "--------------------" << endl;
			}
		}
		else if (Choice == "2")
		{
			cout << "-----Delete Tube------" << endl;
			cout << "Please insert the TubeID." << endl;
			cin >> TheTubeID;
			cout << "--------------------" << endl;
			Res = Controler.DeleteTube(TheTubeID);
			if (Res == RES::INVALID_TUBE_ID)
			{
				cout << "Invalid tube ID number." << endl;
				cout << "--------------------" << endl;
			}
			else if (Res == RES::NO_RIGHTS_DELETE_TUBE)
			{
				cout << "You have no rights to delete tube." << endl;
				cout << "--------------------" << endl;
			}
			else if (Res == RES::NO_TUBE_FOUND)
			{
				cout << "No such tube found." << endl;
				cout << "--------------------" << endl;
			}
			else
			{
				cout << "Tube deleted." << endl;
				cout << "--------------------" << endl;
			}
		}
		else if (Choice == "3")
		{
			cout << SelectIdentityMenu(Controler);
			return " ";
		}
		else if (Choice == "4")
		{
			break;
		}
		else
		{
			cout << "Unknown choice. Please insert 1, 2, 3 or 4." << endl;
		}
	}
	return "Thank you for your use.";
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】string RecorderMenu(ControllerAbstractBase& Controler)
【函数功能】录入员身份窗口函数，用于身份为录入员的各类函数的调用
【参数】Controler：业务流程类对象，用于控制核心类
【返回值】字符串
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
string RecorderMenu(ControllerAbstractBase& Controler)
{
	cout << "-----Recorder Menu------" << endl;
	RES Res;
	bool InfiniteLoop = true;
	string Choice;
	string TheTubeID;
	string TheResult;
	unsigned int uYear;
	unsigned int uMonth;
	unsigned int uDay;
	unsigned int uHour;
	unsigned int uMinute;
	unsigned int uSecond;
	while (InfiniteLoop)
	{
		cout << "Please select your action." << endl;
		cout << "1. Add tube result" << endl;
		cout << "2. Change Identity" << endl;
		cout << "3. Log out" << endl;
		cout << "--------------------" << endl;
		cin >> Choice;
		if (Choice == "1")
		{
			cout << "-----Add Tube Result------" << endl;
			cout << "Please insert the TubeID." << endl;
			cout << "--------------------" << endl;
			cin >> TheTubeID;
			cout << "Please insert the Collection time with YYYY-MM-DD HH:MM:SS" << endl;
			cout << "--------------------" << endl;
			cin >> uYear;
			//缓冲区清空
			getchar();
			cin >> uMonth;
			//缓冲区清空
			getchar();
			cin >> uDay >> uHour;
			//缓冲区清空
			getchar();
			cin >> uMinute;
			//缓冲区清空
			getchar();
			cin >> uSecond;
			cout << "Please insert the Tube Result." << endl;
			cout << "--------------------" << endl;
			cin >> TheResult;
			cout << "--------------------" << endl;
			try
			{
				DateTime TheRecordTime(uYear, uMonth, uDay, uHour, uMinute, uSecond);
				bool IsTimeValid = TheRecordTime.IsValidDateTime();
				Res = Controler.AddTubeResult(TheRecordTime, TheResult, TheTubeID);
			}
			catch (exception& e)
			{
				cout << "Error: " << e.what() << endl;
				cout << "--------------------" << endl;
				continue;
			}
			if (Res == RES::NO_TUBE_FOUND)
			{
				cout << "No such Tube ID number found." << endl;
				cout << "--------------------" << endl;
			}
			else if (Res == RES::INVALID_TUBE_ID)
			{
				cout << "Invalid tube ID number." << endl;
				cout << "--------------------" << endl;
			}
			else if (Res == RES::UNKNOWN_TYPE)
			{
				cout << "Unknown result type." << endl;
				cout << "--------------------" << endl;
			}
			else if (Res == RES::NO_RIGHTS_ADD_TUBE_RESULT)
			{
				cout << "You have no rights to add tube result." << endl;
				cout << "--------------------" << endl;
			}
			else if (Res == RES::TUBE_RESULT_ADDED)
			{
				cout << "Tube result added." << endl;
				cout << "--------------------" << endl;
			}
		}
		else if (Choice == "2")
		{
			cout << SelectIdentityMenu(Controler);
			return " ";
		}
		else if (Choice == "3")
		{
			break;
		}
		else
		{
			cout << "Unknown choice. Please insert 1, 2 or 3." << endl;
		}
	}
	return "Thank you for your use.";
}
//-----------------------------------------------------------------------------
