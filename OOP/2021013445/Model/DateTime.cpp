/*************************************************************************
���ļ�����DateTime.cpp
������ģ���Ŀ�ġ�����ʱ��������
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
#include <iomanip>
#include "DateTime.hpp"
using namespace std;
//-----------------------------------------------------------------------------
//��̬��Ա����
unsigned int DateTime::uUpperYear = 9999u;
unsigned int DateTime::uLowerYear = 1900u;
unsigned int DateTime::uDayInMonths[2][12] = { {31u, 28u, 31u, 30u, 31u, 30u, 31u, 31u, 30u, 31u, 30u, 31u},
										  {31u, 29u, 31u, 30u, 31u, 30u, 31u, 31u, 30u, 31u, 30u, 31u} };
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�bool DateTime::SetYearRange(unsigned int uMaxYear, unsigned int uMinYear)
���������ܡ���̬������������ݷ�Χ
��������MaxYear�������ݣ�MinYear����С���
������ֵ������ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
void DateTime::SetYearRange(unsigned int uMaxYear, unsigned int uMinYear)
{
	//������ֵ���С����Сֵ���
	if (uMaxYear < uMinYear)
	{
		throw invalid_argument("The MaxYear should be after the MinYear.");
	}
	uUpperYear = uMaxYear;
	uLowerYear = uMinYear;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�DateTime::DateTime(unsigned int uYear, unsigned int uMonth, unsigned int uDay, unsigned int uHour, 
                               unsigned int uMinute, unsigned int uSecond)
���������ܡ����캯��������һ������ʱ����Ķ���Ĭ������Ϊ1900-01-01 00:00:00
��������Year���ꣻMonth���£�Day���գ�Hour��ʱ��Minute���֣�Second����
������ֵ�����캯�����ɷ���ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
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
���������ơ�DateTime::DateTime(const DateTime& Source)
���������ܡ��������캯����������������½ӿ��Ա����ά��
��������Source��������������ʱ�������
������ֵ�������������ɷ���ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
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
���������ơ�DateTime& DateTime::operator=(const DateTime& Source)
���������ܡ���ֵ��������أ�������������½ӿ��Ա����ά��
��������Source�����ڸ�ֵ����ʱ�������
������ֵ�������������ɷ���ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
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
���������ơ�DateTime::~DateTime()
���������ܡ���������
����������
������ֵ���������������з���ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
DateTime::~DateTime()
{
	;//��
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�bool DateTime::IsLeapYear() const
���������ܡ��ж϶��������Ƿ�Ϊ����
����������
������ֵ������ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
bool DateTime::IsLeapYear() const
{
	//��ݿ�������400 �� ��ݿ��������ĵ�����������100
	return !(Year % 400u) || (!(Year % 4u) && (Year % 100u));
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�bool DateTime::IsBasicRight() const
���������ܡ��ж϶������ڵ���в����Ƿ�������Ƿ��ڷ�Χ�ڡ����Ƿ����0С��12�����Ƿ����0С��31��
����������
������ֵ������ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
bool DateTime::IsBasicRight() const
{
	//�겻�ڷ�Χ��
	if (Year > uUpperYear || Year < uLowerYear)
	{
		throw invalid_argument("The inserted Year is out of range.");
	}
	//�²��ڷ�Χ��
	else if (Month <= 0u || Month > 12u)
	{
		throw invalid_argument("The inserted Month is out of range.");
	}
	//�ղ��ڷ�Χ��
	else if (Day <= 0u && Day > 31u)
	{
		throw invalid_argument("The inserted Day is out of range.");
	}
	//ʱ���ڷ�Χ��
	else if (Hour < 0u || Hour > 23u)
	{
		throw invalid_argument("The inserted Hour is out of range.");
	}
	//�ֲ��ڷ�Χ��
	else if (Minute < 0u || Minute > 60u)
	{
		throw invalid_argument("The inserted Minute is out of range.");
	}
	//�ֲ��ڷ�Χ��
	else if (Second < 0u || Second > 60u)
	{
		throw invalid_argument("The inserted Second is out of range.");
	}
	return true;;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�bool DateTime::IsValidDateTime() const
���������ܡ��ж϶��������ʱ���Ƿ����
����������
������ֵ������ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
bool DateTime::IsValidDateTime() const
{
	//���ж�������������Ƿ����
	this->IsBasicRight();
	//���������������ۣ��Ƿ��������ں���
	if (this->IsLeapYear())
	{
		//������2����29�������
		if (Day > uDayInMonths[1][Month - 1])
		{
			throw invalid_argument("The inserted Day is out of the Max range of its month.");
		}
	}
	else
	{
		//��������2����28�������
		if (Day > uDayInMonths[0][Month - 1])
		{
			throw invalid_argument("The inserted Day is out of the Max range of its month.");
		}
	}
	return true;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�istream& operator>> (istream& Stream, DateTime& anDateTime)
���������ܡ�>>���������
��������Stream��istream����anDateTime������>>�����������ʱ�������
������ֵ��istream���������
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
istream& operator>> (istream& Stream, DateTime& anDateTime)
{
	//��ջ�����������Ա
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
���������ơ�ostream& operator<< (ostream& Stream, const DateTime& anDateTime)
���������ܡ�<<���������
��������Stream��ostream����anDateTime������<<������ı����������
������ֵ��ostream���������
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
ostream& operator<< (ostream& Stream, const DateTime& anDateTime)
{
	//��YYYY-MM-DD HH:MM:SS�ĸ�ʽ���
	Stream << anDateTime.Year << '-' << setw(2) << setfill('0') << anDateTime.Month << '-'
		   << setw(2) << setfill('0') << anDateTime.Day << ' ' 
		   << setw(2) << setfill('0') << anDateTime.Hour << ':'
		   << setw(2) << setfill('0') << anDateTime.Minute << ':'
		   << setw(2) << setfill('0') << anDateTime.Second;
	return Stream;
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�bool DateTime::operator> (const DateTime& Source) const
���������ܡ�>���������
��������Source����Ҫ�Ƚϵ�����ʱ�������
������ֵ������ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
bool DateTime::operator> (const DateTime& Source) const
{
	//Ȩ�ذ����ꡢ�¡��ա�ʱ���֡������Ա�
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
���������ơ�bool DateTime::operator< (const DateTime& Source) const
���������ܡ�<���������
��������Source����Ҫ�Ƚϵ�����ʱ�������
������ֵ������ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
bool DateTime::operator< (const DateTime& Source) const
{
	//Ȩ�ذ����ꡢ�¡��ա�ʱ���֡������Ա�
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
���������ơ�bool DateTime::operator== (const DateTime& Source) const
���������ܡ�==���������
��������Source����Ҫ�Ƚϵ�����ʱ�������
������ֵ������ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
bool DateTime::operator== (const DateTime& Source) const
{
	//����Ԫ�ض�Ҫ��ȫ��ͬ�ſ��Է�����
	return (Year == Source.Year && Month == Source.Month && Day == Source.Day && Hour == Source.Hour && Minute == Source.Minute
		   && Second == Source.Second);
}
//-----------------------------------------------------------------------------

/*************************************************************************
���������ơ�bool DateTime::operator!= (const DateTime& Source) const
���������ܡ�!=���������
��������Source����Ҫ�Ƚϵ�����ʱ�������
������ֵ������ֵ
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
bool DateTime::operator!= (const DateTime& Source) const
{
	//==������Ĳ���
	return !(Year == Source.Year && Month == Source.Month && Day == Source.Day && Hour == Source.Hour && Minute == Source.Minute
		&& Second == Source.Second);
}