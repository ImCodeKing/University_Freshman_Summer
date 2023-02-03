/*************************************************************************
【文件名】DateTime.hpp
【功能模块和目的】日期时间类声明
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
#ifndef _DATETIME_HPP_
#define _DATETIME_HPP_
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;
//-----------------------------------------------------------------------------

/*************************************************************************
【类名】DateTime
【功能】核心日期时间类，日期时间对象的最基础类
【接口说明】
	构造函数DateTime(unsigned int Year = 1900u, unsigned int Month = 1u, unsigned int Day = 1u, unsigned int Hour = 0u,
	                 unsigned int Minute = 0u, unsigned int Second = 0u);
	拷贝构造函数DateTime(const DateTime& Source);
	赋值运算符重载DateTime& operator= (const DateTime& Source);
    析构virtual ~DateTime();
	函数static void SetYearRange(unsigned int MaxYear, unsigned int MinYear); 指定年份范围的函数，用于设定日期的合理范围
	函数bool IsLeapYear() const; 判断对象的日期年份是否为闰年
	函数bool IsBasicRight() const; 判断对象日期的最共有部分是否合理（年是否在范围内、月是否大于0小于12、日是否大于0小于31）
	函数bool IsValidDateTime() const; 判断对象的日期时间是否合理
	>>运算符重载 istream& operator>> (istream& Stream, DateTime& anDateTime);
	<<运算符重载 ostream& operator<< (ostream& Stream, const DateTime& anDateTime);
	>运算符重载 bool operator> (const DateTime& Source) const;
	<运算符重载 bool operator< (const DateTime& Source) const;
	==运算符重载 bool operator== (const DateTime& Source) const;
	!=运算符重载 bool operator!= (const DateTime& Source) const;
	const unsigned int& Year; 日期时间中年的常引用
	const unsigned int& Month; 日期时间中月的常引用
	const unsigned int& Day; 日期时间中日的常引用
	const unsigned int& Hour; 日期时间中时的常引用
	const unsigned int& Minute; 日期时间中分的常引用
	const unsigned int& Second; 日期时间中秒的常引用
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
class DateTime
{
public:
	DateTime(unsigned int Year = 1900u, unsigned int Month = 1u, unsigned int Day = 1u, unsigned int Hour = 0u,
	         unsigned int Minute = 0u, unsigned int Second = 0u);
	DateTime(const DateTime& Source);
	DateTime& operator= (const DateTime& Source);
	virtual ~DateTime();
	//指定年份范围的函数
	static void SetYearRange(unsigned int MaxYear, unsigned int MinYear);
	//判断年份是否为闰年的非静态函数声明
	bool IsLeapYear() const;
	//判断日期最共有部分是否符合规范的非静态函数声明
	bool IsBasicRight() const;
	//判断日期是否符合规范的非静态函数声明
	bool IsValidDateTime() const;
	// >>运算符重载
	friend istream& operator>> (istream& Stream, DateTime& anDateTime);
	// <<运算符重载
	friend ostream& operator<< (ostream& Stream, const DateTime& anDateTime);
	//大于号运算符重载
	bool operator> (const DateTime& Source) const;
	//小于号运算符重载
	bool operator< (const DateTime& Source) const;
	//等于号运算符重载
	bool operator== (const DateTime& Source) const;
	//不等于号运算符重载
	bool operator!= (const DateTime& Source) const;
	//常引用列表
	const unsigned int& Year;
	const unsigned int& Month;
	const unsigned int& Day;
	const unsigned int& Hour;
	const unsigned int& Minute;
	const unsigned int& Second;
private:
	//年
	unsigned int m_uYear;
	//月
	unsigned int m_uMonth;
	//日
	unsigned int m_uDay;
	//时
	unsigned int m_uHour;
	//分
	unsigned int m_uMinute;
	//秒
	unsigned int m_uSecond;
	//年份设置上限
	static unsigned int uUpperYear;
	//年份设置下限
	static unsigned int uLowerYear;
	//不同年中每月的天数数组
	static unsigned int uDayInMonths[2][12];
};
#endif