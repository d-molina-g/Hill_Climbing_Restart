#include <iostream>
#include "../header/Class.h"
using namespace std;
Nodo::Nodo(int _x, int _y, char _calidad, int _cuota)
{
	x = _x;
	y = _y;
	calidad = _calidad;
	cuota = _cuota;
	visitado = false;
}
Nodo::Nodo(){x=0;y=0;calidad='-';cuota=0;visitado=false;}
void Nodo::setX(int _x){x = _x;}
void Nodo::setY(int _y){y = _y;}
void Nodo::setCalidad(char _calidad){calidad = _calidad;}
void Nodo::setCuota(int _cuota){cuota = _cuota;}
void Nodo::setVisitado(bool _visitado){visitado = _visitado;}
int Nodo::getX(){return x;}
int Nodo::getY(){return y;}
char Nodo::getCalidad(){return calidad;}
int Nodo::getCuota(){return cuota;}
bool Nodo::getVisitado(){return visitado;}
void Nodo::imprimir(){cout<<x<<"\t"<<y<<"\t"<<calidad<<"\t"<<cuota<<"\t"<<visitado<<"\n";}

Leche::Leche(int _cuota, float _valor)
{
	cuota = _cuota;
	valor = _valor;
}
Leche::Leche(){cuota=0;valor=0.0;}
void Leche::setCuota(int _cuota){cuota = _cuota;}
void Leche::setValor(float _valor){valor = _valor;}
int Leche::getCuota(){return cuota;}
float Leche::getValor(){return valor;}
void Leche::imprimir(){cout<<cuota<<"\t"<<valor<<"\n";}
