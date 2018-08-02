#ifndef _DATA_H_
#define _DATA_H_

/* 程序中用到的外部头文件 */
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"

/* 图片本地路径 */
#define PATH_BACKGROUND_1 "..\\image\\background_1.png" // 背景图片1
#define PATH_BACKGROUND_2 "..\\image\\background_2.png" // 背景图片2
#define PATH_BACKGROUND_3 "..\\image\\background_3.png" // 背景图片3
#define PATH_BACKGROUND_4 "..\\image\\background_4.png" // 背景图片4

/* 精灵图片本地路径 */
#define PATH_SPRITE_NORMAL  "..\\image\\spriteNormal.png"   // 普通地鼠
#define PATH_SPRITE_BOMB    "..\\image\\spriteBomb.png"     // 炸弹地鼠
#define PATH_SPRITE_OCTOPUS "..\\image\\spriteOctopus.png"  // 普通章鱼
#define PATH_SPRITE_BEAT    "..\\image\\spriteBeat.png"     // 被打地鼠
#define PATH_SPRITE_OCTBEAT "..\\image\\spriteOctBeat.png"  // 被打章鱼

/* 炸弹效果图片本地路径 */
#define PATH_SPRITE_BLAST_1 "..\\image\\spriteBlast_1.png"
#define PATH_SPRITE_BLAST_2 "..\\image\\spriteBlast_2.png"

/* 墨水图片本地路径 */
#define PATH_SPRITE_INK     "..\\image\\spriteInk.png"

/* 数字图片本地路径 */
#define PATH_NUMBER         "..\\image\\number.png"

/* 窗口大小 */
#define WINDOW_WIDTH    360     // 窗口宽度
#define WINDOW_HEIGHT   507     // 窗口高度

/* 背景图片1位置 */
#define BACKGROUND_PIC1_W   WINDOW_WIDTH
#define BACKGROUND_PIC1_H   222
#define BACKGROUND_PIC1_X   0
#define BACKGROUND_PIC1_Y   0

/* 背景图片2位置 */
#define BACKGROUND_PIC2_W   WINDOW_WIDTH
#define BACKGROUND_PIC2_H   117
#define BACKGROUND_PIC2_X   0
#define BACKGROUND_PIC2_Y   202

/* 背景图片3位置 */
#define BACKGROUND_PIC3_W   WINDOW_WIDTH
#define BACKGROUND_PIC3_H   120
#define BACKGROUND_PIC3_X   0
#define BACKGROUND_PIC3_Y   298

/* 背景图片4位置 */
#define BACKGROUND_PIC4_W   WINDOW_WIDTH
#define BACKGROUND_PIC4_H   109
#define BACKGROUND_PIC4_X   0
#define BACKGROUND_PIC4_Y   398

/* 精灵位置信息 */
#define SPRITE_W 155            // 精灵宽度
#define SPRITE_H 135            // 精灵高度
#define SPRITE_1_X -15          // 精灵1的X坐标
#define SPRITE_1_Y 105          // 精灵1的Y坐标
#define SPRITE_2_X 105
#define SPRITE_2_Y SPRITE_1_Y
#define SPRITE_3_X 225
#define SPRITE_3_Y SPRITE_1_Y
#define SPRITE_4_X SPRITE_1_X
#define SPRITE_4_Y 200
#define SPRITE_5_X SPRITE_2_X
#define SPRITE_5_Y SPRITE_4_Y
#define SPRITE_6_X SPRITE_3_X
#define SPRITE_6_Y SPRITE_4_Y
#define SPRITE_7_X SPRITE_1_X
#define SPRITE_7_Y 300
#define SPRITE_8_X SPRITE_2_X
#define SPRITE_8_Y SPRITE_7_Y
#define SPRITE_9_X SPRITE_3_X
#define SPRITE_9_Y SPRITE_7_Y

/* 墨水位置 */
#define INK_X   -5
#define INK_Y   80
#define INK_W   380
#define INK_H   400

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
#define FRAMENUMBER_INK 60      // 墨水持续帧数

/* 图片类型结构体 */
typedef struct picture
{
    SDL_Texture * pPic; // 图片纹理指针
    SDL_Rect srcRect;   // 源区域
    SDL_Rect dstRect;   // 目标区域
} Picture;

/* 精灵的类型枚举 */
typedef enum spriteType
{
    TypeEmpty = 0,      // 无类型
    TypeNormal,         // 普通地鼠
    TypeBomb,           // 炸弹地鼠
    TypeOctopus         // 章鱼
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

/* 精灵结构体 */
typedef struct sprite
{
    SpriteType type;    // 精灵类型
    SpriteState state;  // 精灵状态
    SDL_Rect initRect;  // 精灵显示区域
    int runningTimes;   // 持续时间计数
} Sprite;

#endif  // _DATA_H_



