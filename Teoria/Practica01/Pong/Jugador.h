#pragma once
#include <GL/glut.h>

class Jugador {
private:
    GLfloat xpos;
    GLfloat ypos;
    GLfloat ancho_jugador = 5.0;
    GLfloat alto_jugador = 15.0;
    GLfloat velocidad = 3.0;

public:
    Jugador(GLfloat x, GLfloat y);
    GLfloat getPosicionX();
    GLfloat getPosicionY();
    GLfloat getAnchura();
    GLfloat getAltura();
    void movimiento(int direccion, GLfloat superior, GLfloat inferior);
    void dibujar() const;
};
