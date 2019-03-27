#include "main.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H


class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();   
    void tick();
    double speed;
    double len;
private:
    VAO *object;
    VAO *object2;
};

#endif //PARACHUTE_H
