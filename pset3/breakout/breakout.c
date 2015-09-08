/*
*
* breakout.c
* GUI made thanks to SPL
* Collision algo made thanks to David J. Malan
*
* Edouard JAMIN
* PSET3
*
* This is CS50.
*/

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// define height and width of the bricks
#define BHEIGHT 10
#define BWIDTH 36

// space between the bricks
#define SPACEBRICKS 4

// height and width of game's paddle in pixels
#define PHEIGHT 10
#define PWIDTH 60

// height (and width then) of the ball
#define CIRCLE 30

// lives
#define LIVES 3

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
    int bricks =  COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // initate for ball moves
    double velocityX = 2.00;
    double velocityY = drand48() * 10;

    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // make the paddle move
        GEvent event = getNextEvent(MOUSE_EVENT);

        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - getWidth(paddle) / 2;
                double y = getY(paddle);
                setLocation(paddle, x, y);

                if (getX(paddle) + getWidth(paddle) >= getWidth(window))
                {
                    x = getWidth(window) - getWidth(paddle);
                    setLocation(paddle, x, y);
                }

                if (getX(paddle) <= 0)
                {
                    x = 0;
                    setLocation(paddle, x, y);
                }
            }
        }

        // make the ball move
        move(ball, velocityX, velocityY);

        if (getX(ball) + getWidth(ball) >= getWidth(window))
            velocityX = -velocityX;
        else if (getX(ball) <= 0)
            velocityX = -velocityX;
        else if (getY(ball) + getWidth(ball) >= getHeight(window))
        {
            int x = ((WIDTH - CIRCLE) / 2);
            int y = ((HEIGHT - CIRCLE) / 2);
            setLocation(ball, x, y);
            lives = lives - 1;
            waitForClick();
        }
        else if (getY(ball) <= 0)
            velocityY = -velocityY;


        pause(20);

        // detect collision
        GObject object = detectCollision(window, ball);

        if (strcmp(getType(object), "GRect") == 0)
        {
            if (object == paddle)
            {
                velocityY = -velocityY;
            }
            else
            {
                velocityY = -velocityY;
                removeGWindow(window, object);
                bricks--;
                points = points + 1;
                char score[3];
                sprintf(score, "%i", points);
                setLabel(label, score);
            }
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

// Initializes window with a grid of bricks.
void initBricks(GWindow window)
{
    // TODO
    string color[] = { "#4e6b50", "#6bba64", "#6bba64", "#6bba64", "#8ec191" };
    for (int i = 0, y = 10; i < ROWS; i++, y = y + 20)
    {
        int x = SPACEBRICKS / 2;
        for (int j = 0; j < COLS; j++)
        {
            GRect bricks = newGRect(x, y, BWIDTH, BHEIGHT);
            setColor(bricks, color[i]);
            setFilled(bricks, true);
            add(window, bricks);
            x = x + BWIDTH + SPACEBRICKS;
        }
    }
}

// Instantiates ball in center of window.  Returns ball.
GOval initBall(GWindow window)
{
    // To comment TODO
    int x = ((WIDTH - CIRCLE) / 2);
    int y = ((HEIGHT - CIRCLE) / 2);
    GOval ball = newGOval(x, y, 30, 30);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

// Instantiates paddle in bottom-middle of window.
GRect initPaddle(GWindow window)
{
    // To comment TODO
    GRect paddle = newGRect(170, 550, PWIDTH, PHEIGHT);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);


    return paddle;
}

// Instantiates, configures, and returns label for scoreboard.
GLabel initScoreboard(GWindow window)
{
    // To comment TODO
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    int x = ((WIDTH - getWidth(label)) / 2);
    int y = ((HEIGHT - getHeight(label)) / 2);
    setLocation(label, x, y);
    add(window, label);
    return label;
}

// Updates scoreboard's label, keeping it centered in window.
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char score[12];
    sprintf(score, "%i", points);
    setLabel(label, score);

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
