#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(float x, float y,float z,double zs,double rot,double rr,  color_t color);
    glm::vec3 position;
    float rotation;
    float rotationpp;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    bounding_box_t bounding_box();
    void tick();
    double zspeed;
    double len;
    double timer ;
private:
    VAO *object;
    VAO *body;
    VAO *body2;
};

#endif //MISSILE_H
