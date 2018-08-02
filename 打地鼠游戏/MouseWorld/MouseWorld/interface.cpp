#include "interface.h"

SDL_Window * g_pWindow = NULL;        // ����ָ��
SDL_Renderer * g_pRenderer = NULL;    // ��Ⱦ��

Picture g_picBackGround;      // ����ͼƬ

Picture g_picSpriteNormal_1;      // ��ͨ����ͼƬ1
Picture g_picSpriteNormal_2;      // ��ͨ����ͼƬ2
Picture g_picSpriteNormal_3;      // ��ͨ����ͼƬ3
Picture g_picSpriteNormal_4;      // ��ͨ����ͼƬ4
Picture g_picSpriteNormal_5;      // ��ͨ����ͼƬ5

Picture g_picSpriteBeat_1;      // ����ͼƬ
Picture g_picSpriteBeat_2;      // ����ͼƬ
Picture g_picSpriteBeat_3;      // ����ͼƬ
Picture g_picSpriteBeat_4;      // ����ͼƬ
Picture g_picSpriteBeat_5;      // ����ͼƬ

extern Sprite g_spriteArr[9];   // ��������
Picture g_picNumber;
extern int g_nScore;



// ��ʼ��SDL�⼰���ڡ���Ⱦ�� 
int initSDL(void)
{
  
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout<<"��ʼ��ʧ��"<< SDL_GetError()<<endl;
        return -1;
    }
    cout<<"��ʼ���ɹ�"<<endl;
    // ��������
    g_pWindow = SDL_CreateWindow("MouseWorld", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(NULL == g_pWindow)
    {
         cout<<"��������ʧ��"<< SDL_GetError()<<endl;
        return -2;
    }
    cout<<"�������ڳɹ�"<<endl;
    // ������Ⱦ��
    g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(NULL == g_pRenderer)
    {
        cout<<"������Ⱦ��ʧ��"<< SDL_GetError()<<endl;
        return -3;
    }
     cout<<"������Ⱦ���ɹ�"<<endl;

    return 0;
}


//  �ͷ�SDL�⡢���ڡ���Ⱦ��
void freeSDL(void)
{
    // �ͷ���Ⱦ��
    SDL_DestroyRenderer(g_pRenderer);
   cout<<"��Ⱦ���ͷ�!"<<endl;

    // �ͷŴ���
    SDL_DestroyWindow(g_pWindow);
    cout<<"�����ͷ�!"<<endl;

    // �˳�SDL2.0��
    SDL_Quit();
   cout<<"SDL�����˳�!"<<endl;
}


// ����һ��ͼƬ
Picture loadPic(const char * path)
{
    Picture pic;
    // ����һ��ͼƬ
    pic.pPic = IMG_LoadTexture(g_pRenderer, path);
    if(NULL == pic.pPic)
    {
        cout<<"ͼƬ����ʧ�ܣ�"<< SDL_GetError()<<endl;
    }
    return pic;
}


//  ����һ��ͼƬ��Ŀ����ʾ����
void setPicDstRect(Picture * picture, int x, int y,
                   int w, int h)
{
    picture->dstRect.x = x;
    picture->dstRect.y = y;
    picture->dstRect.w = w;
    picture->dstRect.h = h;
}


//  ����һ��ͼƬ��Դ��ȡ����
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


// ˵��: ���س��������ͼƬ��Դ
int loadPicResources(void)
{
    // ���ر���ͼƬ
    g_picBackGround= loadPic(PATH_BACKGROUND);
    if(g_picBackGround.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picBackGround, 0, 0, 0, 0);
    setPicDstRect(&g_picBackGround, 
        BACKGROUND_PIC_X, BACKGROUND_PIC_Y, 
        BACKGROUND_PIC_W, BACKGROUND_PIC_H);

     // ���ؾ���ͼƬ-��ͨ����1
    g_picSpriteNormal_1 = loadPic(PATH_SPRITE_NORMAL_1);
    if(g_picSpriteNormal_1.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteNormal_1, 0, 0, 0, 0);
     // ���ؾ���ͼƬ-��ͨ����2
    g_picSpriteNormal_2 = loadPic(PATH_SPRITE_NORMAL_2);
    if(g_picSpriteNormal_2.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteNormal_2, 0, 0, 0, 0);
     // ���ؾ���ͼƬ-��ͨ����3
    g_picSpriteNormal_3 = loadPic(PATH_SPRITE_NORMAL_3);
    if(g_picSpriteNormal_3.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteNormal_3, 0, 0, 0, 0);
     // ���ؾ���ͼƬ-��ͨ����4
    g_picSpriteNormal_4 = loadPic(PATH_SPRITE_NORMAL_4);
    if(g_picSpriteNormal_4.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteNormal_4, 0, 0, 0, 0);
     // ���ؾ���ͼƬ-��ͨ����5
    g_picSpriteNormal_5 = loadPic(PATH_SPRITE_NORMAL_5);
    if(g_picSpriteNormal_5.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteNormal_5, 0, 0, 0, 0);

   // ���ؾ���ͼƬ-�������1
    g_picSpriteBeat_1 = loadPic( PATH_SPRITE_BEAT_1);
    if(g_picSpriteBeat_1.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteBeat_1, 0, 0, 0, 0);
     // ���ؾ���ͼƬ-�������2
    g_picSpriteBeat_2 = loadPic( PATH_SPRITE_BEAT_2);
    if(g_picSpriteBeat_2.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteBeat_2, 0, 0, 0, 0);
     // ���ؾ���ͼƬ-�������3
    g_picSpriteBeat_3 = loadPic( PATH_SPRITE_BEAT_3);
    if(g_picSpriteBeat_3.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteBeat_3, 0, 0, 0, 0);
     // ���ؾ���ͼƬ-�������4
    g_picSpriteBeat_4 = loadPic( PATH_SPRITE_BEAT_4);
    if(g_picSpriteBeat_4.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteBeat_4, 0, 0, 0, 0);
     // ���ؾ���ͼƬ-�������5
    g_picSpriteBeat_5 = loadPic( PATH_SPRITE_BEAT_5);
    if(g_picSpriteBeat_5.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteBeat_5, 0, 0, 0, 0);
     // ��������ͼƬ
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

//  �ͷų�����ص�ͼƬ��Դ
void freePicResources(void)
{
    // �ͷű���ͼƬ
    SDL_DestroyTexture(g_picBackGround.pPic);
    //�ͷ���ͨ����
    SDL_DestroyTexture(g_picSpriteNormal_1.pPic);
    SDL_DestroyTexture(g_picSpriteNormal_2.pPic);
    SDL_DestroyTexture(g_picSpriteNormal_3.pPic);
    SDL_DestroyTexture(g_picSpriteNormal_4.pPic);
    SDL_DestroyTexture(g_picSpriteNormal_5.pPic);
    //�ͷű������
    SDL_DestroyTexture(g_picSpriteBeat_1.pPic);
    SDL_DestroyTexture(g_picSpriteBeat_2.pPic);
    SDL_DestroyTexture(g_picSpriteBeat_3.pPic);
    SDL_DestroyTexture(g_picSpriteBeat_4.pPic);
    SDL_DestroyTexture(g_picSpriteBeat_5.pPic);
    SDL_DestroyTexture(g_picNumber.pPic);
}


//  ����Ⱦ������һ��ͼƬ
void paintPic(Picture * picture)
{
    SDL_RenderCopy(g_pRenderer, picture->pPic,
        &(picture->srcRect), &(picture->dstRect));
}


// ���ƴ���
void paint(void)
{
    paintPic(&g_picBackGround);   // ���Ʊ���ͼƬ1
    paintSprite(0);
    paintSprite(1);
    paintSprite(2);
    // ������Ⱦ��ͼ��
    SDL_RenderPresent(g_pRenderer);
    paintScore();
}

//  ���ƾ���
void paintSprite(int nLayer)
{
    int i = 0;
    Picture * pPic = NULL;
    // ���ݲ���������ָ�������������
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
        
        // ����ͼƬ
        paintPic(pPic); 
    }
}

// ˵��: ��ӡ����
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