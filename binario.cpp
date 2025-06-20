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

bool existe(int code) {
    fstream f("inventario.dat", ios::in | ios::binary);
    if (!f) return false;
    Producto p;
    f.seekg(pos(code));
    return f.read((char*)&p, sizeof(p)) && p.activo;
}

void agregar() {
    Producto p; cout << "Codigo: "; cin >> p.codigo;
    if (p.codigo <= 0 || existe(p.codigo)) {
        cout << "Invalido o existente."; return;
    }
    cin.ignore();
    cout << "Nombre: "; cin.getline(p.nombre, 31);
    cout << "Precio: "; cin >> p.precio;
    cout << "Stock: "; cin >> p.stock; cin.ignore();
    cout << "Categoria: "; cin.getline(p.categoria, 40);
    p.activo = true;
    fstream f("inventario.dat", ios::in | ios::out | ios::binary);
    f.seekp(pos(p.codigo));
    f.write((char*)&p, sizeof(p));
}

void mostrar(bool solo_activos = true) {
    ifstream f("inventario.dat", ios::binary);
    for (Producto p; f.read((char*)&p, sizeof(p));)
        if (!solo_activos || p.activo)
            cout << "Codigo: " << p.codigo << ", Nombre: " << p.nombre << ", Precio: " << p.precio << ", Stock: " << p.stock << ", Categoria: " << p.categoria;
}
int main() {
    crearArchivo();
    int op;
    do {
        cout << "\n1.Agregar \n2.Mostrar \n3.Buscar por categoria \n4.Buscar por codigo \n5.Modificar \n6.Eliminar \n0.Salir \nOpcion: ";
        cin >> op;
        switch(op) {
            case 1: agregar(); break;
            case 2: mostrar(); break;
        }
    } while (op != 0);
}


