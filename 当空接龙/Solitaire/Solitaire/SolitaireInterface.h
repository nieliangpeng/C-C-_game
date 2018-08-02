#ifndef _SOLITAIRE_INTERFACE_H_
#define _SOLITAIRE_INTERFACE_H_

#include "SolitaireData.h"

/* 初始化窗口 */
int interfaceInit(void);

/* 销毁窗口 */
void interfaceDestroy(void);

/* 根据图片路径加载图片 */
SDL_Texture * interfaceLoadImage(const char * pFilePath);

/* 绘制窗口 */
void interfacePaint(int nIsRef);

/* 绘制窗口背景 */
void interfacePaintBackground(void);

/* 绘制普通单元的扑克牌 */
void interfacePaintNormalUnit(void);

/* 绘制回收单元的扑克牌 */
void interfacePaintRetrieveUnit(void);

/* 绘制可用单元的扑克牌 */
void interfacePaintUseUnit(void);

/* 绘制扑克牌背面图片 */
void interfacePaintPokerBack(void);

/* 绘制正在移动的扑克牌组 */
void interfacePaintMovePokers(void);

/* 往渲染器中绘制图像 */
void interfaceDrawImage(SDL_Texture * pTexture, SDL_Renderer * pRenderer, 
                        SDL_Rect * pSrcRect, SDL_Rect * pDstRect);

/* 扑克牌移动动画 */
void interfacePokerMove(int nSrcX, int nSrcY, 
                        int nDstX, int nDstY, 
                        const Poker * pPoker, 
                        int nMoveCount, int nIsDeal);

/* 获取扑克牌在原图中的区域信息 */
SDL_Rect interfaceGetPokerRect(const Poker * pPoker);

#endif // _SOLITAIRE_INTERFACE_H_