#include "helicoptero.h"
#include <math.h>




void Helicoptero::Move(GLfloat d)
{
	if (this->isLanded)
		return;

	this->MoveInX(sin(M_PI * this->gTheta / 180) * d);
	this->MoveInY(-cos(M_PI * this->gTheta / 180) * d);
}


void Helicoptero::MoveInX (GLfloat dx)
{
	this->gX += dx;
}


void Helicoptero::MoveInY (GLfloat dy)
{
	this->gY += dy;
}


void Helicoptero::sumHeliceVelocity (GLfloat vel)
{
	this->heliceVelocity += vel;
	if (this->heliceVelocity < 0.0)
		this->heliceVelocity = 0.0;
}



void Helicoptero::Rotate(GLfloat theta)
{
	if (this->isLanded)
		return;
	this->gTheta += theta;
	if (this->gTheta > 360.0)
		this->gTheta -= 360.0;
	if (this->gTheta < 0.0)
		this->gTheta += 360.0;
}


void Helicoptero::Land(bool land)
{
	this->isLanded = land;
}

void Helicoptero::reabastecer()
{
	this->ultimoAbastecimento = std::time(nullptr);
}

void Helicoptero::shot()
{
	if (this->isLanded == true)
		return;

	Circulo newBullet;
	newBullet.cx = this->gX;
	newBullet.cy = this->gY;
	newBullet.theta = this->gTheta + this->gMetralhadoraAngle;

	if(!this->isLanded)
		newBullet.scale = 1.5;
	else
		newBullet.scale = 1.0;

	newBullet.cx += sin(M_PI * newBullet.theta / 180) * -this->metralhadora.height * newBullet.scale;
	newBullet.cy += -cos(M_PI * newBullet.theta / 180) * -this->metralhadora.height * newBullet.scale;

	newBullet.r = this->metralhadora.width / 2;
	bullet.push_back(newBullet);
}

void Helicoptero::DrawHelice(int r)
{
	glPushMatrix();

	if  (colorPose == 0)
		glColor3f(1, 0, 0);
	else if  (colorPose == 1)
		glColor3f(0, 1, 0);
	else if  (colorPose == 2)
		glColor3f(0, 0, 1);

	glPointSize(3.0);
	this->heliceAngle += this->heliceVelocity;
	if (this->heliceAngle > 360)
		this->heliceAngle -= 360;
	glRotatef(this->heliceAngle, 0, 0, 1);

	for (int i = 0; i < 360; i += 90)
	{
		double degInRad;
		glBegin(GL_QUADS);
			glVertex2f(0, 0);
			degInRad = M_PI * (i + 5) / 180;
			glVertex2f(cos(degInRad) * r, sin(degInRad) * r);
			degInRad = M_PI * (i - 5) / 180;
			glVertex2f(cos(degInRad) * r, sin(degInRad) * r);
			glVertex2f(0, 0);
		glEnd();

	}

	glPopMatrix();


}


void Helicoptero::DrawHelicoptero()
{

	if (this->tempoDeVoo != 0)
		if (std::time(nullptr) - this->ultimoAbastecimento > this->tempoDeVoo)
		{
			this->dead = true;
		}


	for (int i = 0; i < this->bullet.size(); i++)
	{
		glPushMatrix();

		this->bullet[i].cx += sin(M_PI * this->bullet[i].theta / 180) * this->velTiro;
		this->bullet[i].cy += -cos(M_PI * this->bullet[i].theta / 180) * this->velTiro;

			this->bullet[i].DrawCirc();
		glPopMatrix();
	}

	for (int i = 0; i < this->bullet.size(); i++)
	{
		if (this->bullet[i].cx >= (float) glutGet(GLUT_WINDOW_WIDTH) || this->bullet[i].cx <= 0)
		{
			this->bullet.erase(this->bullet.begin() + i);
		}

		if (this->bullet[i].cy >= (float) glutGet(GLUT_WINDOW_HEIGHT) || this->bullet[i].cy <= 0)
		{
			this->bullet.erase(this->bullet.begin() + i);
		}
	}

	glPushMatrix();
		glTranslatef(this->gX, this->gY, 0);
		if(!this->isLanded)
			glScalef(1.5, 1.5, 1.5);

		glRotatef(this->gTheta, 0, 0, 1);

		glPushMatrix();
			glRotatef(this->gMetralhadoraAngle, 0, 0, 1);
			this->metralhadora.DrawRect();
		glPopMatrix();

		this->heliceCaudaL.DrawRect();
		this->heliceCaudaR.DrawRect();
		this->cauda.DrawRect();
		this->cabine.DrawRect();
		this->DrawHelice(this->r);
		this->centerCircle.DrawCirc();
	glPopMatrix();

}


bool  Helicoptero::isMyPose(float x, float y, float raio)
{
	double deltaX = this->gX - x;
	double deltaY = this->gY - y;

	if (raio == 0.0)
	{
		raio = this->r;
		if(!this->isLanded)
			raio *= 1.5;
	}

	double distance = sqrt(deltaX * deltaX + deltaY * deltaY);

	if (distance < raio)
		return true;
	else
		return false;
}
