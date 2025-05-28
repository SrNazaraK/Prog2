#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>
#include <cctype>

//La funcion para que windows permita poner color al texto la saque de Google

#ifdef _WIN32 //verifica si se esta compilando en windows
#include <windows.h> //para la funcione getconsole y setconsole (interactuar con windows)

void coloresConsola() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD modo = 0;
    GetConsoleMode(hOut, &modo);
    modo |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, modo);
}


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
    
	cout << "Este es un programa que te permite leer un archivo de texto linea por linea." << endl;
    
    do {
    	do {
    		cout << "Ingresa la palabra o caracter que deseas buscar: "; 
    		getline(cin, busqueda);
    	
    		if (busqueda.empty()){
    			cout << "No puede estar vacio. Intentalo de nuevo" << endl;
			}
		} while (busqueda.empty());
		
		string linea;
		int coincidencias = 0;

	} while (opcion == 'S');
	
    return 0;
}
