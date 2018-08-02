/***************************************************
 *  文件：SolitaireInterface.c
 *  说明：图形界面相关处理
 *  作者：
 *  日期：
 ***************************************************/

#include "SolitaireInterface.h"
#include <stdio.h>
#include <windows.h>

#define BACKGROUND_PATH "../Image/background.jpg"
#define FRAME_PATH "../Image/frame.png"
#define POKER_PATH "../Image/poker.png"
#define POKER_BACK_PATH "../Image/back.png" 
#define SELECT_FRAME_PATH "../Image/selectFrame.png" 

static SDL_Window * g_pWindow = NULL;       // 主窗口指针
static SDL_Renderer * g_pRenderer = NULL;   // 渲染器指针
static SDL_Texture * g_pBackground = NULL;  // 背景图片
static SDL_Texture * g_pUnitFrame = NULL;   // 单元边框图片
static SDL_Texture * g_pPoker = NULL;       // 扑克图片
static SDL_Texture * g_pPokerBack = NULL;   // 扑克背面图片
static SDL_Texture * g_pSelectFrame = NULL; // 选中边框图片

extern Unit g_arrNormalUnit[8];
extern Unit g_arrUseUnit[4];
extern Unit g_arrRetrieveUnit[4];
extern Poker g_arrPoker[52];

extern SelectPoker g_selectPoker;
extern int g_nIsButtonDownLeft;

extern int g_nMouseX;
extern int g_nMouseY;
extern int g_nMouseOffsetX;
extern int g_nMouseOffsetY;
 
/** 初始化窗口 **/
int interfaceInit(void)
{
    wchar_t * pwcTitle = L"空当接龙";       // 窗口标题文字
    char szTitle[1024] = {0};

    /* 标题中文宽字节转多字节 */ 
    WideCharToMultiByte(CP_UTF8, 0, pwcTitle, -1, szTitle, sizeof(szTitle), NULL, NULL);

    /* 初始化SDL */
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("[Interface]初始化SDL失败：%s\n", SDL_GetError());
        return -1;
    }

    /* 创建主窗口 */
    g_pWindow = SDL_CreateWindow(szTitle, 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        WINDOW_WIDTH, WINDOW_HEIGHT, 
        SDL_WINDOW_SHOWN);
    if(NULL == g_pWindow)
    {
        printf("[Interface]创建窗口失败：%s\n", SDL_GetError());
        return -2;
    }

    /* 创建渲染器 */
    g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(NULL == g_pRenderer)
    {
        printf("[Interface]创建渲染器失败：%s\n", SDL_GetError());
        return -3;
    }

    /* 加载窗口背景图片 */
    g_pBackground = interfaceLoadImage(BACKGROUND_PATH);
    if(NULL == g_pBackground)
    {
        return -4;
    }

    /* 加载单元边框 */
    g_pUnitFrame = interfaceLoadImage(FRAME_PATH);
    if(NULL == g_pUnitFrame)
    {
        return -4;
    }
    
    /* 加载扑克图片 */
    g_pPoker = interfaceLoadImage(POKER_PATH);
    if(NULL == g_pUnitFrame)
    {
        return -4;
    }

    /* 加载扑克背面图片 */
    g_pPokerBack = interfaceLoadImage(POKER_BACK_PATH);
    if(NULL == g_pPokerBack)
    {
        return -4;
    }
    
    /* 选中边框图片 */
    g_pSelectFrame = interfaceLoadImage(SELECT_FRAME_PATH);
    if(NULL == g_pSelectFrame)
    {
        return -4;
    }

    interfacePaint(1);

    return 0;
}

/** 绘制窗口 **/
void interfacePaint(int nIsRef)
{
    /* 清空当前渲染器 */
    //SDL_RenderClear(g_pRenderer);

    /* 绘制窗口背景 */
    interfacePaintBackground();

    /* 绘制普通单元的纸牌 */
    interfacePaintNormalUnit();

    /* 绘制可用单元的纸牌 */
    interfacePaintUseUnit();

    /* 绘制回收单元的纸牌 */
    interfacePaintRetrieveUnit();

    /* 绘制正在拖动的纸牌组 */
    interfacePaintMovePokers();

    if(1 == nIsRef)
    {
        /* 更新渲染器图像 */
        SDL_RenderPresent(g_pRenderer);
    }
}

/** 绘制窗口背景 **/
void interfacePaintBackground(void)
{
    int i = 0;
    SDL_Rect rect;

    /* 绘制背景图 */
    interfaceDrawImage(g_pBackground, g_pRenderer, NULL, NULL);

    /* 调整可用单元与回收单元边框大小 */
    rect.w = POKER_WIDTH + 20;
    rect.h = POKER_HEIGHT + 20;
    /* 绘制可用单元边框 */
    for(i=0; i<4; ++i)
    {
        rect.x = g_arrUseUnit[i].nX - 10;
        rect.y = g_arrUseUnit[i].nY - 10;
        interfaceDrawImage(g_pUnitFrame, g_pRenderer, NULL, &rect);
    }
    /* 绘制回收单元边框 */
    for(i=0; i<4;++i)
    {
        rect.x = g_arrRetrieveUnit[i].nX - 10;
        rect.y = g_arrRetrieveUnit[i].nY - 10;
        interfaceDrawImage(g_pUnitFrame, g_pRenderer, NULL, &rect);
    }

    /* 绘制普通单元边框 */
    rect.w = POKER_WIDTH;
    rect.h = POKER_HEIGHT;
    for(i=0; i<8; ++i)
    {
        rect.x = g_arrNormalUnit[i].nX;
        rect.y = g_arrNormalUnit[i].nY;
        interfaceDrawImage(g_pUnitFrame, g_pRenderer, NULL, &rect);
    }
}

/** 绘制普通单元的扑克牌 **/
void interfacePaintNormalUnit(void)
{
    int i = 0;              // 循环变量
    int j = 0;              // 循环变量
    int nCount = 0;         // 单元中扑克牌数量
    Unit * pUnit = NULL;    // 正在打印的单元的指针
    SDL_Rect srcRect;       // 扑克牌在源图像中的区域
    SDL_Rect dstRect;       // 扑克牌将要打印到屏幕的区域
    SDL_Rect frameRect;     // 选中边框在屏幕中的区域

    /* 普通单元数组循环打印 */
    for(i=0; i<8; ++i)
    {
        /* 当前需要打印的普通单元 */
        pUnit = &g_arrNormalUnit[i];
        /* 单元中扑克牌的数量 */
        nCount = pUnit->nCurCount;
        /* 单元中扑克牌循环打印 */
        for(j=0; j<nCount; ++j)
        {
            /* 如果扑克牌为所选扑克牌则不进行绘制 */
            if(pUnit->arrPoker[j] == g_selectPoker.arrPoker[0]
            && g_nIsButtonDownLeft == 1)
            {
                break;
            }
            /* 扑克牌将要绘制到窗口的区域 */
            dstRect.x = pUnit->arrPoker[j]->rect.x;
            dstRect.y = pUnit->arrPoker[j]->rect.y;
            dstRect.w = pUnit->arrPoker[j]->rect.width;
            dstRect.h = pUnit->arrPoker[j]->rect.height;
            /* 扑克牌在源图像中的区域 */
            srcRect = interfaceGetPokerRect(pUnit->arrPoker[j]);
            /* 绘制扑克牌 */
            interfaceDrawImage(g_pPoker, g_pRenderer, &srcRect, &dstRect);
            /* 如果选中则绘制边框 */
            if(g_selectPoker.arrPoker[0] == pUnit->arrPoker[j])
            {
                frameRect.w = POKER_WIDTH + 10;
                frameRect.h = POKER_HEIGHT + 10 + (g_selectPoker.nCount - 1) * POKER_SPACE;
                frameRect.x = g_selectPoker.arrPoker[0]->rect.x - 5;
                frameRect.y = g_selectPoker.arrPoker[0]->rect.y - 5;
                interfaceDrawImage(g_pSelectFrame, g_pRenderer, NULL, &frameRect);
            }
        }
    }
}

/** 绘制可用单元的扑克牌 **/
void interfacePaintUseUnit(void)
{
    int i = 0;              // 循环变量
    SDL_Rect srcRect;       // 扑克牌在源图像中的区域
    SDL_Rect dstRect;       // 扑克牌将要打印到屏幕的区域

    for(i=0; i<4; ++i)
    {
        if(g_arrUseUnit[i].nCurCount == 1)
        {
            /* 如果扑克牌为所选扑克牌则不进行绘制 */
            if(g_arrUseUnit[i].arrPoker[0] == g_selectPoker.arrPoker[0]
            && g_nIsButtonDownLeft == 1)
            {
                continue;
            }

            /* 扑克牌将要绘制到窗口的区域 */
            dstRect.x = g_arrUseUnit[i].arrPoker[0]->rect.x;
            dstRect.y = g_arrUseUnit[i].arrPoker[0]->rect.y;
            dstRect.w = g_arrUseUnit[i].arrPoker[0]->rect.width;
            dstRect.h = g_arrUseUnit[i].arrPoker[0]->rect.height;
            /* 扑克牌在源图像中的区域 */
            srcRect = interfaceGetPokerRect(g_arrUseUnit[i].arrPoker[0]);
            /* 绘制扑克牌 */
            interfaceDrawImage(g_pPoker, g_pRenderer, &srcRect, &dstRect);
            /* 如果选中则绘制边框 */
            if(g_selectPoker.arrPoker[0] == g_arrUseUnit[i].arrPoker[0])
            {
                SDL_Rect frameRect;
                frameRect.w = POKER_WIDTH + 10;
                frameRect.h = POKER_HEIGHT + 10 + (g_selectPoker.nCount - 1) * POKER_SPACE;
                frameRect.x = g_selectPoker.arrPoker[0]->rect.x - 5;
                frameRect.y = g_selectPoker.arrPoker[0]->rect.y - 5;
                interfaceDrawImage(g_pSelectFrame, g_pRenderer, NULL, &frameRect);
            }
        }
    }
}

/** 绘制回收单元的扑克牌 **/
void interfacePaintRetrieveUnit(void)
{
    int i = 0;              // 循环变量
    SDL_Rect srcRect;       // 扑克牌在源图像中的区域
    SDL_Rect dstRect;       // 扑克牌将要打印到屏幕的区域

    for(i=0; i<4; ++i)
    {
        if(g_arrRetrieveUnit[i].nCurCount == 1)
        {
            /* 扑克牌将要绘制到窗口的区域 */
            dstRect.x = g_arrRetrieveUnit[i].arrPoker[0]->rect.x;
            dstRect.y = g_arrRetrieveUnit[i].arrPoker[0]->rect.y;
            dstRect.w = g_arrRetrieveUnit[i].arrPoker[0]->rect.width;
            dstRect.h = g_arrRetrieveUnit[i].arrPoker[0]->rect.height;
            /* 扑克牌在源图像中的区域 */
            srcRect = interfaceGetPokerRect(g_arrRetrieveUnit[i].arrPoker[0]);
            /* 绘制扑克牌 */
            interfaceDrawImage(g_pPoker, g_pRenderer, &srcRect, &dstRect);
        }
    }
}

/** 绘制扑克牌背面图片 **/
void interfacePaintPokerBack(void)
{
    SDL_Rect rect;

    rect.x = DEAL_POINT_X;
    rect.y = DEAL_POINT_Y;
    rect.w = POKER_WIDTH;
    rect.h = POKER_HEIGHT;

    interfaceDrawImage(g_pPokerBack, g_pRenderer, NULL, &rect);
}

/** 绘制正在移动的扑克牌组 **/
void interfacePaintMovePokers(void)
{
    if(1 == g_nIsButtonDownLeft && g_selectPoker.nCount > 0)
    {
        SDL_Rect arrSrcRect[13];
        int nMovePokerCount = 0;
        int i = 0;
        SDL_Rect dstRect;
        SDL_Rect frameRect;

        /* 扑克牌在源图像中的位置信息 */
        nMovePokerCount = g_selectPoker.nCount;
        for(i=0; i<nMovePokerCount; ++i)
        {
            arrSrcRect[i] = interfaceGetPokerRect(g_selectPoker.arrPoker[i]);
        }


        /* 获取扑克牌将要绘制的位置信息 */
        dstRect.x = g_nMouseX - g_nMouseOffsetX;
        dstRect.y = g_nMouseY - g_nMouseOffsetY;
        dstRect.w = POKER_WIDTH;
        dstRect.h = POKER_HEIGHT;

        /* 选中绘制边框 */
        frameRect.w = POKER_WIDTH + 10;
        frameRect.h = POKER_HEIGHT + 10 + (nMovePokerCount - 1) * POKER_SPACE;
        frameRect.x = dstRect.x - 5;
        frameRect.y = dstRect.y - 5;
        interfaceDrawImage(g_pSelectFrame, g_pRenderer, NULL, &frameRect);

        /* 绘制移动的扑克牌 */
        for(i=0; i<nMovePokerCount; ++i)
        {
            interfaceDrawImage(g_pPoker, g_pRenderer, &arrSrcRect[i], &dstRect);
            dstRect.y += POKER_SPACE;
        }
    }
}

/** 根据图片路径加载图片 **/
SDL_Texture * interfaceLoadImage(const char * pFilePath)
{
    SDL_Texture * pTexture = NULL;
    
    if(NULL == pFilePath)
    {
        return NULL;
    }

    pTexture = IMG_LoadTexture(g_pRenderer, pFilePath);
    if(pTexture == NULL)
    {
        printf("[Interface]加载图片(\"%s\")失败：%s\n", pFilePath, IMG_GetError());
    }
    return pTexture;
}

/** 往渲染器中绘制图像 **/
void interfaceDrawImage(SDL_Texture * pTexture, SDL_Renderer * pRenderer, 
                        SDL_Rect * pSrcRect, SDL_Rect * pDstRect)
{
    SDL_Rect rect;

    if(NULL == pSrcRect)
    {
        pSrcRect = &rect;
        SDL_QueryTexture(pTexture, NULL, NULL, &(pSrcRect->w), &(pSrcRect->h));
        pSrcRect->x = 0;
        pSrcRect->y = 0;
    }
    
    if(NULL == pDstRect)
    {
        pDstRect = &rect;
    }

    SDL_RenderCopy(pRenderer, pTexture, pSrcRect, pDstRect);

    return;
}

/** 销毁窗口 **/
void interfaceDestroy(void)
{
    /* 销毁背景图变量 */
    SDL_DestroyTexture(g_pBackground);
    g_pBackground = NULL;

    /* 销毁单元边框图变量 */
    SDL_DestroyTexture(g_pUnitFrame);
    g_pUnitFrame = NULL;

    /* 销毁扑克图变量 */
    SDL_DestroyTexture(g_pPoker);
    g_pPoker = NULL;

    /* 销毁扑克背面图变量 */
    SDL_DestroyTexture(g_pPokerBack);
    g_pPokerBack = NULL;

    /* 销毁选中边框图片变量 */
    SDL_DestroyTexture(g_pSelectFrame);
    g_pSelectFrame = NULL;

    SDL_DestroyRenderer(g_pRenderer);
    SDL_DestroyWindow(g_pWindow);
 
    SDL_Quit();

    return;
}

/** 扑克牌移动动画 **/
void interfacePokerMove(int nSrcX, int nSrcY, 
                        int nDstX, int nDstY, 
                        const Poker * pPoker, 
                        int nMoveCount, int nIsDeal)
{
    int i = 0, j = 0;       // 循环变量
    int nAddX = (nDstX - nSrcX) / nMoveCount;   // X轴移动增量
    int nAddY = (nDstY - nSrcY) / nMoveCount;   // Y轴移动增量
    SDL_Rect srcRect;       // 源图像区域
    SDL_Rect dstRect;       // 目的区域
    SDL_Rect arrSrcRect[13];
    int nMovePokerCount = 0;
    
    /* 扑克牌在源图像中的位置信息 */
    if(pPoker != NULL)
    {
        nMovePokerCount = 1;
        arrSrcRect[0] = interfaceGetPokerRect(pPoker);
    }
    else
    {
        nMovePokerCount = g_selectPoker.nCount;
        for(i=0; i<nMovePokerCount; ++i)
        {
            arrSrcRect[i] = interfaceGetPokerRect(g_selectPoker.arrPoker[i]);
        }
    }

    /* 获取扑克牌将要绘制的位置信息 */
    dstRect.x = nSrcX;
    dstRect.y = nSrcY;
    dstRect.w = POKER_WIDTH;
    dstRect.h = POKER_HEIGHT;

    /* 循环动画 */
    for(i=0; i<nMoveCount; ++i)
    {        
        SDL_Rect tempRect;

        /* 绘制窗口 */
        interfacePaint(0);

        dstRect.x += nAddX;
        dstRect.y += nAddY;

        tempRect = dstRect;
        /* 绘制移动的扑克牌 */
        for(j=0; j<nMovePokerCount; ++j)
        {
            tempRect.y = dstRect.y + POKER_SPACE * j;
            interfaceDrawImage(g_pPoker, g_pRenderer, &arrSrcRect[j], &tempRect);
        }

        /* 发牌时显示扑克牌背面 */
        if(1 == nIsDeal)
        {
            interfacePaintPokerBack();
        }

        /* 更新渲染器图像 */
        SDL_RenderPresent(g_pRenderer);
    }
}

/** 获取扑克牌在原图中的区域 **/
SDL_Rect interfaceGetPokerRect(const Poker * pPoker)
{
    SDL_Rect rect;  // 扑克牌在原图中的区域

    rect.w = 144;   // 扑克牌在原图中的宽
    rect.h = 194;   // 扑克牌在原图中的高
    
    /* 扑克牌在源图像中的X坐标 */
    rect.x = (144 + 2) * (pPoker->nNum - 1);

    /* 扑克牌在源图像中的Y坐标 */
    switch(pPoker->color)
    {
    case Club:
        rect.y = 0;
        break;
    case Diamond:
        rect.y = 194 + 2;
        break;
    case Spade:
        rect.y = (194 + 2) * 2;
        break;
    case Heart:
        rect.y = (194 + 2) * 3;
        break;
    }

    return rect;
}