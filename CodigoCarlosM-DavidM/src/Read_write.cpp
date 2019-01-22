#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <sstream>

#include "../header/Read_write.h"

using namespace std;
void Escritura(char **argv,vector< vector<int> > routes, vector<float> costes, vector<int> cuote, map<char,Leche> t_leches, int MAX, vector<int> vehiculos, map<int,Nodo> nodos)
{
	string filename = argv[1];
	string filename2 = argv[1];
	ostringstream max;
	max<<MAX;
	filename="Salida/"+filename.substr(0,filename.find("."))+"_"+max.str()+".txt";
	filename2="Salida/"+filename2.substr(0,filename2.find("."))+"_"+max.str()+".csv";
	ofstream output(filename.c_str(),ios_base::out);
	ofstream output2(filename2.c_str(),ios_base::out);

	char j='A';
	vector<int>aux;
	int i;
	int k;

	float t_profit=0;
	float t_trans_cost=0;
	float profit_for_milk=0;

	Leche leche;
	for( i = 0; i < routes.size(); i++)
	{
		leche = t_leches[j];
		t_profit = t_profit + ( cuote[i] * leche.getValor() ) - costes[i];
		t_trans_cost = t_trans_cost + costes[i];
		profit_for_milk = profit_for_milk + (cuote[i] * leche.getValor() );
	}


	j='A';
	output<<t_profit<<"\t"<<t_trans_cost<<"\t"<<profit_for_milk<<"\n";
	output2<<t_profit<<";"<<t_trans_cost<<";"<<profit_for_milk<<"\n";
	for( i=0 ; i< routes.size(); i++)
	{
		aux = routes[i];
		for(k = 0; k < aux.size()-1; k++)
		{output<<aux[k]<<"-";output2<<aux[k]<<"-";}
		output<<aux[ aux.size()-1 ];
		output2<<aux[ aux.size()-1 ];
//		output<<"\t"<<costes[i]<<"\t"<<cuote[i]<<"\t"<<j<<"\t"<<vehiculos[i]<<"\n";
//		output2<<";"<<costes[i]<<";"<<cuote[i]<<";"<<j<<";"<<vehiculos[i]<<"\n";
		output<<"\t"<<costes[i]<<"\t"<<cuote[i]<<"\t"<<j<<"\n";
		output2<<";"<<costes[i]<<";"<<cuote[i]<<";"<<j<<"\n";
		j++;
	}

//	output<<"\nMAX "<<MAX<<"\n";
//	output<<"VEHICULOS\nLECHE\tCAPACIDAD\n";
	output2<<"\nMAX;"<<MAX<<"\n";
	output2<<"VEHICULOS\nLECHE;CAPACIDAD\n";
	j='A';
	for(i = 0 ; i < vehiculos.size() ; i++, j++)
	{
//		output<<j<<"\t"<<vehiculos[i]<<"\n";
		output2<<j<<";"<<vehiculos[i]<<"\n";
	}
//	output<<"GRANJAS NO VISITADAS\nID\tCUOTA\tLECHE\n";
	output2<<"GRANJAS NO VISITADAS\nID;CUOTA;LECHE\n";
	for(map<int,Nodo>::iterator it= nodos.begin(); it!= nodos.end(); it++)
	{
		Nodo auxnodo = it->second;
		//cout<<it->first<<"\t";
		if( !auxnodo.getVisitado() )
		{//output<<it->first<<"\t"<<auxnodo.getCuota()<<"\t"<<auxnodo.getCalidad()<<"\n";
		output2<<it->first<<";"<<auxnodo.getCuota()<<";"<<auxnodo.getCalidad()<<"\n";}
	}

	output.close();
	output2.close();
}
void Lectura(char **argv, vector<int> &vehiculos, map<char,Leche> &t_leches, map<int,Nodo> &nodos)
{
	string line;
	string filename = argv[1];
	filename="Entrada/"+filename;
	ifstream input(filename.c_str());
	int cont=0;
	int cant=0;

	while(!input.eof())
	{
		getline(input,line);
		if(line.size()!=0)
		{
			string aux;
			int cuota;
			char i;//calidad
			istringstream(line)>>cant;
			if(cont==0)//ingresan los vehiculos
			{
				getline(input,line);
				stringstream ss(line);
				while (cant>0)
				{
					ss>>aux;
					int value;
					istringstream(aux)>>value;
					vehiculos.push_back(value);
					cant-=1;
				}
			}
			else if(cont==1)
			{
				string val;
				i='A';
				float ival;
				getline(input,line);//fila de cuotas
				stringstream ss(line);
				getline(input,val);//fila de valores
				stringstream auxss(val);
				while(cant>0)
				{
					ss>>aux;//cuota de leche
					auxss>>val;
					istringstream(aux)>>cuota;
					istringstream(val)>>ival;
					Leche newleche = Leche(cuota,ival);
					t_leches.insert( pair<char,Leche>(i,newleche) );
					i++;
					cant-=1;
				}	
			}
			else if(cont==2)
			{
				int id,x,y;
				while(cant>0)
				{
					getline(input,line);
					stringstream ss(line);
					ss>>aux;
					istringstream(aux)>>id;
					ss>>aux;
					istringstream(aux)>>x;
					ss>>aux;
					istringstream(aux)>>y;
					ss>>i;
					ss>>aux;
					istringstream(aux)>>cuota;
					Nodo nodo = Nodo(x,y,i,cuota);
					nodos.insert( pair<int,Nodo>(id,nodo) );
					cant-=1;
				}
			}
			cont++;
		}
	}
	input.close();

}