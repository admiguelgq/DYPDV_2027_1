#include "Jugador.h"

Jugador::Jugador(GLfloat x, GLfloat y) {
	xpos = x;
	ypos = y;
}

GLfloat Jugador::getPosicionX() {
	return xpos;
}

GLfloat Jugador::getPosicionY() {
	return ypos;
}

GLfloat Jugador::getAnchura() {
	return ancho_jugador;
}

GLfloat Jugador::getAltura() {
	return alto_jugador;
}

void Jugador::movimiento(int direccion, GLfloat superior, GLfloat inferior) {
	GLfloat nuevaPosY = ypos + (direccion * velocidad);
	GLfloat mitad_alto = alto_jugador / 2.0;

	if (direccion > 0 && (nuevaPosY + mitad_alto) <= superior) {
		ypos = nuevaPosY;
	}
	else if (direccion < 0 && (nuevaPosY - mitad_alto) >= inferior) {
		ypos = nuevaPosY;
	}
}

void Jugador::dibujar() const {

	glPushMatrix();
	glTranslatef(xpos,ypos,0.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(-ancho_jugador / 2.0, -alto_jugador / 2.0);
	glVertex2f(ancho_jugador / 2.0, -alto_jugador / 2.0);
	glVertex2f(ancho_jugador / 2.0, alto_jugador / 2.0);
	glVertex2f(-ancho_jugador / 2.0, alto_jugador / 2.0);
	glEnd();
	glPopMatrix();
	
}