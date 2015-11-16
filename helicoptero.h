#ifndef HELICOPTERO_H
#define HELICOPTERO_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "circulo.hpp"
#include "retangulo.hpp"
#include <vector>
#include <ctime>

class Helicoptero
{
public:
	Circulo centerCircle;
	Retangulo cabine;
	Retangulo cauda;
	Retangulo heliceCaudaR;
	Retangulo heliceCaudaL;
	Retangulo metralhadora;

	GLfloat gX;
	GLfloat gY;
	GLfloat gTheta = 0.0;
	GLfloat gMetralhadoraAngle = 0.0;
	GLfloat heliceAngle = 0.0;
	GLfloat r;
	GLfloat heliceVelocity = 10.0;
	GLfloat velTiro = 0.0;
	GLfloat velHelicoptero = 0.0;
	float tempoDeVoo = 0.0;
	std::time_t ultimoAbastecimento = 0.0;
	int colorPose = 0;
	std::time_t ultimoTiro = 0;
	bool dead = 0;


	std::vector<Circulo> bullet;

	bool isLanded = true;


private:
	void DrawHelice (int r);

public:
	void DrawHelicoptero();

	Helicoptero()
	{
		gX = 0;
		gY = 0;
		gTheta = 0;
		this->r = 0;
	};

	Helicoptero(Circulo circulo)
	{
		if (circulo.id.compare("Jogador") == 0)
			colorPose = 1;
		else if(circulo.id.compare("inimigo") == 0)
			colorPose = 0;

		ultimoTiro = std::time(nullptr);
		this->gX = circulo.cx;
		this->gY = circulo.cy;
		this->r = circulo.r;
		this->gTheta = 0;
		this->heliceVelocity = 10.0;

		this->centerCircle.r = circulo.r / 20;
		this->centerCircle.fillColor[colorPose] = 0.4;

		this->cabine = Retangulo(-circulo.r / 6,-circulo.r / 6,circulo.r / 3, circulo.r /3);
		this->cabine.fillColor[colorPose] = 0.6;

		this->cauda = Retangulo(-circulo.r / 16, 0.0,circulo.r / 8, circulo.r / 1.5);
		this->cauda.fillColor[colorPose] = 0.6;

		this->heliceCaudaR = Retangulo(circulo.r / 16, circulo.r / 1.5 - circulo.r / 8, circulo.r / 16, circulo.r / 4);
		this->heliceCaudaR.fillColor[colorPose] = 0.6;

		this->heliceCaudaL = Retangulo(-circulo.r / 16, circulo.r / 1.5 - circulo.r / 8, -circulo.r / 16, circulo.r / 4);
		this->heliceCaudaL.fillColor[colorPose] = 0.6;

		this->metralhadora = Retangulo(-circulo.r / 48, 0.0, circulo.r / 24, -circulo.r / 2.5);
		this->metralhadora.fillColor[colorPose] = 0.4;


		this->isLanded = true;
		this->ultimoAbastecimento = std::time(nullptr);


	};


	void Move (GLfloat d);
	void MoveInX (GLfloat dx);
	void MoveInY (GLfloat dy);
	void sumHeliceVelocity(GLfloat vel);
	void Rotate(GLfloat theta);
	void Land(bool);
	void reabastecer();
	void shot();

	bool  isMyPose(float x, float y, float raio = 0.0);




};

#endif
