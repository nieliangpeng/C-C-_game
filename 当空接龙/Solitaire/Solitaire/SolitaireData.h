#ifndef _SOLITAIRE_DATA_H_
#define _SOLITAIRE_DATA_H_

#include "SDL.h"
#include "SDL_image.h"

#define WINDOW_WIDTH    1000    // ���ڿ��
#define WINDOW_HEIGHT   600     // ���ڸ߶�
#define POKER_WIDTH     85      // �˿˿��
#define POKER_HEIGHT    120     // �˿˸߶�
#define POKER_SPACE     20      // ��ͨ��Ԫ���˿�Y����
#define UNIT_SPACE      30      // ��ԪX����
#define DEAL_POINT_X    (WINDOW_WIDTH-POKER_WIDTH)/2    // ����λ��X����
#define DEAL_POINT_Y    (WINDOW_HEIGHT-POKER_HEIGHT-30) // ����λ��Y����

typedef struct unit Unit;

/** �˿˿��ƿ�ɫ **/
typedef enum pokerColor
{
    Heart = 0,          // ����
    Spade,              // ����
    Diamond,            // ����
    Club                // ÷��
} PokerColor;

/** �˿˿������꼰���� **/
typedef struct pokerRect
{
    int x;              // x����
    int y;              // y����
    unsigned int width; // ���
    unsigned int height;// �߶�
} PokerRect;

/** �˿˿��� **/
typedef struct poker
{
    unsigned int nNum;  // ��������
    PokerColor color;   // ���ƿ�ɫ
    PokerRect rect;     // ����
    Unit * pUnit;       // �˿���������Ԫ
} Poker;

/** ��ѡ�˿��ƽṹ�� **/
typedef struct selectPoker
{
    unsigned int nCount;    // ��ǰѡ����˿�����
    Poker * arrPoker[13];   // ��ǰѡ����˿�����
} SelectPoker;

/** ��Ԫ���� **/
typedef enum unitType
{
    NormalUnit = 0,     // ������Ԫ
    UseUnit,            // ���õ�Ԫ
    RetrieveUnit        // ���յ�Ԫ
} UnitType;

/** ��Ԫ **/
typedef struct unit
{
    UnitType type;          // ��Ԫ����
    Poker * arrPoker[19];   // �˿�������
    unsigned int nCurCount; // ��ǰ�˿�����
    int nX;                 // ��ԪX����
    int nY;                 // ��ԪY����
} Unit;

#endif // _SOLITAIRE_DATA_H_