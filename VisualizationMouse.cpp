
// Ԥ����
#include "stdafx.h"
// ͷ�ļ�
#include "VisualizationMouse.h"
#include "VisualizationDraw.h"
#include "VisualizationGame.h"

//************************************************************************************************
//*************************** ��괦�� ***********************************************************
//************************************************************************************************

// �������
int TheMouseLocationX = 0;
int TheMouseLocationY = 0;

/************************ ������� **********************************/

// ��������Ƿ���ĳ��������
bool MouseRectArea(RECT* rect, int x, int y)
{

	// ������
	if((x>rect->left)&&(x<rect->right)){

		// ������
		if((y>rect->top)&&(y<rect->bottom)){
		
			return true;

		}
	
	}

	return false;

}

/************************ ���˫��ʱ **********************************/

// ���˫��ʱ
void MouseClick(int x, int y)
{
}

/************************ ����ƶ�ʱ **********************************/

// ����ƶ�ʱ
void MouseMove(int x, int y)
{

	

}

/************************ ���̧��ʱ **********************************/

// ���̧��ʱ
void MouseUp(int x, int y)
{

	// �ƶ�̫��
	if(abs(TheMouseLocationY-y)<200){
		return;
	}

	// �ƶ�̫��
	if(abs(TheMouseLocationX-x)>200){
	}

	// �ı�״̬
	if(y<TheMouseLocationY){
		DrawSetWaveNameStep(-1);
	}else{
		DrawSetWaveNameStep(1);
	}
	

}

/************************ ��갴��ʱ **********************************/

// ��갴��ʱ
void MouseDown(int x, int y)
{

	// ��������
	TheMouseLocationX = x;
	TheMouseLocationY = y;

}