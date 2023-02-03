/*************************************************************************
【文件名】ControllerAbstractBase.hpp
【功能模块和目的】业务流程类控制类声明
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
【类名】ControlerRet
【功能】枚举类，控制器的各种结果返回值类
【接口说明】枚举类无接口
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
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

//宏
#define enum_to_string(x) #x

//简化返回值类名
using RES = ControlerRet;

//提示字符串组
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
【类名】ControllerAbstractBase
【功能】业务流程类，调用核心类的各类，实现增加、删除被试者、管理员、采集员、录入员、试管、试管结果的功能
【接口说明】
    构造函数ControllerAbstractBase(const string& ParticipantFileName, const string& ResultFileName);构造一个控制类对象，读取被试者文件和试管文件
    析构virtual ~ControllerAbstractBase();
    拷贝构造函数ControllerAbstractBase(const ControllerAbstractBase& Source);
    赋值运算符重载ControllerAbstractBase& operator= (ControllerAbstractBase& Source);
    函数RES Login(const string& IDNum, const string& Password); 根据参数列表提供的身份证号和密码与系统内部数据进行比对
    函数RES CreateNewParticipant(const string& IDNum, const string& Name, const string& Password); 创建新的被试者对象
    函数RES DeleteMyParticipant(); 删除已有的被试者对象
    函数RES CreateNewCollector(const string& IDNum); 管理员创建新的采集员对象
    函数RES CreateNewRecorder(const string& IDNum); 管理员创建新的录入员对象
    函数RES DeleteCollector(const string& IDNum); 管理员删除已有对象的采集员身份
    函数RES DeleteRecorder(const string& IDNum); 管理员删除已有对象的录入员身份
    函数RES ChangePassword(const string& NewPassword); 更改被试者密码
    函数RES SellectUserType() const; 登入系统后选择自己所用身份
    函数RES ShowResult() const; 展示最近一次核酸采集时间、录入时间、核酸结果
    函数RES ChangeIdentity(); 登入系统选择身份后再次变更身份
    函数RES AddTube(const string& TubeID, const DateTime& CollectTime, const vector<string>& ParticipantIDList); 采集员新增一个测试试管对象
    函数RES DeleteTube(const string& TubeID); 采集员删除已有的试管对象
    函数RES AddTubeResult(const DateTime& RecordTime, string& TheResult, const string& TubeID); 录入员增加已有试管核酸结果
    函数RES Logout() const; 登出系统
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/

class ControllerAbstractBase
{
public:
    //构造函数
    ControllerAbstractBase(const string& ParticipantFileName, const string& ResultFileName);
    //拷贝构造函数
    ControllerAbstractBase(const ControllerAbstractBase& Source);
    //赋值运算符重载
    ControllerAbstractBase& operator= (const ControllerAbstractBase& Source);
    //析构函数
    virtual ~ControllerAbstractBase();
    //用户登陆
    RES Login(const string& IDNum, const string& Password);
    //创建新用户
    RES CreateNewParticipant(const string& IDNum, const string& Name, const string& Password);
    //删除用户
    RES DeleteMyParticipant();
    //创建新采集员
    RES CreateNewCollector(const string& IDNum);
    //创建新录入员
    RES CreateNewRecorder(const string& IDNum);
    //删除采集员
    RES DeleteCollector(const string& IDNum);
    //删除录入员
    RES DeleteRecorder(const string& IDNum);
    //更改密码
    RES ChangePassword(const string& NewPassword);
    //选择用户身份
    RES SellectUserType() const;
    //展示核酸结果
    RES ShowResult() const;
    //更改登入身份
    RES ChangeIdentity() const;
    //增加一个新试管
    RES AddTube(const string& TubeID, const DateTime& CollectTime, const vector<string>& ParticipantIDList);
    //删除试管
    RES DeleteTube(const string& TubeID);
    //为试管增加结果
    RES AddTubeResult(const DateTime& RecordTime, string& TheResult, const string& TubeID);
    //用户登出
    RES Logout() const;
private:
    //被试者数据储存文件名
    string m_ParticipantFileName;
    //试管数据储存文件名
    string m_ResultFileName;
    //登录的被试者
    Participant* m_pLoginedUser = nullptr;
};
#endif