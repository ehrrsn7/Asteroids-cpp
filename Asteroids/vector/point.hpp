//
//  point.hpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/7/20.
//

#ifndef point_hpp
#define point_hpp

#include <string>
#include <iostream>

#include "velocity.hpp"

class Point {

private:
    int x;
    int y;

public:
    // constructors
    Point() {
        x = 0.0;
        y = 0.0;
    }
    
    Point(const Point & rhs) {
        setX(rhs.getX());
        setY(rhs.getY());
    }
    
    Point(float x_init, float y_init) : x(x_init), y(y_init) { }
    
    // getters
    float getX() const { return x; }
    float getY() const { return y; }
    Point get()  const { return new Point(x, y); }
    void display() { std::cout << '(' << x << ", " << y << ')'; }
    
    // setters
    void setX(float new_x) { x = new_x; }
    void setY(float new_y) { y = new_y; }
    void set(Point p) {
        x = p.getX();
        y = p.getY();
    }

    void setXY(float new_x, float new_y) {
        x = new_x;
        y = new_y;
    }
    
    // "adders"
    void add(Velocity v) {
        x += v.getDx();
        y += v.getDy();
    }

    void addX(float dx) { x += dx; }
    void addY(float dy) { y += dy; }
    
    // "check" constructor
    Point(bool check) : x(0.0), y(0.0) {}
};

#endif /* point_hpp */
