#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "data.h"

int initSDL(void);
void freeSDL(void);
Picture loadPic(const char * path);
void setPicDstRect(Picture * picture, int x, int y,int w, int h);
void setPicSrcRect(Picture * picture, int x, int y,int w, int h);
int loadPicResources(void);
void freePicResources(void);
void paintPic(Picture * picture);
void paint(void);
void paintSprite(int nLayer);
void paintBlast(void);
void paintInk(void);
void paintScore(void);
void paint(void);
void paintSprite(int nLayer);
void paintScore(void);
#endif