#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm> // Para sort, binary_search
#include <iomanip>   // Para formato de salida

using namespace std;

// Definición de la estructura Jugador
struct Player {
    int id;
    string nombre;
    int nivel;
    string clase;
    int poder;

    // Sobrecarga del operador < para que el set<Player> sepa cómo ordenar (Requerimiento 1)
    // El set ordenará automáticamente por ID de menor a mayor.
    bool operator<(const Player& other) const {
        return id < other.id;
    }
};

// Función auxiliar para imprimir un jugador
void imprimirJugador(const Player& p) {
    cout << "ID: " << setw(3) << p.id 
         << " | " << setw(10) << p.nombre 
         << " | Lvl: " << setw(3) << p.nivel 
         << " | Clase: " << setw(10) << p.clase 
         << " | Poder: " << p.poder << endl;
}

int main() {
    // Datos iniciales simulados
    vector<Player> datosIniciales = {
        {101, "Aragorn", 50, "Guerrero", 8500},
        {105, "Gandalf", 99, "Mago", 9800},
        {102, "Legolas", 45, "Arquero", 7200},
        {104, "Gimli", 48, "Guerrero", 7100},
        {103, "Frodo", 20, "Ladron", 1500},
        {106, "Saruman", 95, "Mago", 9600}
    };

    // --- REQUERIMIENTO 1: Guardar en set<Player> ordenado por ID ---
    // Al insertar, el set usará el operador < que definimos en la estructura
    set<Player> jugadoresSet;
    for (const auto& p : datosIniciales) {
        jugadoresSet.insert(p);
    }

    // --- REQUERIMIENTO 2: map<string, set<int>> para clasificar por Clase ---
    // Clave: Nombre de la clase (string) -> Valor: Set de IDs (set<int>)
    map<string, set<int>> indicePorClase;

    // --- REQUERIMIENTO 3: unordered_map<int, Player> para acceso rápido ---
    // Clave: ID (int) -> Valor: Objeto Player completo
    unordered_map<int, Player> tablaHashJugadores;

    // Llenamos las estructuras del Req 2 y 3 recorriendo el set principal
    for (const auto& p : jugadoresSet) {
        indicePorClase[p.clase].insert(p.id);
        tablaHashJugadores[p.id] = p;
    }

    cout << "--- 1. Jugadores en el SET (Ordenados por ID) ---" << endl;
    for (const auto& p : jugadoresSet) {
        imprimirJugador(p);
    }
    cout << endl;

    cout << "--- 2. Clasificacion por Clase (MAP) ---" << endl;
    for (const auto& par : indicePorClase) {
        cout << "Clase [" << par.first << "]: ";
        for (int id : par.second) {
            cout << id << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "--- 3. Busqueda Rapida por ID (UNORDERED_MAP) ---" << endl;
    int idBusqueda = 105; // Buscamos a Gandalf
    if (tablaHashJugadores.find(idBusqueda) != tablaHashJugadores.end()) {
        cout << "Jugador encontrado rapido: " << tablaHashJugadores[idBusqueda].nombre << endl;
    } else {
        cout << "Jugador no encontrado." << endl;
    }
    cout << endl;

    // --- REQUERIMIENTO 4: Vector de niveles y sort ---
    vector<int> niveles;
    for (const auto& p : jugadoresSet) {
        niveles.push_back(p.nivel);
    }
    sort(niveles.begin(), niveles.end()); // Ordenamos para poder usar binary_search

    cout << "--- 4. Niveles ordenados (VECTOR + SORT) ---" << endl;
    for (int n : niveles) cout << n << " ";
    cout << endl << endl;

    // --- REQUERIMIENTO 5: binary_search ---
    cout << "--- 5. Busqueda Binaria de Nivel ---" << endl;
    int nivelBuscado = 45; // Nivel de Legolas
    bool existe = binary_search(niveles.begin(), niveles.end(), nivelBuscado);
    cout << "El nivel " << nivelBuscado << (existe ? " SI existe." : " NO existe.") << endl;
    cout << endl;

    // --- REQUERIMIENTO 6: Filtrar por Poder > X ---
    cout << "--- 6. Jugadores con Poder > 8000 ---" << endl;
    int cortePoder = 8000;
    for (const auto& p : jugadoresSet) {
        if (p.poder > cortePoder) {
            cout << "- " << p.nombre << " (" << p.poder << ")" << endl;
        }
    }
    cout << endl;

    // --- REQUERIMIENTO 7: Top 3 Jugadores mas fuertes ---
    // Para ordenar por poder, necesitamos pasar los datos a un vector, 
    // ya que el set está fijo ordenado por ID.
    vector<Player> ranking(jugadoresSet.begin(), jugadoresSet.end());

    // Usamos una función lambda para definir el criterio de ordenamiento (descendente por poder)
    sort(ranking.begin(), ranking.end(), [](const Player& a, const Player& b) {
        return a.poder > b.poder; // Mayor a menor
    });

    cout << "--- 7. TOP 3 Jugadores mas fuertes ---" << endl;
    for (int i = 0; i < 3 && i < ranking.size(); ++i) {
        cout << "#" << (i + 1) << ": " << ranking[i].nombre << " - Poder: " << ranking[i].poder << endl;
    }

    return 0;
}