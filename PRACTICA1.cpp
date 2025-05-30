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
		
		char* busquedaC = new char[busqueda.size() + 1];
        strcpy(busquedaC, busqueda.c_str());
        minusculas(busquedaC);
        
        int coincidencias = 0;
        
        cout << "Resultados:" << endl;
        
         while (getline(archivo, linea)){
            char* lineaC = new char[linea.size() + 1];
            strcpy(lineaC, linea.c_str());

            char* lineaMin = new char[linea.size() + 1];
            strcpy(lineaMin, linea.c_str());
            minusculas(lineaMin);

            string resultado;
            size_t prev = 0;
            size_t pos;
            
             while ((pos = string(lineaMin).find(busquedaC, prev)) != string::npos) {
                resultado += linea.substr(prev, pos - prev);
                resultado += verde + linea.substr(pos, strlen(busquedaC)) + reset;

                prev = pos + strlen(busquedaC);
                coincidencias++;
            }
            
             resultado += linea.substr(prev);

            cout << resultado << endl;
        }
        
        archivo.close();
        
        cout << "Total de coincidencias para " << busqueda << ": " << coincidencias << endl;

		
		cout << "¿Quieres buscar otra letra o palabra? S/N: " << endl;
		cin >> opcion;
		cin.ignore();

	} while (opcion == 'S');
	
    return 0;
}
