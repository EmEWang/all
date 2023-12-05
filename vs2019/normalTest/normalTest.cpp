// normalTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <math.h>
#include <windows.h>
#include <fstream>

using namespace std;
//macro如何将变量名转换为字符串，这就用到了define中的特殊标识符
//##是简单的连接符，#@用来给参数加单引号，#用来给参数加双引号即转成字符串。
#define Conn(x,y) x##y
#define ToChar(x) #@x
#define ToString(x) #x

#define CON1  if (i > 1) {cout << ">1"  << endl;} else {cout << "<=1"  << endl;}
#define CON2  if (i > 2) {cout << ">2"  << endl;} else {cout << "<=2"  << endl;}
#define CON3  if (i > 3) {cout << ">3"  << endl;} else {cout << "<=3"  << endl;}

#define PRINTF_T    0x01
#define LOG_T       0x02

#define EXEC_DATAFILE "select  a.name, nvl(b.phyrds,0) phyrds, nvl( b.phywrts, 0 ) phywrts, c.autoextensible, a.status, c.tablespace_name, \
					nvl(b.READTIM,0) READTIM, nvl( b.WRITETIM, 0 ) WRITETIM ,\
					trunc(decode(nvl(b.phyrds,0),0,0,nvl(b.READTIM,0)/b.phyrds *1000), 3) average_read_cost, \
					trunc(decode(nvl(b.PHYWRTS,0),0,0,nvl(b.WRITETIM,0)/b.PHYWRTS *1000), 3) average_write_cost \
				from v$datafile a, v$filestat b, dba_data_files c where a.file# = b.file# and a.file# = c.file_id order by c.tablespace_name, b.phyrds"


void printandlog(int type, const char* format, ...);

#define VAIARG(format, ...) {printf(format, ...);}

string varStr(const string &str, const string &toke = "::")
{
	return str + toke;
}


enum enum_t1{normal=0, warnning=1, error=2};

void testEnum(enum_t1 eu);
void testMacro();
void testMacro2();
void testMacro3();
void testString();
void testPtr();
void testDelete();  //重复删除
void testClass();   //成员布局 %p表示内存的16进制 不足的前面补零  注意 class::x 打印的offset object.x 打印内存中实际位置
void testMoreThanMax();
std::string timechange(const std::string strCurrentTime);

void stringMatch();
void stringreplace();

void testitoa();

using namespace std;
#include <map>

void testChar();

void testlonglong();

void testFile();
void testMem();

void testtime();

void teststring();
void teststring2();
void teststring3();
void teststring4();
void teststring5();

int main()
{
    //testString();

    //testEnum(warnning);
    //testEnum(error);
    //testMacro();
    //testMacro2();
    //testMacro3();
    //testPtr();
    //int i1 = 12;
    //std::cout << varStr(ToString(i1)) << endl;
    //testDelete();
    //testClass();

    //testMoreThanMax();

    //timechange("");

    //VAIARG("%d--%d", 11,22)
    //string ss = "abc";
    //printandlog(PRINTF_T, "[%s--%d][%s][%d]", __FUNCTION__, __LINE__, ss.c_str(), 123);


    //stringMatch();
    //stringreplace();
    //testitoa();
    //testChar();

    //testlonglong();

    //testFile();
    //testMem();
    testtime();

    //teststring();
    //teststring2();
    //teststring3();
    //teststring4();
    //teststring5();
    std::cout << "Hello World!\n";
}



void testMacro()
{
	printf("[func:%s--line:%4d] \n", __FUNCTION__, __LINE__);
	cout << "func:" << __FUNCTION__ << " line:" << __LINE__ << endl;
}

void testMacro2()
{
    int ii = 1;
    string str = "ssss";
    float ff = 1.1f;

    cout << ToString(ii) << ii << ToString(str) << str << ToString(ff) << ff << endl;

}

void testMacro3()
{
    int i = 2;
	CON1
	CON2
	CON3


}

void testEnum(enum_t1 eu)
{
    printf("enum:%d \n", eu);
    cout << eu << endl;
}

void testString()
{
    string s1= "1";
    string s2 = "2";

    string s3 = "0";
    string s4 = "0";
    if (s3 == s4)
	{
        cout << "equl" << endl;;
	}
    else
    {
        cout << "no equl" << endl;;
    }

    //cout << "equl:" << (s1 == s2) << endl;
}

void testPtr()
{
    int i = 1;
    void * ptr = NULL;
    void* ptr2 = &i;
    void* ptr3 = NULL;*(int*)(&ptr3) = 0x12345678;

    printf("[ptr]%#X[ptr2]%#X[ptr3]%#X\n", *(int*)(&ptr), *(int*)(&ptr2), *(int*)(&ptr3));
}


void testDelete()
{
    char* pc = new char[5];

    delete pc;
    delete pc;
}


void testClass()
{
    class AAA
    {
    public:
        int a;
        int b;
        int c;
    };

    AAA aaa;

    //printf("&AAA = %p\n", &AAA);
    printf("&AAA::a = %p\n", &AAA::a);
    printf("&AAA::b = %p\n", &AAA::b);
    printf("&AAA::c = %p\n", &AAA::c);
    printf("&aaa = %p\n", &aaa);
	printf("&aaa.a = %p\n", &aaa.a);
	printf("&aaa.b = %p\n", &aaa.b);
	printf("&aaa.c = %p\n", &aaa.c);
}

void testMoreThanMax()
{
    unsigned int nLen = pow(2, 32) - 5;
    unsigned char cLen = 110;

    while (1)
    {
        Sleep(200);
        printf("[] --- %u\n", cLen++);
    }

}

std::string timechange(const std::string strCurrentTime)
{
	int arrTime[6] = { 0 };
	int* pTime = arrTime;
	sscanf_s(strCurrentTime.c_str(),
		"%4d-%02d-%02d %02d:%02d:%02d",
		pTime, pTime + 1, pTime + 2, pTime + 3, pTime + 4, pTime + 5);

    char temp[20] = { 0 };
    sprintf_s(temp, "%4d-%02d-%02d %02d:%02d:%02d", *pTime, *(pTime + 1), *(pTime + 2), *(pTime + 3), *(pTime + 4), *(pTime + 5));
    std::cout << temp << std::endl;
    return temp;
}


void printandlog(int type, const char* format, ...)
{
	va_list al;
	va_start(al, format);
    if (type& PRINTF_T != 0)
    {
        fprintf(stdout, format, va_arg(al, const char*));
    }
    va_start(al, format);
	if (type & LOG_T != 0)
	{
        fprintf(stdout, "----\n");
		fprintf(stdout, format, va_arg(al, const char*));
	}
    va_end(al);
}

#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable: 4996)
void stringMatch()                                   //字符串中按照规定的格式选择字符 直到不匹配的字符停止 贪婪算法尽可能的多读
{
    string str = "ccu_1 - 1#123";

    char temp[100] = {0};
    sscanf(str.c_str(), "%[a-z]", temp);             //字符串中按照 a-z 范围选择字符
    string str1 = temp;

	sscanf(str.c_str(), "%[abcdefgu_]", temp);       //字符串中按照 abcdefgu_ 范围选择字符
	string str2 = temp;

	sscanf(str.c_str(), "%[^#]", temp);              //字符串中 直到第一个 # 字符 停止  不包含 #
	string str3 = temp;

	sscanf(str.c_str(), "%[a-z_1]", temp);           //字符串中按照 a-z以及_1 范围选择字符
	string str4 = temp;

    printf("[a-z]%s[abcdefgu_]%s[^#]%s[a-z_1]%s\n", str1.c_str(), str2.c_str(), str3.c_str(), str4.c_str());

    return ;
}

void stringreplace()
{
    char temp[10] = "12345";
    std::cout << "[origin]" << temp << std::endl;
    sprintf_s(temp, sizeof(temp), "%c", "%21");

    std::cout << "[modify]" << temp << std::endl;

    char c1 = '%21';
    char c2 = '%2A';
    char c3 = '%2D';
    char c4 = '%21';
    char c5 = '%21';
    char c6 = '%21';

}

void testitoa()
{
    char buff[100] = {0};
    cout << itoa(123, buff, 10) << endl;
}

void testChar()
{
    string str1 = "abc-";
    string str2 = "按不出";
    string str3 = str1 + str2;

    cout << "[len]" << str3.length()
        << "[size]" << str3.size()
        << "[c-len]" << str3.c_str()
        << "[c-len2]" <<(char*)(str3.c_str())
        << "[--]" << str3 << endl;
}

void testlonglong()
{
    long long ll = 123;
    long long ll2 = pow(2,35);
    unsigned long long llu = 123;
    unsigned long long llu2 = pow(2, 64) -1 ;

    long l = 123;
    unsigned long lu = 1234;

    printf("[lld]%lld\n", ll);
    printf("[lld]%lld\n", ll2);
    printf("[llu]%llu\n", llu);
    printf("[llu]%llu\n", llu2);

	printf("[ld]%ld\n", l);
	printf("[lu]%lu\n", lu);

    int i = 0;
    if (2 == (i = 2))
    {
        printf("[i=%d]!!!\n", i);
    }
}

void testFile()
{
    time_t now = time(0);
    ofstream fstr;
    fstr.open("11" , std::ifstream::binary);
    int a = 0x1234;
    string str = "1234";



    if (!fstr.is_open())
    {
        cout << "open file error" << endl;
        return;
    }

    fstr.clear();
    fstr.write((char *)&a,sizeof(a));
    fstr.write(str.c_str(), str.size());
    fstr.close();


    ofstream ifstr;
    //ifstr.open("12", ios::in);      // 不创建文件
    ifstr.open("12", ios::trunc);     // ios::out | ios::binary | ios::ate | ios::app | ios::trunc 都创建文件
    //ifstr.open("12", std::ifstream::binary);     // 创建文件
	if (!ifstr.is_open())
	{
		cout << "open file error" << endl;
		return;
	}
	ifstr.close();



}


void testMem()
{
    char a = 'c';
    char *p = new char[10];
    char* p2 = &a;

    printf("mem[a]%02X[pa]%02X\n", &a, p);
    printf("mem[a]%u[pa]%u\n", &a, p);

    return;
}
void testtime()
{
    string str = "2022-06-09 13:33:33";
	int year = 2000, month = 1, day = 1, hour = 1, minute = 1, second = 1;
    int ret = sscanf(str.c_str(), "%d-%02d-%02d %02d:%02d:%02d", &year, &month, &day, &hour, &minute, &second);

    time_t t = time(0);

    string str1 = ctime(&t);
    //string str2 = ctime(time(0));
}

void teststring()
{
    string str = "";
    printf("[str]%s[size]%d[len]%d\n", str.c_str(), str.size(), str.length());

    str = "1";
    printf("[str]%s[size]%d[len]%d\n", str.c_str(), str.size(), str.length());

	str = "12";
	printf("[str]%s[size]%d[len]%d\n", str.c_str(), str.size(), str.length());

	str = "123";
	printf("[str]%s[size]%d[len]%d\n", str.c_str(), str.size(), str.length());
}

void teststring2()
{
	string str = EXEC_DATAFILE;
	printf("[str]%s[size]%d[len]%d\n", str.c_str(), str.size(), str.length());
}

void teststring3()
{
	string str = "2010-01-01 01:01:01";
	int nYear = 0;
	int nMonth = 0;
	int nDay = 0;
	int nHour = 0;
	int nMinute = 0;
	int nSecond = 0;

    int nret = sscanf(str.c_str(), "%4d-%2d-%2d %2d:%2d:%2d", &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
	printf("[ret]%d[YYYY]%d[MONTH]%d[DAY]%d[hour]%d[min]%d[sec]%d\n", nret,nYear, nMonth, nDay, nHour, nMinute, nSecond);
}

void teststring4()
{
    string str = "abc fopen 123";
    if (str.find("fopen") != string::npos)
    {
        str.erase(str.find("fopen"), 1);        // 删除一个字符
    }
    cout << str << endl;
}

void teststring5()
{
    char ssc[10] = "hello";
    wchar_t ssc2[10] = L"hello";  //与窄字符相比，宽字符前面多了一个大写的L，这个L的作用就是告诉编译器，这个字符串按照宽字符来存储（一个字符占两个字节）

    wchar_t wc[10] = {0};        //宽字符
    char* pc = (char*)wc;
    char* pc2 = (char*)(wc+1);

    int len = pc2 - pc;



    // ANSIToUnicode
    const char* pcSource = "项目";
	int dwNum = MultiByteToWideChar(CP_ACP, 0, pcSource, -1, NULL, 0);
	if (dwNum <= 0)
	{
		return;
	}
	wchar_t* pwText;
	pwText = new wchar_t[dwNum + 1];
	if (!pwText)
	{
		return ;
	}

	int nRe = MultiByteToWideChar(CP_ACP, 0, pcSource, -1, pwText, dwNum);
	if (nRe != dwNum)
	{
		delete[]pwText;
		pwText = NULL;
		return ;
	}

    // UnicodeToUTF8
	int dwNum_ = WideCharToMultiByte(CP_UTF8, NULL, pwText, -1, NULL, 0, NULL, NULL);
	if (dwNum_ <= 0)
	{
		return ;
	}

	char* psText_;
	psText_ = (char*)malloc((dwNum_ + 1) * sizeof(char));
	if (!psText_)
	{
		return ;
	}

	nRe = WideCharToMultiByte(CP_UTF8, NULL, pwText, -1, psText_, dwNum_, NULL, NULL);
	if (nRe != dwNum_)
	{
		free(psText_);
		psText_ = NULL;
		return ;
	}


    //UTF8ToUnicode
	dwNum_ = MultiByteToWideChar(CP_UTF8, 0, psText_, -1, NULL, 0);
	if (dwNum_ <= 0)
	{
		return ;
	}

	wchar_t* pwText_2;
    pwText_2 = new wchar_t[dwNum_ + 1];
	if (!pwText_2)
	{
		return ;
	}

	nRe = MultiByteToWideChar(CP_UTF8, 0, psText_, -1, pwText_2, dwNum_);
	if (nRe != dwNum_)
	{
		delete[]pwText_2;
        pwText_2 = NULL;
		return ;
	}

    //UnicodeToANSI
	dwNum = WideCharToMultiByte(CP_OEMCP, NULL, pwText_2, -1, NULL, 0, NULL, FALSE);
	if (dwNum <= 0)
	{
		return ;
	}

	char* psText2;
    psText2 = new char[dwNum + 1];
	if (!psText2)
	{
		return ;
	}

	nRe = WideCharToMultiByte(CP_OEMCP, NULL, pwText_2, -1, psText2, dwNum, NULL, FALSE);
	if (dwNum != nRe)
	{
		delete[]psText2;
        psText2 = NULL;
		return ;
	}

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧:
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
