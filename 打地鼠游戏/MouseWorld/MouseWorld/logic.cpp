#include "logic.h"
#include <stdlib.h>
#include<time.h>
Sprite g_spriteArr[9];//��������
int g_nScore=0;


// ��Ϸ��ʼ��
int init(void)
{
    // ��ʼ��SDL��
    if(initSDL() != 0)
    {
        return -1;
    }

    // ����ͼƬ��Դ
    if(loadPicResources() != 0)
    {
        return -2;
    }

   
     // ��ʼ����������
    initSprite();
    return 0;
}


// ��Ϸ��Դ�ͷ�
void gameFree(void)
{
    // �ͷ�ͼƬ
    freePicResources();

    // �˳�SDL�⣬�ͷŴ��ڡ���Ⱦ��
    freeSDL();
}


// ��ʱ����Ӧ����
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
                // ����״̬Ϊ����״̬
                g_spriteArr[nSprite].state = StateUp;
                break;
            }
        }
    }
    // ���ƴ���
    paint();
    // �˶�
    spriteRun();
    return interval;
}


// ��Ϸ��ʼ����Ӷ�ʱ�����Լ��¼�ѭ����
void start(void)
{
    SDL_Event event;    
    int nQuit = 0;      // �˳���ʶ,0ѭ��,��0�˳�ѭ��

    // ��Ӷ�ʱ������
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


// ���ã���ʼ������
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

// ���ã������˶�
void spriteRun(void)
{
    int i;
    // ѭ�������Ÿ�����
    for(i=0; i<9; i++)  
    {
        // �����ͷ���
        if(g_spriteArr[i].type == TypeEmpty)
        {
            continue;
        }

        // ״̬������++
        g_spriteArr[i].runningTimes++;

        if(g_spriteArr[i].state == StateUp)         // ����״̬
        {
            if(g_spriteArr[i].runningTimes == FRAMENUMBER_UP)
            {
                
                g_spriteArr[i].runningTimes = 0;
                g_spriteArr[i].state = StateWait;
            }
        }
        else if(g_spriteArr[i].state == StateWait)  // �ȴ�״̬
        {
            if(g_spriteArr[i].runningTimes == FRAMENUMBER_WAIT)
            {
               
                g_spriteArr[i].runningTimes = 0;
                g_spriteArr[i].state = StateDown;
            }
        }
        else if(g_spriteArr[i].state == StateDown)  // �½�״̬
        {
            if(g_spriteArr[i].runningTimes == FRAMENUMBER_DOWN)
            {
               
                g_spriteArr[i].runningTimes = 0;
                g_spriteArr[i].state = StateEmpty;
                g_spriteArr[i].type = TypeEmpty;
            }
        }
        else                                        // ����״̬
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

// ���ã����·���
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