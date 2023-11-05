#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

struct Palabra {
    string palabra;
    string traduccion;
    string funcionalidad;
};

void agregarPalabra(vector<Palabra>& palabras) {
    Palabra nuevaPalabra;
    cout << "Ingrese Palabra: ";
    cin >> nuevaPalabra.palabra;
    cout << "Ingrese Traduccion: ";
    cin >> nuevaPalabra.traduccion;
    cin.ignore();
    cout << "Ingrese Funcionalidad: ";
    getline(cin, nuevaPalabra.funcionalidad);

    palabras.push_back(nuevaPalabra);
    cout << "La palabra se ha agregado al diccionario." << endl;
}

void mostrarPalabras(const vector<Palabra>& palabras) {
    cout << "Diccionario de palabras:" << endl;
    for (const Palabra& palabra : palabras) {
        cout << "Palabra: " << palabra.palabra << endl;
        cout << "Traduccion: " << palabra.traduccion << endl;
        cout << "Funcionalidad: " << palabra.funcionalidad << endl;
        cout << "==============================" << endl;
    }
}

void actualizarPalabra(vector<Palabra>& palabras) {
    string palabraActual;
    cout << "Ingrese la palabra que desea actualizar: ";
    cin >> palabraActual;

    for (Palabra& palabra : palabras) {
        if (palabra.palabra == palabraActual) {
            cout << "Ingrese nueva Traduccion: ";
            cin >> palabra.traduccion;
            cin.ignore();
            cout << "Ingrese nueva Funcionalidad: ";
            getline(cin, palabra.funcionalidad);
            cout << "La palabra se ha actualizado." << endl;
            return;
        }
    }

    cout << "La palabra no se encontró en el diccionario." << endl;
}

void borrarPalabra(vector<Palabra>& palabras) {
    string palabraAEliminar;
    cout << "Ingrese la palabra que desea eliminar: ";
    cin >> palabraAEliminar;

    for (auto it = palabras.begin(); it != palabras.end(); ++it) {
        if (it->palabra == palabraAEliminar) {
            palabras.erase(it);
            cout << "La palabra se ha eliminado del diccionario." << endl;
            return;
        }
    }

    cout << "La palabra no se encontro en el diccionario." << endl;
}

map<string, string> crearDiccionario(const vector<Palabra>& palabras) {
    map<string, string> diccionario;
    for (const Palabra& palabra : palabras) {
        diccionario[palabra.palabra] = palabra.traduccion;
    }
    return diccionario;
}

string traducirLinea(const string& linea, const map<string, string>& diccionario) {
    istringstream stream(linea);
    string palabra;
    string resultado;

    while (stream >> palabra) {
        if (palabra == "{" || palabra == "}") {
            resultado += palabra + " ";
        } else {
            auto it = diccionario.find(palabra);
            if (it != diccionario.end()) {
                resultado += it->second + " ";
            } else {
                resultado += palabra + " ";
            }
        }
    }

    return resultado;
}

void guardarDiccionario(const vector<Palabra>& palabras) {
    ofstream archivo("diccionario.txt");
    if (archivo.is_open()) {
        for (const Palabra& palabra : palabras) {
            archivo << palabra.palabra << "," << palabra.traduccion << "," << palabra.funcionalidad << endl;
        }
        archivo.close();
    } else {
        cout << "No se pudo guardar el diccionario." << endl;
    }
}

void cargarDiccionario(vector<Palabra>& palabras) {
    ifstream archivo("diccionario.txt");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            Palabra nuevaPalabra;
            getline(ss, nuevaPalabra.palabra, ',');
            getline(ss, nuevaPalabra.traduccion, ',');
            getline(ss, nuevaPalabra.funcionalidad);
            palabras.push_back(nuevaPalabra);
        }
        archivo.close();
    }
}

string traducirCodigo(const string& codigo, const map<string, string>& diccionario) {
    istringstream stream(codigo);
    string linea;
    ostringstream resultado;

    while (getline(stream, linea)) {
        string lineaTraducida = traducirLinea(linea, diccionario);
        resultado << lineaTraducida << endl;
    }

    return resultado.str();
}

int main() {
    vector<Palabra> diccionario;
    map<string, string> diccionarioTraducciones;

    cargarDiccionario(diccionario);
    diccionarioTraducciones = crearDiccionario(diccionario);

    while (true) {
        cout << "Seleccione una opcion:\n";
        cout << "1 - Agregar Palabra\n";
        cout << "2 - Mostrar Palabras\n";
        cout << "3 - Actualizar Palabra\n";
        cout << "4 - Borrar Palabra\n";
        cout << "5 - Traducir C++\n";
        cout << "6 - Salir\n";

        int opcion;
        cin >> opcion;

        if (opcion == 1) {
            agregarPalabra(diccionario);
            guardarDiccionario(diccionario);
            diccionarioTraducciones = crearDiccionario(diccionario);
        } else if (opcion == 2) {
            mostrarPalabras(diccionario);
        } else if (opcion == 3) {
            actualizarPalabra(diccionario);
            guardarDiccionario(diccionario);
            diccionarioTraducciones = crearDiccionario(diccionario);
        } else if (opcion == 4) {
            borrarPalabra(diccionario);
            guardarDiccionario(diccionario);
            diccionarioTraducciones = crearDiccionario(diccionario);
        } else if (opcion == 5) {
            cin.ignore();
            cout << "Ingrese el codigo C++ para traducir:" << endl;
            string codigo;
            string linea;
            while (true) {
                getline(cin, linea);
                if (linea.empty()) {
                    break;
                }
                codigo += linea + "\n";
            }
            string codigoTraducido = traducirCodigo(codigo, diccionarioTraducciones);
            cout << codigoTraducido;
        } else if (opcion == 6) {
            break;
        } else {
            cout << "Opcion no valida. Por favor, seleccione una opcion valida." << endl;
        }
    }

    return 0;
}
