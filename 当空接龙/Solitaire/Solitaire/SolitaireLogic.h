#ifndef _SOLITAIRE_LOGIC_H_
#define _SOLITAIRE_LOGIC_H_

#include "SolitaireData.h"

/* 游戏初始化 */
int logicInit(void);

/* 游戏开始 */
void logicStart(void);

/* 游戏结束 */
void logicEnd(void);

/* 游戏发牌 */
void logicDeal(void);

/* 往普通单元添加扑克 */
void logicUnitDealPoker(Unit * pUnit, Poker * pPoker);

/* 处理鼠标点击事件 */
void logicMouseButtonEvent(const SDL_Event * pEvent);

/* 处理鼠标移动事件 */
void logicMouseMotionEvent(const SDL_Event * pEvent);

/* 判断坐标点对应的扑克牌 */
Poker * logicIsPoker(int nX, int nY);

/* 判断坐标点对应的单元 */
Unit * logicIsUnit(int nX, int nY);

/* 获取选中的扑克牌组  */
void logicGetSelectPokers(Poker * pPoker);

/* 尝试将牌组移动到某单元 */
int logicTryMovingThePokers(Unit * pUnit, int nIsAction);

#endif // _SOLITAIRE_LOGIC_H_