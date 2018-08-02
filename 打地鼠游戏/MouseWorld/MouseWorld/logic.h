#ifndef _LOGIC_H_
#define _LOGIC_H_

#include "interface.h"

int init(void);
void gameFree(void);
Uint32 timerFun(Uint32 interval, void * param);
void start(void);
void initSprite(void);
void spriteRun(void);
void mouseButtonEvent(const SDL_Event * pEvent);
void updateScore(SpriteType type);
#endif  