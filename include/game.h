#ifndef __GAME__
#define __GAME__


/* ************************************************************************* */
/* ***************************		  INCLUDES			******************** */
/* ************************************************************************* */
#include <PA9.h>


/* ************************************************************************* */
/* ***************************		  CONSTANTS			******************** */
/* ************************************************************************* */
//const u16 SCREEN_HEIGHT	= 192; // Defined in PA_Lib or LibNDS...
//const u16 SCREEN_WIDTH	= 256;

// Which screen PA_Lib refers to as what
enum {SCREEN_BOTTOM, SCREEN_TOP};

// Which pallettes things are stored in
enum
{
	PALLETTE_TOP_BG,
	PALLETTE_BOTTOM_BG,
	PALLETTE_TOP_PADDLE,
	PALLETTE_BOTTOM_PADDLE,
	PALLETTE_BALL
};

// Sprite IDs
enum
{
	BALL_TOP,
	BALL_BOTTOM,
	PADDLE1,
	PADDLE2
};


/* ************************************************************************* */
/* ***************************		  "OBJECTS"			******************** */
/* ************************************************************************* */
typedef struct
{
	u8		smartAI;	// Artificial Intelligence Level
	u32		score;		// Players my score
	u32		highscore;	// Players my score
	u8		lives;		// Number of lives I have
	char*	rank;		// Global ranking position
	bool	gameover;	// Keeps a round in action
} Game;


/* ************************************************************************* */
/* ***************************		  VARIABLES			******************** */
/* ************************************************************************* */
extern Game game;


/* ************************************************************************* */
/* *********************		 FUNCTION DEFINITIONS		  ************** */
/* ************************************************************************* */
void print(u16 x, u16 y, char* message);
void clear_text();
void init();
void setupGame();
void setupRound();
void getInput();
void processAI();
void displayOutput();
void postRound();
void postGame();
void debug();


#endif
