#include "retangulo.hpp"
#include <math.h>

void Retangulo::DrawRect ()
{


	glPushMatrix();
		glTranslatef(this->x, this->y, 0);

		glColor3f(fillColor[0], fillColor[1], fillColor[2]);
		glBegin(GL_QUADS);
			glVertex2f(0.0, 0.0);
			glVertex2f(0, this->height);
			glVertex2f(this->width, this->height);
			glVertex2f(this->width, 0.0);
		glEnd();

		glColor3f(strokeColor[0], strokeColor[1], strokeColor[2]);
		glLineWidth(this->strokeWidth);
		glBegin(GL_LINE_LOOP);
			glVertex2f(0.0, 0.0);
			glVertex2f(0, this->height);
			glVertex2f(this->width, this->height);
			glVertex2f(this->width, 0.0);
		glEnd();

	glPopMatrix();

}

bool  Retangulo::isMyPose(float x, float y)
{
	if (
		this->x < x &&
		this->y < y &&
		this->x + this->width > x &&
		this->y + this->height > y
		)
		return true;
	else
		return false;
}
