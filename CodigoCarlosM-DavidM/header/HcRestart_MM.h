#ifndef HCRESTART_MM
#define HCRESTART_MM
#include <iostream>
#include <vector>
#include <map>
#include "Class.h"
void principal(std::vector<int> &vehiculos,std::map<char,Leche> &t_leches, std::map<int,Nodo> &nodos, int MAX, char **argv);
void selectvehicle(std::vector<int> &vehiculos,std::map<char,Leche> &t_leches);
void updatefarms(std::map<int,Nodo> &nodos, std::vector<int> list);
void disableEnablefarms(map<int,Nodo> &nodos, vector<int> solution, bool disEna);
void imprimirvector(std::vector<int> v);
void insertarNoVisiatado(std::vector<int> listfarm_, std::vector<int> vehiculos, std::map<char,Leche> t_leches, std::map<int,Nodo> &nodos);
void insertandoNodo(int idruta, int idpos, int nodo, float costos, float costosback, int cuote);
std::vector<int> listfarm(std::map<int,Nodo> nodos, std::vector<char>listmilk);
std::vector<int> GeneratorsolutionsRandom(int cuotemilk,int capacity, std::vector<int> listfarm_, std::map<int,Nodo> nodos, char tmilk);
std::vector<int> BestNeighborhood(std::vector<int>Sc, std::map<int,Nodo> nodos);
#endif