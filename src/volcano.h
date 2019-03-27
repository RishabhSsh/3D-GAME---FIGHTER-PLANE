#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H


class Volcano {
public:
    Volcano() {}
    Volcano(float x, float y, float z,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    bounding_box_t bounding_box();
    double len;
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

#endif // VOLCANO_H
