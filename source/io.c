/* ************************************************************************* */
/* ***************************		  INCLUDES			******************** */
/* ************************************************************************* */
#include "io.h"
#include "game.h"
#include <PA9.h>


/* ************************************************************************* */
/* *****************************	   FUNCTIONS	  ********************** */
/* ************************************************************************* */
void print(u16 x, u16 y, char* message)
{
	PA_SmartText(SCREEN_TOP, (7*x), (11*y), SCREEN_WIDTH, SCREEN_HEIGHT, message, 1, 1, 0, 10000);
}
/*
void print(u16 x, u16 y, char* message)
{
	PA_SmartText(SCREEN_TOP, (5*x), (12*y), SCREEN_WIDTH, SCREEN_HEIGHT, message, 1, 2, 0, 10000);
}
*/

void clear_text()
{
	PA_SetBgPalCol(SCREEN_TOP, 1, PA_RGB(31, 31, 31));
	PA_Init8bitBg(SCREEN_TOP, 3);
}
