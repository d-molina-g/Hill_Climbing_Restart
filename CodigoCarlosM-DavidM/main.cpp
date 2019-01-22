#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <dirent.h>//manejo de directorio
#include <map>
#include <vector>
#include <stdlib.h>//utilizado para srand, rand
#include "header/Functions.h"
#include "header/Read_write.h"
#include "header/HcRestart_MM.h"
#include "header/Class.h"
using namespace std;
bool existFile(string filename);
bool existDir(string dir);
void list_dir(string dir);
int main(int argc, char **argv)
{
	string input_dir = "Entrada";
	string output_dir = "Salida";
	bool exit=false;
	if( argc != 3)
	{
		cout<<"Error: ./main inputfile MAX\n";
		list_dir(input_dir);
		return 0;
	}
	
	string filename=argv[1];
	int MAX;
	istringstream(argv[2])>>MAX;
	if(MAX<0){cout<<"el parametro MAX debe ser mayor a cero\n";exit=true;}
	if(!existDir(input_dir)){cout<<"La carpeta 'Entrada' No existe. Favor de crearla y dejar archivos de entrada dentro.\n";exit=true;}
	if(!existDir(input_dir)){cout<<"La carpeta 'Salida' No existe. Favor de crearla.\n";exit=true;}
	if(!existFile(filename)){cout<<"El archivo no existe. Asegurece que el archivo se encuetra en la carpeta Entrada.\n";list_dir(input_dir);exit=true;}
	if(exit){cout<<"Ejecucion termiada...\n";return 0;}
	cout<<"Ejecutando...\n";

	srand(time(NULL));//resetea rand

	vector<int> vehiculos;
	map<char,Leche> t_leches;
	map<int,Nodo> nodos;
	Lectura(argv, vehiculos,t_leches,nodos);
	selectvehicle(vehiculos,t_leches);
	principal(vehiculos,t_leches,nodos,MAX,argv);
/*
	cout<<"Lista vehiculos:\n";
	for (vector<int>::iterator it = vehiculos.begin() ; it != vehiculos.end(); ++it)
		cout<< *it<<' ';
	cout<<"\nLista Tipo de Leches:\n";
	cout<<"Tipo\tcuota\tvalor\n";
	for(map<char,Leche>::iterator it= t_leches.begin(); it!= t_leches.end(); it++)
	{
		Leche auxleche= it->second;
		cout<<it->first<<"\t";
		auxleche.imprimir();
	}
	cout<<"Lista Planta y Granjas:\n";
	cout<<"id\tx\ty\tcalidad\tcuota\tVisitado\n";
	for(map<int,Nodo>::iterator it= nodos.begin(); it!= nodos.end(); it++)
	{
		Nodo auxnodo = it->second;
		cout<<it->first<<"\t";
		auxnodo.imprimir();
	}

	cout << '\n';
*/	cout<<"Ejecucion terminada...\n";
	return 0;
}

bool existFile(string filename)
{
	FILE *archivo;
	filename = "Entrada/"+filename;
	if(archivo = fopen(filename.c_str(),"r"))
	{
		fclose(archivo);
		return true;
	}
	else{return false;}
}

bool existDir(string dir)
{
	DIR *directorio;
	if(directorio= opendir(dir.c_str()) )
	{
		closedir(directorio);
		return true;
	}
	else{return false;}
}
void list_dir(string dir)
{
	DIR *directorio;
	struct dirent *elemento;
	if(directorio=opendir(dir.c_str()))
	{
		cout<<"(Carpeta Entrada) inputfiles: ";
		while(elemento=readdir(directorio))
		{
			if(elemento->d_name[0]!='.')
			{cout<<elemento->d_name<<" ";}
		}
		cout<<"\n";
	}
	closedir(directorio);
}