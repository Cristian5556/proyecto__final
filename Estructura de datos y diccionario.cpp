struct Palabra {
    string palabra;
    string traduccion;
    string funcionalidad;
};

map<string, string> crearDiccionario(const vector<Palabra>& palabras) {
    map<string, string> diccionario;
    for (const Palabra& palabra : palabras) {
        diccionario[palabra.palabra] = palabra.traduccion;
    }
    return diccionario;
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
