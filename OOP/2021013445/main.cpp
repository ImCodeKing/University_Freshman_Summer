/*************************************************************************
���ļ�����main.hpp
������ģ���Ŀ�ġ������������ں���
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
����Ȩ��Ϣ�����´�����Դ���廪��ѧ��������ʦԭ����޸ĺͷ�װ��
	������������(lizhaoya21@mails.tsinghua.edu.cn)�����������޸Ĳ��ֵ��κΰ�Ȩ�����κ�ʹ���߿������κ��޸ġ������κ�Ŀ��
	ԭ����ѭ CC 4.0 BY-SA ��ȨЭ�飬ת���븽��ԭ�ĳ������Ӻͱ�����
	https://blog.csdn.net/oHanTanYanYing/article/details/31155985
	https://blog.csdn.net/oHanTanYanYing/article/details/29943973
	CC BY-SA 4.0 ��һ�����Э�飬����������������ҪȨ����
	һ�������Ȩ��������ͨ���κ�ý����κ���ʽ���ơ�������Ʒ��
	�����ı��Ȩ����������μӹ���ת���ͻ�����Ʒ���д�������������;����������ҵӦ�á�
�����ļ�¼��
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

//�����ں�����Ԥ������
string LoginMenu(ControllerAbstractBase& Controler);
string SelectIdentityMenu(ControllerAbstractBase& Controler);
string TrivalMenu(ControllerAbstractBase& Controler);
string AdminMenu(ControllerAbstractBase& Controler);
string CollectorMenu(ControllerAbstractBase& Controler);
string RecorderMenu(ControllerAbstractBase& Controler);
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�int main(int argc, char* argv[])
���������ܡ�������
��������argc���ṩ���������Ĳ���������argv���������ַ��������ָ��
������ֵ������
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
int main(int argc, char* argv[])
{
	ControllerAbstractBase Controler("Participant.txt", "Tube.txt");
	cout << LoginMenu(Controler) << endl;
	return 0;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�string LoginMenu(ControllerAbstractBase& Controler)
���������ܡ���¼���ں��������ڵ�¼ʱ�ĸ��ຯ���ĵ���
��������Controler��ҵ��������������ڿ��ƺ�����
������ֵ���ַ���
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
string LoginMenu(ControllerAbstractBase& Controler)
{
	string IDNum;
	string Name;
	string Password;
	string Choice = "N";
	RES Res;
	//����һ�����޵�ѭ��
	bool InfiniteLoop = true;
	while (InfiniteLoop)
	{
		cout << "------Welcome to Negative is a positive result------" << endl;
		cout << "-----Login------" << endl;
		cout << "Are you a new user? (Y or N)" << endl;
		cin >> Choice;
		while (InfiniteLoop)
		{
			//��������û�
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
				//���֤�Ų���������18λ��
				if (Res == RES::INVALID_ID_NUMBER)
				{
					cout << "Please enter valid ID number." << endl;
					cout << "--------------------" << endl;
					continue;
				}
				//��������������֤����һ���Ѿ����ڵ��û�ƥ��ʱ
				else if (Res == RES::IDNUMBER_EXISTED)
				{
					while (InfiniteLoop)
					{
						cout << "ID Number Existed. Login? (Y or N)" << endl;
						Choice.clear();
						cin >> Choice;
						//ѡ����yes
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
						//ѡ����no
						else if (Choice == "N" || Choice == "n")
						{
							return "Thank you for your use.";
						}
						//�����Ϲ涨��ѡ��
						else
						{
							cout << "Unknown choice. Please enter Y or N." << endl;
							cin >> Choice;
						}
					}
				}
				//���û�����б��з���ƥ������֤�ţ�����½����û���¼
				else
				{
					Res = Controler.Login(IDNum, Password);
					cout << "New participant created. Already login automaticly." << endl;
					cout << SelectIdentityMenu(Controler);
					return "--------------------";
				}
			}
			//����������û�
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
		//��������
		if (Res == RES::WRONG_PASSWORD)
		{
			cout << "Wrong Password. Login failed." << endl;
			cout << "--------------------" << endl;
			continue;
		}
		//�Ҳ������������û�
		else if (Res == RES::NO_USER)
		{
			cout << "No such user. Login failed." << endl;
			cout << "--------------------" << endl;
			continue;
		}
		//���ص�ѡ����ݲ˵�
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
���������ơ�string SelectIdentityMenu(ControllerAbstractBase& Controler)
���������ܡ�ѡ����ݴ��ں���������ѡ�����ʱʱ�ĸ��ຯ���ĵ���
��������Controler��ҵ��������������ڿ��ƺ�����
������ֵ���ַ���
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
string SelectIdentityMenu(ControllerAbstractBase& Controler)
{
	RES Res;
	bool InfiniteLoop = true;
	while (InfiniteLoop)
	{
		cout << "-----Select Your Identity------" << endl;
		//����ҵ����������ѡ��ݺ���
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
���������ơ�string TrivalMenu(ControllerAbstractBase& Controler)
���������ܡ���ͨ��������ݴ��ں������������Ϊ��ͨ�����ߵĸ��ຯ���ĵ���
��������Controler��ҵ��������������ڿ��ƺ�����
������ֵ���ַ���
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
string TrivalMenu(ControllerAbstractBase& Controler)
{
	cout << "-----Participant Menu------" << endl;
	RES Res;
	bool InfiniteLoop = true;
	string Choice;
	string NewPassword;
	//�Զ�չʾ������
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
���������ơ�string AdminMenu(ControllerAbstractBase& Controler)
���������ܡ�����Ա��ݴ��ں������������Ϊ����Ա�ĸ��ຯ���ĵ���
��������Controler��ҵ��������������ڿ��ƺ�����
������ֵ���ַ���
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
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
���������ơ�string CollectorMenu(ControllerAbstractBase& Controler)
���������ܡ��ɼ�Ա��ݴ��ں������������Ϊ�ɼ�Ա�ĸ��ຯ���ĵ���
��������Controler��ҵ��������������ڿ��ƺ�����
������ֵ���ַ���
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
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
	//���Գ�ʼ��Ϊ��Ϊ#���κ�ֵ
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
			//���������
			getchar();
			cin >> uMonth;
			//���������
			getchar();
			cin >> uDay >> uHour;
			//���������
			getchar();
			cin >> uMinute;
			//���������
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
			//����Ϊ����#���κ�ֵ��Ϊ�˷�ֹ��һ������ʧ�󣬵ڶ�����������ֱ�������������б�����׶�
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
���������ơ�string RecorderMenu(ControllerAbstractBase& Controler)
���������ܡ�¼��Ա��ݴ��ں������������Ϊ¼��Ա�ĸ��ຯ���ĵ���
��������Controler��ҵ��������������ڿ��ƺ�����
������ֵ���ַ���
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
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
			//���������
			getchar();
			cin >> uMonth;
			//���������
			getchar();
			cin >> uDay >> uHour;
			//���������
			getchar();
			cin >> uMinute;
			//���������
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
