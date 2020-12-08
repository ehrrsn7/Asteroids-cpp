//
//  score.hpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/7/20.
//

#ifndef score_hpp
#define score_hpp

#include <iostream>
#include "point.hpp"
#include "uiDraw.hpp"

class Score {

private:
    int score;
    Point position;

public:
    Score() {
        std::cout << "Score constructor called." << std::endl;
        score = 0;
    }
    
    void set(Point p) { position.set(p); }
    
    void display() {
        // TODO: not displaying properly.
        drawText(position, "score");
    }
};

#endif /* score_hpp */
