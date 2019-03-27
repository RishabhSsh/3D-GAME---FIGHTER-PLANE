#include "main.h"

#ifndef LAND_H
#define LAND_H


class Land {
public:
    Land() {}
    Land(float x, float y,float z, float l, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
    double length;
private:
    VAO *object;
};

#endif //LAND_H
