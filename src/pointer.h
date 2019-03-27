#include "main.h"

#ifndef POINTER_H
#define POINTER_H


class Pointer {
public:
    Pointer() {}
    Pointer(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
    double len;
private:
    VAO *object;
};

#endif //POINTER_H
