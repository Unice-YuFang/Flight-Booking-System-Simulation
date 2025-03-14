/**********************************************************************
Copyright:   2019武汉大学17级计科7班2017311500181廖妤芳
File name:   FlightTicket
Description: 
模拟实现如下功能：
1）航班信息录入与修改。
2）航班信息查询。
3）订票操作。
4）退票操作。
5）订票信息录入与修改。
6）方便合理的用户操作界面，能直观展示输入数据、处理过程及输出结果。
Author:      廖妤芳
Version:     2.0
Date:        2019.05.31
***********************************************************************/
#include"stdafx.h"
#include<dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<easyx.h>
#define LINE 50			//最大航线数
#define ID 20			//旅客证件号长度

/*旅客信息*/
typedef struct
{
	char number[10];     //票号
	char id[20];         //证件号
	char name[10];       //姓名
	int count;           //订票数
	char flightname[10]; //乘坐航班号
}GUEST;

/*航班信息*/
typedef struct
{
	char Flightnumber[10];//航班号
	char TakeOffCity[20]; //起飞城市
	char ArrivalCity[20]; //抵达城市
	char TakeoffTime[20]; //起飞时间
	char LandingTime[20]; //降落时间
	int  Seats;           //舱位数
	char Price[5];        //票价
	char Discount[5];     //折扣
	GUEST Guest[20];
	int Sit;			  //预定的座位数
}FLY;

/*菜单函数，函数返回值为所选的功能码*/
int menu_select()
{
	int c;				//输入的功能码
	int getch();		//读取字符
	printf("\n\n\n                                  欢迎登录\n\n");
	printf("                                飞机订票系统\n\n");
	printf("                ====================MENU=====================\n\n");
	printf("                           0. 输入航班信息\n");
	printf("                           1. 列出航班的信息\n");
	printf("                           2. 按航班号查询航班信息\n");
	printf("                           3. 按城市来查询航班\n");
	printf("                           4. 订票\n");
	printf("                           5. 退票\n");
	printf("                           6. 修改飞机航班的信息\n");
	printf("                           7. 修改旅客的信息\n");
	printf("                           8. 保存文件\n");
	printf("                           9. 读取和下载文件\n");
	printf("                           10. 退出\n");
	printf("                ==============================================\n\n");
	printf("请输入功能码(0~9)：");
	scanf("%d", &c);
	printf("\n");
	while (c < 0 || c>10)
	{
		printf("\n输入错误！请重新输入！");
		printf("\n请输入功能码(0~9):\n");
		scanf("%d", &c);
	}
	return c;										 //返回选择项，主程序根据该数调用相应的函数
}

/*输入函数*/
int Enter(FLY t[])
{
	int n;					//输入航班数
	int i;					//航班的循环
	printf("请输入航班数(不大于50个航班):");		//输入航线总数
	scanf("%d", &n);
	while (n>50 || n<0)
	{
		printf("\n输入错误!请重新输入（不大于50个航班）:");
		scanf("%d", &n);

	}
	for (i = 0; i<n; i++)
	{
		printf("\n请输入第%d个航班的信息\n", i + 1);
		printf("航班号：");
		scanf("%s", t[i].Flightnumber);				//输入航班号
		printf("出发城市：");
		scanf("%s", t[i].TakeOffCity);				//输入出发城市
		printf("抵达城市：");
		scanf("%s", t[i].ArrivalCity);				//输入抵达城市
		printf("起飞时间：");
		scanf("%s", t[i].TakeoffTime);				//输入起飞时间
		printf("降落时间：");
		scanf("%s", t[i].LandingTime);				//输入降落时间
		printf("剩余空座位：");
		scanf("%d", &t[i].Seats);					//输入空座位数
		printf("机票票价：");
		scanf("%s", t[i].Price);					//输入票价
		printf("机票折扣：");
		scanf("%s", t[i].Discount);					//输入折扣
		printf("第%d个航班信息输入完成！\n\n\n", i + 1);
	}
	for (i = 0; i<n; i++)
		t[i].Sit = 0;
	return n;										//返回记录条数
}

/*显示记录，参数为记录数组和记录条数*/
void List(FLY t[], int n)
{
	int i;
	printf("航班号    出发城市    抵达城市   出发时间   降落时间   剩余座位数   价格  折扣\n");
	printf("------------------------------------------------------------------------------\n");
	for (i = 0; i<n; i++)
		printf("%-12s%-12s%-10s%-12s%-12s%-10d%-7s%-7s\n", t[i].Flightnumber, t[i].TakeOffCity, t[i].ArrivalCity,
			t[i].TakeoffTime, t[i].LandingTime, t[i].Seats, t[i].Price, t[i].Discount);
	printf("          ////////////////////////以上为所有资料/////////////////////////////\n");
}


/*按航班号查找记录*/
void SearchFlightNum(FLY t[], int n)
{
	char s[20];											//保存待查找航班号符串
	int i;												//查询航班记录
	printf("输入您想查找的航班号:");
	scanf("%s", s);										//输入待查找航班号
	for (i = 0; i<n; i++)								//从第一条记录开始扫描
	{
		if (strcmp(s, t[i].Flightnumber) == 0)			//记录中的航班名和待比较的是否相等
			break;										//相等，则返回该记录的下标号，结束
	}
	if (i>n - 1)										//如果整数i值大于n-1，则未找到
		printf("\n对不起！查无此航班！\n");
	else
	{
		printf("航班号    出发城市    抵达城市   出发时间   降落时间   剩余座位数   价格  折扣\n");//显示记录
		printf("------------------------------------------------------------------------------\n");
		printf("%-12s%-12s%-10s%-12s%-12s%-10d%-7s%-7s\n", t[i].Flightnumber, t[i].TakeOffCity, t[i].ArrivalCity,
			t[i].TakeoffTime, t[i].LandingTime, t[i].Seats, t[i].Price, t[i].Discount);
		printf("          ////////////////////////以上为所有资料/////////////////////////////\n");
	}
}


/*按起降城市查找记录*/
void SearchFlightCity(FLY t[], int n)
{
	char s1[20];								//出发城市
	char s2[20];								//抵达城市
	int i;										//循环变量
	printf("请输入出发城市名称:");
	scanf("%s", s1);
	printf("请输入抵达城市名称:");
	scanf("%s", s2);
	for (i = 0; i<n; i++)					    //从第一条记录开始，直到最后一条
	{
		if ((strcmp(s1, t[i].TakeOffCity) == 0) && (strcmp(s2, t[i].ArrivalCity) == 0))  //记录中的城市和待比较的是否相等
			break;																		 //相等，则返回该记录的下标号，结束
	}
	if (i>n - 1)																		 //如果整数i值大于n-1，则未找到
		printf("\n对不起！查无此航线航班！\n");
	else
	{
		printf("航班号    出发城市    抵达城市   出发时间   降落时间   剩余座位数   价格  折扣\n"); //找到，则显示记录
		printf("------------------------------------------------------------------------------\n");
		printf("%-12s%-12s%-10s%-12s%-12s%-10d%-7s%-7s\n", t[i].Flightnumber, t[i].TakeOffCity, t[i].ArrivalCity, t[i].TakeoffTime,
			t[i].LandingTime, t[i].Seats, t[i].Price, t[i].Discount);
		printf("          ////////////////////////以上为所有资料/////////////////////////////\n");
	}
}

/*订票*/
void Booking(FLY t[], int n)
{
	char number1[10];								//票号
	char name1[10];									//姓名
	char id1[20];									//证件号
	char flightname1[10];							//航班号
	int i, j = 0, m, k, count1;						//循环变量
	printf("请输入您想预订的票数:");
	scanf("%d", &m);
	for (k = 0; k<m; k++)
	{
		printf("请输入第%d位旅客的资料\n", k+1);
		printf("票号：");
		scanf("%s", number1);
		printf("姓名：");
		scanf("%s", name1);							//输入订票客户姓名
		printf("有效证件号：");
		scanf("%s", id1);							//输入证件号
		printf("机票张数：");
		scanf("%d", &count1);						//输入订票票数
		printf("航班号：");
		scanf("%s", flightname1);					//输入航班号
		for (i = 0; i<n; i++)						//从第一条记录开始扫描
		{
			if (strcmp(flightname1, t[i].Flightnumber) == 0)  //记录中的航班名和待比较的是否相等
			{
				j = t[i].Sit;
				strcpy(t[i].Guest[j].number, number1);
				strcpy(t[i].Guest[j].name, name1);
				strcpy(t[i].Guest[j].id, id1);
				t[i].Guest[j].count = count1;
				strcpy(t[i].Guest[j].flightname, flightname1);
				t[i].Seats = t[i].Seats - count1;
				t[i].Sit++;
				break;										  //若相等，则返回该记录的下标号，结束
			}
		}
		if (i>n - 1)										 //如果整数i值大于n-1，说明没找到
		{
			printf("\n对不起！查无此记录\n");
			m = m + 2;
			k++;
		}
		else 
			printf("订票成功！");
	}
}

/*退票*/
void Refund(FLY t[], int n)
{
	char s1[20];										 //保存待查找航班号字符串
	char s2[20];                                         //保存证件号字符串
	int i, k, j, h, l, ch;
	printf("请输入您想退订的航班号:");
	scanf("%s", s1);									 //输入待查找航班名
	printf("请输入您的证件号:");
	scanf("%s", s2);									 //输入待查找证件号
	printf("票号         姓名         证件号         订的票数     航班号\n");
	printf("---------------------------------------------------------------\n");
	for (i = 0; i<n; i++)								 //从第一条记录开始扫描
	{
		for (j = 0; j<t[i].Sit; j++)
			if ((strcmp(s1, t[i].Guest[j].flightname) == 0) && (strcmp(s2, t[i].Guest[j].id) == 0))
			{
				printf("%-11s%-16s%-16s%-14d%-10s\n", t[i].Guest[j].number, t[i].Guest[j].name, t[i].Guest[j].id,
					t[i].Guest[j].count, t[i].Guest[j].flightname);
				t[i].Seats = t[i].Seats + t[i].Guest[j].count;
				l = j;
				h = i;
				break;
			}
	}
	printf("          ////////////////////////以上为所有资料/////////////////////////////\n");
	i = h;
	if (i>n - 1)						//如果整数i值大于n-1，则未找到
		printf("\n对不起！未查到此纪录！\n");
	else
	{
		printf("您是否确认退票(1为退票/0为不退票)\n");
		scanf("%d", &ch);
		if (ch == 1)
		{
			for (k = l + 1; k<t[i].Sit; k++)
			{
				strcpy(t[i].Guest[k - 1].number, t[i].Guest[k].number);     //将后一条记录的姓名拷贝到前一条
				strcpy(t[i].Guest[k - 1].name, t[i].Guest[k].name);
				strcpy(t[i].Guest[k - 1].id, t[i].Guest[k].id);
				t[i].Guest[k - 1].count = t[i].Guest[k].count;
				strcpy(t[i].Guest[k - 1].flightname, t[i].Guest[k].flightname);
			}
			t[i].Sit--;
			printf("退票成功!!\n");
		}
	}
}

/*修改航班信息*/
void ModifyFlight(FLY t[], int n)
{
	char s[20];											//要删除记录的航班号
	int i, j;											//循环变量
	printf("请输入您要修改的航班号:");
	scanf("%s", s);										//输入航班号
	for (i = 0; i<n; i++)								//从第一条记录开始扫描
	{
		if (strcmp(s, t[i].Flightnumber) == 0)			//记录中的航班号和待比较的是否相等
			break;										//相等，则返回该记录的下标号，结束
	}
	if (i>n - 1)										//如果整数i值大于n-1，则未找到
		printf("\n对不起！查无此航班！\n");
	else
	{
		printf("原航班记录：\n");
		printf("航班号    出发城市    抵达城市   出发时间   降落时间   剩余座位数   价格  折扣\n"); //找到，则显示原先记录
		printf("------------------------------------------------------------------------------\n");
		printf("%-12s%-12s%-10s%-12s%-12s%-10d%-7s%-7s\n", t[i].Flightnumber, t[i].TakeOffCity, t[i].ArrivalCity, t[i].TakeoffTime,
			t[i].LandingTime, t[i].Seats, t[i].Price, t[i].Discount);
		printf("请输入新的航班资讯：\n");
		printf("航班号：");
		scanf("%s", t[i].Flightnumber);
		printf("出发城市：");
		scanf("%s", t[i].TakeOffCity);
		printf("抵达城市：");
		scanf("%s", t[i].ArrivalCity);
		printf("出发时间：");
		scanf("%s", t[i].TakeoffTime);
		printf("降落时间：");
		scanf("%s", t[i].LandingTime);
		printf("票价：");
		scanf("%s", t[i].Price);
		printf("折扣：");
		scanf("%s", t[i].Discount);
	}
}

/*修改旅客信息*/
void ModifyPassenger(GUEST t[], int n)
{
	char s[20];											//要删除记录的航班号
	int i, j;
	printf("请输入您的证件号:");
	scanf("%s", s);										//输入待查找证件号
	for (i = 0; i<n; i++)								//从第一条记录开始扫描
	{
		if (strcmp(s, t[i].number) == 0)			//记录中的证件号和待比较的是否相等
			break;										//相等，则返回该记录的下标号，结束
	}
	if (i>n-1 )										//如果整数i值大于n-1，则未找到
		printf("\n对不起！查无此旅客！\n");
	else
	{
		printf("该旅客原资料：");
		printf("姓名         证件号         订的票数     航班号\n");
		printf("------------------------------------------------\n");
		printf("%-16s%-16s%-14d%-10s\n", t[i].name, t[i].id, t[i].count, t[i].flightname);
		printf("          ////////////////////////以上为所有资料/////////////////////////////\n");
		printf("请输入该旅客新资料：\n");
		printf("姓名：");
		scanf("%s", t[i].name);							//输入订票客户姓名
		printf("有效证件号：");
		scanf("%s", t[i].id);							//输入证件号
		printf("机票张数：");
		scanf("%d", t[i].count);						//输入订票票数
		printf("航班号：");
		scanf("%s", t[i].flightname);					//输入航班号
	}
}

/*保存资料*/
void Save(FLY t[], int n)
{
	int i, j;										//循环变量
	FILE *fp;										//指向记录文件的指针
	if ((fp = fopen("record.txt", "wb")) == NULL)   //打开文件，并判断是否正常开启
	{
		printf("\n对不起！无法打开文件！\n");		//未打开
		exit(1);									//退出
	}
	printf("\n保存文件\n");
	fprintf(fp, "%d", n);							//将记录数写入文件
	fprintf(fp, "\r\n");							//将换行符号写入文件
	for (i = 0; i<n; i++)
	{
		fprintf(fp, "%s   %s    %s    %s    %s    %d    %s    %s", t[i].Flightnumber, t[i].TakeOffCity, t[i].ArrivalCity,
			t[i].TakeoffTime, t[i].LandingTime, t[i].Seats, t[i].Price, t[i].Discount);
		fprintf(fp, "\r\n");						//将换行符号写入文件
		fprintf(fp, "%d", t[i].Sit);				//将记录数写入文件
		fprintf(fp, "\r\n");						//将换行符号写入文件
		for (j = 0; j<t[i].Sit; j++)
		{
			fprintf(fp, "%s    %s   %s   %d    %s", t[i].Guest[j].number, t[i].Guest[j].name, t[i].Guest[j].id,
				t[i].Guest[j].count, t[i].Guest[j].flightname);				//将格式写入记录文件
			fprintf(fp, "\r\n");											//将换行符号写入文件
		}
	}
	fclose(fp);										//关闭文件
	printf("****************保存成功!*****************\n");
}


/*读入函数，参数为结构体数组*/
int Load(FLY t[])
{
	int i;											//第i个记录
	int j;											//第j位旅客
	int n;											//总记录数
	FILE *fp;										//指向文件的指针
	if ((fp = fopen("record.txt", "rb")) == NULL)	//打开文件
	{
		printf("\n对不起！无法打开文件\n");
		exit(1);
	}
	fscanf(fp, "%d", &n);							//读入记录数
	for (i = 0; i<n; i++)
	{
		fscanf(fp, "%s   %s    %s    %s    %s    %d    %s    %s", t[i].Flightnumber, t[i].TakeOffCity, t[i].ArrivalCity,
			t[i].TakeoffTime, t[i].LandingTime, &t[i].Seats, t[i].Price, t[i].Discount); fscanf(fp, "%d", &t[i].Sit);				//读入记录数
		for (j = 0; j<t[i].Sit; j++)
			fscanf(fp, "%s    %s   %s   %d    %s", t[i].Guest[j].number, t[i].Guest[j].name, t[i].Guest[j].id, &t[i].Guest[j].count,
				t[i].Guest[j].flightname);			//按格式读入记录
	}
	fclose(fp);										//关闭文件
	printf("****************您已经成功从文件读取数据!****************\n\n");
	return n;										//返回记录数
}

/*退出系统*/
void Quit()
{
	HWND wnd = GetHWnd();					//HWND返回窗口或控件的句柄。wnd变量对象描述，表示对象
	if (MessageBox(wnd, _T("\n是否确认退出系统？"), _T("退出系统"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		exit(0);
	else
		menu_select();
}

/*主函数*/
void main()
{
	FLY flight[LINE];
	GUEST id[ID];
	int length;										//保存记录长度
	for (;;)										//无限循环
	{
		switch (menu_select())   //调用主菜单函数，返回值整数作开关语句的条件
		{
		case 0:length = Enter(flight);
			break;							//输入记录
		case 1:List(flight, length);
			break;							//显示所有航班
		case 2:SearchFlightNum(flight, length);
			break;							//由航班号查找航班
		case 3:SearchFlightCity(flight, length);
			break;							//由出发和抵达城市查找航班
		case 4:Booking(flight, length);
			break;							//订票
		case 5:Refund(flight, length);
			break;							//退票
		case 6:ModifyFlight(flight, length);
			break;							//修改航班信息
		case 7:ModifyPassenger(id, length);
			break;							//修改旅客信息
		case 8:Save(flight, length);
			break;							//保存文件
		case 9:length = Load(flight);
			break;							//读文件
		case 10:Quit();						//若返回值为0，则程序结束
		}
	}
}