#include <stdio.h>

#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>


float alfaview = -M_PI / 4 , betaview = -M_PI / 4, step = 2.0;
float px=10,py=10,pz=10;
float dx,dy,dz;
int mode = GL_LINE;
float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;
int seed = 1;


float normA (float x ,float y, float z){
    return sqrt(x*x + y*y + z*z);
}

void normaliza (float* x ,float* y, float* z){
    float xx= *x, yy = *y, zz= *z;
    float norma = normA (xx,yy,zz);
    *x = xx/norma;
    *y = yy/norma;
    *z = zz/norma;
}


void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}


void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}



void arvores(int n){

    float x,z;
    srand(seed);
    int i;
    float posX[n];
    float posZ[n];
    for(i = 0; i<n; i++){

      posX[i] = ((float)rand()/(float)(RAND_MAX))*200.0 - 100.0;
      posZ[i] = ((float)rand()/(float)(RAND_MAX))*200.0 - 100.0;
        if (normA(posX[i],0,posZ[i]) < 50)
        i--;


    }

    for(i = 0; i<n; i++){

        x = posX[i];
        z = posZ[i];


        glPushMatrix();
        glTranslatef(x, 0, z);
        glRotatef(-90,1,0,0);
        glColor3f(0.647059,0.164706,0.164706);
        glutSolidCone(1, 3, 4, 4);
        glTranslatef(0,0,2.5);
        glColor3f(0.137255,0.556863,0.137255);
        glutSolidCone(3, 5, 10, 10);
        glPopMatrix();



    }
}

void drawteepots(int number, float radius){
  float alfa = 0;
  float angleStep = 2*M_PI/number;
  float px, pz;
  int i=0;


    for (i=0; i<number; i++){
      px = radius * sin(alfa);
      pz = radius * cos(alfa);
      glPushMatrix();
      glTranslatef(px,0.75,pz);
      glRotatef(alfa*180/M_PI -90 ,0,1,0);
      glutSolidTeapot(1);
      alfa += angleStep;
      glPopMatrix();

    }
}






void renderScene(void) {

    float viewx, viewy, viewz;
    viewx = cos(betaview)*sin(alfaview);
    viewy = sin(betaview);
    viewz = cos(betaview)*cos(alfaview);

    normaliza (&viewx,&viewy,&viewz);
    dx = viewx;
    dy = viewy;
    dz = viewz;

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(px, py, pz,
              px + dx, py + dy, pz + dz,
              0.0f,1.0f,0.0f);

    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex3f(100.0f, 0, -100.0f);
    glVertex3f(-100.0f, 0, -100.0f);
    glVertex3f(-100.0f, 0, 100.0f);

    glVertex3f(100.0f, 0, -100.0f);
    glVertex3f(-100.0f, 0, 100.0f);
    glVertex3f(100.0f, 0, 100.0f);

    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK,mode);


    arvores(100);

    glColor3f(0,0,1);
    drawteepots(6,15);

    glColor3f(1,0,0);
    drawteepots(24,35);


    glPushMatrix();
    glColor3f(0.737255,0.560784,0.560784);
    glutSolidTorus(1, 3, 10, 10);
    glPopMatrix();


    glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

    switch (c) {
        case 'd':
            alfaview -= M_PI/64;
            break;
        case 'a':
            alfaview += M_PI/64;
            break;
        case 'w':
            px += step*dx;
            py += step*dy;
            pz += step*dz;
            break;
        case 's':
            px -= step*dx;
            py -= step*dy;
            pz -= step*dz;
            break;
        case 'm':
            if(mode == GL_LINE){
                mode = GL_POINT;
                break;
            }else if(mode == GL_POINT){
                mode = GL_FILL;
                break;
            }else if(mode == GL_FILL){
                mode = GL_LINE;
                break;
            }
            break;
        case 'n':
            seed = rand();
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {

    switch (key) {
        case GLUT_KEY_UP :
            betaview += M_PI/64;
            if (betaview > M_PI/3)
                betaview = M_PI / 3;
            break;
        case GLUT_KEY_DOWN:
            betaview -= M_PI/64;
            if (betaview < -M_PI/3)
                betaview = -M_PI / 3;
            break;
        default:
            break;
    }

    glutPostRedisplay();

}


void help() {

        printf ( " ┌-------------------------------------------------HELP---------------------------------------------┐\n");
        printf ( " |                                                                                                  |\n");
        printf ( " |                                                                                                  |\n");
        printf ( " |                                                                                                  |\n");
        printf ( " |      Controls :                                                                                  |\n");
        printf ( " |         move forward: w                                                                          |\n");
        printf ( " |         move backwards: s                                                                        |\n");
        printf ( " |         look left: a                                                                             |\n");
        printf ( " |         look right: d                                                                            |\n");
        printf ( " |         look up: UP KEY                                                                          |\n");
        printf ( " |         look down: DOWN KEY                                                                      |\n");
        printf ( " |         switch drawing mode: m                                                                   |\n");
        printf ( " |         switch tree seed: n                                                                      |\n");
        printf ( " |                                                                                                  |\n");
        printf ( " └--------------------------------------------------------------------------------------------------┘\n");
}



int main(int argc, char **argv) {


    help();

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG@DI-UM");

// Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    //spherical2Cartesian();


// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
