/*************************************************************************
【文件名】ControllerAbstractBase.cpp
【功能模块和目的】业务流程类控制类函数定义
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
【函数名称】ControllerAbstractBase::ControllerAbstractBase(const string& ParticipantFileName, const string& ResultFileName)
【函数功能】构造函数，记录储存文件的名字，并读取其中的数据
【参数】ParticipantFileName：被试者储存文件名；ResultFileName：核酸结果储存文件名
【返回值】构造函数不可有返回值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
ControllerAbstractBase::ControllerAbstractBase(const string& ParticipantFileName, const string& ResultFileName)
{
    m_ParticipantFileName = ParticipantFileName;
    m_ResultFileName = ResultFileName;
    //读取被试者文件中的数据
    Participant::LoadFromFile(m_ParticipantFileName);
    //读取试管文件中的数据
    Tube::LoadFromFile(m_ResultFileName);
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】ControllerAbstractBase::ControllerAbstractBase(const ControllerAbstractBase& Source)
【函数功能】拷贝构造函数，暂无深拷贝，留下接口以便后续维护
【参数】Source：被拷贝的ControllerAbstractBase对象
【返回值】构造函数不可有返回值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
ControllerAbstractBase::ControllerAbstractBase(const ControllerAbstractBase& Source)
{
    m_ParticipantFileName = Source.m_ParticipantFileName;
    m_ResultFileName = Source.m_ResultFileName;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】ControllerAbstractBase& ControllerAbstractBase::operator= (const ControllerAbstractBase& Source)
【函数功能】赋值运算符，暂无深拷贝，留下接口以便后续维护
【参数】Source：被拷贝的ControllerAbstractBase对象
【返回值】被赋值对象的引用
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
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
【函数名称】ControllerAbstractBase::~ControllerAbstractBase()
【函数功能】析构函数
【参数】无
【返回值】析构函数不可有返回值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
ControllerAbstractBase::~ControllerAbstractBase()
{
    Participant::SaveToFile(m_ParticipantFileName);
    Tube::SaveToFile(m_ResultFileName);
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】RES ControllerAbstractBase::Login(const string& IDNum, const string& Password)
【函数功能】根据提供的身份证号和密码调用Participant类的Verify函数，比对用户信息并返回登录请求结果
【参数】IDNum：提供的身份证号；Password：提供的密码
【返回值】控制器枚举返回值类对象
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
RES ControllerAbstractBase::Login(const string& IDNum, const string& Password)
{
    try 
    {
        m_pLoginedUser = Participant::Verify(IDNum, Password);
    }
    //如果没有找到用户（Verify函数返回一个整型-1）
    catch (int) 
    {
        return ControlerRet::NO_USER;
    }
    //如果密码错误（Verify返回一个无符号整型1）
    catch (unsigned int)
    {
        return ControlerRet::WRONG_PASSWORD;
    }
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】RES ControllerAbstractBase::CreateNewParticipant(const string& IDNum, const string& Name, const string& Password)
【函数功能】控制器创建一个新的被试者类对象，并返回创建请求结果
【参数】IDNum：提供的身份证号；Name：提供的名字；Password：提供的密码
【返回值】控制器枚举返回值类对象
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
RES ControllerAbstractBase::CreateNewParticipant(const string& IDNum, const string& Name, const string& Password)
{
    try
    {
        Participant::AddParticipant(IDNum, Name, Password);
    }
    //如果ID已经存在（AddParticipant返回一个无符号整型1）
    catch (unsigned int& e)
    {
        return ControlerRet::IDNUMBER_EXISTED;
    }
    //如果ID不符合规范（AddParticipant返回一个整型-1）
    catch (int& e)
    {
        return ControlerRet::INVALID_ID_NUMBER;
    }
    return ControlerRet::NEW_PARTICIPANT_CREATED;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】RES ControllerAbstractBase::DeleteMyParticipant()
【函数功能】控制器删除一个已存在的被试者类对象，并返回删除请求结果
【参数】无
【返回值】控制器枚举返回值类对象
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
RES ControllerAbstractBase::DeleteMyParticipant()
{
    Participant::DeleteParticipant(m_pLoginedUser->IDNum);
    return ControlerRet::USER_DELETED;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】RES ControllerAbstractBase::CreateNewCollector(const string& IDNum)
【函数功能】控制器为一个已存在的被试者类对象添加采集员身份，并返回添加请求结果
【参数】IDNum：提供的身份证号
【返回值】控制器枚举返回值类对象
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
RES ControllerAbstractBase::CreateNewCollector(const string& IDNum)
{
    //如果用户身份中没有包含Admin
    if (m_pLoginedUser->Type != UsersType::Admin && m_pLoginedUser->Type != UsersType::AdminAndCollector && 
        m_pLoginedUser->Type != UsersType::AdminAndCollectorAndRecorder && m_pLoginedUser->Type != UsersType::AdminAndRecorder)
    {
        return ControlerRet::NO_RIGHTS_CREATE_COLLECTOR;
    }
    //遍历整个被试者列表
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
            //如果身份证号相符但已经有Collector身份，则报错已存在Collector身份
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
【函数名称】RES ControllerAbstractBase::CreateNewRecorder(const string& IDNum)
【函数功能】控制器为一个已存在的被试者类对象添加录入员身份，并返回添加请求结果
【参数】IDNum：提供的身份证号
【返回值】控制器枚举返回值类对象
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
RES ControllerAbstractBase::CreateNewRecorder(const string& IDNum)
{
    //如果用户身份中没有包含Admin
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
            //如果身份证号相符但已经有Recorder身份，则报错已存在Recorder身份
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
【函数名称】RES ControllerAbstractBase::DeleteCollector(const string& IDNum)
【函数功能】控制器为一个已存在的被试者类对象删除采集员身份，并返回删除请求结果
【参数】IDNum：提供的身份证号
【返回值】控制器枚举返回值类对象
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
RES ControllerAbstractBase::DeleteCollector(const string& IDNum)
{
    //如果用户身份中没有包含Admin
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
【函数名称】RES ControllerAbstractBase::DeleteRecorder(const string& IDNum)
【函数功能】控制器为一个已存在的被试者类对象删除录入员身份，并返回删除请求结果
【参数】IDNum：提供的身份证号
【返回值】控制器枚举返回值类对象
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
RES ControllerAbstractBase::DeleteRecorder(const string& IDNum)
{
    //如果用户身份中没有包含Admin
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
【函数名称】RES ControllerAbstractBase::ChangePassword(const string& NewPassword)
【函数功能】一个已存在的被试者类对象更改自己的密码，并返回更改请求结果
【参数】Password：提供的新密码
【返回值】控制器枚举返回值类对象
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
RES ControllerAbstractBase::ChangePassword(const string& NewPassword)
{
    m_pLoginedUser->ChangePassword(NewPassword);
    return ControlerRet::PASSWORD_CHANGED;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】RES ControllerAbstractBase::SellectUserType() const
【函数功能】登入后挑选自己的用户类型，并返回挑选请求结果
【参数】无
【返回值】控制器枚举返回值类对象
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
RES ControllerAbstractBase::SellectUserType() const
{
    //用于选择类型
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
【函数名称】RES ControllerAbstractBase::ShowResult() const
【函数功能】展示最近一次（以录入时间为标准排序）核酸的采集时间、录入时间、核酸结果，并返回展示请求结果
【参数】无
【返回值】控制器枚举返回值类对象
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
RES ControllerAbstractBase::ShowResult() const
{
    DateTime TheLatestTime;
    string TheTubeID{ "NoTube" };
    string MyResult;
    DateTime MyCollectTime;
    DateTime MyRecordTime;
    //遍历所有试管的只读列表
    for (auto& m : Tube::ReadAllTube)
    {
        for (auto& n : m->ParticipantID)
        {
            //如果在试管列表中找到了所需查验人的身份证号
            if (n == m_pLoginedUser->IDNum)
            {
                //如果找到的结果的采集时间比上一次最近时间还要近
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
    //遍历过后没有找到结果，则返回无结果的提示
    if (TheTubeID == "NoTube")
    {
        return ControlerRet::NO_RECENT_RESULT;
    }
    //找到最新结果后输出
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
【函数名称】RES ControllerAbstractBase::ChangeIdentity() const
【函数功能】更改用户的身份时判断用户是否为仅有一种身份的Trival被试者类对象，使Trival不可以进行身份的变换，并返回判断结果
【参数】无
【返回值】控制器枚举返回值类对象
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
RES ControllerAbstractBase::ChangeIdentity() const
{
    //如果用户身份仅有平凡被试者一类，则返回“没有更多身份选择”
    if (m_pLoginedUser->Type == UsersType::Trival)
    {
        return ControlerRet::NO_MORE_IDENITY;
    }
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】RES ControllerAbstractBase::AddTube(const string& TubeID, const DateTime& CollectTime, const vector<string>& ParticipantIDList)
【函数功能】采集员添加一个新的核酸试管，储存新试管的试管编号、采集时间、该试管的被试者身份证号列表
【参数】TubeID：新试管的试管编号；CollectTime：采集时间；ParticipantIDList：所有被试者身份证号列表
【返回值】控制器枚举返回值类对象
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
RES ControllerAbstractBase::AddTube(const string& TubeID, const DateTime& CollectTime, const vector<string>& ParticipantIDList)
{
    //如果身份不是采集员，则没有权利增加试管
    if (m_pLoginedUser->Type != UsersType::Collector && m_pLoginedUser->Type != UsersType::CollectorAndRecorder &&
        m_pLoginedUser->Type != UsersType::AdminAndCollector && m_pLoginedUser->Type != UsersType::AdminAndCollectorAndRecorder)
    {
        return ControlerRet::NO_RIGHTS_ADD_TUBE;
    }
    //如果试管编号合理
    if (Tube::IsTubeIDValid(TubeID))
    {
        //检测该试管的被试者列表是否为空
        if (ParticipantIDList.size() == 0)
        {
            return ControlerRet::INVALID_ID_NUMBER;
        }
        for (auto& n : ParticipantIDList)
        {
            //对被试者列表的每一个身份证号都进行合理性检测
            if (!Participant::IsIDNumValid(n))
            {
                return ControlerRet::INVALID_ID_NUMBER;
            }
        }
        //如果找到了已存在的试管，就更新其中的数据
        for (auto& n : Tube::ReadAllTube)
        {
            if (n->TubeID == TubeID)
            {
                n->m_CollectTime = CollectTime;
                n->m_ParticipantID = ParticipantIDList;
                return ControlerRet::DATA_NEWED;
            }
        }
        //添加新的试管
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
【函数名称】RES ControllerAbstractBase::DeleteTube(const string& TubeID)
【函数功能】采集员删除一个已存在的核酸试管
【参数】TubeID：被删除试管的试管编号
【返回值】控制器枚举返回值类对象
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
RES ControllerAbstractBase::DeleteTube(const string& TubeID)
{
    //如果不是采集员身份，则没有权力删除试管
    if (m_pLoginedUser->Type != UsersType::Collector && m_pLoginedUser->Type != UsersType::CollectorAndRecorder &&
        m_pLoginedUser->Type != UsersType::AdminAndCollector && m_pLoginedUser->Type != UsersType::AdminAndCollectorAndRecorder)
    {
        return ControlerRet::NO_RIGHTS_DELETE_TUBE;
    }
    unsigned int Counter = 0;
    //检测试管编号是否符合规范
    if (!Tube::IsTubeIDValid(TubeID))
    {
        return ControlerRet::INVALID_TUBE_ID;
    }
    for (auto& n : Tube::AllTube)
    {
        //在已有的试管列表中找到需要的试管并删除、指针置空
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
【函数名称】RES ControllerAbstractBase::AddTubeResult(const DateTime& RecordTime, string& TheResult, const string& TubeID)
【函数功能】录入员为一个已存在的核酸试管添加录入时间和核酸结果
【参数】RecordTime：录入时间；TheResult：该试管的核酸结果；TubeID：被添加结果试管的试管编号
【返回值】控制器枚举返回值类对象
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
RES ControllerAbstractBase::AddTubeResult(const DateTime& RecordTime, string& TheResult, const string& TubeID)
{
    //如果不是录入员，则没有权力录入试管结果
    if (m_pLoginedUser->Type != UsersType::Recorder && m_pLoginedUser->Type != UsersType::CollectorAndRecorder &&
        m_pLoginedUser->Type != UsersType::AdminAndRecorder && m_pLoginedUser->Type != UsersType::AdminAndCollectorAndRecorder)
    {
        return ControlerRet::NO_RIGHTS_ADD_TUBE_RESULT;
    }
    //检测试管编号是否合理
    if (!Tube::IsTubeIDValid(TubeID))
    {
        return ControlerRet::INVALID_TUBE_ID;
    }
    for (auto n : Tube::AllTube)
    {
        //写入录入时间和试管结果
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
【函数名称】RES ControllerAbstractBase::Logout() const
【函数功能】返回一个登出成功的信息
【参数】无
【返回值】控制器枚举返回值类对象
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
RES ControllerAbstractBase::Logout() const
{
    return ControlerRet::LOGOUT;
}
//-----------------------------------------------------------------------------
