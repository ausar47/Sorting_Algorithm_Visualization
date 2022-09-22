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

int Is_numberset(); //�ж��Ƿ������ݶ���a 
int Is_numbersave();//�ж��Ƿ����д浵������ 
void CleanNumbers();//����������� 
void WhetherPauseChange();//����Pause��ť״̬ 
void CleanDesktop(); //�������ͼ
void ShowWelcomeTop();//��ʾ��ӭ���� 
void ShowInstruction();//��ʾ����ָ�� 

void ShowInstruction()
{
	MessageBox(NULL,"                                           ��ӭ���� VisualSorting \n"
	"����ָ��:\n"
	"       1.���ȵ�����������ݰ�ť ���򡰶�����ť ����������\n"
	"       2.���ڽ���ռ����ޡ����������㷨ʱ�临�ӶȽϸߣ���������������Ŀ������50��\n" 
	"       3.Ϊ��֤���ۣ�������1��1000000ͬʱ���������뾡������\n" 
	"       4.������ѡ������ʽ��ʼ����\n"
	"       5.����·���ͣ/��ʼ����ո������ͣ/��ʼ\n"
	"       6.�����л��е���ִ�С������ٶȡ��ص���ͷ���������β�İ�ť����̽����\n"
	
	"                                                  ף��ʹ�����","",MB_OK);
}

void ShowWelcomeTop()
{
	double wx,wy,fontsize;
	char text[50];
	char precolor[10];
	int i;
	int style;
	
	wx = GetWindowWidth();
	wy = GetWindowHeight();
	
	CleanDesktop();
	
	style = GetStyle();
	strcpy(precolor,GetPenColor());
	fontsize = GetPointSize();
	SetStyle(1);
	SetPointSize(45);
	
	SetPenColor("black");
	strcpy(text,"��ӭ����Visual Sorting");
	MovePen(wx/2-1.28,wy/2);
	DrawTextString(text);
	
	SetPenColor((char*)ColorList(450));
	strcpy(text,"��ӭ����Visual Sorting");
	MovePen(wx/2-1.3,wy/2+0.02);
	DrawTextString(text);
	
	SetPointSize(fontsize);
	SetPenColor(precolor);
	SetStyle(style);
}

void CleanDesktop()
{
	double wx,wy;
	
	wx = GetWindowWidth();
	wy = GetWindowHeight();
	
	char precolor[10];
	strcpy(precolor,GetPenColor());
	SetPenColor("white");	
	drawRectangle(2.0, 1.5, wx-2.0, wy-2.5, 1);
	SetPenColor(precolor);
}

void WhetherPauseChange()
{
	double wx,wy;
	wx = GetWindowWidth();
	wy = GetWindowHeight();
	
	if (pause_flag == -1){
		SetPenColor("lightblue");
		drawRectangle((wx - 2) / 2  + 2 -0.4, 0.2, 0.6, 0.6, 1);
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
		SetPenColor("lightblue");
		drawRectangle((wx - 2) / 2  + 2 -0.4, 0.2, 0.6, 0.6, 1);
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
	else;
}

void CleanNumbers()
{
	int i,j;
	if(Is_numberset()){
		for(i=0;i<len;i++){
			a[i].data = 0.0;
			a[i].heights = 0.0;
			for(j=0;a[i].lable[j]!='\0';j++){
				a[i].lable[j]='\0';
			}
		}
	}
	else;
	return;
}

int Is_numberset()
{
	int i;
	for(i=0;i<100;i++){
		if(a[i].data > 0){
			return 1;
		}
		else;
	}
	return 0;
}

int Is_numbersave()
{
	int i=0;
	char title[7];
	FILE *fp = fopen("saves.dat", "rb");
	while (title[i] = fgetc(fp))
    {
        if (title[i] == ' '){
        	if(i==0){
        		fclose(fp);
        		return 0;
        	}
        	else{
        		fclose(fp);
        		return 1;
        	}
        }
        i++;
        if(i==6){
    		fclose(fp);
        	return 0;
        }
    }
}


