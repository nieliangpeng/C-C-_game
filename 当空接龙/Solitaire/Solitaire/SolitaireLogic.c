/***************************************************
*  文件：SolitaireLogic.c
*  说明：游戏逻辑相关处理
*  作者：
*  日期：
***************************************************/


#include "SolitaireInterface.h"
#include "SolitaireLogic.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

Unit g_arrNormalUnit[8];
Unit g_arrUseUnit[4];
Unit g_arrRetrieveUnit[4];
Poker g_arrPoker[52];

int g_nIsButtonDownLeft = 0;        // 鼠标左键是否处于按下状态
SelectPoker g_selectPoker = {0, 0}; // 当前鼠标选择的扑克牌

int g_nMouseX = 0;
int g_nMouseY = 0;
int g_nMouseOffsetX = 0;
int g_nMouseOffsetY = 0;

/** 游戏初始化 **/
int logicInit(void)
{
    int i = 0;

    /* 初始化普通单元 */
    for(i=0; i<8; ++i)
    {
        g_arrNormalUnit[i].type = NormalUnit;
        g_arrNormalUnit[i].nCurCount = 0;
        g_arrNormalUnit[i].nX = (WINDOW_WIDTH-8*POKER_WIDTH-7*(UNIT_SPACE-10))/2 
            + i*(POKER_WIDTH+UNIT_SPACE-10);
        g_arrNormalUnit[i].nY = 200;
    }
    /* 初始化可用单元 */
    for(i=0; i<4; ++i)
    {
        g_arrUseUnit[i].type = UseUnit;
        g_arrUseUnit[i].nCurCount = 0;
        g_arrUseUnit[i].nX = (WINDOW_WIDTH-8*POKER_WIDTH-6*UNIT_SPACE-80)/2 
            + i*(POKER_WIDTH+UNIT_SPACE);
        g_arrUseUnit[i].nY = 30;
    }
    /* 初始化回收单元 */
    for(i=0; i<4; ++i)
    {
        g_arrRetrieveUnit[i].type = RetrieveUnit;
        g_arrRetrieveUnit[i].nCurCount = 0;
        g_arrRetrieveUnit[i].nX = (WINDOW_WIDTH-8*POKER_WIDTH-6*UNIT_SPACE-80)/2 
            + 4*POKER_WIDTH + 3*UNIT_SPACE + 80 
            + i*(POKER_WIDTH+UNIT_SPACE);
        g_arrRetrieveUnit[i].nY = 30;
    }

    /* 初始化扑克牌数组 */
    for(i=0; i<52; ++i)
    {
        PokerRect rect;
        rect.width = POKER_WIDTH;
        rect.height = POKER_HEIGHT;
        rect.x = 0;
        rect.y = 0;

        g_arrPoker[i].rect = rect;
        g_arrPoker[i].nNum = i%13 + 1;

        if(0 == i/13)
        {
            g_arrPoker[i].color = Heart;
        }
        else if(1 == i/13)
        {
            g_arrPoker[i].color = Spade;
        }
        else if(2 == i/13)
        {
            g_arrPoker[i].color = Diamond;
        }
        else if(3 == i/13)
        {
            g_arrPoker[i].color = Club;
        }
    }

    /* 初始化游戏窗口 */
    interfaceInit();

    return 0;
}

/** 游戏发牌 **/
void logicDeal(void)
{
    int i = 0;          // 循环变量
    int nRandom = 0;    // 随机数变量
    int arrPokeUsed[52] = {0};  // 记录扑克牌是否已发


    /* 添加一个随机数种子 */
    srand((unsigned int)time(0));

    for(i=0; i<52; ++i)
    {
        /* 在0-51之间取随机数 */
        nRandom = rand()%52;
        /* 如果随机牌为已发牌，则继续循环 */
        if(arrPokeUsed[nRandom] != 0)
        {
            --i;
            continue;
        }
        
        /* 往普通单元添加扑克 */
        logicUnitDealPoker(&g_arrNormalUnit[i%8], &g_arrPoker[nRandom]);
        /* 记录扑克牌所属单元 */
        g_arrPoker[nRandom].pUnit = &g_arrNormalUnit[i%8];
        
        /* 记录已经分发的扑克牌 */
        arrPokeUsed[nRandom] = 1;
    }

    /* 发完牌对窗口进行刷新打印 */
    interfacePaint(1);

    return;
}

/** 往普通单元添加扑克 **/
void logicUnitDealPoker(Unit * pUnit, Poker * pPoker)
{
    int nCurCount = pUnit->nCurCount;

    pPoker->rect.x = pUnit->nX;
    pPoker->rect.y = pUnit->nY + nCurCount * POKER_SPACE;

    /* 动画移动扑克 */
    interfacePokerMove(DEAL_POINT_X, DEAL_POINT_Y, 
        pPoker->rect.x, pPoker->rect.y, 
        pPoker, 3, 1);

    pUnit->arrPoker[nCurCount] = pPoker;
    pUnit->nCurCount += 1;
}

/** 游戏开始 **/
void logicStart(void)
{
    /* 事件变量 */
    SDL_Event event;
    /* 是否退出游戏 */
    int nQuit = -1;

    /* 发牌 */
    logicDeal();

    /* 循环处理事件 */
    while(nQuit == -1)
    {
        /* 从消息队列中取得事件 */
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                {
                    /* 用户关闭窗口，游戏结束 */
                    nQuit = 1;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                {
                    /* 处理鼠标点击事件 */
                    logicMouseButtonEvent(&event);
                }
                break;
            case SDL_MOUSEMOTION:
                {
                    /* 处理鼠标移动事件 */
                    logicMouseMotionEvent(&event);
                }
                break;
            default:
                break;
            }

            /* 重新绘制窗口 */
            interfacePaint(1);
        }
    }
    return;
}

/** 游戏结束 **/
void logicEnd(void)
{
    /* 释放SDL */
    interfaceDestroy();

    return;
}

/** 处理鼠标点击事件 **/
void logicMouseButtonEvent(const SDL_Event * pEvent)
{
    Poker * pCurPoker = NULL;
    SDL_MouseButtonEvent buttonEvent = pEvent->button;

    /* 鼠标左键点击事件 */
    if(buttonEvent.button == SDL_BUTTON_LEFT)
    {
        /* 左键按下 */
        if(buttonEvent.type == SDL_MOUSEBUTTONDOWN)
        {
            /* 获取鼠标左键点击的扑克牌 */
            pCurPoker = logicIsPoker(buttonEvent.x, buttonEvent.y);
            
            /* 没有点击扑克牌 */
            if(NULL == pCurPoker)
            {
                Unit * pUnit = logicIsUnit(buttonEvent.x, buttonEvent.y);
                if(pUnit != NULL && g_selectPoker.nCount != 0)
                {
                    logicTryMovingThePokers(pUnit, 1);
                    memset(g_selectPoker.arrPoker, 0, 13*sizeof(Poker *));
                    g_selectPoker.nCount = 0;
                }
                return;
            }
            /* 点击已选中的扑克牌 */
            else if(g_selectPoker.arrPoker[0] == pCurPoker)
            {
                memset(g_selectPoker.arrPoker, 0, 13*sizeof(Poker *));
                g_selectPoker.nCount = 0;
            }
            /* 点击其他扑克怕 */
            else
            {
                /* 点击前已选中其他扑克牌 */
                if(g_selectPoker.nCount != 0)
                {
                    /* 尝试移动已选中牌组 */
                    logicTryMovingThePokers(pCurPoker->pUnit, 1);
                    memset(g_selectPoker.arrPoker, 0, 13*sizeof(Poker *));
                    g_selectPoker.nCount = 0;
                }
                /* 点击前没有选中其他扑克牌 */
                else
                {
                    /* 记录鼠标左键点击状态 */
                    g_nIsButtonDownLeft = 1;
                    g_nMouseOffsetX = pEvent->button.x - pCurPoker->rect.x;
                    g_nMouseOffsetY = pEvent->button.y - pCurPoker->rect.y;
                    g_nMouseX = pEvent->button.x;
                    g_nMouseY = pEvent->button.y;
                    /* 尝试将点击牌组选为选中状态 */
                    logicGetSelectPokers(pCurPoker);
                }
            }
        }
        /* 左键释放 */
        else if(buttonEvent.type == SDL_MOUSEBUTTONUP)
        {
            g_nIsButtonDownLeft = 0;
            if(0 == g_selectPoker.nCount)
            {
                return;
            }

            /* 获取鼠标左键点击的扑克牌 */
            pCurPoker = logicIsPoker(buttonEvent.x, buttonEvent.y);
            
            /* 没有在扑克牌上弹起 */
            if(NULL == pCurPoker)
            {
                Unit * pUnit = logicIsUnit(buttonEvent.x, buttonEvent.y);
                if(pUnit != NULL && g_selectPoker.nCount != 0)
                {
                    logicTryMovingThePokers(pUnit, 0);
                    memset(g_selectPoker.arrPoker, 0, 13*sizeof(Poker *));
                    g_selectPoker.nCount = 0;
                }
                return;
            }
            /* 在已选中的扑克牌上弹起 */
            else if(g_selectPoker.arrPoker[0]->pUnit == pCurPoker->pUnit)
            {
                return;
            }
            /* 在其他扑克怕上弹起 */
            else
            {
                /* 尝试移动已选中牌组 */
                logicTryMovingThePokers(pCurPoker->pUnit, 0);
                memset(g_selectPoker.arrPoker, 0, 13*sizeof(Poker *));
                g_selectPoker.nCount = 0;
            }
        }
    }
    /* 鼠标右键点击事件 */
    else if(buttonEvent.button == SDL_BUTTON_RIGHT)
    {
        int i = 0, j = 0;   // 循环变量
        int nRtn = 0;       // 记录返回值变量
        int nUnitPokerCount = 0;

        while(1)
        {
            nRtn = 0;

            for(i=0; i<4; ++i)
            {
                if(1 == g_arrUseUnit[i].nCurCount)
                {
                    for(j=0; j<4 && 0==nRtn; ++j)
                    {
                        /* 清空选中扑克牌 */
                        memset(g_selectPoker.arrPoker, 0, 13*sizeof(Poker *));
                        g_selectPoker.nCount = 0;
                        /* 将单元中的扑克牌选中 */
                        g_selectPoker.arrPoker[0] = g_arrUseUnit[i].arrPoker[0];
                        g_selectPoker.nCount = 1;
                        /* 尝试移动扑克牌到回收单元 */
                        nRtn = logicTryMovingThePokers(&g_arrRetrieveUnit[j], 1);
                    }
                    
                    if(1 == nRtn) 
                    {
                        break;
                    }
                }
            }

            if(1 == nRtn)
            {
                continue;
            }

            for(i=0; i<8; ++i)
            {
                nUnitPokerCount = g_arrNormalUnit[i].nCurCount;
                if(0 < nUnitPokerCount)
                {
                    for(j=0; j<4 && 0==nRtn; ++j)
                    {
                        /* 清空选中扑克牌 */
                        memset(g_selectPoker.arrPoker, 0, 13*sizeof(Poker *));
                        g_selectPoker.nCount = 0;
                        /* 将单元中的扑克牌选中 */
                        g_selectPoker.arrPoker[0] = g_arrNormalUnit[i].arrPoker[nUnitPokerCount-1];
                        g_selectPoker.nCount = 1;
                        /* 尝试移动扑克牌到回收单元 */
                        nRtn = logicTryMovingThePokers(&g_arrRetrieveUnit[j], 1);
                    }

                    if(1 == nRtn)
                    {
                        break;
                    }

                }
            }

            if(nRtn != 1)
            {
                break;
            }
        }

        memset(g_selectPoker.arrPoker, 0, 13*sizeof(Poker *));
        g_selectPoker.nCount = 0;
    }
}

/** 处理鼠标移动事件 **/
void logicMouseMotionEvent(const SDL_Event * pEvent)
{
    
    if(1 == g_nIsButtonDownLeft)
    {
        g_nMouseX = pEvent->motion.x; 
        g_nMouseY = pEvent->motion.y;
    }
}

/** 获取选中的扑克牌组  **/
void logicGetSelectPokers(Poker * pPoker)
{
    int i = 0;
    int nCount = 0;
    int nFlag = 0;

    Unit * pUnit = pPoker->pUnit;

    /* 清空之前选择的扑克牌组 */
    g_selectPoker.nCount = 0;
    memset(g_selectPoker.arrPoker, 0, 13*sizeof(Poker *));

    /* 在普通单元中查找 */
    if(pUnit->type == NormalUnit)
    {
        nCount = pUnit->nCurCount;
        for(i=0; i<nCount; ++i)
        {
            if(pUnit->arrPoker[i] == pPoker)
            {
                nFlag = 1;
                g_selectPoker.arrPoker[0] = pUnit->arrPoker[i];
                g_selectPoker.nCount++;
            }
            else if(1 == nFlag)
            {
                if((pUnit->arrPoker[i]->nNum 
                        == g_selectPoker.arrPoker[g_selectPoker.nCount-1]->nNum - 1)
                    && (pUnit->arrPoker[i]->color % 2 
                        != g_selectPoker.arrPoker[g_selectPoker.nCount-1]->color % 2))
                {
                    g_selectPoker.arrPoker[g_selectPoker.nCount] = pUnit->arrPoker[i];
                    g_selectPoker.nCount++;
                }
                else
                {
                    g_selectPoker.nCount = 0;
                    memset(g_selectPoker.arrPoker, 0, 13*sizeof(Poker *));
                    break;
                }
            }
        }
    }
    /* 在可用单元中查找 */
    else if(pUnit->type == UseUnit)
    {
        g_selectPoker.arrPoker[0] = pPoker;
        g_selectPoker.nCount = 1;
    }

    return;
}

/** 判断坐标点对应的扑克牌 **/
Poker * logicIsPoker(int nX, int nY)
{
    int i = 0;
    Poker * pPoker = NULL;

    for(i=0; i<52; ++i)
    {
        if((nX >= g_arrPoker[i].rect.x) && (nY >= g_arrPoker[i].rect.y)
            && (nX <= (g_arrPoker[i].rect.x + POKER_WIDTH))
            && (nY <= (g_arrPoker[i].rect.y + POKER_HEIGHT)))
        {
            if(pPoker != NULL)
            {
                if(pPoker->rect.y >= g_arrPoker[i].rect.y)
                {
                    continue;
                }
            }
            pPoker = &g_arrPoker[i];
        }
    }

    return pPoker;
}

/** 判断坐标点对应的单元 **/
Unit * logicIsUnit(int nX, int nY)
{
    int i = 0;
    Unit * pUnit = NULL;
    int nUnitX = 0;
    int nUnitY = 0;

    /* 坐标是否属于普通单元 */
    for(i=0; i<8; ++i)
    {
        nUnitX = g_arrNormalUnit[i].nX;
        nUnitY = g_arrNormalUnit[i].nY;

        if((nUnitX)<=nX && (nUnitY)<=nY 
            && (nUnitX+POKER_WIDTH)>=nX && (nUnitY+POKER_HEIGHT)>=nY)
        {
            return &g_arrNormalUnit[i];
        }
    }

    /* 坐标是否属于可用单元 */
    for(i=0; i<4; ++i)
    {
        nUnitX = g_arrUseUnit[i].nX;
        nUnitY = g_arrUseUnit[i].nY;

        if((nUnitX-10)<=nX && (nUnitY-10)<=nY 
            && (nUnitX+POKER_WIDTH+20)>=nX && (nUnitY+POKER_HEIGHT+20)>=nY)
        {
            return &g_arrUseUnit[i];
        }
    }

    /* 坐标是否属于回收单元 */
    for(i=0; i<4; ++i)
    {
        nUnitX = g_arrRetrieveUnit[i].nX;
        nUnitY = g_arrRetrieveUnit[i].nY;

        if((nUnitX-10)<=nX && (nUnitY-10)<=nY 
            && (nUnitX+POKER_WIDTH+20)>=nX && (nUnitY+POKER_HEIGHT+20)>=nY)
        {
            return &g_arrRetrieveUnit[i];
        }
    }

    return pUnit;
}

/** 尝试将牌组移动到某单元 **/
int logicTryMovingThePokers(Unit * pUnit, int nIsAction)
{
    int i = 0;                      // 循环变量
    int nUnitPokerCount = 0;        // 目标单元扑克牌数
    int nOldUnitCount = 0;          // 源单元扑克牌数
    int nOldX = 0, nOldY = 0;       // 源扑克牌的坐标点
    int nSelectPokerCount = 0;      // 所选的扑克牌数
    Poker * pDstPoker = NULL;       // 目标单元最下方的扑克牌
    Unit * pOldUnit = NULL;         // 源单元

    /* 获取目标单元扑克牌数 */
    nUnitPokerCount = pUnit->nCurCount;
    /* 获取目标单元最下方的扑克牌 */
    if(0 != nUnitPokerCount)
    {
        pDstPoker = pUnit->arrPoker[nUnitPokerCount - 1];
    }
    /* 获取所选的扑克牌数 */
    nSelectPokerCount = g_selectPoker.nCount;
    /* 获取源单元以及源单元的扑克牌数 */
    pOldUnit = g_selectPoker.arrPoker[0]->pUnit;
    nOldUnitCount = pOldUnit->nCurCount;


    /* 判断回收单元 */
    switch (pUnit->type)
    {
    case RetrieveUnit:
        {
            /* 所选牌数不为1则返回 */
            if(1 != nSelectPokerCount)
            {
                return 0;
            }

            /* 单元中已有扑克牌 */
            if(pDstPoker != NULL)
            {
                /* 所选扑克牌不符合规则则返回 */
                if((g_selectPoker.arrPoker[0]->color != pDstPoker->color)
                    || (g_selectPoker.arrPoker[0]->nNum != pDstPoker->nNum + 1))
                {
                    return 0;
                }
            }
            /* 单元中没有扑克牌 */
            else
            {
                /* 扑克牌数字不为1则返回 */
                if(g_selectPoker.arrPoker[0]->nNum != 1)
                {
                    return 0;
                }
            }

            /* 从扑克牌原属于单元中删除移动的扑克牌 */
            pOldUnit->nCurCount = nOldUnitCount - 1;
            pOldUnit->arrPoker[nOldUnitCount - 1] = NULL;
            /* 记录扑克牌原坐标点 */
            nOldX = g_selectPoker.arrPoker[0]->rect.x;
            nOldY = g_selectPoker.arrPoker[0]->rect.y;
            /* 修改扑克牌所属单元 */
            g_selectPoker.arrPoker[0]->pUnit = pUnit;
            g_selectPoker.arrPoker[0]->rect.x = pUnit->nX;
            g_selectPoker.arrPoker[0]->rect.y = pUnit->nY;
            if(1 == nIsAction)
            {
                /* 动画移动效果 */
                interfacePokerMove(nOldX, nOldY, pUnit->nX, pUnit->nY, 
                    g_selectPoker.arrPoker[0], 10, 0);
            }
            /* 在新单元中添加移动的扑克牌 */
            pUnit->arrPoker[0] = g_selectPoker.arrPoker[0];
            pUnit->nCurCount = 1;
        }
        break;
        /* 判断可用单元 */
    case UseUnit:
        {
            /* 所选牌数不为1或者单元中已有扑克牌则返回 */
            if(1 != nSelectPokerCount || pDstPoker != NULL)
            {
                return 0;
            }

            /* 从扑克牌原属于单元中删除移动的扑克牌 */
            pOldUnit->nCurCount = nOldUnitCount - 1;
            pOldUnit->arrPoker[nOldUnitCount - 1] = NULL;
            /* 记录扑克牌原坐标点 */
            nOldX = g_selectPoker.arrPoker[0]->rect.x;
            nOldY = g_selectPoker.arrPoker[0]->rect.y;
            /* 修改扑克牌所属单元 */
            g_selectPoker.arrPoker[0]->pUnit = pUnit;
            g_selectPoker.arrPoker[0]->rect.x = pUnit->nX;
            g_selectPoker.arrPoker[0]->rect.y = pUnit->nY;
            if(1 == nIsAction)
            {
                /* 动画移动效果 */
                interfacePokerMove(nOldX, nOldY, pUnit->nX, pUnit->nY, 
                    g_selectPoker.arrPoker[0], 10, 0);
            }
            /* 在新单元中添加移动的扑克牌 */
            pUnit->arrPoker[0] = g_selectPoker.arrPoker[0];
            pUnit->nCurCount = 1;

        }
        break;
    /* 判断普通单元 */
    case NormalUnit:
        {
            /* 目标单元当前牌数不为0时，要做是否符合规则判断 */
            if(0 != nUnitPokerCount)
            {
                if((pDstPoker->color % 2 == g_selectPoker.arrPoker[0]->color % 2)
                    || (pDstPoker->nNum != g_selectPoker.arrPoker[0]->nNum + 1))
                {
                    return 0;
                }
            }

            /* 将所选牌组从原单元删除 */
            for(i=0; i<nOldUnitCount; ++i)
            {
                if(g_selectPoker.arrPoker[0] == pOldUnit->arrPoker[i])
                {
                    pOldUnit->nCurCount = nOldUnitCount - nSelectPokerCount;
                    memset(pOldUnit->arrPoker + i, 0, 
                        nSelectPokerCount * sizeof(Poker *));
                }
            }

            if(1 == nIsAction)
            {
                /* 移动动画 */
                interfacePokerMove(g_selectPoker.arrPoker[0]->rect.x,
                    g_selectPoker.arrPoker[0]->rect.y,
                    pUnit->nX, pUnit->nY + POKER_SPACE * nUnitPokerCount, NULL, 10, 0);
            }
            /* 将所选牌组添加到目标单元 */
            for(i=0; i<nSelectPokerCount; ++i)
            {
                g_selectPoker.arrPoker[i]->pUnit = pUnit;
                g_selectPoker.arrPoker[i]->rect.x = pUnit->nX;
                g_selectPoker.arrPoker[i]->rect.y 
                    = pUnit->nY + POKER_SPACE * pUnit->nCurCount;
                pUnit->arrPoker[pUnit->nCurCount] = g_selectPoker.arrPoker[i];
                pUnit->nCurCount++;
            } 
        }
        break;
    }

    return 1;
}