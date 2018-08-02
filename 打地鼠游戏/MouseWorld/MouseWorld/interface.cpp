#include "interface.h"

SDL_Window * g_pWindow = NULL;        // 窗口指针
SDL_Renderer * g_pRenderer = NULL;    // 渲染器

Picture g_picBackGround;      // 背景图片

Picture g_picSpriteNormal_1;      // 普通地鼠图片1
Picture g_picSpriteNormal_2;      // 普通地鼠图片2
Picture g_picSpriteNormal_3;      // 普通地鼠图片3
Picture g_picSpriteNormal_4;      // 普通地鼠图片4
Picture g_picSpriteNormal_5;      // 普通地鼠图片5

Picture g_picSpriteBeat_1;      // 被打图片
Picture g_picSpriteBeat_2;      // 被打图片
Picture g_picSpriteBeat_3;      // 被打图片
Picture g_picSpriteBeat_4;      // 被打图片
Picture g_picSpriteBeat_5;      // 被打图片

extern Sprite g_spriteArr[9];   // 地鼠数组
Picture g_picNumber;
extern int g_nScore;



// 初始化SDL库及窗口、渲染器 
int initSDL(void)
{
  
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout<<"初始化失败"<< SDL_GetError()<<endl;
        return -1;
    }
    cout<<"初始化成功"<<endl;
    // 创建窗口
    g_pWindow = SDL_CreateWindow("MouseWorld", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(NULL == g_pWindow)
    {
         cout<<"创建窗口失败"<< SDL_GetError()<<endl;
        return -2;
    }
    cout<<"创建窗口成功"<<endl;
    // 创建渲染器
    g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(NULL == g_pRenderer)
    {
        cout<<"创建渲染器失败"<< SDL_GetError()<<endl;
        return -3;
    }
     cout<<"创建渲染器成功"<<endl;

    return 0;
}


//  释放SDL库、窗口、渲染器
void freeSDL(void)
{
    // 释放渲染器
    SDL_DestroyRenderer(g_pRenderer);
   cout<<"渲染器释放!"<<endl;

    // 释放窗口
    SDL_DestroyWindow(g_pWindow);
    cout<<"窗口释放!"<<endl;

    // 退出SDL2.0库
    SDL_Quit();
   cout<<"SDL库已退出!"<<endl;
}


// 加载一幅图片
Picture loadPic(const char * path)
{
    Picture pic;
    // 加载一幅图片
    pic.pPic = IMG_LoadTexture(g_pRenderer, path);
    if(NULL == pic.pPic)
    {
        cout<<"图片创建失败："<< SDL_GetError()<<endl;
    }
    return pic;
}


//  设置一幅图片的目标显示区域
void setPicDstRect(Picture * picture, int x, int y,
                   int w, int h)
{
    picture->dstRect.x = x;
    picture->dstRect.y = y;
    picture->dstRect.w = w;
    picture->dstRect.h = h;
}


//  设置一幅图片的源读取区域
void setPicSrcRect(Picture * picture, int x, int y,
                   int w, int h)
{
    picture->srcRect.x = x;
    picture->srcRect.y = y;
    
    if(0 == w || 0 == h)
    {
        SDL_QueryTexture(picture->pPic, NULL, NULL,
            &(picture->srcRect.w), &(picture->srcRect.h));
    }
    else
    {
        picture->srcRect.w = w;
        picture->srcRect.h = h;
    }
    
}


// 说明: 加载程序所需的图片资源
int loadPicResources(void)
{
    // 加载背景图片
    g_picBackGround= loadPic(PATH_BACKGROUND);
    if(g_picBackGround.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picBackGround, 0, 0, 0, 0);
    setPicDstRect(&g_picBackGround, 
        BACKGROUND_PIC_X, BACKGROUND_PIC_Y, 
        BACKGROUND_PIC_W, BACKGROUND_PIC_H);

     // 加载精灵图片-普通地鼠1
    g_picSpriteNormal_1 = loadPic(PATH_SPRITE_NORMAL_1);
    if(g_picSpriteNormal_1.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteNormal_1, 0, 0, 0, 0);
     // 加载精灵图片-普通地鼠2
    g_picSpriteNormal_2 = loadPic(PATH_SPRITE_NORMAL_2);
    if(g_picSpriteNormal_2.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteNormal_2, 0, 0, 0, 0);
     // 加载精灵图片-普通地鼠3
    g_picSpriteNormal_3 = loadPic(PATH_SPRITE_NORMAL_3);
    if(g_picSpriteNormal_3.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteNormal_3, 0, 0, 0, 0);
     // 加载精灵图片-普通地鼠4
    g_picSpriteNormal_4 = loadPic(PATH_SPRITE_NORMAL_4);
    if(g_picSpriteNormal_4.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteNormal_4, 0, 0, 0, 0);
     // 加载精灵图片-普通地鼠5
    g_picSpriteNormal_5 = loadPic(PATH_SPRITE_NORMAL_5);
    if(g_picSpriteNormal_5.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteNormal_5, 0, 0, 0, 0);

   // 加载精灵图片-被打地鼠1
    g_picSpriteBeat_1 = loadPic( PATH_SPRITE_BEAT_1);
    if(g_picSpriteBeat_1.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteBeat_1, 0, 0, 0, 0);
     // 加载精灵图片-被打地鼠2
    g_picSpriteBeat_2 = loadPic( PATH_SPRITE_BEAT_2);
    if(g_picSpriteBeat_2.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteBeat_2, 0, 0, 0, 0);
     // 加载精灵图片-被打地鼠3
    g_picSpriteBeat_3 = loadPic( PATH_SPRITE_BEAT_3);
    if(g_picSpriteBeat_3.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteBeat_3, 0, 0, 0, 0);
     // 加载精灵图片-被打地鼠4
    g_picSpriteBeat_4 = loadPic( PATH_SPRITE_BEAT_4);
    if(g_picSpriteBeat_4.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteBeat_4, 0, 0, 0, 0);
     // 加载精灵图片-被打地鼠5
    g_picSpriteBeat_5 = loadPic( PATH_SPRITE_BEAT_5);
    if(g_picSpriteBeat_5.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteBeat_5, 0, 0, 0, 0);
     // 加载数字图片
    g_picNumber = loadPic(PATH_NUMBER);
    if(g_picNumber.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picNumber, 
        0, NUMBER_SRC_Y, 
        NUMBER_SRC_W, NUMBER_SRC_H);
    setPicDstRect(&g_picNumber, 
        0, NUMBER_DST_Y, 
        NUMBER_DST_W, NUMBER_DST_H);
   

   
    return 0;
}

//  释放程序加载的图片资源
void freePicResources(void)
{
    // 释放背景图片
    SDL_DestroyTexture(g_picBackGround.pPic);
    //释放普通地鼠
    SDL_DestroyTexture(g_picSpriteNormal_1.pPic);
    SDL_DestroyTexture(g_picSpriteNormal_2.pPic);
    SDL_DestroyTexture(g_picSpriteNormal_3.pPic);
    SDL_DestroyTexture(g_picSpriteNormal_4.pPic);
    SDL_DestroyTexture(g_picSpriteNormal_5.pPic);
    //释放被打地鼠
    SDL_DestroyTexture(g_picSpriteBeat_1.pPic);
    SDL_DestroyTexture(g_picSpriteBeat_2.pPic);
    SDL_DestroyTexture(g_picSpriteBeat_3.pPic);
    SDL_DestroyTexture(g_picSpriteBeat_4.pPic);
    SDL_DestroyTexture(g_picSpriteBeat_5.pPic);
    SDL_DestroyTexture(g_picNumber.pPic);
}


//  往渲染器绘制一幅图片
void paintPic(Picture * picture)
{
    SDL_RenderCopy(g_pRenderer, picture->pPic,
        &(picture->srcRect), &(picture->dstRect));
}


// 绘制窗口
void paint(void)
{
    paintPic(&g_picBackGround);   // 绘制背景图片1
    paintSprite(0);
    paintSprite(1);
    paintSprite(2);
    // 更新渲染器图像
    SDL_RenderPresent(g_pRenderer);
    paintScore();
}

//  绘制精灵
void paintSprite(int nLayer)
{
    int i = 0;
    Picture * pPic = NULL;
    // 根据层数，遍历指定层的三个精灵
    for(i=nLayer*3; i<((nLayer+1)*3); i++)
    {
        if(g_spriteArr[i].type == TypeEmpty)        
        {
            continue;
        }
        else if(g_spriteArr[i].type ==  TypeNormal1) 
        {
            if(g_spriteArr[i].state == StateBeat)
            {
                pPic = &g_picSpriteBeat_1; 
            }
            else
            {
                pPic = & g_picSpriteNormal_1; 
            }          
        }
        else if(g_spriteArr[i].type == TypeNormal2)   
        {
            if(g_spriteArr[i].state == StateBeat)
            {
                pPic = &g_picSpriteBeat_2;   
            }
            else
            {
                pPic = &g_picSpriteNormal_2;   
            }        
        }
        else if(g_spriteArr[i].type == TypeNormal3)   
        {
            if(g_spriteArr[i].state == StateBeat)
            {
                pPic = &g_picSpriteBeat_3;   
            }
            else
            {
                pPic = &g_picSpriteNormal_3;   
            }        
        }
        else if(g_spriteArr[i].type == TypeNormal4)   
        {
            if(g_spriteArr[i].state == StateBeat)
            {
                pPic = &g_picSpriteBeat_4;   
            }
            else
            {
                pPic = &g_picSpriteNormal_4;   
            }        
        }
        else                                      
        {
            if(g_spriteArr[i].state == StateBeat)
            {
                pPic = &g_picSpriteBeat_5;   
            }
            else
            {
                pPic = &g_picSpriteNormal_5;   
            }        
        }

       
        pPic->dstRect = g_spriteArr[i].initRect;
        if(g_spriteArr[i].state == StateUp)
        {
            pPic->dstRect.y = 
                (g_spriteArr[i].initRect.y + g_spriteArr[i].initRect.h)
                - g_spriteArr[i].initRect.h / FRAMENUMBER_UP 
                * g_spriteArr[i].runningTimes;
        }
        if(g_spriteArr[i].state == StateDown)
        {
            pPic->dstRect.y = 
                g_spriteArr[i].initRect.y + 
                g_spriteArr[i].initRect.h / FRAMENUMBER_DOWN 
                * g_spriteArr[i].runningTimes;
        }
        
        // 绘制图片
        paintPic(pPic); 
    }
}

// 说明: 打印分数
void paintScore(void)
{
    int nScoreBit = 0;
    int nCurScore = g_nScore;
    int nCurBitNumber = 0;
    int i, j;

    while(nCurScore > 0)
    {
        nCurScore /= 10;
        nScoreBit++;
    }

    if(g_nScore == 0)
    {
        nScoreBit = 1;
    }

    for(i=0; i<nScoreBit; i++)
    {
        g_picNumber.dstRect.x = 300;
           
          g_picNumber.dstRect.y=50;
        nCurScore = g_nScore;
        for(j=1; j < (nScoreBit - i); j++)
        {
            nCurScore /= 10;
        }
        nCurBitNumber = nCurScore % 10;
        g_picNumber.srcRect.x = nCurBitNumber * NUMBER_SRC_W;
        paintPic(&g_picNumber);
    }
}