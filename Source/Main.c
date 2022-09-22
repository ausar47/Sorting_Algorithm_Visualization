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

void MouseEventProcess(int x,int y,int button,int event);
void KeyboardEventProcess(int key, int event);

void Main()
{
	InitGraphics();
	InitWindowGraphics();						//�����ʼ�������� 
	registerMouseEvent(MouseEventProcess);		//ע�������Ϣ�ص�����
	registerKeyboardEvent(KeyboardEventProcess);//ע�������Ϣ�ص����� 
}
