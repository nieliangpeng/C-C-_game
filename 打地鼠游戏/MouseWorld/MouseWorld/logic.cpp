#include "logic.h"
#include <stdlib.h>
#include<time.h>
Sprite g_spriteArr[9];//地鼠数组
int g_nScore=0;


// 游戏初始化
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


// 游戏资源释放
void gameFree(void)
{
    // 释放图片
    freePicResources();

    // 退出SDL库，释放窗口、渲染器
    freeSDL();
}


// 定时器响应函数
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
            int nType = rand()%7;
            if(g_spriteArr[nSprite].type == TypeEmpty)
            {
                if(nType == 0)      
                {
                    g_spriteArr[nSprite].type = TypeNormal1;
                }
                else if(nType == 1) 
                {
                    g_spriteArr[nSprite].type = TypeNormal2;
                }
                 else if(nType == 2) 
                {
                    g_spriteArr[nSprite].type = TypeNormal3;
                }
                 else if(nType == 3) 
                {
                    g_spriteArr[nSprite].type = TypeNormal4;
                }
                else                
                {
                    g_spriteArr[nSprite].type = TypeNormal5;
                }
                // 设置状态为上升状态
                g_spriteArr[nSprite].state = StateUp;
                break;
            }
        }
    }
    // 绘制窗口
    paint();
    // 运动
    spriteRun();
    return interval;
}


// 游戏开始（添加定时器，以及事件循环）
void start(void)
{
    SDL_Event event;    
    int nQuit = 0;      // 退出标识,0循环,非0退出循环

    // 添加定时器函数
    /*SDL_TimerID SDL_AddTimer(Uint32 interval,SDL_TimerCallback callback,void* param)*/
    SDL_AddTimer(75, timerFun, NULL);

    while(nQuit == 0)  
    {
        while(SDL_PollEvent(&event))   
        {
            switch(event.type) 
            {
            case SDL_QUIT:     
                nQuit = 1; 
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseButtonEvent(&event);
                break;
            default:
                break;
            }
        }
    }
}


// 作用：初始化地鼠
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

// 作用：精灵运动
void spriteRun(void)
{
    int i;
    // 循环遍历九个地鼠
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
                
                g_spriteArr[i].runningTimes = 0;
                g_spriteArr[i].state = StateWait;
            }
        }
        else if(g_spriteArr[i].state == StateWait)  // 等待状态
        {
            if(g_spriteArr[i].runningTimes == FRAMENUMBER_WAIT)
            {
               
                g_spriteArr[i].runningTimes = 0;
                g_spriteArr[i].state = StateDown;
            }
        }
        else if(g_spriteArr[i].state == StateDown)  // 下降状态
        {
            if(g_spriteArr[i].runningTimes == FRAMENUMBER_DOWN)
            {
               
                g_spriteArr[i].runningTimes = 0;
                g_spriteArr[i].state = StateEmpty;
                g_spriteArr[i].type = TypeEmpty;
            }
        }
        else                                        // 被打状态
        {
            if(g_spriteArr[i].runningTimes == FRAMENUMBER_BEAT)
            {
               
                g_spriteArr[i].runningTimes = 0;
                g_spriteArr[i].state = StateEmpty;
                g_spriteArr[i].type = TypeEmpty;
            }
        }
    }
}


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
                updateScore(g_spriteArr[i].type);
               
            }
        }
    }
}

// 作用：更新分数
void updateScore(SpriteType type)
{
    if(type == TypeNormal1)
    {
        g_nScore += 2;
    }
    if(type == TypeNormal2)
    {
        g_nScore += 2;
    }
    if(type == TypeNormal3)
    {
        g_nScore += 2;
    }
    if(type == TypeNormal4)
    {
        g_nScore += 2;
    }
    if(type == TypeNormal5)
    {
        g_nScore += 2;
    }

    
}