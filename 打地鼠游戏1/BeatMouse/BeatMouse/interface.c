#include "interface.h"

SDL_Window * g_pWindow = NULL;        // ����ָ��
SDL_Renderer * g_pRenderer = NULL;    // ��Ⱦ��

Picture g_picBackGround_1;      // ����ͼƬ1
Picture g_picBackGround_2;      // ����ͼƬ2
Picture g_picBackGround_3;      // ����ͼƬ3
Picture g_picBackGround_4;      // ����ͼƬ4

Picture g_picSpriteNormal;      // ��ͨ����ͼƬ
Picture g_picSpriteBomb;        // ը������ͼƬ
Picture g_picSpriteBeat;        // �������ͼƬ
Picture g_picSpriteOctopus;     // ����ͼƬ
Picture g_picSpriteOctBeat;     // ���㱻��ͼƬ

Picture g_picSpriteBlast1;      // ��ըͼƬ1
Picture g_picSpriteBlast2;      // ��ըͼƬ2

Picture g_picSpriteInk;         // ī֭ͼƬ

Picture g_picNumber;            // ����ͼƬ 

extern int g_nScore;            // ���� 

extern Sprite g_spriteArr[9];   // ��������
extern int g_nInkTimes;         // īˮ��ʱ��


//======================================================
// ������int initSDL(void)
// ���ã���ʼ��SDL�⼰���ڡ���Ⱦ�� 
// ���أ�0 ��ʾ��ʼ���ɹ�����0��ʼ��ʧ��
//======================================================
int initSDL(void)
{
    // ��ʼ��SDL2.0������
    if(0 != SDL_Init(SDL_INIT_EVERYTHING))
    {
        printf("SDL2.0��ʼ��ʧ�ܣ�%s\n", SDL_GetError());
        return -1;
    }
    printf("SDL2.0��ʼ���ɹ���\n");

    // ��������
    g_pWindow = SDL_CreateWindow("BeatMouse", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        WINDOW_WIDTH, WINDOW_HEIGHT, 
        SDL_WINDOW_SHOWN);
    if(NULL == g_pWindow)
    {
        printf("���ڴ���ʧ�ܣ�%s\n", SDL_GetError());
        return -2;
    }

    // ������Ⱦ��
    g_pRenderer = SDL_CreateRenderer(g_pWindow,
        -1, SDL_RENDERER_ACCELERATED);
    if(NULL == g_pRenderer)
    {
        printf("��Ⱦ������ʧ�ܣ�%s\n", SDL_GetError());
        return -3;
    }

    return 0;
}

//================================================
// ����: void freeSDL(void)
// ˵��: �ͷ�SDL�⡢���ڡ���Ⱦ��
//================================================
void freeSDL(void)
{
    // �ͷ���Ⱦ��
    SDL_DestroyRenderer(g_pRenderer);
    printf("��Ⱦ���ͷ�!\n");

    // �ͷŴ���
    SDL_DestroyWindow(g_pWindow);
    printf("�����ͷ�!\n");

    // �˳�SDL2.0��
    SDL_Quit();
    printf("SDL�����˳�!\n");
}

//================================================
// ����: Picture loadPic(const char * path))
// ˵��: ����һ��ͼƬ
// ����: path ����ͼƬ·��
// ����: ͼƬ�ṹ��
//================================================
Picture loadPic(const char * path)
{
    Picture pic;
    // ����һ��ͼƬ
    pic.pPic = IMG_LoadTexture(g_pRenderer, path);
    if(NULL == pic.pPic)
    {
        printf("ͼƬ����ʧ�ܣ�%s\n", SDL_GetError());
    }
    return pic;
}

//================================================
// ����: void setPicDstRect(Picture * picture, int x, int y,
//                   int w, int h)
// ˵��: ����һ��ͼƬ��Ŀ����ʾ����
// ����: picture ͼƬ�ṹ��ָ��
//       x, y    Ŀ����������
//       w, h    Ŀ�������С
//================================================
void setPicDstRect(Picture * picture, int x, int y,
                   int w, int h)
{
    picture->dstRect.x = x;
    picture->dstRect.y = y;
    picture->dstRect.w = w;
    picture->dstRect.h = h;
}

//================================================
// ����: void setPicSrcRect(Picture * picture, int x, int y,
//                   int w, int h)
// ˵��: ����һ��ͼƬ��Դ��ȡ����
// ����: picture ͼƬ�ṹ��ָ��
//       x, y    Ŀ����������
//       w, h    Ŀ�������С
//================================================
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

//================================================
// ����: int loadPicResources(void)
// ˵��: ���س��������ͼƬ��Դ
// ����: 0��ʾ���سɹ�����0��ʾ����ʧ��
//================================================
int loadPicResources(void)
{
    // ���ر���ͼƬ1
    g_picBackGround_1 = loadPic(PATH_BACKGROUND_1);
    if(g_picBackGround_1.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picBackGround_1, 0, 0, 0, 0);
    setPicDstRect(&g_picBackGround_1, 
        BACKGROUND_PIC1_X, BACKGROUND_PIC1_Y, 
        BACKGROUND_PIC1_W, BACKGROUND_PIC1_H);

    // ���ر���ͼƬ2
    g_picBackGround_2 = loadPic(PATH_BACKGROUND_2);
    if(g_picBackGround_2.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picBackGround_2, 0, 0, 0, 0);
    setPicDstRect(&g_picBackGround_2, 
        BACKGROUND_PIC2_X, BACKGROUND_PIC2_Y, 
        BACKGROUND_PIC2_W, BACKGROUND_PIC2_H);

    // ���ر���ͼƬ3
    g_picBackGround_3 = loadPic(PATH_BACKGROUND_3);
    if(g_picBackGround_3.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picBackGround_3, 0, 0, 0, 0);
    setPicDstRect(&g_picBackGround_3, 
        BACKGROUND_PIC3_X, BACKGROUND_PIC3_Y, 
        BACKGROUND_PIC3_W, BACKGROUND_PIC3_H);

    // ���ر���ͼƬ4
    g_picBackGround_4 = loadPic(PATH_BACKGROUND_4);
    if(g_picBackGround_4.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picBackGround_4, 0, 0, 0, 0);
    setPicDstRect(&g_picBackGround_4, 
        BACKGROUND_PIC4_X, BACKGROUND_PIC4_Y, 
        BACKGROUND_PIC4_W, BACKGROUND_PIC4_H);

    // ���ؾ���ͼƬ-��ͨ����
    g_picSpriteNormal = loadPic(PATH_SPRITE_NORMAL);
    if(g_picSpriteNormal.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteNormal, 0, 0, 0, 0);

    // ���ؾ���ͼƬ-ը������
    g_picSpriteBomb = loadPic(PATH_SPRITE_BOMB);
    if(g_picSpriteBomb.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteBomb, 0, 0, 0, 0);

    // ���ؾ���ͼƬ-�������
    g_picSpriteBeat = loadPic(PATH_SPRITE_BEAT);
    if(g_picSpriteBeat.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteBeat, 0, 0, 0, 0);

    // ���ؾ���ͼƬ-����
    g_picSpriteOctopus = loadPic(PATH_SPRITE_OCTOPUS);
    if(g_picSpriteOctopus.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteOctopus, 0, 0, 0, 0);

    // ���ؾ���ͼƬ-���㱻��
    g_picSpriteOctBeat = loadPic(PATH_SPRITE_OCTBEAT);
    if(g_picSpriteOctBeat.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteOctBeat, 0, 0, 0, 0);

    // ���ر�ըͼƬ1
    g_picSpriteBlast1 = loadPic(PATH_SPRITE_BLAST_1);
    if(g_picSpriteBlast1.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteBlast1, 0, 0, 0, 0);

    // ���ر�ըͼƬ2
    g_picSpriteBlast2 = loadPic(PATH_SPRITE_BLAST_2);
    if(g_picSpriteBlast2.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteBlast2, 0, 0, 0, 0);

    // ����ī֭ͼƬ
    g_picSpriteInk = loadPic(PATH_SPRITE_INK);
    if(g_picSpriteInk.pPic == NULL)
    {
        return -1;
    }
    setPicSrcRect(&g_picSpriteInk, 0, 0, 0, 0);
    setPicDstRect(&g_picSpriteInk, INK_X, INK_Y,
        INK_W, INK_H);

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

//================================================
// ����: void freePicResources(void)
// ˵��: �ͷų�����ص�ͼƬ��Դ
//================================================
void freePicResources(void)
{
    // �ͷű���ͼƬ
    SDL_DestroyTexture(g_picBackGround_1.pPic);
    SDL_DestroyTexture(g_picBackGround_2.pPic);
    SDL_DestroyTexture(g_picBackGround_3.pPic);
    SDL_DestroyTexture(g_picBackGround_4.pPic);

    // �ͷž���ͼƬ
    SDL_DestroyTexture(g_picSpriteNormal.pPic);
    SDL_DestroyTexture(g_picSpriteBomb.pPic);
    SDL_DestroyTexture(g_picSpriteBeat.pPic);
    SDL_DestroyTexture(g_picSpriteOctopus.pPic);
    SDL_DestroyTexture(g_picSpriteOctBeat.pPic);

    // �ͷ���ЧͼƬ
    SDL_DestroyTexture(g_picSpriteBlast1.pPic);
    SDL_DestroyTexture(g_picSpriteBlast2.pPic);
    SDL_DestroyTexture(g_picSpriteInk.pPic);

    // �ͷ�����ͼƬ
    SDL_DestroyTexture(g_picNumber.pPic);
}

//================================================
// ����: void paintPic(Picture * picture)
// ˵��: ����Ⱦ������һ��ͼƬ
// ����: picture ͼƬ�ṹ��ָ��
//================================================
void paintPic(Picture * picture)
{
    SDL_RenderCopy(g_pRenderer, picture->pPic,
        &(picture->srcRect), &(picture->dstRect));
}

//================================================
// ����: void paint(void)
// ˵��: ���ƴ���
//================================================
void paint(void)
{
    paintPic(&g_picBackGround_1);   // ���Ʊ���ͼƬ1
    paintSprite(0);     // ���Ƶ�1�㾫��
    paintPic(&g_picBackGround_2);   // ���Ʊ���ͼƬ2
    paintSprite(1);     // ���Ƶ�2�㾫��
    paintPic(&g_picBackGround_3);   // ���Ʊ���ͼƬ3
    paintSprite(2);     // ���Ƶ�3�㾫��
    paintPic(&g_picBackGround_4);   // ���Ʊ���ͼƬ4

    paintBlast();   // ����ը��Ч��

    paintInk();     // ����īˮЧ��

    paintScore();   // ���Ʒ���

    // ������Ⱦ��ͼ��
    SDL_RenderPresent(g_pRenderer);
}

//================================================
// ����: void paintSprite(int nLayer)
// ˵��: ���ƾ���
// ����: nLayer ���������Ĳ���
//================================================
void paintSprite(int nLayer)
{
    int i = 0;
    Picture * pPic = NULL;
    // ���ݲ���������ָ�������������
    for(i=nLayer*3; i<((nLayer+1)*3); i++)
    {
        if(g_spriteArr[i].type == TypeEmpty)        // ������
        {
            continue;
        }
        else if(g_spriteArr[i].type == TypeOctopus) // ��������
        {
            if(g_spriteArr[i].state == StateBeat)
            {
                pPic = &g_picSpriteOctBeat; // ͼƬ��Ϊ���㱻��ͼƬ
            }
            else
            {
                pPic = &g_picSpriteOctopus; // ͼƬ��Ϊ��ͨ����ͼƬ
            }          
        }
        else if(g_spriteArr[i].type == TypeBomb)    // ը����������
        {
            if(g_spriteArr[i].state == StateBeat)
            {
                pPic = &g_picSpriteBeat;    // ͼƬ��Ϊ���󱻴�ͼƬ
            }
            else
            {
                pPic = &g_picSpriteBomb;    // ͼƬ��Ϊը������ͼƬ
            }        
        }
        else                                        // ��ͨ��������
        {
            if(g_spriteArr[i].state == StateBeat)
            {
                pPic = &g_picSpriteBeat;    // ͼƬ��Ϊ���󱻴�ͼƬ
            }
            else
            {
                pPic = &g_picSpriteNormal;  // ͼƬ��Ϊ��ͨ����ͼƬ
            }
        }

        // ���ݾ���ļ������������㾫����ֵ�λ��
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
        
        // ���ƾ���ͼƬ
        paintPic(pPic); 
    }
}

//================================================
// ����: void paintBlast(void)
// ˵��: ���Ʊ�ը
//================================================
void paintBlast(void)
{
    int i = 0;
    Picture * pPic = NULL;
    for(i=0; i<9; i++)
    {
        // ��ը������Ǳ���
        if(g_spriteArr[i].type != TypeBomb
            || g_spriteArr[i].state != StateBeat) 
        {
            continue;
        }
        
        if(g_spriteArr[i].runningTimes < FRAMENUMBER_BEAT/2)
        {
            pPic = &g_picSpriteBlast1;
        }
        else
        {
            pPic = &g_picSpriteBlast2;
        }
        pPic->dstRect = g_spriteArr[i].initRect;
        paintPic(pPic);
    }
}

//================================================
// ����: void paintInk(void)
// ˵��: ����ī֭
//================================================
void paintInk(void)
{
    int i = 0;
    Picture * pPic = NULL;

    if(0 == g_nInkTimes)
    {
        return;
    }

    pPic = &g_picSpriteInk;

    // ����ͼƬ͸����
    SDL_SetTextureAlphaMod(pPic->pPic, 
        255 - 255/FRAMENUMBER_INK * g_nInkTimes); 

    // ����īˮͼƬ
    paintPic(pPic);

    g_nInkTimes++;
    if(g_nInkTimes > FRAMENUMBER_INK)
    {
        g_nInkTimes = 0;
    }
}

//================================================
// ����: void paintScore(void)
// ˵��: ��ӡ����
//================================================
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
        g_picNumber.dstRect.x = 
            (WINDOW_WIDTH - nScoreBit * NUMBER_DST_W) 
            / 2 + i*NUMBER_DST_W;

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