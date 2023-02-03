/*************************************************************************
���ļ�����Tube.cpp
������ģ���Ŀ�ġ��Թ�������
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
#include "DateTime.hpp"
#include "Tube.hpp"
using namespace std;
//-----------------------------------------------------------------------------

//��̬��Ա��ʼ��
vector<Tube*> Tube::AllTube = {};
string Tube::SystemTubeID = { "20000101000000000000" };
vector<string> Tube::SystemParticipantIDList{};
DateTime Tube::SystemCollectTime{};
DateTime Tube::SystemRecordTime{};
string Tube::SystemResult{"WaitingForResult"};
vector<Tube*>& Tube::ReadAllTube{AllTube};
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�Tube::~Tube()
���������ܡ���������
����������
������ֵ�������������ɷ���ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
Tube::~Tube()
{
	;//��
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�Tube::Tube(const string& TubeID, const DateTime& CollectTime, const DateTime& RecordTime,
                       const vector<string>& ParticipantID, const TubeResult Result)
���������ܡ����캯���������������Թܱ�š��ɼ�ʱ�䡢¼��ʱ�䡢���������֤���б������������µ��Թܶ���
��������TubeID���Թܱ�ţ�CollectTime���ɼ�ʱ�䣻RecordTime��¼��ʱ�䣻ParticipantID�����������֤���б�Result��������
������ֵ�����캯�����ɷ���ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
Tube::Tube(const string& TubeID, const DateTime& CollectTime, const DateTime& RecordTime,
      const vector<string>& ParticipantID, const TubeResult Result) :
      TubeID(m_TubeID), CollectTime(m_CollectTime), RecordTime(m_RecordTime), 
      ParticipantID(m_ParticipantID), Result(m_Result)
{
    //����Թܱ�Ų����Ϲ淶
    if (!IsTubeIDValid)
    {
        throw invalid_argument("Invalid Tube ID.");
    }
    m_TubeID = TubeID;
    m_CollectTime = CollectTime;
    m_RecordTime = RecordTime;
    m_ParticipantID = ParticipantID;
    m_Result = Result;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�istream& operator>>(istream& Stream, Tube& anTube)
���������ܡ�>>���������
��������Stream��istream����anTube������>>��������Թ������
������ֵ��istream���������
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
istream& operator>>(istream& Stream, Tube& anTube)
{
    string TheTubeResult;
    unsigned int uParticipantCount;
    string Temp;
    //д���Թܱ�š��ɼ�ʱ�䡢¼��ʱ�䡢������Թܱ������б�����
    Stream >> anTube.m_TubeID >> anTube.m_CollectTime >> anTube.m_RecordTime >> TheTubeResult >> uParticipantCount;
    //�ַ������ת��ΪΪTubeResult���
    if (TheTubeResult == "Positive")
    {
        anTube.m_Result = TubeResult::Positive;
    }
    else if (TheTubeResult == "Negative")
    {
        anTube.m_Result = TubeResult::Negative;
    }
    else if (TheTubeResult == "WaitingForResult")
    {
        anTube.m_Result = TubeResult::WaitingForResult;
    }
    else
    {
        throw invalid_argument("Unknown Result.");
    }
    for (unsigned int i = 0; i < uParticipantCount; i++)
    {
        Stream >> Temp;
        (anTube.m_ParticipantID).push_back(Temp);
    }
    return Stream;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�ostream& operator<<(ostream& Stream, const Tube& anTube)
���������ܡ�<<���������
��������Stream��ostream����anTube������<<��������Թ������
������ֵ��ostream���������
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
ostream& operator<<(ostream& Stream, const Tube& anTube)
{
    //д���Թܱ�š��ɼ�ʱ�䡢¼��ʱ��
    Stream << anTube.TubeID << ' ' << anTube.CollectTime << ' ' << anTube.RecordTime << ' ';
    //����TubeResult���ת��Ϊ�ַ���������
    if (anTube.Result == TubeResult::Positive)
    {
        Stream << "Positive" << ' ';
    }
    else if (anTube.Result == TubeResult::Negative)
    {
        Stream << "Negative" << ' ';
    }
    else if (anTube.Result == TubeResult::WaitingForResult)
    {
        Stream << "WaitingForResult" << ' ';
    }
    //����Թܱ������б�����
    Stream << (anTube.ParticipantID).size() << ' ';
    //����Թܱ������б�
    for (unsigned int i = 0; i < (anTube.ParticipantID).size(); i++)
    {
        Stream << anTube.ParticipantID[i] << ' ';
    }
    return Stream;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�void Tube::LoadTubeData(const string& TubeID, const DateTime& CollectTime, const DateTime& RecordTime,
                                    const vector<string>& ParticipantID, const string Result)
���������ܡ�����һ���µ��Թ�����󣬲��������뵽�����Թ��б���
��������TubeID���Թܱ�ţ�CollectTime���ɼ�ʱ�䣻RecordTime��¼��ʱ�䣻ParticipantID�����������֤���б�Result��������
������ֵ����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
void Tube::LoadTubeData(const string& TubeID, const DateTime& CollectTime, const DateTime& RecordTime,
                        const vector<string>& ParticipantID, const string Result)
{
    //�½�һ���Թܶ��󲢼����Թ��б�
    Tube* pNewTube = new Tube(TubeID, CollectTime, RecordTime, ParticipantID);
    if (Result == "Positive")
    {
        pNewTube->m_Result = TubeResult::Positive;
    }
    else if (Result == "Negative")
    {
        pNewTube->m_Result = TubeResult::Negative;
    }
    else if (Result == "WaitingForResult")
    {
        pNewTube->m_Result = TubeResult::WaitingForResult;
    }
    AllTube.push_back(pNewTube);
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�void Tube:: LoadFromFile(const string& FileName)
���������ܡ���̬����������ָ���ļ��ж����Թ��б����û���ҵ��ļ������½�һ���ļ�
��������FileName��ָ��������ļ���
������ֵ����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
void Tube:: LoadFromFile(const string& FileName)
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
    unsigned int uTubeCount;
    File >> uTubeCount;
    //���������
    File.get();
    //�Թ��б����
    AllTube.clear();
    for (unsigned int i = 0; i < uTubeCount; i++)
    {
        //�½�һ��ϵͳ�Թܣ�Ȼ����ļ��ж��뾫ȷ����
        LoadTubeData(SystemTubeID, SystemCollectTime, SystemRecordTime, SystemParticipantIDList, SystemResult);
        File >> *(*(AllTube.end() - 1));
    }
    File.close();
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�void Tube::SaveToFile(const string& FileName)
���������ܡ���̬���������Թ��б��浽ָ���ļ���
��������FileName��ָ��������ļ�����
������ֵ����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
void Tube::SaveToFile(const string& FileName)
{
    //�򿪻��½�һ��FileName���ļ�
    ofstream File(FileName);
    //������ܴ�
    if (!File.is_open())
    {
        throw invalid_argument("Can't open/Create for saving, File : " + FileName);
    }
    auto Saver = [&File](Tube* pPtrOfTube) {File << *pPtrOfTube << endl; };
    //�ȴ�������û�������
    File << AllTube.size() << endl;
    //���ÿ���û�������
    for_each(AllTube.begin(), AllTube.end(), Saver);
    //���浽ϵͳ
    File.close();
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�bool Tube::IsTubeIDValid(const string& TubeID)
���������ܡ���̬����������Թܱ���Ƿ����20λ��
��������TubeID���Թܱ��
������ֵ������ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
bool Tube::IsTubeIDValid(const string& TubeID)
{
    //�Թܱ��Ӧ��Ϊ20λ
    return TubeID.size() == 20;
}
//-----------------------------------------------------------------------------

