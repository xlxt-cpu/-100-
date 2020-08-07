#include <iostream>
#include<graphics.h>    // ���� EasyX ͼ�ο� 
#include <stdlib.h>
#include <conio.h>     // ����������⡢���յȺ��� 
#include <windows.h>
#include <time.h>
#include<process.h>     // ���߳�
#include <mmsystem.h>   // ���ֲ��ŵĶ�ý���
#pragma comment(lib,"winmm.lib")  //����winmm.lib�����
#pragma comment(lib, "Msimg32.lib")// ���øÿ����ʹ�� AlphaBlend ������ʵ�� png ͸����ʾ 
using namespace std;


IMAGE Background;
IMAGE Brick1;
IMAGE Brick2;
IMAGE Brick3;
IMAGE Brick4;
IMAGE Brick5;
IMAGE Brick6;
IMAGE Brick7;
IMAGE Man0;
IMAGE Man1;
IMAGE Man2;
IMAGE Top;
IMAGE Over;
IMAGE Button;

// ש��
struct brick
{
	int x;   //����
	int y;   //����
	int type;  //����
	int flag;   // ���Ƿ񱻲ȹ�
	int breakTime; // ����ʱ��
};
// ����
struct man
{
	int x;   // ����
	int y;   // ����
	int hp;   //Ѫ��
	int walk;  // �ƶ�״̬���� �ң���ֹ
	int flag;   // �ж������Ƿ�վ�ڰ���
};


int xman = 26;      // ������
int yman = 34;      // ����߶�
int xwin = 432;     // ���ڿ��
int ywin = 559;     // ���ڸ߶�
int xbrick = 97;    // ���ӿ��
int ybrick = 16;    // ���Ӻ��
int xLWall = 25;    // ��ǽ
int xRWall = 425;   // ��ǽ
float vybrick = 1;    // ���������ٶ�
int vxman = 5;      // ����ˮƽ����
float vyman = 4;      // ���������ٶ�
int index;          // �������
int jump = 45;     // �����嵯���߶�
int fx = 2;          // ˮƽ�ƶ����ƶ��ٶ�
int msType = 0;    // ��Ч���Ʊ���
char ch;            //���ռ�������
int score = 0;      //����
int timesc = 0;     //������ʱ
int timehp = 0;     //��Ѫ��ʱ
char temp1[10];    // unicode ����洢�ַ��õ� 
char temp2[10];    // unicode ����洢�ַ��õ� 


struct brick brick[11];
struct man man;

// �����ƶ�����
void gotoxy(int a, int b)
{
	int xx = 0x0b;
	HANDLE hOutput;
	COORD loc;
	loc.X = a;
	loc.Y = b;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, loc);
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;  // ���ؿ���̨���
	cursor.dwSize = sizeof(cursor);
	SetConsoleCursorInfo(hOutput, &cursor);  // ���ÿ���̨���״̬


}

// png ͼ��͸�������������
void transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg) {
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	// �ṹ��ĵ�������Ա��ʾ�����͸���ȣ�0 ��ʾȫ͸����255 ��ʾ��͸����  
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// ʹ�� Windows GDI ����ʵ�ְ�͸��λͼ  
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

// ������Դ
void loadRes()
{
	loadimage(&Background, "res\\BJ.bmp");
	loadimage(&Man0, "res\\man0.png", xman, yman);
	loadimage(&Man1, "res\\manleft.png", xman, yman);
	loadimage(&Man2, "res\\manright.png", xman, yman);
	loadimage(&Brick1, "res\\board1.bmp", xbrick, ybrick);
	loadimage(&Brick2, "res\\board2.bmp", xbrick, ybrick);
	loadimage(&Brick3, "res\\board3.bmp", xbrick, ybrick);
	loadimage(&Brick4, "res\\board4.bmp", xbrick, ybrick);
	loadimage(&Brick5, "res\\board5.bmp", xbrick, ybrick);
	loadimage(&Brick6, "res\\board6.bmp", xbrick, ybrick);
	loadimage(&Brick7, "res\\board7.bmp", xbrick, ybrick);
	loadimage(&Top, "res\\TOU.png",450,630);
	loadimage(&Over, "res\\over.png", 400, 304);
	loadimage(&Button, "res\\button.png", 100, 30);
	mciSendString("open res/begin.mp3", 0, 0, 0);
	mciSendString("open res/brick1.mp3", 0, 0, 0);
	mciSendString("open res/brick2.mp3", 0, 0, 0);
	mciSendString("open res/brick3.mp3", 0, 0, 0);
	mciSendString("open res/brick4.mp3", 0, 0, 0);
	mciSendString("open res/brick6.mp3", 0, 0, 0);
	mciSendString("open res/die.mp3", 0, 0, 0);
};

// ��ʼ��
void start()
{
	score = 0;
	vyman = 4;      // ���������ٶ�
	vybrick = 1;    // ���������ٶ�
	srand(time(NULL));  //���������
	for (index = 1; index < 11; index++)
	{
		brick[index].type = rand() % 6 + 1;
		brick[index].flag = 1;
		brick[index].x = rand() % (400 - xbrick) + 25;
		brick[index].y = 610 + 60 * index;
	}
	brick[0].x = 180;
	brick[0].y = 614;
	brick[0].type = 1;
	man.hp = 100;
	man.walk = 0;
	man.x = 210;
	man.y = 614 - yman;
	man.flag = 1;
	//putimage(brick[0].x, brick[0].y, &Brick1);
	//putimage(man.x, man.y, &Man0);

};

// �������ƻ���
void draw()
{
	BeginBatchDraw();
	putimage(0, 0, &Top);   //����
	putimage(5, 70, &Background);  //��Ϸ�߿�
	//��Ϸ����
	for (index = 0; index < 11; index++)
	{
		if (brick[index].type == 1)
			putimage(brick[index].x, brick[index].y, &Brick1);
		else if (brick[index].type == 2)
			putimage(brick[index].x, brick[index].y, &Brick2);
		else if (brick[index].type == 3)
			putimage(brick[index].x, brick[index].y, &Brick3);
		else if (brick[index].type == 4)
			putimage(brick[index].x, brick[index].y, &Brick4);
		else if (brick[index].type == 5)
			putimage(brick[index].x, brick[index].y, &Brick5);
		else if (brick[index].type == 6 && brick[index].flag == 1 && brick[index].breakTime < 6)
			putimage(brick[index].x, brick[index].y, &Brick6);
		else if (brick[index].type == 6 && brick[index].flag == 1 && brick[index].breakTime >= 6)
			putimage(brick[index].x, brick[index].y, &Brick7);
	}
	if (man.walk == 0)
		transparentimage(NULL, man.x, man.y, &Man0);
	else if (man.walk == 1)
		transparentimage(NULL, man.x, man.y, &Man1);
	else if (man.walk == 2)
		transparentimage(NULL, man.x, man.y, &Man2);

	// ���ݻ���
	setbkmode(TRANSPARENT);     // �������ֱ���ģʽΪ TRANSPARENT ʵ����������ޱ���ɫ 
	settextcolor(RGB(255, 0, 0));    // ����������ɫΪ ��ɫ 
	settextstyle(25, 0, _T("����")); // �������ִ�С�����壬��������Ϊ���ߡ������塣����0Ϊ����Ӧ��
	itoa(man.hp, temp1, 10);
	itoa(score, temp2, 10);
	outtextxy(70, 45, temp1);
	outtextxy(330, 45, temp2);

	FlushBatchDraw();
};

// ��Ѫ,�Ʒֹ���
void updateData()
{
	// ����Ѫ������100ʱ����Ѫ
	if (man.hp < 100 && man.hp>0)
	{
		timehp++;
		if (timehp == 60)    //����һ�����һ��Ѫ
		{
			man.hp++;
			timehp = 0;
		}
	}
	// �Ʒ�
	timesc++;
	if (timesc % 60 == 0)   //ÿ����һ�����һ��
	{
		score++;
	}
};

// ���°���
void newBrick()
{
	for (index = 0; index < 11; index++)
	{
		if (brick[index].y <= 90)
		{
			brick[index].type = rand() % 6 + 1;
			brick[index].flag = 1;
			brick[index].y = 750;
			brick[index].x = rand() % (400 - xbrick) + 25;
		}
	}
};

// ����������޹ص�λ�ø���
void updateWithoutInput()
{
	//���������˶�
	for (index = 0; index < 11; index++)
	{
		brick[index].y -= vybrick;
	}
	// ������ֱ�����˶�
	for (index = 0; index < 11; index++)
	{
		// �ڰ��� 
		if ((man.y <= brick[index].y - yman + vyman ) && (man.y >= brick[index].y - yman - vyman) && (man.x > brick[index].x - xman + 6) && (man.x < brick[index].x + xbrick - xman / 2))
		{
			if (brick[index].type == 1 || (brick[index].type == 2 && brick[index].flag == 0))
			{
				man.y -= vybrick;
				man.flag = 1;
				if (brick[index].flag == 1)
					msType = 1;
				brick[index].flag = 0;
			}
			else if (brick[index].type == 2 && brick[index].flag == 1)
			{
				man.hp -= 40;
				man.y -= vybrick;
				man.flag = 1;
				msType = 2;
				brick[index].flag = 0;
			}
			else if (brick[index].type == 3)
			{
				man.y -= jump;
				man.flag = 0;
				msType = 3;
				brick[index].flag = 0;
			}
			else if (brick[index].type == 4)
			{
				if (man.x > 25 && man.x < 425 - xman)
				{
					man.x -= fx;
				}
				man.y -= vybrick;
				man.flag = 1;
				if (brick[index].flag == 1)
					msType = 4;
				brick[index].flag = 0;
			}
			else if (brick[index].type == 5)
			{
				if (man.x > 25 && man.x < 425 - xman)
				{
					man.x += fx;
				}
				man.y -= vybrick;
				man.flag = 1;
				if (brick[index].flag == 1)
					msType = 4;
				brick[index].flag = 0;
			}
			else if (brick[index].type == 6 && brick[index].flag == 1)
			{
				man.y -= vybrick;
				if (brick[index].flag == 1 && brick[index].breakTime == 0)
					msType = 5;
				man.flag = 1;
				brick[index].breakTime++;
				if (brick[index].breakTime == 10)
				{
					brick[index].flag = 0;
					brick[index].breakTime = 0;
				}
			}
			vyman = 4;
			break;
		}
		// ���ڰ���
		man.flag = 0;
	}
	// �������ٶ�ʵ��
	if (man.flag == 0)
	{
		man.y += vyman;
		vyman += 0.1;
	}
};

// ����������йص�λ�ø���
void updateWithInput()
{
	// �ж��û�����
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (man.x > 25)
			man.x -= vxman;
		man.walk = 1;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (man.x < 425 - xman)
			man.x += vxman;
		man.walk = 2;
	}
	else
	{
		man.walk = 0;
	}
};

//���ٹ���
void aSpeed()
{
	if (score > 11&&score<80)
	{
		vybrick += 0.001;
		vyman += 0.0001;
	}
	else if (score > 80)
	{
		vybrick += 0.003;
		vyman += 0.003;
	}
}

// ��Ϸ��������
void gameover()
{
	transparentimage(NULL, 25, 163, &Over);
	setbkmode(TRANSPARENT);     // �������ֱ���ģʽΪ TRANSPARENT ʵ����������ޱ���ɫ 
	settextcolor(RGB(255, 0, 0));    // ����������ɫΪ ��ɫ 
	settextstyle(125, 0, _T("����")); // �������ִ�С�����壬��������Ϊ���ߡ������塣����0Ϊ����Ӧ��
	outtextxy(185, 310, temp2);
	
}

// ���̲߳�������
void music(void *pArg)
{
	switch (msType)
	{
	case -1:
		mciSendString("play res/begin.mp3 from 0", 0, 0, 0);
		break;
	case 1:
		mciSendString("play res/brick1.mp3 from 0", 0, 0, 0);
		break;
	case 2:
		mciSendString("play res/brick2.mp3 from 0", 0, 0, 0);
		break;
	case 3:
		mciSendString("play res/brick3.mp3 from 0", 0, 0, 0);
		break;
	case 4:
		mciSendString("play res/brick4.mp3 from 0", 0, 0, 0);
		break;
	case 5:
		mciSendString("play res/brick6.mp3 from 0", 0, 0, 0);
		break;
	case 6:
		mciSendString("play res/die.mp3 from 0", 0, 0, 0);
		break;
	default:
		break;
	}
	msType = 0;
	//_endthread();
}

int game()
{
	loadRes();  //������Դ
	start();    //��ʼ��
	while (man.hp > 0 && man.y < 630 && man.y>90)
	{
		draw();   //���ƻ���
		updateWithInput();   // �������йص�λ�ø���
		updateWithoutInput();   //�������޹ص�λ�ø���
		_beginthread(music, 0, 0);   //������Ч���߳�
		newBrick();    //���°��
		updateData();   //��Ѫ���Ʒֹ���
		aSpeed();     // ���ٹ���
		Sleep(40);    // ��ͣ40����
	}
	EndBatchDraw();  //����������ͼ 
	mciSendString("open res/die.mp3", 0, 0, 0);
	mciSendString("play res/die.mp3 from 0", 0, 0, 0);
	gameover();  // ��Ϸ��������
	while (1)   //�ж��û��Ƿ�����ո�����ո������
	{
		if(getch() == ' ')
			break;
	};   //��ͣ�����
	return score;   //���ص��ַ���
}

