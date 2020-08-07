#include <iostream>
#include"game.h"
#include<graphics.h>    // ���� EasyX ͼ�ο� 
#include <stdlib.h>
#include <conio.h>     // ����������⡢���յȺ��� 
#include <windows.h>
#include <time.h>
#include<process.h>     // ���߳�
#include <mmsystem.h>   // ���ֲ��ŵĶ�ý���
#pragma comment(lib,"winmm.lib")  //����winmm.lib�����
#pragma comment(lib, "Msimg32.lib")

int fun;   // �������
int sc[7];  //�洢����
int newS;   // �µķ���
int height = 50;   // ���а���
struct Player
{
	int score[5];
}player[7];

IMAGE Fun1;
IMAGE Fun2;
IMAGE Fun3;
IMAGE Fun4;
IMAGE Details;
IMAGE Hint;
IMAGE Sort;
IMAGE Begin;

// ������Դ
void loadResources()
{
	loadimage(&Fun1, "res\\menu1.png", 450, 630);
	loadimage(&Fun2, "res\\menu2.png", 450, 630);
	loadimage(&Fun3, "res\\menu3.png", 450, 630);
	loadimage(&Fun4, "res\\menu4.png", 450, 630);
	loadimage(&Details, "res\\details.png", 450, 630);
	loadimage(&Hint, "res\\hint.png", 450, 630);
	loadimage(&Sort, "res\\sort.png", 450, 630);
	loadimage(&Begin, "res\\begin.png", 450, 630);

}

//��ʾ��
void promt()
{
	MessageBox(NULL, _T("��Ϸ�����У�\nʹ�����·�������ƣ�\n�س���������ع���!"), _T("��ܰ��ʾ"), MB_OK | MB_ICONWARNING);
	
}

// ���ݴ洢
void saveData(int newS)
{
	FILE *fp2;
	if ((fp2 = fopen("score.dat", "r")) == NULL)
		outtextxy(0, 0, _T("�����ļ��쳣��"));
	for (int i = 0; i < 7; i++)
	{
		fscanf_s(fp2, "%d", player[i].score);
	}
	fclose(fp2);
	*player[6].score = newS;
	for (int i = 0; i < 7; i++)
	{
		for (int j = i + 1; j < 7; j++)
		{
			if (*player[i].score < *player[j].score)
			{
				int temp = *player[i].score;
				*player[i].score = *player[j].score;
				*player[j].score = temp;
				
			}
		}
	}
	if ((fp2 = fopen("score.dat", "w")) == NULL)
		outtextxy(0, 0, _T("�����ļ��쳣��"));
	for (int i = 0; i < 7; i++)
	{
		fprintf_s(fp2, "%d\n", *player[i].score);
	}
	fclose(fp2);
}

// ����1
void fun1()
{
	newS = game();
	saveData(newS);
}

// ����2
void fun2()
{
	FILE *fp2;
	if ((fp2 = fopen("score.dat", "r")) == NULL)
		outtextxy(0, 0, _T("�����ļ��쳣��"));
	int ii = 0;
	char mid2[11];
	putimage(0, 0, &Sort);
	for (int i = 0; i < 7; i++)
	{
		fscanf_s(fp2,"%d",player[i].score);
	}
	fclose(fp2);
	setbkmode(TRANSPARENT);  // �������ֱ���ģʽΪ TRANSPARENT ʵ����������ޱ���ɫ 
	settextcolor(RGB(0, 0, 0));  // 2.����������ɫΪ ��ɫ 
	settextstyle(25, 0, _T("����")); // 3.�������ִ�С�����壬��������Ϊ���ߡ������塣
	for (int ii = 0; ii < 6; ii++)
	{
		itoa(*player[ii].score, mid2, 10);
		outtextxy(320, 233 + ii * height, mid2);
	}
	getch();
}

// ����3
void fun3()
{
	putimage(0,0, &Details);
	getch();
}

// �����û�ѡ��
void Choice()
{
	int choice;
	choice = 1;
	putimage(0, 0, &Fun1);
	while (_kbhit)
	{
		char ch = getch();
		if (ch == 72)
		{
			choice--;
			if (choice == 0)
				choice = 4;
			
		}
		else if (ch == 80)
		{
			choice++;
			if (choice == 5)
				choice = 1;
		}
		else if (ch == '\r')
			break;
		if (choice==1)
		{
			putimage(0, 0, &Fun1);
		}
		else if (choice == 2)
		{
			putimage(0, 0, &Fun2);
		}
		else if (choice == 3)
		{
			putimage(0, 0, &Fun3);
		}
		else if (choice == 4)
		{
			putimage(0, 0, &Fun4);
		}
	}
	switch (choice)
	{
	case 1:
		fun1();
		break;
	case 2:
		fun2();
		break;
	case 3:
		fun3();
		break;
	case 4:
		exit(0);
	default:
		break;
	}
}

// ��֧������
void menu()
{
	initgraph(450, 630);   //��������
	loadResources();   //������Դ
	mciSendString("open res/begin.mp3", 0, 0, 0);   //������
	mciSendString("play res/begin.mp3 from 0", 0, 0, 0);  //��������
	putimage(0, 0, &Hint);   // ������Ϸ�Ҹ�
	Sleep(2000);   // ��ͣ2��
	promt();   //������ʾ
	putimage(0, 0, &Begin);  //��ӭ����
	while (1)   //�ж��û��Ƿ�����ո�����ո������
	{
		if(getch() == ' ')
			break;
	}
	while (1)
	{
		Choice();  //�˵�
	
	}
	
}