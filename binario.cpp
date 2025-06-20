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
            cout << "Codigo: " << p.codigo << ", Nombre: " << p.nombre << ", Precio: " << p.precio << ", Stock: " << p.stock << ", Categoria: " << p.categoria << "\n";
}

void mostrarPorCategoria() {
    char cat[40]; cout << "Categoria: "; cin.ignore(); cin.getline(cat, 40);
    fstream f("inventario.dat", ios::in | ios::binary);
    Producto p;
    while (f.read((char*)&p, sizeof(p)))
        if (p.activo && strcmp(p.categoria, cat) == 0)
            cout << p.codigo << ": " << p.nombre << "\n";
}

void buscar() {
    int c; cout << "Codigo: "; cin >> c;
    fstream f("inventario.dat", ios::in | ios::binary);
    Producto p;
    f.seekg(pos(c));
    if (f.read((char*)&p, sizeof(p)) && p.activo)
        cout << p.nombre << ", $" << p.precio << ", stock: " << p.stock
             << ", categoria: " << p.categoria << "\n";
    else cout << "No encontrado.\n";
}

void modificar() {
    int c; cout << "Codigo: "; cin >> c;
    fstream f("inventario.dat", ios::in | ios::out | ios::binary);
    Producto p;
    f.seekg(pos(c));
    if (f.read((char*)&p, sizeof(p)) && p.activo) {
        cout << "Nuevo precio: "; cin >> p.precio;
        cout << "Nuevo stock: "; cin >> p.stock; cin.ignore();
        cout << "Nueva categoria: "; cin.getline(p.categoria, 40);
        f.seekp(pos(c)); f.write((char*)&p, sizeof(p));
    } else cout << "No encontrado.\n";
}

void eliminar() {
    int c; cout << "Codigo: "; cin >> c;
    fstream f("inventario.dat", ios::in | ios::out | ios::binary);
    Producto p;
    f.seekg(pos(c));
    if (f.read((char*)&p, sizeof(p)) && p.activo) {
        p.activo = false;
        f.seekp(pos(c)); f.write((char*)&p, sizeof(p));
    } else cout << "No encontrado.\n";
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
            case 3: mostrarPorCategoria(); break;
            case 4: buscar(); break;
            case 5: modificar(); break;
            case 6: eliminar(); break;
        }
    } while (op != 0);
}


