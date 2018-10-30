#ifndef _BINARIO_H
#define	_BINARIO_H
#include "NodoBinario.h"

using namespace std;

class Binario{
public:
    pNodoBinario raiz;

    Binario():raiz(NULL){}

    void InsertaNodo(int indice,string cedula);
    void PreordenI();
    void InordenI();
    void PostordenI();
	void Borrar(string cedula);
	int buscar(string cedula);


};



#endif	/* _BINARIO_H */

