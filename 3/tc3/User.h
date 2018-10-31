#pragma once

#ifndef _USER_H
#define	_USER_H

#include <iostream>

using namespace std;

class User {
	public:
		User(int pIndice,string pCedula,string pNombre) {
			indice = pIndice;
			cedula = pCedula;
			nombre = pNombre;
		}

	int indice;
	string cedula;
	string nombre;
};

#endif