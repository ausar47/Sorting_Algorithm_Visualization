struct array{			    	//结构：待排序数组及一些参数 
	double data;				//数组中存储的数据
	char lable[20];	 	    	//记录数据对应的字符串 
	double heights;			    //记录数据对应柱的高度 
};
extern int isInt;
extern int isFloat;
extern int isDouble;
extern int len;
extern char rch[7];
extern struct array a[100000]; 
extern int pause_flag;	
extern int step_flag;        		//当暂停/进入单步执行时 
extern int toend;		        		//到结束标记
extern int toset;	        			//到开始标记 
extern struct array arrayset[100000];	//用以记录最初结构 
extern int step;						//单步执行标记 
extern int isBubble;
extern int isSelection;
extern int isMerge;						//排序模式标记 
extern int cnt;							//选择/冒泡排序次数 
extern int endcnt;						//选择/冒泡暂停时排序次数
extern int stepcnt;						//选择/冒泡单步执行时排序次数 
extern int isshow;				//选择/冒泡显示标记 
extern int end_flag;			//选择/冒泡结束标记 
extern double sortspeed;  		//速度 
extern int tmpx;
extern int tmpi;
extern int tmpj;				//选择冒泡中的i,j,x 
 
extern int showstep;					//显示到的步数 
extern int sortstep;					//排序到的步数 
extern int endstep;						//最后截至的步数 
extern int stepmode;					//单步执行模式 
extern int pausemode;					//暂停模式 
