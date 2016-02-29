#pragma once

// DirectDraw
#include <ddraw.h>

// 屏幕属性
#define	DRAW_SCREEN_WIDTH			480			// 屏幕宽度
#define	DRAW_SCREEN_HEIGHT			720			// 屏幕高度
#define	DRAW_SCREEN_WIDTH_MID		240			// 屏幕宽度一半
#define	DRAW_SCREEN_HEIGHT_MID		360			// 屏幕高度一半
#define DRAW_SCREEN_COLOR			16			// 16 位色
#define DRAW_SCREEN_SIZE			345600		// 屏幕占用字节数

// 常用颜色
#define DRAW_COLOR_BLACK			0					// 黑色
#define DRAW_COLOR_WHITE			0xFFFF				// 白色
#define DRAW_COLOR_GREEN			0x07E0				// 绿色
#define DRAW_COLOR_BLUE				0x001F				// 蓝色
#define DRAW_COLOR_RED				0xF800				// 红色
#define DRAW_COLOR_YELLOW			0xFFE0				// 黄色

// 颜色渐变幅度
#define DRAW_COLOR_STEP				32					// 渐变数
#define DRAW_COLOR_ALL_STEP			0x821				// 渐变数
#define DRAW_COLOR_RED_STEP			0x800				// 红色
#define DRAW_COLOR_YELLOW_STEP		0x820				// 黄色
#define DRAW_COLOR_GREEN_STEP		0x20				// 绿色
#define DRAW_COLOR_BLUE_STEP		0x1					// 蓝色
#define DRAW_COLOR_WHITE_STEP		0x841				// 白色


// 定义是否透明
#define DRAW_BLT_NORMAL				0				// 正常填充
#define DRAW_BLT_COLORKEY			DDBLT_KEYSRC	// 透明填充

// 半透明数据
#define DRAW_ALPHA_MIN				0				// 最小半透明色
#define DRAW_ALPHA_MID				128				// 50% 半透明色
#define DRAW_ALPHA_MAX				255				// 最大半透明色

// 图像缓冲
#define DRAW_BACKGROUND_WIDTH		480			// 背景宽度
#define DRAW_BACKGROUND_HEIGHT		720			// 背景高度
#define DRAW_BACKGROUND_SIZE		691200		// 背景大小
#define DRAW_BACKGROUND_FILE		L"Visualization.dat"

#define DRAW_FOREGROUND_WIDTH		1			// 前景宽度
#define DRAW_FOREGROUND_HEIGHT		1			// 前景高度
#define DRAW_FOREGROUND_SIZE		4			// 前景大小
#define DRAW_FOREGROUND_FILE		L"10681027.dat"

// 波形显示设置
#define DRAW_WAVE_MIN				-32767			// 最小值
#define DRAW_WAVE_MIDDLE			0				// 中间值
#define DRAW_WAVE_MAX				32767			// 最大值
#define DRAW_WAVE_RATE_SMALL		69				// 比值小
#define DRAW_WAVE_RATE				138				// 比值
#define DRAW_WAVE_RATE_BIG			276				// 比值大

// 波形显示名称
#define DRAW_NAME_MIN				0			// 最小值
#define DRAW_NAME_MAX				7			// 最大值
#define DRAW_NAME_WAVE				0			// 波形
#define DRAW_NAME_WAVE_LINE			1			// 波形线条
#define DRAW_NAME_LASER				2			// 激光
#define DRAW_NAME_LASER_LINE		3			// 激光线条
#define DRAW_NAME_DOT				4			// 点阵
#define DRAW_NAME_DOT_LINE			5			// 点阵线条
#define DRAW_NAME_STAR				6			// 星星
#define DRAW_NAME_STAR_LINE			7			// 星星线条

// 程序状态
#define DRAW_STATUS_START			0			// 开始
#define DRAW_STATUS_LOGO			1			// 标志
#define DRAW_STATUS_RUN				2			// 运行

// 坐标数据
#define DRAW_LOCATION_COUNT			720			// 坐标计数

// 人物数据
#define DRAW_JACKSON_COUNT				10			// 动作总数
#define DRAW_JACKSON_NAME_STAND			0			// 站立
#define DRAW_JACKSON_NAME_WALK			1			// 步行
#define DRAW_JACKSON_NAME_MOONWALK		2			// 太空步
#define DRAW_JACKSON_NAME_KICK			3			// 踢腿
#define DRAW_JACKSON_NAME_SPINING		4			// 旋转
#define DRAW_JACKSON_NAME_BEAT_IT		5			// BEAT
#define DRAW_JACKSON_NAME_BEAT_IT_DANCE	6			// BEAT IT DANCE
#define DRAW_JACKSON_NAME_BILLIE_JEAN	7			// BILLIE JEAN
#define DRAW_JACKSON_NAME_JUMP			8			// 步行
#define DRAW_JACKSON_NAME_THRILLER		9			// 僵尸
#define DRAW_JACKSON_NAME_SMOOTH		10			// 倒

// 人物动作数据
#define DRAW_JACKSON_STAND_COUNT		2			// 站立帧数
#define DRAW_JACKSON_STAND_WIDTH		46			// 站立宽度
#define DRAW_JACKSON_STAND_HEIGHT		130			// 站立高度

#define DRAW_JACKSON_WALK_COUNT			7			// 步行帧数
#define DRAW_JACKSON_WALK_WIDTH			60			// 步行宽度
#define DRAW_JACKSON_WALK_HEIGHT		130			// 步行高度

// 人物结构
typedef struct{

	RECT*	left;		// 从左往右数据
	RECT*	right;		// 从右往左数据
	BYTE*	step;		// 每一步步长
	BYTE*	time;		// 每一步时长
	BYTE	count;		// 帧数
	BYTE	width;		// 宽度
	BYTE	height;		// 高度

}MICHAEL_JACKSON;

//************************************************************************************************
//*************************** DirectDraw *********************************************************
//************************************************************************************************

#define DDRAW_INIT_STRUCT(ddsd) {memset(&ddsd,0,sizeof(ddsd));ddsd.dwSize=sizeof(ddsd);}
#define _RGB16BIT565(r,g,b) ((b&31)+((g&63)<<5)+((r&31)<<11))

// 初始化
bool DirectDrawInit(HWND);
// 销毁
void DirectDrawEnd(void);
// 创建表面
bool DirectDrawCreateSurface(LPDIRECTDRAWSURFACE*, int, int);

//************************************************************************************************
//*************************** 类型状态 ***********************************************************
//************************************************************************************************

// 设置类型状态（步伐）
void DrawSetWaveNameStep(int);

// 设置类型状态（直接）
void DrawSetWaveName(int);

//************************************************************************************************
//*************************** 视觉效果 ***********************************************************
//************************************************************************************************

// 绘制波形
void DrawVisualizationWave(USHORT*, int);
// 绘制星星
void DrawVisualizationStar(USHORT*, int, bool);
// 绘制波形线条
void DrawVisualizationWaveLine(USHORT*, int, bool);
// 绘制激光线条
void DrawVisualizationLaserLine(USHORT*, int, bool);
// 绘制点阵
void DrawVisualizationDotLine(USHORT*, int, bool);

//************************************************************************************************
//*************************** 人物绘制 ***********************************************************
//************************************************************************************************

// 绘制人物
void DrawMichaelJackson(void);

//************************************************************************************************
//*************************** 标志绘制 ***********************************************************
//************************************************************************************************

// 绘制标志
void DrawLogo(void);

//************************************************************************************************
//*************************** 画面绘制 ***********************************************************
//************************************************************************************************

// 游戏绘制入口
void Draw(void);
// 清屏幕（内存）
void DrawCls(USHORT*, int, USHORT);
// 清屏
void DrawClsRect(void);
// 绘制主表面
void DrawPrimary(void);

/*************************** 矩形绘制 ****************************************/

// 绘制矩形
void DrawRect(LPDIRECTDRAWSURFACE, RECT*, RECT*, int);
// 快速绘制矩形（半透明）
void DrawRectAlpha(LPDIRECTDRAWSURFACE, RECT*, RECT*, int);

//************************************************************************************************
//*************************** 音频部分 ***********************************************************
//************************************************************************************************

// 给绘图模块发送数据指针
void DrawSetWaveData(SHORT*);
// 绘制声音图形
void DrawWaveData(void);

//************************************************************************************************
//*************************** 素 材 读 取 ********************************************************
//************************************************************************************************

// 读取图像文件
bool LoadingImageFile(LPTSTR, int, LPDIRECTDRAWSURFACE);