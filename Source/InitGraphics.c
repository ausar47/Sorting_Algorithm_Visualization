#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include <math.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <math.h>
#include "ExternVariables.h"

//������ֵ
#define LeftColumnWidth              2.0
#define UpColumnHeight               1.0
#define DownColumnHeight             1.0
#define DataColumnHeight             0.5
//��ť��ֵ 
#define LeftButtonHeight             0.6
#define LeftButtonWidth              1.8

int len;
//���򷽷���ģʽ
int BubbleSortMode = -1;
int SelectionSortMode = -1;
int MergeSortMode = -1;
int isBubble = -1;
int isSelection = -1;
int isMerge = -1;
double BubbleX;
double BubbleY;
double SelectionX;
double SelectionY;
double MergeX;
double MergeY;						
//��ť��ģʽ 
int ArchiveMode   =               -1;
int ReadMode      =               -1;
int ReadfromtheFileMode=          -1;
int ConfirmationMode    =         -1;
int ClearMode            =        -1;
int BacktotheBeginning    =       -1;
int BackMode              =       -1;
int StartMode              =      -1;
int ForwardMode            =      -1;
int ForwardtotheEnd       =       -1;
int pausemode ;
double sortspeed;
//��ťѡ�е�ģʽ
int ShowBubbleButton = 0; 
int ShowSelectionButton = 0; 
int ShowMergeButton = 0; 
int Show9Button = 0;
int Show10Button = 0;
int Show11Button = 0;
int Show11aButton = -1;
int Show11bButton = -1;
int Show12Button = 0;
int Show13Button = 0;
int Show14Button = 0;
int Show15Button = 0;
int Show16Button = 0;

//��ͼ���������� 
void DrawBox(double x, double y, double width, double height);
void InitWindowGrapgics();
void RedisplaySortbuttons();
void RedisplayTextStrings(int n);
//��Ϣ�ص����������� 
void KeyboardEventProcess(int key, int event);/*������Ϣ�ص�����*/
void CharEventProcess(char c);/*�ַ���Ϣ�ص�����*/
void MouseEventProcess(int x, int y, int button, int event);/*�����Ϣ�ص�����*/
void TimerEventProcess(int timerID);/*��ʱ����Ϣ�ص�����*/
//��������������
void DrawAllTheColumns();
void DoMergeSort(struct array a[]); 
void ReadArray();//�����¶�ȡ����ʱ���򿪿��ƴ��ڶ������� 
void DoNextMergeStep();
void DoFromTheEnd(int where);

//�ж��������ť
//1/2:           �浵����                                              ArchiveMode/ReadMode
//3/4/5��        ð��/ѡ��/�鲢                                        BubbleSortMode/SelectionMode/MergeSortMode
//6��            ���ļ���������                                        ReadfromtheFileMode 
//7/8��          ȷ��/���                                             ConfirmationMode/ClearMode
//9/11/13��		 ���˵���ͷ/��ʼ����ͣ��/ǰ������� 				   BacktotheBeginning/StartMode/ForwardtotheEnd
//14/15          ���ٶ�/���ٶ� 			
//16             ����			
				   
int is_inbox(double x,double y,int Bu); 
//ִ�п��ӻ�
void InitWindowGraphics()
{
	double x, y;
	x = GetWindowWidth();
	y = GetWindowHeight();
	double fontsize;
	
	
	DefineColor("littleblue", 0.88, 0.93, 0.98);//ǳ�� 
	DefineColor("lightblue", 0.65, 0.83, 0.9);//���� 
	DefineColor("heavyblue", 0.38, 0.69, 0.82);//���� 
	DefineColor("darkblue", 47.0/255, 132.0/255, 168.0/255);
	
	SetPenColor("littleblue");
    drawRectangle(LeftColumnWidth, DownColumnHeight, x-LeftColumnWidth, DataColumnHeight, 1);
    
	SetPenColor("lightblue");
	//��ߵ�һ�� 
    drawRectangle(0.0, 0.0, LeftColumnWidth, y, 1);
    //�������һ�� 
    drawRectangle(LeftColumnWidth, 0.0, x-LeftColumnWidth, DownColumnHeight, 1);
    //���ݿ������������ť 
	drawRectangle(x-1.4, 1.1, 1.3, 0.3, 1);
	drawRectangle(2.2, 1.1, 1.5, 0.3, 1); 	
	
	SetPenColor("white");
	//���ݿ� 
	drawRectangle(3.9, 1.1, 9.5, 0.3, 1);   
	//�������м�ͼ���ȦȦ 
	MovePen((x - 2) / 2  + 2 + 0.2, 0.5);
	SetPenSize(4);
	DrawArc(0.3, 0, 360);
	//����ߵİ�ɫ��ť���浵�Ͷ����� 
	drawRectangle(0.1, y - UpColumnHeight - 0.2 - 0.3, 0.85, 0.3, 1);
	drawRectangle(1.05, y - UpColumnHeight - 0.2 - 0.3, 0.85, 0.3, 1);
    ///����ͼ��滭 
	    //���м����� �������ڣ�x/2+1.05,0.5,r=0.3) 
	SetPenSize(3);
	MovePen((x - 2) / 2 + 2 + 0.2 - 0.4, 0.33);
	DrawLine(0, 0.34);
	DrawLine(0.289, -0.17);
	DrawLine(-0.289, -0.17);
	    //������ߵļ�
	 //DrawBox(x/2-1.13,0.25,0.5,0.5); �����˵���ͷ��������Χ 
	drawRectangle(x / 2 + 2.05 - 3.1, 0.33, 0.02, 0.34);
	MovePen(x / 2 - 0.7, 0.33);
	DrawLine(0, 0.34);
	DrawLine(-0.289, -0.17);
	DrawLine(0.289, -0.17);
	    // �����ұߵļ�
	   // DrawBox(x/2+2.35,0.25,0.5,0.5); ��ǰ������󡱰�����Χ
	drawRectangle(x / 2 + 2.75, 0.33, 0.02, 0.34);
	MovePen(x / 2 + 2.43, 0.33);
	DrawLine(0, 0.34);
	DrawLine(0.289, -0.17);
	DrawLine(-0.289, -0.17);
	//���ٶ�ѡ���
	    //�Ӻ� DrawBox(x-0.4,0.4,0.2,0.2); �����ٶȡ�������Χ 
	MovePen(x - 0.2, 0.5);
	SetPenSize(3);
	DrawArc(0.1, 0, 360);
	MovePen(x - 0.3, 0.45);
	DrawLine(0.0,0.1); 
	MovePen(x - 0.35, 0.51);
	DrawLine(0.09,0.0); 
		//���� DrawBox(x-1.5,0.4,0.2,0.2);�����ٶȡ�������Χ 
	MovePen(x - 1.3, 0.5);
	DrawArc(0.1, 0, 360);
	MovePen(x - 1.45, 0.51);
	DrawLine(0.09,0.0); 
		//�������ٶ� �� 
	fontsize = GetPointSize();
	SetPointSize(0.3);
	MovePen(x - 1.18, 0.45);
	SetPenColor("black");
	DrawTextString("�����ٶ�");
	SetPointSize(fontsize);
	sortspeed = 0.5;
	 
	fontsize = GetPointSize();
	SetPointSize(40);
	SetPenColor("black");
	MovePen(0.35, y-0.5);
	DrawTextString("Visual");
	SetPenColor("white");
	MovePen(0.348, y-0.45);
	DrawTextString("Visual");
	SetPenColor("black");
	MovePen(0.25, y-0.9);
	DrawTextString("Sorting");
	SetPenColor("white");
	MovePen(0.248, y-0.85);
	DrawTextString("Sorting");
	SetPointSize(fontsize);
	
	ShowWelcomeTop();
	 
    SetPenColor("heavyblue");
    //�Ϸ�����Ŀ 
    drawRectangle(LeftColumnWidth, y - UpColumnHeight, x - LeftColumnWidth, UpColumnHeight, 1);
    //��ߵ�����ģʽ��ť 
	drawRectangle(0.1, y - UpColumnHeight - 0.7 - LeftButtonHeight, LeftColumnWidth - 0.2, LeftButtonHeight, 1);
	drawRectangle(0.1, y-UpColumnHeight - 0.7 - LeftButtonHeight * 2 - 0.1, LeftColumnWidth - 0.2,LeftButtonHeight, 1);
	drawRectangle(0.1, y-UpColumnHeight - 0.7 - LeftButtonHeight * 3 - 0.2, LeftColumnWidth - 0.2,LeftButtonHeight, 1);  
	
	//��help 
	SetPenColor("lightblue");
	drawRectangle(x-1.4, y-0.9, 1.3, 0.3, 1);  
    
    BubbleX = 0.1;
    BubbleY = y - UpColumnHeight - 0.7 - LeftButtonHeight;
	SelectionX = 0.1 + LeftColumnWidth / 2.0;
	SelectionY = y - UpColumnHeight - 0.7 - LeftButtonHeight * 2.0 - 0.1 + LeftButtonHeight / 2.0;
	MergeX = 0.1 + LeftColumnWidth / 2.0;
	MergeY = y - UpColumnHeight - 0.7 - LeftButtonHeight * 3 - 0.2 + LeftButtonHeight / 2.0;
	
	int i;
	for (i=1; i<=16; i++){
		RedisplayTextStrings(i);
	}
	
	ShowInstruction();
	
}

void DrawBox(double x, double y, double width, double height)
{
    MovePen(x, y);
    DrawLine(0, height);
    DrawLine(width, 0);
    DrawLine(0, -height);
    DrawLine(-width, 0);
}

void RedisplaySortbuttons()
{
	int i;
	double wx, wy;
	wy = GetWindowHeight();
	wx = GetWindowWidth();
	
	if (BubbleSortMode>0){
			SetPenColor("darkblue");
			drawRectangle(0.1, GetWindowHeight() - UpColumnHeight - 0.7 - LeftButtonHeight, LeftColumnWidth - 0.2, LeftButtonHeight, 1);

	}
	else {
			SetPenColor("heavyblue");
			drawRectangle(0.1, GetWindowHeight() - UpColumnHeight - 0.7 - LeftButtonHeight, LeftColumnWidth - 0.2, LeftButtonHeight, 1);

	}
	if (SelectionSortMode>0){
			SetPenColor("darkblue");
			drawRectangle(0.1, GetWindowHeight() - UpColumnHeight - 0.7 - LeftButtonHeight * 2 - 0.1, LeftColumnWidth - 0.2, LeftButtonHeight, 1);

	}
	else {
			SetPenColor("heavyblue");
			drawRectangle(0.1, GetWindowHeight() - UpColumnHeight - 0.7 - LeftButtonHeight * 2 - 0.1, LeftColumnWidth - 0.2, LeftButtonHeight, 1);

	}
				
	if (MergeSortMode>0){
			SetPenColor("darkblue");
			drawRectangle(0.1, GetWindowHeight() - UpColumnHeight - 0.7 - LeftButtonHeight * 3 - 0.2, LeftColumnWidth - 0.2, LeftButtonHeight, 1); 
	}
	else {
			SetPenColor("heavyblue");
			drawRectangle(0.1, GetWindowHeight() - UpColumnHeight - 0.7 - LeftButtonHeight * 3 - 0.2, LeftColumnWidth - 0.2, LeftButtonHeight, 1); 
	}
	for (i=3;i<=5;i++){
		RedisplayTextStrings(i);
	}
}


void MouseEventProcess(int x, int y, int button, int event)
{
	double cx,cy;
	int o;
	
		 char tempp[200];
	
	double wx,wy;
	wy = GetWindowHeight();
	wx = GetWindowWidth();
	
	cx = ScaleXInches(x);
	cy = wy - ScaleXInches(y);
	
	switch(event){
		case BUTTON_DOWN:
			if (button == LEFT_BUTTON){
				if (is_inbox(cx, cy, 3)){
					if(!Is_numberset()){
						MessageBox(NULL,"���ȶ������ȡ����","",MB_OK);
					}
					else{
						if (step_flag == 1 || step)
						{
							MessageBox(NULL,"���ȿ�ʼ�������л�����ģʽ","",MB_OK);
							return;
						}
						isBubble = 1;
						isSelection = -1;
						isMerge = -1;
						BubbleSortMode = (-1) * BubbleSortMode;
						SelectionSortMode = -1;
						MergeSortMode = -1;
						RedisplaySortbuttons();
						pause_flag =-1;
						CleanDesktop();
						InitArray();
						BubbleSort(a, len);			//ð��������ӻ� 
						pause_flag =1;
						pausemode = 1;
					} 
					
				}
				else if (is_inbox(cx, cy, 4)){
					if(!Is_numberset()){
						MessageBox(NULL,"���ȶ������ȡ����","",MB_OK);
					}
					else{
						if (step_flag == 1 || step)
						{
							MessageBox(NULL,"���ȿ�ʼ�������л�����ģʽ","",MB_OK);
							return;
						}
						isBubble = -1;
						isSelection = 1;
						isMerge = -1;
						BubbleSortMode = -1;
						SelectionSortMode=(-1) * SelectionSortMode;
						MergeSortMode = -1;
						RedisplaySortbuttons();
						pause_flag =-1;
						CleanDesktop();
						InitArray();
						SelectionSort(a, len); 		//ѡ��������ӻ� 
						pause_flag =1;
						pausemode = 1;
					} 
					
				}
				else if (is_inbox(cx, cy, 5)){
					if(!Is_numberset()){
						MessageBox(NULL,"���ȶ������ȡ����","",MB_OK);
					}
					else{
						if (step_flag == 1 || step)
						{
							MessageBox(NULL,"���ȿ�ʼ�������л�����ģʽ","",MB_OK);
							return;
						}
						isBubble = -1;
						isSelection = -1;
						isMerge = 1;
						BubbleSortMode = -1;
						SelectionSortMode = -1;
						MergeSortMode=(-1) * MergeSortMode;
						RedisplaySortbuttons();
						pause_flag =-1;
						stepmode = 0;
						pausemode = 0;
						CleanDesktop();
						DrawAllTheColumns(a);
						Pause(sortspeed);
						DoMergeSort(a);			//�鲢������ӻ� 
						pause_flag =1;
						pausemode = 1;
					} 
				}
				else;
				
				if (is_inbox(cx, cy, 9)){ //��ת����� 
					if(!Is_numberset()){
						MessageBox(NULL,"���ȶ������ȡ����","",MB_OK);
					}
					else{
						SetPenColor("darkblue");
						drawRectangle(wx/2+2.05-3.1, 0.33, 0.02, 0.34);
						MovePen(wx/2-0.7, 0.33);
						DrawLine(0, 0.34);
						DrawLine(-0.289, -0.17);
						DrawLine(0.289, -0.17);
						Pause(0.3); 
						SetPenColor("white");
						drawRectangle(wx/2+2.05-3.1, 0.33, 0.02, 0.34);
						MovePen(wx/2-0.7, 0.33);
						DrawLine(0, 0.34);
						DrawLine(-0.289, -0.17);
						DrawLine(0.289, -0.17);	
						//��ת����ʼ
						if (end_flag)
						{
							MessageBox(NULL,"���������","",MB_OK);
							return;
						}
						toset = 1; 
						step_flag = 1;
						if(isMerge == 1){
							DoFromTheEnd(1);
						}
					} 
					
				}
				
				else if (is_inbox(cx, cy, 11)){
					if(!Is_numberset()){
						MessageBox(NULL,"���ȶ������ȡ����","",MB_OK);
					}
					else{
						if (pause_flag == -1){
							SetPenColor("lightblue");
							drawRectangle((wx - 2) / 2  + 2 - 0.4, 0.2, 0.6, 0.6, 1);  //��ʼ��ť��̬ 
							SetPenColor("darkblue");
							MovePen((wx - 2) / 2  + 2 + 0.2, 0.5);
							SetPenSize(4);
							DrawArc(0.3, 0, 360);
							MovePen((wx - 2) / 2 + 2 + 0.2 - 0.4, 0.33);
							DrawLine(0, 0.34);
							MovePen((wx - 2) / 2 + 2 + 0.4 - 0.4, 0.33);
							DrawLine(0, 0.34);
							Pause(0.3);
							SetPenColor("white");
							MovePen((wx - 2) / 2  + 2 + 0.2, 0.5);
							SetPenSize(4);
							DrawArc(0.3, 0, 360);
							SetPenSize(3);
							MovePen((wx - 2) / 2 + 2 + 0.2 - 0.4, 0.33);
							DrawLine(0, 0.34);
							MovePen((wx - 2) / 2 + 2 + 0.4 - 0.4, 0.33);
							DrawLine(0, 0.34);
						}
						else if (pause_flag == 1){
							SetPenColor("lightblue");									//��ͣ��ť��̬ 
							drawRectangle((wx - 2) / 2  + 2 -0.4,0.2,0.6,0.6,1);
							SetPenColor("darkblue");
							MovePen((wx - 2) / 2  + 2 + 0.2, 0.5);
							SetPenSize(4);
							DrawArc(0.3, 0, 360);
							SetPenSize(3);
							MovePen((wx - 2) / 2 + 2 + 0.2 - 0.4, 0.33);
							DrawLine(0, 0.34);
							DrawLine(0.289, -0.17);
							DrawLine(-0.289, -0.17);
							Pause(0.3);
							SetPenColor("white");
							MovePen((wx - 2) / 2  + 2 + 0.2, 0.5);
							SetPenSize(4);
							DrawArc(0.3, 0, 360);
							SetPenSize(3);
							MovePen((wx - 2) / 2 + 2 + 0.2 - 0.4, 0.33);
							DrawLine(0, 0.34);
							DrawLine(0.289, -0.17);
							DrawLine(-0.289, -0.17);
						}
						//��ͣ��
						if (end_flag)
						{
							MessageBox(NULL,"���������","",MB_OK);
							return;
						}
						if (step_flag == 1)
						{
							step_flag = 0;
						}
						else if (step_flag == 0)
						{
							step_flag = 1;
						}
						pause_flag = -pause_flag; 
						if (pause_flag == -1)
						{
							step_flag = 0;
						}
						if(pausemode == 0){
							pausemode = 1;
							endstep = sortstep;
						} 
						else{
							pausemode = 0;
						}
						
						if (pause_flag == -1)
						{
							step = 0;	//��ͣ���ٿ�ʼ�����ٵ��� 
							int q;
							for (q = 0; q < len; q++)
							{
								a[q] = arrayset[q];
							}							//��ԭ��ʼֵ 
							if (isBubble > 0)
							BubbleSort(a, len);			//ð��������ӻ� 
							else if (isSelection > 0)
							SelectionSort(a, len); 		//ѡ��������ӻ�
							else if (isMerge > 0)
							{
								endstep = showstep;
								DoMergeSort(a);			//�鲢������ӻ� 
								
							}
							else;
							pause_flag = 1;
							pausemode = 1;
						}
					}
				
					
				}
				else if (is_inbox(cx, cy, 13)){
					if(!Is_numberset()){
						MessageBox(NULL,"���ȶ������ȡ����","",MB_OK);
					}
					else{
						SetPenColor("darkblue");
						drawRectangle(wx/2+2.75, 0.33, 0.02, 0.34);
						MovePen(wx/2+2.43, 0.33);
						DrawLine(0, 0.34);
						DrawLine(0.289, -0.17);
						DrawLine(-0.289, -0.17);	
						Pause(0.3);
						SetPenColor("white");
						drawRectangle(wx/2+2.75, 0.33, 0.02, 0.34);
						MovePen(wx/2+2.43, 0.33);
						DrawLine(0, 0.34);
						DrawLine(0.289, -0.17);
						DrawLine(-0.289, -0.17);
						//��ת�����
						if (end_flag)
						{
							MessageBox(NULL,"���������","",MB_OK);
							return;
						} 
						toend = 1;	
						if(isMerge == 1){
							DoFromTheEnd(2);
						}
					}
				}
				else;
				
				if (is_inbox(cx, cy, 1)){
					SetPenColor("littleblue");
					drawRectangle(0.1, wy-UpColumnHeight-0.2-0.3, 0.85, 0.3, 1);
					RedisplayTextStrings(1);
					Pause(0.3);
					SetPenColor("white");
					drawRectangle(0.1, wy-UpColumnHeight-0.2-0.3, 0.85, 0.3, 1);
					RedisplayTextStrings(1);
					if(!Is_numberset()){
						MessageBox(NULL,"���ȶ������ȡ����","",MB_OK);
					}
					else{
						//�浵���� 
						int i;
						FILE *fp = fopen("saves.dat", "wb");
						fputs(rch, fp);
						for (i = 0; i < len; i++)
						{
							fputc(' ', fp);
							fprintf(fp, a[i].lable);
						}
						fclose(fp);
					}
					
				} 
				else if (is_inbox(cx, cy, 2)){
					SetPenColor("littleblue");
					drawRectangle(1.05, wy-UpColumnHeight-0.2-0.3, 0.85, 0.3, 1);
					RedisplayTextStrings(2);
					Pause(0.3);
					SetPenColor("white");
					drawRectangle(1.05, wy-UpColumnHeight-0.2-0.3, 0.85, 0.3, 1);
					RedisplayTextStrings(2);
					
					if(!Is_numbersave()){
						MessageBox(NULL,"���ȴӽ����·���ť��ȡ����","",MB_OK);
					}
					else{
						//�������� 
						CleanNumbers();
						isInt = 0;
						isFloat = 0;
						isDouble = 0;		
						end_flag = 0;//��ǩ����
						int i = 0, j = 0, temp = 0, count = 0;
	    				double dtemp = 0;
	    				char num[7] = {0};
	    				FILE *fp = fopen("saves.dat", "rb");
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
						InitArray();
						for (i = 0; i < len; i++)
						{
							arrayset[i] = a[i];		//����ʼ���ݴ浵 
						}
						MessageBox(NULL,"�����ɹ�����ѡ������ʽ","",MB_OK);
					}
					
				}
				else if (is_inbox(cx, cy, 6)){
					SetPenColor("heavyblue");
					drawRectangle(2.2, 1.1, 1.5, 0.3, 1); 
					RedisplayTextStrings(6);
					Pause(0.3);
					SetPenColor("lightblue");
					drawRectangle(2.2, 1.1, 1.5, 0.3, 1); 
					RedisplayTextStrings(6);
					//��յ�ǰ����
					CleanNumbers(); 
					//���ļ��������ݺ��� 
					ReadArray(); 
					if(Is_numberset()){
						MessageBox(NULL,"�������ݳɹ����������ѡ������ʽ","",MB_OK);
					}
				}
				else if (is_inbox(cx,cy,7)){
					SetPenColor("heavyblue");
					drawRectangle(wx-1.4, 1.1, 1.3, 0.3, 1);
					RedisplayTextStrings(7);
					Pause(0.3);
					SetPenColor("lightblue");
					drawRectangle(wx-1.4, 1.1, 1.3, 0.3, 1);
					RedisplayTextStrings(7); 
					
					if(!Is_numberset()){
						MessageBox(NULL,"���ȶ������ȡ����","",MB_OK);
					}
					else{
						//����ִ��
						if (step_flag == 1)
						{
							MessageBox(NULL,"���ȿ�ʼ����","",MB_OK);
							return;
						}
						step = 1;
						if (isSelection == 1)
						{
							if (end_flag)
							{
								MessageBox(NULL,"���������","",MB_OK);
								return;
							}
							DoNextSelectionStep();
						}
						else if (isBubble == 1)
						{
							if (end_flag)
							{
								MessageBox(NULL,"���������","",MB_OK);
								return;
							}
							DoNextBubbleStep();
						}
						else if(isMerge == 1)
						{
							DoNextMergeStep();
						} 
						else;
					}
					
				}
				else if (is_inbox(cx,cy,14)){
					if(!Is_numberset()){
						MessageBox(NULL,"���ȶ������ȡ����","",MB_OK);
					}
					else{
						if(sortspeed <= 0.2){
							MessageBox(NULL,"�Ѿ��ܿ��ˣ����������Ե�����е����İ�ť","",MB_OK);
						}
						else{
							sortspeed -= 0.1;
						} 
					}
				}
				else if (is_inbox(cx,cy,15)){
					if(!Is_numberset()){
						MessageBox(NULL,"���ȶ������ȡ����","",MB_OK);
					}
					else{
						sortspeed += 0.1;
					}
				}
				else if (is_inbox(cx,cy,16)){
					SetPenSize(3);
					SetPenColor("heavyblue");
					drawRectangle(wx-1.4, wy-0.9, 1.3, 0.3, 1); 
					RedisplayTextStrings(16);
					Pause(0.5);
					SetPenColor("lightblue");
					drawRectangle(wx-1.4, wy-0.9, 1.3, 0.3, 1); 
					RedisplayTextStrings(16);
					
					ShowInstruction();
				}
				else; 
			}
			break;
		 case MOUSEMOVE:   
		  //ʵʱ�������ٴ��� 
		 /*for(o=0;o<200;o++){
		 	tempp[o]='\0';
		 }
		 SetPenColor("white");
		 drawRectangle(wx-9.0,wy-1.0,7.0,5.0,1);
		 sprintf(tempp,"pausemode=%d  pause_flag=%d  sortstep=%d  stepmode=%d endstep=%d showstep=%d istoshow=%d",pausemode,pause_flag,sortstep,stepmode,endstep,showstep,IsToShow());
		 MovePen(wx-9.0,wy-1.0);
		 SetPenColor("black");
		 DrawTextString(tempp);
		 */
		 	WhetherPauseChange(); 
			SetPenSize(5);
			if (is_inbox(cx, cy, 3)){
				SetPenColor("darkblue");
				ShowBubbleButton = 1;
				if(ShowBubbleButton)
				drawRectangle(0.1, GetWindowHeight()-UpColumnHeight-0.7-LeftButtonHeight, LeftColumnWidth-0.2, LeftButtonHeight, 0);
				
			}
			else {
				if (ShowBubbleButton){
					ShowBubbleButton = 0;
					SetPenColor("heavyblue");
					drawRectangle(0.1, GetWindowHeight()-UpColumnHeight-0.7-LeftButtonHeight, LeftColumnWidth-0.2, LeftButtonHeight, 0);
				}
			}
			if (is_inbox(cx, cy, 4)){
				SetPenColor("darkblue");
				ShowSelectionButton = 1;
				if(ShowSelectionButton)
				drawRectangle(0.1, GetWindowHeight()-UpColumnHeight-0.7-LeftButtonHeight*2-0.1, LeftColumnWidth-0.2, LeftButtonHeight, 0);
				
			}
			else {
				if (ShowSelectionButton){
					ShowSelectionButton = 0;
					SetPenColor("heavyblue");
					drawRectangle(0.1, GetWindowHeight()-UpColumnHeight-0.7-LeftButtonHeight*2-0.1, LeftColumnWidth-0.2, LeftButtonHeight, 0);
				}
			}
			if (is_inbox(cx, cy, 5)){
				SetPenColor("darkblue");
				ShowMergeButton = 1;
				if(ShowMergeButton)
				drawRectangle(0.1, GetWindowHeight()-UpColumnHeight-0.7-LeftButtonHeight*3-0.2, LeftColumnWidth-0.2, LeftButtonHeight, 0);
				
			}
			else {
				if (ShowMergeButton){
					ShowMergeButton = 0;
					SetPenColor("heavyblue");
					drawRectangle(0.1, GetWindowHeight()-UpColumnHeight-0.7-LeftButtonHeight*3-0.2, LeftColumnWidth-0.2, LeftButtonHeight, 0);
				}
			}
			if (is_inbox(cx, cy, 9)){
				SetPenColor("darkblue");
				Show9Button = 1;
				if(Show9Button)
				DrawBox(wx/2-1.13, 0.25, 0.5, 0.5);
			}
			else {
				if (Show9Button){
					Show9Button = 0;
					SetPenColor("lightblue");
					DrawBox(wx/2-1.13, 0.25, 0.5, 0.5);
				}
			}
			if (is_inbox(cx, cy, 11)){
				Show11Button = 1;
			}
			else ;
			
			if (is_inbox(cx, cy, 13)){
				SetPenColor("darkblue");
				Show13Button = 1;
				if(Show13Button)
				DrawBox(wx/2+2.35, 0.25, 0.5, 0.5);
			}
			else {
				if (Show13Button){
					Show13Button = 0;
					SetPenColor("lightblue");
					DrawBox(wx/2+2.35, 0.25, 0.5, 0.5);
				}
			}
			
			if (is_inbox(cx, cy, 14)){
				SetPenColor("darkblue");
				Show14Button = 1;
				if(Show14Button){
					MovePen(wx - 0.2, 0.5);
					SetPenSize(3);
					DrawArc(0.1, 0, 360);
					MovePen(wx - 0.3, 0.45);
					DrawLine(0.0,0.1); 
					MovePen(wx - 0.35, 0.51);
					DrawLine(0.09,0.0); 
				}
					
			}
			else {
				if (Show14Button){
					Show14Button = 0;
					SetPenColor("white");
					MovePen(wx - 0.2, 0.5);
					SetPenSize(3);
					DrawArc(0.1, 0, 360);
					MovePen(wx - 0.3, 0.45);
					DrawLine(0.0,0.1); 
					MovePen(wx - 0.35, 0.51);
					DrawLine(0.09,0.0); 
				}
			}
			
			if (is_inbox(cx, cy, 15)){
				SetPenColor("darkblue");
				Show15Button = 1;
				if(Show14Button){
					SetPenSize(3);
					MovePen(wx - 1.3, 0.5);
					DrawArc(0.1, 0, 360);
					MovePen(wx - 1.45, 0.51);
					DrawLine(0.09,0.0);  
				}
					
			}
			else {
				if (Show15Button){
					Show15Button = 0;
					SetPenSize(3);
					SetPenColor("white");
					MovePen(wx - 1.3, 0.5);
					DrawArc(0.1, 0, 360);
					MovePen(wx - 1.45 , 0.51);
					DrawLine(0.09,0.0);  
				}
			}
			
			if (is_inbox(cx, cy, 16)){
				SetPenColor("heavyblue");
				Show16Button = 1;
				if(Show16Button){
					drawRectangle(wx-1.4, wy-0.9, 1.3, 0.3, 1);  
				}
				RedisplayTextStrings(16);
			}
			else {
				if (Show16Button){
					SetPenColor("lightblue");
					Show16Button = 0;
					drawRectangle(wx-1.4, wy-0.9, 1.3, 0.3, 1);  
					RedisplayTextStrings(16);
				}
			}
	}
}


int is_inbox(double x,double y,int Bu)
{
	
	double wx,wy;
	wy = GetWindowHeight();
	wx = GetWindowWidth();
	
	//DrawBox(x,y,0.5,0.5);
	
	switch(Bu){
		case 1:
			if (x>=0.1 && y >= wy-UpColumnHeight-0.2-0.3 && x<= 0.95 && y<=  wy-UpColumnHeight-0.2)
			return 1; 
			break;
		case 2:
			if (x>=1.05 && y >= wy-UpColumnHeight-0.2-0.3 && x<= 1.9 && y<=wy-UpColumnHeight-0.2)
			return 1; 
			break;
		case 3:
			if (x>=0.1 && x<=1.9 && y>= wy -2.3 && y<=wy -1.7){
			//if((x>=0.1) && (y >= (GetWindowHeight()-UpColumnHeight-0.7-LeftButtonHeight)) && (x<= (LeftColumnWidth-0.1) )&& (y<= (GetWindowHeight()-UpColumnHeight-0.7-LeftButtonHeight+LeftButtonHeight))){
				return 1;
			}
			break;
		case 4:
			if ((fabs(x-SelectionX)<=(LeftColumnWidth/2.0)) && (fabs(y-SelectionY)<=(LeftButtonHeight/2.0))){
				return 1;
			}
			break;
		case 5:
			if ((fabs(x-MergeX)<=(LeftColumnWidth/2.0)) && (fabs(y-MergeY)<=(LeftButtonHeight/2.0))){
				return 1;
			}
			break;
		case 6:
			if (x>=2.2 && y >= 1.1 && x<= 3.7 && y<= 1.4)
			return 1; 
			break;
		case 7:
			if (x>=wx-1.4 && y >= 1.1 && x<= wx-0.1 && y<= 1.4)
			return 1; 
			break;
		case 8:
			if (x>=wx-0.7 && y >= 1.1 && x<= wx-0.2 && y<= 1.4)
			return 1; 
			break;
		case 9:
			//DrawBox(wx/2-1.13,0.25,0.5,0.5);
			//DrawBox(x,y,0.5,0.5);
			if (x>=wx/2-1.13 && y >= 0.25 && x<=wx/2-1.13 +0.5 && y<= 0.75)
			return 1;
			break;
		case 10:
			//DrawBox(wx/2+2.05-2.4,0.25,0.8,0.5,1);; 
			if (x>=wx/2+2.05-2.4 && y >= 0.25 && x<=wx/2+2.05-1.6 && y<= 0.75)
			return 1;
			break;
		case 11:
			//MovePen((x-2)/2+2+0.2,0.5);
			//SetPenSize(4);
			//DrawArc(0.3,0,360);
			if (x>=(wx-2)/2+1.6 && y >= 0.2 && x<=(wx-2)/2+1.6 +0.6 && y<= 0.8)
			return 1;
			break;
		case 12:
			//drawRectangle(wx/2+2.05-0.77,0.25,0.8,0.5,1);
			if (x>=wx/2+2.05-0.77 && y >= 0.25 && x<=wx/2+2.05-0.77+0.8 && y<= 0.75)
			return 1;
			break;
		case 13:
			//DrawBox(x/2+2.35,0.25,0.5,0.5);
		    if (x>=wx/2+2.35 && y >= 0.25 && x<=wx/2+2.35 +0.5 && y<= 0.75)
			return 1;
			break;
		case 14:
			//DrawBox(x-0.4,0.4,0.2,0.2); 
			if (x>=wx-0.4 && y >= 0.4 && x<=wx-0.2 && y<= 0.6)
			return 1;
			break;
		case 15:
			//DrawBox(x-1.5,0.4,0.2,0.2);
			if (x>=wx-1.5 && y >= 0.4 && x<=wx-1.5+0.2 && y<=0.6)
			return 1;
			break;
		case 16:
			//drawRectangle(x-1.4, y-0.9, 1.3, 0.3, 1);  
			if (x>=wx-1.4 && y >= wy-0.9 && x<=wx-0.1 && y<=wy-0.6)
			return 1;
			break;
	}
	
	return 0 ;
	
}

void RedisplayTextStrings(int n)
{
	SetPenColor("black"); 
    SetPenSize(1);
    
    double wx, wy;
	wy = GetWindowHeight();
	wx = GetWindowWidth();
    
	switch(n){
		case 1:
			MovePen(0.35, wy-UpColumnHeight-0.2-0.2);
			DrawTextString("�浵");
			break;
		case 2:
			MovePen(1.3, wy-UpColumnHeight-0.2-0.2);
			DrawTextString("����");
			break;
		case 3:
			MovePen(0.65, wy-UpColumnHeight-0.7-LeftButtonHeight+0.25);
			DrawTextString("ð������");
			break;
		case 4:
			MovePen(0.65, wy-UpColumnHeight-0.7-LeftButtonHeight-0.45);
			DrawTextString("ѡ������");
			break;
		case 5:
			MovePen(0.65, wy-UpColumnHeight-0.7-LeftButtonHeight-1.15);
			DrawTextString("�鲢����");
			break;
		case 6:
			MovePen(2.55, 1.2);
			DrawTextString("��ȡ����");
			break;
		case 7:
			MovePen(wx-1.1, 1.2);
			DrawTextString("����ִ��");
			break;
		case 16:
			MovePen(wx-0.93,wy - 0.82);
			DrawTextString("HELP");
			break;
		
	}
}
void KeyboardEventProcess(int key, int event)
{
	double cx,cy;
	double wx,wy;
	wy = GetWindowHeight();
	wx = GetWindowWidth();
	switch (event)
	{
		case KEY_DOWN:
			if (key == VK_SPACE)
			{
				if(!Is_numberset()){
					MessageBox(NULL,"���ȶ������ȡ����","",MB_OK);
				}
				else{
					if (pause_flag == -1){
						SetPenColor("lightblue");
						drawRectangle((wx - 2) / 2  + 2 - 0.4, 0.2, 0.6, 0.6, 1);  //��ʼ��ť��̬ 
						SetPenColor("darkblue");
						MovePen((wx - 2) / 2  + 2 + 0.2, 0.5);
						SetPenSize(4);
						DrawArc(0.3, 0, 360);
						MovePen((wx - 2) / 2 + 2 + 0.2 - 0.4, 0.33);
						DrawLine(0, 0.34);
						MovePen((wx - 2) / 2 + 2 + 0.4 - 0.4, 0.33);
						DrawLine(0, 0.34);
						Pause(0.3);
						SetPenColor("white");
						MovePen((wx - 2) / 2  + 2 + 0.2, 0.5);
						SetPenSize(4);
						DrawArc(0.3, 0, 360);
						SetPenSize(3);
						MovePen((wx - 2) / 2 + 2 + 0.2 - 0.4, 0.33);
						DrawLine(0, 0.34);
						MovePen((wx - 2) / 2 + 2 + 0.4 - 0.4, 0.33);
						DrawLine(0, 0.34);
					}
					else if (pause_flag == 1){
						SetPenColor("lightblue");									//��ͣ��ť��̬ 
						drawRectangle((wx - 2) / 2  + 2 -0.4,0.2,0.6,0.6,1);
						SetPenColor("darkblue");
						MovePen((wx - 2) / 2  + 2 + 0.2, 0.5);
						SetPenSize(4);
						DrawArc(0.3, 0, 360);
						SetPenSize(3);
						MovePen((wx - 2) / 2 + 2 + 0.2 - 0.4, 0.33);
						DrawLine(0, 0.34);
						DrawLine(0.289, -0.17);
						DrawLine(-0.289, -0.17);
						Pause(0.3);
						SetPenColor("white");
						MovePen((wx - 2) / 2  + 2 + 0.2, 0.5);
						SetPenSize(4);
						DrawArc(0.3, 0, 360);
						SetPenSize(3);
						MovePen((wx - 2) / 2 + 2 + 0.2 - 0.4, 0.33);
						DrawLine(0, 0.34);
						DrawLine(0.289, -0.17);
						DrawLine(-0.289, -0.17);
					}
					//��ͣ��
					if (end_flag)
					{
						MessageBox(NULL,"���������","",MB_OK);
						return;
					}
					if (step_flag == 1)
					{
						step_flag = 0;
					}
					else if (step_flag == 0)
					{
						step_flag = 1;
					}
					pause_flag = -pause_flag; 
					if (pause_flag == -1)
					{
						step_flag = 0;
					}
					if(pausemode == 0){
						pausemode = 1;
						endstep = sortstep;
					} 
					else{
						pausemode = 0;
					}
					
					if (pause_flag == -1)
					{
						step = 0;	//��ͣ���ٿ�ʼ�����ٵ��� 
						int q;
						for (q = 0; q < len; q++)
						{
							a[q] = arrayset[q];
						}							//��ԭ��ʼֵ 
						if (isBubble > 0)
						BubbleSort(a, len);			//ð��������ӻ� 
						else if (isSelection > 0)
						SelectionSort(a, len); 		//ѡ��������ӻ�
						else if (isMerge > 0)
						{
							endstep = showstep;
							DoMergeSort(a);			//�鲢������ӻ� 
							
						}
						else;
						pause_flag = 1;
						pausemode = 1;
					}
				}
			}
			break;
		case KEY_UP:
			break; 
	}
} 
