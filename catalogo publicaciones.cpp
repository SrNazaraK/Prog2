#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

class Publicacion {
protected:
    string titulo;
    int ano;
public:
    Publicacion(string t, int a) : titulo(move(t)), ano(a) {}
    virtual void mostrar() const = 0;
    virtual string tipo() const = 0;
    virtual ~Publicacion() {}
    string getTitulo() const { return titulo; }
    int getAno() const { return ano; }
};

class Libro : public Publicacion {
    int paginas;
public:
    Libro(string t, int a, int p) : Publicacion(move(t), a), paginas(p) {}
    void mostrar() const override {
        cout << "[Libro] \"" << titulo << "\" - A�o: " << ano << ", P�ginas: " << paginas << '\n';
    }
    string tipo() const override { return "Libro"; }
};

class Revista : public Publicacion {
    int edicion;
public:
    Revista(string t, int a, int e) : Publicacion(move(t), a), edicion(e) {}
    void mostrar() const override {
        cout << "[Revista] \"" << titulo << "\" - A�o: " << ano << ", Edici�n: " << edicion << '\n';
    }
    string tipo() const override { return "Revista"; }
};

class Periodico : public Publicacion {
    string fecha;
public:
    Periodico(string t, int a, string f) : Publicacion(move(t), a), fecha(move(f)) {}
    void mostrar() const override {
        cout << "[Peri�dico] \"" << titulo << "\" - A�o: " << ano << ", Fecha: " << fecha << '\n';
    }
    string tipo() const override { return "Periodico"; }
};

