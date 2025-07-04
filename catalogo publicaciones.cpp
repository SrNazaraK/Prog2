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
        cout << "[Libro] \"" << titulo << "\" - Año: " << ano << ", Páginas: " << paginas << '\n';
    }
    string tipo() const override { return "Libro"; }
};

class Revista : public Publicacion {
    int edicion;
public:
    Revista(string t, int a, int e) : Publicacion(move(t), a), edicion(e) {}
    void mostrar() const override {
        cout << "[Revista] \"" << titulo << "\" - Año: " << ano << ", Edición: " << edicion << '\n';
    }
    string tipo() const override { return "Revista"; }
};

class Periodico : public Publicacion {
    string fecha;
public:
    Periodico(string t, int a, string f) : Publicacion(move(t), a), fecha(move(f)) {}
    void mostrar() const override {
        cout << "[Periódico] \"" << titulo << "\" - Año: " << ano << ", Fecha: " << fecha << '\n';
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
    cout << "\nSeleccione tipo de publicación:\n1. Libro\n2. Revista\n3. Periódico\n> ";
    int tipo;
    cin >> tipo;
    limpiarBuffer();

    string titulo = leerTexto("Título: ");
    int ano = leerEntero("Año de publicación (>=1500): ", 1500);
    if (!validarAno(ano)) {
        cout << "Año fuera de rango.\n";
        return;
    }

    Publicacion* p = nullptr;
    if (tipo == 1) {
        int paginas = leerEntero("Número de páginas: ");
        p = new Libro(titulo, ano, paginas);
    } else if (tipo == 2) {
        int edicion = leerEntero("Número de edición: ");
        p = new Revista(titulo, ano, edicion);
    } else if (tipo == 3) {
        string fecha = leerTexto("Fecha de publicación: ");
        p = new Periodico(titulo, ano, fecha);
    } else {
        cout << "Opción inválida.\n";
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
    string clave = leerTexto("Buscar título: ");
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

    int idx = leerEntero("Seleccione número a eliminar: ") - 1;
    if (idx < 0 || idx >= nroPublicaciones) {
        cout << "Índice inválido.\n";
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

    cout << "Publicación eliminada.\n";
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

    cout << "\nEstadísticas:\n";
    cout << "Total: " << nroPublicaciones << '\n';
    cout << "Libros: " << libros << ", Revistas: " << revistas << ", Periódicos: " << periodicos << '\n';
    if (nroPublicaciones > 0)
        cout << "Año más antiguo: " << minAno << ", Año más reciente: " << maxAno << '\n';
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
        cout << "\n--- MENÚ PRINCIPAL ---\n"
             << "1. Agregar publicación\n"
             << "2. Mostrar publicaciones\n"
             << "3. Buscar por título\n"
             << "4. Eliminar publicación\n"
             << "5. Estadísticas\n"
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
            default: cout << "Opción inválida.\n"; break;
        }
    } while (opcion != 6);

    return 0;
}

