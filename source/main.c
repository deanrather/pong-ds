/* ************************************************************************* */
/* ***************************		  INCLUDES			******************** */
/* ************************************************************************* */
// Libraries
#include <PA9.h>

// Includes
#include "game.h"
#include "pong.h"
#include "time.h"
#include "scores.h"
#include "credits.h"
#include "io.h"

// Graphics
#include "gfx/all_gfx.c"
#include "gfx/all_gfx.h"

// Sound Effects
#include "sfx_ping.h"
#include "sfx_pong.h"
#include "sfx_win.h"
#include "sfx_lose.h"
#include "sfx_bounce.h"

// Music
#include "music_music.h"


/* ************************************************************************* */
/* *****************************	   FUNCTIONS	  ********************** */
/* ************************************************************************* */
/**
 * Entry point of program.
 */
int main(int argc, char ** argv)
{
	init();
	while(true) // Keep app running
	{
		setupGame();
		while(game.lives) // New Round
		{
			setupRound();
			while(!game.gameover) // Neither player missed the ball
			{
				getInput();
				processAI();
				moveBall();
				displayOutput();
				
				// Sleep
				PA_CheckLid();
				PA_WaitForVBL();
			}
			postRound();
		}
		postGame();
	}
	return 0;
}

/**
 * Inits things for the game
 */
void init()
{
	// Init PA
	PA_Init();
	PA_InitVBL();
	
    // Init Sound
    PA_InitSound();
    
	// Init Text
	PA_InitText(SCREEN_TOP, 0);
	
//	debug();
	
	// Roll pre-game credits
	if(false)
	{
		// Code I wish I could put into rollPreCredits();
		u8 counter=0; // used to count till timeout
		
		// Text
		clear_text();
		print(5,3,PRECREDITS);
		
		// logo on bottom screen
		PA_EasyBgLoad(SCREEN_BOTTOM,3, splash_pong);
		
		// Wait & fade out
		counter = 0;
		PA_WaitFor(Pad.Newpress.A || Pad.Newpress.Start || Stylus.Newpress || counter++>IDLETIME);
		fadeOut();
		
		// run DSX/Comp screen
		PA_EasyBgLoad(SCREEN_TOP,	3, splash_comp);
		PA_EasyBgLoad(SCREEN_BOTTOM,3, splash_comp2);
		
		// Wait & fade out
		counter = 0;
		PA_WaitFor(Pad.Newpress.A || Pad.Newpress.Start || Stylus.Newpress || counter++>IDLETIME);
		fadeOut();
		
		// run PA_Lib & Eclipse screens
		PA_EasyBgLoad(SCREEN_TOP,	3, splash_palib);
		PA_EasyBgLoad(SCREEN_BOTTOM,3, splash_eclipse);
		
		// Wait & fade out
		counter = 0;
		PA_WaitFor(Pad.Newpress.A || Pad.Newpress.Start || Stylus.Newpress || counter++>IDLETIME);
		fadeOut();
		//rollPreCredits();
	}
	
	PA_InitText(SCREEN_TOP, 0);
	PA_SetTextCol(SCREEN_TOP, 0, 0, 0);
	
	// Some variables
	game.smartAI	= 0;
	game.score		= 0;
	game.lives		= 3;
	game.rank		= "";
	game.gameover	= false;
	
	// Load Palletes
	PA_LoadSpritePal(SCREEN_TOP,	1,	(void*)ball_Pal);
	PA_LoadSpritePal(SCREEN_BOTTOM,	2,	(void*)ball_Pal);
	PA_LoadSpritePal(SCREEN_TOP,	3,	(void*)paddle_a_Pal);
	PA_LoadSpritePal(SCREEN_BOTTOM,	4,	(void*)paddle_b_Pal);
	
	// create sprites
	PA_CreateSprite(SCREEN_BOTTOM,	BALL_BOTTOM,	(void*)ball_Sprite,		OBJ_SIZE_16X16, 1, 1, 	-BALL_WIDTH,	-BALL_HEIGHT);
	PA_CreateSprite(SCREEN_TOP,		BALL_TOP,		(void*)ball_Sprite,		OBJ_SIZE_16X16, 1, 2, 	-BALL_WIDTH,	-BALL_HEIGHT);
	PA_CreateSprite(SCREEN_BOTTOM,	PADDLE1,		(void*)paddle_a_Sprite,	OBJ_SIZE_32X16, 1, 3,	-PADDLE_WIDTH,	-PADDLE_HEIGHT);
	PA_CreateSprite(SCREEN_TOP,		PADDLE2,		(void*)paddle_b_Sprite,	OBJ_SIZE_32X16, 1, 4,	-PADDLE_WIDTH,	-PADDLE_HEIGHT);
	
	// create backgrounds
	PA_EasyBgLoad(SCREEN_TOP,		2, background_top);
	PA_EasyBgLoad(SCREEN_BOTTOM,	2, background_bottom);
	
	// Init high score to 0. (Should probably read from a save)
	highscore.points	= 0;
	highscore.name		= "No one";
	highscore.submitted	= false;
}

void setupGame()
{
	game.score = 0;
	game.lives = 3;
	PA_PlayMod(music_music);
}

void setupRound()
{
	// Clear Screen
	PA_ClearTextBg(SCREEN_TOP);
	
	// Reset paddles and ball
	PA_SetSpriteXY(SCREEN_BOTTOM,	BALL_BOTTOM,	-BALL_WIDTH, -BALL_HEIGHT);
	PA_SetSpriteXY(SCREEN_TOP,		BALL_TOP,		-BALL_WIDTH, -BALL_HEIGHT);
	
	ball.x 	= SCREEN_WIDTH/2-BALL_WIDTH/2;
	ball.y	= SCREEN_HEIGHT-BALL_HEIGHT/2;
	ball.vx = 1+((float)PA_RandMax(10)/10);
	ball.vy = -2-((float)PA_RandMax(5*game.score)/10);
	ball.ax = 0;
	ball.ay = 0;
	
	game.smartAI = 0;
	testBall.x = 0;
	testBall.y = 0;
	testBall.vx = 0;
	testBall.vy = 0;
	testBall.ax = 0;
	testBall.ay = 0;
	
	if(PA_RandMax(1)) ball.vx = -ball.vx;
	
	theirPaddle.x = SCREEN_WIDTH/2-PADDLE_WIDTH/2;
	theirPaddle.y = 0;
	
	myPaddle.x = SCREEN_WIDTH/2-PADDLE_WIDTH/2;
	myPaddle.y = SCREEN_HEIGHT-PADDLE_HEIGHT;
	
	game.gameover = false;
}

void getInput()
{
	// Glitch Button: L+R+Select
	if(Pad.Held.Left && Pad.Held.Right && Pad.Held.Select) game.gameover=true;

	// Player X
	if(Stylus.Held)
	{
		if(Stylus.X-PADDLE_WIDTH/2 > myPaddle.x) myPaddle.x += PADDLE_SPEED;
		if(Stylus.X-PADDLE_WIDTH/2 < myPaddle.x) myPaddle.x -= PADDLE_SPEED;
	}
	else
	{
		if((Pad.Held.Left || Pad.Held.L) && myPaddle.x>0)
		{
			myPaddle.x -= PADDLE_SPEED;
		}
		if((Pad.Held.Right || Pad.Held.R) && myPaddle.x<SCREEN_WIDTH-PADDLE_WIDTH)
		{
			myPaddle.x += PADDLE_SPEED;
		}
	}
	
	// Player Y
//	if(Stylus.Held)
//	{
//		if(Stylus.Y-PADDLE_WIDTH/2 > myPaddle.y) myPaddle.y += PADDLE_SPEED;
//		if(Stylus.Y-PADDLE_WIDTH/2 < myPaddle.y) myPaddle.y -= PADDLE_SPEED;
//	}
}

void displayOutput()
{
	// Paddles
	PA_SetSpriteXY(SCREEN_BOTTOM,	PADDLE1,		myPaddle.x,		myPaddle.y);
	PA_SetSpriteXY(SCREEN_TOP,		PADDLE2,		theirPaddle.x,	theirPaddle.y);
	
	// Ball
	if(ball.y > SCREEN_HEIGHT-BALL_HEIGHT-1)
		PA_SetSpriteXY(SCREEN_BOTTOM, BALL_BOTTOM, ball.x, ball.y-SCREEN_HEIGHT);
	else
		PA_SetSpriteXY(SCREEN_BOTTOM, BALL_BOTTOM, -BALL_WIDTH, -BALL_HEIGHT);
		
	if(ball.y < SCREEN_HEIGHT+BALL_HEIGHT-1)
		PA_SetSpriteXY(SCREEN_TOP, BALL_TOP, ball.x, ball.y);
	else
		PA_SetSpriteXY(SCREEN_TOP, BALL_BOTTOM, -BALL_WIDTH, -BALL_HEIGHT);
	
	// Text
	//if(ball.vy>0) PA_OutputSimpleText(SCREEN_TOP, 0, 1, "PING");
	//else PA_OutputSimpleText(SCREEN_TOP,0,1,"PONG");
	
	PA_OutputText(SCREEN_TOP, 0, 2, "Score: %d", game.score);
	PA_OutputText(SCREEN_TOP, 0, 3, "Balls: %d", game.lives);
	
	/*
	PA_OutputText(SCREEN_TOP, 0, 2, "Ball X: %d ,Y: %d ", ball.x, ball.y);
	PA_OutputText(1,0,3,"Stylus X:%d, Y:%d", Stylus.X, Stylus.Y);
	PA_OutputText(1,0,4,"Ball V X:%f5, Y:%f5", ball.vx, ball.vy);
	*/
}


void processAI()
{
	//TODO merge aiS
	if(ball.y < SCREEN_HEIGHT+(game.score*2) && ball.vy < 0) // Ball approaches enemy
	{
		switch(game.smartAI)
		{
			case 3: // Go wait for the ball
				if(testBall.x > theirPaddle.x) theirPaddle.x += PADDLE_SPEED;
				if(testBall.x < theirPaddle.x) theirPaddle.x -= PADDLE_SPEED;
				break;
			case 1: // Chase the ball slowly
				if(ball.x > theirPaddle.x) theirPaddle.x += PADDLE_SPEED*0.75;
				if(ball.x < theirPaddle.x) theirPaddle.x -= PADDLE_SPEED*0.75;
				break;
			default: // Chase the ball
				if(ball.x > theirPaddle.x) theirPaddle.x += PADDLE_SPEED;
				if(ball.x < theirPaddle.x) theirPaddle.x -= PADDLE_SPEED;
		}
	}else{
		switch(game.smartAI)
		{
			case 0: // Chase the ball
				if(ball.x > theirPaddle.x) theirPaddle.x += PADDLE_SPEED;
				if(ball.x < theirPaddle.x) theirPaddle.x -= PADDLE_SPEED;
				break;
			
			case 1: // Return to center
				if(theirPaddle.x < SCREEN_WIDTH/2) theirPaddle.x += PADDLE_SPEED;
				if(theirPaddle.x > SCREEN_WIDTH/2) theirPaddle.x -= PADDLE_SPEED;
				break;
				
			case 2: // move opposite me
				if(theirPaddle.x < SCREEN_WIDTH-myPaddle.x) theirPaddle.x += PADDLE_SPEED;
				if(theirPaddle.x > SCREEN_WIDTH-myPaddle.x) theirPaddle.x -= PADDLE_SPEED;
				break;
			
			default: // Stay where they are
				break;
		}
	}
}

void postRound()
{
	if(ball.vy > 0) game.lives--;
	if(game.lives)
	{
		if(ball.vy > 0) // I lose
		{
			PA_OutputSimpleText(SCREEN_TOP,0,6,"YOU LOSE THIS ROUND");
			if(game.lives>1) PA_OutputText(SCREEN_TOP,0,7,"ONLY %d BALLS LEFT!", game.lives);
			else PA_OutputSimpleText(SCREEN_TOP,0,7,"LAST BALL");
		}else{ // They lose
			game.score++;
			if(game.lives<5) game.lives++;
			PA_OutputSimpleText(SCREEN_TOP,0,6,"YOU WIN THIS ROUND");
			if(game.score>1) PA_OutputText(SCREEN_TOP,0,7,"YOU HAVE %d POINTS!", game.score);
			else PA_OutputSimpleText(SCREEN_TOP,0,7,"YOU EARNED A POINT & A BALL!");
		}
		
		PA_OutputSimpleText(SCREEN_TOP,0,12,"Press A to Play Again");
		while(!Pad.Newpress.A && !Stylus.Newpress)
		{
			if(Pad.Newpress.X) PA_SetDSLBrightness(0);
			if(Pad.Newpress.Y) PA_SetDSLBrightness(1);
			if(Pad.Newpress.B) PA_SetDSLBrightness(2);
			if(Pad.Newpress.Start) PA_SetDSLBrightness(3);
			
			// Sleep
			PA_CheckLid();
			PA_WaitForVBL();
		}
	}
}

void postGame()
{
	PA_PauseMod(1);
	bool submitted = false;
	while(!Pad.Newpress.Start && !Stylus.DblClick && !submitted)
	{
		PA_ClearTextBg(SCREEN_TOP);
		PA_OutputSimpleText(SCREEN_TOP,0,0,"GAME OVER");
		PA_OutputText(SCREEN_TOP,0,1,"YOUR SCORE: %d", game.score);
		
		if(game.score<highscore.points)
		{
			PA_OutputText(SCREEN_TOP,0,2,"%s's High Score: %d", highscore.name, highscore.points);
			PA_OutputSimpleText(SCREEN_TOP,0,4,"Press Start to Play Again");
		}else{
			PA_OutputText(SCREEN_TOP,0,2,"NEW HIGH SCORE!!!");
			highscore.points=game.score;
			highscore.name=(char*)PA_UserInfo.Name;
			PA_OutputSimpleText(SCREEN_TOP,0,3,"Press Y To submit score online.");
			PA_OutputSimpleText(SCREEN_TOP,0,4,"Press Start to Play Again");
			if(Pad.Newpress.Y)
			{
				PA_OutputSimpleText(SCREEN_TOP,0,5,"Ranking globally...");
				
				// Init Network
				PA_InitWifi();
			    if(PA_ConnectWifiWFC())
			    {
			    	submitScore();
					getHighScores();
					submitted=true;
					Wifi_DisconnectAP();
			    }else{
			    	PA_OutputSimpleText(SCREEN_TOP,0,6,"Wifi Connection Failed.");
			    }
				Wifi_DisableWifi();
			}
		}
		// Sleep
		PA_CheckLid();
		PA_WaitForVBL();
	}
}
