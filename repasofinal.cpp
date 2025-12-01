#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm> // Para sort
#include <limits>    // Para limpiar buffer

using namespace std;

// --------------------------------------------------------------------------
// COMMIT: Creación del struct con los campos correspondientes.
// --------------------------------------------------------------------------
struct Libro {
    string titulo;
    string autor;
    int vecesPrestado;
    int copiasDisponibles;
    float indicePopularidad;
};

// --------------------------------------------------------------------------
// COMMIT: Creación de las estructuras dinámicas no lineales (Definición de tipos)
// --------------------------------------------------------------------------
// 1. map<string, Libro>: Clave título, Valor estructura
// 2. map<string, map...>: Clave nombre biblioteca, Valor mapa de libros
map<string, map<string, Libro>> bibliotecas;

// --------------------------------------------------------------------------
// COMMIT: Declaración y definición de función calcularIndiceDePopularidad
// --------------------------------------------------------------------------
void calcularIndiceDePopularidad(Libro& libro) {
    // Formula: popularidad = vecesPrestado / (copiasDisponibles + 1)
    // Se hace cast a float para evitar división entera
    libro.indicePopularidad = (float)libro.vecesPrestado / (libro.copiasDisponibles + 1);
}

// --------------------------------------------------------------------------
// COMMIT: Declaración y definición de función solicitarInformacionLibro
// --------------------------------------------------------------------------
void solicitarInformacionLibro(Libro& libro) {
    // Limpieza de buffer previa por si acaso
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    cout << "Ingrese el titulo del libro: ";
    getline(cin, libro.titulo);

    cout << "Ingrese el autor: ";
    getline(cin, libro.autor);

    cout << "Ingrese veces prestado: ";
    cin >> libro.vecesPrestado;

    cout << "Ingrese copias disponibles: ";
    cin >> libro.copiasDisponibles;

    // Calculamos la popularidad inmediatamente después de recibir los datos
    calcularIndiceDePopularidad(libro);
}

// --------------------------------------------------------------------------
// COMMIT: Declaración y definición de función buscar libros por palabra clave
// --------------------------------------------------------------------------
void buscarLibros(string palabraClave) {
    bool encontrado = false;
    cout << "\n--- Resultados de Busqueda para: '" << palabraClave << "' ---\n";
    
    // Recorremos todas las bibliotecas
    for (auto& parBiblioteca : bibliotecas) {
        string nombreBiblio = parBiblioteca.first;
        auto& mapaLibros = parBiblioteca.second;

        // Recorremos los libros de la biblioteca actual
        for (auto& parLibro : mapaLibros) {
            Libro& l = parLibro.second;
            
            // Buscamos coincidencia en Titulo o Autor (búsqueda simple)
            // .find retorna string::npos si no encuentra la subcadena
            if (l.titulo.find(palabraClave) != string::npos || 
                l.autor.find(palabraClave) != string::npos) {
                
                cout << "Biblioteca: " << nombreBiblio << " | Libro: " << l.titulo 
                     << " (" << l.autor << ") - Pop: " << l.indicePopularidad << endl;
                encontrado = true;
            }
        }
    }
    if (!encontrado) cout << "No se encontraron libros con esa palabra clave.\n";
}

// Función auxiliar para el sort (ordenar descendentemente por popularidad)
bool compararPopularidad(const Libro& a, const Libro& b) {
    return a.indicePopularidad > b.indicePopularidad;
}

// --------------------------------------------------------------------------
// COMMIT: Declaración y definición de función obtener top 5 libros más populares.
// --------------------------------------------------------------------------
void obtenerTop5(string nombreBiblioteca) {
    // Verificar si la biblioteca existe
    if (bibliotecas.find(nombreBiblioteca) == bibliotecas.end()) {
        cout << "La biblioteca no existe.\n";
        return;
    }

    // Paso 1: Pasar los libros del mapa a un vector para poder ordenarlos
    vector<Libro> listaLibros;
    for (auto& par : bibliotecas[nombreBiblioteca]) {
        listaLibros.push_back(par.second);
    }

    // Paso 2: Ordenar el vector
    sort(listaLibros.begin(), listaLibros.end(), compararPopularidad);

    // Paso 3: Mostrar los primeros 5 (o menos si no hay 5)
    cout << "\n--- TOP 5 LIBROS EN " << nombreBiblioteca << " ---\n";
    int limite = min((int)listaLibros.size(), 5);
    
    for (int i = 0; i < limite; i++) {
        cout << (i + 1) << ". " << listaLibros[i].titulo 
             << " - Popularidad: " << listaLibros[i].indicePopularidad << endl;
    }
}

// --------------------------------------------------------------------------
// COMMIT: Declaración y definición de función copiar un libro de una biblioteca a otra
// --------------------------------------------------------------------------
void copiarLibro(string biblioOrigen, string biblioDestino, string tituloLibro) {
    // Verificar origen
    if (bibliotecas.find(biblioOrigen) == bibliotecas.end()) {
        cout << "Error: Biblioteca origen no existe.\n";
        return;
    }
    // Verificar libro en origen
    if (bibliotecas[biblioOrigen].find(tituloLibro) == bibliotecas[biblioOrigen].end()) {
        cout << "Error: El libro no existe en la biblioteca de origen.\n";
        return;
    }

    // Obtener el libro (hacemos una copia)
    Libro libroACopiar = bibliotecas[biblioOrigen][tituloLibro];

    // Insertar en destino (si la biblioteca destino no existe, el map la crea automáticamente al acceder con [])
    bibliotecas[biblioDestino][libroACopiar.titulo] = libroACopiar;
    
    cout << "Exito: Libro '" << tituloLibro << "' copiado a '" << biblioDestino << "'.\n";
}

// --------------------------------------------------------------------------
// COMMIT: El diseño del menú (Función Main)
// --------------------------------------------------------------------------
int main() {
    int opcion = 0;
    
    do {
        cout << "\n=== SISTEMA DE GESTION DE BIBLIOTECAS (UCA) ===\n";
        cout << "1. Agregar Libro a una Biblioteca\n"; // Solicitar datos
        cout << "2. Ver Top 5 Populares de una Biblioteca\n"; // Ordenar / Imprimir top
        cout << "3. Buscar libros (Global)\n"; // Buscar
        cout << "4. Copiar libro entre bibliotecas\n";
        cout << "5. Imprimir todos los libros (Debug)\n"; // Extra para visualizar
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string nombreBib;
                cout << "Nombre de la biblioteca: ";
                cin.ignore(); 
                getline(cin, nombreBib);
                
                Libro nuevoLibro;
                // La funcion solicita info y calcula popularidad internamente
                solicitarInformacionLibro(nuevoLibro); 
                
                // Guardamos en el mapa anidado. Clave 1: Biblioteca, Clave 2: Titulo
                bibliotecas[nombreBib][nuevoLibro.titulo] = nuevoLibro;
                cout << "Libro registrado correctamente.\n";
                break;
            }
            case 2: {
                string nombreBib;
                cout << "Ingrese nombre de la biblioteca a consultar: ";
                cin.ignore();
                getline(cin, nombreBib);
                obtenerTop5(nombreBib);
                break;
            }
            case 3: {
                string keyword;
                cout << "Ingrese palabra clave (Titulo o Autor): ";
                cin.ignore();
                getline(cin, keyword);
                buscarLibros(keyword);
                break;
            }
            case 4: {
                string origen, destino, titulo;
                cin.ignore();
                cout << "Biblioteca Origen: "; getline(cin, origen);
                cout << "Biblioteca Destino: "; getline(cin, destino);
                cout << "Titulo exacto del libro: "; getline(cin, titulo);
                copiarLibro(origen, destino, titulo);
                break;
            }
            case 5: {
                // Impresión general para verificar
                for(auto const& [nomBib, mapLibros] : bibliotecas) {
                    cout << "\nBiblioteca: " << nomBib << endl;
                    for(auto const& [titulo, libro] : mapLibros) {
                        cout << " - " << libro.titulo << " (Pop: " << libro.indicePopularidad << ")\n";
                    }
                }
                break;
            }
            case 6:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 6);

    return 0;
}
