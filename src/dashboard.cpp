#include "dashboard.h"
#include "main.h"

Dashboard::Dashboard(float x, float y,float l, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 180+90;
    this->length = l;
    float h = 0.1f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        0.0f,0.0f,0.0f,
        h,0.0f,0.0f,
        0.0f,this->length ,0.0f,
        0.0f,this->length , 0.0f,
        h,this->length,0.0f,
        h,0.0f,0.0f,

    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}


void Dashboard::draw() {
   // printf("%f\n",this->length);
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP =  Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

}

void Dashboard::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Dashboard::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

