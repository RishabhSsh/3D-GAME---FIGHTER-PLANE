#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick(float x, float y,float z);
    double speed;
    double len;
    double roo;
private:
    VAO *object;
    VAO *point;
};

#endif //ARROW_H
