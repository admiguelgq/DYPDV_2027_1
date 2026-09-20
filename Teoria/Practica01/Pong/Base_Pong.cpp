#include <windows.h> //the windows include file, required by all windows applications
#include <GL/glut.h> //the glut file for windows operations
                     // it also includes gl.h and glu.h for the openGL library calls
#include <math.h>
#include "Jugador.h"

#define PI 3.1415926535898 

double xpos, ypos, ydir, xdir;    // x and y position for house to be drawn
double sx, sy, squash;          // xy scale factors
double rot, rdir;             // rotation
double ball_speed;

Jugador jugador(10.0,60.0); //jugador(rectangulo izquierdo)
Jugador segundojugador(150.0, 60.0); //jugador 2(rectangulo derecho)

GLfloat T1[16] = {1.,0.,0.,0.,\
                  0.,1.,0.,0.,\
                  0.,0.,1.,0.,\
                  0.,0.,0.,1.};
GLfloat S[16] = {1.,0.,0.,0.,\
                 0.,1.,0.,0.,\
                 0.,0.,1.,0.,\
                 0.,0.,0.,1.};
GLfloat T[16] = {1.,0.,0.,0.,\
                 0., 1., 0., 0.,\
                 0.,0.,1.,0.,\
                 0.,0.,0.,1.};

#define PI 3.1415926535898 
GLint circle_points = 100; 
void MyCircle2f(GLfloat centerx, GLfloat centery, GLfloat radius){
  GLint i;
  GLdouble angle;
  glBegin(GL_POLYGON); 
  for (i = 0; i < circle_points; i++) {    
    angle = 2*PI*i/circle_points; 
    glVertex2f(centerx+radius*cos(angle), centery+radius*sin(angle)); 
  } 
  glEnd();
}

GLfloat RadiusOfBall = 5.;
// Draw the ball, centered at the origin
void draw_ball() {
  glColor3f(1.0,1.0,1.0);
  MyCircle2f(0.,0.,RadiusOfBall);
  
}

void controlJugador() {

    if (GetAsyncKeyState('W') & 0x8000) {
        jugador.movimiento(1.0, 120.0, 0.0);
    }
    if (GetAsyncKeyState('S') & 0x8000) {
        jugador.movimiento(-1.0, 120.0, 0.0);
    }

    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        segundojugador.movimiento(1.0, 120.0, 0.0);
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        segundojugador.movimiento(-1.0, 120.0, 0.0);
    }
}

bool colision(float bx, float by, float radius, Jugador& p) {

    float ball_izquierda = bx - radius;
    float ball_derecha = bx + radius;
    float ball_abajo = by - radius;
    float ball_arriba = by + radius;

    float jugador_izquierda = p.getPosicionX() - (p.getAnchura() / 2.0);
    float jugador_derecha = p.getPosicionX() + (p.getAnchura() / 2.0);
    float jugador_abajo = p.getPosicionY() - (p.getAltura() / 2.0);
    float jugador_arriba = p.getPosicionY() + (p.getAltura() / 2.0);
   
    if (ball_derecha >= jugador_izquierda && ball_izquierda <= jugador_derecha && ball_arriba >= jugador_abajo && ball_abajo <= jugador_arriba) return true;
    
    return false;
}

void Display(void)
{
    // swap the buffers
    glutSwapBuffers();

    //clear all pixels with the specified clear color
    glClear(GL_COLOR_BUFFER_BIT);
    // 160 is max X value in our world

    /*  //reset transformation state
      glLoadIdentity();

      // apply translation
      glTranslatef(xpos,ypos, 0.);

      // Translate ball back to center
      glTranslatef(0.,-RadiusOfBall, 0.);
      // Scale the ball about its bottom
      glScalef(sx,sy, 1.);
      // Translate ball up so bottom is at the origin
      glTranslatef(0.,RadiusOfBall, 0.);
      // draw the ball
      draw_ball();
    */

    //Translate the bouncing ball to its new position
    T[12] = xpos;
    T[13] = ypos;
    glLoadMatrixf(T);

    T1[13] = -RadiusOfBall;
    // Translate ball back to center
    glMultMatrixf(T1);
    S[0] = sx;
    S[5] = sy;
    // Scale the ball about its bottom
    glMultMatrixf(S);

    T1[13] = RadiusOfBall;
    // Translate ball up so bottom is at the origin

    glMultMatrixf(T1);
    draw_ball();
    glLoadIdentity();
    jugador.dibujar();
    glLoadIdentity();
    segundojugador.dibujar();
    glutPostRedisplay(); 
}

void update(void) {
    controlJugador();
    // Shape has hit the ground! Stop moving and start squashing down and then back up 
    if (ypos <= RadiusOfBall && ydir == -1) {
        ypos = RadiusOfBall;
        sy = sy * squash;

        if (sy < 0.8)
            // reached maximum suqash, now unsquash back up 
            squash = 1.1;
        else if (sy > 1.) {
            // reset squash parameters and bounce ball back upwards
            sy = 1.;
            squash = 0.9;
            ydir = 1;
        }
        sx = 1. / sy;

        // 120 is max Y value in our world

    }
    else {
        // set Y position to increment 1.5 times the direction of the bounce
        ypos += ydir * ball_speed;

        // If ball touches the top, change direction of ball downwards
        if (ypos >= 120 - RadiusOfBall) {
            ydir = -1;
        }
        // If ball touches the bottom, change direction of ball upwards
        else if (ypos < RadiusOfBall)
            ydir = 1;
    }

    xpos += xdir * ball_speed;

    if (colision(xpos, ypos, RadiusOfBall, jugador)) {

        if (xpos >= jugador.getPosicionX() - jugador.getAnchura() / 2.0) {
            xdir = 1.0;
                 
        }
        if (ypos >= jugador.getPosicionY() + jugador.getAltura() / 2.0) {
            ydir = 1.0;
            
        }
        else if (ypos <= jugador.getPosicionY() - jugador.getAltura() / 2.0) {
            ydir = -1.0;
            
        } 
    }

    if (colision(xpos, ypos, RadiusOfBall, segundojugador)) {
       
        if (xpos <= segundojugador.getPosicionX() + segundojugador.getAnchura() / 2.0) {
            xdir = -1.0;
              
        }
        if (ypos >= segundojugador.getPosicionY() + segundojugador.getAltura() / 2.0) {
            ydir = 1.0;
            
        }
        else if (ypos <= segundojugador.getPosicionY() - segundojugador.getAltura() / 2.0) {
            ydir = -1.0;
            
        }
    }
    glutPostRedisplay();
}


void reshape (int w, int h)
{
   // on reshape and on startup, keep the viewport to be the entire size of the window
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();

   // keep our logical coordinate system constant
   gluOrtho2D(0.0, 160.0, 0.0, 120.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();

}


void init(void){
  //set the clear color
  glClearColor(0.0,0.0,0.0,0.0);
  // initial position set to 0,0
  xpos = 80; ypos = RadiusOfBall; xdir = 1; ydir = 1;
  sx = 1.; sy = 1.; squash = 0.9;
  rot = 0;
  ball_speed = 1.5;

}

int main(int argc, char* argv[])
{

  glutInit( & argc, argv );
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (320, 240);   
  glutCreateWindow("Bouncing Ball");
  init();
  glutIdleFunc(update);
  glutDisplayFunc(Display);
  glutReshapeFunc(reshape);
  glutMainLoop();

  return 1;
}
