#pragma once

// �����趨
#define		PAINT_MAX_WIDTH		480			// ��ͼ���
#define		PAINT_MAX_HEGITH	720			// ��ͼ�߶�
#define		PAINT_CENTER_X		240			// X ���м�
#define		PAINT_CENTER_Y		360			// Y ���м�

// ��ѧ����
#define		PI				3.1415926		// Բ����

// internal clipping codes
#define CLIP_CODE_C  0x0000
#define CLIP_CODE_N  0x0008
#define CLIP_CODE_S  0x0004
#define CLIP_CODE_E  0x0002
#define CLIP_CODE_W  0x0001

#define CLIP_CODE_NE 0x000a
#define CLIP_CODE_SE 0x0006
#define CLIP_CODE_NW 0x0009 
#define CLIP_CODE_SW 0x0005

//************************************************************************************************
//*************************** �� ͼ �� �� ********************************************************
//************************************************************************************************

// ����
void PaintPixel(USHORT*, int, int, USHORT, int);
// ���ߣ�δ�ü���
void PaintLineNotClip(USHORT*, int, int, int, int, USHORT, int);
// ���ߣ��Ѳü���
void PaintLine(USHORT*, int, int, int, int, USHORT, int);
// ���βü�
bool PaintClip(int &x1,int &y1,int &x2, int &y2);