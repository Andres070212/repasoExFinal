#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm> // Para sort, binary_search
#include <iomanip>   // Para formato de salida

using namespace std;

struct Producto
{
    int id;
    string nombre;
    string categoria;
    double precio;
    int stock;
    // Sobrecarga necesaria para el set (ordena por ID)
    bool operator<(const Producto& other) const {
        return id < other.id;
    }
};

void AgregarProducto(set<Producto>& productos);
void AgruparCategoria(map<string,set<int>>& indicePorCategoria,set<Producto>& productos);
void BuscarId(unordered_map<int, Producto>& tablaHashProductos, set<Producto>& productos);
void StockBajo(set<Producto>& productos);
void TopProductosCaros(set<Producto>& productos);

int main() {
  set<Producto> productos_main;
  map<string, set<int>> indicePorCategoria;
 
    unordered_map<int, Producto> tablaHashProductos_main;
    AgregarProducto(productos_main);
    AgruparCategoria(indicePorCategoria,productos_main);
    BuscarId(tablaHashProductos_main,productos_main);
    TopProductosCaros(productos_main);
    return 0;
}

void AgregarProducto(set<Producto>& productos){
    Producto new_product;
    cout << "=== SISTEMA DE REGISTRO DE PRODUCTOS ===" << endl;
    cout << "Ingresa los datos de los productos. Escribe ID 0 para terminar." << endl;
    do
    {
        cout<<"id: "<<endl;
        cin>> new_product.id;
        if(new_product.id==0) break;
        cout<<"name: "<<endl;
        cin.ignore();
        getline(cin, new_product.nombre);
        cout<<"category: "<<endl;
        getline(cin, new_product.categoria);
        cout<<"precio: "<<endl;
        cin>>new_product.precio;
        cout<<"stock: "<<endl;
        cin>>new_product.stock;
        productos.insert(new_product);
    } while (new_product.id != 0 );
   


}

void AgruparCategoria(map<string,set<int>>& indicePorCategoria,set<Producto>& productos){
    for (const auto &p : productos)
    {
        indicePorCategoria[p.categoria].insert(p.id);
    };
        cout<<"\n--- CLASIFICACION POR CATEGORIA ---" << endl;
        for (const auto& par : indicePorCategoria) {
            cout << "Categoria [" << par.first << "]: ";
            for (int id : par.second) cout << id << " ";
            cout << endl;
        }

}

void BuscarId(unordered_map<int, Producto>& tablaHashProductos, set<Producto>& productos){
    cout<<"\n--- BUSQUEDA POR ID ---" << endl;
   
    for(const auto &p : productos){
        tablaHashProductos[p.id]=p;
    }

    int idBusqueda;
    cout << "\nIngrese ID a buscar: ";
    cin >> idBusqueda;
    if(tablaHashProductos.find(idBusqueda) != tablaHashProductos.end()){
        cout << ">> ENCONTRADO: ";
        Producto p = tablaHashProductos[idBusqueda];
        cout << "ID: " << p.id 
             << " | " << p.nombre 
             << " | Categoria: " << p.categoria 
             << " | Precio: " << p.precio 
             << " | Stock: " << p.stock << endl;
    } else {
        cout << ">> ERROR: Producto no encontrado." << endl;

    }

    



}

void StockBajo(set<Producto>& productos){
    cout << "\n--- PRODUCTOS CON STOCK BAJO (<=5) ---" << endl;
    for (const auto& p : productos) {
        if (p.stock <= 5) {
            cout << "ID: " << p.id 
                 << " | " << p.nombre 
                 << " | Categoria: " << p.categoria 
                 << " | Precio: " << p.precio 
                 << " | Stock: " << p.stock << endl;
        }
    }

}
void TopProductosCaros(set<Producto>& productos){
  vector<Producto> precios (productos.begin(),productos.end());

    sort(precios.begin(), precios.end(), [](const Producto& a, const Producto& b) {
        return a.precio > b.precio; // Descendente
    });
    

    cout << "\n--- TOP 3 PRODUCTOS MAS CAROS ---" << endl;
    for (int i = 0; i < 3 && i < precios.size(); ++i) {
        cout << "Nombre# " << (i + 1) << ": " << precios[i].nombre << endl;
    cout << "ID# " << (i + 1) << ": " << precios[i].id << endl;
    }

}