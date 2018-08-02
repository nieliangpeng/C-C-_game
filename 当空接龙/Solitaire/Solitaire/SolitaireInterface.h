#ifndef _SOLITAIRE_INTERFACE_H_
#define _SOLITAIRE_INTERFACE_H_

#include "SolitaireData.h"

/* ��ʼ������ */
int interfaceInit(void);

/* ���ٴ��� */
void interfaceDestroy(void);

/* ����ͼƬ·������ͼƬ */
SDL_Texture * interfaceLoadImage(const char * pFilePath);

/* ���ƴ��� */
void interfacePaint(int nIsRef);

/* ���ƴ��ڱ��� */
void interfacePaintBackground(void);

/* ������ͨ��Ԫ���˿��� */
void interfacePaintNormalUnit(void);

/* ���ƻ��յ�Ԫ���˿��� */
void interfacePaintRetrieveUnit(void);

/* ���ƿ��õ�Ԫ���˿��� */
void interfacePaintUseUnit(void);

/* �����˿��Ʊ���ͼƬ */
void interfacePaintPokerBack(void);

/* ���������ƶ����˿����� */
void interfacePaintMovePokers(void);

/* ����Ⱦ���л���ͼ�� */
void interfaceDrawImage(SDL_Texture * pTexture, SDL_Renderer * pRenderer, 
                        SDL_Rect * pSrcRect, SDL_Rect * pDstRect);

/* �˿����ƶ����� */
void interfacePokerMove(int nSrcX, int nSrcY, 
                        int nDstX, int nDstY, 
                        const Poker * pPoker, 
                        int nMoveCount, int nIsDeal);

/* ��ȡ�˿�����ԭͼ�е�������Ϣ */
SDL_Rect interfaceGetPokerRect(const Poker * pPoker);

#endif // _SOLITAIRE_INTERFACE_H_