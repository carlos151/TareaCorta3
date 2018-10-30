#ifndef _LISTA_H
#define	_LISTA_H
#include "NodoBinario.h"
using namespace std;


class Pila {
   public:
    Pila() : plista(NULL) {}

    void Push(pNodoBinario);
    bool Vacia() { return plista == NULL; }
	pNodoBinario Pop();
    int Size();
    
	pNodoBinario plista;
};

#endif	/* _LISTADOBLES_H */

