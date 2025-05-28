#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>
#include <cctype>

#include <windows.h> //para la funcione getconsole y setconsole (interactuar con windows)

//La funcion para el color anterior no funcionaba y no compile antes del commit... 
//Deje el windows.h porque seguramente sea necesario para la funcion del color

using namespace std;

void minusculas(char* cadena){
	for (char* p = cadena; *p; p++){
		*p = tolower(*p);
	}
}

int main(){	

	setlocale(LC_ALL, "");

    ifstream archivo("archivo.txt");

    if (!archivo.is_open()) {
			cout << "No se pudo abrir el archivo para su lectura." << endl;
        }
        archivo.close();
    
    string busqueda;
    string linea;
	char opcion;
    
	cout << "Este es un programa que te permite leer un archivo de texto linea por linea." << endl;
    
    do {
    	do {
    		cout << "Ingresa la palabra o caracter que deseas buscar: "; 
    		getline(cin, busqueda);
    	
    		if (busqueda.empty()){
    			cout << "No puede estar vacio. Intentalo de nuevo" << endl;
			}
		} while (busqueda.empty()); 
		
		cout << "¿Quieres buscar otra letra o palabra? S/N: " << endl;
		cin >> opcion;
		cin.ignore();

	} while (opcion == 'S');
	
    return 0;
}
