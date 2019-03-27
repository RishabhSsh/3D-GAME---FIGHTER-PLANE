#include "main.h"
#include "timer.h"
#include "plane.h"
#include "water.h"
#include "volcano.h"
#include "dashboard.h"
#include "arrow.h"
#include "missile.h"
#include "ring.h"
#include "fuel.h"
#include "parachute.h"
#include "bomb.h"
#include "canon.h"
#include "land.h"
#include "pointer.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
int cam = 0;
bool drag = 0;
Plane Plane1;
double cxpos, pxpos, cypos, pypos;
Water water;
Pointer poin,poo;
vector <Volcano> vol;
vector <Missile> mis;
vector <Bomb> bb,bp;
vector <Fuel> ff;
vector <Ring> rin;
vector <Land> ld;
vector <Parachute> pa;
bool barr = 0;
vector <Canon> co; 
Parachute ppp;
Arrow arrow;
Dashboard dheight,dspeed,dfuel;
glm::vec3 helcamEye = glm::vec3(5.0f, 0.0f, 15.0f);
glm::vec3 helcamTarget = glm::vec3(0.0, 0.0f, -100.0f);

float eyex=0,eyey=0,eyez=0,targetx=0,targety=0,targetz=0;
float upx=0,upy=0,upz=0;


long long score = 0;
double health  = 100;
int lock = 0;
bool uuf = 0;
float gravity = 0.5f;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float d = 0, h =0;
bool ufl;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    if(cam == 0){
        eyex = Plane1.position.x + 1.5f ;
        eyey = Plane1.position.y - 8.0f*sin(Plane1.yaw*M_PI/180.0f);
        eyez = Plane1.position.z + 8.0f*cos(Plane1.yaw*M_PI/180.0f);
        targetx = Plane1.position.x;
        targety =  Plane1.position.y;
        targetz = Plane1.position.z;
        upx = 1;
        upy = 0;
        upz = 0;
    }
    else if(cam == 1){
        eyex = Plane1.position.x ;
        eyey = Plane1.position.y + 2.0f*sin(Plane1.yaw*M_PI/180.0f);
        eyez = Plane1.position.z - 2.0f*cos(Plane1.yaw*M_PI/180.0f);
        targetx = Plane1.position.x;
        targety =  Plane1.position.y + 3.0f*sin(Plane1.yaw*M_PI/180.0f);
        targetz = Plane1.position.z - 3.0f*cos(Plane1.yaw*M_PI/180.0f);
        upx = 1;
        upy = 0;
        upz = 0;
    }
    else if(cam == 2){
        eyex = Plane1.position.x + 10.0f ;
        eyey = Plane1.position.y;
        eyez = Plane1.position.z;
        targetx = Plane1.position.x;
        targety =  Plane1.position.y;
        targetz = Plane1.position.z;
        upx = 0;
        upy = 0;
        upz = -1;
    }
    else if(cam == 3){
        eyex = 5.0f ;
        eyey = 0.0f;
        eyez = -10.0f;
        targetx = Plane1.position.x;
        targety =  Plane1.position.y;
        targetz = Plane1.position.z;
        upx = 1;
        upy = 0;
        upz = 0;
    }
    else if(cam == 4){
        eyex =  helcamEye.x ;
        eyey = helcamEye.y;
        eyez =  helcamEye.z;
        targetx = helcamTarget.x;
        targety =  helcamTarget.y;
        targetz = helcamTarget.z;
        upx = 1;
        upy = 0;
        upz = 0;
    }

    // Eye - Location of camera. Don't change unless you are sure!!
    //glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 eye ( eyex,eyey,eyez );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (targetx,targety,targetz);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (upx,upy,upz);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
 // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
  dheight.draw();
  dspeed.draw();
  dfuel.draw();
  water.draw(VP);
 // poo.draw(VP);
   for(auto c: vol) c.draw(VP);
    for(auto c: ld) c.draw(VP);
   for(auto c: rin) c.draw(VP);
   for(auto c: mis) c.draw(VP);
   for(auto c:ff) c.draw(VP);
     for(auto c:bb) c.draw(VP);
 for(auto c:co) c.draw(VP);
for(auto c:pa) c.draw(VP);
    for(auto c:bp) c.draw(VP);
   Plane1.draw(VP);
   arrow.draw(VP);
   if(co.size()) poin.draw(VP);
   //cout<<Plane1.position.x<<endl;
  // dheight.draw();
  // dheight.draw();
  }

void tick_input(GLFWwindow *window) {
    
    int space  = glfwGetKey(window, GLFW_KEY_SPACE);
    int down  = glfwGetKey(window, GLFW_KEY_S);
    int forward  = glfwGetKey(window, GLFW_KEY_UP);
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right  = glfwGetKey(window, GLFW_KEY_RIGHT);
    int rotl  = glfwGetKey(window, GLFW_KEY_Q);
    int rotr  = glfwGetKey(window, GLFW_KEY_E);
    int opp = glfwGetKey(window, GLFW_KEY_R);
    double deltax, deltay;
    if(opp == GLFW_PRESS && barr == 0){
        barr =1;
    }
    else if(opp == GLFW_RELEASE && barr == 1){
        barr = 0;
    }
    glfwGetCursorPos(window, &cxpos, &cypos);
//    cout << cxpos << " " << cypos << endl;
    if (cam == 4 && drag) {
        float dragx = ((float) cxpos - (float) pxpos) ;
        float dragy = ((float) cypos - (float) pypos) ;

        glm::vec3 delta = helcamTarget - helcamEye;
        glm::vec3 l;
        l.x += delta.x / sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
        l.y += delta.y / sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
        l.z += delta.z / sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);

        float coss = l.z / sqrt(l.x * l.x + l.z * l.z);
        float sinn = l.y / sqrt(l.x * l.x + l.z * l.z);

        helcamTarget.y += 3*dragy * sinn;
        helcamTarget.z -= 3*dragy * coss;

        helcamTarget.y -= 3*dragx * coss;
        helcamTarget.z += 3*dragx * sinn;
    }

   if (space == GLFW_PRESS && ufl==0) {
        ufl = 1;
       
        Plane1.xspeed = 1.0f;
    }
    if(ufl == 1){
        if(Plane1.pitch > -10.0f) Plane1.pitch -= 0.1f;
    }
    if (space == GLFW_RELEASE && ufl == 1){ 
        Plane1.xspeed = 0;
        Plane1.pitch = 0;
        ufl = false;
    }


    if (down == GLFW_PRESS && uuf==0) {
        uuf = 1;
        Plane1.xspeed = -1.0f;
    }
    if(uuf == 1){
        if(Plane1.pitch < 10.0f) Plane1.pitch += 0.1f;
    }
    if (down == GLFW_RELEASE && uuf == 1 ){ 
        Plane1.xspeed = 0;
        Plane1.pitch = 0;
        uuf = false;
    }

    if (forward == GLFW_PRESS ) {
        Plane1.exspeed = 1.5f;
        Plane1.fuel -=0.02;
    }
    else if (space == GLFW_RELEASE ){ 
        Plane1.exspeed = 0;
    }

    if( left == GLFW_PRESS) {
        Plane1.yspeed = 1.5f;
        if(Plane1.roll < 30.0f) Plane1.roll += 0.5f;
        
    }

    if( right == GLFW_PRESS) {
        Plane1.yspeed = -2.0f;
        if(Plane1.roll > -30.0f) Plane1.roll -= 0.5f;
        
    }
    
    if (right == GLFW_RELEASE && left == GLFW_RELEASE){ 
        Plane1.yspeed = 0;
        Plane1.roll = 0.0f;
    }
    
    if(rotl == GLFW_PRESS){
        Plane1.yaw += 0.6f;
    }

    if(rotr == GLFW_PRESS){
        Plane1.yaw -= 0.6f;
    }    

}

void tick_elements() {
    if(Plane1.position.x==-100 || Plane1.fuel == 0 || health <= 0){
        cout<<"Game Over"<<endl;
        exit(0);
    }
    Plane1.tick();
    if(barr){
        Plane1.roll += 10;
    }
    //dheight.length = 0.75*(Plane1.position.x + 100)/200.0;
    dheight = Dashboard(-1.0,-0.5,0.6*(Plane1.position.x + 100)/200.0,COLOR_RED2);
    dspeed = Dashboard(-1.0,-0.65,0.6*(Plane1.exspeed==1.5?1:0.5),COLOR_VI);
    dfuel = Dashboard(-1.0,-0.8,0.6*Plane1.fuel/100.0,COLOR_YY);
   // cout<<Plane1.position.x<<endl;
    water.tick();
    for(auto &c: vol) c.tick();
        for(auto &c: bp) c.tick();
            for(auto &c: bb) c.tick();
    for(auto &c: rin) c.tick();
    for(auto &c: co) c.tick(Plane1.position);
    for(auto &c: ff) c.tick();
//
    if(co.size()){
    auto pu = co.begin();
    glm::vec3 delta = pu->position - Plane1.position;
    glm::vec3 l;
    l.x += 20.0*delta.x / sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
    l.y += 20.0*delta.y / sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
    l.z += 20.0*delta.z / sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
    poo = Pointer(0,Plane1.position.y + l.y,Plane1.position.z + l.z,COLOR_BLACKM);
}
  //  poin.rotation+=20;
    for(auto c = pa.begin(); c < pa.end() ; ) {
       // cout<<c.position.x<<" ";
        c->position.x-=0.25f;
        if(c->position.x < -100.0f){
            c = pa.erase(c);
            ppp = Parachute(randf(-50.0f,100.0f),randf(-300.0f,300.0f),randf(-5000.0f,5000.0f),COLOR_YY);
            pa.push_back(ppp);
        }
        else c++;
        }
    for(auto c = mis.begin(); c < mis.end() ; ){
   // cout<<"hi"<<endl;
     c->tick();
     c->timer -=0.05;
     if(c->timer<0){
       // cout<<"yee\n"<<endl;
         c = mis.erase(c);
     }
     else c++;
 }
for(auto c = co.begin(); c < co.end() ; ){
   // cout<<"hi"<<endl;
     c->timer -=0.05;
     if(c->timer<0){
     //  cout<<"yee\n"<<endl;
         c->timer = 5;
         Bomb m = Bomb(c->position.x,c->position.y,c->position.z,2,c->roo,c->rotation - M_PI,0,COLOR_RED2);
         bp.push_back(m);
     }
     else c++;
 }
    for(auto c = bb.begin(); c < bb.end() ; ){
   // cout<<"hi"<<endl;
     c->tick();
     if(c->position.x<-120){
       // cout<<"yee\n"<<endl;
         c = bb.erase(c);

     }
     else c++;
 }

// collisionss  :) 

    for(auto c = ff.begin(); c < ff.end() ; ){
        if(detect_collision(c->bounding_box(),Plane1.bounding_box())){
            Plane1.fuel = min(Plane1.fuel + 10.0f, 100.0);
            c = ff.erase(c);
            printf("fuel!!!\n");
            Fuel fff = Fuel(randf(-50.0f,100.0f),randf(-300.0f,300.0f),randf(-5000.0f,5000.0f),COLOR_YY);
            ff.push_back(fff);
        }
        else c++;
    }

    for(auto c = rin.begin(); c < rin.end() ; ){
        if(detect_collision(c->bounding_box(),Plane1.bounding_box())){
            score += 5;
            c = rin.erase(c);
            printf("ring!!!\n");
            Ring r = Ring(randf(-50.0f,100.0f),randf(-300.0f,300.0f),randf(-5000.0f,5000.0f),COLOR_RED2);
            rin.push_back(r);
        }
        else c++;
    }

    for(auto c = vol.begin(); c < vol.end() ; ){
        if(detect_collision(c->bounding_box(),Plane1.bounding_box())){
            health -= 30;
            c = vol.erase(c);
            printf("volcano!!!\n");
        }
        else c++;
    }

    for(auto c = pa.begin(); c < pa.end() ; ){
        if(detect_collision(c->bounding_box(),Plane1.bounding_box())){
            health -= 10;
            c = pa.erase(c);
            printf("Parachute collisionss!!!\n");
            ppp = Parachute(randf(-50.0f,100.0f),randf(-300.0f,300.0f),randf(-5000.0f,5000.0f),COLOR_YY);
            pa.push_back(ppp);
        }
        else c++;
    }

    for(auto c = bp.begin(); c < bp.end() ; ){
        if(detect_collision(c->bounding_box(),Plane1.bounding_box())){
            health -= 5;
            c = bp.erase(c);
            printf("booo collisionss!!!\n");
        }
        else c++;
    }

    for(auto c = pa.begin(); c < pa.end() ; ){

        for(auto c2 = mis.begin(); c2 < mis.end() ; )
         {
            if(detect_collision(c->bounding_box(),c2->bounding_box())){
                score += 20;
                c2 = mis.erase(c2);
                c = pa.erase(c);
              }
            else c2++;
         }
        c++;
    } 
    for(auto c = co.begin(); c < co.end() ; ){

        for(auto c2 = mis.begin(); c2 < mis.end() ; )
         {
            if(detect_collision(c->bounding_box(),c2->bounding_box())){
                score += 50;
                
                c2 = mis.erase(c2);
                c->life--;
                if(c->life < 0){c = co.erase(c);
                health+=20;
                if(health>100) health =100;
                float ry= randf(-200.0f,200.0f);
                float rz= randf(-5000.0f,5000.0f);
                Canon cc = Canon(-99.5,ry,rz,COLOR_BLACKM);
                poin = Pointer(0,ry,rz,COLOR_RED);
                Land lp = Land(-99.7,ry,rz,10,COLOR_GREEN);
                ld.push_back(lp);
                co.push_back(cc);
            }
              }
            else c2++;
         }
        c++;
    } 

    for(auto c = co.begin(); c < co.end() ; ){

        for(auto c2 = bb.begin(); c2 < bb.end() ; )
         {
            if(detect_collision(c->bounding_box(),c2->bounding_box())){
                score += 1;
              //  cout<<"yes"<<endl;
                c2 = bb.erase(c2);
                c->life--;
                if(c->life < 0){c = co.erase(c);
                float ry= randf(-200.0f,200.0f);
                float rz= randf(-5000.0f,5000.0f);
                Canon cc = Canon(-99.5,ry,rz,COLOR_BLACKM);
                poin = Pointer(0,ry,rz,COLOR_RED);
                Land lp = Land(-99.7,ry,rz,10,COLOR_GREEN);
                ld.push_back(lp);
                co.push_back(cc);
            }
              }
            else c2++;
         }
        c++;
    } 

//
    //dheight.length = 0.75*(Plane1.position.x + 100)/200.0;
    
    //for(auto c: mis) c.tick(Plane1.position.x + 0.8f,Plane1.position.y - 7.0f*sin(Plane1.yaw*M_PI/180.0f), Plane1.position.z + 7.0f*cos(Plane1.yaw*M_PI/180.0f));
    arrow.tick(Plane1.position.x + 0.8f,Plane1.position.y - 7.0f*sin(Plane1.yaw*M_PI/180.0f), Plane1.position.z + 7.0f*cos(Plane1.yaw*M_PI/180.0f));
   // camera_rotation_angle += 1;
    char mscore[256];
    sprintf(mscore, "Airplane Fight!! 1.0 Score: %lld | Health :%f ",score,health);
    glfwSetWindowTitle(window, mscore);

}

/* Initialize the OpenGL rendering properties */
/* Adheight all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    Plane1   = Plane(0, 0, COLOR_RED);
    water   = Water(-100.0f,0,0,COLOR_WATER);
    arrow = Arrow(-50.0,0,-100,COLOR_RED2);
    Canon cc = Canon(-99.5,0,-100,COLOR_BLACKM);
    poin = Pointer(0,0,-100,COLOR_RED);
    poo = Pointer(0,0,-100,COLOR_RED);
    Land lp = Land(-99.7,0,-100,12,COLOR_GREEN);
    ld.push_back(lp);
    co.push_back(cc);
    for(int i = 0; i<=40; i++){
    Ring r = Ring(randf(-50.0f,100.0f),randf(-300.0f,300.0f),randf(-5000.0f,5000.0f),COLOR_RED2);
    Fuel fff = Fuel(randf(-50.0f,100.0f),randf(-300.0f,300.0f),randf(-5000.0f,5000.0f),COLOR_YY);
    ppp = Parachute(randf(-50.0f,100.0f),randf(-300.0f,300.0f),randf(-5000.0f,5000.0f),COLOR_YY);
    pa.push_back(ppp);
    ff.push_back(fff);
    rin.push_back(r);
    Volcano v = Volcano(-100.0f,randf(-150.0f,150.0f),randf(-5000.0f,5000.0f),COLOR_VOL);
    vol.push_back(v);
    }  
    dheight = Dashboard(-1.0,-0.65,0.1,COLOR_RED2);
    dspeed = Dashboard(-1.0,-0.65,0.1,COLOR_VI);
    dfuel = Dashboard(-1.0,-0.75,0.1,COLOR_YY);
            // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    float dis = sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)+ (a.z-b.z)*(a.z-b.z));
    return dis < a.r + b.r;
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    GLfloat fov = M_PI / 2;
    Matrices.projection = glm::perspective(fov, (right-left)/(top-bottom), 1.0f, 700.0f);
}

float randf(float lo, float hi) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = hi - lo;
    float r = random * diff;
    return lo + r;
}

void deploy_missile(){
    Missile m = Missile(Plane1.position.x,Plane1.position.y,Plane1.position.z-1.5,-2,Plane1.yaw,Plane1.pitch,COLOR_BLACKM);
    mis.push_back(m);
}

void deploy_bomb(){
    Bomb m = Bomb(Plane1.position.x,Plane1.position.y - 0.3,Plane1.position.z,Plane1.exspeed,Plane1.yaw,Plane1.pitch,1,COLOR_BLACKM);
    bb.push_back(m);
}

void scroll_call(double x_scroll, double y_scroll) {
    glm::vec3 delta = helcamTarget - helcamEye;
    helcamEye.x += (y_scroll) * delta.x / sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
    helcamEye.y += (y_scroll) * delta.y / sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
    helcamEye.z += (y_scroll) * delta.z / sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
}

void dragS() {
    drag = true;
}

void dragE() {
    drag = false;
}
