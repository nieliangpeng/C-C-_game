#ifndef _SOLITAIRE_LOGIC_H_
#define _SOLITAIRE_LOGIC_H_

#include "SolitaireData.h"

/* ��Ϸ��ʼ�� */
int logicInit(void);

/* ��Ϸ��ʼ */
void logicStart(void);

/* ��Ϸ���� */
void logicEnd(void);

/* ��Ϸ���� */
void logicDeal(void);

/* ����ͨ��Ԫ����˿� */
void logicUnitDealPoker(Unit * pUnit, Poker * pPoker);

/* ����������¼� */
void logicMouseButtonEvent(const SDL_Event * pEvent);

/* ��������ƶ��¼� */
void logicMouseMotionEvent(const SDL_Event * pEvent);

/* �ж�������Ӧ���˿��� */
Poker * logicIsPoker(int nX, int nY);

/* �ж�������Ӧ�ĵ�Ԫ */
Unit * logicIsUnit(int nX, int nY);

/* ��ȡѡ�е��˿�����  */
void logicGetSelectPokers(Poker * pPoker);

/* ���Խ������ƶ���ĳ��Ԫ */
int logicTryMovingThePokers(Unit * pUnit, int nIsAction);

#endif // _SOLITAIRE_LOGIC_H_