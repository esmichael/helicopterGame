#ifndef RETANGULO_H
#define RETANGULO_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <pthread.h>
#include <iostream>



class Retangulo
{

private:

public:
	float x = 0.0;
	float y = 0.0;
	float width = 0.0;
	float height = 0.0;
	float strokeWidth = 0.01;
	std::string id;
	double strokeColor[3] = {0.0, 0.0, 0.0};
	double fillColor[3] = {0.0, 0.0, 0.0};

	void DrawRect();
	bool isMyPose(float x, float y);


	Retangulo(){};

	Retangulo(float x, float y, float width, float height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	Retangulo(float x, float y, float width, float height,const char *fill, float strokeWidth ,const char *stroke ,const char *id)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->strokeWidth = strokeWidth;
		this->id = id;


		if(std::string(fill).compare("white") == 0)
		{
			fillColor[0] = 1;
			fillColor[1] = 1;
			fillColor[2] = 1;
		}

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
			fillColor[1] = 1.0;
			fillColor[2] = 0;
		}

		if(std::string(fill).compare("blue") == 0)
		{
			fillColor[0] = 0;
			fillColor[1] = 0;
			fillColor[2] = 1.0;
		}


		//stroke color
		if(std::string(stroke).compare("black") == 0)
		{
			strokeColor[0] = 0;
			strokeColor[1] = 0;
			strokeColor[2] = 0;
		}

		if(std::string(stroke).compare("gray") == 0)
		{
			strokeColor[0] = 0.6;
			strokeColor[1] = 0.6;
			strokeColor[2] = 0.6;
		}

		if(std::string(stroke).compare("red") == 0)
		{
			strokeColor[0] = 1.0;
			strokeColor[1] = 0;
			strokeColor[2] = 0;
		}

		if(std::string(stroke).compare("green") == 0)
		{
			strokeColor[0] = 0;
			strokeColor[1] = 1.0;
			strokeColor[2] = 0;
		}

		if(std::string(stroke).compare("blue") == 0)
		{
			strokeColor[0] = 0;
			strokeColor[1] = 0;
			strokeColor[2] = 1.0;
		}
	};

};

#endif
