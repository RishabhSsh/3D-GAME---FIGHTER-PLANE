#include "main.h"

#ifndef CANON_H
#define CANON_H


class Canon {
public:
    Canon() {}
    Canon(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    float timer;
    float roo;
    void draw(glm::mat4 VP);
    void tick(glm::vec3 A);
    double len;
    int life;
    bounding_box_t bounding_box();
private:
    VAO *body;
    VAO *body2;
};

#endif //CANON_H
