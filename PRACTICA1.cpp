#include <iostream>
#include <fstream>
#include <cstring>
#include <locale.h>
#include <cctype>

using namespace std;

const string verde = "\033[32m";
const string reset = "\033[0m";

void minusculas(char* cadena){
	for (char* p = cadena; *p; p++){
		*p = tolower(*p);
	}
}

int main(){	

	setlocale(LC_ALL, "");
    
    string busqueda;
    string linea;
	char opcion;
	int coincidencias;
    
	cout << "Este es un programa que te permite leer un archivo de texto linea por linea." << endl;
    
    do {
    	
		ifstream archivo("archivo.txt");
    	if (!archivo.is_open()){
			cout << "No se pudo abrir el archivo para su lectura." << endl;
        }
        
    	do {
    		cout << "Ingresa la palabra o caracter que deseas buscar: "; 
    		getline(cin, busqueda);
    	
    		if (busqueda.empty()){
    			cout << "No puede estar vacio. Intentalo de nuevo" << endl;
			}
		} while (busqueda.empty()); 
        
        archivo.close();
        
        cout << "Total de coincidencias para " << busqueda << ": " << coincidencias << endl;

		
		cout << "¿Quieres buscar otra letra o palabra? S/N: " << endl;
		cin >> opcion;
		cin.ignore();

	} while (opcion == 'S');
	
    return 0;
}
