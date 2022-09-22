#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "exception.h"
#include "imgui.h"
#include "random.h"
#include "gcalloc.h"
#include "ExternVariables.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 100000			//������󳤶� 
#define MAXLEN 1024			//�ļ�����󳤶� 

double pos[MAXN] = {0};		//��¼���ݶ�Ӧ�������x���� 
int len;					//���鳤�� 
double width, height;		//���ڿ�ȡ��߶� 
double sx = 3, sy, block_height_SI, block_width_SI;	
							//��ʼx,y���ꡢ���ĵ�λ�߶�,��λ��� 
char rch[7] = {'\0'};		//��������int/float/double 
struct array a[MAXN] = {0, "\0", 0}; 
							//���岢��ʼ���ṹa 
struct array arrayset[100000];	//���Լ�¼����ṹ 
int isInt = 0;
int isFloat = 0;
int isDouble = 0;		//�������ͱ�� 
int pause_flag = 1;		//�Ƿ���ͣ��� 
int step_flag = 0;		//����������� 
int toend = 0;			//��ת����� 
int toset = 0;			//��ת����ʼ 
int isBubble;
int isSelection;
int isMerge;			//����ģʽ��� 
int step = 0;
int pause_step = 0;
int cnt = 0;
int tmpi = 0;
int tmpj = 0;
int tmpx = 0;
int endcnt = 0;
int stepcnt = 0;
int isshow = 1;
int end_flag = 0;
//functions
void MouseEventProcess(int x,int y,int button,int event);
void KeyboardEventProcess(int key,int event);
void TimerEventProcess(int timerID);
void CharEventProcess(char c);

void Display();			//����+������ʾ 
void Visualize();		//ѡ��/ð��������ӻ� 
void GetSI(void);		//����ó���λ�߶Ⱥ͵�λ��� 
void InitArray();		//����ReadArray��������֮��ĳ�ʼ�� 
void TransNumChar(int n, int number);	//������תΪ�ַ��� 
void SelectionSort(struct array a[], int len); 	//ѡ������ 
void BubbleSort(struct array a[], int len);		//ð������ 
void MergeSort(struct array a[], int len); 		//�鲢���� 
void SwapStruct(struct array *x, struct array *y);	//�����ṹ 
void DoNextSelectionStep();			//����ѡ����
void DoNextSelectionStep();			//����ð�ݺ��� 

void InitArray()
{
    width = GetWindowWidth();
	height = GetWindowHeight();
	sy = height / 2.0 - 2;						//��ʼx=1��yΪ���ڸ߶ȵ�һ�� - 2
	SetPenColor((char*)ColorList(450));
	SetPenSize(0);
	GetSI();
	pos[0] = sx;			//��pos[0]��Ϊ��ʼx���� ,����ÿ��pos[i]Ϊpos[i-1] + block_width
	int i;
	for(i = 0; i < len; i++)
	{
		if (i > 0)
			pos[i] = pos[i - 1] + block_width_SI;
		a[i].heights = a[i].data * block_height_SI;
		strcpy(a[i].lable, "\0");
		if (isInt)
			sprintf(a[i].lable, "%.0lf", a[i].data);
		if (isFloat)
			sprintf(a[i].lable, "%.2lf", a[i].data);
		if (isDouble)
			sprintf(a[i].lable, "%.2lf", a[i].data);
	}

	Display();
			//ѡ��orð��������ӻ�	
}
void Display()
{
	CleanDesktop();
	int i;
	MovePen(sx, sy);
	for(i = 0; i < len; i++)
	{
		MovePen(pos[i], sy);
		SetPenColor((char*)ColorList(450));
		SetPenSize(0);
		drawBox(pos[i], sy, block_width_SI * 0.8, a[i].heights, 1, a[i].lable, 'C', "Black");
	}
}
void Visualize()
{
	Display();
	int k;
	if (isSelection == 1)
	{
		SetPenColor("Green");
		drawBox(pos[tmpx], sy, block_width_SI * 0.8, a[tmpx].heights, 1, a[tmpx].lable, 'C', "Black");
		for (k = 0; k < tmpi; k++)
		{
			SetPenColor((char*)ColorList(20));
			drawBox(pos[k], sy, block_width_SI * 0.8, a[k].heights, 1, a[k].lable, 'C', "Black");
		} 
	}
	else if (isBubble == 1)
	{	
		SetPenColor("Green");
		drawBox(pos[tmpj], sy, block_width_SI * 0.8, a[tmpj].heights, 1, a[tmpj].lable, 'C', "Black");
		if (tmpj + 1 < len)
		{
			SetPenColor("Green");
			drawBox(pos[tmpj + 1], sy, block_width_SI * 0.8, a[tmpj + 1].heights, 1, a[tmpj + 1].lable, 'C', "Black");
		}
		for (k = len - 1; k > tmpi; k--)
		{
			SetPenColor((char*)ColorList(20));
			drawBox(pos[k], sy, block_width_SI * 0.8, a[k].heights, 1, a[k].lable, 'C', "Black");
		}
	}
	else;
	if (!toend || step)
		Pause(sortspeed);
}
void SelectionSort(struct array a[], int len)
{
	toset = 0;
	toend = 0;	
	cnt = 0;
	end_flag = 0;
	pause_flag = -1;
	//��ձ�� 
	int i, j, p, x, chx = 0;	//chxΪx�仯��ǣ���δ���������򲻻�ͼ��ʾ 
	for (i = 0; i < len; i++)
	{
		x = i;
		tmpi = i;
		tmpx = x;
		for (j = i + 1; j < len; j++)
		{
			chx = 0;
			tmpj = j;
			if (toset)
			{
				for (p = 0; p < len; p++)
				{
					a[p] = arrayset[p];		//�ص���ʼֵ 
				}
				if (isSelection == 1) 
					Display();
				toset = 0;
				cnt = 0;
				pause_flag = 1;						//����ͣ 
			}
			if (a[j].data < a[x].data)
			{
				chx = 1;
				x = j;
				tmpx = x;
			}
			cnt++;
			if (cnt == endcnt)
				isshow = 1;
			if (step)
			{
				pause_flag = 1;
				return;
			}
			if (pause_flag == 1 && isshow)
			{
				endcnt = cnt;
				isshow = 0;
			}
			if (isshow && chx)
			{
				Visualize();
			}
		}
		SwapStruct(&a[i], &a[x]);
		if (isshow)
			Visualize();			
	}
	if (isshow)
	{
		Display();
		pause_flag = 1;
		end_flag = 1;
	}
}
void BubbleSort(struct array a[], int len)
{
	int i, j, p;
	toend = 0;
	toset = 0;	
	cnt = 0;
	end_flag = 0; 
	pause_flag = -1;
	//��ձ�� 
	for (i = len - 1; i >= 0; i--)
	{
		tmpi = i;
		for (j = 0; j < i; j++)
		{
			tmpj = j;
			SetPenColor((char*)ColorList(450));
			if (a[j].data > a[j + 1].data)
			{
				SwapStruct(&a[j], &a[j + 1]);
			} 
			if (toset)
			{
				for (p = 0; p < len; p++)
				{
					a[p] = arrayset[p];		//�ص���ʼֵ 
				}
				if (isBubble == 1)	
					Display();
				toset = 0;
				cnt = 0;
				pause_flag = 1;						//����ͣ 
			}
			if (step)
			{
				isshow = 0;
				pause_flag = 1;
				return;
			}		
			cnt++;
			if (cnt == endcnt)
				isshow = 1;
			if (pause_flag == 1 && isshow)
			{
				endcnt = cnt;
				isshow = 0;
			}
			if (isshow)
				Visualize(); 
		}
	}
	if (isshow)
	{
		Display();
		pause_flag = 1;
		end_flag = 1;
	}
}
void DoNextSelectionStep()
{
	int chx = 0;			//chxΪx�仯��ǣ���δ�����������ٴε��� 
	if (a[tmpj].data < a[tmpx].data)
	{
		chx = 1;
		tmpx = tmpj;
	}
	else;
	if (tmpj < len - 1)
	{
		tmpj++;
	}
	else if (tmpj == len - 1)
	{
		SwapStruct(&a[tmpi], &a[tmpx]);
		tmpi++;
		tmpx = tmpi;
		tmpj = tmpi + 1;
	}
	cnt++;
	endcnt = cnt;
	if (!chx)
		DoNextSelectionStep();
	else if (chx)
		Visualize();
	if (cnt >= len * (len - 1) / 2 + 1)
	{
		Display();
		pause_flag = 1;
		end_flag = 1;
		cnt = len * (len - 1) / 2 + 1;
		endcnt = cnt;
	}
}
void DoNextBubbleStep()
{				
	if (a[tmpj].data > a[tmpj + 1].data)
	{
		SwapStruct(&a[tmpj], &a[tmpj + 1]);
	} 
	if (tmpj < tmpi - 1)
	{
		tmpj++;
	}
	else if (tmpj == tmpi - 1)
	{
		tmpi--;
		tmpj = 0;
	}
	cnt++;
	endcnt = cnt;
	Visualize();
	if (cnt >= len * (len - 1) / 2)
	{
		Display();
		pause_flag = 1;
		end_flag = 1;
		cnt = len * (len - 1) / 2;
		endcnt = cnt;
	}
}
void GetSI(void)		//����ó����ĵ�λ�߶� ,��λ��� 
{
	int i;
	double aMax = a[0].data;
	for(i = 1; i < len; i++)
		if (a[i].data > aMax)
			aMax = a[i].data;
	block_height_SI = 4.0 / aMax ;			//��aMax�߶�Ϊ4.0���������������� 
	block_width_SI = (width - 4.0) / len;//�Դ��ڿ�ȣ�������2����������1���������鳤��Ϊ��λ���
}
void SwapStruct(struct array *x, struct array *y)
//�������ṹ 
{
	struct array temp;
	temp = *x;
	*x = *y;
	*y = temp;
}
void ReadArray()
{
	isInt = 0;
	isFloat = 0;
	isDouble = 0;		
	end_flag = 0;//��ǩ���� 
	int mode = 0;	//1:�ӿ��ƴ��ڶ���
					//2�����ļ����� 
	char *fname = NULL;
	char num[4] = {0};
	FILE *fp;
	int i;
	CleanDesktop();
	OpenConsole();
	system("cls");//�����Ļ����ʾ����Ϣ
	printf("\n\n\n");
	printf("                                          ��������������������������������������������������������������������\n");
    printf("                                          ��            WELCOME!            ��\n"); 
    printf("                                          ��������������������������������������������������������������������\n");
    printf("                                          ��                                ��\n");
	printf("                                          �� ��ӭʹ��Visual Sorting������� ��\n");	
	printf("                                          ��      ��ѡ��������ݵķ�ʽ      ��\n");
	printf("                                          ��                                ��\n");
	printf("                                          ��������������������������������������������������������������������\n");
	printf("                                          ��          1.�ֶ�����            ��\n");
	printf("                                          ��          2.���ļ�����          ��\n");
	printf("                                          ��������������������������������������������������������������������\n");
	printf("                                          ��          3.�˳�                ��\n");	
	printf("                                          ��     ������ǿ�йرմ˴��ڣ�     ��\n");
	printf("                                          ��������������������������������������������������������������������\n\n");
	printf("\n\n\n                                                           ");
	scanf("%d", &mode);
	getchar();			//��������scanf��Ŀո��س�������Ӱ������gets 
	if (mode == 1)
	{
		system("cls");
		printf("\n\n                                                ������ǿ�йرմ˴��ڣ�        \n");
		printf("\n\n\n                                           ��������������:(int float double)\n");
		printf("\n\n\n                                                          ");
		gets(rch);
		if (strcmp(rch, "int") == 0)
		{
			isInt = 1;
		}
		if (strcmp(rch, "float") == 0)
		{
			isFloat = 1;
		}
		if (strcmp(rch, "double") == 0)
		{
			isDouble = 1;
		}
		printf("\n\n\n                                             ���������鳤�ȣ�������������\n");
		printf("\n\n\n                                                           ");
		scanf("%d", &len);
		printf("\n\n\n                                                     �������ݣ�\n");
		printf("\n\n\n                                                ");
		for (i = 0; i < len; i++)
		{
			scanf("%lf", &a[i].data);
		}
		CloseConsole();
		InitArray();
	}
	else if (mode == 2)
	{
		fname = (char *)malloc(1000 * sizeof(char));
		int i = 0, j = 0, temp = 0, count = 0;
    	double dtemp = 0;
    	system("cls");
    	printf("                                                    ������ǿ�йرմ˴��ڣ�        \n");
k:		
		printf("\n    ���� test1.txt / test2.txt / test3.txt / test4.txt �ɹ�ѡ�񣬻����������а��������ļ���ʽ�ڵ�ǰ�ļ����´�����������");
		printf("\n\n\n                                                     �������ļ�����\n");
		printf("\n\n\n                                                     ");
		gets(fname);
		fp = fopen(fname, "r");
	    if (fp == NULL)
	    {
	    	char kkk[16] = "..\\testfiles\\"; 
	    	strcat(kkk, fname);
	    	fp = fopen(kkk, "r");
	    	if (fp == NULL)
	    	{
	    		printf("\n\n\n                                             %s �޷���!\n", fname);
	        	goto k;
	    	}
	    }
	    while (rch[i] = fgetc(fp))
	    {
	        if (rch[i] == ' ')
	            break;
	        i++;
	    }
	    rch[i] = '\0';
		if (strcmp(rch,"int") == 0) 
		{
			isInt = 1;
			i = 0;
			while (!feof(fp))
			{
				num[i] = fgetc(fp);
				if (num[i] == ' ' || feof(fp) || num[i] == '\n')
				{
					i--;
					while (i >= 0)
						temp = temp + (num[i--] - 48) * pow(10, j++);
					printf("%d ",temp);
					a[count++].data = temp; //�����ݱ��浽������
					if (num[j] == '\n')
						break;//i���꣬j���üӵ�ԭ��num�������ֺ�Ŀո���з��� 
					temp = 0;
					i = 0;
					j = 0;
					strcpy(num,"\0\0\0");
				}
				else
					i++;
			}
			
		}
		else if (strcmp(rch,"float") == 0 || strcmp(rch,"double") == 0)
		{
			i = 0;
			if (strcmp(rch, "float") == 0)
			{
				isFloat = 1;
			}
			if (strcmp(rch, "double") == 0)
			{
				isDouble = 1;
			}
			while (!feof(fp))
			{
				num[i] = fgetc(fp);
				if (num[i] == ' ' || feof(fp) || num[i] == '\n')
				{
					i--;
					int t = i;
					while (num[t--] != 46);
					if (t < 0)
					{
						while (i >= 0)
							dtemp = dtemp + (num[i--] - 48) * pow(10, j++);
						goto e;
					}
					t += 2;
					int k = t;
					while (k <= i)
					{
						dtemp = dtemp + (num[k++] - 48) * pow(10, --j);
					}
					j = 0;
					t -= 2;
					while (t >= 0)
					{
						dtemp = dtemp + (num[t--] - 48) * pow(10, j++);
					}
	e:				if (num[++i] == '\n')
						break;
					a[count++].data = dtemp; //�����ݱ��浽������ 
					dtemp = 0;
					i = 0;
					j = 0;
				}
				else
					i++;
			}
		}
	    fclose(fp);
	    len = count;
	    free(fname);
	    
		CloseConsole();
		InitArray();
		for (i = 0; i < len; i++)
		{
			arrayset[i] = a[i];		//����ʼ���ݴ浵 
		}
	}
	else if(mode == 3){
		CloseConsole();
		ShowWelcomeTop();
	}
	else;
}
