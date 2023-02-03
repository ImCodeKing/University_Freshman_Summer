/*************************************************************************
���ļ�����DateTime.hpp
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
��������DateTime
�����ܡ���������ʱ���࣬����ʱ�������������
���ӿ�˵����
	���캯��DateTime(unsigned int Year = 1900u, unsigned int Month = 1u, unsigned int Day = 1u, unsigned int Hour = 0u,
	                 unsigned int Minute = 0u, unsigned int Second = 0u);
	�������캯��DateTime(const DateTime& Source);
	��ֵ���������DateTime& operator= (const DateTime& Source);
    ����virtual ~DateTime();
	����static void SetYearRange(unsigned int MaxYear, unsigned int MinYear); ָ����ݷ�Χ�ĺ����������趨���ڵĺ���Χ
	����bool IsLeapYear() const; �ж϶������������Ƿ�Ϊ����
	����bool IsBasicRight() const; �ж϶������ڵ���в����Ƿ�������Ƿ��ڷ�Χ�ڡ����Ƿ����0С��12�����Ƿ����0С��31��
	����bool IsValidDateTime() const; �ж϶��������ʱ���Ƿ����
	>>��������� istream& operator>> (istream& Stream, DateTime& anDateTime);
	<<��������� ostream& operator<< (ostream& Stream, const DateTime& anDateTime);
	>��������� bool operator> (const DateTime& Source) const;
	<��������� bool operator< (const DateTime& Source) const;
	==��������� bool operator== (const DateTime& Source) const;
	!=��������� bool operator!= (const DateTime& Source) const;
	const unsigned int& Year; ����ʱ������ĳ�����
	const unsigned int& Month; ����ʱ�����µĳ�����
	const unsigned int& Day; ����ʱ�����յĳ�����
	const unsigned int& Hour; ����ʱ����ʱ�ĳ�����
	const unsigned int& Minute; ����ʱ���зֵĳ�����
	const unsigned int& Second; ����ʱ������ĳ�����
�������߼����ڡ�������(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
�����ļ�¼��
*************************************************************************/
class DateTime
{
public:
	DateTime(unsigned int Year = 1900u, unsigned int Month = 1u, unsigned int Day = 1u, unsigned int Hour = 0u,
	         unsigned int Minute = 0u, unsigned int Second = 0u);
	DateTime(const DateTime& Source);
	DateTime& operator= (const DateTime& Source);
	virtual ~DateTime();
	//ָ����ݷ�Χ�ĺ���
	static void SetYearRange(unsigned int MaxYear, unsigned int MinYear);
	//�ж�����Ƿ�Ϊ����ķǾ�̬��������
	bool IsLeapYear() const;
	//�ж�������в����Ƿ���Ϲ淶�ķǾ�̬��������
	bool IsBasicRight() const;
	//�ж������Ƿ���Ϲ淶�ķǾ�̬��������
	bool IsValidDateTime() const;
	// >>���������
	friend istream& operator>> (istream& Stream, DateTime& anDateTime);
	// <<���������
	friend ostream& operator<< (ostream& Stream, const DateTime& anDateTime);
	//���ں����������
	bool operator> (const DateTime& Source) const;
	//С�ں����������
	bool operator< (const DateTime& Source) const;
	//���ں����������
	bool operator== (const DateTime& Source) const;
	//�����ں����������
	bool operator!= (const DateTime& Source) const;
	//�������б�
	const unsigned int& Year;
	const unsigned int& Month;
	const unsigned int& Day;
	const unsigned int& Hour;
	const unsigned int& Minute;
	const unsigned int& Second;
private:
	//��
	unsigned int m_uYear;
	//��
	unsigned int m_uMonth;
	//��
	unsigned int m_uDay;
	//ʱ
	unsigned int m_uHour;
	//��
	unsigned int m_uMinute;
	//��
	unsigned int m_uSecond;
	//�����������
	static unsigned int uUpperYear;
	//�����������
	static unsigned int uLowerYear;
	//��ͬ����ÿ�µ���������
	static unsigned int uDayInMonths[2][12];
};
#endif