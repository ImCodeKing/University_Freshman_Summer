/*************************************************************************
【文件名】Participant.cpp
【功能模块和目的】被试者类静态成员初始化和函数定义
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
#include "DateTime.hpp"
#include "Tube.hpp"
using namespace std;
//-----------------------------------------------------------------------------

//静态成员初始化
vector<string> Participant::AdminIDNum{ "620103200302042122", "62010320030204161x" };
vector<string> Participant::AdminName{ "李昭阳","lzy" };
vector<string> Participant::AdminPassword{ "123", "123" };
UsersType Participant::AdminType = UsersType::Admin;
vector<Participant*> Participant::AllParticipants = {};
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】Participant:: ~Participant()
【函数功能】析构函数
【参数】无
【返回值】析构函数不可有返回值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
Participant:: ~Participant()
{
    ;//空
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】Participant::Participant(const string& IDNum, const string& Name, const string& Password)
【函数功能】被试者类的构造函数，判断所给身份证号是否合理和唯一，创建一个新的被试者类对象
【参数】IDNum：所给对象身份证号；Name：所给对象名字；Password：所给对象密码
【返回值】构造函数不可有返回值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
Participant::Participant(const string& IDNum, const string& Name, const string& Password) :
    IDNum(m_IDNum), Name(m_Name), Type(m_Type)
{
    //判断身份证号是否合理
    if (!IsIDNumValid(IDNum))
    {
        throw -1;//invalid_argument("The ID number is invalid.");
    }
    //判断身份证号是否存在
    for (const auto& n : AllParticipants)
    {
        if (n->IsIDNumSole(IDNum))
        {
            throw 1u;//invalid_argument("ID number existed.");
        }
    }
    m_IDNum = IDNum;
    m_Name = Name;
    m_Password = Password;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】bool Participant::IsIDNumValid(const string& Source)
【函数功能】静态函数，判断所给身份证号是否合理
【参数】Source：需要被判断是否合理的身份证号
【返回值】布尔值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
bool Participant::IsIDNumValid(const string& Source)
{
    if (Source.length() == 18)
    {
        //判断身份证号前17位是否为数字，最后一位是否为X
        for (int i = 0; i < 17; i++)
        {
            if (Source[i] < '0' || Source[i] > '9')
            {
                return false;
            }
        }
        //判断并返回身份证号最后一位是否为x或数字
        return (Source[17] == 'X' || Source[17] == 'x' || (Source[17] >= '0' && Source[17] <= '9'));
    }
    //在第一次读取文件写入列表时发挥作用
    if (Source == "SystemIDNum")
    {
        return true;
    }
    return false;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】bool Participant::IsIDNumSole(const string& Source) const
【函数功能】判断所给身份证号在被试者列表中是否唯一
【参数】Source：需要被判断是否唯一的身份证号
【返回值】布尔值
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
bool Participant::IsIDNumSole(const string& Source) const
{
    //比对自己的身份证号和参数列表中给的身份证号是否一致
    return IDNum == Source;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】istream& operator>>(istream& Stream, Participant& anParticipant)
【函数功能】>>运算符重载
【参数】Stream：istream对象；anParticipant：调用>>运算符的被试者类对象
【返回值】istream对象的引用
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
istream& operator>>(istream& Stream, Participant& anParticipant)
{
    string TheType;
    //写入身份证号、姓名、密码
    Stream >> anParticipant.m_IDNum >> anParticipant.m_Name >> anParticipant.m_Password >> TheType;
    //根据字符串写入的用户类型，转换为UsersType型数据
    if (TheType == "Trival")
    {
        anParticipant.m_Type = UsersType::Trival;
    }
    else if (TheType == "Admin")
    {
        anParticipant.m_Type = UsersType::Admin;
    }
    else if (TheType == "Collector")
    {
        anParticipant.m_Type = UsersType::Collector;
    }
    else if (TheType == "Recorder")
    {
        anParticipant.m_Type = UsersType::Recorder;
    }
    else if (TheType == "CollectorAndRecorder")
    {
        anParticipant.m_Type = UsersType::CollectorAndRecorder;
    }
    else if (TheType == "AdminAndCollector")
    {
        anParticipant.m_Type = UsersType::AdminAndCollector;
    }
    else if (TheType == "AdminAndRecorder")
    {
        anParticipant.m_Type = UsersType::AdminAndRecorder;
    }
    else if (TheType == "AdminAndCollectorAndRecorder")
    {
        anParticipant.m_Type = UsersType::AdminAndCollectorAndRecorder;
    }
    else
    {
        throw invalid_argument("Unknown Type.");
    }
    return Stream;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】ostream& operator<<(ostream& Stream, const Participant& anParticipant)
【函数功能】<<运算符重载
【参数】Stream：ostream对象；anParticipant：调用<<运算符的被试者类对象
【返回值】ostream对象的引用
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
ostream& operator<<(ostream& Stream, const Participant& anParticipant)
{
    //写出身份证号、姓名、密码
    Stream << anParticipant.IDNum << ' ' << anParticipant.Name << ' ' << anParticipant.m_Password << ' ';
    //根据UsersType型数据，转换为字符串输出
    if (anParticipant.Type == UsersType::Trival)
    {
        Stream << "Trival";
    }
    else if (anParticipant.Type == UsersType::Admin)
    {
        Stream << "Admin";
    }
    else if (anParticipant.Type == UsersType::Collector)
    {
        Stream << "Collector";
    }
    else if (anParticipant.Type == UsersType::Recorder)
    {
        Stream << "Recorder";
    }
    else if (anParticipant.Type == UsersType::CollectorAndRecorder)
    {
        Stream << "CollectorAndRecorder";
    }
    else if (anParticipant.Type == UsersType::AdminAndCollector)
    {
        Stream << "AdminAndCollector";
    }
    else if (anParticipant.Type == UsersType::AdminAndRecorder)
    {
        Stream << "AdminAndRecorder";
    }
    else if (anParticipant.Type == UsersType::AdminAndCollectorAndRecorder)
    {
        Stream << "AdminAndCollectorAndRecorder";
    }
    return Stream;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】void Participant::ChangePassword(const string& NewPassord)
【函数功能】更改用户密码
【参数】NewPassword：新的密码
【返回值】无
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
void Participant::ChangePassword(const string& NewPassord)
{
    m_Password = NewPassord;
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】Participant* Participant::Verify(const string& TheIDNum, const string& ThePassword)
【函数功能】在已有被试者列表中寻找与所给身份证号匹配的被试者，并比对密码是否一致
【参数】TheIDNum：需要比对的身份证号；ThePassword：需要比对的密码
【返回值】被试者类对象的指针
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
Participant* Participant::Verify(const string& TheIDNum, const string& ThePassword)
{
    //身份证号对比标准
    auto Finder = [&TheIDNum](Participant* ptr)->bool {return (ptr->IDNum == TheIDNum); };
    //找到身份证号的
    auto it = find_if(AllParticipants.begin(), AllParticipants.end(), Finder);
    //没有找到用户
    if (it == AllParticipants.end()) 
    {
        throw -1;
    }
    //错误密码
    else if ((*it)->m_Password != ThePassword) 
    {
        throw 1u;
    }
    //返回用户指针
    else 
    {
        return *it;
    }
}
//-----------------------------------------------------------------------------


/*************************************************************************
【函数名称】void Participant::AddParticipant(const string& IDNum, const string& Name, const string& Password)
【函数功能】静态函数，创建一个新的被试者类对象，并把这个对象加入所有被试者列表中
【参数】IDNum：新建用户的身份证号；Name：新建用户的名字；Password：新建用户的密码
【返回值】无
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
void Participant::AddParticipant(const string& IDNum, const string& Name, const string& Password)
{
    //创建一个新用户
    Participant* pNewParticipant = new Participant(IDNum, Name, Password);
    pNewParticipant->m_Type = UsersType::Trival;
    //加入到所有被试者列表中
    AllParticipants.push_back(pNewParticipant);
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】void Participant::DeleteParticipant(const string& IDNum)
【函数功能】静态函数，将给定对象从所有被试者列表中移除，并将其动态调用的内存空间释放、指针置空
【参数】IDNum：新建用户的身份证号；
【返回值】无
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
void Participant::DeleteParticipant(const string& IDNum)
{
    unsigned int uCounter = 0;
    for (auto& n : AllParticipants)
    {
        //找到与身份证号相符的被试者
        if (n->IDNum == IDNum)
        {
            //从列表中清除
            AllParticipants.erase(AllParticipants.begin() + uCounter);
            //清除指针的内容
            delete n;
            //指针置空
            n = nullptr;
            return;
        }
        //用于计数所找的被试者是列表中的第几个
        uCounter++;
    }
    throw invalid_argument("Participant not existed.");
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】void Participant::LoadFromFile(const string& FileName)
【函数功能】静态函数，从所指定文件中读入被试者列表；如果没有找到文件，则新建一个文件，并把cpp文件中预置的管理员列表读入
【参数】FileName：指定读入的文件名
【返回值】无
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
void Participant::LoadFromFile(const string& FileName)
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
    unsigned int uParticipantsCount;
    File >> uParticipantsCount;
    //缓冲区清空
    File.get();
    //用户列表清空
    AllParticipants.clear();
    //如果一个用户都没有，先写入系统预制的Admin列表
    if (uParticipantsCount == 0)
    {
        if (AdminIDNum.size() == 0)
        {
            throw invalid_argument("No participant found. Please creat Admin first.");
        }
        else
        {
            InitializeAdmin();
            SaveToFile(FileName);
        }
    }
    else
    {
        //如果有用户
        for (unsigned int i = 0; i < uParticipantsCount; i++)
        {
            //先创建一个系统化的被试者对象
            AddParticipant("SystemIDNum", "SystemName", "SystemPassword");
            //从文件中读入每个被试者对象的具体数据
            File >> *(*(AllParticipants.end() - 1));
        }
    }
    File.close();
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】void Participant::SaveToFile(const string& FileName)
【函数功能】静态函数，将被试者列表保存到指定文件中
【参数】FileName：指定保存的文件名；
【返回值】无
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
void Participant::SaveToFile(const string& FileName)
{
    //打开或新建一个FileName的文件
    ofstream File(FileName);
    //如果不能打开
    if (!File.is_open())
    {
        throw invalid_argument("Can't open/Create for saving, File : " + FileName);
    }
    auto Saver = [&File](Participant* pPtrOfParticipant) {File << *pPtrOfParticipant << endl; };
    //先存放所有用户的数量
    File << AllParticipants.size() << endl;
    //存放每个用户的数据
    for_each(AllParticipants.begin(), AllParticipants.end(), Saver);
    //保存到系统
    File.close();
}
//-----------------------------------------------------------------------------

/*************************************************************************
【函数名称】void Participant::InitializeAdmin()
【函数功能】静态函数，加载管理员列表到被试者列表，在新建文件时被调用
【参数】无
【返回值】无
【开发者及日期】李昭阳(lizhaoya21@mails.tsinghua.edu.cn) 2022-7-7
【更改记录】
*************************************************************************/
void Participant::InitializeAdmin()
{
    for (unsigned int i = 0; i < AdminIDNum.size(); i++)
    {
        //初始化系统预置的管理员进入到被试者列表中，可以修改cpp中的静态变量来改变
        Participant* pNewAdmin = new Participant(AdminIDNum[i], AdminName[i], AdminPassword[i]);
        pNewAdmin->m_Type = UsersType::Admin;
        AllParticipants.push_back(pNewAdmin);
    }
}
//-----------------------------------------------------------------------------