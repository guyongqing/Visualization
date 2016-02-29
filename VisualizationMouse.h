#pragma once

//************************************************************************************************
//*************************** 鼠标处理 ***********************************************************
//************************************************************************************************

/************************ 鼠标区间 **********************************/

// 鼠标坐标是否在某个矩阵中
bool MouseRectArea(RECT*, int, int);

/************************ 鼠标双击时 **********************************/

// 鼠标双击时
void MouseClick(int, int);

/************************ 鼠标移动时 **********************************/

// 鼠标移动时
void MouseMove(int, int);

/************************ 鼠标抬起时 **********************************/

// 鼠标抬起时
void MouseUp(int, int);

/************************ 鼠标按下时 **********************************/

// 鼠标按下时
void MouseDown(int, int);

