#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm> // Para sort, binary_search
#include <iomanip>   // Para formato de salida

using namespace std;

struct Player {
    int id;
    string nombre;
    int nivel;
    string clase;
    int poder;

    // Sobrecarga necesaria para el set (ordena por ID)
    bool operator<(const Player& other) const {
        return id < other.id;
    }
};

void imprimirJugador(const Player& p) {
    cout << "ID: " << setw(3) << p.id 
         << " | " << setw(15) << p.nombre 
         << " | Lvl: " << setw(3) << p.nivel 
         << " | Clase: " << setw(10) << p.clase 
         << " | Poder: " << p.poder << endl;
}

int main() {
    // Estructuras de datos principales
    set<Player> jugadoresSet;
    map<string, set<int>> indicePorClase;
    unordered_map<int, Player> tablaHashJugadores;
    vector<int> niveles; // Para estadísticas de niveles

    int opcion;
    Player temp;

    // --- FASE 1: INGRESO DE DATOS ---
    cout << "=== SISTEMA DE REGISTRO DE JUGADORES ===" << endl;
    cout << "Ingresa los datos de los jugadores. Escribe ID 0 para terminar." << endl;

    while (true) {
        cout << "\nIngrese ID (0 para salir): ";
        cin >> temp.id;
        if (temp.id == 0) break;

        // Limpieza de buffer necesaria antes de leer strings con getline o cin
        cin.ignore(); 

        cout << "Nombre: ";
        getline(cin, temp.nombre); // getline permite nombres con espacios

        cout << "Nivel: ";
        cin >> temp.nivel;
        cin.ignore();

        cout << "Clase (Guerrero/Mago/Arquero): ";
        getline(cin, temp.clase);

        cout << "Poder: ";
        cin >> temp.poder;

        // Insertamos en el set principal
        jugadoresSet.insert(temp);
    }

    // --- FASE 2: PROCESAMIENTO DE DATOS ---
    // Llenamos las estructuras auxiliares basándonos en el set que acabamos de crear
    for (const auto& p : jugadoresSet) {
        indicePorClase[p.clase].insert(p.id);
        tablaHashJugadores[p.id]= p;
        niveles.push_back(p.nivel);
    }
    // Ordenamos niveles para la búsqueda binaria
    sort(niveles.begin(), niveles.end());

    // --- FASE 3: MENÚ INTERACTIVO ---
    do {
        cout << "\n\n=== MENU DE GESTION ===" << endl;
        cout << "1. Mostrar todos los jugadores (Orden ID)" << endl;
        cout << "2. Mostrar IDs por Clase" << endl;
        cout << "3. Buscar Jugador por ID (Rapido)" << endl;
        cout << "4. Verificar si existe un Nivel especifico" << endl;
        cout << "5. Filtrar por Poder Minimo" << endl;
        cout << "6. Ver TOP 3 Jugadores mas fuertes" << endl;
        cout << "0. Salir" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cout << "\n--- LISTA COMPLETA ---" << endl;
                if (jugadoresSet.empty()) cout << "No hay jugadores registrados." << endl;
                for (const auto& p : jugadoresSet) imprimirJugador(p);
                break;
            }
            case 2: {
                cout << "\n--- CLASIFICACION POR CLASE ---" << endl;
                for (const auto& par : indicePorClase) {
                    cout << "Clase [" << par.first << "]: ";
                    for (int id : par.second) cout << id << " ";
                    cout << endl;
                }
                break;
            }
            case 3: {
                int idBusqueda;
                cout << "\nIngrese ID a buscar: ";
                cin >> idBusqueda;
                if (tablaHashJugadores.find(idBusqueda) != tablaHashJugadores.end()) {
                    cout << ">> ENCONTRADO: ";
                    imprimirJugador(tablaHashJugadores[idBusqueda]);
                } else {
                    cout << ">> ERROR: Jugador no encontrado." << endl;
                }
                break;
            }
            case 4: {
                int lvlBuscado;
                cout << "\nIngrese Nivel a verificar: ";
                cin >> lvlBuscado;
                if (binary_search(niveles.begin(), niveles.end(), lvlBuscado)) {
                    cout << ">> SI existe al menos un jugador con nivel " << lvlBuscado << endl;
                } else {
                    cout << ">> NO existe nadie con ese nivel." << endl;
                }
                break;
            }
            case 5: {
                int poderMin;
                cout << "\nIngrese poder minimo: ";
                cin >> poderMin;
                cout << "Jugadores con poder > " << poderMin << ":" << endl;
                for (const auto& p : jugadoresSet) {
                    if (p.poder > poderMin) {
                        cout << "- " << p.nombre << " (" << p.poder << ")" << endl;
                    }
                }
                break;
            }
            case 6: {
                // Copiamos a vector para ordenar por poder
                vector<Player> ranking(jugadoresSet.begin(), jugadoresSet.end());
                sort(ranking.begin(), ranking.end(), [](const Player& a, const Player& b) {
                    return a.poder > b.poder; // Descendente
                });

                cout << "\n--- TOP 3 JUGADORES ---" << endl;
                for (int i = 0; i < 3 && i < ranking.size(); ++i) {
                    cout << "#" << (i + 1) << ": " << ranking[i].nombre 
                         << " (Poder: " << ranking[i].poder << ")" << endl;
                }
                break;
            }
            case 0: cout << "Saliendo..." << endl; break;
            default: cout << "Opcion no valida." << endl;
        }

    } while (opcion != 0);

    return 0;
}