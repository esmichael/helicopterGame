#include "circulo.hpp"
#include <math.h>

void Circulo::DrawCirc ()
{


	glPushMatrix();
	glTranslatef(this->cx, this->cy, 0);
	glScalef(this->scale, this->scale, this->scale);
	glColor3f(fillColor[0], fillColor[1], fillColor[2]);
	glPointSize(this->r);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i += 20)
	{
	  double degInRad = M_PI * i / 180;
	  glVertex2f(cos(degInRad) * this->r, sin(degInRad) * this->r);
	}
	glEnd();
	glPopMatrix();


}


bool  Circulo::isMyPose(float x, float y)
{
	double deltaX = this->cx - x;
	double deltaY = this->cy - y;

	double distance = sqrt(deltaX * deltaX + deltaY * deltaY);

	if (distance < r)
		return true;
	else
		return false;
}
