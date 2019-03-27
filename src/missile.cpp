#include "missile.h"
#include "main.h"

Missile::Missile(float x, float y,float z,double zs,double rot,double rr,  color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = rot ;
    this->rotationpp = rr;
    zspeed = zs;
    int n = 50;
    double rad = 0.2f;
    double len = 0.5f;
    timer = 10;
    //speed = 0.1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat g_vertex_buffer_data[9*n];
    for(int i=0;i<9*n;i+=9){
      //sin (param*PI/180)
      int p = i/9;
      double k = p;
      double o = n;
      g_vertex_buffer_data[i] = 0.0f;
      g_vertex_buffer_data[i+1] = 0.0f;
      g_vertex_buffer_data[i+2] = -len-0.3;

      g_vertex_buffer_data[i+5] = -len;
      g_vertex_buffer_data[i+3] = (double)rad*cos(2.0*PI*(k)/o);
      g_vertex_buffer_data[i+4] = (double)rad*sin(2.0*PI*(k)/o);

      g_vertex_buffer_data[i+8] = -len;
      g_vertex_buffer_data[i+6] = (double)rad*cos(2.0*PI*(k+1.0)/o);
      g_vertex_buffer_data[i+7] = (double)rad*sin(2.0*PI*(k+1.0)/o);

    }

    GLfloat g_vertex_buffer_data2[9*n];
    for(int i=0;i<9*n;i+=9){
      //sin (param*PI/180)
      int p = i/9;
      double k = p;
      double o = n;
      g_vertex_buffer_data2[i] = (double)rad*cos(2.0*PI*(k)/o);
      g_vertex_buffer_data2[i+1] = (double)rad*sin(2.0*PI*(k)/o);
      g_vertex_buffer_data2[i+2] = -len;

      g_vertex_buffer_data2[i+5] = 0.0f;
      g_vertex_buffer_data2[i+3] = (double)rad*cos(2.0*PI*(k)/o);
      g_vertex_buffer_data2[i+4] = (double)rad*sin(2.0*PI*(k)/o);

      g_vertex_buffer_data2[i+8] = 0.0f;
      g_vertex_buffer_data2[i+6] = (double)rad*cos(2.0*PI*(k+1.0)/o);
      g_vertex_buffer_data2[i+7] = (double)rad*sin(2.0*PI*(k+1.0)/o);

    }

    GLfloat g_vertex_buffer_data3[9*n];
    for(int i=0;i<9*n;i+=9){
      //sin (param*PI/180)
      int p = i/9;
      double k = p;
      double o = n;
      g_vertex_buffer_data3[i] = (double)rad*cos(2.0*PI*(k+1)/o);
      g_vertex_buffer_data3[i+1] = (double)rad*sin(2.0*PI*(k+1)/o);
      g_vertex_buffer_data3[i+2] = 0.0f;

      g_vertex_buffer_data3[i+5] = -len;
      g_vertex_buffer_data3[i+3] = (double)rad*cos(2.0*PI*(k)/o);
      g_vertex_buffer_data3[i+4] = (double)rad*sin(2.0*PI*(k)/o);

      g_vertex_buffer_data3[i+8] = -len;
      g_vertex_buffer_data3[i+6] = (double)rad*cos(2.0*PI*(k+1.0)/o);
      g_vertex_buffer_data3[i+7] = (double)rad*sin(2.0*PI*(k+1.0)/o);

    }
    this->object = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data,  COLOR_BLACKM, GL_FILL);
    this->body = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data2, COLOR_BLACKM, GL_FILL);  
    this->body2 = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data3, COLOR_BLACKM, GL_FILL); 
}


void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0 ));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate          = rotate * glm::translate(glm::vec3(0, 0, -1.5));
    rotate = glm::translate(glm::vec3(0, 0, 1.5))*rotate;
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->body);
    draw3DObject(this->body2);  
}

void Missile::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}


void Missile::tick() {
    this->position.x += zspeed*sin(this->rotationpp*M_PI/180.0f);
    this->position.y += -zspeed*cos(this->rotationpp*M_PI/180.0f)*sin(this->rotation*M_PI/180.0f);
    this->position.z += zspeed*cos(this->rotationpp*M_PI/180.0f)*cos(this->rotation*M_PI/180.0f);
    //printf("hihhiiihh  %f\n\n",this->position.z);
      //  this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Missile::bounding_box() {
    float x = this->position.x , y = this->position.y + 0.4*sin(this->rotation*M_PI/180.0f), z = this->position.z - 0.4*cos(this->rotation*M_PI/180.0f);
    float d = 2.75;
    bounding_box_t bbox = { x,y,z,d };
    return bbox;
}