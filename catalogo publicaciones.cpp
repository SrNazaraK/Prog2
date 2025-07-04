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

void limpiarBuffer() {
    while (cin.get() != '\n');
}

bool validarAno(int ano) {
    return ano >= 1500 && ano <= 2025;
}

string leerTexto(const string& prompt) {
    string texto;
    do {
        cout << prompt;
        getline(cin, texto);
    } while (texto.empty());
    return texto;
}

int leerEntero(const string& prompt, int min = 1) {
    int valor;
    do {
        cout << prompt;
        cin >> valor;
        limpiarBuffer();
    } while (valor < min);
    return valor;
}

void agregarPublicacion(Publicacion**& catalogo, int& nroPublicaciones) {
    cout << "\nSeleccione tipo de publicaci�n:\n1. Libro\n2. Revista\n3. Peri�dico\n> ";
    int tipo;
    cin >> tipo;
    limpiarBuffer();

    string titulo = leerTexto("T�tulo: ");
    int ano = leerEntero("A�o de publicaci�n (>=1500): ", 1500);
    if (!validarAno(ano)) {
        cout << "A�o fuera de rango.\n";
        return;
    }

    Publicacion* p = nullptr;
    if (tipo == 1) {
        int paginas = leerEntero("N�mero de p�ginas: ");
        p = new Libro(titulo, ano, paginas);
    } else if (tipo == 2) {
        int edicion = leerEntero("N�mero de edici�n: ");
        p = new Revista(titulo, ano, edicion);
    } else if (tipo == 3) {
        string fecha = leerTexto("Fecha de publicaci�n: ");
        p = new Periodico(titulo, ano, fecha);
    } else {
        cout << "Opci�n inv�lida.\n";
        return;
    }

    Publicacion** nuevoCatalogo = new Publicacion*[nroPublicaciones + 1];
    for (int i = 0; i < nroPublicaciones; ++i)
        nuevoCatalogo[i] = catalogo[i];
    nuevoCatalogo[nroPublicaciones++] = p;

    delete[] catalogo;
    catalogo = nuevoCatalogo;
}

void mostrarCatalogo(Publicacion** catalogo, int nroPublicaciones) {
    if (nroPublicaciones == 0) {
        cout << "No hay publicaciones registradas.\n";
        return;
    }
    for (int i = 0; i < nroPublicaciones; ++i) {
        cout << i + 1 << ". ";
        catalogo[i]->mostrar();
    }
}

void minusculas(char* cadena){
    for (char* p = cadena; *p; p++){
        *p = tolower(*p);
    }
}

void buscarTitulo(Publicacion** catalogo, int nroPublicaciones) {
    string clave = leerTexto("Buscar t�tulo: ");
    minusculas(&clave[0]);

    bool encontrado = false;
    for (int i = 0; i < nroPublicaciones; ++i) {
        string t = catalogo[i]->getTitulo();
        minusculas(&t[0]);
        if (t.find(clave) != string::npos) {
            catalogo[i]->mostrar();
            encontrado = true;
        }
    }
    if (!encontrado)
        cout << "No se encontraron coincidencias.\n";
}

void eliminarPublicacion(Publicacion**& catalogo, int& nroPublicaciones) {
    mostrarCatalogo(catalogo, nroPublicaciones);
    if (nroPublicaciones == 0) return;

    int idx = leerEntero("Seleccione n�mero a eliminar: ") - 1;
    if (idx < 0 || idx >= nroPublicaciones) {
        cout << "�ndice inv�lido.\n";
        return;
    }

    delete catalogo[idx];
    for (int i = idx; i < nroPublicaciones - 1; ++i)
        catalogo[i] = catalogo[i + 1];

    Publicacion** nuevoCatalogo = new Publicacion*[nroPublicaciones - 1];
    for (int i = 0; i < nroPublicaciones - 1; ++i)
        nuevoCatalogo[i] = catalogo[i];

    delete[] catalogo;
    catalogo = nuevoCatalogo;
    --nroPublicaciones;

    cout << "Publicaci�n eliminada.\n";
}

void mostrarEstadisticas(Publicacion** catalogo, int nroPublicaciones) {
    int libros = 0, revistas = 0, periodicos = 0;
    int minAno = 9999, maxAno = 0;

    for (int i = 0; i < nroPublicaciones; ++i) {
        string tipo = catalogo[i]->tipo();
        if (tipo == "Libro") ++libros;
        else if (tipo == "Revista") ++revistas;
        else if (tipo == "Periodico") ++periodicos;

        int a = catalogo[i]->getAno();
        if (a < minAno) minAno = a;
        if (a > maxAno) maxAno = a;
    }

    cout << "\nEstad�sticas:\n";
    cout << "Total: " << nroPublicaciones << '\n';
    cout << "Libros: " << libros << ", Revistas: " << revistas << ", Peri�dicos: " << periodicos << '\n';
    if (nroPublicaciones > 0)
        cout << "A�o m�s antiguo: " << minAno << ", A�o m�s reciente: " << maxAno << '\n';
}

void liberarMemoria(Publicacion**& catalogo, int& nroPublicaciones) {
    for (int i = 0; i < nroPublicaciones; ++i)
        delete catalogo[i];
    delete[] catalogo;
    catalogo = nullptr;
    nroPublicaciones = 0;
}

int main() {
    Publicacion** catalogo = nullptr;
    int nroPublicaciones = 0, opcion;

    do {
        cout << "\n--- MEN� PRINCIPAL ---\n"
             << "1. Agregar publicaci�n\n"
             << "2. Mostrar publicaciones\n"
             << "3. Buscar por t�tulo\n"
             << "4. Eliminar publicaci�n\n"
             << "5. Estad�sticas\n"
             << "6. Salir\n> ";
        cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
            case 1: agregarPublicacion(catalogo, nroPublicaciones); break;
            case 2: mostrarCatalogo(catalogo, nroPublicaciones); break;
            case 3: buscarTitulo(catalogo, nroPublicaciones); break;
            case 4: eliminarPublicacion(catalogo, nroPublicaciones); break;
            case 5: mostrarEstadisticas(catalogo, nroPublicaciones); break;
            case 6: liberarMemoria(catalogo, nroPublicaciones); cout << "Saliendo...\n"; break;
            default: cout << "Opci�n inv�lida.\n"; break;
        }
    } while (opcion != 6);

    return 0;
}

