/*************************************************************************
���ļ�����Participant.hpp
������ģ���Ŀ�ġ�������������
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
#ifndef _PARTICIPANT_HPP_
#define _PARTICIPANT_HPP_
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <fstream>
#include <iostream>
#include "DateTime.hpp"
using namespace std;
//-----------------------------------------------------------------------------

/*************************************************************************
��������UsersType
�����ܡ�ö���࣬�û��ĸ����������
���ӿ�˵����ö�����޽ӿ�
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
enum class UsersType
{
	Trival,
	Admin,
	Collector,
	Recorder,
	CollectorAndRecorder,
	AdminAndCollector,
	AdminAndRecorder,
	AdminAndCollectorAndRecorder
};
//-----------------------------------------------------------------------------

/*************************************************************************
��������Participant
�����ܡ����ı������࣬�����߶�����������
���ӿ�˵����
    ��ֹ�޲ι��졢�����͸�ֵ���ѽ���Ĭ�Ϲ��캯�����������캯���͸�ֵ�����
	��������Ӧ���������ⲻ�ɼ��ԣ��ʲ����ó�����ֻ����ʽ
	���캯��Participant(const string& IDNum, const string& Name, const string& Password);����һ�������������������֤�š�������������Ϣ
	����virtual ~Participant();
	>>��������� istream& operator>>(istream& Stream, Participant& anParticipant);
	<<��������� ostream& operator<<(ostream& Stream, const Participant& anParticipant);
	����void ChangePassword(const string& NewPassord); �޸ı���������������
	����static bool IsIDNumValid(const string& Source); ��̬�������ж���������֤���Ƿ����
	����bool IsIDNumSole(const string& Source) const; �Ǿ�̬�������ж���������֤�����û��б����Ƿ�Ψһ
	����static void AddParticipant(const string& IDNum, const string& Name, const string& Password); ��̬�������ڱ������б��м����µı����������
	����static void DeleteParticipant(const string& IDNum); ��̬�������ڱ������б���ɾ�������ı����������
	����static void LoadFromFile(const string& FileName); ��̬���������ļ��м��س�ʼ���������б�
	����static void SaveToFile(const string& FileName); ��̬���������������б��浽ָ���ļ���
	����static Participant* Verify(const string& TheIDNum, const string& ThePassword); �ڱ������б��в���ָ�������߶��󣬲��ȶ�����
	����static void InitializeAdmin(); ��ʼ������Ա�б�����δ����ָ���ļ�ʱ��ʼ���������б�
	const string& IDNum; �������֤�ŵĳ�����
	const string& Name; �������ֵĳ�����
	const UsersType& Type; �������͵ĳ�����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
class Participant
{
public:
	//Ĭ�Ϲ��캯��ɾ��
	Participant() = delete;
	//�������캯��ɾ��
	Participant(const Participant&) = delete;
	//��ֵ�����ɾ��
	Participant& operator=(const Participant&) = delete;
	//��������
	virtual ~Participant();
	// >>���������
	friend istream& operator>>(istream& Stream, Participant& anParticipant);
	// <<���������
	friend ostream& operator<<(ostream& Stream, const Participant& anParticipant);
	//�������뺯��
	void ChangePassword(const string& NewPassord);
	//������֤���Ƿ����ľ�̬����
	static bool IsIDNumValid(const string& Source);
	//������֤���Ƿ�Ψһ�ķǾ�̬����
	bool IsIDNumSole(const string& Source) const;
	//�������б������ӱ�����
	static void AddParticipant(const string& IDNum, const string& Name, const string& Password);
	//�������б���ע��������
	static void DeleteParticipant(const string& IDNum);
	//���ļ��м����û��б�
	static void LoadFromFile(const string& FileName);
	//���û��б��浽�ļ���
	static void SaveToFile(const string& FileName);
	//��¼����������Ѱ�Ҳ��ȶԣ�
	static Participant* Verify(const string& TheIDNum, const string& ThePassword);
	//��ʼ������Ա�б�
	static void InitializeAdmin();
	//������
	const string& IDNum;
	const string& Name;
	const UsersType& Type;
private:
	//���֤��
	string m_IDNum;
	//����
	string m_Name;
	//����
	string m_Password;
	//���������
	UsersType m_Type;
	//Participant��Ĺ��캯��
	Participant(const string& IDNum, const string& Name, const string& Password);
	//ҵ������������Ϊ��Ԫ��
	friend class ControllerAbstractBase;
	//���б������б�
	static vector<Participant*> AllParticipants;
	//����Ա�ľ�̬���֤���б�
	static vector<string> AdminIDNum;
	//����Ա�ľ�̬�����б�
	static vector<string> AdminName;
	//����Ա�ľ�̬�����б�
	static vector<string> AdminPassword;
	//����Ա�ľ�̬���
	static UsersType AdminType;
};
#endif