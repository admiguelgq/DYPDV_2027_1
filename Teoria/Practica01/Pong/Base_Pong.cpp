#include <iostream>
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

Jugador jugador(10.0, 60.0); //jugador(rectangulo izquierdo)
Jugador segundojugador(150.0, 60.0); //jugador 2(rectangulo derecho)

int tiempo_anterior = 0;
double tiempo_reaparecer = 0.0;
double tiempo_espera = 1.0;
double deltaTime = 0.0;  

bool pelota_afuera = false;

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
   
    if (ball_derecha >= jugador_izquierda && ball_izquierda <= jugador_derecha && ball_arriba 
        >=jugador_abajo && ball_abajo <= jugador_arriba) return true;
    
    return false;
}

bool tunnelingProof(Jugador& p, float tiempo) {
    
    float desplazamientoX = xdir * ball_speed * tiempo;
    float desplazamientoY = ydir * ball_speed * tiempo;
    int particiones = 10;
    float partX = desplazamientoX / particiones;
    float partY = desplazamientoY / particiones;
    float tempX = xpos;
    float tempY = ypos;
    int i = 0;
    while (i < particiones) {
        tempX += partX;
        tempY += partY;
        if (colision(tempX, tempY, RadiusOfBall, p)) {
            return true; 
        }
        i++;
    }
    return false;
}

void partida(Jugador& p, Jugador& p_segundo, double tiempo) {
    if (xpos+RadiusOfBall<0 && !pelota_afuera) {
        pelota_afuera = true;
        tiempo_reaparecer = 0.0;
        p_segundo.aumentaPuntaje();
        std::cout << "Jugador 1: " << p.getPuntaje() << std::endl;
        std::cout << "Jugador 2: " << p_segundo.getPuntaje() << std::endl;

    }

    if (xpos - RadiusOfBall > 160 && !pelota_afuera) {
        pelota_afuera = true;
        tiempo_reaparecer = 0.0;
        p.aumentaPuntaje();
        std::cout << "Jugador 1: " << p.getPuntaje() << std::endl;
        std::cout << "Jugador 2: " << p_segundo.getPuntaje() << std::endl;

    }
    
    if (pelota_afuera) {
        tiempo_reaparecer += tiempo;
        ball_speed = 0.0;
        xpos = 80; ypos = 60;
        if (tiempo_reaparecer >= tiempo_espera) {
            xdir = xdir*-1;
            ball_speed = 100.0;
            pelota_afuera = false;
            tiempo_reaparecer = 0.0;

        }
       
    }
}

void Display(void)
{
    //clear all pixels with the specified clear color
    glClear(GL_COLOR_BUFFER_BIT);
    // 160 is max X value in our world
    // 120 is max Y value in our world
    glPushMatrix();
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
    glPopMatrix();

    jugador.dibujar();
    segundojugador.dibujar();
    glutSwapBuffers();
}

void update(void) {
    controlJugador();
    double tiempo_actual = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = (tiempo_actual - tiempo_anterior) / 1000.0;
    tiempo_anterior = tiempo_actual;

    if (deltaTime > 0.05) deltaTime = 0.05;
   
    ypos += ydir * ball_speed * deltaTime;
    xpos += xdir * ball_speed * deltaTime;

    if (ypos >= 120 - RadiusOfBall) ydir = -1;
        
    else if (ypos < RadiusOfBall) ydir = 1;
    
    if (tunnelingProof(jugador, deltaTime)) {
        if (xpos >= jugador.getPosicionX()) {
            xdir = 1.0;
        }
             
        if (ypos >= jugador.getPosicionY() + jugador.getAltura() / 2.0) {
            ydir = 1.0;
        }

        else if (ypos <= jugador.getPosicionY() - jugador.getAltura() / 2.0) {
            ydir = -1.0;  
        } 
        ball_speed += 0.5;
    }

    if (tunnelingProof(segundojugador, deltaTime)) {
        if (xpos <= segundojugador.getPosicionX()) {
            xdir = -1.0;

        }
         
        if (ypos >= segundojugador.getPosicionY() + segundojugador.getAltura() / 2.0) {
            ydir = 1.0;
            
        }
        else if (ypos <= segundojugador.getPosicionY() - segundojugador.getAltura() / 2.0) {
            ydir = -1.0;
            
        }
        ball_speed += 0.5;
    }
    partida(jugador,segundojugador,deltaTime);
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
  ball_speed = 100.0;
  tiempo_anterior = glutGet(GLUT_ELAPSED_TIME);

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