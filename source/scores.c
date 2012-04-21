/* ************************************************************************* */
/* ***************************		  INCLUDES			******************** */
/* ************************************************************************* */
// Library
#include <PA9.h>

// Includes
#include "game.h"
#include "scores.h"


/* ************************************************************************* */
/* ***************************		  VARIABLES			******************** */
/* ************************************************************************* */
Score highscore;


/* ************************************************************************* */
/* *****************************	   FUNCTIONS	  ********************** */
/* ************************************************************************* */
/**
 * Gets high scores from online scoreboard, displays them on top screen.
 */
void getHighScores()
{
	// Webby Stuff.
	char* url="http://www.deanrather.com/highscores/retrieve.php";
	url = strcat(url, "?game=");
	url = strcat(url, (char*)(int)HIGHSCORE_ID);
	PA_OutputSimpleText(1,1,1,url);
	
	char* result = malloc(256*256);
	PA_GetHTTP(result,url);
	PA_OutputSimpleText(1,1,5,result);
	
	// result="#,Score,Player,Time\r\n1,70000000,dean,6 hours ago.\r\n2,70000000,dean,6 hours ago.\r\n3,7000000,dean,6 hours ago.\r\n4,700000,dean,6 hours ago.\r\n5,70000,dean,6 hours ago.\r\n6,22345,Grimey,10 hours ago.\r\n7,16345,Fred,10 hours ago.\r\n8,12345,Joe,10 hours ago.\r\n9,7000,dean,6 hours ago.\r\n10,7000,dean,6 hours ago.";
	const u8 SCOREBOARD_HEIGHT = 10;
	const u8 SCOREBOARD_WIDTH = 31;
	char scoreboard[SCOREBOARD_HEIGHT][SCOREBOARD_WIDTH];
	
	int row = 0;
	int col = 0;
	int i = 0;
	for(row=0; row<SCOREBOARD_HEIGHT; row++)
	{
		for(col=0; col<SCOREBOARD_WIDTH; col++)
		{
			switch(result[i])
			{
				case '\0':	break;
				case '\r':	break;
				case ',':	scoreboard[row][col]='\t';	break;
				case '\n':	row++;						break;
				default:	scoreboard[row][col]=result[i];
			}
			i++;
		}
		PA_OutputSimpleText(SCREEN_TOP,0,row+9,scoreboard[row]);
	}
}

/**
 * Submits your score to the online scoreboard, and prints your ranking
 */
void submitScore()
{
	char* buffer = malloc(256*256);
	PA_OutputSimpleText(SCREEN_TOP,0,6,"Fetching Data");
	PA_GetHTTP(buffer,"http://delfare.pizz.biz/getip.php3");
	PA_OutputSimpleText(SCREEN_TOP,0,6,buffer);
	PA_GetHTTP(buffer,"http://www.deanrather.com/highscores/index.html"); PA_OutputSimpleText(SCREEN_TOP,0,6,"Retrieved Data");
	PA_OutputSimpleText(SCREEN_TOP,0,6,buffer); // Should output "Server Online"
	
	char* url="http://www.deanrather.com/highscores/add.php";
	url = strcat(url, "?game=");
	url = strcat(url, (char*)(int)HIGHSCORE_ID);
	url = strcat(url, "&key=");
	url = strcat(url, (char*)HIGHSCORE_KEY);
	url = strcat(url, "&score=");
	url = strcat(url, (char*)(int)game.score);
	url = strcat(url, "&name=");
	url = strcat(url, (char*)PA_UserInfo.Name);
	
	buffer = malloc(256*256);
	PA_GetHTTP(buffer,url);
	
	/*
	//char* buffer="SUCCESS: 32";
	u16 i = 0;
	u16 j = 0;
	while(buffer[i] != ':') i++;
	i+= 2;
	while(buffer[i] != '\0')
	{
		rank[j] = buffer[i];
		i++;
		j++;
	}
	*/
	
	PA_OutputSimpleText(SCREEN_TOP,0,7,buffer);
}
