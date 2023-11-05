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
