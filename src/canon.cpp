#include "canon.h"
#include "main.h"

Canon::Canon(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 30 + 180;
    this->roo = 0;
    int n = 50;
    double rad = 1.0f;
    double len = 11;
    timer = 5;
    this->life = 10;
    //speed = 0.1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

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
    this->body = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data2, COLOR_BLACKM, GL_FILL);  
    this->body2 = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data3, COLOR_YY, GL_FILL); 
}


void Canon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rr = glm::rotate((float) (this->rotation), glm::vec3(0, 1, 0 ));
    glm::mat4 rotate   = glm::rotate((float) (this->roo), glm::vec3(1, 0, 0 )) * rr;
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate          = rotate * glm::translate(glm::vec3(0, 0, -1.5));
    rotate = glm::translate(glm::vec3(0, 0, 1.5))*rotate;
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->body);
    draw3DObject(this->body2);  
}

void Canon::tick(glm::vec3 A) {
  glm::vec3 delta = A - this->position;
  float vv = abs(delta.y/delta.z);
  if(delta.y >= 0 && delta.z>=0 ){
     this->roo = -atan(vv);
    // printf("111\n");
   }
  else if(delta.y >= 0 && delta.z<=0){
      this->roo = M_PI + atan(vv);
      //printf("222\n");
    }
  else if(delta.y <= 0 && delta.z<=0){
      this->roo = M_PI - atan(vv);
    //  printf("333\n");
    }
  else 
     { this->roo = +atan(vv);
     // printf("444\n");
    }

  float zz = sqrt(delta.z*delta.z + delta.y*delta.y)/ sqrt(delta.x*delta.x + delta.y*delta.y + delta.z*delta.z);
  this->rotation =M_PI+acos(zz);

}

bounding_box_t Canon::bounding_box() {
    float x = this->position.x , y = this->position.y , z = this->position.z;
    float d = 5;
    bounding_box_t bbox = { x,y,z,d };
    return bbox;
}

