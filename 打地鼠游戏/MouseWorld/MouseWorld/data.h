#ifndef _DATA_H_
#define _DATA_H_

#include "SDL.h"
#include <iostream>
#include "SDL_image.h"
using namespace std;

/* ͼƬ����·�� */
#define PATH_BACKGROUND "..\\image\\background.png" // ����ͼƬ

/* ����ǰ����ͼƬ����·�� */
#define PATH_SPRITE_NORMAL_1  "..\\image\\mouse1.png"   // ��ͨ����1
#define PATH_SPRITE_NORMAL_2    "..\\image\\mouse3.png"      // ��ͨ����2
#define PATH_SPRITE_NORMAL_3 "..\\image\\mouse5.png"  // ��ͨ����3
#define PATH_SPRITE_NORMAL_4     "..\\image\\mouse7.png"     // ��ͨ����4
#define PATH_SPRITE_NORMAL_5  "..\\image\\mouse9.png"   // ��ͨ����5

/* �������ͼƬ����·�� */
#define PATH_SPRITE_BEAT_1 "..\\image\\mouse2.png"
#define PATH_SPRITE_BEAT_2 "..\\image\\mouse4.png"
#define PATH_SPRITE_BEAT_3 "..\\image\\mouse6.png"
#define PATH_SPRITE_BEAT_4 "..\\image\\mouse8.png"
#define PATH_SPRITE_BEAT_5 "..\\image\\mouse10.png"

/* ����ͼƬ����·�� */
#define PATH_NUMBER         "..\\image\\number.png"

/* ���ڴ�С */
#define WINDOW_WIDTH    400     // ���ڿ��
#define WINDOW_HEIGHT   500  // ���ڸ߶�

/* ����ͼƬλ�� */
#define BACKGROUND_PIC_W   WINDOW_WIDTH
#define BACKGROUND_PIC_H   500
#define BACKGROUND_PIC_X   0
#define BACKGROUND_PIC_Y   0

/* ����λ����Ϣ */
#define SPRITE_W 145            // ������
#define SPRITE_H 130            // ����߶�
#define SPRITE_1_X 35          // ����1��X����
#define SPRITE_1_Y 110         // ����1��Y����
#define SPRITE_2_X 155
#define SPRITE_2_Y SPRITE_1_Y
#define SPRITE_3_X 275
#define SPRITE_3_Y SPRITE_1_Y
#define SPRITE_4_X SPRITE_1_X
#define SPRITE_4_Y 205
#define SPRITE_5_X SPRITE_2_X
#define SPRITE_5_Y SPRITE_4_Y
#define SPRITE_6_X SPRITE_3_X
#define SPRITE_6_Y SPRITE_4_Y
#define SPRITE_7_X SPRITE_1_X
#define SPRITE_7_Y 285
#define SPRITE_8_X SPRITE_2_X
#define SPRITE_8_Y SPRITE_7_Y
#define SPRITE_9_X SPRITE_3_X
#define SPRITE_9_Y SPRITE_7_Y



/* ����ÿλ���ִ�С������λ�� */
#define NUMBER_DST_Y    10
#define NUMBER_DST_W    32
#define NUMBER_DST_H    40

#define NUMBER_SRC_Y    0
#define NUMBER_SRC_W    40
#define NUMBER_SRC_H    50


/* ����ÿ��״̬����֡�� */
#define FRAMENUMBER_UP 8        // ����״̬֡��
#define FRAMENUMBER_WAIT 30     // �ȴ�״̬֡��
#define FRAMENUMBER_DOWN 8      // �½�״̬֡��
#define FRAMENUMBER_BEAT 8      // ����״̬֡��

class Picture
{
public:
    SDL_Texture * pPic; // ͼƬ����ָ��
    SDL_Rect srcRect;   // Դ����
    SDL_Rect dstRect;   // Ŀ������
};

/* ���������ö�� */
typedef enum spriteType
{
    TypeEmpty = 0,      // ������
    TypeNormal1,         // ��ͨ����1
    TypeNormal2,         // ��ͨ����2
    TypeNormal3,         // ��ͨ����3
    TypeNormal4,         // ��ͨ����4
    TypeNormal5,         // ��ͨ����5
} SpriteType;

/* �����״̬ö�� */
typedef enum spriteState
{
    StateEmpty = 0,     // ��״̬
    StateWait,          // �ȴ�״̬
    StateUp,            // ����״̬
    StateDown,          // �½�״̬
    StateBeat           // ����״̬
} SpriteState;


class Sprite
{
public:
    SpriteType type;    // ��������
    SpriteState state;  // ����״̬
    SDL_Rect initRect;  // ������ʾ����
    int runningTimes;   // ����ʱ�����
};

#endif 



