#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Producto {
    int codigo; char nombre[31], categoria[40];
    float precio; int stock; bool activo;
};

long pos(int c) { return (c - 1) * sizeof(Producto); }

void crearArchivo() {
    fstream f("inventario.dat", ios::in | ios::binary);
    if (!f) f.open("inventario.dat", ios::out | ios::binary);
}

