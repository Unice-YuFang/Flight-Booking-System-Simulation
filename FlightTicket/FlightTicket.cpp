/**********************************************************************
Copyright:   2019�人��ѧ17���ƿ�7��2017311500181��楷�
File name:   FlightTicket
Description: 
ģ��ʵ�����¹��ܣ�
1��������Ϣ¼�����޸ġ�
2��������Ϣ��ѯ��
3����Ʊ������
4����Ʊ������
5����Ʊ��Ϣ¼�����޸ġ�
6�����������û��������棬��ֱ��չʾ�������ݡ�������̼���������
Author:      ��楷�
Version:     2.0
Date:        2019.05.31
***********************************************************************/
#include"stdafx.h"
#include<dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<easyx.h>
#define LINE 50			//�������
#define ID 20			//�ÿ�֤���ų���

/*�ÿ���Ϣ*/
typedef struct
{
	char number[10];     //Ʊ��
	char id[20];         //֤����
	char name[10];       //����
	int count;           //��Ʊ��
	char flightname[10]; //���������
}GUEST;

/*������Ϣ*/
typedef struct
{
	char Flightnumber[10];//�����
	char TakeOffCity[20]; //��ɳ���
	char ArrivalCity[20]; //�ִ����
	char TakeoffTime[20]; //���ʱ��
	char LandingTime[20]; //����ʱ��
	int  Seats;           //��λ��
	char Price[5];        //Ʊ��
	char Discount[5];     //�ۿ�
	GUEST Guest[20];
	int Sit;			  //Ԥ������λ��
}FLY;

/*�˵���������������ֵΪ��ѡ�Ĺ�����*/
int menu_select()
{
	int c;				//����Ĺ�����
	int getch();		//��ȡ�ַ�
	printf("\n\n\n                                  ��ӭ��¼\n\n");
	printf("                                �ɻ���Ʊϵͳ\n\n");
	printf("                ====================MENU=====================\n\n");
	printf("                           0. ���뺽����Ϣ\n");
	printf("                           1. �г��������Ϣ\n");
	printf("                           2. ������Ų�ѯ������Ϣ\n");
	printf("                           3. ����������ѯ����\n");
	printf("                           4. ��Ʊ\n");
	printf("                           5. ��Ʊ\n");
	printf("                           6. �޸ķɻ��������Ϣ\n");
	printf("                           7. �޸��ÿ͵���Ϣ\n");
	printf("                           8. �����ļ�\n");
	printf("                           9. ��ȡ�������ļ�\n");
	printf("                           10. �˳�\n");
	printf("                ==============================================\n\n");
	printf("�����빦����(0~9)��");
	scanf("%d", &c);
	printf("\n");
	while (c < 0 || c>10)
	{
		printf("\n����������������룡");
		printf("\n�����빦����(0~9):\n");
		scanf("%d", &c);
	}
	return c;										 //����ѡ�����������ݸ���������Ӧ�ĺ���
}

/*���뺯��*/
int Enter(FLY t[])
{
	int n;					//���뺽����
	int i;					//�����ѭ��
	printf("�����뺽����(������50������):");		//���뺽������
	scanf("%d", &n);
	while (n>50 || n<0)
	{
		printf("\n�������!���������루������50�����ࣩ:");
		scanf("%d", &n);

	}
	for (i = 0; i<n; i++)
	{
		printf("\n�������%d���������Ϣ\n", i + 1);
		printf("����ţ�");
		scanf("%s", t[i].Flightnumber);				//���뺽���
		printf("�������У�");
		scanf("%s", t[i].TakeOffCity);				//�����������
		printf("�ִ���У�");
		scanf("%s", t[i].ArrivalCity);				//����ִ����
		printf("���ʱ�䣺");
		scanf("%s", t[i].TakeoffTime);				//�������ʱ��
		printf("����ʱ�䣺");
		scanf("%s", t[i].LandingTime);				//���뽵��ʱ��
		printf("ʣ�����λ��");
		scanf("%d", &t[i].Seats);					//�������λ��
		printf("��ƱƱ�ۣ�");
		scanf("%s", t[i].Price);					//����Ʊ��
		printf("��Ʊ�ۿۣ�");
		scanf("%s", t[i].Discount);					//�����ۿ�
		printf("��%d��������Ϣ������ɣ�\n\n\n", i + 1);
	}
	for (i = 0; i<n; i++)
		t[i].Sit = 0;
	return n;										//���ؼ�¼����
}

/*��ʾ��¼������Ϊ��¼����ͼ�¼����*/
void List(FLY t[], int n)
{
	int i;
	printf("�����    ��������    �ִ����   ����ʱ��   ����ʱ��   ʣ����λ��   �۸�  �ۿ�\n");
	printf("------------------------------------------------------------------------------\n");
	for (i = 0; i<n; i++)
		printf("%-12s%-12s%-10s%-12s%-12s%-10d%-7s%-7s\n", t[i].Flightnumber, t[i].TakeOffCity, t[i].ArrivalCity,
			t[i].TakeoffTime, t[i].LandingTime, t[i].Seats, t[i].Price, t[i].Discount);
	printf("          ////////////////////////����Ϊ��������/////////////////////////////\n");
}


/*������Ų��Ҽ�¼*/
void SearchFlightNum(FLY t[], int n)
{
	char s[20];											//��������Һ���ŷ���
	int i;												//��ѯ�����¼
	printf("����������ҵĺ����:");
	scanf("%s", s);										//��������Һ����
	for (i = 0; i<n; i++)								//�ӵ�һ����¼��ʼɨ��
	{
		if (strcmp(s, t[i].Flightnumber) == 0)			//��¼�еĺ������ʹ��Ƚϵ��Ƿ����
			break;										//��ȣ��򷵻ظü�¼���±�ţ�����
	}
	if (i>n - 1)										//�������iֵ����n-1����δ�ҵ�
		printf("\n�Բ��𣡲��޴˺��࣡\n");
	else
	{
		printf("�����    ��������    �ִ����   ����ʱ��   ����ʱ��   ʣ����λ��   �۸�  �ۿ�\n");//��ʾ��¼
		printf("------------------------------------------------------------------------------\n");
		printf("%-12s%-12s%-10s%-12s%-12s%-10d%-7s%-7s\n", t[i].Flightnumber, t[i].TakeOffCity, t[i].ArrivalCity,
			t[i].TakeoffTime, t[i].LandingTime, t[i].Seats, t[i].Price, t[i].Discount);
		printf("          ////////////////////////����Ϊ��������/////////////////////////////\n");
	}
}


/*���𽵳��в��Ҽ�¼*/
void SearchFlightCity(FLY t[], int n)
{
	char s1[20];								//��������
	char s2[20];								//�ִ����
	int i;										//ѭ������
	printf("�����������������:");
	scanf("%s", s1);
	printf("������ִ��������:");
	scanf("%s", s2);
	for (i = 0; i<n; i++)					    //�ӵ�һ����¼��ʼ��ֱ�����һ��
	{
		if ((strcmp(s1, t[i].TakeOffCity) == 0) && (strcmp(s2, t[i].ArrivalCity) == 0))  //��¼�еĳ��кʹ��Ƚϵ��Ƿ����
			break;																		 //��ȣ��򷵻ظü�¼���±�ţ�����
	}
	if (i>n - 1)																		 //�������iֵ����n-1����δ�ҵ�
		printf("\n�Բ��𣡲��޴˺��ߺ��࣡\n");
	else
	{
		printf("�����    ��������    �ִ����   ����ʱ��   ����ʱ��   ʣ����λ��   �۸�  �ۿ�\n"); //�ҵ�������ʾ��¼
		printf("------------------------------------------------------------------------------\n");
		printf("%-12s%-12s%-10s%-12s%-12s%-10d%-7s%-7s\n", t[i].Flightnumber, t[i].TakeOffCity, t[i].ArrivalCity, t[i].TakeoffTime,
			t[i].LandingTime, t[i].Seats, t[i].Price, t[i].Discount);
		printf("          ////////////////////////����Ϊ��������/////////////////////////////\n");
	}
}

/*��Ʊ*/
void Booking(FLY t[], int n)
{
	char number1[10];								//Ʊ��
	char name1[10];									//����
	char id1[20];									//֤����
	char flightname1[10];							//�����
	int i, j = 0, m, k, count1;						//ѭ������
	printf("����������Ԥ����Ʊ��:");
	scanf("%d", &m);
	for (k = 0; k<m; k++)
	{
		printf("�������%dλ�ÿ͵�����\n", k+1);
		printf("Ʊ�ţ�");
		scanf("%s", number1);
		printf("������");
		scanf("%s", name1);							//���붩Ʊ�ͻ�����
		printf("��Ч֤���ţ�");
		scanf("%s", id1);							//����֤����
		printf("��Ʊ������");
		scanf("%d", &count1);						//���붩ƱƱ��
		printf("����ţ�");
		scanf("%s", flightname1);					//���뺽���
		for (i = 0; i<n; i++)						//�ӵ�һ����¼��ʼɨ��
		{
			if (strcmp(flightname1, t[i].Flightnumber) == 0)  //��¼�еĺ������ʹ��Ƚϵ��Ƿ����
			{
				j = t[i].Sit;
				strcpy(t[i].Guest[j].number, number1);
				strcpy(t[i].Guest[j].name, name1);
				strcpy(t[i].Guest[j].id, id1);
				t[i].Guest[j].count = count1;
				strcpy(t[i].Guest[j].flightname, flightname1);
				t[i].Seats = t[i].Seats - count1;
				t[i].Sit++;
				break;										  //����ȣ��򷵻ظü�¼���±�ţ�����
			}
		}
		if (i>n - 1)										 //�������iֵ����n-1��˵��û�ҵ�
		{
			printf("\n�Բ��𣡲��޴˼�¼\n");
			m = m + 2;
			k++;
		}
		else 
			printf("��Ʊ�ɹ���");
	}
}

/*��Ʊ*/
void Refund(FLY t[], int n)
{
	char s1[20];										 //��������Һ�����ַ���
	char s2[20];                                         //����֤�����ַ���
	int i, k, j, h, l, ch;
	printf("�����������˶��ĺ����:");
	scanf("%s", s1);									 //��������Һ�����
	printf("����������֤����:");
	scanf("%s", s2);									 //���������֤����
	printf("Ʊ��         ����         ֤����         ����Ʊ��     �����\n");
	printf("---------------------------------------------------------------\n");
	for (i = 0; i<n; i++)								 //�ӵ�һ����¼��ʼɨ��
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
	printf("          ////////////////////////����Ϊ��������/////////////////////////////\n");
	i = h;
	if (i>n - 1)						//�������iֵ����n-1����δ�ҵ�
		printf("\n�Բ���δ�鵽�˼�¼��\n");
	else
	{
		printf("���Ƿ�ȷ����Ʊ(1Ϊ��Ʊ/0Ϊ����Ʊ)\n");
		scanf("%d", &ch);
		if (ch == 1)
		{
			for (k = l + 1; k<t[i].Sit; k++)
			{
				strcpy(t[i].Guest[k - 1].number, t[i].Guest[k].number);     //����һ����¼������������ǰһ��
				strcpy(t[i].Guest[k - 1].name, t[i].Guest[k].name);
				strcpy(t[i].Guest[k - 1].id, t[i].Guest[k].id);
				t[i].Guest[k - 1].count = t[i].Guest[k].count;
				strcpy(t[i].Guest[k - 1].flightname, t[i].Guest[k].flightname);
			}
			t[i].Sit--;
			printf("��Ʊ�ɹ�!!\n");
		}
	}
}

/*�޸ĺ�����Ϣ*/
void ModifyFlight(FLY t[], int n)
{
	char s[20];											//Ҫɾ����¼�ĺ����
	int i, j;											//ѭ������
	printf("��������Ҫ�޸ĵĺ����:");
	scanf("%s", s);										//���뺽���
	for (i = 0; i<n; i++)								//�ӵ�һ����¼��ʼɨ��
	{
		if (strcmp(s, t[i].Flightnumber) == 0)			//��¼�еĺ���źʹ��Ƚϵ��Ƿ����
			break;										//��ȣ��򷵻ظü�¼���±�ţ�����
	}
	if (i>n - 1)										//�������iֵ����n-1����δ�ҵ�
		printf("\n�Բ��𣡲��޴˺��࣡\n");
	else
	{
		printf("ԭ�����¼��\n");
		printf("�����    ��������    �ִ����   ����ʱ��   ����ʱ��   ʣ����λ��   �۸�  �ۿ�\n"); //�ҵ�������ʾԭ�ȼ�¼
		printf("------------------------------------------------------------------------------\n");
		printf("%-12s%-12s%-10s%-12s%-12s%-10d%-7s%-7s\n", t[i].Flightnumber, t[i].TakeOffCity, t[i].ArrivalCity, t[i].TakeoffTime,
			t[i].LandingTime, t[i].Seats, t[i].Price, t[i].Discount);
		printf("�������µĺ�����Ѷ��\n");
		printf("����ţ�");
		scanf("%s", t[i].Flightnumber);
		printf("�������У�");
		scanf("%s", t[i].TakeOffCity);
		printf("�ִ���У�");
		scanf("%s", t[i].ArrivalCity);
		printf("����ʱ�䣺");
		scanf("%s", t[i].TakeoffTime);
		printf("����ʱ�䣺");
		scanf("%s", t[i].LandingTime);
		printf("Ʊ�ۣ�");
		scanf("%s", t[i].Price);
		printf("�ۿۣ�");
		scanf("%s", t[i].Discount);
	}
}

/*�޸��ÿ���Ϣ*/
void ModifyPassenger(GUEST t[], int n)
{
	char s[20];											//Ҫɾ����¼�ĺ����
	int i, j;
	printf("����������֤����:");
	scanf("%s", s);										//���������֤����
	for (i = 0; i<n; i++)								//�ӵ�һ����¼��ʼɨ��
	{
		if (strcmp(s, t[i].number) == 0)			//��¼�е�֤���źʹ��Ƚϵ��Ƿ����
			break;										//��ȣ��򷵻ظü�¼���±�ţ�����
	}
	if (i>n-1 )										//�������iֵ����n-1����δ�ҵ�
		printf("\n�Բ��𣡲��޴��ÿͣ�\n");
	else
	{
		printf("���ÿ�ԭ���ϣ�");
		printf("����         ֤����         ����Ʊ��     �����\n");
		printf("------------------------------------------------\n");
		printf("%-16s%-16s%-14d%-10s\n", t[i].name, t[i].id, t[i].count, t[i].flightname);
		printf("          ////////////////////////����Ϊ��������/////////////////////////////\n");
		printf("��������ÿ������ϣ�\n");
		printf("������");
		scanf("%s", t[i].name);							//���붩Ʊ�ͻ�����
		printf("��Ч֤���ţ�");
		scanf("%s", t[i].id);							//����֤����
		printf("��Ʊ������");
		scanf("%d", t[i].count);						//���붩ƱƱ��
		printf("����ţ�");
		scanf("%s", t[i].flightname);					//���뺽���
	}
}

/*��������*/
void Save(FLY t[], int n)
{
	int i, j;										//ѭ������
	FILE *fp;										//ָ���¼�ļ���ָ��
	if ((fp = fopen("record.txt", "wb")) == NULL)   //���ļ������ж��Ƿ���������
	{
		printf("\n�Բ����޷����ļ���\n");		//δ��
		exit(1);									//�˳�
	}
	printf("\n�����ļ�\n");
	fprintf(fp, "%d", n);							//����¼��д���ļ�
	fprintf(fp, "\r\n");							//�����з���д���ļ�
	for (i = 0; i<n; i++)
	{
		fprintf(fp, "%s   %s    %s    %s    %s    %d    %s    %s", t[i].Flightnumber, t[i].TakeOffCity, t[i].ArrivalCity,
			t[i].TakeoffTime, t[i].LandingTime, t[i].Seats, t[i].Price, t[i].Discount);
		fprintf(fp, "\r\n");						//�����з���д���ļ�
		fprintf(fp, "%d", t[i].Sit);				//����¼��д���ļ�
		fprintf(fp, "\r\n");						//�����з���д���ļ�
		for (j = 0; j<t[i].Sit; j++)
		{
			fprintf(fp, "%s    %s   %s   %d    %s", t[i].Guest[j].number, t[i].Guest[j].name, t[i].Guest[j].id,
				t[i].Guest[j].count, t[i].Guest[j].flightname);				//����ʽд���¼�ļ�
			fprintf(fp, "\r\n");											//�����з���д���ļ�
		}
	}
	fclose(fp);										//�ر��ļ�
	printf("****************����ɹ�!*****************\n");
}


/*���뺯��������Ϊ�ṹ������*/
int Load(FLY t[])
{
	int i;											//��i����¼
	int j;											//��jλ�ÿ�
	int n;											//�ܼ�¼��
	FILE *fp;										//ָ���ļ���ָ��
	if ((fp = fopen("record.txt", "rb")) == NULL)	//���ļ�
	{
		printf("\n�Բ����޷����ļ�\n");
		exit(1);
	}
	fscanf(fp, "%d", &n);							//�����¼��
	for (i = 0; i<n; i++)
	{
		fscanf(fp, "%s   %s    %s    %s    %s    %d    %s    %s", t[i].Flightnumber, t[i].TakeOffCity, t[i].ArrivalCity,
			t[i].TakeoffTime, t[i].LandingTime, &t[i].Seats, t[i].Price, t[i].Discount); fscanf(fp, "%d", &t[i].Sit);				//�����¼��
		for (j = 0; j<t[i].Sit; j++)
			fscanf(fp, "%s    %s   %s   %d    %s", t[i].Guest[j].number, t[i].Guest[j].name, t[i].Guest[j].id, &t[i].Guest[j].count,
				t[i].Guest[j].flightname);			//����ʽ�����¼
	}
	fclose(fp);										//�ر��ļ�
	printf("****************���Ѿ��ɹ����ļ���ȡ����!****************\n\n");
	return n;										//���ؼ�¼��
}

/*�˳�ϵͳ*/
void Quit()
{
	HWND wnd = GetHWnd();					//HWND���ش��ڻ�ؼ��ľ����wnd����������������ʾ����
	if (MessageBox(wnd, _T("\n�Ƿ�ȷ���˳�ϵͳ��"), _T("�˳�ϵͳ"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		exit(0);
	else
		menu_select();
}

/*������*/
void main()
{
	FLY flight[LINE];
	GUEST id[ID];
	int length;										//�����¼����
	for (;;)										//����ѭ��
	{
		switch (menu_select())   //�������˵�����������ֵ������������������
		{
		case 0:length = Enter(flight);
			break;							//�����¼
		case 1:List(flight, length);
			break;							//��ʾ���к���
		case 2:SearchFlightNum(flight, length);
			break;							//�ɺ���Ų��Һ���
		case 3:SearchFlightCity(flight, length);
			break;							//�ɳ����͵ִ���в��Һ���
		case 4:Booking(flight, length);
			break;							//��Ʊ
		case 5:Refund(flight, length);
			break;							//��Ʊ
		case 6:ModifyFlight(flight, length);
			break;							//�޸ĺ�����Ϣ
		case 7:ModifyPassenger(id, length);
			break;							//�޸��ÿ���Ϣ
		case 8:Save(flight, length);
			break;							//�����ļ�
		case 9:length = Load(flight);
			break;							//���ļ�
		case 10:Quit();						//������ֵΪ0����������
		}
	}
}