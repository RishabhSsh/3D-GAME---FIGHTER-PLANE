#include "main.h"

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y,float z,double ss, double rot, double rr, int tt,color_t color);
    glm::vec3 position;
    float rotation;
    int type;
    double zspeed;
    double rot;
    float rotationpp;
    double sos;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    bounding_box_t bounding_box();
    double speed;
    double len;
private:
    VAO *object;
    VAO *object2;
};

#endif //BOMB_H
