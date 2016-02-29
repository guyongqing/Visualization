
// 预编译
#include "stdafx.h"
// 头文件
#include "VisualizationMouse.h"
#include "VisualizationDraw.h"
#include "VisualizationGame.h"

//************************************************************************************************
//*************************** 鼠标处理 ***********************************************************
//************************************************************************************************

// 鼠标坐标
int TheMouseLocationX = 0;
int TheMouseLocationY = 0;

/************************ 鼠标区间 **********************************/

// 鼠标坐标是否在某个矩阵中
bool MouseRectArea(RECT* rect, int x, int y)
{

	// 横坐标
	if((x>rect->left)&&(x<rect->right)){

		// 纵坐标
		if((y>rect->top)&&(y<rect->bottom)){
		
			return true;

		}
	
	}

	return false;

}

/************************ 鼠标双击时 **********************************/

// 鼠标双击时
void MouseClick(int x, int y)
{
}

/************************ 鼠标移动时 **********************************/

// 鼠标移动时
void MouseMove(int x, int y)
{

	

}

/************************ 鼠标抬起时 **********************************/

// 鼠标抬起时
void MouseUp(int x, int y)
{

	// 移动太少
	if(abs(TheMouseLocationY-y)<200){
		return;
	}

	// 移动太多
	if(abs(TheMouseLocationX-x)>200){
	}

	// 改变状态
	if(y<TheMouseLocationY){
		DrawSetWaveNameStep(-1);
	}else{
		DrawSetWaveNameStep(1);
	}
	

}

/************************ 鼠标按下时 **********************************/

// 鼠标按下时
void MouseDown(int x, int y)
{

	// 复制坐标
	TheMouseLocationX = x;
	TheMouseLocationY = y;

}