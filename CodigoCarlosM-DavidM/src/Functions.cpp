#include "../header/Functions.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>
int random_point( int desde, int hasta ){return rand() % hasta + desde;}
float distanciaEuclidiana(int x1,int y1,int x2,int y2)
{return sqrt(pow((x2-x1),2)+pow((y2-y1),2));}
