/*************************************************************************
【文件名】Tube.cpp
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
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <fstream>
#include <iostream>
#include "DateTime.hpp"
#include "Tube.hpp"
using namespace std;
//-----------------------------------------------------------------------------

//静态成员初始化
vector<Tube*> Tube::AllTube = {};
string Tube::SystemTubeID = { "20000101000000000000" };
vector<string> Tube::SystemParticipantIDList{};
DateTime Tube::SystemCollectTime{};
DateTime Tube::SystemRecordTime{};
string Tube::SystemResult{"WaitingForResult"};
vector<Tube*>& Tube::ReadAllTube{AllTube};
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】Tube::~Tube()
【函数功能】析构函数
【参数】无
【返回值】析构函数不可返回值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
Tube::~Tube()
{
	;//空
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】Tube::Tube(const string& TubeID, const DateTime& CollectTime, const DateTime& RecordTime,
                       const vector<string>& ParticipantID, const TubeResult Result)
【函数功能】构造函数，根据所给的试管编号、采集时间、录入时间、被试者身份证号列表、核酸结果创建新的试管对象
【参数】TubeID：试管编号；CollectTime：采集时间；RecordTime：录入时间；ParticipantID：被试者身份证号列表；Result：核酸结果
【返回值】构造函数不可返回值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
Tube::Tube(const string& TubeID, const DateTime& CollectTime, const DateTime& RecordTime,
      const vector<string>& ParticipantID, const TubeResult Result) :
      TubeID(m_TubeID), CollectTime(m_CollectTime), RecordTime(m_RecordTime), 
      ParticipantID(m_ParticipantID), Result(m_Result)
{
    //如果试管编号不符合规范
    if (!IsTubeIDValid)
    {
        throw invalid_argument("Invalid Tube ID.");
    }
    m_TubeID = TubeID;
    m_CollectTime = CollectTime;
    m_RecordTime = RecordTime;
    m_ParticipantID = ParticipantID;
    m_Result = Result;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】istream& operator>>(istream& Stream, Tube& anTube)
【函数功能】>>运算符重载
【参数】Stream：istream对象；anTube：调用>>运算符的试管类对象
【返回值】istream对象的引用
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
istream& operator>>(istream& Stream, Tube& anTube)
{
    string TheTubeResult;
    unsigned int uParticipantCount;
    string Temp;
    //写入试管编号、采集时间、录入时间、结果、试管被试者列表人数
    Stream >> anTube.m_TubeID >> anTube.m_CollectTime >> anTube.m_RecordTime >> TheTubeResult >> uParticipantCount;
    //字符串结果转变为为TubeResult结果
    if (TheTubeResult == "Positive")
    {
        anTube.m_Result = TubeResult::Positive;
    }
    else if (TheTubeResult == "Negative")
    {
        anTube.m_Result = TubeResult::Negative;
    }
    else if (TheTubeResult == "WaitingForResult")
    {
        anTube.m_Result = TubeResult::WaitingForResult;
    }
    else
    {
        throw invalid_argument("Unknown Result.");
    }
    for (unsigned int i = 0; i < uParticipantCount; i++)
    {
        Stream >> Temp;
        (anTube.m_ParticipantID).push_back(Temp);
    }
    return Stream;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】ostream& operator<<(ostream& Stream, const Tube& anTube)
【函数功能】<<运算符重载
【参数】Stream：ostream对象；anTube：调用<<运算符的试管类对象
【返回值】ostream对象的引用
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
ostream& operator<<(ostream& Stream, const Tube& anTube)
{
    //写出试管编号、采集时间、录入时间
    Stream << anTube.TubeID << ' ' << anTube.CollectTime << ' ' << anTube.RecordTime << ' ';
    //根据TubeResult结果转化为字符串结果输出
    if (anTube.Result == TubeResult::Positive)
    {
        Stream << "Positive" << ' ';
    }
    else if (anTube.Result == TubeResult::Negative)
    {
        Stream << "Negative" << ' ';
    }
    else if (anTube.Result == TubeResult::WaitingForResult)
    {
        Stream << "WaitingForResult" << ' ';
    }
    //输出试管被试者列表人数
    Stream << (anTube.ParticipantID).size() << ' ';
    //输出试管被试者列表
    for (unsigned int i = 0; i < (anTube.ParticipantID).size(); i++)
    {
        Stream << anTube.ParticipantID[i] << ' ';
    }
    return Stream;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】void Tube::LoadTubeData(const string& TubeID, const DateTime& CollectTime, const DateTime& RecordTime,
                                    const vector<string>& ParticipantID, const string Result)
【函数功能】创建一个新的试管类对象，并把它加入到所有试管列表中
【参数】TubeID：试管编号；CollectTime：采集时间；RecordTime：录入时间；ParticipantID：被试者身份证号列表；Result：核酸结果
【返回值】无
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
void Tube::LoadTubeData(const string& TubeID, const DateTime& CollectTime, const DateTime& RecordTime,
                        const vector<string>& ParticipantID, const string Result)
{
    //新建一个试管对象并加入试管列表
    Tube* pNewTube = new Tube(TubeID, CollectTime, RecordTime, ParticipantID);
    if (Result == "Positive")
    {
        pNewTube->m_Result = TubeResult::Positive;
    }
    else if (Result == "Negative")
    {
        pNewTube->m_Result = TubeResult::Negative;
    }
    else if (Result == "WaitingForResult")
    {
        pNewTube->m_Result = TubeResult::WaitingForResult;
    }
    AllTube.push_back(pNewTube);
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】void Tube:: LoadFromFile(const string& FileName)
【函数功能】静态函数，从所指定文件中读入试管列表；如果没有找到文件，则新建一个文件
【参数】FileName：指定读入的文件名
【返回值】无
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
void Tube:: LoadFromFile(const string& FileName)
{
    ifstream File(FileName);
    //如果无法打开文件
    if (!File.is_open())
    {
        //新建一个文件
        ofstream NewFile(FileName);
        //如果新建失败
        if (!NewFile.is_open())
        {
            throw invalid_argument("Can't open/create for loading, file: " + FileName);
        }
        NewFile << 0 << endl;
        //保存到系统
        NewFile.close();
        //将新建好的文件打开
        File.open(FileName);
    }
    unsigned int uTubeCount;
    File >> uTubeCount;
    //缓冲区清空
    File.get();
    //试管列表清空
    AllTube.clear();
    for (unsigned int i = 0; i < uTubeCount; i++)
    {
        //新建一个系统试管，然后从文件中读入精确数据
        LoadTubeData(SystemTubeID, SystemCollectTime, SystemRecordTime, SystemParticipantIDList, SystemResult);
        File >> *(*(AllTube.end() - 1));
    }
    File.close();
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】void Tube::SaveToFile(const string& FileName)
【函数功能】静态函数，将试管列表保存到指定文件中
【参数】FileName：指定保存的文件名；
【返回值】无
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
void Tube::SaveToFile(const string& FileName)
{
    //打开或新建一个FileName的文件
    ofstream File(FileName);
    //如果不能打开
    if (!File.is_open())
    {
        throw invalid_argument("Can't open/Create for saving, File : " + FileName);
    }
    auto Saver = [&File](Tube* pPtrOfTube) {File << *pPtrOfTube << endl; };
    //先存放所有用户的数量
    File << AllTube.size() << endl;
    //存放每个用户的数据
    for_each(AllTube.begin(), AllTube.end(), Saver);
    //保存到系统
    File.close();
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】bool Tube::IsTubeIDValid(const string& TubeID)
【函数功能】静态函数，检测试管编号是否合理（20位）
【参数】TubeID：试管编号
【返回值】布尔值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
bool Tube::IsTubeIDValid(const string& TubeID)
{
    //试管编号应该为20位
    return TubeID.size() == 20;
}
//-----------------------------------------------------------------------------

