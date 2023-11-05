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
