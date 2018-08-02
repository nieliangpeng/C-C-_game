/***************************************************
 *  文件：Solitaire.c
 *  说明：程序主函数所在源文件
 *  作者：
 *  日期：
 ***************************************************/
 
#include "SolitaireLogic.h"

int main(void)
{
    /* 初始化游戏 */
    if(logicInit() != 0)
    {
        return -1;
    };

    /* 开始游戏 */
    logicStart();

    /* 结束游戏 */
    logicEnd();

    return 0;
}