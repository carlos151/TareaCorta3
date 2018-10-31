#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "archivos/Binario.h"
#include "archivos/listaSimple.cpp"
#include "User.h"

std::string extraerCedula(std::string datos) {
	std::string cedula;
	bool bandera = false;
	for (int i = 0; i < datos.length(); i++) {
		if (datos[i] != *";") 
			cedula.operator+=(datos[i]);
		else
			break;
	}
	return cedula;
}

void crearArchivoIndices() {
	int indice = 1;
	lista cedulas; // Lista para buscar cedulas repetidas
	std::string datosBuffer;
	std::ifstream clientesFile; 
	std::ofstream indicesFile; 
	indicesFile.open("indices.txt");
	clientesFile.open("Clientes.txt");
	while (!clientesFile.eof()) {
		getline(clientesFile, datosBuffer);
		string cedula,nombre;
		bool bandera = false;
		for (int i = 0; i < datosBuffer.length(); i++) {
			if (datosBuffer[i] != *";") {
				if (!bandera)
					cedula.operator+=(datosBuffer[i]);
				else
					nombre.operator+=(datosBuffer[i]);
			}
			else
				bandera = true;
		}
		if (cedulas.buscar(stoi(cedula))) {
			cout << "CEDULA REPETIDA: " << cedula << endl;
		}
		else {
			cedulas.InsertarFinal(stoi(cedula));
			indicesFile << indice << ";" << cedula << ";" << nombre << endl;
			indice++;
		}
	}
	cedulas.~lista();
	clientesFile.close();
	indicesFile.close();
}

void insertarUsuario(Binario &arbol,std::string datos) {
	string cedula, indice, nombre;
	bool bandera = false;
	bool bandera1 = false;
	for (int i = 0; i < datos.length(); i++) {
		if (datos[i] != *";") {
			if (!bandera)
				indice.operator+=(datos[i]);
			else if (bandera && !bandera1)
				cedula.operator+=(datos[i]);
			else
				nombre.operator+=(datos[i]);
		}
		else if (!bandera)
			bandera = true;
		else
			bandera1 = true;
	}
	arbol.InsertaNodo(stoi(indice), cedula);
}

Binario crearArbol() {
	Binario arbol;
	std::string datosBuffer;
	std::ifstream indicesFile;
	indicesFile.open("indices.txt");
	while (!indicesFile.eof()) {
		getline(indicesFile, datosBuffer);
		if(!datosBuffer.empty())
			insertarUsuario(arbol,datosBuffer);
	}
	return arbol;
}

void iniciarCache(User *cache[20]) {
	string datos;
	ifstream indicesFile;
	indicesFile.open("indices.txt");
	for (int i = 0; i < 20; i++) {
		getline(indicesFile, datos);
		string cedula, indice, nombre;
		bool bandera = false;
		bool bandera1 = false;
		for (int i = 0; i < datos.length(); i++) {
			if (datos[i] != *";") {
				if (!bandera)
					indice.operator+=(datos[i]);
				else if (bandera && !bandera1)
					cedula.operator+=(datos[i]);
				else
					nombre.operator+=(datos[i]);
			}
			else if (!bandera)
				bandera = true;
			else
				bandera1 = true;
		}
		cache[i] = new User(stoi(indice), cedula, nombre);
	}
}

void imprimirCache(User *cache[20]) {
	for (int i = 0; i < 20;i++) {
		if (cache[i] != NULL)
			cout << cache[i]->cedula << ";" << cache[i]->nombre << "-> ";
	}
	cout << endl;
}

int buscarEnCache(int indice, User *cache[20]) {
	for (int i = 0; i < 20; i++) {
		if (cache[i] != NULL && cache[i]->indice == indice) {
			cout << "Cliente encontrado en cache: " << cache[i]->cedula << ";" << cache[i]->nombre << endl;
			return cache[i]->indice;
		}
	}
	cout << "Cliente no encontrado en la cache" << endl;
	return -1;
}

void actualizarCache(User *cache[20], int pIndice) {
	cout << "Actualizando cache" << endl;
	int indiceAux = 0;
	string datos;
	ifstream indicesFile;
	indicesFile.open("indices.txt");
	bool banderaMasterPro = false;
	while(true){
		getline(indicesFile, datos);
		if (!datos.empty()) {
			string cedula, indice, nombre;
			bool bandera = false;
			bool bandera1 = false;
			for (int i = 0; i < datos.length(); i++) {
				if (datos[i] != *";") {
					if (!bandera)
						indice.operator+=(datos[i]);
					else if (bandera && !bandera1)
						cedula.operator+=(datos[i]);
					else
						nombre.operator+=(datos[i]);
				}
				else if (!bandera)
					bandera = true;
				else
					bandera1 = true;

			}
			if (banderaMasterPro) {
				cache[indiceAux] = new User(stoi(indice), cedula, nombre);
				indiceAux++;
			}
			else if (stoi(indice) >= pIndice) {
				cache[indiceAux] = new User(stoi(indice), cedula, nombre);
				indiceAux++;
			}
		}
		else {
			banderaMasterPro = true;
			indicesFile.clear();
			indicesFile.seekg(0, ios::beg);
		}
		if (indiceAux == 20)
			break;
	}
	indicesFile.close();
}

void buscarCliente(Binario &arbol,User *cache[20]) {
	string cedula;
	cout << "Cedula: ";
	cin >> cedula;
	int indice = arbol.buscar(cedula);
	if (indice != -1) {
		int buscarCache = buscarEnCache(indice, cache); // Buscar en cache
		if(buscarCache == -1){ // Si no esta
			actualizarCache(cache,indice); // Actualizar cache
			buscarEnCache(indice,cache); // Buscar de nuevo
		}
	}
}

int main() {
	User *cache[20];
	crearArchivoIndices();
	cout << endl;
	Binario arbol = crearArbol();
	arbol.PreordenI();
	cout << endl;
	cout << endl;
	iniciarCache(cache);
	cout << "Cache: ";
	imprimirCache(cache);
	cout << endl;
	buscarCliente(arbol, cache);
	cout << "Cache: ";
	imprimirCache(cache);

	cin.get();
	cin.get();
	return 0;
}