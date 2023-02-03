/*************************************************************************
【文件名】Tube.hpp
【功能模块和目的】试管类声明
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
【类名】TubeResult
【功能】枚举类，试管的各种核酸结果
【接口说明】枚举类无接口
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
enum class TubeResult
{
    Positive,
    Negative,
    WaitingForResult
};
//-----------------------------------------------------------------------------

/*************************************************************************
【类名】Tube
【功能】核心试管类，试管对象的最基础类
【接口说明】
    禁止无参构造、拷贝和赋值，已禁用默认构造函数、拷贝构造函数和赋值运算符
    构造函数Participant(const string& IDNum, const string& Name, const string& Password);构造一个被试者类对象，添加身份证号、姓名和密码信息
    析构virtual ~Participant();
    >>运算符重载 istream& operator>>(istream& Stream, Tube& anTube);
    <<运算符重载 ostream& operator<<(ostream& Stream, const Tube& anTube);
    函数static void LoadFromFile(const string& FileName); 静态函数，从文件中加载初始化试管列表
    函数static void SaveToFile(const string& FileName); 静态函数，将试管列表保存到指定文件中
    函数void ChangePassword(const string& NewPassord); 修改被试者类对象的密码
    函数static bool IsTubeIDValid(const string& TubeID);; 静态函数，判断输入的试管编号是否合理
    函数bool IsIDNumSole(string Source) const; 非静态函数，判断输入的身份证号在用户列表中是否唯一
    函数static void AddParticipant(const string& IDNum, const string& Name, const string& Password); 静态函数，在被试者列表中加入新的被试者类对象
    函数static void DeleteParticipant(const string& IDNum); 静态函数，在被试者列表中删除所给的被试者类对象
    函数static Participant* Verify(const string& TheIDNum, const string& ThePassword); 在被试者列表中查找指定被试者对象，并比对密码
    函数static void InitializeAdmin(); 初始化管理员列表，用于未发现指定文件时初始化被试者列表
    const string& TubeID; 试管编号的常引用
    const vector<string>& ParticipantID; 单个试管被试者列表的常引用
    const DateTime& CollectTime; 采集时间的常引用
    const DateTime& RecordTime; 录入时间的常引用
    const TubeResult& Result; 试管核酸结果的常引用
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
class Tube
{
public:
    Tube() = delete;
    Tube(Tube&) = delete;
    Tube& operator=(Tube& Source) = delete;
    virtual ~Tube();
    // >>运算符重载
    friend istream& operator>>(istream& Stream, Tube& anTube);
    // <<运算符重载
    friend ostream& operator<<(ostream& Stream, const Tube& anTube);
    //从文件中加载试管列表
    static void LoadFromFile(const string& FileName);
    //将试管列表保存到文件中
    static void SaveToFile(const string& FileName);
    //检查试管编号是否合理
    static bool IsTubeIDValid(const string& TubeID);
    //常引用列表
    const string& TubeID;
    const vector<string>& ParticipantID;
    const DateTime& CollectTime;
    const DateTime& RecordTime;
    const TubeResult& Result;
private:
    //Tube构造函数
    Tube(const string& TubeID, const DateTime& CollectTime, const DateTime& RecordTime, const vector<string>& ParticipantID,
         const TubeResult Result = TubeResult::WaitingForResult);
    //加载试管信息函数
    static void LoadTubeData(const string& TubeID, const DateTime& CollectTime, const DateTime& RecordTime,
                             const vector<string>& ParticipantID, const string Result);
    //业务流程类声明为友元类
    friend class ControllerAbstractBase;
    //所有试管列表
    static vector<Tube*> AllTube;
    //系统初始试管信息
    static string SystemTubeID;
    static vector<string> SystemParticipantIDList;
    static DateTime SystemCollectTime;
    static DateTime SystemRecordTime;
    static string SystemResult;
    //试管类私有成员
    string m_TubeID;
    vector<string> m_ParticipantID;
    DateTime m_CollectTime;
    DateTime m_RecordTime;
    TubeResult m_Result;
    //只读所有试管列表
    static vector<Tube*>& ReadAllTube;
};
#endif