struct array{			    	//�ṹ�����������鼰һЩ���� 
	double data;				//�����д洢������
	char lable[20];	 	    	//��¼���ݶ�Ӧ���ַ��� 
	double heights;			    //��¼���ݶ�Ӧ���ĸ߶� 
};
extern int isInt;
extern int isFloat;
extern int isDouble;
extern int len;
extern char rch[7];
extern struct array a[100000]; 
extern int pause_flag;	
extern int step_flag;        		//����ͣ/���뵥��ִ��ʱ 
extern int toend;		        		//���������
extern int toset;	        			//����ʼ��� 
extern struct array arrayset[100000];	//���Լ�¼����ṹ 
extern int step;						//����ִ�б�� 
extern int isBubble;
extern int isSelection;
extern int isMerge;						//����ģʽ��� 
extern int cnt;							//ѡ��/ð��������� 
extern int endcnt;						//ѡ��/ð����ͣʱ�������
extern int stepcnt;						//ѡ��/ð�ݵ���ִ��ʱ������� 
extern int isshow;				//ѡ��/ð����ʾ��� 
extern int end_flag;			//ѡ��/ð�ݽ������ 
extern double sortspeed;  		//�ٶ� 
extern int tmpx;
extern int tmpi;
extern int tmpj;				//ѡ��ð���е�i,j,x 
 
extern int showstep;					//��ʾ���Ĳ��� 
extern int sortstep;					//���򵽵Ĳ��� 
extern int endstep;						//�������Ĳ��� 
extern int stepmode;					//����ִ��ģʽ 
extern int pausemode;					//��ͣģʽ 
