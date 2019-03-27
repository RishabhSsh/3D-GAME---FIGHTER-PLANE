#include "plane.h"
#include "main.h"

Plane::Plane(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, -5);
    this->rotation = 0;
    this->roll = 0 ;
    this->pitch = 0 ;
    this->yaw = 0 ;
    this->fuel = 100;
    this->o = 10;

    xspeed = 0;
    yspeed = 0;
    zspeed = 0.02f;
    exspeed = 0.0f;
    this->ss = sqrt(zspeed*zspeed + exspeed*exspeed);
    double rad = 0.6;
    int n = 50;
    len = 4.3f;
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
      g_vertex_buffer_data[i+2] = -1.2f;

      g_vertex_buffer_data[i+5] = 0.0f;
      g_vertex_buffer_data[i+3] = (double)rad*cos(2.0*PI*(k)/o);
      g_vertex_buffer_data[i+4] = (double)rad*sin(2.0*PI*(k)/o);

      g_vertex_buffer_data[i+8] = 0.0f;
      g_vertex_buffer_data[i+6] = (double)rad*cos(2.0*PI*(k+1.0)/o);
      g_vertex_buffer_data[i+7] = (double)rad*sin(2.0*PI*(k+1.0)/o);

    }

    GLfloat g_vertex_buffer_datab[9*n];
    for(int i=0;i<9*n;i+=9){
      //sin (param*PI/180)
      int p = i/9;
      double k = p;
      double o = n;
      g_vertex_buffer_datab[i] = 0.0f;
      g_vertex_buffer_datab[i+1] = 0.0f;
      g_vertex_buffer_datab[i+2] = len;

      g_vertex_buffer_datab[i+5] = len;
      g_vertex_buffer_datab[i+3] = (double)rad*cos(2.0*PI*(k)/o);
      g_vertex_buffer_datab[i+4] = (double)rad*sin(2.0*PI*(k)/o);

      g_vertex_buffer_datab[i+8] = len;
      g_vertex_buffer_datab[i+6] = (double)rad*cos(2.0*PI*(k+1.0)/o);
      g_vertex_buffer_datab[i+7] = (double)rad*sin(2.0*PI*(k+1.0)/o);

    }

    GLfloat g_vertex_buffer_datab2[9*n];
    for(int i=0;i<9*n;i+=9){
      //sin (param*PI/180)
      int p = i/9;
      double k = p;
      double o = n;
      g_vertex_buffer_datab2[i] = 0.0f;
      g_vertex_buffer_datab2[i+1] = 0.0f;
      g_vertex_buffer_datab2[i+2] = len;

      g_vertex_buffer_datab2[i+5] = len;
      g_vertex_buffer_datab2[i+3] = (double)0.5*rad*cos(2.0*PI*(k)/o);
      g_vertex_buffer_datab2[i+4] = (double)0.5*rad*sin(2.0*PI*(k)/o);

      g_vertex_buffer_datab2[i+8] = len;
      g_vertex_buffer_datab2[i+6] = (double)0.5*rad*cos(2.0*PI*(k+1.0)/o);
      g_vertex_buffer_datab2[i+7] = (double)0.5*rad*sin(2.0*PI*(k+1.0)/o);

    }

    GLfloat g_vertex_buffer_datab3[9*n];
    for(int i=0;i<9*n;i+=9){
      //sin (param*PI/180)
      int p = i/9;
      double k = p;
      double o = n;
      g_vertex_buffer_datab3[i] = 0.0f;
      g_vertex_buffer_datab3[i+1] = 0.0f;
      g_vertex_buffer_datab3[i+2] = len;

      g_vertex_buffer_datab3[i+5] = len;
      g_vertex_buffer_datab3[i+3] = (double)0.25*rad*cos(2.0*PI*(k)/o);
      g_vertex_buffer_datab3[i+4] = (double)0.25*rad*sin(2.0*PI*(k)/o);

      g_vertex_buffer_datab3[i+8] = len;
      g_vertex_buffer_datab3[i+6] = (double)0.25*rad*cos(2.0*PI*(k+1.0)/o);
      g_vertex_buffer_datab3[i+7] = (double)0.25*rad*sin(2.0*PI*(k+1.0)/o);

    }

    GLfloat g_vertex_buffer_data2[9*n];
    for(int i=0;i<9*n;i+=9){
      //sin (param*PI/180)
      int p = i/9;
      double k = p;
      double o = n;
      g_vertex_buffer_data2[i] = (double)rad*cos(2.0*PI*(k)/o);
      g_vertex_buffer_data2[i+1] = (double)rad*sin(2.0*PI*(k)/o);
      g_vertex_buffer_data2[i+2] = len;

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

      g_vertex_buffer_data3[i+5] = len;
      g_vertex_buffer_data3[i+3] = (double)rad*cos(2.0*PI*(k)/o);
      g_vertex_buffer_data3[i+4] = (double)rad*sin(2.0*PI*(k)/o);

      g_vertex_buffer_data3[i+8] = len;
      g_vertex_buffer_data3[i+6] = (double)rad*cos(2.0*PI*(k+1.0)/o);
      g_vertex_buffer_data3[i+7] = (double)rad*sin(2.0*PI*(k+1.0)/o);

    }

    double l = 0.45*len;
    GLfloat g_vertex_buffer_wing[] = {
         -0.3f,(float)len, (float)l,
         -0.3f,(float)-len, (float)l,
         -0.3f, 0.0f, 0.8f*(float)len,
    };

    GLfloat g_vertex_buffer_fl[] = {
         0.8f*(float)rad,-0.1f,(float)len,
         (float)rad,0.0f, 1.7f*(float)l,
         3.0f*(float)rad, 0.0f, (float)len,
         0.8f*(float)rad,0.1f,(float)len,
         (float)rad,0.0f, 1.7f*(float)l,
         3.0f*(float)rad, 0.0f, (float)len,
         0.8f*(float)rad,-0.1f,(float)len,
         0.8f*(float)rad,0.1f,(float)len,
         3.0f*(float)rad, 0.0f, (float)len,
    };


    this->object = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data, color, GL_FILL);
    this->body = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data2, color, GL_FILL);  
    this->body2 = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data3, COLOR_BLACK, GL_FILL); 
    this->wing = create3DObject(GL_TRIANGLES, 3, g_vertex_buffer_wing, COLOR_BLACK, GL_FILL);  
    this->bck = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_datab, COLOR_BLACK, GL_FILL);
    this->bck2= create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_datab2, color, GL_FILL);
    this->bck3= create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_datab3, COLOR_BLACK, GL_FILL);
    this->fl = create3DObject(GL_TRIANGLES, 9, g_vertex_buffer_fl, COLOR_BLACK, GL_FILL);  
}

void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 ryaw = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rroll = glm::rotate((float) (this->roll * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rpitch = glm::rotate((float) (this->pitch * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*ryaw*rpitch*rroll);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->body);
    draw3DObject(this->body2);
    draw3DObject(this->wing);
    draw3DObject(this->fl);
    draw3DObject(this->bck);
    draw3DObject(this->bck2);
    draw3DObject(this->bck3);
}

void Plane::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Plane::rotater(float x){
    this->roll += x;
}

void Plane::tick() {
  //  if(ufl==0)xspeed -= gravity;
    if(this->position.x >= 100.0f && ufl == 1) xspeed = 0;
    //if(this->position.x <= -100.0f && ufl == 0) xspeed = 0;
    
    //this->rotation += speed;
   this->position.x += xspeed;
   this->position.y += (zspeed + exspeed)*sin(this->yaw*M_PI/180.0f) + yspeed*cos(this->yaw*M_PI/180.0f);
   this->position.z -= (zspeed + exspeed)*cos(this->yaw*M_PI/180.0f) - yspeed*sin(this->yaw*M_PI/180.0f);
   this->ss = sqrt(zspeed*zspeed + exspeed*exspeed);
   //printf("%f\n",this->position.x);
    // this->position.y -= speed;
  // this->position.z += zspeed;
}

bounding_box_t Plane::bounding_box() {
    float x = this->position.x , y = this->position.y - 1.55*sin(this->yaw*M_PI/180.0f), z = this->position.z +  1.55*cos(this->yaw*M_PI/180.0f);
    float d = 2.75;
    bounding_box_t bbox = { x,y,z,d };
    return bbox;
}