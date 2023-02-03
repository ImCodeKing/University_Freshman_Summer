/*************************************************************************
���ļ�����ControllerAbstractBase.hpp
������ģ���Ŀ�ġ�ҵ�����������������
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
#ifndef _CONTROLLERABSTRACTBASE_HPP_
#define _CONTROLLERABSTRACTBASE_HPP_
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <fstream>
#include <iostream>
#include "DateTime.hpp"
#include "Participant.hpp"
using namespace std;
//-----------------------------------------------------------------------------

/*************************************************************************
��������ControlerRet
�����ܡ�ö���࣬�������ĸ��ֽ������ֵ��
���ӿ�˵����ö�����޽ӿ�
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
enum class ControlerRet
{
    NO_USER,
    NO_TUBE_FOUND,
    NO_RECENT_RESULT,
    WRONG_PASSWORD,
    IDNUMBER_EXISTED,
    NEW_PARTICIPANT_CREATED,
    ADMIN_LOGINED,
    COLLECTOR_LOGINED,
    RECORDER_LOGINED,
    PARTICIPANT_LOGINED,
    PASSWORD_CHANGED,
    NO_MORE_IDENITY,
    NO_RIGHTS_CREATE_USER,
    NO_RIGHTS_CREATE_COLLECTOR,
    NO_RIGHTS_CREATE_RECORDER,
    NO_RIGHTS_SHOW_RESULT,
    NO_RIGHTS_ADD_TUBE,
    NO_RIGHTS_DELETE_TUBE,
    NO_RIGHTS_ADD_TUBE_RESULT,
    NO_RIGHTS_DELETE_COLLECTOR,
    NO_RIGHTS_DELETE_RECORDER,
    USER_CREATED,
    TUBE_ADDED,
    TUBE_DELETED,
    USER_DELETED,
    TUBE_RESULT_ADDED,
    SHOW_COMPLETE,
    DUPLICATE_PARTICIPANT,
    DUPLICATE_COLLECTOR,
    DUPLICATE_RECORDER,
    INVALID_TUBE_ID,
    INVALID_ID_NUMBER,
    DATA_NEWED,
    UNKNOWN_TYPE,
    LOGOUT
};

//��
#define enum_to_string(x) #x

//�򻯷���ֵ����
using RES = ControlerRet;

//��ʾ�ַ�����
const string ResStr[]{
  enum_to_string(NO_USER),
  enum_to_string(NO_TUBE_FOUND),
  enum_to_string(NO_RECENT_RESULT),
  enum_to_string(WRONG_PASSWORD),
  enum_to_string(IDNUMBER_EXISTED),
  enum_to_string(NEW_PARTICIPANT_CREATED),
  enum_to_string(ADMIN_LOGINED),
  enum_to_string(PARTICIPANT_LOGINED),
  enum_to_string(PASSWORD_CHANGED),
  enum_to_string(COLLECTOR_LOGINED),
  enum_to_string(RECORDER_LOGINED),
  enum_to_string(NO_MORE_IDENITY),
  enum_to_string(NO_RIGHTS_CREATE_USER),
  enum_to_string(NO_RIGHTS_CREATE_COLLECTOR),
  enum_to_string(NO_RIGHTS_CREATE_RECORDER),
  enum_to_string(NO_RIGHTS_SHOW_RESULT),
  enum_to_string(NO_RIGHTS_ADD_TUBE),
  enum_to_string(NO_RIGHTS_DELETE_TUBE),
  enum_to_string(NO_RIGHTS_ADD_TUBE_RESULT),
  enum_to_string(NO_RIGHTS_DELETE_COLLECTOR),
  enum_to_string(NO_RIGHTS_DELETE_RECORDER),
  enum_to_string(USER_CREATED),
  enum_to_string(TUBE_ADDED),
  enum_to_string(TUBE_DELETED),
  enum_to_string(USER_DELETED),
  enum_to_string(TUBE_RESULT_ADDED),
  enum_to_string(SHOW_COMPLETE),
  enum_to_string(DUPLICATE_PARTICIPANT),
  enum_to_string(DUPLICATE_COLLECTOR),
  enum_to_string(DUPLICATE_RECORDER),
  enum_to_string(INVALID_TUBE_ID),
  enum_to_string(INVALID_ID_NUMBER),
  enum_to_string(DATA_NEWED)
  enum_to_string(UNKNOWN_TYPE),
  enum_to_string(LOGOUT)
};

/*************************************************************************
��������ControllerAbstractBase
�����ܡ�ҵ�������࣬���ú�����ĸ��࣬ʵ�����ӡ�ɾ�������ߡ�����Ա���ɼ�Ա��¼��Ա���Թܡ��Թܽ���Ĺ���
���ӿ�˵����
    ���캯��ControllerAbstractBase(const string& ParticipantFileName, const string& ResultFileName);����һ����������󣬶�ȡ�������ļ����Թ��ļ�
    ����virtual ~ControllerAbstractBase();
    �������캯��ControllerAbstractBase(const ControllerAbstractBase& Source);
    ��ֵ���������ControllerAbstractBase& operator= (ControllerAbstractBase& Source);
    ����RES Login(const string& IDNum, const string& Password); ���ݲ����б��ṩ�����֤�ź�������ϵͳ�ڲ����ݽ��бȶ�
    ����RES CreateNewParticipant(const string& IDNum, const string& Name, const string& Password); �����µı����߶���
    ����RES DeleteMyParticipant(); ɾ�����еı����߶���
    ����RES CreateNewCollector(const string& IDNum); ����Ա�����µĲɼ�Ա����
    ����RES CreateNewRecorder(const string& IDNum); ����Ա�����µ�¼��Ա����
    ����RES DeleteCollector(const string& IDNum); ����Աɾ�����ж���Ĳɼ�Ա���
    ����RES DeleteRecorder(const string& IDNum); ����Աɾ�����ж����¼��Ա���
    ����RES ChangePassword(const string& NewPassword); ���ı���������
    ����RES SellectUserType() const; ����ϵͳ��ѡ���Լ��������
    ����RES ShowResult() const; չʾ���һ�κ���ɼ�ʱ�䡢¼��ʱ�䡢������
    ����RES ChangeIdentity(); ����ϵͳѡ����ݺ��ٴα�����
    ����RES AddTube(const string& TubeID, const DateTime& CollectTime, const vector<string>& ParticipantIDList); �ɼ�Ա����һ�������Թܶ���
    ����RES DeleteTube(const string& TubeID); �ɼ�Աɾ�����е��Թܶ���
    ����RES AddTubeResult(const DateTime& RecordTime, string& TheResult, const string& TubeID); ¼��Ա���������Թܺ�����
    ����RES Logout() const; �ǳ�ϵͳ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/

class ControllerAbstractBase
{
public:
    //���캯��
    ControllerAbstractBase(const string& ParticipantFileName, const string& ResultFileName);
    //�������캯��
    ControllerAbstractBase(const ControllerAbstractBase& Source);
    //��ֵ���������
    ControllerAbstractBase& operator= (const ControllerAbstractBase& Source);
    //��������
    virtual ~ControllerAbstractBase();
    //�û���½
    RES Login(const string& IDNum, const string& Password);
    //�������û�
    RES CreateNewParticipant(const string& IDNum, const string& Name, const string& Password);
    //ɾ���û�
    RES DeleteMyParticipant();
    //�����²ɼ�Ա
    RES CreateNewCollector(const string& IDNum);
    //������¼��Ա
    RES CreateNewRecorder(const string& IDNum);
    //ɾ���ɼ�Ա
    RES DeleteCollector(const string& IDNum);
    //ɾ��¼��Ա
    RES DeleteRecorder(const string& IDNum);
    //��������
    RES ChangePassword(const string& NewPassword);
    //ѡ���û����
    RES SellectUserType() const;
    //չʾ������
    RES ShowResult() const;
    //���ĵ������
    RES ChangeIdentity() const;
    //����һ�����Թ�
    RES AddTube(const string& TubeID, const DateTime& CollectTime, const vector<string>& ParticipantIDList);
    //ɾ���Թ�
    RES DeleteTube(const string& TubeID);
    //Ϊ�Թ����ӽ��
    RES AddTubeResult(const DateTime& RecordTime, string& TheResult, const string& TubeID);
    //�û��ǳ�
    RES Logout() const;
private:
    //���������ݴ����ļ���
    string m_ParticipantFileName;
    //�Թ����ݴ����ļ���
    string m_ResultFileName;
    //��¼�ı�����
    Participant* m_pLoginedUser = nullptr;
};
#endif