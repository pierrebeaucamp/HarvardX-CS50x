//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
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
#define COLS 10
#define GAP 2

// radius of ball in pixels
#define RADIUS 10

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
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // velocity of the ball
    double ball_vx = (drand48() - 0.5) * 5;
    double ball_vy = 3;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // Player movement
        GEvent e = getNextEvent(MOUSE_EVENT);
        if (e != NULL)
        {
            int x = getX(e) - getWidth(paddle) / 2;
            setLocation(paddle, x, getY(paddle));
        }

        // Game Logic
        GObject object = detectCollision(window, ball);
        if (object != NULL && !(strcmp(getType(object), "GRect")) &&
            object != paddle)
        {
             removeGWindow(window, object);
             ball_vy = ball_vy * -1;
             bricks -= 1;
             points += 1;
             updateScoreboard(window, label, points);
        }

        if (getY(ball) + 2 * RADIUS >= getHeight(window))
        {
            lives -= 1;
            removeGWindow(window, ball);
            ball = initBall(window);
            if (lives)
                waitForClick();
        }

        if (getY(ball) <= 0 || object == paddle)
            ball_vy = ball_vy * -1;

        if (getX(ball) <= 0 || getX(ball) + 2 * RADIUS >= getWidth(window))
            ball_vx = ball_vx * -1;

        // Rendering
        move(ball, ball_vx, ball_vy);
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
    int width = getWidth(window) / COLS - 2 * GAP;
    int height = width / 4;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            int x = j * (width + 2 * GAP) + GAP;
            int y = i * (height + 2 * GAP) + GAP + RADIUS;

            GRect brick = newGRect(x, y, width, height);
            setColor(brick, "BLUE");
            setFilled(brick, true);
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    int x = getWidth(window) / 2 - RADIUS;
    int y = getHeight(window) / 2 - RADIUS;

    GOval ball = newGOval(x, y, RADIUS * 2, RADIUS * 2);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);

    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    int width = getWidth(window) / COLS * 1.5;
    int height = width / 6;
    int x = getWidth(window) / 2 - width / 2;
    int y = getHeight(window) - height - 2 * RADIUS;

    GRect paddle = newGRect(x, y, width, height);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);

    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setColor(label, "BLACK");
    setFont(label, "SansSerif-20");

    updateScoreboard(window, label, 0);
    add(window, label);
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
