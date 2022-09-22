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

int Is_numberset(); //判断是否有数据读入a 
int Is_numbersave();//判断是否已有存档的数据 
void CleanNumbers();//清楚现有数据 
void WhetherPauseChange();//更新Pause按钮状态 
void CleanDesktop(); //清空柱形图
void ShowWelcomeTop();//显示欢迎界面 
void ShowInstruction();//显示操作指南 

void ShowInstruction()
{
	MessageBox(NULL,"                                           欢迎来到 VisualSorting \n"
	"操作指南:\n"
	"       1.请先点击“读入数据按钮 ”或“读档按钮 ”读入数据\n"
	"       2.由于界面空间有限、部分排序算法时间复杂度较高，建议输入数据数目不超过50个\n" 
	"       3.为保证美观，类似于1和1000000同时输入的情况请尽量避免\n" 
	"       4.再在左方选择排序方式开始排序\n"
	"       5.点击下方暂停/开始键或空格可以暂停/开始\n"
	"       6.过程中还有单步执行、调节速度、回到开头、快进到结尾的按钮供您探索。\n"
	
	"                                                  祝您使用愉快","",MB_OK);
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
	strcpy(text,"欢迎来到Visual Sorting");
	MovePen(wx/2-1.28,wy/2);
	DrawTextString(text);
	
	SetPenColor((char*)ColorList(450));
	strcpy(text,"欢迎来到Visual Sorting");
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


