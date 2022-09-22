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
#include <string.h>
#include "ExternVariables.h"

char strofa[7]={'\0'};
int currentcolor = 1;
double eachwidth;
int showstep;
int sortstep;
int endstep;
int stepmode;
 

//排序的函数 
void DoMergeSort(struct array a[]);
void merge(struct array arr[], int low, int mid, int high);
void merge_sort(struct array arr[], unsigned int first, unsigned int last);
//实现可视化的函数
char* ColorList(int color);//0<=color<=762
double ColorChange(int n);
void DrawAllTheColumns(struct array a[]);
void DrawOneColumn(int num,int positionY,double amount,char * colorname);
void StressColumn(int num,double amount,char* colorname);//着重显示
void DownColumn(int begin,int order,double amount);
void UpColumn(int order,double amount); 
//单步执行
void DoNextMergeStep(); 
int IsToShow();
//到头/到尾
void DoFromTheEnd(int where); 

void DoFromTheEnd(int where)
{
	int i;
	if(where == 1){
		DrawAllTheColumns(arrayset);
		for(i=0;i<len;i++){
			a[i].data = arrayset[i].data;
		}
		showstep = 0;
		pause_flag = 1;
		pausemode = 1;
	}
	else if(where == 2){
		for(i=0;i<len;i++){
			a[i].data = arrayset[i].data;
		}
		pause_flag = 1;
		pausemode = 1;
		DoMergeSort(a);
		showstep = sortstep - 1;
		DrawAllTheColumns(a);
	}
	else;
}

int IsToShow()
{
	if(sortstep >= showstep+1){
		if(stepmode == 1){
			if(sortstep == endstep+1){
				return 1;
			}
			else{
				return 0;
			}
		}
		if(pause_flag == 1 || pausemode == 1){
			return 0;
		}
		else;
		return 1;
	}
	else{
		return 0;
	}
}


void DoNextMergeStep()
{
	int i=0,j;
	
	pause_flag = -1; 
	pausemode = 0;
	stepmode = 1;
	endstep = showstep;
	sortstep = 0;
	for(i=0;i<len;i++){
		a[i].data = arrayset[i].data;
	}
	DoMergeSort(a);
	stepmode = 0;
	pause_flag = 1;
	pausemode = 1;   
	
}

void UpColumn(int order,double amount)
{
	double wx,wy;
	double leftlocaX,leftlocaY,eachwidth;
	double showpercent;
	int max=0;
	int i;
	char strofa[5]={'\0'};
	
	wx = GetWindowWidth();
	wy = GetWindowHeight();
	
	SetPenSize(2);
	
	eachwidth = (wx-4-(len-1)*0.05)/len;
	if(eachwidth>=1)eachwidth = 0.5;
	leftlocaX = (wx-2)/2-(eachwidth+0.05)*len/2+2;
	leftlocaY = wy - 4.2;
	
	for(i=0;i<len;i++){
		if(a[max].data <= a[i].data)max = i;
	}
	showpercent = 3/a[max].data;

	SetPenColor("white");
 	drawBox(leftlocaX+(eachwidth+0.05)*order-0.025,leftlocaY,eachwidth+0.05,3.0,1,strofa,'D',"white");
	if (isInt)
		sprintf(strofa,"%.0lf",amount);
	if (isFloat)
		sprintf(strofa,"%.2lf",amount);
	if (isDouble)
		sprintf(strofa,"%.2lf",amount);
	SetPenColor(ColorList((762/(len*2))*currentcolor));
	
	drawBox(leftlocaX+(eachwidth+0.05)*order,leftlocaY,eachwidth,(double)amount*showpercent,1,strofa,'D',"black");
	SetPenColor("white");
	drawBox(leftlocaX+(eachwidth+0.05)*order-0.025,leftlocaY-3.0,eachwidth+0.05,(double)amount*showpercent,1,strofa,'D',"white");
	for(i=0;strofa[i];i++){
		strofa[i]='\0';
	}
}

void DownColumn(int begin,int order,double amount)
{
	
	double wx,wy;
	double leftlocaX,leftlocaY,eachwidth;
	double showpercent;
	int max=0;
	int i,color = 2;
	char strofa[5]={'\0'};
	
	wx = GetWindowWidth();
	wy = GetWindowHeight();
	
	SetPenSize(2);
	
	eachwidth = (wx-4-(len-1)*0.05)/len;
	if(eachwidth>=1)eachwidth = 0.5;
	leftlocaX = (wx-2)/2-(eachwidth+0.05)*len/2+2;
	leftlocaY = wy - 4.2;
	
	for(i=0;i<len;i++){
		if(a[max].data <= a[i].data)max = i;
	}
	showpercent = 3/a[max].data;

	if (isInt)
		sprintf(strofa,"%.0lf",amount);
	if (isFloat)
		sprintf(strofa,"%.2lf",amount);
	if (isDouble)
		sprintf(strofa,"%.2lf",amount);
	SetPenColor("white");
 	drawBox(leftlocaX+(eachwidth+0.05)*order-0.025,leftlocaY-0.1,eachwidth+0.05,3.2,1,strofa,'D',"white");
	SetPenColor(ColorList((762/len)*color));
	
	drawBox(leftlocaX+(eachwidth+0.05)*begin,leftlocaY-3.0,eachwidth,(double)amount*showpercent,1,strofa,'D',"black");
	SetPenColor("white");
	drawBox(leftlocaX+(eachwidth+0.05)*order-0.025,leftlocaY,eachwidth+0.05,(double)amount*showpercent,1,strofa,'D',"white");
	for(i=0;strofa[i];i++){
		strofa[i]='\0';
	}
}

void DrawOneColumn(int num,int positionY,double amount,char * colorname)
{
	double wx,wy;
	double leftlocaX,leftlocaY,eachwidth;
	double showpercent;
	int max=0;
	int i;
	char strofa[10]={'\0'};
	
	wx = GetWindowWidth();
	wy = GetWindowHeight();
	
	SetPenSize(2);
	
	eachwidth = (wx-4-(len-1)*0.05)/len;
	if(eachwidth>=1)eachwidth = 0.5;
	leftlocaX = (wx-2)/2-(eachwidth+0.05)*len/2+2;
	leftlocaY = wy - 4.2;
	
	for(i=0;i<len;i++){
		if(a[max].data <= a[i].data)max = i;
	}
	showpercent = 3/a[max].data;
	if (isInt)
		sprintf(strofa,"%.0lf",amount);
	if (isFloat)
		sprintf(strofa,"%.2lf",amount);
	if (isDouble)
		sprintf(strofa,"%.2lf",amount);
	SetPenColor(colorname);
	if(positionY==1){
		drawBox(leftlocaX+(eachwidth+0.05)*num,leftlocaY,eachwidth,amount*showpercent,1,strofa,'D',"black");
	}
	else{
		drawBox(leftlocaX+(eachwidth+0.05)*num,leftlocaY-3.0,eachwidth,amount*showpercent,1,strofa,'D',"black");
	}
	for(i=0;strofa[i];i++){
		strofa[i]='\0';
	}
	
}

void StressColumn(int num,double amount,char* colorname)
{
	DrawOneColumn(num,1,amount,colorname);
}

void DrawAllTheColumns(struct array a[])
{
	double wx,wy;
	double leftlocaX,leftlocaY;
	double showpercent;
	int max=0;
	int i,j;
	char strofa[5]={'\0'};
	
	wx = GetWindowWidth();
	wy = GetWindowHeight();
	
	for(i=0;i<len;i++){
		if(a[max].data <= a[i].data)max = i;
	}
	
	showpercent = 3/a[max].data;
	
	eachwidth = (wx-4-(len-1)*0.05)/len;
	if(eachwidth>=1)eachwidth = 0.5;
	leftlocaX = (wx-2)/2-(eachwidth+0.05)*len/2+2;
	leftlocaY = wy - 4.2;
	
	CleanDesktop();
	//drawBox(2.0,1.5,wx-2,wy-2.5,0,"0",'C',"black");
	//drawBox(2.0,1.5,wx-2,wy-5.7,0,"0",'C',"black");//down location
	
	SetPenSize(2);
	
	for(i=0;i<=len-1;i++){
		if (isInt)
			sprintf(strofa,"%.0lf",a[i].data);
		if (isFloat)
			sprintf(strofa,"%.2lf",a[i].data);
		if (isDouble)
			sprintf(strofa,"%.2lf",a[i].data);
		SetPenColor(ColorList(762/len*i));
		drawBox(leftlocaX+(eachwidth+0.05)*i,leftlocaY,eachwidth,a[i].data*showpercent,1,strofa,'D',"black");	
		for(j=0;strofa[j];j++){
			strofa[j]='\0';
		}
		
	}
	
	
}

double ColorChange(int n)
{
	return (double)n/255;
}

char* ColorList(int color)//0<=color<=762
{
	static char colorname[3];
	
	colorname[2]=color%10+48;
	colorname[1]=(color-color/100*100)/10+48;
	colorname[0]=color/100;
	
	if(color>=0 && color<=128){
		DefineColor(colorname,1,(double)(127+color)/255,0.5);
	}
	else if(color>128 && color<=255){
		DefineColor(colorname,(double)(254-(color-129))/255,1,0.5);
	}
	else if(color>255 && color<=382){
		DefineColor(colorname,0.5,1,(double)(127+color-255)/255);
	}
	else if(color>382 && color<=509){
		DefineColor(colorname,0.5,(double)(255-color+382)/255,1);
	}
	else if(color>509 && color<=636){
		DefineColor(colorname,(double)(127+(color-509))/255,0.5,1);
	}
	else if(color>636 && color<763){
		DefineColor(colorname,1,0.5,(double)(255-color+636)/255);
	}
	else;
	
	return colorname;
}

void DoMergeSort(struct array a[])
{
	currentcolor = 0;
	sortstep = 0;
    merge_sort(a,0,len-1);  // 排序
	if (pause_flag == -1)
	end_flag = 1;
}

 

void merge(struct array arr[], int low, int mid, int high){
	int i, k;
    double *tmp = (double *)malloc((high-low+1)*sizeof(double));
    //申请空间，使其大小为两个
    int left_low = low;
    int left_high = mid;
    int right_low = mid + 1;
    int right_high = high;
    
    double wx,wy;
	double leftlocaX,leftlocaY,eachwidth;
	double showpercent;
	 
	wx = GetWindowWidth();
	wy = GetWindowHeight();
	 
	eachwidth = (wx-4-(len-1)*0.05)/len;
	if(eachwidth>=1)eachwidth = 0.5;
	leftlocaX = (wx-2)/2-(eachwidth+0.05)*len/2+2;
	leftlocaY = wy - 4.2;

    for(k=0; left_low<=left_high && right_low<=right_high; k++){
		//着重显示两个元素柱子 
		sortstep++;
		if(IsToShow()){
			SetPenColor("white");
	  		drawRectangle(leftlocaX+(eachwidth+0.05)*left_low,leftlocaY-0.1,eachwidth+0.058,3.1,1);
	  		SetPenColor("white");
	  		drawRectangle(leftlocaX+(eachwidth+0.05)*right_low,leftlocaY-0.1,eachwidth+0.058,3.1,1);
			StressColumn(left_low,a[left_low].data,"green");
			StressColumn(right_low,a[right_low].data,"green");
			showstep++;
			Pause(sortspeed);
		}
	  // 比较两个指针所指向的元素
        if (a[left_low].data<=a[right_low].data){
        	sortstep++;
            tmp[k] = a[left_low++].data; 
            if(IsToShow()){
            	DownColumn(low+k,left_low-1,tmp[k]);
            	showstep++;
				Pause(sortspeed);
            }
        }else {
        	sortstep++;
            tmp[k] = a[right_low++].data;
            if(IsToShow()){
           		DownColumn(low+k,right_low-1,tmp[k]);
           		showstep++;
				Pause(sortspeed);
            }
           
            //同上 
        }
        
    }
	
    if (left_low <= left_high){  //若第一个序列有剩余，直接复制出来粘到合并序列尾
    //memcpy(tmp+k, arr+left_low, (left_high-left_low+l)*sizeof(int));
    for (i=left_low;i<=left_high;i++){
    	sortstep++;
    	tmp[k++] = a[i].data;
    	if(IsToShow()){
    		DownColumn(low+k-1,i,a[i].data);
    		showstep++;
			Pause(sortspeed);
    	}
    }
        
        
    }

    if(right_low <= right_high){
    //若第二个序列有剩余，直接复制出来粘到合并序列尾
    //memcpy(tmp+k, arr+right_low, (right_high-right_low+1)*sizeof(int));
        for(i=right_low; i<=right_high; i++){
        	sortstep++;
        	tmp[k++] = a[i].data;
        	if(IsToShow()){
        		DownColumn(low+k-1,i,a[i].data);
        		showstep++;
		   		Pause(sortspeed);
        	}
        }
           
    }

    for(i=0; i<high-low+1; i++){
    	sortstep++;
    	a[low+i].data= tmp[i];
    	if(IsToShow()){
    		UpColumn(low+i,(double)a[low+i].data);
    		showstep++;
			Pause(sortspeed);
    	}
    }
    for(i=0;i < len;i++){
	    if (isInt)
	   		sprintf(a[i].lable,"%.0lf",a[i].data);
	 	if (isFloat)
	   		sprintf(a[i].lable,"%.2lf",a[i].data);
	 	if (isDouble)
	   		sprintf(a[i].lable,"%.2lf",a[i].data);
    }     
    free(tmp);
    return;
}

void merge_sort(struct array arr[], unsigned int first, unsigned int last){
	int mid = 0;
    if(first<last){
        mid = (first+last)/2; /* 注意防止溢出 */
        /*mid = first/2 + last/2;*/
        //mid = (first & last) + ((first ^ last) >> 1);
        merge_sort(a, first, mid);
        merge_sort(a, mid+1,last);
        merge(arr,first,mid,last);
    }
    currentcolor++;
    return;
}
