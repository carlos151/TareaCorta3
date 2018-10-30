#include <iostream>
#include <string>
#include "Pila.h"
#include "NodoBinario.h"
#include "Binario.h"

void NodoBinario::InsertaBinario(int indice,string cedula)
{
    if(cedula < this->cedula){
        if(Hizq==NULL){
            Hizq = new NodoBinario(indice,cedula);
        }else{
            Hizq->InsertaBinario(indice,cedula);
        }
    }else{
        if(Hder==NULL){
            Hder = new NodoBinario(indice, cedula);
        }else{
            Hder->InsertaBinario(indice, cedula);
        }
    }
}

void Binario::InsertaNodo(int indice, string cedula)
{
    if(raiz==NULL){
        raiz = new NodoBinario(indice, cedula);
    }else{
        raiz->InsertaBinario(indice, cedula);
    }
}

void Binario::PreordenI(){
    NodoBinario *Act = raiz;
    Pila p;
    while(p.Vacia()==false || (Act!=NULL)){
        if(Act!=NULL){
            cout << Act->indice << ";" << Act->cedula << " - ";
            p.Push(Act);
            Act = Act->Hizq;
        }else{
            Act=p.Pop();
            Act=Act->Hder;
        }
    }
}

void Binario::InordenI(){
    NodoBinario *Act = raiz;
    Pila p;
    bool band=true;
    while(band){
        
        while(Act!=NULL){
            p.Push(Act);
            Act = Act->Hizq;
        }
        if(!p.Vacia()){
            Act=p.Pop();
			cout << Act->indice << ";" << Act->cedula << " - ";
            Act=Act->Hder;          
        }
        if(p.Vacia() & Act==NULL){
            break;
        }
    }
}

void Binario::PostordenI(){
    NodoBinario *Act = raiz;
    Pila p;
    Pila p2;
    while(!p.Vacia() || Act!=NULL){
        if(Act!=NULL){
            p2.Push(new NodoBinario(Act->indice,Act->cedula));            
            p.Push(Act);
            Act = Act->Hder;
        }else{            
            Act=p.Pop();
            Act = Act->Hizq;
        }
    }
    while(!p2.Vacia()){
        NodoBinario *salida=p2.Pop();
		cout << salida->indice << ";" << salida->cedula << " - ";
    }
}

int Binario::buscar(string cedula) {
	NodoBinario *actual = raiz;
	while (actual != NULL) {
		if (actual->cedula == cedula) {
			return actual->indice;
		}
		else if (actual->cedula < cedula) {
			actual = actual->Hder;
		}
		else {
			actual = actual->Hizq;
		}
	}
	return -1;
}

void PreordenR(NodoBinario *R){
    
    if(R==NULL){
        return;
    }else{
		cout << R->indice << ";" << R->cedula << " - ";
        PreordenR(R->Hizq);
        PreordenR(R->Hder);
    }
}

void InordenR(NodoBinario *R){

    if(R==NULL){
        return;
    }else{
        InordenR(R->Hizq);
		cout << R->indice << ";" << R->cedula << " - ";
        InordenR(R->Hder);
    }
}

void PostordenR(NodoBinario *R){

    if(R==NULL){
        return;
    }else{
        PostordenR(R->Hizq);
        PostordenR(R->Hder);
		cout << R->indice << ";" << R->cedula << " - ";
    }
}