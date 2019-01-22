#ifndef CLASS
#define CLASS
#include <iostream>
using namespace std;

class Nodo
{
	private:
		int x;
		int y;
		char calidad;
		int cuota;
		bool visitado;
	public:
		Nodo(int,int,char,int);//Constructor
		Nodo();
		void setX(int);
		void setY(int);
		void setCalidad(char);
		void setCuota(int);
		void setVisitado(bool);
		int getX();
		int getY();
		char getCalidad();
		int getCuota();
		bool getVisitado();
		void imprimir();
};

class Leche
{
	private:
		int cuota;
		float valor;
	public:
		Leche(int,float);
		Leche();
		void setCuota(int);
		void setValor(float);
		int getCuota();
		float getValor();
		void imprimir();
};

#endif