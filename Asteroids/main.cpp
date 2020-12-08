/**
ASTEROIDS
 */

/*****************************************************
 * File: Driver.cpp
 * Author: Br. Burton
 *
 * Description: This file contains the main function
 *  that starts the game and the callback function
 *  that specifies what methods of the game class are
 *  called each time through the game loop.
 ******************************************************/
#include "game.hpp"
#include "uiInteract.hpp"

#include <iostream>
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void update(const Interface *pUI, void *p) {
    Game *pGame = (Game *) p;

    pGame->update();
    pGame->handleInput(*pUI);
    pGame->display(*pUI);
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * the game and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char ** argv) {
    std::cout << "Hello world!" << std::endl;
    Point topLeft(-SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    Point bottomRight(SCREEN_WIDTH/2, -SCREEN_HEIGHT/2);

    Interface ui(argc, argv, "Asteroids", topLeft, bottomRight);
    Game game(topLeft, bottomRight);
    ui.run(update, &game);

    return 0;
}
