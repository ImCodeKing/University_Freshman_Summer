/*************************************************************************
���ļ�����Participant.cpp
������ģ���Ŀ�ġ��������ྲ̬��Ա��ʼ���ͺ�������
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
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <fstream>
#include <iostream>
#include "Participant.hpp"
#include "DateTime.hpp"
#include "Tube.hpp"
using namespace std;
//-----------------------------------------------------------------------------

//��̬��Ա��ʼ��
vector<string> Participant::AdminIDNum{ "620103200302042122", "62010320030204161x" };
vector<string> Participant::AdminName{ "������","lzy" };
vector<string> Participant::AdminPassword{ "123", "123" };
UsersType Participant::AdminType = UsersType::Admin;
vector<Participant*> Participant::AllParticipants = {};
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�Participant:: ~Participant()
���������ܡ���������
����������
������ֵ���������������з���ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
Participant:: ~Participant()
{
    ;//��
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�Participant::Participant(const string& IDNum, const string& Name, const string& Password)
���������ܡ���������Ĺ��캯�����ж��������֤���Ƿ�����Ψһ������һ���µı����������
��������IDNum�������������֤�ţ�Name�������������֣�Password��������������
������ֵ�����캯�������з���ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
Participant::Participant(const string& IDNum, const string& Name, const string& Password) :
    IDNum(m_IDNum), Name(m_Name), Type(m_Type)
{
    //�ж����֤���Ƿ����
    if (!IsIDNumValid(IDNum))
    {
        throw -1;//invalid_argument("The ID number is invalid.");
    }
    //�ж����֤���Ƿ����
    for (const auto& n : AllParticipants)
    {
        if (n->IsIDNumSole(IDNum))
        {
            throw 1u;//invalid_argument("ID number existed.");
        }
    }
    m_IDNum = IDNum;
    m_Name = Name;
    m_Password = Password;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�bool Participant::IsIDNumValid(const string& Source)
���������ܡ���̬�������ж��������֤���Ƿ����
��������Source����Ҫ���ж��Ƿ��������֤��
������ֵ������ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
bool Participant::IsIDNumValid(const string& Source)
{
    if (Source.length() == 18)
    {
        //�ж����֤��ǰ17λ�Ƿ�Ϊ���֣����һλ�Ƿ�ΪX
        for (int i = 0; i < 17; i++)
        {
            if (Source[i] < '0' || Source[i] > '9')
            {
                return false;
            }
        }
        //�жϲ��������֤�����һλ�Ƿ�Ϊx������
        return (Source[17] == 'X' || Source[17] == 'x' || (Source[17] >= '0' && Source[17] <= '9'));
    }
    //�ڵ�һ�ζ�ȡ�ļ�д���б�ʱ��������
    if (Source == "SystemIDNum")
    {
        return true;
    }
    return false;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�bool Participant::IsIDNumSole(const string& Source) const
���������ܡ��ж��������֤���ڱ������б����Ƿ�Ψһ
��������Source����Ҫ���ж��Ƿ�Ψһ�����֤��
������ֵ������ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
bool Participant::IsIDNumSole(const string& Source) const
{
    //�ȶ��Լ������֤�źͲ����б��и������֤���Ƿ�һ��
    return IDNum == Source;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�istream& operator>>(istream& Stream, Participant& anParticipant)
���������ܡ�>>���������
��������Stream��istream����anParticipant������>>������ı����������
������ֵ��istream���������
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
istream& operator>>(istream& Stream, Participant& anParticipant)
{
    string TheType;
    //д�����֤�š�����������
    Stream >> anParticipant.m_IDNum >> anParticipant.m_Name >> anParticipant.m_Password >> TheType;
    //�����ַ���д����û����ͣ�ת��ΪUsersType������
    if (TheType == "Trival")
    {
        anParticipant.m_Type = UsersType::Trival;
    }
    else if (TheType == "Admin")
    {
        anParticipant.m_Type = UsersType::Admin;
    }
    else if (TheType == "Collector")
    {
        anParticipant.m_Type = UsersType::Collector;
    }
    else if (TheType == "Recorder")
    {
        anParticipant.m_Type = UsersType::Recorder;
    }
    else if (TheType == "CollectorAndRecorder")
    {
        anParticipant.m_Type = UsersType::CollectorAndRecorder;
    }
    else if (TheType == "AdminAndCollector")
    {
        anParticipant.m_Type = UsersType::AdminAndCollector;
    }
    else if (TheType == "AdminAndRecorder")
    {
        anParticipant.m_Type = UsersType::AdminAndRecorder;
    }
    else if (TheType == "AdminAndCollectorAndRecorder")
    {
        anParticipant.m_Type = UsersType::AdminAndCollectorAndRecorder;
    }
    else
    {
        throw invalid_argument("Unknown Type.");
    }
    return Stream;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�ostream& operator<<(ostream& Stream, const Participant& anParticipant)
���������ܡ�<<���������
��������Stream��ostream����anParticipant������<<������ı����������
������ֵ��ostream���������
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
ostream& operator<<(ostream& Stream, const Participant& anParticipant)
{
    //д�����֤�š�����������
    Stream << anParticipant.IDNum << ' ' << anParticipant.Name << ' ' << anParticipant.m_Password << ' ';
    //����UsersType�����ݣ�ת��Ϊ�ַ������
    if (anParticipant.Type == UsersType::Trival)
    {
        Stream << "Trival";
    }
    else if (anParticipant.Type == UsersType::Admin)
    {
        Stream << "Admin";
    }
    else if (anParticipant.Type == UsersType::Collector)
    {
        Stream << "Collector";
    }
    else if (anParticipant.Type == UsersType::Recorder)
    {
        Stream << "Recorder";
    }
    else if (anParticipant.Type == UsersType::CollectorAndRecorder)
    {
        Stream << "CollectorAndRecorder";
    }
    else if (anParticipant.Type == UsersType::AdminAndCollector)
    {
        Stream << "AdminAndCollector";
    }
    else if (anParticipant.Type == UsersType::AdminAndRecorder)
    {
        Stream << "AdminAndRecorder";
    }
    else if (anParticipant.Type == UsersType::AdminAndCollectorAndRecorder)
    {
        Stream << "AdminAndCollectorAndRecorder";
    }
    return Stream;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�void Participant::ChangePassword(const string& NewPassord)
���������ܡ������û�����
��������NewPassword���µ�����
������ֵ����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
void Participant::ChangePassword(const string& NewPassord)
{
    m_Password = NewPassord;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�Participant* Participant::Verify(const string& TheIDNum, const string& ThePassword)
���������ܡ������б������б���Ѱ�����������֤��ƥ��ı����ߣ����ȶ������Ƿ�һ��
��������TheIDNum����Ҫ�ȶԵ����֤�ţ�ThePassword����Ҫ�ȶԵ�����
������ֵ��������������ָ��
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
Participant* Participant::Verify(const string& TheIDNum, const string& ThePassword)
{
    //���֤�ŶԱȱ�׼
    auto Finder = [&TheIDNum](Participant* ptr)->bool {return (ptr->IDNum == TheIDNum); };
    //�ҵ����֤�ŵ�
    auto it = find_if(AllParticipants.begin(), AllParticipants.end(), Finder);
    //û���ҵ��û�
    if (it == AllParticipants.end()) 
    {
        throw -1;
    }
    //��������
    else if ((*it)->m_Password != ThePassword) 
    {
        throw 1u;
    }
    //�����û�ָ��
    else 
    {
        return *it;
    }
}
//-----------------------------------------------------------------------------


/*************************************************************************
���������ơ�void Participant::AddParticipant(const string& IDNum, const string& Name, const string& Password)
���������ܡ���̬����������һ���µı���������󣬲����������������б������б���
��������IDNum���½��û������֤�ţ�Name���½��û������֣�Password���½��û�������
������ֵ����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
void Participant::AddParticipant(const string& IDNum, const string& Name, const string& Password)
{
    //����һ�����û�
    Participant* pNewParticipant = new Participant(IDNum, Name, Password);
    pNewParticipant->m_Type = UsersType::Trival;
    //���뵽���б������б���
    AllParticipants.push_back(pNewParticipant);
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�void Participant::DeleteParticipant(const string& IDNum)
���������ܡ���̬��������������������б������б����Ƴ��������䶯̬���õ��ڴ�ռ��ͷš�ָ���ÿ�
��������IDNum���½��û������֤�ţ�
������ֵ����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
void Participant::DeleteParticipant(const string& IDNum)
{
    unsigned int uCounter = 0;
    for (auto& n : AllParticipants)
    {
        //�ҵ������֤������ı�����
        if (n->IDNum == IDNum)
        {
            //���б������
            AllParticipants.erase(AllParticipants.begin() + uCounter);
            //���ָ�������
            delete n;
            //ָ���ÿ�
            n = nullptr;
            return;
        }
        //���ڼ������ҵı��������б��еĵڼ���
        uCounter++;
    }
    throw invalid_argument("Participant not existed.");
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�void Participant::LoadFromFile(const string& FileName)
���������ܡ���̬����������ָ���ļ��ж��뱻�����б����û���ҵ��ļ������½�һ���ļ�������cpp�ļ���Ԥ�õĹ���Ա�б����
��������FileName��ָ��������ļ���
������ֵ����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
void Participant::LoadFromFile(const string& FileName)
{
    ifstream File(FileName);
    //����޷����ļ�
    if (!File.is_open())
    {
        //�½�һ���ļ�
        ofstream NewFile(FileName);
        //����½�ʧ��
        if (!NewFile.is_open())
        {
            throw invalid_argument("Can't open/create for loading, file: " + FileName);
        }
        NewFile << 0 << endl;
        //���浽ϵͳ
        NewFile.close();
        //���½��õ��ļ���
        File.open(FileName);
    }
    unsigned int uParticipantsCount;
    File >> uParticipantsCount;
    //���������
    File.get();
    //�û��б����
    AllParticipants.clear();
    //���һ���û���û�У���д��ϵͳԤ�Ƶ�Admin�б�
    if (uParticipantsCount == 0)
    {
        if (AdminIDNum.size() == 0)
        {
            throw invalid_argument("No participant found. Please creat Admin first.");
        }
        else
        {
            InitializeAdmin();
            SaveToFile(FileName);
        }
    }
    else
    {
        //������û�
        for (unsigned int i = 0; i < uParticipantsCount; i++)
        {
            //�ȴ���һ��ϵͳ���ı����߶���
            AddParticipant("SystemIDNum", "SystemName", "SystemPassword");
            //���ļ��ж���ÿ�������߶���ľ�������
            File >> *(*(AllParticipants.end() - 1));
        }
    }
    File.close();
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�void Participant::SaveToFile(const string& FileName)
���������ܡ���̬���������������б��浽ָ���ļ���
��������FileName��ָ��������ļ�����
������ֵ����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
void Participant::SaveToFile(const string& FileName)
{
    //�򿪻��½�һ��FileName���ļ�
    ofstream File(FileName);
    //������ܴ�
    if (!File.is_open())
    {
        throw invalid_argument("Can't open/Create for saving, File : " + FileName);
    }
    auto Saver = [&File](Participant* pPtrOfParticipant) {File << *pPtrOfParticipant << endl; };
    //�ȴ�������û�������
    File << AllParticipants.size() << endl;
    //���ÿ���û�������
    for_each(AllParticipants.begin(), AllParticipants.end(), Saver);
    //���浽ϵͳ
    File.close();
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�void Participant::InitializeAdmin()
���������ܡ���̬���������ع���Ա�б��������б����½��ļ�ʱ������
����������
������ֵ����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
void Participant::InitializeAdmin()
{
    for (unsigned int i = 0; i < AdminIDNum.size(); i++)
    {
        //��ʼ��ϵͳԤ�õĹ���Ա���뵽�������б��У������޸�cpp�еľ�̬�������ı�
        Participant* pNewAdmin = new Participant(AdminIDNum[i], AdminName[i], AdminPassword[i]);
        pNewAdmin->m_Type = UsersType::Admin;
        AllParticipants.push_back(pNewAdmin);
    }
}
//-----------------------------------------------------------------------------