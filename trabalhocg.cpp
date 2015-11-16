#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <GL/glut.h>
#include "tinyxml/tinyxml.h"
#include "circulo.hpp"
#include "retangulo.hpp"
#include "helicoptero.h"
#include <math.h>

std::vector<Circulo> circuloVector;
std::vector<Retangulo> retanguloVector;
Retangulo arena;
Helicoptero jogador;
std::vector<Helicoptero> inimigoVector;

unsigned char isPressed[256];

double velTiro = 0.0;
double velHelicoptero = 0.0;
double tempoDeVoo = 0.0;
double freqTiroInimigo = 0.0;
double velHelicopteroInimigo = 0.0;
int gameover = 0;


void
keyPress(unsigned char key, int x, int y)
{
	isPressed[key] = 1;
	if(isPressed['+']) jogador.sumHeliceVelocity(1.0);
	if(isPressed['-']) jogador.sumHeliceVelocity(-1.0);

}

void
keyUp(unsigned char key, int x, int y)
{
	isPressed[key] = 0;
}


void drawFuel()
{
	static std::vector<Retangulo> fuelVector;
	static int initialized = 0;

	if (initialized == 0)
	{
		fuelVector.push_back(Retangulo(100, 20, 20, 10,"blue", 0, "blue" ,"fuel"));
		fuelVector.push_back(Retangulo(80, 20, 20, 10,"blue", 0, "blue" ,"fuel"));
		fuelVector.push_back(Retangulo(60, 20, 20, 10,"green", 0, "green" ,"fuel"));
		fuelVector.push_back(Retangulo(40, 20, 20, 10,"green", 0, "green" ,"fuel"));
		fuelVector.push_back(Retangulo(20, 20, 20, 10,"red", 0, "red" ,"fuel"));
		initialized = 1;

	}

	for (int i = 0; i < fuelVector.size() ; i++)
	{
		if((std::time(nullptr) - jogador.ultimoAbastecimento) < (float)(jogador.tempoDeVoo / fuelVector.size()) * i)
			fuelVector[i].DrawRect();

	}
}

void
idle(void)
{
	static int animation = -1;
	GLfloat oldX = jogador.gX;
	GLfloat oldY = jogador.gY;

	if(isPressed['w']) jogador.Move(jogador.velHelicoptero);
	if(isPressed['s']) jogador.Move(-jogador.velHelicoptero);

	if(isPressed['d']) jogador.Rotate(2);
	if(isPressed['a']) jogador.Rotate(-2);



for (unsigned int j = 0; j < inimigoVector.size(); j++)
	if(inimigoVector[j].isMyPose(jogador.gX, jogador.gY, jogador.r * 3) == true)
	{
		jogador.gX = oldX;
		jogador.gY = oldY;

	}
	glutPostRedisplay();
}

char*
readXMLConfig(char* file)
{
	char *fileName = new char [256];
	TiXmlDocument document(file);
	document.LoadFile();
	TiXmlHandle docHandle(&document);
	for (TiXmlElement* aplicacao = docHandle.FirstChildElement("aplicacao").ToElement(); aplicacao; aplicacao = aplicacao->NextSiblingElement())
	{
		for (TiXmlElement* arquivosDeEntrada = aplicacao->FirstChildElement("arquivosDeEntrada"); arquivosDeEntrada; arquivosDeEntrada = arquivosDeEntrada->NextSiblingElement())
			for (TiXmlElement* arquivoDaArena = arquivosDeEntrada->FirstChildElement("arquivoDaArena"); arquivoDaArena; arquivoDaArena = arquivoDaArena->NextSiblingElement())
				sprintf(fileName, "%s%s.%s", arquivoDaArena->Attribute("caminho"), arquivoDaArena->Attribute("nome"), arquivoDaArena->Attribute("tipo"));

		TiXmlElement* helicoptero = aplicacao->FirstChildElement("helicoptero");
		velTiro = atof(helicoptero->Attribute("velTiro"));
		velHelicoptero = atof(helicoptero->Attribute("velHelicoptero"));
		tempoDeVoo = atof(helicoptero->Attribute("tempoDeVoo"));

		TiXmlElement* helicopteroInimigo = aplicacao->FirstChildElement("helicopteroInimigo");
		freqTiroInimigo = 0.001 / atof(helicopteroInimigo->Attribute("freqTiro"));
		velHelicopteroInimigo = atof(helicopteroInimigo->Attribute("velHelicoptero"));

	}
	return fileName;
}


void
readSGV(char* file)
{
	TiXmlDocument document(file);
	document.LoadFile();
	TiXmlHandle docHandle(&document);
	for (TiXmlElement* svg = docHandle.FirstChildElement("svg").ToElement(); svg; svg = svg->NextSiblingElement())
	{
		for (TiXmlElement* circle = svg->FirstChildElement("circle"); circle; circle = circle->NextSiblingElement("circle"))
			if (std::string(circle->Attribute("id")).compare("Jogador") == 0)
			{
				jogador = Helicoptero(Circulo(
						atof(circle->Attribute("cx")),
						atof(circle->Attribute("cy")),
						atof(circle->Attribute("r")),
						circle->Attribute("fill"),
						circle->Attribute("id")));
				jogador.velTiro = velTiro * 10;
				jogador.velHelicoptero = velHelicoptero * 10;
				jogador.tempoDeVoo = tempoDeVoo;

			}
			else if(std::string(circle->Attribute("id")).compare("Inimigo") == 0)
			{

				inimigoVector.push_back(Helicoptero(Circulo(
						atof(circle->Attribute("cx")),
						atof(circle->Attribute("cy")),
						atof(circle->Attribute("r")),
						circle->Attribute("fill"),
						circle->Attribute("id"))));

				inimigoVector.back().velHelicoptero  = velHelicopteroInimigo *  10;
				inimigoVector.back().velTiro = velTiro * 10;


				inimigoVector.back().Land(false);

			}
			else
			{
				circuloVector.push_back(Circulo(
						atof(circle->Attribute("cx")),
						atof(circle->Attribute("cy")),
						atof(circle->Attribute("r")),
						circle->Attribute("fill"),
						circle->Attribute("id")));
			}

		for (TiXmlElement* rect = svg->FirstChildElement("rect"); rect; rect = rect->NextSiblingElement("rect"))
		{
			if (std::string(rect->Attribute("id")).compare("Arena") == 0)
			{
				arena = (Retangulo(
						atof(rect->Attribute("x")),
						atof(rect->Attribute("y")),
						atof(rect->Attribute("width")),
						atof(rect->Attribute("height")),
						rect->Attribute("fill"),
						atof(rect->Attribute("stroke-width")),
						rect->Attribute("stroke"),
						rect->Attribute("id")));
			}
			else
			{
				retanguloVector.push_back(Retangulo(
						atof(rect->Attribute("x")),
						atof(rect->Attribute("y")),
						atof(rect->Attribute("width")),
						atof(rect->Attribute("height")),
						rect->Attribute("fill"),
						atof(rect->Attribute("stroke-width")),
						rect->Attribute("stroke"),
						rect->Attribute("id")));
			}
		}
	}
}

void movimentoAleatorio()
{
	static std::time_t ultimoTiro = std::time(nullptr);


	for (unsigned int i = 0; i < inimigoVector.size(); i++)
	{
		if (std::time(nullptr) - inimigoVector[i].ultimoTiro > freqTiroInimigo)
		{

			double deltaX = jogador.gX - inimigoVector[i].gX;
			double deltaY = jogador.gY - inimigoVector[i].gY;

			GLfloat angleInDegrees = atan2(deltaY, deltaX) * 180 / M_PI + 90;
			if (angleInDegrees < 0) angleInDegrees += 360;
			if (angleInDegrees > 360) angleInDegrees -= 360;

			if(fabs(inimigoVector[i].gTheta - angleInDegrees) <= 10.0)
			{
				inimigoVector[i].gTheta = angleInDegrees;
				inimigoVector[i].shot();
				inimigoVector[i].ultimoTiro = std::time(nullptr);
			}

			if (inimigoVector[i].gTheta - angleInDegrees < 0)
				inimigoVector[i].Rotate(2.0);
			else
				inimigoVector[i].Rotate(-2.0);

			continue;
		}


		if(rand() % 2 == 0)
		{
			GLfloat oldX = inimigoVector[i].gX;
			GLfloat oldY = inimigoVector[i].gY;

			inimigoVector[i].Move(inimigoVector[i].velHelicoptero);

			if(jogador.isMyPose(inimigoVector[i].gX, inimigoVector[i].gY, inimigoVector[i].r * 3) == true)
			{
				inimigoVector[i].gX = oldX;
				inimigoVector[i].gY = oldY;

			}

			for (unsigned int j = 0; j < inimigoVector.size(); j++)
				if(inimigoVector[j].isMyPose(inimigoVector[i].gX, inimigoVector[i].gY, inimigoVector[i].r * 3) == true && i != j)
				{
					inimigoVector[i].gX = oldX;
					inimigoVector[i].gY = oldY;

				}
		}
		else
		{
			//inimigoVector[i].Move(-inimigoVector[i].velHelicoptero);
		}

		if(rand() % 2 == 0)
		{
			inimigoVector[i].Rotate(2);
		}
		else
		{
			inimigoVector[i].Rotate(-2);
		}


	}
}

void antiColisao()
{
	if (jogador.gX + jogador.r > arena.width)
		jogador.gX = arena.width - jogador.r;
	if (jogador.gY + jogador.r > arena.height)
		jogador.gY = arena.height - jogador.r;

	if (jogador.gX - jogador.r < 0)
		jogador.gX = jogador.r;
	if (jogador.gY - jogador.r < 0)
		jogador.gY = jogador.r;

	for (unsigned int i = 0; i < inimigoVector.size(); i++)
	{
		if (inimigoVector[i].gX + inimigoVector[i].r > arena.width)
			inimigoVector[i].gX = arena.width - inimigoVector[i].r;
		if (inimigoVector[i].gY + inimigoVector[i].r > arena.height)
			inimigoVector[i].gY = arena.height - inimigoVector[i].r;

		if (inimigoVector[i].gX - inimigoVector[i].r < 0)
			inimigoVector[i].gX = inimigoVector[i].r;
		if (inimigoVector[i].gY - inimigoVector[i].r < 0)
			inimigoVector[i].gY = inimigoVector[i].r;
	}

}


void
display(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0, -1, 1);
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	if (gameover != 0)
	{
		  char *c;
		  char text[100] = "GameOver: ";
		  if (gameover == 1)
		  {
			  char message[100] = "voce perdeu";
			  glColor3f(1.0f, 0.0f, 0.0f);
			  strcat(text,message);
		  }

		  if (gameover == 2)
		  {
			  char message[100] = "voce ganhou";
			  glColor3f(0.0f, 0.0f, 1.0f);
			  strcat(text,message);
		  }


		  glRasterPos3f(glutGet(GLUT_WINDOW_WIDTH) /2 , glutGet(GLUT_WINDOW_HEIGHT) / 2,1);
		  for (c=text; *c != '\0'; c++) {
		    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
		  }
			glutSwapBuffers();
			return;

	}


	for(int i = 0; i < jogador.bullet.size(); i++)
	{
		for (unsigned int j = 0; j < inimigoVector.size(); j++)
		{
			if(inimigoVector[j].isMyPose(jogador.bullet[i].cx, jogador.bullet[i].cy) == true)
			{
				inimigoVector.erase(inimigoVector.begin() + j);
				 jogador.bullet.erase( jogador.bullet.begin() + i);
			}
		}
	}



	for (unsigned int i = 0; i < circuloVector.size(); i++)
	{
		if(circuloVector[i].isMyPose(jogador.gX, jogador.gY))
		{
			circuloVector.erase(circuloVector.begin() + i);
		}
	}

	if (jogador.isLanded == false)
	for (unsigned int i = 0; i < inimigoVector.size(); i++)
	for (unsigned int j = 0; j < inimigoVector[i].bullet.size(); j++)
	{
		if(jogador.isMyPose(inimigoVector[i].bullet[j].cx, inimigoVector[i].bullet[j].cy) == true)
		{
			gameover = 1;
		}
	}



	if(retanguloVector[0].isMyPose(jogador.gX, jogador.gY) == true && jogador.isLanded == true)
	{
		jogador.reabastecer();
	}

	if (jogador.dead == true)
		gameover = 1;

	if (circuloVector.size() == 0 && inimigoVector.size() == 0)
		gameover = 2;

	movimentoAleatorio();
	antiColisao();

	arena.DrawRect();

	for (unsigned int i = 0; i < retanguloVector.size(); i++)
	{
		retanguloVector[i].DrawRect();

	}
	for (unsigned int i = 0; i < circuloVector.size(); i++)
	{
		circuloVector[i].DrawCirc();
	}



	for (unsigned int i = 0; i < inimigoVector.size(); i++)
	{
		inimigoVector[i].DrawHelicoptero();
	}
	jogador.DrawHelicoptero();


	drawFuel();

	glutSwapBuffers();
}


void 
mouseCallback(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		jogador.Land(!jogador.isLanded);
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		jogador.shot();
	glutPostRedisplay();
}

void
motionCallback(int x, int y)
{
	static int lastX = x;

	if (x < lastX && jogador.gMetralhadoraAngle > -45.0)
		jogador.gMetralhadoraAngle -= 1.0;

	if (x > lastX && jogador.gMetralhadoraAngle < 45.0)
		jogador.gMetralhadoraAngle += 1.0;
	lastX = x;
	glutPostRedisplay();

}



int main(int argc, char** argv)
{
	char configFileName[256] = "";
	char *svgFileName;
	srand(time(NULL));

	if (argc > 1) strcat(configFileName,argv[1]);
	strcat(configFileName,"config.xml");

	svgFileName = readXMLConfig(configFileName);
	readSGV(svgFileName);


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(arena.width, arena.height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("trabalhocg4");
	glutMouseFunc(mouseCallback);
	glutPassiveMotionFunc(motionCallback);
    glutKeyboardFunc (keyPress);
	glutKeyboardUpFunc(keyUp);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
