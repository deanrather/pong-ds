/* ************************************************************************* */
/* ***************************		  INCLUDES			******************** */
/* ************************************************************************* */
#include "game.h"
#include <PA9.h>


/* ************************************************************************* */
/* ***************************		  VARIABLES			******************** */
/* ************************************************************************* */
Game game;

/* ************************************************************************* */
/* *****************************	   FUNCTIONS	  ********************** */
/* ************************************************************************* */
void debug()
{
	PA_OutputSimpleText(1, 0, 0, "Lets go online...");
	PA_InitWifi();
    PA_ConnectWifiWFC();
	
	char* buffer = malloc(256*256);
	PA_GetHTTP(buffer,"http://delfare.pizz.biz/getip.php3");
	PA_OutputSimpleText(1, 0, 1, buffer);
	
	PA_GetHTTP(buffer,"http://deanrather.com/index.php");
	PA_OutputSimpleText(1, 0, 2, buffer);
	
	PA_GetHTTP(buffer,"http://deanrather.com/highscores/");
	PA_OutputSimpleText(1, 0, 3, buffer);
	
	PA_OutputSimpleText(1, 0, 4, "Wow, That was fun!!");
	PA_WaitFor(Pad.Newpress.Start);
}

