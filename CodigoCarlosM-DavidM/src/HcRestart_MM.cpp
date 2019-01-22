#include <iostream>
#include <vector>
#include <map>
#include "../header/HcRestart_MM.h"
#include "../header/Functions.h"
#include "../header/Class.h"
#include "../header/Read_write.h"

using namespace std;
/* Psudocodigo hill-climbing
 *
 *
 * crear un vector donde se guarden las calidades aceptadas ("nodo consistencia")
 * 
 * 
 * Procedure hill-climbing
 * 		t <- 0
 * 		inicilize Sbest
 * 		Repeat
 *			local <- FALSE
 *			Sc <- select a point at random
 *			evaluate Sc
 *			Repeat
 *				select Sn the best quiality point in N(Sc)
 *				If f(Sn) is better than f(Sc) Then
 *					Sc <- Sn
 *				Else
 *					local <- TRUE
 *			Until local
 *			t <- t + 1
 *			If Sc is better than Sbest Then
 *				Sbest <- Sc
 *
 *		Until t = MAX
 *
 */


float Sb_costo;//costo de la mejor solucion
float Sc_costo;//costo de la solucion candidata
float Sn_costo;//costo de la solucion nueva
int Sb_cuote;//cuota de la mejor solucion
int Sc_cuote;//cuota de la solucion candidata
int cuotemilk;//cuota de la leche solicitada
int capacity;//capacidad del vehiculo

vector< vector<int> > routesvec;//mejores rutas
vector<float> costesvec;//lista de costos
vector<int> cuotevec;//lista de cuotas

void selectvehicle(vector<int> &vehiculos,map<char,Leche> &t_leches)
{
	int aux=0;
	
	bool cambio=false;
	int itv = 0;//vehiculo comparado
	while(true)
	{
		for(map<char,Leche>::iterator it= t_leches.begin(); it!= t_leches.end(); it++)
		{
			Leche auxleche= it->second;
			if( ( vehiculos[itv]-auxleche.getCuota() ) <= 0 )//si la capacidad del vehiculo es menor que es de la leche se hace cambio de vehiculo
			{
				int x= vehiculos[itv];
				if( itv< vehiculos.size()-1 )
				{
					vehiculos[itv]=vehiculos[itv+1];
					vehiculos[itv+1]=x;
				}
				else
				{
					vehiculos[itv]=vehiculos[0];
					vehiculos[0]=x;
				}
				cambio=true;
				it=t_leches.begin();
				itv=0;
			}
		}
		if(!cambio){break;}
		else{cambio=false;}
	}
}
void updatefarms(map<int,Nodo> &nodos, vector<int> solution)
{
	for(vector<int>::iterator it = solution.begin(); it != solution.end(); it++ )
	{
		Nodo aux = nodos[*it];
		aux.setVisitado(true);
		nodos[*it]=aux;
	}
}
//Funcion para seleccionar las grajas candidatas para buscar la solucion
vector<int> listfarm(map<int,Nodo> nodos, vector<char>listmilk)
{
	vector<int> listfarm_;//lista de id de granjas
	Nodo aux;
	//iterador para obtener las granjas con las leches aceptadas
	for(map<int,Nodo>::iterator it= nodos.begin(); it!= nodos.end(); it++)
	{
		aux = it->second;
		//iterador de leches, Tipo de leches a iterar [A]-> [A,B]-> [A,B,C]
		for (vector<char>::iterator itv = listmilk.begin() ; itv != listmilk.end(); ++itv)
		{
			//Se inserta la granja que tenga la calidad de leches aceptada.
			if(aux.getCalidad() == *itv && !aux.getVisitado() )//&& !aux.getDisableEnable())
			{
				//cout<<it->first<<"\t";
				//cout<<aux.getCalidad()<<"\n";
				listfarm_.push_back( it->first );
				break;
			}
		}
	}
	return listfarm_;
}
void imprimirvector(vector<int> v)
{
	for(int i =0; i < v.size() ; i++)
	{
		cout<<v[i]<<" ";
	}
	cout<<"\n";
}
//Funcion que busca el mejor vecino de una solucion
vector<int> BestNeighborhood(vector<int>Sc, map<int,Nodo> nodos)
{

	float Dback;//distancia nodo anterior
	float Dnext;//distancia nodo siguiente
	float Dactual = Sc_costo;//distancia actual
	float Dneighbor=0;//distancia nueva;
	float Dbestneighbor=0;//distancia del mejor vecino
	vector<int>bestneighbor;
	vector<int>auxSc=Sc;
	Nodo actualnodo1;
	Nodo actualnodo2;
	Nodo backnodo;
	Nodo nextnodo;
	int idmv;

	for(int i = 1; i < Sc.size()-2 ; i++)
	{
		idmv = auxSc[i];
		actualnodo1 = nodos[ idmv ];
		backnodo = nodos[ auxSc[i-1] ];
		Dback = distanciaEuclidiana( backnodo.getX() , backnodo.getY() , actualnodo1.getX() , actualnodo1.getY() );
		actualnodo2 =nodos[ auxSc[i+1] ];
		nextnodo = nodos[ auxSc[i+2] ];
		Dnext = distanciaEuclidiana( actualnodo2.getX() , actualnodo2.getY() , nextnodo.getX() , nextnodo.getY() );
		Dactual = Dactual - Dback - Dnext;
		auxSc[i] = auxSc[i+1];
		auxSc[i+1] = idmv;

		Dback = distanciaEuclidiana( backnodo.getX() , backnodo.getY() , actualnodo2.getX() , actualnodo2.getY() );
		Dnext = distanciaEuclidiana( actualnodo1.getX() , actualnodo1.getY() , nextnodo.getX() , nextnodo.getY() );
		Dactual = Dactual + Dback + Dnext;
		Dneighbor = Dactual;
		if(Dbestneighbor == 0)
		{
			Dbestneighbor = Dneighbor;
			Dactual = Dneighbor;
			bestneighbor = auxSc;
		}
		else if(Dbestneighbor > Dneighbor)//si la distancia del nuevo vecino es menor que el mejor vecino se cambia y resetean los valores
		{
			Dbestneighbor = Dneighbor;
			Dactual = Dneighbor;
			bestneighbor = auxSc;
		}
	}
	Sn_costo = Dbestneighbor;
	return bestneighbor;
}
// Funcion que genera una solucion escogiendo granjas al azar desde el vecto de granjas candidatas
vector<int> GeneratorsolutionsRandom(int cuotemilk,int capacity,vector<int> listfarm_, map<int,Nodo> nodos, char tmilk)
{
	vector<int> solution;
	vector<int>auxlistfarm = listfarm_;
	int cuote=0;
	int cost=0;
	int aux; //aux para calcula la nueva cuota
	int idfarm;// se obtiene el id de la granja
	char auxtmilk=' ';//comparador de leche
	Nodo nodoactual;
	Nodo nodoback;
	//	se agregaria al principio y al final el id de la planta en el vector de soluciones
	solution.push_back(1);//agrego 1 ya que ese es el id de la planta y para calcular la distancia con el punto siguiente para el costo.
	int poss;//Posicion del vector a buscar
	vector<int> noinsert;
	noinsert.clear();
	vector<int>::iterator it;
	while(true)
	{
		aux = cuote;
													// desde, hasta
		if(auxlistfarm.size()>1){poss = random_point(   0   , auxlistfarm.size()-1 );}
		else{poss=0;}

		idfarm = auxlistfarm[ poss ];
		nodoactual = nodos[idfarm];
		aux = aux + nodoactual.getCuota();//calculo de cuota acumulada si se agruega el nuevo nodo
		if(aux <= capacity)
		{
			solution.push_back(idfarm);
			cuote = aux;
			nodoback = nodos[ solution[solution.size()-2] ];//se obtiene el nodo anterior para hacer el calculo de la distancia
			cost = cost + distanciaEuclidiana( nodoactual.getX() , nodoactual.getY() , nodoback.getX() , nodoback.getY() );
			if(auxtmilk!=' ')
			{
				if(nodoactual.getCalidad() > auxtmilk )
				{auxtmilk=nodoactual.getCalidad();}
			}
			else { auxtmilk = nodoactual.getCalidad(); }
		}
		auxlistfarm.erase (auxlistfarm.begin()+poss);//elimina el nodo de la posicion i

		if(cuote >= cuotemilk && cuote <= capacity)//se verifica si la solucion cumple con la cuota
		{
			if(auxtmilk == tmilk)
			{
				break;
			}//se verifica si la leche actual de vehiculo es la que se necesita
			else//si no es se resetea la solución
			{
				auxlistfarm = listfarm_;
				cuote = 0;
				cost = 0;
				noinsert.clear();
				solution.clear();
				solution.push_back(1);
			}
		}
		else
		{
			if(auxlistfarm.size()==0)//si se itera y no se encuentra solucion se resetea para buscar nuevamente una nueva solucion
			{
				auxlistfarm = listfarm_;
				cuote = 0;
				cost = 0;
				noinsert.clear();
				solution.clear();
				solution.push_back(1);
			}
		}
	}
	solution.push_back(1);
	nodoactual = nodos[1];
	nodoback = nodos[ solution.size()-2 ];
	Sc_cuote = cuote;
	Sc_costo = cost + distanciaEuclidiana( nodoactual.getX() , nodoactual.getY() , nodoback.getX() , nodoback.getY() );

	return solution;
}
//inserta la granja en la ruta y posicion que es de menor costo
void insertandoNodo(int idruta, int idpos, int nodo, float costos, float costosback, int cuote)
{
	int size = routesvec[idruta].size()-1;
	vector<int>aux;
	//vector<int>
	//imprimirvector(routesvec[idruta]);
	for(int i =  size ; i >= idpos ; i--)
	{
		aux.push_back( routesvec[idruta].back() );
		routesvec[idruta].pop_back();
	}
	//imprimirvector(routesvec[idruta]);
	routesvec[idruta].push_back(nodo);
	while(!aux.empty())
	{
		routesvec[idruta].push_back( aux.back() );
		aux.pop_back();
	}
	costesvec[idruta] = costosback+costos;
	cuotevec[idruta] = cuote;
}

//Buscar la ruta y la posicion de cada granja que no ha sido visitada
void insertarNoVisiatado(vector<int> listfarm_, vector<int> vehiculos,map<char,Leche> t_leches, map<int,Nodo> &nodos)
{
	int Sb_idruta;//identificador de la mejor ruta en la cual se va a insertar
	int Sb_pos;//mejor posicion en el cual se insertara la granja
	int sn_cuote;//cuote de la solucion nueva
	bool insert;
	Nodo toinsert;
	Nodo nodoback;
	Nodo nodonext;
	vector<int> auxruta;
	float auxcoste;
	int auxcuote;
	int auxcap;//capacidad del vehiculo
	float dback;
	float dnext;
	float dactual;
	float costosback;//costo de la ruta menos es costo de la ruta en la posicion j-1 y j 
	char milk;
	char Sb_milk;
	float aa;
	int i;
	for(vector<int>::iterator it = listfarm_.begin(); it!= listfarm_.end(); it++)
	{
		toinsert = nodos[*it];
		insert = false;
		Sc_costo=0;
		Sc_cuote=0;
		Sn_costo=0;
		sn_cuote=0;
		Sb_costo=0;
		Sb_cuote=0;
		Sb_pos=-1;
		Sb_milk = '-';
		if(toinsert.getCalidad() == 'A'){ i = 0; milk = 'A';}
		else if(toinsert.getCalidad() == 'B'){ i = 1; milk = 'B';}
		else { i = 2; milk = 'C';}
		for( i ; i < routesvec.size(); i++, milk++ )
		{
			auxruta = routesvec[i];
			auxcoste = costesvec[i];
			auxcuote = cuotevec[i];
			auxcap = vehiculos[i];
			for(int j = 1; j < auxruta.size()-1 ; j++)
			{
				if( ( auxcuote + toinsert.getCuota() ) <=  auxcap )
				{
					insert =true;
					nodoback = nodos[ auxruta [ j-1 ] ];
					nodonext = nodos[ auxruta [ j ] ];
					dback = distanciaEuclidiana( nodoback.getX() , nodoback.getY() , nodonext.getX() , nodonext.getY() );
					dactual = auxcoste - dback;
					dback = distanciaEuclidiana( nodoback.getX() , nodoback.getY() , toinsert.getX() , toinsert.getY() );
					dnext = distanciaEuclidiana( toinsert.getX() , toinsert.getY() , nodonext.getX() , nodonext.getY() );
					Sc_costo = dback + dnext;
					Sc_cuote = auxcuote + toinsert.getCuota();
					
					if(Sb_cuote == 0)
					{
							Sb_idruta= i;
							Sb_pos = j;
							Sb_costo = Sc_costo;
							Sb_cuote = Sc_cuote;
							costosback = dactual;
							Sb_milk = milk;
					}
					else
					{
						if(Sc_costo < Sb_costo)
						{
							Sb_idruta= i;
							Sb_pos = j;
							Sb_costo = Sc_costo;
							Sb_cuote = Sc_cuote;
							costosback = dactual;
							Sb_milk = milk;
						}
					}
				}
				else
				{
					aa= ( auxcuote + toinsert.getCuota() );
				}
			}
		}
		if(insert)
		{
			insertandoNodo(Sb_idruta, Sb_pos, *it, Sb_costo, costosback, Sb_cuote);
			toinsert.setVisitado(true);
			nodos[*it] = toinsert;
		}
	}
	
}

//Funcion principal de Hill-clining+restart Mejor mejora
void principal(vector<int> &vehiculos,map<char,Leche> &t_leches, map<int,Nodo> &nodos, int MAX, char **argv)
{
	char aux = 'A';//Calidad de leche inicial
	int itv = 0; //iterador de el vehiculo
	Leche leche;
	vector<char> listmilk;
	vector<int> listfarm_;
	vector<int> Sb;//vector de la mejor solucion
	vector<int> Sc;//Vector de la solucion candidata
	vector<int> Sn;//mejor vecino;

	int t_profit=0;//total de ganancia
	float t_trans_cost=0;//total de costos de transporte
	float profit_for_milk=0;//ganancia por leche

	int t;//contador de iteraciones
	bool local;
	for(char i = aux; i< aux+t_leches.size(); i++)//Se van iterando Las leches con la cual se va a realizar la busqueda
	{
		Sc_costo=0;
		Sc_cuote=0;
		Sn_costo=0;
		Sb_costo=0;
		Sb_cuote=0;
		leche = t_leches[i];
		cuotemilk= leche.getCuota();//Cuota de la leche
		capacity  = vehiculos[itv]; //Se obtiene la capacidad del vehiculo
		listmilk.push_back(i);//agrega la leche a un vector donde se van guardando las lechas que se han iterado
		listfarm_ = listfarm(nodos,listmilk);//se obtiene la lista de granjas candidatas
		t = 0;
		do{
			
			local = false;
			Sc = GeneratorsolutionsRandom(cuotemilk,capacity,listfarm_,nodos,i);
			
			do{
				Sn = BestNeighborhood(Sc, nodos);//se obtiene la solucion del mejor vecino
				if(Sn_costo < Sc_costo)
				{
					Sc = Sn;
					Sc_costo = Sn_costo;
				}
				else
				{local = true;}
			}while(!local);
			t++;
			if(Sb_costo == 0)
			{
				Sb = Sc;
				Sb_costo = Sc_costo;
				Sb_cuote = Sc_cuote;
			}
			else if( Sc_costo < Sb_costo)
			{
				Sb = Sc;
				Sb_costo = Sc_costo;
				Sb_cuote = Sc_cuote;
			}
		}while(t<=MAX);
		updatefarms(nodos,Sb);
		/**Se guardan las mejores soluciones**/
		routesvec.push_back(Sb);
		costesvec.push_back(Sb_costo);
		cuotevec.push_back(Sb_cuote);
	}
	listfarm_ = listfarm(nodos,listmilk);//se obtiene la lista de granjas candidatas No Visitadas
	insertarNoVisiatado(listfarm_, vehiculos, t_leches, nodos);
	listfarm_ = listfarm(nodos,listmilk);//se obtiene la lista de granjas candidatas No Visitadas
	Escritura(argv, routesvec, costesvec, cuotevec, t_leches, MAX, vehiculos, nodos);
}
