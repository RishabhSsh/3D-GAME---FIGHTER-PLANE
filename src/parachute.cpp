#include "parachute.h"
#include "main.h"

Parachute::Parachute(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 100;
    int n = 10;
    double rad = 7.0f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat g_vertex_buffer_data[9*n];
    GLfloat g_vertex_buffer_data2[9*(n/2)];
    int kk =0, j=0 ;
    //printf("called\n");
    for(int i=0;i<9*n;i+=9,kk++){
      //sin (param*PI/180)
      int p = i/9;
      double k = p;
      double o = n;
      g_vertex_buffer_data[i] = 0.0f;
      g_vertex_buffer_data[i+1] = 0.0f;
      g_vertex_buffer_data[i+2] = 0.0f;

      g_vertex_buffer_data[i+3] = 0.0f;
      g_vertex_buffer_data[i+4] = (double)rad*cos(2.0*PI*(k)/o);
      g_vertex_buffer_data[i+5] = (double)rad*sin(2.0*PI*(k)/o);

      g_vertex_buffer_data[i+6] = 0.0f;
      g_vertex_buffer_data[i+7] = (double)rad*cos(2.0*PI*(k+1.0)/o);
      g_vertex_buffer_data[i+8] = (double)rad*sin(2.0*PI*(k+1.0)/o);

      if(kk%2 == 0){
      g_vertex_buffer_data2[j] = -20.0f;
      g_vertex_buffer_data2[j+1] = 0.0f;
      g_vertex_buffer_data2[j+2] = 0.0f;

      g_vertex_buffer_data2[j+3] = 0.0f;
      g_vertex_buffer_data2[j+4] = (double)rad*cos(2.0*PI*(k)/o);
      g_vertex_buffer_data2[j+5] = (double)rad*sin(2.0*PI*(k)/o);

      g_vertex_buffer_data2[j+6] = 0.0f;
      g_vertex_buffer_data2[j+7] = (double)rad*cos(2.0*PI*(k+1.0)/o);
      g_vertex_buffer_data2[j+8] = (double)rad*sin(2.0*PI*(k+1.0)/o);
      j+=9;
      }

    }

    this->object = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data, COLOR_DG, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3*(n/2), g_vertex_buffer_data2, COLOR_RED, GL_FILL);
}


void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);    
}


void Parachute::tick() {
   // this->rotation += speed;
  //  this->position.x -= 1.0f;
   // printf("%f\n",this->position.x);
    // this->position.y -= speed;
}

bounding_box_t Parachute::bounding_box() {
    float x = this->position.x - 10.0f, y = this->position.y, z = this->position.z;
    float d = (sqrt(149) + 10.0)/2;
    bounding_box_t bbox = { x,y,z,d };
    return bbox;
}