#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>

using namespace std;

int main(){	
	system("chcp 65001 > nul");
	setlocale(LC_ALL, "");

    ifstream archivo("archivo.txt");

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)){ 
        }
        archivo.close();
    }
    else {
        cout << "No se pudo abrir el archivo para lectura" << endl;
    } 
    
    string busqueda;
    
    do {
    	cout << "Este es un programa que te permite leer un archivo de texto linea por linea." << endl;
    	cout << "Ingresa la palabra o caracter que deseas buscar: "; 
    	getline(cin, busqueda);
    	
    	if (palabra.empty()){
    		cout << "No puede estar vacio. Intentalo de nuevo" << endl;
		}
	} while (busqueda.empty());

    return 0;
}
