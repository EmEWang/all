

#include <stdio.h>
#include <stdlib.h>

#include <string>

#include "tinyxml.h"

using namespace std;

void testxml1();

int main()
{
	puts("----------XML Start----------");
	testxml1();
	puts("----------XML End----------");
	return 0;
}




void getName(TiXmlElement* elem, int index = 0)
{
	string space;
	for (int i = 0; i < index; ++i)
	{
		space += "  ";
	}
	printf("%sname=%s ", space.c_str(), elem->Value());
}

void getAttr(TiXmlElement* elem, int index = 0)
{
	string space;
	for (int i = 0; i < index; ++i)
	{
		space += "  ";
	}
	TiXmlAttribute *attr = elem->FirstAttribute();
	//printf("%s", space.c_str());
	while (attr)
	{
		printf("  key=%s value =%s", attr->Name(), attr->Value());
		attr = attr->Next();
	}
	printf("%\n");
}
void travelNode(TiXmlElement* elem, int index = 0);
void travelSubElem(TiXmlElement* elem, int index = 0)
{
	string space;
	for (int i = 0; i < index; ++i)
	{
		space += "  ";
	}
	TiXmlElement* sub = elem->FirstChildElement();
	while (sub)
	{
		travelNode(sub, index + 1);
		sub = sub->NextSiblingElement();
	}
}


void travelNode(TiXmlElement* elem, int index)
{
	string space;
	for (int i = 0; i < index; ++i)
	{
		space += "  ";
	}

	getName(elem, index);
	getAttr(elem, index);
	travelSubElem(elem, index);
}



void testxml1()
{
	string str = "abc";
	string str2 = 
		"abc\
123\
		";
	string str3 = 
		"abc"
		"123";
	string str4(        //C++ 11开始支持Raw string literal,可以写成 R"delimiter(raw_characters)delimiter" 这种形式 其中EOF是分界字符，可以是任意组合
		R"EOF(
<Auto>
    <Disk mxproptype="1">
        <Disk Name="F1" Label="L1" />
        <Disk Name="F2" Label="L2" />
        <Disk Name="F3" Label="L3" />        
	</Disk>
</Auto>
<Bite>
    <Echo>
        <Fun Name="N1"/>
        <Fun Name="N2"/>
        <Fun Name="N3"/>        
	</Echo>
</Bite>
<T>
    <TT>
        <TTT>
			<TTT1 Name="T1"/>
			<TTT2 Name="T2"/>
			<TTT3 Name="T3"/>        
		</TTT>
        <Fun Name="N2"/>
        <Fun Name="N3"/>        
	</TT>
</T>
)EOF");
	string str5 =
		R"EOF(
<Auto>
    <Disk mxproptype="1">
        <Disk Name="F1" Label="L1" />
        <Disk Name="F2" Label="L2" />
        <Disk Name="F3" Label="L3" />        
	</Disk>
</Auto>
)EOF";

	string str6 =
		R"(
<Auto>
    <Disk mxproptype="1">
        <Disk Name="F1" Label="L1" />
        <Disk Name="F2" Label="L2" />
        <Disk Name="F3" Label="L3" />        
	</Disk>
</Auto>
)";
	TiXmlDocument doc;
	doc.Parse(str6.c_str());

	if (doc.Error())
	{
		printf("parse error:%s\n", doc.ErrorDesc());
		return;
	}

	TiXmlElement* elem = doc.RootElement();

	while (elem)
	{
		travelNode(elem);
		elem = elem->NextSiblingElement();
	}

	
}

