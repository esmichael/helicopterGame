#ifndef CIRCULO_H
#define CIRCULO_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <pthread.h>



class Circulo
{

private:

public:
	float cx = 0;
	float cy = 0;
	float r = 0;
	float scale = 1.0;
	float theta = 0;
	std::string fill;
	std::string id;
	double fillColor[3] = {0.0, 0.0, 0.0};

	void DrawCirc();

	bool isMyPose(float x, float y);

	Circulo()
	{
	}

	Circulo(float cx, float cy, float r, const char *fill, const char *id)
	{
		this->cx = cx;
		this->cy = cy;
		this->r = r;
		this->fill = fill;
		this->id = id;

		if(std::string(fill).compare("black") == 0)
		{
			fillColor[0] = 0;
			fillColor[1] = 0;
			fillColor[2] = 0;
		}

		if(std::string(fill).compare("gray") == 0)
		{
			fillColor[0] = 0.5;
			fillColor[1] = 0.5;
			fillColor[2] = 0.5;
		}

		if(std::string(fill).compare("red") == 0)
		{
			fillColor[0] = 1.0;
			fillColor[1] = 0;
			fillColor[2] = 0;
		}

		if(std::string(fill).compare("green") == 0)
		{
			fillColor[0] = 0;
			fillColor[1] = 0.5;
			fillColor[2] = 0;
		}

		if(std::string(fill).compare("blue") == 0)
		{
			fillColor[0] = 0;
			fillColor[1] = 0;
			fillColor[2] = 1.0;
		}

	};

};

#endif
