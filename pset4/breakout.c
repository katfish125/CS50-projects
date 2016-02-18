//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

//height and width of paddle and blocks
#define BHEIGHT 5
#define BWIDTH 30

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;
    updateScoreboard(window, label, 0);

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // define ball's velocity
    double xvelocity = 2.5 * drand48();
    double yvelocity = 2.5;

    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // TODO
        //set paddle to follow mouse
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - 25;
                setLocation(paddle, x, 500);
            }
        }
        
        // move ball
        move(ball, xvelocity, yvelocity);
        
        // bounce from side walls
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            xvelocity = -xvelocity;
        }
        else if (getX(ball) <= 0)
        {
            xvelocity = -xvelocity;
        }
        
        // bounce from ceiling or floor
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives--;
            removeGWindow(window, ball);
            ball = initBall(window);
            waitForClick();
            continue;
        }
        else if (getY(ball) <= 0)
        {
            yvelocity = -yvelocity;
        }
        
        // detect collision between objects
        GObject object = detectCollision(window, ball);
        
        if (object != NULL)
        {
            // bounce off paddle
            if (object == paddle)
            {
                if (yvelocity > 0.0)
                {
                    yvelocity = -yvelocity;
                }
            }
            
            // bounce off and remove block
            else if (strcmp(getType(object), "GRect") == 0)
            {
                yvelocity = -yvelocity;
                bricks--;
                updateScoreboard(window, label, 50 - bricks);
                removeGWindow(window, object);
            }
        }
        
        pause(10);
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            GRect block = newGRect(5+40*i, 50+15*j, BWIDTH, BHEIGHT);
            add(window, block);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(200 - RADIUS, 300 - RADIUS, 2*RADIUS, 2*RADIUS);
    setFilled(ball, true);
    setFillColor(ball, "RED");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(185, 500, 50, 10);
    setFilled(paddle, true);
    setFillColor(paddle, "BLACK");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-72");
    setColor(label, "GRAY");
    add(window, label);
    sendToBack(label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
