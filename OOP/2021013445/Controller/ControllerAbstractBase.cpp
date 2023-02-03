/*************************************************************************
���ļ�����ControllerAbstractBase.cpp
������ģ���Ŀ�ġ�ҵ������������ຯ������
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
#include "Tube.hpp"
#include "ControllerAbstractBase.hpp"
using namespace std;
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�ControllerAbstractBase::ControllerAbstractBase(const string& ParticipantFileName, const string& ResultFileName)
���������ܡ����캯������¼�����ļ������֣�����ȡ���е�����
��������ParticipantFileName�������ߴ����ļ�����ResultFileName�������������ļ���
������ֵ�����캯�������з���ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
ControllerAbstractBase::ControllerAbstractBase(const string& ParticipantFileName, const string& ResultFileName)
{
    m_ParticipantFileName = ParticipantFileName;
    m_ResultFileName = ResultFileName;
    //��ȡ�������ļ��е�����
    Participant::LoadFromFile(m_ParticipantFileName);
    //��ȡ�Թ��ļ��е�����
    Tube::LoadFromFile(m_ResultFileName);
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�ControllerAbstractBase::ControllerAbstractBase(const ControllerAbstractBase& Source)
���������ܡ��������캯����������������½ӿ��Ա����ά��
��������Source����������ControllerAbstractBase����
������ֵ�����캯�������з���ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
ControllerAbstractBase::ControllerAbstractBase(const ControllerAbstractBase& Source)
{
    m_ParticipantFileName = Source.m_ParticipantFileName;
    m_ResultFileName = Source.m_ResultFileName;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�ControllerAbstractBase& ControllerAbstractBase::operator= (const ControllerAbstractBase& Source)
���������ܡ���ֵ�������������������½ӿ��Ա����ά��
��������Source����������ControllerAbstractBase����
������ֵ������ֵ���������
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
ControllerAbstractBase& ControllerAbstractBase::operator= (const ControllerAbstractBase& Source)
{
    if (this != &Source)
    {
        m_ParticipantFileName = Source.m_ParticipantFileName;
        m_ResultFileName = Source.m_ResultFileName;
        return *this;
    }
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�ControllerAbstractBase::~ControllerAbstractBase()
���������ܡ���������
����������
������ֵ���������������з���ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
ControllerAbstractBase::~ControllerAbstractBase()
{
    Participant::SaveToFile(m_ParticipantFileName);
    Tube::SaveToFile(m_ResultFileName);
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�RES ControllerAbstractBase::Login(const string& IDNum, const string& Password)
���������ܡ������ṩ�����֤�ź��������Participant���Verify�������ȶ��û���Ϣ�����ص�¼������
��������IDNum���ṩ�����֤�ţ�Password���ṩ������
������ֵ��������ö�ٷ���ֵ�����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
RES ControllerAbstractBase::Login(const string& IDNum, const string& Password)
{
    try 
    {
        m_pLoginedUser = Participant::Verify(IDNum, Password);
    }
    //���û���ҵ��û���Verify��������һ������-1��
    catch (int) 
    {
        return ControlerRet::NO_USER;
    }
    //����������Verify����һ���޷�������1��
    catch (unsigned int)
    {
        return ControlerRet::WRONG_PASSWORD;
    }
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�RES ControllerAbstractBase::CreateNewParticipant(const string& IDNum, const string& Name, const string& Password)
���������ܡ�����������һ���µı���������󣬲����ش���������
��������IDNum���ṩ�����֤�ţ�Name���ṩ�����֣�Password���ṩ������
������ֵ��������ö�ٷ���ֵ�����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
RES ControllerAbstractBase::CreateNewParticipant(const string& IDNum, const string& Name, const string& Password)
{
    try
    {
        Participant::AddParticipant(IDNum, Name, Password);
    }
    //���ID�Ѿ����ڣ�AddParticipant����һ���޷�������1��
    catch (unsigned int& e)
    {
        return ControlerRet::IDNUMBER_EXISTED;
    }
    //���ID�����Ϲ淶��AddParticipant����һ������-1��
    catch (int& e)
    {
        return ControlerRet::INVALID_ID_NUMBER;
    }
    return ControlerRet::NEW_PARTICIPANT_CREATED;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�RES ControllerAbstractBase::DeleteMyParticipant()
���������ܡ�������ɾ��һ���Ѵ��ڵı���������󣬲�����ɾ��������
����������
������ֵ��������ö�ٷ���ֵ�����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
RES ControllerAbstractBase::DeleteMyParticipant()
{
    Participant::DeleteParticipant(m_pLoginedUser->IDNum);
    return ControlerRet::USER_DELETED;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�RES ControllerAbstractBase::CreateNewCollector(const string& IDNum)
���������ܡ�������Ϊһ���Ѵ��ڵı������������Ӳɼ�Ա��ݣ����������������
��������IDNum���ṩ�����֤��
������ֵ��������ö�ٷ���ֵ�����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
RES ControllerAbstractBase::CreateNewCollector(const string& IDNum)
{
    //����û������û�а���Admin
    if (m_pLoginedUser->Type != UsersType::Admin && m_pLoginedUser->Type != UsersType::AdminAndCollector && 
        m_pLoginedUser->Type != UsersType::AdminAndCollectorAndRecorder && m_pLoginedUser->Type != UsersType::AdminAndRecorder)
    {
        return ControlerRet::NO_RIGHTS_CREATE_COLLECTOR;
    }
    //���������������б�
    for (auto& n : Participant::AllParticipants)
    {
        if (n->IDNum == IDNum && n->Type == UsersType::Trival)
        {
            n->m_Type = UsersType::Collector;
            return ControlerRet::USER_CREATED;
        }
        else if (n->IDNum == IDNum && n->Type == UsersType::Admin)
        {
            n->m_Type = UsersType::AdminAndCollector;
            return ControlerRet::USER_CREATED;
        }
        else if (n->IDNum == IDNum && n->Type == UsersType::Recorder)
        {
            n->m_Type = UsersType::CollectorAndRecorder;
            return ControlerRet::USER_CREATED;
        }
        else if (n->IDNum == IDNum && n->Type == UsersType::AdminAndRecorder)
        {
            n->m_Type = UsersType::AdminAndCollectorAndRecorder;
            return ControlerRet::USER_CREATED;
        }
        else
        {
            //������֤��������Ѿ���Collector��ݣ��򱨴��Ѵ���Collector���
            if (n->IDNum == IDNum)
            {
                return ControlerRet::DUPLICATE_COLLECTOR;
            }
        }
    }
    return ControlerRet::NO_USER;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�RES ControllerAbstractBase::CreateNewRecorder(const string& IDNum)
���������ܡ�������Ϊһ���Ѵ��ڵı�������������¼��Ա��ݣ����������������
��������IDNum���ṩ�����֤��
������ֵ��������ö�ٷ���ֵ�����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
RES ControllerAbstractBase::CreateNewRecorder(const string& IDNum)
{
    //����û������û�а���Admin
    if (m_pLoginedUser->Type != UsersType::Admin && m_pLoginedUser->Type != UsersType::AdminAndCollector &&
        m_pLoginedUser->Type != UsersType::AdminAndCollectorAndRecorder && m_pLoginedUser->Type != UsersType::AdminAndRecorder)
    {
        return ControlerRet::NO_RIGHTS_CREATE_RECORDER;
    }
    for (auto& n : Participant::AllParticipants)
    {
        if (n->IDNum == IDNum && n->Type == UsersType::Trival)
        {
            n->m_Type = UsersType::Recorder;
            return ControlerRet::USER_CREATED;
        }
        else if (n->IDNum == IDNum && n->Type == UsersType::Admin)
        {
            n->m_Type = UsersType::AdminAndRecorder;
            return ControlerRet::USER_CREATED;
        }
        else if (n->IDNum == IDNum && n->Type == UsersType::Collector)
        {
            n->m_Type = UsersType::CollectorAndRecorder;
            return ControlerRet::USER_CREATED;
        }
        else if (n->IDNum == IDNum && n->Type == UsersType::AdminAndCollector)
        {
            n->m_Type = UsersType::AdminAndCollectorAndRecorder;
            return ControlerRet::USER_CREATED;
        }
        else
        {
            //������֤��������Ѿ���Recorder��ݣ��򱨴��Ѵ���Recorder���
            if (n->IDNum == IDNum)
            {
                return ControlerRet::DUPLICATE_RECORDER;
            }
        }
    }
    return ControlerRet::NO_USER;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�RES ControllerAbstractBase::DeleteCollector(const string& IDNum)
���������ܡ�������Ϊһ���Ѵ��ڵı����������ɾ���ɼ�Ա��ݣ�������ɾ��������
��������IDNum���ṩ�����֤��
������ֵ��������ö�ٷ���ֵ�����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
RES ControllerAbstractBase::DeleteCollector(const string& IDNum)
{
    //����û������û�а���Admin
    if (m_pLoginedUser->Type != UsersType::Admin && m_pLoginedUser->Type != UsersType::AdminAndCollector && 
        m_pLoginedUser->Type != UsersType::AdminAndCollectorAndRecorder && m_pLoginedUser->Type != UsersType::AdminAndRecorder)
    {
        return ControlerRet::NO_RIGHTS_DELETE_COLLECTOR;
    }
    for (auto& n : Participant::AllParticipants)
    {
        if (n->IDNum == IDNum && n->Type == UsersType::Collector)
        {
            n->m_Type = UsersType::Trival;
            return ControlerRet::USER_CREATED;
        }
        else if (n->IDNum == IDNum && n->Type == UsersType::AdminAndCollector)
        {
            n->m_Type = UsersType::Admin;
            return ControlerRet::USER_CREATED;
        }
        else if (n->IDNum == IDNum && n->Type == UsersType::CollectorAndRecorder)
        {
            n->m_Type = UsersType::Recorder;
            return ControlerRet::USER_CREATED;
        }
        else if (n->IDNum == IDNum && n->Type == UsersType::AdminAndCollectorAndRecorder)
        {
            n->m_Type = UsersType::AdminAndRecorder;
            return ControlerRet::USER_CREATED;
        }
    }
    return ControlerRet::NO_USER;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�RES ControllerAbstractBase::DeleteRecorder(const string& IDNum)
���������ܡ�������Ϊһ���Ѵ��ڵı����������ɾ��¼��Ա��ݣ�������ɾ��������
��������IDNum���ṩ�����֤��
������ֵ��������ö�ٷ���ֵ�����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
RES ControllerAbstractBase::DeleteRecorder(const string& IDNum)
{
    //����û������û�а���Admin
    if (m_pLoginedUser->Type != UsersType::Admin && m_pLoginedUser->Type != UsersType::AdminAndCollector &&
        m_pLoginedUser->Type != UsersType::AdminAndCollectorAndRecorder && m_pLoginedUser->Type != UsersType::AdminAndRecorder)
    {
        return ControlerRet::NO_RIGHTS_DELETE_RECORDER;
    }
    for (auto& n : Participant::AllParticipants)
    {
        if (n->IDNum == IDNum && n->Type == UsersType::Recorder)
        {
            n->m_Type = UsersType::Trival;
            return ControlerRet::USER_CREATED;
        }
        else if (n->IDNum == IDNum && n->Type == UsersType::AdminAndRecorder)
        {
            n->m_Type = UsersType::Admin;
            return ControlerRet::USER_CREATED;
        }
        else if (n->IDNum == IDNum && n->Type == UsersType::CollectorAndRecorder)
        {
            n->m_Type = UsersType::Collector;
            return ControlerRet::USER_CREATED;
        }
        else if (n->IDNum == IDNum && n->Type == UsersType::AdminAndCollectorAndRecorder)
        {
            n->m_Type = UsersType::AdminAndCollector;
            return ControlerRet::USER_CREATED;
        }
    }
    return ControlerRet::NO_USER;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�RES ControllerAbstractBase::ChangePassword(const string& NewPassword)
���������ܡ�һ���Ѵ��ڵı��������������Լ������룬�����ظ���������
��������Password���ṩ��������
������ֵ��������ö�ٷ���ֵ�����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
RES ControllerAbstractBase::ChangePassword(const string& NewPassword)
{
    m_pLoginedUser->ChangePassword(NewPassword);
    return ControlerRet::PASSWORD_CHANGED;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�RES ControllerAbstractBase::SellectUserType() const
���������ܡ��������ѡ�Լ����û����ͣ���������ѡ������
����������
������ֵ��������ö�ٷ���ֵ�����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
RES ControllerAbstractBase::SellectUserType() const
{
    //����ѡ������
    string MyChoice;
    if (m_pLoginedUser->Type == UsersType::Trival)
    {
        return ControlerRet::PARTICIPANT_LOGINED;
    }
    else if (m_pLoginedUser->Type == UsersType::Admin)
    {
        cout << "Please choose your identity. Admin or Trival." << endl;
        cin >> MyChoice;
        if (MyChoice == "Trival")
        {
            return ControlerRet::PARTICIPANT_LOGINED;
        }
        else if (MyChoice == "Admin")
        {
            return ControlerRet::ADMIN_LOGINED;
        }
        else
        {
            return ControlerRet::UNKNOWN_TYPE;
        }
    }
    else if (m_pLoginedUser->Type == UsersType::Collector)
    {
        cout << "Please choose your identity. Collector or Trival." << endl;
        cin >> MyChoice;
        if (MyChoice == "Trival")
        {
            return ControlerRet::PARTICIPANT_LOGINED;
        }
        else if (MyChoice == "Collector")
        {
            return ControlerRet::COLLECTOR_LOGINED;
        }
        else
        {
            return ControlerRet::UNKNOWN_TYPE;
        }
    }
    else if (m_pLoginedUser->Type == UsersType::Recorder)
    {
        cout << "Please choose your identity. Recorder or Trival." << endl;
        cin >> MyChoice;
        if (MyChoice == "Trival")
        {
            return ControlerRet::PARTICIPANT_LOGINED;
        }
        else if (MyChoice == "Recorder")
        {
            return ControlerRet::RECORDER_LOGINED;
        }
        else
        {
            return ControlerRet::UNKNOWN_TYPE;
        }
    }
    else if (m_pLoginedUser->Type == UsersType::CollectorAndRecorder)
    {
        cout << "Please choose your identity. Collector, Recorder or Trival." << endl;
        cin >> MyChoice;
        if (MyChoice == "Trival")
        {
            return ControlerRet::PARTICIPANT_LOGINED;
        }
        else if (MyChoice == "Collector")
        {
            return ControlerRet::COLLECTOR_LOGINED;
        }
        else if (MyChoice == "Recorder")
        {
            return ControlerRet::RECORDER_LOGINED;
        }
        else
        {
            return ControlerRet::UNKNOWN_TYPE;
        }
    }
    else if (m_pLoginedUser->Type == UsersType::AdminAndRecorder)
    {
        cout << "Please choose your identity. Admin, Recorder or Trival." << endl;
        cin >> MyChoice;
        if (MyChoice == "Trival")
        {
            return ControlerRet::PARTICIPANT_LOGINED;
        }
        else if (MyChoice == "Admin")
        {
            return ControlerRet::ADMIN_LOGINED;
        }
        else if (MyChoice == "Recorder")
        {
            return ControlerRet::RECORDER_LOGINED;
        }
        else
        {
            return ControlerRet::UNKNOWN_TYPE;
        }
    }
    else if (m_pLoginedUser->Type == UsersType::AdminAndCollector)
    {
        cout << "Please choose your identity. Admin, Collector or Trival." << endl;
        cin >> MyChoice;
        if (MyChoice == "Trival")
        {
            return ControlerRet::PARTICIPANT_LOGINED;
        }
        else if (MyChoice == "Admin")
        {
            return ControlerRet::ADMIN_LOGINED;
        }
        else if (MyChoice == "Collector")
        {
            return ControlerRet::COLLECTOR_LOGINED;
        }
        else
        {
            return ControlerRet::UNKNOWN_TYPE;
        }
    }
    else if (m_pLoginedUser->Type == UsersType::AdminAndCollectorAndRecorder)
    {
        cout << "Please choose your identity. Admin, Collector, Recorder or Trival." << endl;
        cin >> MyChoice;
        if (MyChoice == "Trival")
        {
            return ControlerRet::PARTICIPANT_LOGINED;
        }
        else if (MyChoice == "Admin")
        {
            return ControlerRet::ADMIN_LOGINED;
        }
        else if (MyChoice == "Collector")
        {
            return ControlerRet::COLLECTOR_LOGINED;
        }
        else if (MyChoice == "Recorder")
        {
            return ControlerRet::RECORDER_LOGINED;
        }
        else
        {
            return ControlerRet::UNKNOWN_TYPE;
        }
    }
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�RES ControllerAbstractBase::ShowResult() const
���������ܡ�չʾ���һ�Σ���¼��ʱ��Ϊ��׼���򣩺���Ĳɼ�ʱ�䡢¼��ʱ�䡢��������������չʾ������
����������
������ֵ��������ö�ٷ���ֵ�����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
RES ControllerAbstractBase::ShowResult() const
{
    DateTime TheLatestTime;
    string TheTubeID{ "NoTube" };
    string MyResult;
    DateTime MyCollectTime;
    DateTime MyRecordTime;
    //���������Թܵ�ֻ���б�
    for (auto& m : Tube::ReadAllTube)
    {
        for (auto& n : m->ParticipantID)
        {
            //������Թ��б����ҵ�����������˵����֤��
            if (n == m_pLoginedUser->IDNum)
            {
                //����ҵ��Ľ���Ĳɼ�ʱ�����һ�����ʱ�仹Ҫ��
                if (m->RecordTime > TheLatestTime)
                {
                    if (m->Result != TubeResult::WaitingForResult)
                    {
                        TheLatestTime = m->RecordTime;
                        TheTubeID = m->TubeID;
                    }
                }
            }
        }
    }
    //��������û���ҵ�������򷵻��޽������ʾ
    if (TheTubeID == "NoTube")
    {
        return ControlerRet::NO_RECENT_RESULT;
    }
    //�ҵ����½�������
    for (auto& i : Tube::ReadAllTube)
    {
        if (i->TubeID == TheTubeID)
        {
            if (i->Result == TubeResult::Negative)
            {
                MyResult = "Negative";
            }
            else
            {
                MyResult = "Positive";
            }
            MyCollectTime = (i->CollectTime);
            MyRecordTime = (i->RecordTime);
        }
    }
    cout << "Collect Time: " << MyCollectTime << endl;
    cout << "Record Time: " << MyRecordTime << endl;
    cout << "The Result: " << MyResult << endl;
    return ControlerRet::SHOW_COMPLETE;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�RES ControllerAbstractBase::ChangeIdentity() const
���������ܡ������û������ʱ�ж��û��Ƿ�Ϊ����һ����ݵ�Trival�����������ʹTrival�����Խ�����ݵı任���������жϽ��
����������
������ֵ��������ö�ٷ���ֵ�����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
RES ControllerAbstractBase::ChangeIdentity() const
{
    //����û���ݽ���ƽ��������һ�࣬�򷵻ء�û�и������ѡ��
    if (m_pLoginedUser->Type == UsersType::Trival)
    {
        return ControlerRet::NO_MORE_IDENITY;
    }
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�RES ControllerAbstractBase::AddTube(const string& TubeID, const DateTime& CollectTime, const vector<string>& ParticipantIDList)
���������ܡ��ɼ�Ա���һ���µĺ����Թܣ��������Թܵ��Թܱ�š��ɼ�ʱ�䡢���Թܵı��������֤���б�
��������TubeID�����Թܵ��Թܱ�ţ�CollectTime���ɼ�ʱ�䣻ParticipantIDList�����б��������֤���б�
������ֵ��������ö�ٷ���ֵ�����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
RES ControllerAbstractBase::AddTube(const string& TubeID, const DateTime& CollectTime, const vector<string>& ParticipantIDList)
{
    //�����ݲ��ǲɼ�Ա����û��Ȩ�������Թ�
    if (m_pLoginedUser->Type != UsersType::Collector && m_pLoginedUser->Type != UsersType::CollectorAndRecorder &&
        m_pLoginedUser->Type != UsersType::AdminAndCollector && m_pLoginedUser->Type != UsersType::AdminAndCollectorAndRecorder)
    {
        return ControlerRet::NO_RIGHTS_ADD_TUBE;
    }
    //����Թܱ�ź���
    if (Tube::IsTubeIDValid(TubeID))
    {
        //�����Թܵı������б��Ƿ�Ϊ��
        if (ParticipantIDList.size() == 0)
        {
            return ControlerRet::INVALID_ID_NUMBER;
        }
        for (auto& n : ParticipantIDList)
        {
            //�Ա������б��ÿһ�����֤�Ŷ����к����Լ��
            if (!Participant::IsIDNumValid(n))
            {
                return ControlerRet::INVALID_ID_NUMBER;
            }
        }
        //����ҵ����Ѵ��ڵ��Թܣ��͸������е�����
        for (auto& n : Tube::ReadAllTube)
        {
            if (n->TubeID == TubeID)
            {
                n->m_CollectTime = CollectTime;
                n->m_ParticipantID = ParticipantIDList;
                return ControlerRet::DATA_NEWED;
            }
        }
        //����µ��Թ�
        Tube* pANewTube = new Tube(TubeID, CollectTime, Tube::SystemRecordTime, ParticipantIDList);
        Tube::AllTube.push_back(pANewTube);
        return ControlerRet::TUBE_ADDED;
    }
    else
    {
        return ControlerRet::INVALID_TUBE_ID;
    }
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�RES ControllerAbstractBase::DeleteTube(const string& TubeID)
���������ܡ��ɼ�Աɾ��һ���Ѵ��ڵĺ����Թ�
��������TubeID����ɾ���Թܵ��Թܱ��
������ֵ��������ö�ٷ���ֵ�����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
RES ControllerAbstractBase::DeleteTube(const string& TubeID)
{
    //������ǲɼ�Ա��ݣ���û��Ȩ��ɾ���Թ�
    if (m_pLoginedUser->Type != UsersType::Collector && m_pLoginedUser->Type != UsersType::CollectorAndRecorder &&
        m_pLoginedUser->Type != UsersType::AdminAndCollector && m_pLoginedUser->Type != UsersType::AdminAndCollectorAndRecorder)
    {
        return ControlerRet::NO_RIGHTS_DELETE_TUBE;
    }
    unsigned int Counter = 0;
    //����Թܱ���Ƿ���Ϲ淶
    if (!Tube::IsTubeIDValid(TubeID))
    {
        return ControlerRet::INVALID_TUBE_ID;
    }
    for (auto& n : Tube::AllTube)
    {
        //�����е��Թ��б����ҵ���Ҫ���Թܲ�ɾ����ָ���ÿ�
        if (n->TubeID == TubeID)
        {
            Tube::AllTube.erase(Tube::AllTube.begin() + Counter);
            delete n;
            n = nullptr;
            return ControlerRet::TUBE_DELETED;
        }
        Counter++;
    }
    return ControlerRet::NO_TUBE_FOUND;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�RES ControllerAbstractBase::AddTubeResult(const DateTime& RecordTime, string& TheResult, const string& TubeID)
���������ܡ�¼��ԱΪһ���Ѵ��ڵĺ����Թ����¼��ʱ��ͺ�����
��������RecordTime��¼��ʱ�䣻TheResult�����Թܵĺ�������TubeID������ӽ���Թܵ��Թܱ��
������ֵ��������ö�ٷ���ֵ�����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
RES ControllerAbstractBase::AddTubeResult(const DateTime& RecordTime, string& TheResult, const string& TubeID)
{
    //�������¼��Ա����û��Ȩ��¼���Թܽ��
    if (m_pLoginedUser->Type != UsersType::Recorder && m_pLoginedUser->Type != UsersType::CollectorAndRecorder &&
        m_pLoginedUser->Type != UsersType::AdminAndRecorder && m_pLoginedUser->Type != UsersType::AdminAndCollectorAndRecorder)
    {
        return ControlerRet::NO_RIGHTS_ADD_TUBE_RESULT;
    }
    //����Թܱ���Ƿ����
    if (!Tube::IsTubeIDValid(TubeID))
    {
        return ControlerRet::INVALID_TUBE_ID;
    }
    for (auto n : Tube::AllTube)
    {
        //д��¼��ʱ����Թܽ��
        if (n->TubeID == TubeID)
        {
            n->m_RecordTime = RecordTime;
            if (TheResult == "Positive" || TheResult == "positive")
            {
                n->m_Result = TubeResult::Positive;
            }
            else if (TheResult == "Negative" || TheResult == "negative")
            {
                n->m_Result = TubeResult::Negative;
            }
            else
            {
                return ControlerRet::UNKNOWN_TYPE;
            }
            return ControlerRet::TUBE_RESULT_ADDED;
        }
    }
    return ControlerRet::NO_TUBE_FOUND;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�RES ControllerAbstractBase::Logout() const
���������ܡ�����һ���ǳ��ɹ�����Ϣ
����������
������ֵ��������ö�ٷ���ֵ�����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
RES ControllerAbstractBase::Logout() const
{
    return ControlerRet::LOGOUT;
}
//-----------------------------------------------------------------------------
