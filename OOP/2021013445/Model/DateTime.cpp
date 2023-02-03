/*************************************************************************
【文件名】DateTime.cpp
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
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "DateTime.hpp"
using namespace std;
//-----------------------------------------------------------------------------
//静态成员定义
unsigned int DateTime::uUpperYear = 9999u;
unsigned int DateTime::uLowerYear = 1900u;
unsigned int DateTime::uDayInMonths[2][12] = { {31u, 28u, 31u, 30u, 31u, 30u, 31u, 31u, 30u, 31u, 30u, 31u},
										  {31u, 29u, 31u, 30u, 31u, 30u, 31u, 31u, 30u, 31u, 30u, 31u} };
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】bool DateTime::SetYearRange(unsigned int uMaxYear, unsigned int uMinYear)
【函数功能】静态函数，设置年份范围
【参数】MaxYear：最大年份；MinYear：最小年份
【返回值】布尔值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
void DateTime::SetYearRange(unsigned int uMaxYear, unsigned int uMinYear)
{
	//如果最大值年份小于最小值年份
	if (uMaxYear < uMinYear)
	{
		throw invalid_argument("The MaxYear should be after the MinYear.");
	}
	uUpperYear = uMaxYear;
	uLowerYear = uMinYear;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】DateTime::DateTime(unsigned int uYear, unsigned int uMonth, unsigned int uDay, unsigned int uHour, 
                               unsigned int uMinute, unsigned int uSecond)
【函数功能】构造函数，构造一个日期时间类的对象，默认设置为1900-01-01 00:00:00
【参数】Year：年；Month：月；Day：日；Hour：时；Minute：分；Second：秒
【返回值】构造函数不可返回值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
DateTime::DateTime(unsigned int uYear, unsigned int uMonth, unsigned int uDay, unsigned int uHour, unsigned int uMinute, 
	      unsigned int uSecond) : Year(m_uYear), Month(m_uMonth), Day(m_uDay), Hour(m_uHour), Minute(m_uMinute), Second(m_uSecond)
{
	m_uYear = uYear;
	m_uMonth = uMonth;
	m_uDay = uDay;
	m_uHour = uHour;
	m_uMinute = uMinute;
	m_uSecond = uSecond;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】DateTime::DateTime(const DateTime& Source)
【函数功能】拷贝构造函数，暂无深拷贝，留下接口以便后续维护
【参数】Source：被拷贝的日期时间类对象
【返回值】拷贝函数不可返回值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
DateTime::DateTime(const DateTime& Source) : Year(m_uYear), Month(m_uMonth), Day(m_uDay), 
                                             Hour(m_uHour), Minute(m_uMinute), Second(m_uSecond)
{
	m_uYear = Source.Year;
	m_uMonth = Source.Month;
	m_uDay = Source.Day;
	m_uHour = Source.Hour;
	m_uMinute = Source.Minute;
	m_uSecond = Source.Second;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】DateTime& DateTime::operator=(const DateTime& Source)
【函数功能】赋值运算符重载，暂无深拷贝，留下接口以便后续维护
【参数】Source：用于赋值日期时间类对象
【返回值】拷贝函数不可返回值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
DateTime& DateTime::operator=(const DateTime& Source)
{
	if (this != &Source)
	{
		m_uYear = Source.Year;
		m_uMonth = Source.Month;
		m_uDay = Source.Day;
		m_uHour = Source.Hour;
		m_uMinute = Source.Minute;
		m_uSecond = Source.Second;
	}
	return *this;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】DateTime::~DateTime()
【函数功能】析构函数
【参数】无
【返回值】析构函数不可有返回值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
DateTime::~DateTime()
{
	;//空
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】bool DateTime::IsLeapYear() const
【函数功能】判断对象的年份是否为闰年
【参数】无
【返回值】布尔值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
bool DateTime::IsLeapYear() const
{
	//年份可以整除400 或 年份可以整除四但不可以整除100
	return !(Year % 400u) || (!(Year % 4u) && (Year % 100u));
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】bool DateTime::IsBasicRight() const
【函数功能】判断对象日期的最共有部分是否合理（年是否在范围内、月是否大于0小于12、日是否大于0小于31）
【参数】无
【返回值】布尔值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
bool DateTime::IsBasicRight() const
{
	//年不在范围内
	if (Year > uUpperYear || Year < uLowerYear)
	{
		throw invalid_argument("The inserted Year is out of range.");
	}
	//月不在范围内
	else if (Month <= 0u || Month > 12u)
	{
		throw invalid_argument("The inserted Month is out of range.");
	}
	//日不在范围内
	else if (Day <= 0u && Day > 31u)
	{
		throw invalid_argument("The inserted Day is out of range.");
	}
	//时不在范围内
	else if (Hour < 0u || Hour > 23u)
	{
		throw invalid_argument("The inserted Hour is out of range.");
	}
	//分不在范围内
	else if (Minute < 0u || Minute > 60u)
	{
		throw invalid_argument("The inserted Minute is out of range.");
	}
	//分不在范围内
	else if (Second < 0u || Second > 60u)
	{
		throw invalid_argument("The inserted Second is out of range.");
	}
	return true;;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】bool DateTime::IsValidDateTime() const
【函数功能】判断对象的日期时间是否合理
【参数】无
【返回值】布尔值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
bool DateTime::IsValidDateTime() const
{
	//先判断日期最共有条件是否合理
	this->IsBasicRight();
	//闰年非闰年分类讨论，是否月中日期合理
	if (this->IsLeapYear())
	{
		//闰年用2月有29天的日历
		if (Day > uDayInMonths[1][Month - 1])
		{
			throw invalid_argument("The inserted Day is out of the Max range of its month.");
		}
	}
	else
	{
		//非闰年用2月有28天的日历
		if (Day > uDayInMonths[0][Month - 1])
		{
			throw invalid_argument("The inserted Day is out of the Max range of its month.");
		}
	}
	return true;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】istream& operator>> (istream& Stream, DateTime& anDateTime)
【函数功能】>>运算符重载
【参数】Stream：istream对象；anDateTime：调用>>运算符的日期时间类对象
【返回值】istream对象的引用
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
istream& operator>> (istream& Stream, DateTime& anDateTime)
{
	//清空缓冲区的垃圾员
	char cGarbo;
	Stream >> anDateTime.m_uYear >> cGarbo;
	Stream >> anDateTime.m_uMonth >> cGarbo;
	Stream >> anDateTime.m_uDay;
	Stream >> anDateTime.m_uHour >> cGarbo;
	Stream >> anDateTime.m_uMinute >> cGarbo;
	Stream >> anDateTime.m_uSecond;
	return Stream;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】ostream& operator<< (ostream& Stream, const DateTime& anDateTime)
【函数功能】<<运算符重载
【参数】Stream：ostream对象；anDateTime：调用<<运算符的被试者类对象
【返回值】ostream对象的引用
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
ostream& operator<< (ostream& Stream, const DateTime& anDateTime)
{
	//按YYYY-MM-DD HH:MM:SS的格式输出
	Stream << anDateTime.Year << '-' << setw(2) << setfill('0') << anDateTime.Month << '-'
		   << setw(2) << setfill('0') << anDateTime.Day << ' ' 
		   << setw(2) << setfill('0') << anDateTime.Hour << ':'
		   << setw(2) << setfill('0') << anDateTime.Minute << ':'
		   << setw(2) << setfill('0') << anDateTime.Second;
	return Stream;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】bool DateTime::operator> (const DateTime& Source) const
【函数功能】>运算符重载
【参数】Source：需要比较的日期时间类对象
【返回值】布尔值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
bool DateTime::operator> (const DateTime& Source) const
{
	//权重按照年、月、日、时、分、秒来对比
	if (Year > Source.Year)
	{
		return true;
	}
	else if (Year == Source.Year && Month > Source.Month)
	{
		return true;
	}
	else if (Year == Source.Year && Month == Source.Month && Day > Source.Day)
	{
		return true;
	}
	else if (Year == Source.Year && Month == Source.Month && Day == Source.Day && Hour > Source.Hour)
	{
		return true;
	}
	else if (Year == Source.Year && Month == Source.Month && Day == Source.Day && Hour == Source.Hour && Minute > Source.Minute)
	{
		return true;
	}
	else if (Year == Source.Year && Month == Source.Month && Day == Source.Day && Hour == Source.Hour && Minute == Source.Minute
		     && Second > Source.Second)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】bool DateTime::operator< (const DateTime& Source) const
【函数功能】<运算符重载
【参数】Source：需要比较的日期时间类对象
【返回值】布尔值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
bool DateTime::operator< (const DateTime& Source) const
{
	//权重按照年、月、日、时、分、秒来对比
	if (Year < Source.Year)
	{
		return true;
	}
	else if (Year == Source.Year && Month < Source.Month)
	{
		return true;
	}
	else if (Year == Source.Year && Month == Source.Month && Day < Source.Day)
	{
		return true;
	}
	else if (Year == Source.Year && Month == Source.Month && Day == Source.Day && Hour < Source.Hour)
	{
		return true;
	}
	else if (Year == Source.Year && Month == Source.Month && Day == Source.Day && Hour == Source.Hour && Minute < Source.Minute)
	{
		return true;
	}
	else if (Year == Source.Year && Month == Source.Month && Day == Source.Day && Hour == Source.Hour && Minute == Source.Minute
		&& Second < Source.Second)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】bool DateTime::operator== (const DateTime& Source) const
【函数功能】==运算符重载
【参数】Source：需要比较的日期时间类对象
【返回值】布尔值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
bool DateTime::operator== (const DateTime& Source) const
{
	//所有元素都要完全相同才可以返回真
	return (Year == Source.Year && Month == Source.Month && Day == Source.Day && Hour == Source.Hour && Minute == Source.Minute
		   && Second == Source.Second);
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】bool DateTime::operator!= (const DateTime& Source) const
【函数功能】!=运算符重载
【参数】Source：需要比较的日期时间类对象
【返回值】布尔值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
bool DateTime::operator!= (const DateTime& Source) const
{
	//==运算符的补集
	return !(Year == Source.Year && Month == Source.Month && Day == Source.Day && Hour == Source.Hour && Minute == Source.Minute
		&& Second == Source.Second);
}