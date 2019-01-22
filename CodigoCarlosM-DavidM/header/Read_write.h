#ifndef READ_WRITE
#define READ_WRITE
#include <iostream>
#include <map>
#include <vector>
#include "Class.h"
void Lectura(char **argv, std::vector<int> &vehiculos, std::map<char,Leche> &t_leches, std::map<int,Nodo> &nodos);
void Escritura(char **argv,std::vector< std::vector<int> > routes, std::vector<float>  costes, std::vector<int> cuote, std::map<char,Leche> t_leches, int MAX, std::vector<int> vehiculos,std:: map<int,Nodo> nodos);
#endif