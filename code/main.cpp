#include "Head.h"

using namespace std;

// ϵͳ
string Firmware_Version = "13.2.1";

#define Title "Arceus 901"
#define App "Arceus"
#define X 960
#define Y 540


// ����
// ����������
double decimal_total = 0, decimal_avl = 0;
#define  GBYTES  1073741824    
#define  MBYTES  1048576    
#define  KBYTES  1024    
#define  DKBYTES 1024.0
// �������
int button_wait = 1;

// ������ɫ
int light_color[10] = { 12, 14, 10, 15, 4, 6, 2, 8 };
int deviation = 11;

// ����
int lan;

// ����
const int NR = 10010;
int code[NR];

// ��ʾ
bool light[10];
bool digital[35];
int show_cnt = 0;
bool show = false;

// ����
bool key[110];
bool keydown = false;

// ����ʱ����
int cnt = 0, pos = 0, all, main_pos, now;
bool is_run = false, digit = false, is_edit = false, is_standby, is_save = false, show_c = false;

// �ȶ�ʱ��
clock_t begint;


// Debug����
void error(string message)
{
	stringstream ss;
	ss << pos;
	string pos_s;
	ss >> pos_s;
	message = message + "\n" + ((lan == 1) ? ("λ��") : ("Pos")) +  " : " + pos_s;
	MessageBox(0, message.c_str(), App, MB_OK);
	getch();
	exit(0);
}

void check_code(int n)
{
	for (int i = 0; i <= n; i++)
	{
		if (code[i] < 10) printf("0");
		printf("%d ", code[i]);
	}
}

void test_light()
{
	while (1)
	{
		if (KEY_DOWN('1')) light[0] = true;
		else light[0] = false;
		if (KEY_DOWN('2')) light[1] = true;
		else light[1] = false;
		if (KEY_DOWN('3')) light[2] = true;
		else light[2] = false;
		if (KEY_DOWN('4')) light[3] = true;
		else light[3] = false;
		if (KEY_DOWN('5')) light[4] = true;
		else light[4] = false;
		if (KEY_DOWN('6')) light[5] = true;
		else light[5] = false;
		if (KEY_DOWN('7')) light[6] = true;
		else light[6] = false;
		if (KEY_DOWN('8')) light[7] = true;
		else light[7] = false;
		Sleep(1);
	}
	return;
}

// ���ܺ���
void chooselan()
{
	const LANGID lid = GetSystemDefaultLangID();
	switch (lid)
	{
		//Ӣ�� 
	case 0x0409:
		lan = 0;
		break;
	case 0x0809:
		lan = 0;
		break;
	case 0x0c09:
		lan = 0;
		break;
	case 0x1009:
		lan = 0;
		break;
	case 0x1409:
		lan = 0;
		break;
	case 0x1809:
		lan = 0;
		break;
	case 0x1c09:
		lan = 0;
		break;
	case 0x2009:
		lan = 0;
		break;
	case 0x2409:
		lan = 0;
		break;
	case 0x2809:
		lan = 0;
		break;
	case 0x2c09:
		lan = 0;
		break;

		//���ļ���
	case 0X0804:
		lan = 1;
		break;

		//���ķ��� 
	case 0X0404:
		lan = 2;
		break;
	case 0X0c04:
		lan = 2;
		break;
	case 0X1004:
		lan = 2;
		break;
		//����
	case 0X0411:
		lan = 3;
		break;
		//����
	case 0X0412:
		lan = 4;
		break;
	case 0X0812:
		lan = 4;
		break;

	default: break;
	}
}
void standby()
{
	is_standby = true;
	is_run = false;
	is_edit = false;
	memset(digital, false, sizeof(digital));
	digital[1] = true;
	digital[2] = true;
	digital[3] = true;
	digital[4] = true;
	digital[6] = true;
	digital[8] = true;
	digital[9] = true;
	digital[12] = true;
	digital[13] = true;
	digital[14] = true;
	digital[22] = true;
	digital[24] = true;
	digital[25] = true;
	digital[26] = true;
	digital[27] = true;
	digital[29] = true;
	digital[30] = true;
	memset(key, false, sizeof(key));
	memset(light, false, sizeof(light));
	while (!(KEY_DOWN('D') || KEY_DOWN('R') || KEY_DOWN('F') || KEY_DOWN('U') || KEY_DOWN('J') || KEY_DOWN('K'))) continue;
	memset(digital, false, sizeof(digital));
	pos = 0;
	is_run = false;
	now = code[pos];
	is_standby = false;
}

void waitfor()
{
	if (KEY_DOWN('D') || KEY_DOWN('R') || KEY_DOWN('F') || KEY_DOWN('U') || KEY_DOWN('J') || KEY_DOWN('K') || KEY_DOWN('N')) while (1) if (!(KEY_DOWN('D') || KEY_DOWN('R') || KEY_DOWN('F') || KEY_DOWN('U') || KEY_DOWN('J') || KEY_DOWN('K') || KEY_DOWN('N'))) break;
	memset(digital, false, sizeof(digital));
	digital[3] = true;
	digital[4] = true;
	digital[5] = true;
	digital[9] = true;
	digital[10] = true;
	digital[11] = true;
	digital[12] = true;
	digital[14] = true;
	digital[24] = true;
	digital[25] = true;
	digital[26] = true;
	digital[27] = true;
	digital[28] = true;
	digital[29] = true;
	memset(key, false, sizeof(key));
	while (1)
	{
		is_edit = false;
		if (KEY_DOWN('K'))
		{
			is_edit = true;
			break;
		}
		if (KEY_DOWN('J'))
		{
			pos = 0;
			show = false;
			cnt = 0;
			digit = false;
			is_run = true;
			break;
		}
		Sleep(1);
	}
	memset(digital, false, sizeof(digital));
	
}

void playsound() // �������� δ���
{
	pos++;
	pos++;
	return;
}

void save()
{
	while (1)
	{
		if (is_save == true)
		{
			ofstream out("code.txt", ios::binary);
			for (int i = 0; i < all; i++)
			{
				if (code[i] < 10) out << 0;
				out << code[i] << endl;
			}
			// out.close();
			is_save = false;
		}
	}
}

// ����
void initialization() // ��ʼ��
{
	// ����
	const int x = GetSystemMetrics(SM_CXSCREEN);
	const int y = GetSystemMetrics(SM_CYSCREEN);
	SetConsoleTitle(TEXT(Title));
	system("mode con cols=101 lines=27");
	HWND hWnd = FindWindow(NULL, Title);
	MoveWindow(hWnd, (x * 3 - X * 2) / 8, (y - Y) / 2, X, Y, true);
	HindCursor();

	// ��ʼ������
	memset(code, 0, sizeof(code));
	memset(light, false, sizeof(light));
	memset(digital, false, sizeof(digital));
	memset(key, false, sizeof(key));

	// ѡ������
	chooselan();

	// ��ȡ����
	ifstream in("code.txt", ios::binary);
	if (!in)
	{
		MessageBox(0, ((lan == 1) ? ("δ�ҵ������ļ�!\n�뽫����д�� \"code.txt\" ��!") : ("No Code File Founded!\nPlease write your code in \"code.txt\" !")), Title, MB_OK);
		ofstream out("code.txt", ios::binary);
		out.close();
	}
	else
	{
		int i = 0;
		while (in >> code[i++]);
		//check_code(--i);
		all = i - 1;
	}
	in.close();

	// ��������
	ifstream in1("D:\\Data\\Arceus\\Run.Ceh", ios::binary);
	if (!in1)
	{
		CreateDirectory(_T("D:\\Data\\"), NULL);
		SetFileAttributes("D:\\Data\\", FILE_ATTRIBUTE_HIDDEN);
		CreateDirectory(_T("D:\\Data\\Arceus\\"), NULL);
		ofstream out("D:\\Data\\Arceus\\Run.Ceh", ios::binary);
		MessageBox(0, ((lan == 1) ? ("Arceus ��һ��ʵ���ԵĿ�Դ dp901 ģ������\n\n��������Ӧ�������зǷ�ȡ�õĲ����롣\n\n\"dp901\"�ǵ�Ƭ�������ơ�Arceus�뵥Ƭ��û���κι�ϵ��") : ("Arceus is an experimental open-source emulator for the dp901 singlechip.\n\nThis software should not be used to run codes you have not legally obtained.\n\n\"dp901\" is the name of singlechip. Arceus is not affliated with singlechip in anyway.")), App, MB_OK);
		MessageBox(0, ((lan == 1) ? ("11-15�Ű�����Ӧ D R F U J K\n��λ�����Ϊ100 ��Ӧ N ��") : ("Keys 11-15 correspond to keys D R F U J K\nThe number of reset key is 100, corresponding to n key")), App, MB_OK);
		out.close();
	}
	in.close();

	// �˳��󱣴�
	// atexit(save);

	return;
}

void input()
{
	while (1)
	{
		if (KEY_DOWN('D')) key[10] = true;
		else key[10] = false;
		if (KEY_DOWN('R')) key[11] = true;
		else key[11] = false;
		if (KEY_DOWN('F')) key[12] = true;
		else key[12] = false;
		if (KEY_DOWN('U')) key[13] = true;
		else key[13] = false;
		if (KEY_DOWN('J')) key[14] = true;
		else key[14] = false;
		if (KEY_DOWN('K')) key[15] = true;
		else key[15] = false;
		if (KEY_DOWN('N'))
		{
			key[100] = true;
			standby();
			if (KEY_DOWN('D') || KEY_DOWN('R') || KEY_DOWN('F') || KEY_DOWN('U') ||  KEY_DOWN('J') || KEY_DOWN('K') || KEY_DOWN('N'))
			{
				while (1)
				{
					if (!(KEY_DOWN('D') || KEY_DOWN('R') || KEY_DOWN('F') || KEY_DOWN('U') || KEY_DOWN('J') || KEY_DOWN('K') || KEY_DOWN('N')))
					{
						break;
					}
				}
			}
			is_edit = true;
		}
		else key[100] = false;
		if (KEY_DOWN('D') || KEY_DOWN('R') || KEY_DOWN('F') || KEY_DOWN('J') || KEY_DOWN('K') || KEY_DOWN('N')) keydown = true;
		else keydown = false;
		Sleep(1);
	}
}

void display()
{
	while (1)
	{
		float cd = 1000 / 60.0f;// ÿ��60֡ 
		clock_t beginClock = clock();
		float totalCd = 0.0f;
		while (1)
		{
			if (clock() >= beginClock + (int)totalCd)
			{
				totalCd += cd;
				// ����
				for (int i = 0; i <= 7; i++)
				{
					if (light[i] == true) tellraw(light_color[i % 4], i * 5 + deviation, 8, "��");
					else tellraw(light_color[i % 4 + 4], i * 5 + deviation, 8, "��");
				}
				for (int i = 0; i <= 7; i++)
				{
					color(7); gotoxy(i * 5 + deviation, 9); printf("0%d", i);
				}

				// ������
				for (int i = 0; i <= 3; i++)
				{
					int x = 35, y = 11;
					if (digital[i * 8] == true) color(12);
					else color(8);
					SetPosition(x + i * 13 + 2, y); printf("����");
					if (digital[i * 8 + 1] == true) color(12);
					else color(8);
					SetPosition(x + i * 13 + 6, y + 1); printf("��");
					SetPosition(x + i * 13 + 6, y + 2); printf("��");
					if (digital[i * 8 + 2] == true) color(12);
					else color(8);
					SetPosition(x + i * 13 + 6, y + 4); printf("��");
					SetPosition(x + i * 13 + 6, y + 5); printf("��");
					if (digital[i * 8 + 3] == true) color(12);
					else color(8);
					SetPosition(x + i * 13 + 2, y + 6); printf("����");
					if (digital[i * 8 + 4] == true) color(12);
					else color(8);
					SetPosition(x + i * 13, y + 4); printf("��");
					SetPosition(x + i * 13, y + 5); printf("��");
					if (digital[i * 8 + 5] == true) color(12);
					else color(8);
					SetPosition(x + i * 13, y + 1); printf("��");
					SetPosition(x + i * 13, y + 2); printf("��");
					if (digital[i * 8 + 6] == true) color(12);
					else color(8);
					SetPosition(x + i * 13 + 2, y + 3); printf("����");
					if (digital[i * 8 + 7] == true) color(12);
					else color(8);
					SetPosition(x + i * 13 + 9, y + 6); printf("��");
				}
				// ��ť
				if (key[10] == true) tellraw(15, 9, 21, " ��");
				else tellraw(8, 9, 21, " ��");
				tellraw(7, 9, 20, "����");
				if (key[11] == true) tellraw(15, 13, 20, "��");
				else tellraw(8, 13, 20, "��");
				tellraw(7, 13, 19, "+1");
				if (key[12] == true) tellraw(15, 13, 22, "��");
				else tellraw(8, 13, 22, "��");
				tellraw(7, 13, 23, "-1");
				if (key[13] == true) tellraw(15, 45, 20, " ��");
				else tellraw(8, 45, 20, " ��");
				tellraw(7, 44, 19, "����/��ַ");
				if (key[14] == true) tellraw(15, 45, 22, " ��");
				else tellraw(8, 45, 22, " ��");
				tellraw(7, 44, 23, "ִ��/����");
				if (key[15] == true) tellraw(15, 49, 21, " ��");
				else tellraw(8, 49, 21, " ��");
				tellraw(7, 49, 20, "ȷ��");
				if (KEY_DOWN('N')) tellraw(15, 40, 26, " ��");
				else tellraw(8, 40, 26, " ��");
				tellraw(7, 40, 25, "��λ");

				// ��ʱ�ȶ�60֡
				if(totalCd - clock() > 0) Sleep((int)(totalCd - clock()));
				//error("display");
				//break;
			}
			
		}
	}
}
void show_num()
{
	while (1)
	{
		if (is_edit == true)
		{
			int start = 0;
			// MessageBox(0, to_string(show_cnt).c_str(), App, MB_OK);
			if (pos >= 10)
			{
				if (pos / 10 == 1)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start + 1] = true;
					digital[start + 2] = true;
				}
				if (pos / 10 == 2)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start] = true;
					digital[start + 1] = true;
					digital[start + 3] = true;
					digital[start + 4] = true;
					digital[start + 6] = true;
				}
				if (pos / 10 == 3)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start] = true;
					digital[start + 1] = true;
					digital[start + 2] = true;
					digital[start + 3] = true;
					digital[start + 6] = true;
				}
				if (pos / 10 == 4)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start + 1] = true;
					digital[start + 2] = true;
					digital[start + 5] = true;
					digital[start + 6] = true;
				}
				if (pos / 10 == 5)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start] = true;
					digital[start + 2] = true;
					digital[start + 3] = true;
					digital[start + 5] = true;
					digital[start + 6] = true;
				}
				if (pos / 10 == 6)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start] = true;
					digital[start + 2] = true;
					digital[start + 3] = true;
					digital[start + 4] = true;
					digital[start + 5] = true;
					digital[start + 6] = true;
				}
				if (pos / 10 == 7)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start] = true;
					digital[start + 1] = true;
					digital[start + 2] = true;
				}
				if (pos / 10 == 8)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = true;
					digital[start + 7] = false;
				}
				if (pos / 10 == 9)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = true;
					digital[start + 4] = false;
					digital[start + 7] = false;
				}
			}
			else
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = true;
				digital[start + 6] = false;
				digital[start + 7] = false;
			}
			start = 8;
			if (pos % 10 == 0)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = true;
				digital[start + 6] = false;
				digital[start + 7] = false;
			}
			if (pos % 10 == 1)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start + 1] = true;
				digital[start + 2] = true;
			}
			if (pos % 10 == 2)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start] = true;
				digital[start + 1] = true;
				digital[start + 3] = true;
				digital[start + 4] = true;
				digital[start + 6] = true;
			}
			if (pos % 10 == 3)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start] = true;
				digital[start + 1] = true;
				digital[start + 2] = true;
				digital[start + 3] = true;
				digital[start + 6] = true;
			}
			if (pos % 10 == 4)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start + 1] = true;
				digital[start + 2] = true;
				digital[start + 5] = true;
				digital[start + 6] = true;
			}
			if (pos % 10 == 5)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start] = true;
				digital[start + 2] = true;
				digital[start + 3] = true;
				digital[start + 5] = true;
				digital[start + 6] = true;
			}
			if (pos % 10 == 6)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start] = true;
				digital[start + 2] = true;
				digital[start + 3] = true;
				digital[start + 4] = true;
				digital[start + 5] = true;
				digital[start + 6] = true;
			}
			if (pos % 10 == 7)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start] = true;
				digital[start + 1] = true;
				digital[start + 2] = true;
			}
			if (pos % 10 == 8)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = true;
				digital[start + 7] = false;
			}
			if (pos % 10 == 9)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = true;
				digital[start + 4] = false;
				digital[start + 7] = false;
			}
			digital[15] = true;
			if (pos > 99) digital[7] = true;

			start = 16;
			// MessageBox(0, to_string(show_cnt).c_str(), App, MB_OK);
			if (now >= 10)
			{
				if (now / 10 == 1)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start + 1] = true;
					digital[start + 2] = true;
				}
				if (now / 10 == 2)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start] = true;
					digital[start + 1] = true;
					digital[start + 3] = true;
					digital[start + 4] = true;
					digital[start + 6] = true;
				}
				if (now / 10 == 3)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start] = true;
					digital[start + 1] = true;
					digital[start + 2] = true;
					digital[start + 3] = true;
					digital[start + 6] = true;
				}
				if (now / 10 == 4)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start + 1] = true;
					digital[start + 2] = true;
					digital[start + 5] = true;
					digital[start + 6] = true;
				}
				if (now / 10 == 5)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start] = true;
					digital[start + 2] = true;
					digital[start + 3] = true;
					digital[start + 5] = true;
					digital[start + 6] = true;
				}
				if (now / 10 == 6)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start] = true;
					digital[start + 2] = true;
					digital[start + 3] = true;
					digital[start + 4] = true;
					digital[start + 5] = true;
					digital[start + 6] = true;
				}
				if (now / 10 == 7)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start] = true;
					digital[start + 1] = true;
					digital[start + 2] = true;
				}
				if (now / 10 == 8)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = true;
					digital[start + 7] = false;
				}
				if (now / 10 == 9)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = true;
					digital[start + 4] = false;
					digital[start + 7] = false;
				}
			}
			else
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = true;
				digital[start + 6] = false;
				digital[start + 7] = false;
			}
			start = 24;
			if (now % 10 == 0)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = true;
				digital[start + 6] = false;
				digital[start + 7] = false;
			}
			if (now % 10 == 1)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start + 1] = true;
				digital[start + 2] = true;
			}
			if (now % 10 == 2)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start] = true;
				digital[start + 1] = true;
				digital[start + 3] = true;
				digital[start + 4] = true;
				digital[start + 6] = true;
			}
			if (now % 10 == 3)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start] = true;
				digital[start + 1] = true;
				digital[start + 2] = true;
				digital[start + 3] = true;
				digital[start + 6] = true;
			}
			if (now % 10 == 4)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start + 1] = true;
				digital[start + 2] = true;
				digital[start + 5] = true;
				digital[start + 6] = true;
			}
			if (now % 10 == 5)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start] = true;
				digital[start + 2] = true;
				digital[start + 3] = true;
				digital[start + 5] = true;
				digital[start + 6] = true;
			}
			if (now % 10 == 6)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start] = true;
				digital[start + 2] = true;
				digital[start + 3] = true;
				digital[start + 4] = true;
				digital[start + 5] = true;
				digital[start + 6] = true;
			}
			if (now % 10 == 7)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start] = true;
				digital[start + 1] = true;
				digital[start + 2] = true;
			}
			if (now % 10 == 8)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = true;
				digital[start + 7] = false;
			}
			if (now % 10 == 9)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = true;
				digital[start + 4] = false;
				digital[start + 7] = false;
			}
		}
		else if (show == true)
		{
			int start = 16;
			// MessageBox(0, to_string(show_cnt).c_str(), App, MB_OK);
			if (show_cnt >= 10)
			{
				if (show_cnt / 10 == 1)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start + 1] = true;
					digital[start + 2] = true;
				}
				if (show_cnt / 10 == 2)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start] = true;
					digital[start + 1] = true;
					digital[start + 3] = true;
					digital[start + 4] = true;
					digital[start + 6] = true;
				}
				if (show_cnt / 10 == 3)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start] = true;
					digital[start + 1] = true;
					digital[start + 2] = true;
					digital[start + 3] = true;
					digital[start + 6] = true;
				}
				if (show_cnt / 10 == 4)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start + 1] = true;
					digital[start + 2] = true;
					digital[start + 5] = true;
					digital[start + 6] = true;
				}
				if (show_cnt / 10 == 5)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start] = true;
					digital[start + 2] = true;
					digital[start + 3] = true;
					digital[start + 5] = true;
					digital[start + 6] = true;
				}
				if (show_cnt / 10 == 6)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start] = true;
					digital[start + 2] = true;
					digital[start + 3] = true;
					digital[start + 4] = true;
					digital[start + 5] = true;
					digital[start + 6] = true;
				}
				if (show_cnt / 10 == 7)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = false;
					digital[start] = true;
					digital[start + 1] = true;
					digital[start + 2] = true;
				}
				if (show_cnt / 10 == 8)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = true;
					digital[start + 7] = false;
				}
				if (show_cnt / 10 == 9)
				{
					for (int i = 0; i < 8; i++)
						digital[start + i] = true;
					digital[start + 4] = false;
					digital[start + 7] = false;
				}
			}
			else
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
			}
			start = 24;
			if (show_cnt % 10 == 0)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = true;
				digital[start + 6] = false;
				digital[start + 7] = false;
			}
			if (show_cnt % 10 == 1)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start + 1] = true;
				digital[start + 2] = true;
			}
			if (show_cnt % 10 == 2)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start] = true;
				digital[start + 1] = true;
				digital[start + 3] = true;
				digital[start + 4] = true;
				digital[start + 6] = true;
			}
			if (show_cnt % 10 == 3)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start] = true;
				digital[start + 1] = true;
				digital[start + 2] = true;
				digital[start + 3] = true;
				digital[start + 6] = true;
			}
			if (show_cnt % 10 == 4)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start + 1] = true;
				digital[start + 2] = true;
				digital[start + 5] = true;
				digital[start + 6] = true;
			}
			if (show_cnt % 10 == 5)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start] = true;
				digital[start + 2] = true;
				digital[start + 3] = true;
				digital[start + 5] = true;
				digital[start + 6] = true;
			}
			if (show_cnt % 10 == 6)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start] = true;
				digital[start + 2] = true;
				digital[start + 3] = true;
				digital[start + 4] = true;
				digital[start + 5] = true;
				digital[start + 6] = true;
			}
			if (show_cnt % 10 == 7)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = false;
				digital[start] = true;
				digital[start + 1] = true;
				digital[start + 2] = true;
			}
			if (show_cnt % 10 == 8)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = true;
				digital[start + 7] = false;
			}
			if (show_cnt % 10 == 9)
			{
				for (int i = 0; i < 8; i++)
					digital[start + i] = true;
				digital[start + 4] = false;
				digital[start + 7] = false;
			}
		}
		Sleep(1);
	}
}
void system_key()
{
	while (1)
	{
		if (is_edit == true)
		{
			all = max(all, pos);
			if (keydown == true)
			{
				if (key[13] == true)
				{
					if (key[11] == true) pos = min(pos + 1, 199);
					if (key[12] == true) pos = max(pos - 1, 0);
				}
				else
				{
					if (key[10] == true)
					{
						code[pos] = now;
						is_save = true;
					}
					if (key[11] == true) now = min(now + 1, 99);
					if (key[12] == true) now = max(now - 1, 0);
					if (key[14] == true) waitfor();
					if (key[15] == true)
					{
						code[pos] = now;
						pos = min(pos + 1, 199);
						now = code[pos];
						is_save = true;
					}
				}
				clock_t c = clock();
				while (1)
				{
					if (keydown == false) break;
					// if (is_edit == false) break;
					if (clock() - c >= 1000)
					{
						if (key[13] == true)
						{
							if (key[11] == true) pos = min(pos + 1, 199);
							if (key[12] == true) pos = max(pos - 1, 0);
						}
						else
						{
							if (key[10] == true)
							{
								code[pos] = now;
								is_save = true;
							}
							if (key[11] == true) now = min(now + 1, 99);
							if (key[12] == true) now = max(now - 1, 0);
							if (key[14] == true) waitfor();
							if (key[15] == true)
							{
								code[pos] = now;
								pos = min(pos + 1, 199);
								now = code[pos];
								is_save = true;
							}
						}
						Sleep(250);
					}
					Sleep(1);
				}
				Sleep(button_wait);
			}
			else
			{
				Sleep(1);
			}
		}
	}
}

// ������
void code_00()
{
	pos++;
	if (digit == false)
	{
		if (code[pos] > 07 || code[pos] < 00) error((lan == 1) ? ("��ָ����LED�Ʋ���֧��") : ("The light you specified is not supported!"));
		light[code[pos]] = true;
	}
	else
	{
		if (code[pos] > 07 || code[pos] < 00) error((lan == 1) ? ("��ָ��������ܲ���֧��") : ("The digital tube you specified is not supported!"));
		digital[code[pos]] = true;
	}
}
void code_01()
{
	pos++;
	if (digit == false)
	{
		if (code[pos] > 07 || code[pos] < 00) error((lan == 1) ? ("��ָ����LED�Ʋ���֧��") : ("The light you specified is not supported!"));
		light[code[pos]] = false;
	}
	else
	{
		if (code[pos] > 07 || code[pos] < 00) error((lan == 1) ? ("��ָ��������ܲ���֧��") : ("The digital tube you specified is not supported!"));
		digital[code[pos]] = false;
	}
}
void code_02()
{
	int value, t;
	pos++;
	t = code[pos];
	pos++;
	if (code[pos] > 03 || code[pos] < 00) error((lan == 1) ? ("û�и�ʱ�䵥λ") : ("There is no such time unit!"));
	if (code[pos] == 00) value = 100;
	else if (code[pos] == 01) value = 1000;
	else if (code[pos] == 02) value = 60000;
	else if (code[pos] == 03) value = 3600000;
	for (int i = t; i >= 0; i--)
	{
		if (show_c == false)
		{
			show_cnt = i;
			show = true;
		}
		begint += value;
		Sleep((begint > clock()) ? (begint - clock()) : (1));
	}
	show = false;
}
void code_10()
{
	if (code[++pos] > all) error((lan == 1) ? ("�õ�ַû�в�����") : ("The address has no opcode!"));
	else pos = code[pos] - 1;
}
void code_05()
{
	pos++;
	if (code[pos] == 02 || code[pos] == 01)
	{
		digit = true;
		show = true;
		show_c = true;
	}
	else if (code[pos] == 00)
	{
		digit = false;
		show = false;
		show_c = false;
	}
	else error((lan == 1) ? ("û�и�����ܲ���") : ("There is no such digital tube operation"));
}
void code_04()
{
	pos++;
	if (code[pos] > 99 || code[pos] < 0) error((lan == 1) ? ("�������ֹ�����С") : ("The definition number is too large or too small"));
	else cnt = code[pos];
	if (show_c == true) show_cnt = cnt;
}
void code_06()
{
	pos++;
	cnt += code[pos];
	if (show_c == true) show_cnt = cnt;
}
void code_07()
{
	pos++;
	cnt -= code[pos];
	if (show_c == true) show_cnt = cnt;
}
void code_12()
{
	main_pos = pos;
	pos++;
	if (code[pos + 1] > all) error((lan == 1) ? ("�õ�ַû�в�����") : ("The address has no opcode!"));
	else pos = code[pos] - 1;
}
void code_13()
{
	pos = main_pos - 1;
}
void code_17()
{
	Sleep(10 - (clock() - begint));
}
void code_11()
{
	//if (cnt == code[++pos]) pos = code[++pos] - 1;
	pos++;
	if (code[pos] > 99 || code[pos] < 00)
	{
		error((lan == 1) ? ("��������������") : ("Too many or too few tests!"));
	}
	
	if (cnt >= code[pos])
	{
		pos++;
		if (code[pos] > all) error((lan == 1) ? ("�õ�ַû�в�����") : ("The address has no opcode!"));
		else pos = code[pos] - 1;
	}
	else pos++;
}
void code_08()
{
	// if (key[code[++pos]] != true) pos = code[++pos] - 1;
	// else pos++;
	pos++;
	if (code[pos] > 15 || code[pos] < 10)
	{
		error((lan == 1) ? ("û�иð���") : ("There is no such button!"));
	}
	else
	{
		if (key[code[pos]] != true) pos = code[++pos] - 1;
		else pos++;
	}
}
void code_09()
{
	// if (key[code[++pos]] == true) pos = code[++pos] - 1;
	// else pos++;
	pos++;
	if (code[pos] > 15 || code[pos] < 10)
	{
		error((lan == 1) ? ("û�иð���") : ("There is no such button!"));
	}
	else
	{
		if (key[code[pos]] == true) pos = code[++pos] - 1;
		else pos++;
	}
}
void code_15()
{
	is_run = false;
	is_edit = true;
	pos = 0;
	memset(light, false, sizeof(light));
}
void code_14()
{
	pos++;
	if (code[pos] == 02)
	{
		pos++;
		if (code[pos] == 00)
		{
			show = true;
			show_cnt = 14;
			memset(light, true, sizeof(light));
			Sleep(100);
			memset(light, false, sizeof(light));
			Sleep(2000);
			memset(light, true, sizeof(light));
			Sleep(100);
			memset(light, false, sizeof(light));
			memset(code, 0, sizeof(code));
			is_save = true;
			now = 0;
			show = false;
			code_15();
		}
	}
}
void code_03()
{
	playsound();
}

void run()
{
	standby();
	if (KEY_DOWN('D') || KEY_DOWN('R') || KEY_DOWN('F') || KEY_DOWN('U') || KEY_DOWN('J') || KEY_DOWN('K') || KEY_DOWN('N'))
	{
		while (1)
		{
			if (!(KEY_DOWN('D') || KEY_DOWN('R') || KEY_DOWN('F') || KEY_DOWN('U') || KEY_DOWN('J') || KEY_DOWN('K') || KEY_DOWN('N')))
			{
				break;
			}
		}
	}
	is_edit = true;
	while (1)
	{
		if (is_run == true)
		{
			begint = clock();
			if (pos > all)
			{
				is_run = false;
				is_edit = true;
				pos = 0;
			}
			else if (code[pos] == 00) code_00();
			else if (code[pos] == 01) code_01();
			else if (code[pos] == 02) code_02();
			else if (code[pos] == 15) code_15();
			else if (code[pos] == 10) code_10();
			else if (code[pos] == 05) code_05();
			else if (code[pos] == 04) code_04();
			else if (code[pos] == 06) code_06();
			else if (code[pos] == 07) code_07();
			else if (code[pos] == 12) code_12();
			else if (code[pos] == 13) code_13();
			else if (code[pos] == 17) code_17();
			else if (code[pos] == 11) code_11();
			else if (code[pos] == 8) code_08();
			else if (code[pos] == 9) code_09();
			else if (code[pos] == 03) code_03();
			else if (code[pos] == 15) code_15();
			else if (code[pos] == 14) code_14();
			else if (code[pos] == 666) MessageBox(0, "OK", App, MB_OK);;
			pos++;
		}
	}
}

// ������
int main()
{
	initialization();
	thread task01(display);
	thread task02(input);
	thread task03(run);
	thread task04(show_num);
	thread task05(system_key);
	thread task06(save);
	task01.join();
	task02.join();
	task03.join();
	task04.join();
	task05.join();
	task06.join();
	return 0;
}