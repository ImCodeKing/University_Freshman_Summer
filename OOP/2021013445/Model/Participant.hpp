/*************************************************************************
【文件名】Participant.hpp
【功能模块和目的】被试者类声明
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
【类名】UsersType
【功能】枚举类，用户的各种身份类型
【接口说明】枚举类无接口
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
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
【类名】Participant
【功能】核心被试者类，被试者对象的最基础类
【接口说明】
    禁止无参构造、拷贝和赋值，已禁用默认构造函数、拷贝构造函数和赋值运算符
	对象密码应保持其类外不可见性，故不设置常引用只读形式
	构造函数Participant(const string& IDNum, const string& Name, const string& Password);构造一个被试者类对象，添加身份证号、姓名和密码信息
	析构virtual ~Participant();
	>>运算符重载 istream& operator>>(istream& Stream, Participant& anParticipant);
	<<运算符重载 ostream& operator<<(ostream& Stream, const Participant& anParticipant);
	函数void ChangePassword(const string& NewPassord); 修改被试者类对象的密码
	函数static bool IsIDNumValid(const string& Source); 静态函数，判断输入的身份证号是否合理
	函数bool IsIDNumSole(const string& Source) const; 非静态函数，判断输入的身份证号在用户列表中是否唯一
	函数static void AddParticipant(const string& IDNum, const string& Name, const string& Password); 静态函数，在被试者列表中加入新的被试者类对象
	函数static void DeleteParticipant(const string& IDNum); 静态函数，在被试者列表中删除所给的被试者类对象
	函数static void LoadFromFile(const string& FileName); 静态函数，从文件中加载初始化被试者列表
	函数static void SaveToFile(const string& FileName); 静态函数，将被试者列表保存到指定文件中
	函数static Participant* Verify(const string& TheIDNum, const string& ThePassword); 在被试者列表中查找指定被试者对象，并比对密码
	函数static void InitializeAdmin(); 初始化管理员列表，用于未发现指定文件时初始化被试者列表
	const string& IDNum; 对象身份证号的常引用
	const string& Name; 对象名字的常引用
	const UsersType& Type; 对象类型的常引用
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
class Participant
{
public:
	//默认构造函数删除
	Participant() = delete;
	//拷贝构造函数删除
	Participant(const Participant&) = delete;
	//赋值运算符删除
	Participant& operator=(const Participant&) = delete;
	//析构函数
	virtual ~Participant();
	// >>运算符重载
	friend istream& operator>>(istream& Stream, Participant& anParticipant);
	// <<运算符重载
	friend ostream& operator<<(ostream& Stream, const Participant& anParticipant);
	//更改密码函数
	void ChangePassword(const string& NewPassord);
	//检测身份证号是否合理的静态函数
	static bool IsIDNumValid(const string& Source);
	//检测身份证号是否唯一的非静态函数
	bool IsIDNumSole(const string& Source) const;
	//在整体列表中增加被试者
	static void AddParticipant(const string& IDNum, const string& Name, const string& Password);
	//在整体列表中注销被试者
	static void DeleteParticipant(const string& IDNum);
	//从文件中加载用户列表
	static void LoadFromFile(const string& FileName);
	//将用户列表保存到文件中
	static void SaveToFile(const string& FileName);
	//登录辅助函数（寻找并比对）
	static Participant* Verify(const string& TheIDNum, const string& ThePassword);
	//初始化管理员列表
	static void InitializeAdmin();
	//常引用
	const string& IDNum;
	const string& Name;
	const UsersType& Type;
private:
	//身份证号
	string m_IDNum;
	//名字
	string m_Name;
	//密码
	string m_Password;
	//被试者身份
	UsersType m_Type;
	//Participant类的构造函数
	Participant(const string& IDNum, const string& Name, const string& Password);
	//业务流程类声明为友元类
	friend class ControllerAbstractBase;
	//所有被试者列表
	static vector<Participant*> AllParticipants;
	//管理员的静态身份证号列表
	static vector<string> AdminIDNum;
	//管理员的静态名字列表
	static vector<string> AdminName;
	//管理员的静态密码列表
	static vector<string> AdminPassword;
	//管理员的静态身份
	static UsersType AdminType;
};
#endif