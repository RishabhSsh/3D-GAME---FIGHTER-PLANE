#include "main.h"

#ifndef PLANE_H
#define PLANE_H


class Plane {
public:
    Plane() {}
    Plane(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float roll;
    float yaw;
    float pitch;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void rotater(float x);
    double xspeed;
    double yspeed;
    bounding_box_t bounding_box();
    double zspeed;
    double exspeed;
    double len;
    double fuel;
    double ss;
    double o;
private:
    VAO *object;
    VAO *body;
    VAO *body2;
    VAO *wing;
    VAO *fl;
    VAO *bck;
    VAO *bck2;
    VAO *bck3;
};

#endif // PLANE_H
