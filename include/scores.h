#ifndef __SCORES__
#define __SCORES__


/* ************************************************************************* */
/* ***************************		  INCLUDES			******************** */
/* ************************************************************************* */
#include "time.h"
#include <PA9.h>


/* ************************************************************************* */
/* ***************************		  CONSTANTS			******************** */
/* ************************************************************************* */
// Unique game details for online scoreboard
#define HIGHSCORE_ID	1
#define HIGHSCORE_KEY	"AKJSDhasod"


/* ************************************************************************* */
/* ***************************		  "OBJECTS"			******************** */
/* ************************************************************************* */
typedef struct
{
	u32		points;
	char*	name;
	bool	submitted;
//	Time 	time;
} Score;


/* ************************************************************************* */
/* ***************************		  VARIABLES			******************** */
/* ************************************************************************* */
extern Score highscore;


/* ************************************************************************* */
/* *********************		 FUNCTION DEFINITIONS		  ************** */
/* ************************************************************************* */
void getHighScores();
void submitScore();

#endif