#include "main.h"

#ifndef WATER_h
#define WATER_h


class Water {
public:
    Water() {}
    Water(float x, float y,float z, color_t color);
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

#endif //WATER_h
