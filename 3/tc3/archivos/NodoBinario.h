#ifndef _NODOBINARIO_H
#define	_NODOBINARIO_H

using namespace std;

class NodoBinario {
   public:

    NodoBinario(int index,string ced, NodoBinario *der = NULL, NodoBinario *izq = NULL, NodoBinario *sig=NULL, NodoBinario *ant=NULL):
        Hizq(izq), Hder(der), indice(index),cedula(ced), siguiente(sig), anterior(ant) {}


    int indice;
	std::string cedula;
    NodoBinario *Hizq, *Hder, *siguiente, *anterior;

    friend class Pila;
    friend class Binario;

    void InsertaBinario(int indice,string cedula);
};

typedef NodoBinario *pNodoBinario;

void PreordenR(NodoBinario* R);
void InordenR(NodoBinario* R);
void PostordenR(NodoBinario* R);
#endif	

