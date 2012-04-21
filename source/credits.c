/* ************************************************************************* */
/* ***************************		  INCLUDES			******************** */
/* ************************************************************************* */
// Lib
#include <PA9.h>

// Includes
#include "credits.h"
#include "game.h"


/* ************************************************************************* */
/* *****************************	   FUNCTIONS	  ********************** */
/* ************************************************************************* */
void rollPreCredits()
{
	
}

void rollCredits()
{
	
}

void fadeOut()
{
	s8 brightness = 0;
	while(brightness-->-32)
	{
		PA_SetBrightness(SCREEN_TOP,	brightness);
		PA_SetBrightness(SCREEN_BOTTOM,	brightness);
		if(Pad.Newpress.A || Pad.Newpress.Start || Stylus.Newpress) break;
		PA_WaitForVBL();
	}
	PA_ClearTextBg(SCREEN_TOP);
	PA_SetBrightness(SCREEN_TOP, 0);
	PA_SetBrightness(SCREEN_BOTTOM, 0);
	PA_ResetBgSys();
}
