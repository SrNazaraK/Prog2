#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Producto {
    int codigo; char nombre[31], categoria[40];
    float precio; int stock; bool activo;
};
