/* ************************************************************************* */
/* ***************************		  INCLUDES			******************** */
/* ************************************************************************* */
// Library
#include <PA9.h>

// Includes
#include "game.h"
#include "pong.h"


/* ************************************************************************* */
/* ***************************		  VARIABLES			******************** */
/* ************************************************************************* */
Ball 	ball;
Ball	testBall;
Paddle	theirPaddle;
Paddle	myPaddle;


/* ************************************************************************* */
/* *****************************	   FUNCTIONS	  ********************** */
/* ************************************************************************* */
void moveBall(void)
{
//	PA_OutputText(SCREEN_TOP, 0, 15, "X:%d, Y:%d", ball.x, ball.y);
//	PA_OutputText(SCREEN_TOP, 0, 16, "vX:%f3, vY:%f3", ball.vx, ball.vy);
//	PA_OutputText(SCREEN_TOP, 0, 17, "aX:%f3, aY:%f3", ball.ax, ball.ay);
	
	// Process acceleration
	//ball.vx += ball.ax;
	//ball.vy += ball.ay;
	
	// Bounce off walls
	if(ball.x+ball.vx+BALL_WIDTH > SCREEN_WIDTH || ball.x+ball.vx < 0)
	{
		ball.vx = -ball.vx;
		//PA_PlaySimpleSound(3, bounce);
	}
	
	// a goal?
	//if(ball.y+ball.vy<0 || ball.y+ball.vy>(SCREEN_HEIGHT*2)-BALL_HEIGHT) gameover=true;
	
	// My Paddle
	if(ball.y+BALL_HEIGHT<myPaddle.y+SCREEN_HEIGHT && ball.y+ball.vy+BALL_HEIGHT > myPaddle.y+SCREEN_HEIGHT)
	{
		if(ball.x+BALL_WIDTH+ball.vx < myPaddle.x || ball.x+ball.vx > myPaddle.x+PADDLE_WIDTH)
		{
			// I lose.
			//PA_PlaySimpleSound(5, lose);
			game.gameover = true;
		}else{ // I hit
			//PA_PlaySimpleSound(1, pong);
			ball.vy = -ball.vy;
			
			// Speed Ball Up
			ball.vx *= 1.2;
			ball.vy *= 1.2;
			
			// Spin Ball
			//if(Stylus.Held) ball.vx += (Stylus.X - myPaddle.x) / 100;
			if((Stylus.Held && Stylus.X < myPaddle.x) || Pad.Held.Left)		ball.vx-=1;
			if((Stylus.Held && Stylus.X > myPaddle.x) || Pad.Held.Right)	ball.vx+=1;
			//if((Stylus.Held && Stylus.X < myPaddle.x) || Pad.Held.Left) ball.ax-=0.1;
			//if((Stylus.Held && Stylus.X > myPaddle.x) || Pad.Held.Right) ball.ax+=0.1;
			
			// Speed ball more
			//if(Stylus.Held) ball.vy += (Stylus.Y - myPaddle.y) / 100;
			
			// Give them AI
			game.smartAI=PA_RandMax(3);
			if(game.smartAI == 3)
			{
				testBall = ball;
				while(testBall.vy < 0 && testBall.y > PADDLE_HEIGHT)
				{
					if(testBall.x+testBall.vx+BALL_WIDTH > SCREEN_WIDTH || testBall.x+testBall.vx < 0) testBall.vx = -testBall.vx;
					testBall.y += testBall.vy;
					testBall.x += testBall.vx;
				}
				// Fudge accuracy
				testBall.x += -(BALL_WIDTH)+PA_RandMax(2*BALL_WIDTH);
			}
		}
	}
	
	// Their Paddle
	if(ball.y+ball.vy < theirPaddle.y+PADDLE_HEIGHT)
	{
		if(ball.x+BALL_WIDTH+ball.vx < theirPaddle.x || ball.x+ball.vx > theirPaddle.x+PADDLE_WIDTH)
		{
			// They lose.
			//PA_PlaySimpleSound(5, win);
			game.gameover = true;
		}else{
			//PA_PlaySimpleSound(2, pong);
			ball.vy = -ball.vy;
		}
	}
	
	// Move the ball
	ball.x += ball.vx;
	ball.y += ball.vy;
}
