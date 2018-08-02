#include "logic.h"

#include <stdlib.h>
#include <time.h>

Sprite g_spriteArr[9];      // 精灵数组
int g_nInkTimes = 0;        // 墨水计时器
int g_nScore = 0;           // 分数

//======================================================
// 函数：void init(void)
// 作用：游戏初始化
//======================================================
int init(void)
{
    // 初始化SDL库
    if(initSDL() != 0)
    {
        return -1;
    }

    // 加载图片资源
    if(loadPicResources() != 0)
    {
        return -2;
    }

    // 初始化精灵数组
    initSprite();

    return 0;
}

//======================================================
// 函数：void gameFree(void)
// 作用：游戏资源释放
//======================================================
void gameFree(void)
{
    // 释放图片
    freePicResources();

    // 退出SDL库，释放窗口、渲染器
    freeSDL();
}

//======================================================
// 函数：Uint32 timerFun(Uint32 interval, void * param)
// 作用：定时器响应函数
//======================================================
Uint32 timerFun(Uint32 interval, void * param)
{
    static int nTime = 0;
    nTime++;
    if(nTime == 3)
    {
        int i = 0;
        nTime = 0;
        srand((unsigned int)time(0));

        while(i++ != 9)
        {
            int nSprite = rand()%9;
            int nType = rand()%5;
            if(g_spriteArr[nSprite].type == TypeEmpty)           
            {
                if(nType == 0)      // 炸弹
                {
                    g_spriteArr[nSprite].type = TypeBomb;
                }
                else if(nType == 1) // 章鱼
                {
                    g_spriteArr[nSprite].type = TypeOctopus;
                }
                else                // 普通
                {
                    g_spriteArr[nSprite].type = TypeNormal;
                }
                // 设置状态为上升状态
                g_spriteArr[nSprite].state = StateUp;
                break;
            }
        }
    }

    // 绘制窗口
    paint();

    // 精灵运动
    spriteRun();

    return interval;
}

//======================================================
// 函数：void logicStart(void)
// 作用：游戏开始（添加定时器，以及事件循环）
//======================================================
void start(void)
{
    SDL_Event event;    // 事件类型变量
    int nQuit = 0;      // 退出标识,0循环,非0退出循环

    // 添加定时器函数
    SDL_AddTimer(85, timerFun, NULL);

    // 从消息队列中循环取得事件
    while(nQuit == 0)   // 判断是否退出事件循环
    {
        while(SDL_PollEvent(&event))    // 获取事件
        {
            switch(event.type)  // 事件的类别
            {
            case SDL_QUIT:      // 退出事件
                nQuit = 1; // 用户激活退出事件,跳出循环
                break;
            case SDL_MOUSEBUTTONDOWN:   // 鼠标点击事件
                mouseButtonEvent(&event);
                break;
            default:
                break;
            }
        }
    }
}

//======================================================
// 函数：void initSprite(void)
// 作用：初始化精灵
//======================================================
void initSprite(void)
{
    int i;
    for(i=0; i<9; i++)
    {
        g_spriteArr[i].type = TypeEmpty;
        g_spriteArr[i].state = StateEmpty;
        g_spriteArr[i].initRect.w = SPRITE_W;
        g_spriteArr[i].initRect.h = SPRITE_H;
        g_spriteArr[i].runningTimes = 0;

        switch(i)
        {
        case 0:
            g_spriteArr[i].initRect.x = SPRITE_1_X;
            g_spriteArr[i].initRect.y = SPRITE_1_Y;
            break;
        case 1:
            g_spriteArr[i].initRect.x = SPRITE_2_X;
            g_spriteArr[i].initRect.y = SPRITE_2_Y;
            break;
        case 2:
            g_spriteArr[i].initRect.x = SPRITE_3_X;
            g_spriteArr[i].initRect.y = SPRITE_3_Y;
            break;
        case 3:
            g_spriteArr[i].initRect.x = SPRITE_4_X;
            g_spriteArr[i].initRect.y = SPRITE_4_Y;
            break;
        case 4:
            g_spriteArr[i].initRect.x = SPRITE_5_X;
            g_spriteArr[i].initRect.y = SPRITE_5_Y;
            break;
        case 5:
            g_spriteArr[i].initRect.x = SPRITE_6_X;
            g_spriteArr[i].initRect.y = SPRITE_6_Y;
            break;
        case 6:
            g_spriteArr[i].initRect.x = SPRITE_7_X;
            g_spriteArr[i].initRect.y = SPRITE_7_Y;
            break;
        case 7:
            g_spriteArr[i].initRect.x = SPRITE_8_X;
            g_spriteArr[i].initRect.y = SPRITE_8_Y;
            break;
        case 8:
            g_spriteArr[i].initRect.x = SPRITE_9_X;
            g_spriteArr[i].initRect.y = SPRITE_9_Y;
            break;
        }
    }
}

//======================================================
// 函数：void spriteRun(void)
// 作用：精灵运动
//======================================================
void spriteRun(void)
{
    int i;
    // 循环遍历九个精灵
    for(i=0; i<9; i++)  
    {
        // 空类型返回
        if(g_spriteArr[i].type == TypeEmpty)
        {
            continue;
        }

        // 状态计数器++
        g_spriteArr[i].runningTimes++;

        if(g_spriteArr[i].state == StateUp)         // 上升状态
        {
            if(g_spriteArr[i].runningTimes == FRAMENUMBER_UP)
            {
                // 帧数达到上升的最大帧数，状态变为等待
                g_spriteArr[i].runningTimes = 0;
                g_spriteArr[i].state = StateWait;
            }
        }
        else if(g_spriteArr[i].state == StateWait)  // 等待状态
        {
            if(g_spriteArr[i].runningTimes == FRAMENUMBER_WAIT)
            {
                // 帧数达到等待的最大帧数，状态变为下降
                g_spriteArr[i].runningTimes = 0;
                g_spriteArr[i].state = StateDown;
            }
        }
        else if(g_spriteArr[i].state == StateDown)  // 下降状态
        {
            if(g_spriteArr[i].runningTimes == FRAMENUMBER_DOWN)
            {
                // 帧数达到下降的最大帧数，状态类型计数器都置零
                g_spriteArr[i].runningTimes = 0;
                g_spriteArr[i].state = StateEmpty;
                g_spriteArr[i].type = TypeEmpty;
            }
        }
        else                                        // 被打状态
        {
            if(g_spriteArr[i].runningTimes == FRAMENUMBER_BEAT)
            {
                // 帧数达到被打的最大帧数，状态类型计数器都置零
                g_spriteArr[i].runningTimes = 0;
                g_spriteArr[i].state = StateEmpty;
                g_spriteArr[i].type = TypeEmpty;
            }
        }
    }
}

//======================================================
// 函数：void mouseButtonEvent(const SDL_Event * pEvent)
// 作用：处理鼠标点击事件
// 参数：事件类型指针
//======================================================
void mouseButtonEvent(const SDL_Event * pEvent)
{
    int i;

    if(pEvent->button.button != SDL_BUTTON_LEFT
        || pEvent->button.type != SDL_MOUSEBUTTONDOWN)
    {
        return;
    }

    for(i=0; i<9; i++)
    {
        if((pEvent->button.x >= g_spriteArr[i].initRect.x)
            && (pEvent->button.x <= g_spriteArr[i].initRect.x 
                                    + g_spriteArr[i].initRect.w)
            && (pEvent->button.y >= g_spriteArr[i].initRect.y)
            && (pEvent->button.y <= g_spriteArr[i].initRect.y 
                                    + g_spriteArr[i].initRect.h))
        {
            if(g_spriteArr[i].state == StateWait)
            {
                g_spriteArr[i].state = StateBeat;
                g_spriteArr[i].runningTimes = 0;
                if(g_spriteArr[i].type == TypeOctopus)
                {
                    g_nInkTimes = 1;
                }
                // 更新分数
                updateScore(g_spriteArr[i].type);
            }
        }
    }
}

//======================================================
// 函数：void updateScore(SpriteType type)
// 作用：更新分数
// 参数：type 被打精灵类型
//======================================================
void updateScore(SpriteType type)
{
    if(type == TypeNormal)
    {
        g_nScore += 2;
    }
    else if(type == TypeBomb)
    {
        g_nScore -= 3;
    }

    if(g_nScore < 0)
    {
        g_nScore = 0;
    }
}