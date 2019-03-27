#include "main.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H


class Dashboard {
public:
    Dashboard() {}
    Dashboard(float x, float y,float l, color_t color);
    glm::vec3 position;
    float rotation;
    float length;
    void draw();
    void set_position(float x, float y);
    void tick();
    double speed;
    double len;
private:
    VAO *object;
};

#endif //DASHBOARD_H
