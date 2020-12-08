//
//  rocks.cpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/14/20.
//

#include "rocks.hpp"

void Rock::initializeRotation() {
    da = random(ROCK_SPEED/2, ROCK_SPEED);
}
