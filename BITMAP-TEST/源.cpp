/******************************************
�ļ����ƣ�main.cpp
�ļ�������ʵ��ͼ�ν�����������Ϸ
���뻷����VS2008-VS2017     VC6.0
����޸ģ�
<2018��1��13��>  <��������>  <���ػ�>
******************************************/

#include"gomoku.h"
#include<stdio.h>
//========================������===========================
int main()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	PlaySound(L"res/flower dance.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC| SND_NODEFAULT);
	Initbefore();
	do {
		cnt = 0;
		chongwan = 0;
		flag = 0;
		GameInit();
		while (flag == 0)
		{
			MouseClick();
			Judge();
			if (chongwan == 1)
				break;
		}
		for (i = 0; i < Num + 1; i++) {
			for (j = 0; j < Num + 1; j++)
			{
				Map[i][j] = 0;
			}
		}
		if (flag)
		{
			settextcolor(hong);
			LOGFONT q;
			gettextstyle(&q);						 // ��ȡ��ǰ��������
			q.lfHeight = 64;						 // ��������߶�Ϊ 24
			_tcscpy_s(q.lfFaceName, _T("����"));	// ��������Ϊ�����顱(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)
			q.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
			settextstyle(&q);						// ����������ʽ
			setbkmode(0);
			TCHAR baoliu[] = _T("�밴���������...");
			outtextxy(170, 400, baoliu);
			getchar();
			FlushMouseMsgBuffer();//��������Ϣ������
		}
		cleardevice();
	} while (1);
	return 0;
}

VOID Initbefore()
{
	srand((unsigned int)time(NULL));
	//loadimage(NULL, _T("IMAGE"), _T("bkimage.ico"));
	loadimage(&Background1, TEXT("res/Background1.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&Background2, TEXT("res/Background2.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&Background3, TEXT("res/Background3.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&Background4, TEXT("res/Background4.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&Background5, TEXT("res/Background5.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&Background6, TEXT("res/Background6.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&Background7, TEXT("res/Background7.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&Background8, TEXT("res/Background8.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&Background9, TEXT("res/Background9.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&Background10, TEXT("res/Backgroun10.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
}
//��Ϸ��ʼ������
VOID GameInit()
{
	putimage(0, 0, &Background6);
	BeginBatchDraw();
	for (i = 0; i < 19; i++)
	{
		setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 2);
		if (i < 7)
			j = i + 1;
		else if (i >= 7 && i<14)
			j = i - 6;
		else j = i - 13;
		switch (j)
		{
		case 1:
			setlinecolor(hong);
			break;
		case 2:
			setlinecolor(cheng);
			break;
		case 3:
			setlinecolor(huang);
			break;
		case 4:
			setlinecolor(lv);
			break;
		case 5:
			setlinecolor(lan);
			break;
		case 6:
			setlinecolor(dian);
			break;
		case 7:
			setlinecolor(zi);
			break;
		}
		line(Leftjie + GeLength*i, UpDownjie, Leftjie + GeLength*i, WINDOW_HEIGHT - UpDownjie);
		line(Leftjie, UpDownjie + GeLength*i, WINDOW_WIDTH - Rightjie, UpDownjie + GeLength*i);
	}
	EndBatchDraw();

	//����Ҳ�˵������
	settextcolor(dian);
	LOGFONT f;
	gettextstyle(&f);						 // ��ȡ��ǰ��������
	f.lfHeight = 24;						 // ��������߶�Ϊ 24
	_tcscpy_s(f.lfFaceName, _T("����"));	// ��������Ϊ�����顱(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	setbkmode(0);

	outtextxy(850, 60, hei);
	outtextxy(850, 90, bai);
	settextcolor(hong);
	outtextxy(850, 150, luozi);
	outtextxy(850,630, qiege);
	outtextxy(850, 670, qiebkp);

	//������Ϸ
	settextcolor(hong);
	outtextxy(850, 390, again);

	//����
	outtextxy(850, 470, huiqi);

	//��Ц
	outtextxy(850, 550, gaoxiao);

	//������ʾ
	settextcolor(lv);
	outtextxy(850, 210, heibu);
	outtextxy(850, 240, baibu);
}

VOID MouseClick()
{
	msg = GetMouseMsg();
	switch (msg.uMsg)
	{
	case WM_LBUTTONUP:
		if (msg.x > 70 && msg.x < 810 && msg.y > 30 && msg.y < 770)
		{
			if (msg.x>100 && msg.y>60)
			{
				if (Map[(msg.x - Leftjie - GeLength / 2) / GeLength + 1][(msg.y - UpDownjie - GeLength / 2) / GeLength + 1] == 0)
				{
					X = (msg.x - Leftjie - GeLength / 2) / GeLength + 1;
					Y = (msg.y - UpDownjie - GeLength / 2) / GeLength + 1;
					Record.rx[cnt] = X;
					Record.ry[cnt] = Y;
					cnt++;
					drawX = ((msg.x - Leftjie - GeLength / 2) / GeLength + 1)*GeLength + Leftjie;
					drawY = ((msg.y - UpDownjie - GeLength / 2) / GeLength + 1)*GeLength + UpDownjie;
					if (cnt % 2) {
						Map[X][Y] = 1;
					}
					else Map[X][Y] = 2;
					if (cnt > 0)
					PlayGame();
				}
				else if (Map[(msg.x - Leftjie - GeLength / 2) / GeLength + 1][(msg.y - UpDownjie - GeLength / 2) / GeLength + 1] == 1 || Map[(msg.x - Leftjie - GeLength / 2) / GeLength + 1][(msg.y - UpDownjie - GeLength / 2) / GeLength + 1] == 2)
				{
					hWnd = GetHWnd();
					MessageBox(hWnd, L"����������Ŷ,��ѡ���", L"Are you���ȣ�", MB_OK);
				}
			}
			else if (msg.x<100 && msg.y > 60)
			{
				if (Map[(msg.x - Leftjie - GeLength / 2) / GeLength][(msg.y - UpDownjie - GeLength / 2) / GeLength + 1] == 0)
				{
					X = 0;
					Y = (msg.y - UpDownjie - GeLength / 2) / GeLength + 1;
					Record.rx[cnt] = X;
					Record.ry[cnt] = Y;
					cnt++;
					drawX = Leftjie;
					drawY = ((msg.y - UpDownjie - GeLength / 2) / GeLength + 1)*GeLength + UpDownjie;
					if (cnt % 2) {
						Map[X][Y] = 1;
					}
					else Map[X][Y] = 2;
					if (cnt > 0)
					PlayGame();
				}
				else if (Map[(msg.x - Leftjie - GeLength / 2) / GeLength][(msg.y - UpDownjie - GeLength / 2) / GeLength + 1] == 1 || Map[(msg.x - Leftjie - GeLength / 2) / GeLength][(msg.y - UpDownjie - GeLength / 2) / GeLength + 1] == 2)
				{
					hWnd = GetHWnd();
					MessageBox(hWnd, L"����������Ŷ,��ѡ���", L"Are you���ȣ�", MB_OK);
				}
			}
			else if (msg.x>100 && msg.y < 60)
			{
				if (Map[(msg.x - Leftjie - GeLength / 2) / GeLength + 1][(msg.y - UpDownjie - GeLength / 2) / GeLength] == 0)
				{
					X = (msg.x - Leftjie - GeLength / 2) / GeLength + 1;
					Y = 0;
					Record.rx[cnt] = X;
					Record.ry[cnt] = Y;
					cnt++;
					drawX = ((msg.x - Leftjie - GeLength / 2) / GeLength + 1)*GeLength + Leftjie;
					drawY = UpDownjie;
					if (cnt % 2) {
						Map[X][Y] = 1;
					}
					else Map[X][Y] = 2;
					if (cnt > 0)
					PlayGame();
				}
				else if (Map[(msg.x - Leftjie - GeLength / 2) / GeLength + 1][(msg.y - UpDownjie - GeLength / 2) / GeLength] == 1 || Map[(msg.x - Leftjie - GeLength / 2) / GeLength + 1][(msg.y - UpDownjie - GeLength / 2) / GeLength] == 2)
				{
					hWnd = GetHWnd();
					MessageBox(hWnd, L"����������Ŷ,��ѡ���", L"Are you���ȣ�", MB_OK);
				}
			}
			else if (msg.x<100 && msg.y < 60)
			{
				if (Map[(msg.x - Leftjie - GeLength / 2) / GeLength][(msg.y - UpDownjie - GeLength / 2) / GeLength] == 0)
				{
					X = 0;
					Y = 0;
					Record.rx[cnt] = X;
					Record.ry[cnt] = Y;
					cnt++;
					drawX = Leftjie;
					drawY = UpDownjie;
					if (cnt % 2) {
						Map[X][Y] = 1;
					}
					else Map[X][Y] = 2;
					if (cnt > 0)
					PlayGame();
				}
				else if (Map[(msg.x - Leftjie - GeLength / 2) / GeLength][(msg.y - UpDownjie - GeLength / 2) / GeLength] == 1 || Map[(msg.x - Leftjie - GeLength / 2) / GeLength][(msg.y - UpDownjie - GeLength / 2) / GeLength] == 2)
				{
					hWnd = GetHWnd();
					MessageBox(hWnd, L"����������Ŷ����ѡ���", L"Are you���ȣ�", MB_OK);
				}
			}
		}
		else if (msg.x >= 845 && msg.y >= 370 && msg.y <= 410)
			chongwan = 1;
		else if (msg.x >= 845 && msg.y >= 450 && msg.y <= 490)
		{
			if (cnt>0)
			{
				Back();
			}
		else {
				hWnd = GetHWnd();
				MessageBox(hWnd, L"����ʲô�����Ѿ��ڵ�ͷ���أ�", L"���Ǻ�����", MB_OK);
			}
		}
		else if (msg.x >= 845 && msg.y >= 530 && msg.y <= 570)
		{
			hWnd = GetHWnd();
			MessageBox(hWnd, L"ū澽��������У���������ĵȴ���", L"��ʵ�Ҳ���д���......", MB_OK);
		}
		else if (msg.x >= 845 && msg.y >= 610 && msg.y <= 650)
		{
			NO_Songs=rand()%SUM_Songs+1;
			ChangeSong();
		}
		else if (msg.x >= 845 && msg.y >= 650 && msg.y <= 690)
		{
			ChangePictures();
		}
		break;
	}
}

VOID PlayGame()
{
	BeginBatchDraw();
	if (cnt % 2)
		setfillcolor(heise);
	else setfillcolor(baise);
	//if (Map[X][Y] == 0)
	solidcircle(drawX, drawY, 19);

	//�Ʋ�
	setcolor(RGB(255, 255, 255));
	setbkmode(OPAQUE);
	heibuS[1] = (int)(cnt - 0.001) / 2 + 1;
	_stprintf_s(heibuS, _T("%d"), heibuS[1]);
	outtextxy(948, 210, heibuS);

	baibuS[1] = cnt / 2;
	_stprintf_s(baibuS, _T("%d"), baibuS[1]);
	outtextxy(948, 240, baibuS);

	//�ֵ������ʾ
	if (cnt % 2) {
		wanjia[1] = 2;
	}
	else wanjia[1] = 1;
	_stprintf_s(wanjia, _T("%d"), wanjia[1]);
	outtextxy(905, 150, wanjia);
	EndBatchDraw();
}

VOID Judge()
{
	//����Ӯ
	if (
		(Map[X][Y] == 1 && Map[X + 1][Y] == 1 && Map[X + 2][Y] == 1 && Map[X + 3][Y] == 1 && Map[X + 4][Y] == 1) ||
		(Map[X - 1][Y] == 1 && Map[X][Y] == 1 && Map[X + 1][Y] == 1 && Map[X + 2][Y] == 1 && Map[X + 3][Y] == 1) ||
		(Map[X - 2][Y] == 1 && Map[X - 1][Y] == 1 && Map[X][Y] == 1 && Map[X + 1][Y] == 1 && Map[X + 2][Y] == 1) ||
		(Map[X - 3][Y] == 1 && Map[X - 2][Y] == 1 && Map[X - 1][Y] == 1 && Map[X][Y] == 1 && Map[X + 1][Y] == 1) ||
		(Map[X - 4][Y] == 1 && Map[X - 3][Y] == 1 && Map[X - 2][Y] == 1 && Map[X - 1][Y] == 1 && Map[X][Y] == 1) ||
		(Map[X][Y] == 1 && Map[X][Y + 1] == 1 && Map[X][Y + 2] == 1 && Map[X][Y + 3] == 1 && Map[X][Y + 4] == 1) ||
		(Map[X][Y - 1] == 1 && Map[X][Y] == 1 && Map[X][Y + 1] == 1 && Map[X][Y + 2] == 1 && Map[X][Y + 3] == 1) ||
		(Map[X][Y - 2] == 1 && Map[X][Y - 1] == 1 && Map[X][Y] == 1 && Map[X][Y + 1] == 1 && Map[X][Y + 2] == 1) ||
		(Map[X][Y - 3] == 1 && Map[X][Y - 2] == 1 && Map[X][Y - 1] == 1 && Map[X][Y] == 1 && Map[X][Y + 1] == 1) ||
		(Map[X][Y - 4] == 1 && Map[X][Y - 3] == 1 && Map[X][Y - 2] == 1 && Map[X][Y - 1] == 1 && Map[X][Y] == 1) ||
		(Map[X][Y] == 1 && Map[X + 1][Y - 1] == 1 && Map[X + 2][Y - 2] == 1 && Map[X + 3][Y - 3] == 1 && Map[X + 4][Y - 4] == 1) ||
		(Map[X - 1][Y + 1] == 1 && Map[X][Y] == 1 && Map[X + 1][Y - 1] == 1 && Map[X + 2][Y - 2] == 1 && Map[X + 3][Y - 3] == 1) ||
		(Map[X - 2][Y + 2] == 1 && Map[X - 1][Y + 1] == 1 && Map[X][Y] == 1 && Map[X + 1][Y - 1] == 1 && Map[X + 2][Y - 2] == 1) ||
		(Map[X - 3][Y + 3] == 1 && Map[X - 2][Y + 2] == 1 && Map[X - 1][Y + 1] == 1 && Map[X][Y] == 1 && Map[X + 1][Y - 1] == 1) ||
		(Map[X - 4][Y + 4] == 1 && Map[X - 3][Y + 3] == 1 && Map[X - 2][Y + 2] == 1 && Map[X - 1][Y + 1] == 1 && Map[X][Y] == 1) ||
		(Map[X][Y] == 1 && Map[X + 1][Y + 1] == 1 && Map[X + 2][Y + 2] == 1 && Map[X + 3][Y + 3] == 1 && Map[X + 4][Y + 4] == 1) ||
		(Map[X - 1][Y - 1] == 1 && Map[X][Y] == 1 && Map[X + 1][Y + 1] == 1 && Map[X + 2][Y + 2] == 1 && Map[X + 3][Y + 3] == 1) ||
		(Map[X - 2][Y - 2] == 1 && Map[X - 1][Y - 1] == 1 && Map[X][Y] == 1 && Map[X + 1][Y + 1] == 1 && Map[X + 2][Y + 2] == 1) ||
		(Map[X - 3][Y - 3] == 1 && Map[X - 2][Y - 2] == 1 && Map[X - 1][Y - 1] == 1 && Map[X][Y] == 1 && Map[X + 1][Y + 1] == 1) ||
		(Map[X - 4][Y - 4] == 1 && Map[X - 3][Y - 3] == 1 && Map[X - 2][Y - 2] == 1 && Map[X - 1][Y - 1] == 1 && Map[X][Y] == 1)
		)
		flag = 1;

	//����Ӯ
	if (
		(Map[X][Y] == 2 && Map[X + 1][Y] == 2 && Map[X + 2][Y] == 2 && Map[X + 3][Y] == 2 && Map[X + 4][Y] == 2) ||
		(Map[X - 1][Y] == 2 && Map[X][Y] == 2 && Map[X + 1][Y] == 2 && Map[X + 2][Y] == 2 && Map[X + 3][Y] == 2) ||
		(Map[X - 2][Y] == 2 && Map[X - 1][Y] == 2 && Map[X][Y] == 2 && Map[X + 1][Y] == 2 && Map[X + 2][Y] == 2) ||
		(Map[X - 3][Y] == 2 && Map[X - 2][Y] == 2 && Map[X - 1][Y] == 2 && Map[X][Y] == 2 && Map[X + 1][Y] == 2) ||
		(Map[X - 4][Y] == 2 && Map[X - 3][Y] == 2 && Map[X - 2][Y] == 2 && Map[X - 1][Y] == 2 && Map[X][Y] == 2) ||
		(Map[X][Y] == 2 && Map[X][Y + 1] == 2 && Map[X][Y + 2] == 2 && Map[X][Y + 3] == 2 && Map[X][Y + 4] == 2) ||
		(Map[X][Y - 1] == 2 && Map[X][Y] == 2 && Map[X][Y + 1] == 2 && Map[X][Y + 2] == 2 && Map[X][Y + 3] == 2) ||
		(Map[X][Y - 2] == 2 && Map[X][Y - 1] == 2 && Map[X][Y] == 2 && Map[X][Y + 1] == 2 && Map[X][Y + 2] == 2) ||
		(Map[X][Y - 3] == 2 && Map[X][Y - 2] == 2 && Map[X][Y - 1] == 2 && Map[X][Y] == 2 && Map[X][Y + 1] == 2) ||
		(Map[X][Y - 4] == 2 && Map[X][Y - 3] == 2 && Map[X][Y - 2] == 2 && Map[X][Y - 1] == 2 && Map[X][Y] == 2) ||
		(Map[X][Y] == 2 && Map[X + 1][Y - 1] == 2 && Map[X + 2][Y - 2] == 2 && Map[X + 3][Y - 3] == 2 && Map[X + 4][Y - 4] == 2) ||
		(Map[X - 1][Y + 1] == 2 && Map[X][Y] == 2 && Map[X + 1][Y - 1] == 2 && Map[X + 2][Y - 2] == 2 && Map[X + 3][Y - 3] == 2) ||
		(Map[X - 2][Y + 2] == 2 && Map[X - 1][Y + 1] == 2 && Map[X][Y] == 2 && Map[X + 1][Y - 1] == 2 && Map[X + 2][Y - 2] == 2) ||
		(Map[X - 3][Y + 3] == 2 && Map[X - 2][Y + 2] == 2 && Map[X - 1][Y + 1] == 2 && Map[X][Y] == 2 && Map[X + 1][Y - 1] == 2) ||
		(Map[X - 4][Y + 4] == 2 && Map[X - 3][Y + 3] == 2 && Map[X - 2][Y + 2] == 2 && Map[X - 1][Y + 1] == 2 && Map[X][Y] == 2) ||
		(Map[X][Y] == 2 && Map[X + 1][Y + 1] == 2 && Map[X + 2][Y + 2] == 2 && Map[X + 3][Y + 3] == 2 && Map[X + 4][Y + 4] == 2) ||
		(Map[X - 1][Y - 1] == 2 && Map[X][Y] == 2 && Map[X + 1][Y + 1] == 2 && Map[X + 2][Y + 2] == 2 && Map[X + 3][Y + 3] == 2) ||
		(Map[X - 2][Y - 2] == 2 && Map[X - 1][Y - 1] == 2 && Map[X][Y] == 2 && Map[X + 1][Y + 1] == 2 && Map[X + 2][Y + 2] == 2) ||
		(Map[X - 3][Y - 3] == 2 && Map[X - 2][Y - 2] == 2 && Map[X - 1][Y - 1] == 2 && Map[X][Y] == 2 && Map[X + 1][Y + 1] == 2) ||
		(Map[X - 4][Y - 4] == 2 && Map[X - 3][Y - 3] == 2 && Map[X - 2][Y - 2] == 2 && Map[X - 1][Y - 1] == 2 && Map[X][Y] == 2)
		)
		flag = 2;
	if (flag == 1) {
		hWnd = GetHWnd();
		MessageBox(hWnd, L"����ʤ", L"��ϲ��", MB_OK);
	}
	else if (flag == 2)
	{
		hWnd = GetHWnd();
		MessageBox(hWnd, L"����ʤ", L"��ϲ��", MB_OK);
	}
}

//����
VOID Back()
{
	//cleardevice();
	GameInit();
	if(cnt>0)
	cnt--;
	X=Record.rx[cnt];
	Y=Record.ry[cnt];
	Map[X][Y] = 0;

	for (i = 0; i < Num + 1; i++)
	{
		for (j = 0; j < Num + 1; j++)
		{
			if (Map[i][j]==1)
				setfillcolor(heise);
			else if(Map[i][j]==2)
				setfillcolor(baise);
			else continue;
			drawX = Leftjie + i*GeLength;
			drawY = UpDownjie + j*GeLength;
			solidcircle(drawX, drawY, 19);
		}
	}
	//�Ʋ�
	setcolor(RGB(255, 255, 255));
	setbkmode(OPAQUE);
	if (cnt == 0)
	{
		heibuS[1] = 0;
	}else 
	heibuS[1] = (int)(cnt - 0.001) / 2 + 1;
	_stprintf_s(heibuS, _T("%d"), heibuS[1]);
	outtextxy(948, 210, heibuS);

	baibuS[1] = cnt / 2;
	_stprintf_s(baibuS, _T("%d"), baibuS[1]);
	outtextxy(948, 240, baibuS);

	//�ֵ������ʾ
	if (cnt % 2) {
		wanjia[1] = 2;
	}
	else wanjia[1] = 1;
	_stprintf_s(wanjia, _T("%d"), wanjia[1]);
	outtextxy(905, 150, wanjia);
}

VOID ChangeSong()
{
	PlaySound(NULL, NULL, SND_FILENAME);
	switch (NO_Songs)
	{
	case 1:
		PlaySound(L"res/han.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		break;
	case 2:
		PlaySound(L"res/flower dance.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		break;
	case 3:
		PlaySound(L"res/������ - һ�׺����Ĺ�����.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		break;
	case 4:
		PlaySound(L"res/�����  ������ - ɨ��2.0.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		break;
	case 5:
		PlaySound(L"res/����.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		break;
	}
}

VOID ChangePictures()
{
	NO_Pictures = rand() % SUM_Pictures + 1;
	switch (NO_Pictures)
	{
	case 1:
		putimage(0, 0, &Background1);
		break;
	case 2:
		putimage(0, 0, &Background2);
		break;
	case 3:
		putimage(0, 0, &Background3);
		break;
	case 4:
		putimage(0, 0, &Background4);
		break;
	case 5:
		putimage(0, 0, &Background5);
		break;
	case 6:
		putimage(0, 0, &Background6);
		break;
	case 7:
		putimage(0, 0, &Background7);
		break;
	case 8:
		putimage(0, 0, &Background8);
		break;
	case 9:
		putimage(0, 0, &Background9);
		break;
	case 10:
		putimage(0, 0, &Background10);
		break;
	}

	BeginBatchDraw();
	for (i = 0; i < 19; i++)
	{
		setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 2);
		if (i < 7)
			j = i + 1;
		else if (i >= 7 && i<14)
			j = i - 6;
		else j = i - 13;
		switch (j)
		{
		case 1:
			setlinecolor(hong);
			break;
		case 2:
			setlinecolor(cheng);
			break;
		case 3:
			setlinecolor(huang);
			break;
		case 4:
			setlinecolor(lv);
			break;
		case 5:
			setlinecolor(lan);
			break;
		case 6:
			setlinecolor(dian);
			break;
		case 7:
			setlinecolor(zi);
			break;
		}
		line(Leftjie + GeLength*i, UpDownjie, Leftjie + GeLength*i, WINDOW_HEIGHT - UpDownjie);
		line(Leftjie, UpDownjie + GeLength*i, WINDOW_WIDTH - Rightjie, UpDownjie + GeLength*i);

	}
	EndBatchDraw();

	//����Ҳ�˵������
	settextcolor(dian);
	LOGFONT f;
	gettextstyle(&f);						 // ��ȡ��ǰ��������
	f.lfHeight = 24;						 // ��������߶�Ϊ 24
	_tcscpy_s(f.lfFaceName, _T("����"));	// ��������Ϊ�����顱(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	setbkmode(0);

	outtextxy(850, 60, hei);
	outtextxy(850, 90, bai);
	settextcolor(hong);
	outtextxy(850, 150, luozi);
	outtextxy(850, 630, qiege);
	outtextxy(850, 670, qiebkp);

	//������Ϸ
	settextcolor(hong);
	outtextxy(850, 390, again);

	//����
	outtextxy(850, 470, huiqi);

	//��Ц
	outtextxy(850, 550, gaoxiao);

	//������ʾ
	settextcolor(lv);
	outtextxy(850, 210, heibu);
	outtextxy(850, 240, baibu);
	//�Ʋ�
	setcolor(RGB(255, 255, 255));
	setbkmode(OPAQUE);
	if (cnt == 0)
	{
		heibuS[1] = 0;
	}
	else
		heibuS[1] = (int)(cnt - 0.001) / 2 + 1;
	_stprintf_s(heibuS, _T("%d"), heibuS[1]);
	outtextxy(948, 210, heibuS);

	baibuS[1] = cnt / 2;
	_stprintf_s(baibuS, _T("%d"), baibuS[1]);
	outtextxy(948, 240, baibuS);

	//�ֵ������ʾ
	if (cnt % 2) {
		wanjia[1] = 2;
	}
	else wanjia[1] = 1;
	_stprintf_s(wanjia, _T("%d"), wanjia[1]);
	outtextxy(905, 150, wanjia);


	for (i = 0; i < Num + 1; i++)
	{
		for (j = 0; j < Num + 1; j++)
		{
			if (Map[i][j] == 1)
				setfillcolor(heise);
			else if (Map[i][j] == 2)
				setfillcolor(baise);
			else continue;
			drawX = Leftjie + i*GeLength;
			drawY = UpDownjie + j*GeLength;
			solidcircle(drawX, drawY, 19);
		}
	}
}