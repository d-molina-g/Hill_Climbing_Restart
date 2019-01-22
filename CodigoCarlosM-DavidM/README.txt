*****************************************************************
* Código realizado por: Carlos Manchego - David Molina          *
* Fecha : 26/11/2018                                            *
* Algoritmo: Hill Climbing + Restart Mejor Mejora               *
*****************************************************************
* El código cuenta con un archivo makefile para su compilación,	*
* limpiado y ejecución.                                         *
*                                                               *
* Para ejecutar el programa ejecutar desde consola:             *
*                                                               *
* make clean                                                    *
* make                                                          *
* make run                                                      *
*                                                               *
* o ejecutar directamente el archivo main                       *
*                                                               *
* make clean                                                    *
* make                                                          *
* ./main nombreArchivoEntrada MAX                               *
*                                                               *
*                                                               *
* nombreArchivoEntrada: los archivos de entrada deben de estar  *
* localizados en la carpeta Entrada                             *
* MAX:  es el numero de iteraciones que realizara como restart  *
*---------------------------------------------------------------*
* Los archivos de salida se generaran en la carpeta Salida.     *
* se generan 2 tipos de archivos uno de extensión .csv y .txt   *
* los nombres de los archivos esta dado por:                    *
*                                                               *
* nombreArchivoEntrada_MAX.txt                                  *
* nombreArchivoEntrada_MAX.csv                                  *
*                                                               *
* El archivo solicitado como salida es el de extensión .txt     *
*                                                               *
* El archivo de salida .csv se genera con información adicional *
* a lo solicitado:                                              *
* - MAX                                                         *
* - Leche y capacidad del vehiculo asignado                     *
* - granjas no visitadas (id, cuota, tipo de leche)             *
*                                                               *
*****************************************************************
