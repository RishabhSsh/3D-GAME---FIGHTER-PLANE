#include "arrow.h"
#include "main.h"

Arrow::Arrow(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 90;
    this->roo = 0;
    int n = 50;
    double rad = 0.03;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
     static const GLfloat vertex_buffer_data[] = {
            -0.015f, -0.015f, -0.05f, // triangle 1 : begin
            -0.015f, -0.015f, 0.05f,
            -0.015f, 0.015f, 0.05f, // triangle 1 : end
             0.015f, 0.015f, -0.05f, // triangle 2 : begin
            -0.015f, -0.015f, -0.05f,
            -0.015f, 0.015f, -0.05f, // triangle 2 : end
             0.015f, -0.015f, 0.05f,
            -0.015f, -0.015f, -0.05f,
            0.015f, -0.015f, -0.05f,
            0.015f, 0.015f, -0.05f,
            0.015f, -0.015f, -0.05f,
            -0.015f, -0.015f, -0.05f,
            -0.015f, -0.015f, -0.05f,
            -0.015f, 0.015f, 0.05f,
            -0.015f, 0.015f, -0.05f,
            0.015f, -0.015f, 0.05f,
            -0.015f, -0.015f, 0.05f,
            -0.015f, -0.015f, -0.05f,
            -0.015f, 0.015f, 0.05f,
            -0.015f, -0.015f, 0.05f,
            0.015f, -0.015f, 0.05f,
            0.015f, 0.015f, 0.05f,
            0.015f, -0.015f, -0.05f,
            0.015f, 0.015f, -0.05f,
            0.015f, -0.015f, -0.05f,
            0.015f, 0.015f, 0.05f,
            0.015f, -0.015f, 0.05f,
            0.015f, 0.015f, 0.05f,
            0.015f, 0.015f, -0.05f,
            -0.015f, 0.015f, -0.05f,
            0.015f, 0.015f, 0.05f,
            -0.015f, 0.015f, -0.05f,
            -0.015f, 0.015f, 0.05f,
            0.015f, 0.015f, 0.05f,
            -0.015f, 0.015f, 0.05f,
            0.015f, -0.015f, 0.05f,
    };

    GLfloat g_vertex_buffer_head[9*n];
    for(int i=0;i<9*n;i+=9){
      //sin (param*PI/180)
      int p = i/9;
      double k = p;
      double o = n;
      g_vertex_buffer_head[i] = 0.0f;
      g_vertex_buffer_head[i+1] = 0.0f;
      g_vertex_buffer_head[i+2] = -0.10f;

      g_vertex_buffer_head[i+5] = -0.05f;
      g_vertex_buffer_head[i+3] = (double)rad*cos(2.0*PI*(k)/o);
      g_vertex_buffer_head[i+4] = (double)rad*sin(2.0*PI*(k)/o);

      g_vertex_buffer_head[i+8] = -0.05f;
      g_vertex_buffer_head[i+6] = (double)rad*cos(2.0*PI*(k+1.0)/o);
      g_vertex_buffer_head[i+7] = (double)rad*sin(2.0*PI*(k+1.0)/o);

    }
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_BACKGROUND, GL_FILL);
    this->point = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_head, color, GL_FILL);

}


void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rr    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate    = rr;
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->point);
}

void Arrow::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Arrow::tick(float x, float y,float z) {
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
    
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

