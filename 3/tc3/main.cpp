#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "archivos/Binario.h"
#include "archivos/listaSimple.cpp"

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
	std::string cedulaBuffer;
	std::ifstream clientesFile; 
	std::ofstream indicesFile; 
	indicesFile.open("indices.txt");
	clientesFile.open("Clientes.txt");
	while (!clientesFile.eof()) {
		getline(clientesFile, datosBuffer);
		cedulaBuffer = extraerCedula(datosBuffer);
		if (cedulas.buscar(stoi(cedulaBuffer))) {
			cout << "CEDULA REPETIDA: " << cedulaBuffer << endl;
		}
		else {
			cedulas.InsertarFinal(stoi(cedulaBuffer));
			indicesFile << indice << ";" << cedulaBuffer << endl;
			indice++;
		}
	}
	cedulas.~lista();
	clientesFile.close();
	indicesFile.close();
}

void insertarUsuario(Binario &arbol,std::string datos) {
	std::string cedula,indice;
	bool bandera = false;
	for (int i = 0; i < datos.length(); i++) {
		if (datos[i] != *";") {
			if (!bandera)
				indice.operator+=(datos[i]);
			else
				cedula.operator+=(datos[i]);
		}
		else
			bandera = true;
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

void buscarCliente(Binario &arbol,string cedula) {
	int indice = arbol.buscar(cedula);
	if (indice != -1) {
		// buscar en cache
		// si no esta
			// buscar en txt de indices y actualizar cache
	}
}

int main() {
	NodoBinario *cache[20];
	crearArchivoIndices();
	cout << endl;
	Binario arbol = crearArbol();
	arbol.PreordenI();


	std::cin.get();
	return 0;

}