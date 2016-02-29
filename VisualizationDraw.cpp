// 预编译
#include "stdafx.h"

// 画面绘制
#include "VisualizationDraw.h"
// 图形绘制
#include "VisualizationPaint.h"
// 文件操作
#include "VisualizationFile.h"

// DirectDraw 全局变量

DDSURFACEDESC			TheDDrawSurface;		// DirectDraw 表面结构
DDCOLORKEY				TheDDrawColorKey;		// DirectDraw 透明色
DDALPHABLTFX			TheDDrawAlphaBltfx;		// DirectDraw 半透明色	
DDPIXELFORMAT			TheDDrawPixelFormat;	// DirectDraw 像素格式结构

LPDIRECTDRAW			TheDDraw;				// DirectDraw 界面
LPDIRECTDRAWCLIPPER		TheDDrawClipper;		// DirectDraw 裁剪器
LPDIRECTDRAWSURFACE		TheDDrawPrimary;		// DirectDraw 主表面
LPDIRECTDRAWSURFACE		TheDDrawBackBuffer;		// DirectDraw 后备表面
LPDIRECTDRAWSURFACE		TheDDrawBackground;		// DirectDraw 背景表面
LPDIRECTDRAWSURFACE		TheDDrawForeground;		// DirectDraw 前景表面

//************************** 全局矩阵 *********************************************//

// 屏幕矩阵
RECT	TheRectScreen = {0,0,PAINT_MAX_WIDTH,PAINT_MAX_HEGITH};
// 目标矩阵
RECT	TheRectTarget = {0,0,0,0};
// 来源矩阵
RECT	TheRectSource = {0,0,0,0};

//************************** 颜色部分 *********************************************//

RECT	TheRectColorBlack = {0,0,1,1};		 // 黑色矩阵

//************************** 文字部分 *********************************************//

RECT	TheRectTextTitle = {113,321,137,641};
RECT	TheRectTextTitleTarget = {228,321,252,641};

//************************** 人物部分 *********************************************//

RECT	TheRectJacksonHead = {348,625,449,719};
RECT	TheRectJacksonHeadTarget = {190,150,291,244};

// 站立
RECT	TheRectJacksonStandLeft[DRAW_JACKSON_STAND_COUNT] = {{11,565,76,587},{11,588,76,610}};
RECT	TheRectJacksonStandRight[DRAW_JACKSON_STAND_COUNT] = {{11,634,76,656},{11,611,76,633}};
BYTE	TheStepJacksonStand[DRAW_JACKSON_STAND_COUNT] = {0,0};
BYTE	TheTimeJacksonStand[DRAW_JACKSON_STAND_COUNT] = {3,3};

// 步行
RECT	TheRectJacksonWalkLeft[DRAW_JACKSON_WALK_COUNT] ={{414,1,479,30},{414,31,479,60},{414,61,479,90},{414,91,479,120},{414,121,479,150},{414,151,479,180},{414,181,479,210}};
RECT	TheRectJacksonWalkRight[DRAW_JACKSON_WALK_COUNT] ={{414,391,479,420},{414,361,479,390},{414,331,479,360},{414,301,479,330},{414,271,479,300},{414,241,479,270},{414,211,479,240}};
BYTE	TheStepJacksonWalk[DRAW_JACKSON_WALK_COUNT] = {2,2,2,2,2,2,2};
BYTE	TheTimeJacksonWalk[DRAW_JACKSON_WALK_COUNT] = {2,2,2,2,2,2,2};

// 人物结构
MICHAEL_JACKSON	TheMichaelJackson[DRAW_JACKSON_COUNT] = {

	{TheRectJacksonStandLeft,TheRectJacksonStandRight,TheStepJacksonStand,TheTimeJacksonStand,DRAW_JACKSON_STAND_COUNT,DRAW_JACKSON_STAND_WIDTH,DRAW_JACKSON_STAND_HEIGHT},		// 站立
	{TheRectJacksonWalkLeft,TheRectJacksonWalkRight,TheStepJacksonWalk,TheTimeJacksonWalk,DRAW_JACKSON_WALK_COUNT,DRAW_JACKSON_WALK_WIDTH,DRAW_JACKSON_WALK_HEIGHT}				// 步行

};

// 全局控制变量
int	TheJacksonIndex = 0;			// 当前人物动作
int	TheJacksonLocation = 0;			// 当前人物位置
int	TheJacksonStep = 0;				// 当前人物帧数
int	TheJacksonTime = 0;				// 当前人物时间控制
bool TheJacksonIsLeft = true;		// 是否由左往右

//************************** 音频数据 *********************************************//

SHORT*	TheDrawWaveData;

//************************** 状态数据 *********************************************//

// 程序状态
int TheDrawStatus = DRAW_STATUS_START;
// 类型状态
int TheDrawWaveName = DRAW_NAME_STAR;
// 索引
int TheDrawIndex = 0;
// 步伐
int TheDrawStep = 0;
// 进程
int TheDrawFoot = 0;

//************************** 坐标数据 *********************************************//

int TheDrawLocationX[DRAW_LOCATION_COUNT];
int TheDrawLocationY[DRAW_LOCATION_COUNT];

double TheDrawAreaX[DRAW_LOCATION_COUNT];
double TheDrawAreaY[DRAW_LOCATION_COUNT];


//************************************************************************************************
//*************************** 类型状态 ***********************************************************
//************************************************************************************************

// 设置类型状态（步伐）
void DrawSetWaveNameStep(int i)
{

	// 设置值
	TheDrawWaveName+=i;

	// 小于最小值
	if(TheDrawWaveName<DRAW_NAME_MIN){
		TheDrawWaveName = DRAW_NAME_MAX;
		return;
	}

	// 大于最大值
	if(TheDrawWaveName>DRAW_NAME_MAX){
		TheDrawWaveName = DRAW_NAME_MIN;
		return;
	}

}

// 设置类型状态（直接）
void DrawSetWaveName(int i)
{

	// 设置值
	TheDrawWaveName=i;

}

//************************************************************************************************
//*************************** 音频部分 ***********************************************************
//************************************************************************************************

// 给绘图模块发送数据指针
void DrawSetWaveData(SHORT* data)
{

	// 复制指针
	TheDrawWaveData = data;

}

// 绘制声音图形
void DrawWaveData(void)
{

	// 没有获取到数据
	if(TheDrawWaveData==NULL){
		return;
	}

	// 间距
	int pitch = 0;

	// 初始化表面结构
	DDRAW_INIT_STRUCT(TheDDrawSurface);
	// 锁定表面
	if(TheDDrawBackBuffer->Lock(NULL,&TheDDrawSurface,DDLOCK_WAITNOTBUSY,NULL)==DD_OK){

		// 获取数据指针
		USHORT* bb = (USHORT*)TheDDrawSurface.lpSurface;
		// 计算间距
		pitch = (int)(TheDDrawSurface.lPitch>>1);

		// 这里直接对显存操作
		/*******************************/

		// 绘制图形
		DrawVisualizationWave(bb,pitch);

		/*******************************/

		// 解锁表面
		TheDDrawBackBuffer->Unlock(NULL);
	
	}

}

//************************************************************************************************
//*************************** 视觉效果 ***********************************************************
//************************************************************************************************

// 绘制波形
void DrawVisualizationWave(USHORT* bb, int lPitch)
{

	// 绘制图案判断
	switch(TheDrawWaveName){

		// 绘制波形
		case DRAW_NAME_WAVE:

			// 绘制波形线条
			DrawVisualizationWaveLine(bb, lPitch,false);
			break;

		// 绘制波形（线）
		case DRAW_NAME_WAVE_LINE:

			// 绘制波形线条
			DrawVisualizationWaveLine(bb,lPitch,true);
			break;

		// 绘制激光线条（点）
		case DRAW_NAME_LASER:

			// 绘制激光线条
			DrawVisualizationLaserLine(bb,lPitch,false);
			break;

		// 绘制激光线条（线）
		case DRAW_NAME_LASER_LINE:

			// 绘制激光线条
			DrawVisualizationLaserLine(bb,lPitch,true);
			break;

		// 绘制点阵（点）
		case DRAW_NAME_DOT:

			// 绘制点阵（点）
			DrawVisualizationDotLine(bb,lPitch,false);
			break;

		// 绘制点阵（线）
		case DRAW_NAME_DOT_LINE:

			// 绘制点阵（线）
			DrawVisualizationDotLine(bb,lPitch,true);
			break;

		// 绘制星星
		case DRAW_NAME_STAR:

			// 绘制星星
			DrawVisualizationStar(bb,lPitch,false);
			break;

		// 绘制星星线条
		case DRAW_NAME_STAR_LINE:

			// 绘制星星
			DrawVisualizationStar(bb,lPitch,true);
			break;
	
	}

}

// 绘制星星
void DrawVisualizationStar(USHORT* bb, int lPitch, bool isLine)
{

	// 清屏幕
	DrawCls(bb,lPitch,DRAW_COLOR_BLACK);

	// 清零
	TheDrawFoot = 0;

	// 绘制点阵
	for(int i=0;i<PAINT_MAX_HEGITH;i++){

		// 计算坐标
		TheDrawIndex = abs(TheDrawWaveData[i]+DRAW_WAVE_MIN);
		TheDrawStep =  TheDrawIndex / 4096;

		// 获取颜色
		if(TheDrawIndex>TheDrawFoot){
			TheDrawFoot = TheDrawIndex;
		}

		// 超出范围重新生成坐标
		if((TheDrawLocationX[i]<0)){
			TheDrawLocationX[i] = DRAW_SCREEN_WIDTH_MID + rand()%DRAW_SCREEN_WIDTH_MID;
			TheDrawLocationY[i] = rand()%DRAW_SCREEN_HEIGHT;
		}

		// 往下掉
		TheDrawLocationX[i]-=TheDrawStep;

		// 画线
		if(isLine){

			// 颜色
			TheDrawFoot = TheDrawWaveData[i];

			// 画点
			for(int j=0;j<DRAW_COLOR_STEP;j++){			
				PaintPixel(bb,TheDrawLocationX[i]+j*(2+j)/2,TheDrawLocationY[i],TheDrawFoot-j*DRAW_COLOR_ALL_STEP,lPitch);
			}

		}else{

			// 画点（星星）
			PaintPixel(bb,TheDrawLocationX[i]-i,TheDrawLocationY[i],TheDrawFoot,lPitch);
			PaintPixel(bb,TheDrawLocationX[i],TheDrawLocationY[i]+i,TheDrawFoot,lPitch);
			PaintPixel(bb,TheDrawLocationX[i]+i,TheDrawLocationY[i],TheDrawFoot,lPitch);
			PaintPixel(bb,TheDrawLocationX[i],TheDrawLocationY[i]-i,TheDrawFoot,lPitch);
		
		}

		// 画点（星星）
		PaintPixel(bb,TheDrawLocationX[i]-1,TheDrawLocationY[i]-1,TheDrawFoot,lPitch);		
		PaintPixel(bb,TheDrawLocationX[i]-1,TheDrawLocationY[i]+1,TheDrawFoot,lPitch);		
		PaintPixel(bb,TheDrawLocationX[i]+1,TheDrawLocationY[i]+1,TheDrawFoot,lPitch);		
		PaintPixel(bb,TheDrawLocationX[i]+1,TheDrawLocationY[i]-1,TheDrawFoot,lPitch);

	}

}

// 绘制点阵
void DrawVisualizationDotLine(USHORT* bb, int lPitch,bool isLine)
{

	// 清屏幕
	DrawCls(bb,lPitch,DRAW_COLOR_BLACK);

	// 绘制点阵
	for(int i=0;i<PAINT_MAX_HEGITH;i++){

		if(isLine){

			// 画点
			TheDrawLocationX[0] = abs(TheDrawWaveData[i]+DRAW_WAVE_MIN)*5;
			bb[TheDrawLocationX[0]] = DRAW_COLOR_WHITE;

			// 过度线
			for(int j=0;j<DRAW_COLOR_STEP;j++){

				// 计算坐标
				TheDrawLocationX[1] = TheDrawLocationX[0] + j*(2+j)/2*lPitch+j;
				TheDrawLocationX[2] = TheDrawLocationX[0] - j*(2+j)/2*lPitch-j;
		
				// 超出范围
				if(TheDrawLocationX[1]>DRAW_SCREEN_SIZE){
					TheDrawLocationX[1] = DRAW_SCREEN_SIZE;
				}

				// 小于最小值
				if(TheDrawLocationX[2]<0){
					TheDrawLocationX[2] = 0;
				}

				// 过度点
				bb[TheDrawLocationX[1]] = DRAW_COLOR_RED-j*DRAW_COLOR_RED_STEP;		
				bb[TheDrawLocationX[2]] = DRAW_COLOR_RED-j*DRAW_COLOR_RED_STEP;		

			}
		
		// 画点
		}else{

			// 计算新坐标
			if(TheDrawLocationX[i]<=0){

				TheDrawLocationX[i] = DRAW_SCREEN_WIDTH_MID + rand()%DRAW_SCREEN_WIDTH_MID;
				TheDrawLocationY[i] = rand()%DRAW_SCREEN_HEIGHT;

			}

			// 下降
			TheDrawLocationX[i] -= abs((int)(sin(TheDrawWaveData[i])*cos(TheDrawWaveData[i]) + TheDrawWaveData[i]/256))+2;

			// 过度线
			for(int j=0;j<10;j++){

				// 步长
				TheDrawIndex = j*(5+j)/5;
				// 颜色
				TheDrawStep = TheDrawWaveData[i]-j*DRAW_COLOR_ALL_STEP;

				// 画点
				PaintPixel(bb,TheDrawLocationX[i]+TheDrawIndex,TheDrawLocationY[i]-TheDrawIndex,TheDrawStep,lPitch);				
				PaintPixel(bb,TheDrawLocationX[i]-TheDrawIndex,TheDrawLocationY[i]-TheDrawIndex,TheDrawStep,lPitch);
				PaintPixel(bb,TheDrawLocationX[i]+TheDrawIndex,TheDrawLocationY[i]+TheDrawIndex,TheDrawStep,lPitch);
				PaintPixel(bb,TheDrawLocationX[i]-TheDrawIndex,TheDrawLocationY[i]+TheDrawIndex,TheDrawStep,lPitch);				

			}
			
			// 白点
			PaintPixel(bb,TheDrawLocationX[i],TheDrawLocationY[i],DRAW_COLOR_WHITE,lPitch);

		}

	}

}

// 绘制激光线条
void DrawVisualizationLaserLine(USHORT* bb, int lPitch,bool isLine)
{

	// 清屏幕
	DrawCls(bb,lPitch,DRAW_COLOR_BLACK);

	// 绘制激光线条
	for(int i=0;i<PAINT_MAX_HEGITH;i++){

		// 半径
		TheDrawAreaX[1] = (TheDrawWaveData[i]+DRAW_WAVE_MIN)/DRAW_WAVE_RATE_BIG;
		// 角度
		TheDrawAreaY[1] = (i+TheDrawIndex)*PI/180;

		// X坐标
		TheDrawAreaX[0] = DRAW_SCREEN_WIDTH_MID + TheDrawAreaX[1]*cos(TheDrawAreaY[1]);
		// Y坐标
		TheDrawAreaY[0] = DRAW_SCREEN_HEIGHT_MID + TheDrawAreaX[1]*sin(TheDrawAreaY[1]);

		// 坐标
		TheDrawLocationX[0] = (int)TheDrawAreaX[0];
		TheDrawLocationY[0] = (int)TheDrawAreaY[0];
		
		// 是否线条
		if(isLine){

			// 画线
			PaintLineNotClip(bb,DRAW_SCREEN_WIDTH_MID,DRAW_SCREEN_HEIGHT_MID,TheDrawLocationX[0],TheDrawLocationY[0],DRAW_COLOR_WHITE-i*64,lPitch);

		}else{	

			// 彩色点
			PaintPixel(bb,TheDrawLocationX[0],TheDrawLocationY[0],TheDrawWaveData[i],lPitch);			

		}

		// 旋转
		TheDrawIndex++;
		// 复位
		if(TheDrawIndex>360){TheDrawIndex=0;}
	
	}

}

// 绘制波形线条
void DrawVisualizationWaveLine(USHORT* bb, int lPitch,bool isLine)
{

	// 是否线条
	if(!isLine){
		// 清屏幕
		DrawCls(bb,lPitch,DRAW_COLOR_BLACK);
	}

	// 绘制波形线条
	for(int i=0;i<PAINT_MAX_HEGITH;i++){

		// 是否线条
		if(isLine){

			// 计算坐标
			TheDrawLocationY[i] = abs(TheDrawWaveData[i])/DRAW_WAVE_RATE_SMALL;

			// 复制坐标
			if(TheDrawLocationX[i]<TheDrawLocationY[i]){
				TheDrawLocationX[i] = TheDrawLocationY[i];
			}else{
				TheDrawLocationX[i]-=5;
			}

			// 超过最大值
			if(TheDrawLocationX[i]>DRAW_SCREEN_WIDTH){TheDrawLocationX[i] = DRAW_SCREEN_WIDTH-1;}
			// 低于最小值
			if(TheDrawLocationX[i]<0){TheDrawLocationX[i] = 0;}
			
			// 画线段
			PaintLineNotClip(bb,0,i,TheDrawLocationX[i],i,DRAW_COLOR_BLUE,lPitch);

			// 过度线
			for(int j=0;j<DRAW_COLOR_STEP;j++){
				// 红点
				PaintPixel(bb,TheDrawLocationX[i]+j*(2+j)/2,i,DRAW_COLOR_BLUE-j*DRAW_COLOR_BLUE_STEP,lPitch);		
			}		

			// 白点
			PaintPixel(bb,TheDrawLocationX[i]+2,i,DRAW_COLOR_WHITE,lPitch);

		}else{

			// 计算坐标
			TheDrawLocationY[0] = (TheDrawWaveData[i]+DRAW_WAVE_MIN)/DRAW_WAVE_RATE;
			TheDrawLocationY[1] = (TheDrawWaveData[i+1]+DRAW_WAVE_MIN)/DRAW_WAVE_RATE;
			
			// 画线段
			PaintLineNotClip(bb,TheDrawLocationY[0],i,TheDrawLocationY[1],i+1,DRAW_COLOR_GREEN,lPitch);

		}

	}

}

//************************************************************************************************
//*************************** 人物绘制 ***********************************************************
//************************************************************************************************

// 绘制人物
void DrawMichaelJackson(void)
{

	// 由左往右
	if(TheJacksonIsLeft){

		// 获取数据源
		TheRectSource.left = TheMichaelJackson[TheJacksonIndex].left[TheJacksonStep].left;
		TheRectSource.right = TheMichaelJackson[TheJacksonIndex].left[TheJacksonStep].right;
		TheRectSource.top = TheMichaelJackson[TheJacksonIndex].left[TheJacksonStep].top;
		TheRectSource.bottom = TheMichaelJackson[TheJacksonIndex].left[TheJacksonStep].bottom;

		// 计算目标位置
		TheRectTarget.bottom = TheJacksonLocation+TheMichaelJackson[TheJacksonIndex].width;

	}else{

		// 获取数据源
		TheRectSource.left = TheMichaelJackson[TheJacksonIndex].right[TheJacksonStep].left;
		TheRectSource.right = TheMichaelJackson[TheJacksonIndex].right[TheJacksonStep].right;
		TheRectSource.top = TheMichaelJackson[TheJacksonIndex].right[TheJacksonStep].top;
		TheRectSource.bottom = TheMichaelJackson[TheJacksonIndex].right[TheJacksonStep].bottom;

		// 计算目标位置
		TheRectTarget.bottom = TheJacksonLocation-TheMichaelJackson[TheJacksonIndex].width;

	}

	// 目的位置
	TheRectTarget.left = 0;
	TheRectTarget.right = TheMichaelJackson[TheJacksonIndex].height;
	TheRectTarget.top = TheJacksonLocation;

	// 绘制矩形
	DrawRect(TheDDrawBackground,&TheRectSource,&TheRectTarget,DRAW_BLT_COLORKEY);

	// 播放下一帧
	TheJacksonTime++;

	// 一帧播放完成
	if(TheJacksonTime>TheMichaelJackson[TheJacksonIndex].time[TheJacksonStep]){

		// 时间状态清零
		TheJacksonTime=0;
		
		// 从左往右
		if(TheJacksonIsLeft){
			TheJacksonLocation+=TheMichaelJackson[TheJacksonIndex].step[TheJacksonStep];
		// 从右往左
		}else{
			TheJacksonLocation-=TheMichaelJackson[TheJacksonIndex].step[TheJacksonStep];
		}

		// 超过屏幕右侧
		if(TheJacksonLocation>DRAW_SCREEN_HEIGHT-TheMichaelJackson[TheJacksonIndex].width){			
			TheJacksonIsLeft = false;
		}

		// 超过屏幕左右
		if(TheJacksonLocation<0+TheMichaelJackson[TheJacksonIndex].width){			
			TheJacksonIsLeft = true;
		}

		// 进入下一帧
		TheJacksonStep++;

	}

	// 全部动作完成
	if(TheJacksonStep>=TheMichaelJackson[TheJacksonIndex].count){

		// 恢复站立姿势
		TheJacksonStep=0;

		// 恢复站立
		if(TheJacksonIndex>0){
			TheJacksonIndex=0;
		}else{
			TheJacksonIndex=1;
		}

	}
	

}

//************************************************************************************************
//*************************** 标志绘制 ***********************************************************
//************************************************************************************************

// 绘制标志
void DrawLogo(void)
{

	// 文字
	DrawRect(TheDDrawBackground,&TheRectTextTitle,&TheRectTextTitleTarget,DRAW_BLT_COLORKEY);

	// 头像
	DrawRect(TheDDrawBackground,&TheRectJacksonHead,&TheRectJacksonHeadTarget,DRAW_BLT_NORMAL);

	// 等待
	TheDrawIndex++;

	// 两秒钟后切换画面
	if(TheDrawIndex>60){
		TheDrawStatus = DRAW_STATUS_RUN;
	}

}

//************************************************************************************************
//*************************** 画面绘制 ***********************************************************
//************************************************************************************************

// 游戏绘制入口
void Draw(void)
{

	// 状态判断
	switch(TheDrawStatus){

		// 开始
		case DRAW_STATUS_START:
			
			// 读取背景图像文件
			if(LoadingImageFile(DRAW_BACKGROUND_FILE, DRAW_BACKGROUND_SIZE, TheDDrawBackground)){
				TheDrawStatus = DRAW_STATUS_LOGO;
			}else{
				PostQuitMessage(0);
			}
			
			break;

		// 标志
		case DRAW_STATUS_LOGO:

			// 绘制标志
			DrawLogo();
			break;

		// 运行
		case DRAW_STATUS_RUN:

			// 绘制声波图形
			DrawWaveData();

			// 绘制人物
			DrawMichaelJackson();
			break;
	
	
	}
	
	// 显示主表面
	DrawPrimary();

}

// 清屏幕（内存）
void DrawCls(USHORT* bb, int lPitch, USHORT color)
{
	
	// 宽度与屏幕相同
	if(lPitch==DRAW_SCREEN_WIDTH){
		
		// 填充颜色
		for(int i=0;i<DRAW_SCREEN_SIZE;i++){
			bb[i] = color;
		}

	// 有额外内存
	}else{

		// 依坐标填充颜色
		for(int x=0;x<DRAW_SCREEN_WIDTH;x++){
			for(int y=0;y<DRAW_SCREEN_HEIGHT;y++){
				bb[x+y*lPitch] = color;
			}		
		}
	
	}
	
}

// 清屏幕（矩阵）
void DrawClsRect(void)
{
	
	// 绘制矩形
	DrawRect(TheDDrawBackground,&TheRectColorBlack,&TheRectScreen,DRAW_BLT_NORMAL);
	
}

// 绘制主表面
void DrawPrimary(void)
{
	
	// 将后备表面复制到主表面
	TheDDrawPrimary->Blt(&TheRectScreen,TheDDrawBackBuffer,&TheRectScreen,DDBLT_WAITNOTBUSY,NULL);	

}

// 绘制暂停画面
void DrawPause(void)
{

	

}

//************************************************************************************************
//*************************** DirectDraw *********************************************************
//************************************************************************************************


// 初始化
bool DirectDrawInit(HWND hwnd)
{

	// 创建DirectDraw对象
	if(DirectDrawCreate(NULL,&TheDDraw,NULL)!=DD_OK){
		return false;
	}

	// 设置协作方式
	if(TheDDraw->SetCooperativeLevel(hwnd,DDSCL_NORMAL)!=DD_OK){
		return false;
	}

	/********************************主表面****************************************/

	// 初始化表面结构
	DDRAW_INIT_STRUCT(TheDDrawSurface);

	TheDDrawSurface.dwFlags = DDSD_CAPS;
	TheDDrawSurface.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	// 创建主表面
	if(TheDDraw->CreateSurface(&TheDDrawSurface,&TheDDrawPrimary,NULL)!=DD_OK){
		return false;
	}

	// 设置像素格式	
	DDRAW_INIT_STRUCT(TheDDrawPixelFormat);
	// 获取像素格式
	TheDDrawPrimary->GetPixelFormat(&TheDDrawPixelFormat);

	// 如果不是16位色模式
	if(TheDDrawPixelFormat.dwRGBBitCount!=DRAW_SCREEN_COLOR){
		return false;
	}

	// 创建裁剪器
	if(TheDDraw->CreateClipper(0,&TheDDrawClipper,NULL)!=DD_OK){
		return false;
	}
	
	// 设置裁剪器窗口句柄
	if(TheDDrawClipper->SetHWnd(0,hwnd)!=DD_OK){
		return false;
	}

	// 关联裁剪器
	if(TheDDrawPrimary->SetClipper(TheDDrawClipper)!=DD_OK){
		return false;
	}

	// 创建后备表面
	if(!DirectDrawCreateSurface(&TheDDrawBackBuffer,DRAW_SCREEN_WIDTH,DRAW_SCREEN_HEIGHT)){
		return false;
	}

	// 创建背景表面
	if(!DirectDrawCreateSurface(&TheDDrawBackground,DRAW_BACKGROUND_WIDTH,DRAW_BACKGROUND_HEIGHT)){
		return false;
	}

	// 创建前景表面
	if(!DirectDrawCreateSurface(&TheDDrawForeground,DRAW_FOREGROUND_WIDTH,DRAW_FOREGROUND_HEIGHT)){
		return false;
	}

	// 设置透明色	
	TheDDrawColorKey.dwColorSpaceHighValue = DRAW_COLOR_GREEN;
	TheDDrawColorKey.dwColorSpaceLowValue = DRAW_COLOR_GREEN;
	TheDDrawBackground->SetColorKey(DDCKEY_SRCBLT,&TheDDrawColorKey);

	// 初始化半透明结构
	DDRAW_INIT_STRUCT(TheDDrawAlphaBltfx);

	return true;

}

// 创建表面
bool DirectDrawCreateSurface(LPDIRECTDRAWSURFACE* s, int w, int h)
{

	// 初始化表面结构
	DDRAW_INIT_STRUCT(TheDDrawSurface);

	// 设置资料读取中表面参数
	TheDDrawSurface.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	TheDDrawSurface.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY;
	TheDDrawSurface.dwWidth = w;
	TheDDrawSurface.dwHeight = h;

	// 创建资料读取中表面
	if(TheDDraw->CreateSurface(&TheDDrawSurface,s,NULL)!=DD_OK){
		return false;
	}

	return true;

}

// 销毁
void DirectDrawEnd(void)
{

	// 释放前景表面
	if(TheDDrawForeground){
		TheDDrawForeground->Release();
		TheDDrawForeground = NULL;
	}

	// 释放背景表面
	if(TheDDrawBackground){
		TheDDrawBackground->Release();
		TheDDrawBackground = NULL;
	}

	// 释放后备表面
	if(TheDDrawBackBuffer){
		TheDDrawBackBuffer->Release();
		TheDDrawBackBuffer = NULL;
	}

	// 释放主表面
	if(TheDDrawPrimary){
		TheDDrawPrimary->Release();
		TheDDrawPrimary = NULL;
	}

	// 销毁剪切版
	if(TheDDrawClipper){
		TheDDrawClipper->Release();
		TheDDrawClipper = NULL;
	}

	// 释放内部分配资源
	if(TheDDraw){
		TheDDraw->Release();
		TheDDraw = NULL;
	}

}

//************************************************************************************************
//*************************** 素 材 读 取 ********************************************************
//************************************************************************************************


// 读取图像文件
bool LoadingImageFile(LPTSTR imgFile, int imgSize, LPDIRECTDRAWSURFACE imgSurface)
{

	bool flag = false;

	// 初始化表面结构
	DDRAW_INIT_STRUCT(TheDDrawSurface);

	// 锁定主角表面
	if(imgSurface->Lock(NULL,&TheDDrawSurface,DDLOCK_WAITNOTBUSY,NULL)!=DD_OK){
		return false;
	}

	// 缓冲数据
	CHAR* bb = (CHAR *)TheDDrawSurface.lpSurface;

	// 读取文件
	flag = FileGetData(imgFile,bb,imgSize);

	// 解锁主角表面
	imgSurface->Unlock(NULL);

	// 操作成功
	return flag;	

}



//************************************************************************************************
//*************************** 矩 形 绘 制 ********************************************************
//************************************************************************************************

// 快速绘制矩形
void DrawRect(LPDIRECTDRAWSURFACE ddSurface, RECT* rSource, RECT* rTarget, int colorkey)
{

	// 复制源画面数据至后备画面
	TheDDrawBackBuffer->Blt(rTarget,ddSurface,rSource,DDBLT_WAITNOTBUSY|colorkey,NULL);

}

// 快速绘制矩形（半透明）
void DrawRectAlpha(LPDIRECTDRAWSURFACE ddSurface, RECT* rSource, RECT* rTarget, int alpha)
{

	// 设置半透明程度
	TheDDrawAlphaBltfx.ddargbScaleFactors.alpha = alpha;

	// 复制源画面数据至后备画面
	TheDDrawBackBuffer->AlphaBlt(rTarget,ddSurface,rSource,DDABLT_WAITNOTBUSY|DDABLT_ALPHASRCNEG,&TheDDrawAlphaBltfx);

}