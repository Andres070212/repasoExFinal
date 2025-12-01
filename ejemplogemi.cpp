#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <iomanip>

using namespace std;

// --- ESTRUCTURA ---
struct Player {
    int id;
    string nombre;
    int nivel;
    string clase;
    int poder;

    bool operator<(const Player& other) const {
        return id < other.id;
    }
};

// --- 1. FUNCIONES DE UTILIDAD ---

// Imprime una sola línea con los datos de un jugador
void imprimirFicha(const Player& p) {
    cout << "ID: " << setw(3) << p.id 
         << " | " << setw(10) << p.nombre 
         << " | Lvl: " << setw(3) << p.nivel 
         << " | Clase: " << setw(10) << p.clase 
         << " | Poder: " << p.poder << endl;
}

// --- 2. FUNCIONES DE LÓGICA DE DATOS ---

// Se encarga de pedir datos al usuario y llenar el SET principal
void ingresarJugadores(set<Player>& dbJugadores) {
    Player temp;
    cout << "--- INGRESO DE DATOS (ID 0 para terminar) ---" << endl;
    while (true) {
        cout << "\nID: "; cin >> temp.id;
        if (temp.id == 0) break;
        cin.ignore(); // Limpiar buffer
        cout << "Nombre: "; getline(cin, temp.nombre);
        cout << "Nivel: "; cin >> temp.nivel; cin.ignore();
        cout << "Clase: "; getline(cin, temp.clase);
        cout << "Poder: "; cin >> temp.poder;
        
        dbJugadores.insert(temp);
    }
}

// Esta es la "Fase 2": Recibe el SET lleno y reparte datos a las otras estructuras
// Nota el uso de '&' (referencia) para poder modificar las variables originales
void sincronizarEstructuras(const set<Player>& origen, 
                            map<string, set<int>>& destClases, 
                            unordered_map<int, Player>& destHash, 
                            vector<int>& destNiveles) {
    // Limpiamos por seguridad
    destClases.clear();
    destHash.clear();
    destNiveles.clear();

    for (const auto& p : origen) {
        destClases[p.clase].insert(p.id); // Llenar Map
        destHash[p.id] = p;               // Llenar Hash
        destNiveles.push_back(p.nivel);   // Llenar Vector
    }
    // Ordenamos niveles una sola vez
    sort(destNiveles.begin(), destNiveles.end());
}

// --- 3. FUNCIONES DE REPORTE (MENÚ) ---

void mostrarTodos(const set<Player>& db) {
    cout << "\n--- LISTA MAESTRA ---" << endl;
    for (const auto& p : db) imprimirFicha(p);
}

void mostrarPorClase(const map<string, set<int>>& indice) {
    cout << "\n--- INDICE POR CLASES ---" << endl;
    for (const auto& par : indice) {
        cout << ">> " << par.first << ": "; // Nombre clase
        for (int id : par.second) cout << id << " "; // IDs
        cout << endl;
    }
}

void buscarRapido(const unordered_map<int, Player>& hash) {
    int id;
    cout << "\nIngrese ID a buscar: ";
    cin >> id;
    // .count() devuelve 1 si existe, 0 si no. Es más rápido de escribir que .find() != .end()
    if (hash.count(id)) {
        cout << "ENCONTRADO: ";
        imprimirFicha(hash.at(id));
    } else {
        cout << "Jugador no encontrado." << endl;
    }
}

void verificarNivel(const vector<int>& niveles) {
    int obj;
    cout << "\nNivel a buscar: ";
    cin >> obj;
    // Binary search requiere el vector ordenado (ya lo hicimos en sincronizar)
    if (binary_search(niveles.begin(), niveles.end(), obj)) {
        cout << "SI existe al menos un jugador nivel " << obj << endl;
    } else {
        cout << "NO existe ese nivel." << endl;
    }
}

void mostrarTop3(const set<Player>& db) {
    // Creamos vector temporal solo para este reporte
    vector<Player> ranking(db.begin(), db.end());
    
    // Lambda para ordenar por poder descendente
    sort(ranking.begin(), ranking.end(), [](const Player& a, const Player& b) {
        return a.poder > b.poder; 
    });

    cout << "\n--- TOP 3 PODER ---" << endl;
    for (int i = 0; i < 3 && i < ranking.size(); ++i) {
        cout << "#" << i+1 << ": " << ranking[i].nombre 
             << " (" << ranking[i].poder << ")" << endl;
    }
}

// --- MAIN (CONTROLADOR PRINCIPAL) ---
int main() {
    // 1. Declaración de Bases de Datos
    set<Player> dbJugadores;
    map<string, set<int>> idxClases;
    unordered_map<int, Player> idxRapido;
    vector<int> statsNiveles;

    // 2. Ejecución
    ingresarJugadores(dbJugadores);

    // 3. Procesamiento (Sincronización)
    // Pasamos todas las estructuras para que la funcion las llene
    sincronizarEstructuras(dbJugadores, idxClases, idxRapido, statsNiveles);

    // 4. Menú
    int op = -1;
    while (op != 0) {
        cout << "\n=== MENU MODULAR ===" << endl;
        cout << "1. Ver Todos | 2. Ver Clases | 3. Buscar ID | 4. Check Nivel | 5. Top 3 | 0. Salir" << endl;
        cout << "Opcion: "; cin >> op;

        switch (op) {
            case 1: mostrarTodos(dbJugadores); break;
            case 2: mostrarPorClase(idxClases); break;
            case 3: buscarRapido(idxRapido); break;
            case 4: verificarNivel(statsNiveles); break;
            case 5: mostrarTop3(dbJugadores); break;
            case 0: cout << "Adios!" << endl; break;
            default: cout << "Invalido" << endl;
        }
    }
    return 0;
}