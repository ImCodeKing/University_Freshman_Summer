/*************************************************************************
���ļ�����Tube.hpp
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
#ifndef _TUBE_HPP_
#define _TUBE_HPP_
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <fstream>
#include <iostream>
#include "DateTime.hpp"
#include "ControllerAbstractBase.hpp"
using namespace std;
//-----------------------------------------------------------------------------

/*************************************************************************
��������TubeResult
�����ܡ�ö���࣬�Թܵĸ��ֺ�����
���ӿ�˵����ö�����޽ӿ�
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
enum class TubeResult
{
    Positive,
    Negative,
    WaitingForResult
};
//-----------------------------------------------------------------------------

/*************************************************************************
��������Tube
�����ܡ������Թ��࣬�Թܶ�����������
���ӿ�˵����
    ��ֹ�޲ι��졢�����͸�ֵ���ѽ���Ĭ�Ϲ��캯�����������캯���͸�ֵ�����
    ���캯��Participant(const string& IDNum, const string& Name, const string& Password);����һ�������������������֤�š�������������Ϣ
    ����virtual ~Participant();
    >>��������� istream& operator>>(istream& Stream, Tube& anTube);
    <<��������� ostream& operator<<(ostream& Stream, const Tube& anTube);
    ����static void LoadFromFile(const string& FileName); ��̬���������ļ��м��س�ʼ���Թ��б�
    ����static void SaveToFile(const string& FileName); ��̬���������Թ��б��浽ָ���ļ���
    ����void ChangePassword(const string& NewPassord); �޸ı���������������
    ����static bool IsTubeIDValid(const string& TubeID);; ��̬�������ж�������Թܱ���Ƿ����
    ����bool IsIDNumSole(string Source) const; �Ǿ�̬�������ж���������֤�����û��б����Ƿ�Ψһ
    ����static void AddParticipant(const string& IDNum, const string& Name, const string& Password); ��̬�������ڱ������б��м����µı����������
    ����static void DeleteParticipant(const string& IDNum); ��̬�������ڱ������б���ɾ�������ı����������
    ����static Participant* Verify(const string& TheIDNum, const string& ThePassword); �ڱ������б��в���ָ�������߶��󣬲��ȶ�����
    ����static void InitializeAdmin(); ��ʼ������Ա�б�����δ����ָ���ļ�ʱ��ʼ���������б�
    const string& TubeID; �Թܱ�ŵĳ�����
    const vector<string>& ParticipantID; �����Թܱ������б�ĳ�����
    const DateTime& CollectTime; �ɼ�ʱ��ĳ�����
    const DateTime& RecordTime; ¼��ʱ��ĳ�����
    const TubeResult& Result; �Թܺ������ĳ�����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
class Tube
{
public:
    Tube() = delete;
    Tube(Tube&) = delete;
    Tube& operator=(Tube& Source) = delete;
    virtual ~Tube();
    // >>���������
    friend istream& operator>>(istream& Stream, Tube& anTube);
    // <<���������
    friend ostream& operator<<(ostream& Stream, const Tube& anTube);
    //���ļ��м����Թ��б�
    static void LoadFromFile(const string& FileName);
    //���Թ��б��浽�ļ���
    static void SaveToFile(const string& FileName);
    //����Թܱ���Ƿ����
    static bool IsTubeIDValid(const string& TubeID);
    //�������б�
    const string& TubeID;
    const vector<string>& ParticipantID;
    const DateTime& CollectTime;
    const DateTime& RecordTime;
    const TubeResult& Result;
private:
    //Tube���캯��
    Tube(const string& TubeID, const DateTime& CollectTime, const DateTime& RecordTime, const vector<string>& ParticipantID,
         const TubeResult Result = TubeResult::WaitingForResult);
    //�����Թ���Ϣ����
    static void LoadTubeData(const string& TubeID, const DateTime& CollectTime, const DateTime& RecordTime,
                             const vector<string>& ParticipantID, const string Result);
    //ҵ������������Ϊ��Ԫ��
    friend class ControllerAbstractBase;
    //�����Թ��б�
    static vector<Tube*> AllTube;
    //ϵͳ��ʼ�Թ���Ϣ
    static string SystemTubeID;
    static vector<string> SystemParticipantIDList;
    static DateTime SystemCollectTime;
    static DateTime SystemRecordTime;
    static string SystemResult;
    //�Թ���˽�г�Ա
    string m_TubeID;
    vector<string> m_ParticipantID;
    DateTime m_CollectTime;
    DateTime m_RecordTime;
    TubeResult m_Result;
    //ֻ�������Թ��б�
    static vector<Tube*>& ReadAllTube;
};
#endif