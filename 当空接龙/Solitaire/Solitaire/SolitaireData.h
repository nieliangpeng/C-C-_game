#ifndef _SOLITAIRE_DATA_H_
#define _SOLITAIRE_DATA_H_

#include "SDL.h"
#include "SDL_image.h"

#define WINDOW_WIDTH    1000    // 窗口宽度
#define WINDOW_HEIGHT   600     // 窗口高度
#define POKER_WIDTH     85      // 扑克宽度
#define POKER_HEIGHT    120     // 扑克高度
#define POKER_SPACE     20      // 普通单元中扑克Y轴间距
#define UNIT_SPACE      30      // 单元X间间距
#define DEAL_POINT_X    (WINDOW_WIDTH-POKER_WIDTH)/2    // 发牌位置X坐标
#define DEAL_POINT_Y    (WINDOW_HEIGHT-POKER_HEIGHT-30) // 发牌位置Y坐标

typedef struct unit Unit;

/** 扑克卡牌卡色 **/
typedef enum pokerColor
{
    Heart = 0,          // 红桃
    Spade,              // 黑桃
    Diamond,            // 方块
    Club                // 梅花
} PokerColor;

/** 扑克卡牌坐标及长宽 **/
typedef struct pokerRect
{
    int x;              // x坐标
    int y;              // y坐标
    unsigned int width; // 宽度
    unsigned int height;// 高度
} PokerRect;

/** 扑克卡牌 **/
typedef struct poker
{
    unsigned int nNum;  // 卡牌数字
    PokerColor color;   // 卡牌卡色
    PokerRect rect;     // 卡牌
    Unit * pUnit;       // 扑克牌所属单元
} Poker;

/** 所选扑克牌结构体 **/
typedef struct selectPoker
{
    unsigned int nCount;    // 当前选择的扑克数量
    Poker * arrPoker[13];   // 当前选择的扑克数组
} SelectPoker;

/** 单元类型 **/
typedef enum unitType
{
    NormalUnit = 0,     // 正常单元
    UseUnit,            // 可用单元
    RetrieveUnit        // 回收单元
} UnitType;

/** 单元 **/
typedef struct unit
{
    UnitType type;          // 单元类型
    Poker * arrPoker[19];   // 扑克牌数组
    unsigned int nCurCount; // 当前扑克牌数
    int nX;                 // 单元X坐标
    int nY;                 // 单元Y坐标
} Unit;

#endif // _SOLITAIRE_DATA_H_