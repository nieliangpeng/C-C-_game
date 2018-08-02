#ifndef _DATA_H_
#define _DATA_H_

#include "SDL.h"
#include <iostream>
#include "SDL_image.h"
using namespace std;

/* 图片本地路径 */
#define PATH_BACKGROUND "..\\image\\background.png" // 背景图片

/* 被打前地鼠图片本地路径 */
#define PATH_SPRITE_NORMAL_1  "..\\image\\mouse1.png"   // 普通地鼠1
#define PATH_SPRITE_NORMAL_2    "..\\image\\mouse3.png"      // 普通地鼠2
#define PATH_SPRITE_NORMAL_3 "..\\image\\mouse5.png"  // 普通地鼠3
#define PATH_SPRITE_NORMAL_4     "..\\image\\mouse7.png"     // 普通地鼠4
#define PATH_SPRITE_NORMAL_5  "..\\image\\mouse9.png"   // 普通地鼠5

/* 被打地鼠图片本地路径 */
#define PATH_SPRITE_BEAT_1 "..\\image\\mouse2.png"
#define PATH_SPRITE_BEAT_2 "..\\image\\mouse4.png"
#define PATH_SPRITE_BEAT_3 "..\\image\\mouse6.png"
#define PATH_SPRITE_BEAT_4 "..\\image\\mouse8.png"
#define PATH_SPRITE_BEAT_5 "..\\image\\mouse10.png"

/* 数字图片本地路径 */
#define PATH_NUMBER         "..\\image\\number.png"

/* 窗口大小 */
#define WINDOW_WIDTH    400     // 窗口宽度
#define WINDOW_HEIGHT   500  // 窗口高度

/* 背景图片位置 */
#define BACKGROUND_PIC_W   WINDOW_WIDTH
#define BACKGROUND_PIC_H   500
#define BACKGROUND_PIC_X   0
#define BACKGROUND_PIC_Y   0

/* 精灵位置信息 */
#define SPRITE_W 145            // 精灵宽度
#define SPRITE_H 130            // 精灵高度
#define SPRITE_1_X 35          // 精灵1的X坐标
#define SPRITE_1_Y 110         // 精灵1的Y坐标
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



/* 分数每位数字大小及数字位置 */
#define NUMBER_DST_Y    10
#define NUMBER_DST_W    32
#define NUMBER_DST_H    40

#define NUMBER_SRC_Y    0
#define NUMBER_SRC_W    40
#define NUMBER_SRC_H    50


/* 精灵每种状态持续帧数 */
#define FRAMENUMBER_UP 8        // 上升状态帧数
#define FRAMENUMBER_WAIT 30     // 等待状态帧数
#define FRAMENUMBER_DOWN 8      // 下降状态帧数
#define FRAMENUMBER_BEAT 8      // 被打状态帧数

class Picture
{
public:
    SDL_Texture * pPic; // 图片纹理指针
    SDL_Rect srcRect;   // 源区域
    SDL_Rect dstRect;   // 目标区域
};

/* 精灵的类型枚举 */
typedef enum spriteType
{
    TypeEmpty = 0,      // 无类型
    TypeNormal1,         // 普通地鼠1
    TypeNormal2,         // 普通地鼠2
    TypeNormal3,         // 普通地鼠3
    TypeNormal4,         // 普通地鼠4
    TypeNormal5,         // 普通地鼠5
} SpriteType;

/* 精灵的状态枚举 */
typedef enum spriteState
{
    StateEmpty = 0,     // 无状态
    StateWait,          // 等待状态
    StateUp,            // 上升状态
    StateDown,          // 下降状态
    StateBeat           // 被打状态
} SpriteState;


class Sprite
{
public:
    SpriteType type;    // 精灵类型
    SpriteState state;  // 精灵状态
    SDL_Rect initRect;  // 精灵显示区域
    int runningTimes;   // 持续时间计数
};

#endif 



