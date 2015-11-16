all:
	g++  trabalhocg.cpp circulo.cpp retangulo.cpp helicoptero.cpp tinyxml/tinyxml.cpp  tinyxml/tinystr.cpp tinyxml/tinyxmlparser.cpp  tinyxml/tinyxmlerror.cpp -o trabalhocg -lglut -lGL -std=c++11 	
clean:
	rm trabalhocg
