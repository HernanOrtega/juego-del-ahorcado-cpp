/*Juego del ahorcado en C++. Versión Final.
Creado por: Hernán Ariel Ortega Agüero.
NOTA: Para que el juego funcione sin errores en devC++ o similares, usar el flag -std=c++11 en las opciones del compilador.
*/
#include <iostream>
#include <cstdlib>
#include <string>
#include <windows.h> // Para colores y sonidos (solo Windows)
#include <ctime>
#include <chrono>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm> // Para sort
#include <set>
using namespace std;
// --- Declaración de funciones ---
void LimpiarPantalla();
bool IniciarSesion();
bool RegistrarUsuario();
void MenuLogin();
void MostrarMenuPrincipal();
void MostrarSubmenuJugar();
void JugarModoSolitario();
void JugarModoMultijugador();
void MostrarCategorias();
void MostrarDificultad();
void MostrarPuntajes();
void Dibujar(int vida);
void ReproducirSonido(const string&);
bool EntradaValida(const string&);
void ConfigurarColor(int color);
// --- Variables globales ---
char eleccion;
string usuarioActivo = "";
bool esAnonimo = false;
// Categorías y palabras
// Tecnología
string tecnologia[] = {
    "computadora", "internet", "programador", "pantalla", "teclado",
    "monitor", "raton", "usb", "servidor", "red",
    "software", "hardware", "sistema", "procesador", "archivo",
    "bit", "circuito", "robot", "codigo", "algoritmo"
};
string pistas_tecnologia[] = {
    "Maquina de procesamiento de datos",
    "Red mundial de comunicacion",
    "Persona que escribe codigo",
    "Dispositivo de salida visual",
    "Dispositivo de entrada con teclas",
    "Pantalla de computadora",
    "Dispositivo senialador",
    "Puerto de conexion rapida",
    "Equipo que almacena y distribuye datos",
    "Conexion entre dispositivos",
    "Conjunto de programas",
    "Parte fisica de un sistema",
    "Conjunto de elementos que interactuan",
    "Unidad central de procesamiento",
    "Contenedor digital de informacion",
    "Unidad minima de informacion",
    "Conexion entre componentes",
    "Maquina automatica programable",
    "Conjunto de instrucciones",
    "Serie de pasos logicos"
};
// Naturaleza
string naturaleza[] = {
    "arbol", "flor", "rayo", "trueno", "lluvia",
    "bosque", "lago", "rio", "montana", "nube",
    "sol", "mar", "viento", "hoja", "piedra",
    "arena", "cascada", "desierto", "fuego", "cielo"
};
string pistas_naturaleza[] = {
    "Planta grande con tronco",
    "Parte colorida de la planta",
    "Descarga electrica natural",
    "Sonido fuerte en tormentas",
    "Agua que cae del cielo",
    "Conjunto de arboles",
    "Cuerpo de agua cerrado",
    "Corriente de agua",
    "Elevacion del terreno",
    "Acumulacion de vapor de agua",
    "Estrella del sistema solar",
    "Gran masa de agua salada",
    "Corriente de aire",
    "Parte de la planta",
    "Fragmento solido natural",
    "Particulas finas del suelo",
    "Agua cayendo desde altura",
    "Zona arida y seca",
    "Elemento caliente",
    "Espacio azul sobre nosotros"
};
// Comidas
string comidas[] = {
    "pizza", "hamburguesa", "arroz", "pollo", "ensalada",
    "caldo", "asado", "tarta", "empanada", "tortilla",
    "fruta", "manzana", "banana", "naranja", "pan",
    "queso", "fideo", "guiso", "sushi", "milanesa"
};
string pistas_comidas[] = {
    "Comida con queso y salsa",
    "Sandwich con carne y pan",
    "Grano basico cocido",
    "Ave comestible",
    "Mezcla de vegetales",
    "Liquido caliente para comer",
    "Carne cocida a la parrilla",
    "Comida horneada con relleno",
    "Masa rellena doblada",
    "Plato con huevo batido",
    "Alimento dulce o acido",
    "Fruta roja o verde",
    "Fruta amarilla curvada",
    "Fruta citrica",
    "Producto de harina basico",
    "Lacteo firme y sabroso",
    "Pasta delgada hervida",
    "Comida casera de olla",
    "Comida japonesa con arroz",
    "Filete de carne frito u horneado"
};
// Profesiones
string profesiones[] = {
    "doctor", "maestro", "bombero", "policia", "ingeniero",
    "arquitecto", "abogado", "panadero", "electricista", "mecanico",
    "enfermero", "carpintero", "veterinario", "cocinero", "cientifico",
    "dentista", "soldado", "musico", "actor", "piloto"
};
string pistas_profesiones[] = {
    "Atiende la salud de las personas",
    "Ensenia en escuelas",
    "Apaga incendios",
    "Mantiene el orden",
    "Disenia soluciones tecnicas",
    "Disenia planos de edificios",
    "Defiende legalmente a otros",
    "Hace pan",
    "Trabaja con electricidad",
    "Repara vehiculos",
    "Cuida pacientes",
    "Trabaja con madera",
    "Cuida animales",
    "Prepara alimentos",
    "Investiga fenomenos",
    "Cuida los dientes",
    "Miembro del ejercito",
    "Hace musica",
    "Actua en obras o peliculas",
    "Conduce aviones"
};
// Objetos
string objetos[] = {
    "reloj", "celular", "mesa", "silla", "lampara",
    "puerta", "ventana", "cuadro", "libro", "lapiz",
    "boligrafo", "mochila", "caja", "control", "bateria",
    "zapato", "anteojo", "botella", "camara", "regla"
};
string pistas_objetos[] = {
    "Marca la hora",
    "Telefono movil",
    "Mueble para apoyar cosas",
    "Mueble para sentarse",
    "Emite luz",
    "Entrada con cerradura",
    "Abertura con vidrio",
    "Decoracion en la pared",
    "Conjunto de hojas escritas",
    "Instrumento para escribir o dibujar",
    "Lapiz de tinta",
    "Bolso para llevar cosas",
    "Contenedor rectangular",
    "Mando a distancia",
    "Fuente de energia portatil",
    "Calzado para el pie",
    "Lentes para ver mejor",
    "Recipiente para liquidos",
    "Dispositivo para sacar fotos",
    "Instrumento para medir"
};
// Variables para juego
string palabraOculta;       // palabra que se adivina
string palabraEnProgreso;   // palabra con guiones y letras descubiertas
string letrasFallidas;      // letras incorrectas ingresadas
int vida;                  // intentos restantes
int categoriaSeleccionada = 0;  // categoría elegida
int dificultadSeleccionada = 0;
// --- Función principal ---
int main(){
	MenuLogin();
    srand(static_cast<unsigned int>(time(0))); // inicializar semilla aleatoria
    while (true) {
        LimpiarPantalla();
        MostrarMenuPrincipal();
        cin >> eleccion;
        cin.ignore();
        switch (eleccion) {
            case '1':
                MostrarSubmenuJugar();
                break;
            case '2':
                MostrarPuntajes();
                break;
            case '3':
                cout << "Gracias por jugar. iHasta la proxima!" << endl;
                return 0;
            default:
				continue;
        }
    }
    return 0;
}
// --- Funciones de menú ---
void MostrarMenuPrincipal() {
	ConfigurarColor(6); // amarillo para títulos
    cout << "\t:::: JUEGO DEL AHORCADO - MENU PRINCIPAL ::::" << endl;
    ConfigurarColor(11); // celeste para opciones
    cout << "1) Jugar partida." << endl;
    cout << "2) Ver puntajes globales." << endl;
    cout << "3) Salir." << endl;
    ConfigurarColor(7); // blanco para ingresar valores
    cout << "\nSeleccione una opcion: ";
}
void MostrarSubmenuJugar() {
while (true) {
    LimpiarPantalla();
    ConfigurarColor(6);
    cout << "\t:::: MODO DE JUEGO ::::" << endl;
    ConfigurarColor(11);
    cout << "1) Modo Solitario." << endl;
    cout << "2) Modo Multijugador." << endl;
    cout << "3) Volver al menu principal." << endl;
    ConfigurarColor(7);
    cout << "\nSeleccione una opcion: ";
    cin >> eleccion;
    cin.ignore();
    if (eleccion == '1') {
        JugarModoSolitario();
        break;
    } else if (eleccion == '2') {
        JugarModoMultijugador();
        break;
    } else if (eleccion == '3') {
        break;  // salir del submenu
    }
  }
}
void MostrarCategorias(){
    while (true){
        LimpiarPantalla();
        ConfigurarColor(6);
        cout << "\t:::: CATEGORIAS ::::" << endl;
        ConfigurarColor(11);
        cout << "1) Tecnologia." << endl;
        cout << "2) Naturaleza." << endl;
        cout << "3) Comidas." << endl;
        cout << "4) Profesiones." << endl;
        cout << "5) Volver al menu anterior." << endl;
        ConfigurarColor(7);
        cout << "\nSeleccione una opcion: ";
        cin >> eleccion;
        cin.ignore();
        if (eleccion == '1' || eleccion == '2' || eleccion == '3' || eleccion == '4') {
            categoriaSeleccionada = eleccion - '0'; // Guardamos como número 1 a 4
            break; // salimos del menú de categorías
        } else if (eleccion == '5') {
            categoriaSeleccionada = 0; // para saber que se canceló
            return MostrarSubmenuJugar(); // salimos y volvemos al menú anterior
        }
        // si la entrada no es válida, simplemente repite el menú
    }
}
void MostrarDificultad(){
	while(true){
	LimpiarPantalla();
	ConfigurarColor(6);
    cout << "\t:::: DIFICULTAD ::::" << endl;
    ConfigurarColor(11);
    cout << "1) Facil (con pistas)." << endl;
    cout << "2) Dificil (sin pistas)." << endl;
    cout << "3) Volver al menu anterior. " << endl;
    ConfigurarColor(7);
    cout << "\nSeleccione una opcion: ";
    cin >> eleccion;
    cin.ignore();
        if (eleccion == '1' || eleccion == '2') {
            dificultadSeleccionada = eleccion - '0'; // Guardamos como número 1 a 2
            break; // salimos del menú de dificultades
        } else if (eleccion == '3') {
            dificultadSeleccionada = 0; // para saber que se canceló
            return MostrarCategorias(); // salimos y volvemos al menú anterior
        }
        // si la entrada no es válida, simplemente repite el menú
    }
}
// --- Función que elige palabra y pista según categoría ---
void ElegirPalabraYPista(string& palabra, string& pista) {
    int n = 0;
    switch (categoriaSeleccionada) {
        case 1: // Tecnología
            n = rand() % (sizeof(tecnologia)/sizeof(tecnologia[0]));
            palabra = tecnologia[n];
            pista = pistas_tecnologia[n];
            break;
        case 2: // Naturaleza
            n = rand() % (sizeof(naturaleza)/sizeof(naturaleza[0]));
            palabra = naturaleza[n];
            pista = pistas_naturaleza[n];
            break;
        case 3: // Comidas
            n = rand() % (sizeof(comidas)/sizeof(comidas[0]));
            palabra = comidas[n];
            pista = pistas_comidas[n];
            break;
        case 4: // Profesiones
            n = rand() % (sizeof(profesiones)/sizeof(profesiones[0]));
            palabra = profesiones[n];
            pista = pistas_profesiones[n];
            break;
        case 5: // Objetos
            n = rand() % (sizeof(objetos)/sizeof(objetos[0]));
            palabra = objetos[n];
            pista = pistas_objetos[n];
            break;
        default:
            palabra = "computadora";
            pista = "Maquina de procesamiento de datos";
            break;
    }
}
void JugarModoSolitario() {
    LimpiarPantalla();
    MostrarCategorias();
    if (categoriaSeleccionada == 0) return;
    MostrarDificultad();
    if (dificultadSeleccionada == 0) return;
    string pista;
    ElegirPalabraYPista(palabraOculta, pista);
    palabraEnProgreso = string(palabraOculta.size(), '-');
    letrasFallidas = "";
    vida = 6;
    auto inicio = chrono::steady_clock::now();
    int intentos = 0;
    while (vida > 0) {
        LimpiarPantalla();
        ConfigurarColor(6);
        cout << "\t::: S O L I T A R I O :::" << endl;
        ConfigurarColor(7);
        Dibujar(vida);
        if (dificultadSeleccionada == 1) cout << "Pista: " << pista << endl;
        cout << "Fallos: " << letrasFallidas << endl;
        cout << "Progreso: " << palabraEnProgreso << endl;
        cout << "Ingrese letra(s) minuscula(s) o ingrese el numero 0 para rendirse: ";
        string entrada;
        getline(cin, entrada);
        if (entrada == "0") {
            ReproducirSonido("derrota");
            LimpiarPantalla();
            ConfigurarColor(6);
            cout << "\t::: S O L I T A R I O :::" << endl;
            ConfigurarColor(4);
            Dibujar(vida);
            ConfigurarColor(4);
            cout << "Te rendiste, " << usuarioActivo << "." << endl;
            cout << "La palabra correcta era: " << palabraOculta << endl;
            auto fin = chrono::steady_clock::now();
            auto duracion = chrono::duration_cast<chrono::seconds>(fin - inicio).count();
            if (!esAnonimo && !usuarioActivo.empty()) {
                ofstream out("puntajes.txt", ios::app);
                out << usuarioActivo << ";derrota;" << palabraOculta << ";" << duracion << ";\n";
            }
            ConfigurarColor(7);
            system("pause");
            return;
        }
        if (entrada == palabraOculta) {
            palabraEnProgreso = palabraOculta;
            intentos++; // ? contar como intento
            ReproducirSonido("victoria");
            LimpiarPantalla();
            ConfigurarColor(6);
            cout << "\t::: S O L I T A R I O :::" << endl;
            ConfigurarColor(2);
            Dibujar(vida);
            ConfigurarColor(2);
            cout << "¡Ganaste, " << usuarioActivo << "!" << endl;
            cout << "Palabra: " << palabraOculta << endl;
            auto fin = chrono::steady_clock::now();
            auto duracion = chrono::duration_cast<chrono::seconds>(fin - inicio).count();
            cout << "Tiempo tomado: " << duracion << " segundos." << endl;
            cout << "Cantidad de intentos: " << intentos << endl;
            if (!esAnonimo && !usuarioActivo.empty()) {
                ofstream out("puntajes.txt", ios::app);
                out << usuarioActivo << ";victoria;" << palabraOculta << ";" << duracion << ";" << dificultadSeleccionada << ";\n";
            }
            ConfigurarColor(7);
            system("pause");
            return;
        }

        // Ingreso de letras
        for (char letra : entrada) {
            if (!isalpha(letra) || !islower(letra)) continue;
            if (palabraEnProgreso.find(letra) != string::npos || letrasFallidas.find(letra) != string::npos) continue;

            intentos++; // ? contar solo nuevas letras

            bool acierto = false;
            for (size_t i = 0; i < palabraOculta.size(); i++) {
                if (palabraOculta[i] == letra && palabraEnProgreso[i] == '-') {
                    palabraEnProgreso[i] = letra;
                    acierto = true;
                }
            }

            if (acierto) {
                ReproducirSonido("acierto");
            } else {
                letrasFallidas += letra;
                vida--;
                ReproducirSonido("fallo");
            }
        }

        if (palabraEnProgreso == palabraOculta) {
            ReproducirSonido("victoria");
            LimpiarPantalla();
            ConfigurarColor(6);
            cout << "\t::: S O L I T A R I O :::" << endl;
            ConfigurarColor(2);
            Dibujar(vida);
            ConfigurarColor(2);
            cout << "¡Ganaste, " << usuarioActivo << "!" << endl;
            cout << "Palabra: " << palabraOculta << endl;
            auto fin = chrono::steady_clock::now();
            auto duracion = chrono::duration_cast<chrono::seconds>(fin - inicio).count();
            cout << "Tiempo tomado: " << duracion << " segundos." << endl;
            cout << "Cantidad de intentos: " << intentos << endl;
            if (!esAnonimo && !usuarioActivo.empty()) {
                ofstream out("puntajes.txt", ios::app);
                out << usuarioActivo << ";victoria;" << palabraOculta << ";" << duracion << ";" << dificultadSeleccionada << ";\n";
            }
            ConfigurarColor(7);
            system("pause");
            return;
        }
    }

    ReproducirSonido("derrota");
    LimpiarPantalla();
    ConfigurarColor(6);
    cout << "\t::: S O L I T A R I O :::" << endl;
    ConfigurarColor(4);
    Dibujar(vida);
    ConfigurarColor(4);
    cout << "Perdiste, " << usuarioActivo << "." << endl;
    cout << "La palabra correcta era: " << palabraOculta << endl;
    auto fin = chrono::steady_clock::now();
    auto duracion = chrono::duration_cast<chrono::seconds>(fin - inicio).count();
    if (!esAnonimo && !usuarioActivo.empty()) {
        ofstream out("puntajes.txt", ios::app);
        out << usuarioActivo << ";derrota;" << palabraOculta << ";" << duracion << ";" << dificultadSeleccionada << ";\n";
    }
    ConfigurarColor(7);
    system("pause");
}

// --- Juego modo multijugador ---
void JugarModoMultijugador() {
    while (true) {
        LimpiarPantalla();
        ConfigurarColor(6);
        cout << "Jugador 1 - Ingrese una palabra secreta (solo letras minusculas): ";
        string palabraSecreta;
        getline(cin, palabraSecreta);
        if (!EntradaValida(palabraSecreta)) continue;

        palabraOculta = palabraSecreta;
        palabraEnProgreso = string(palabraOculta.size(), '-');
        letrasFallidas = "";
        vida = 6;
        auto inicio = chrono::steady_clock::now();
        int intentos = 0;
        set<char> letrasUsadas;

        LimpiarPantalla();
        ConfigurarColor(6);
        cout << "Jugador 2 - Adivine la palabra secreta." << endl;

        while (vida > 0) {
            ConfigurarColor(6);
            cout << "\t::: M U L T I J U G A D O R :::" << endl;
            ConfigurarColor(7);
            Dibujar(vida);
            cout << "Fallos: " << letrasFallidas << endl;
            cout << "Progreso: " << palabraEnProgreso << endl;
            cout << "Ingrese letra(s) minuscula(s) o ingrese 0 para rendirse: ";
            string entrada;
            getline(cin, entrada);
            LimpiarPantalla();

            if (entrada == "0") {
                vida = 0;
                break;
            }

            if (entrada == palabraOculta) {
                palabraEnProgreso = palabraOculta;
                intentos++; // ? se cuenta como intento
                ReproducirSonido("victoria");
                ConfigurarColor(6);
                cout << "\t::: M U L T I J U G A D O R :::" << endl;
                ConfigurarColor(2);
                Dibujar(vida);
                ConfigurarColor(2);
                cout << "Jugador 2 GANO" << endl;
                cout << "Palabra: " << palabraOculta << endl;
                auto fin = chrono::steady_clock::now();
                auto duracion = chrono::duration_cast<chrono::seconds>(fin - inicio).count();
                cout << "Tiempo tomado: " << duracion << " segundos." << endl;
                cout << "Cantidad de intentos: " << intentos << endl;
                ConfigurarColor(7);
                system("pause");
                return;
            }

            // Ingreso de letras
            bool huboAcierto = false;
            for (char letra : entrada) {
                if (!isalpha(letra) || !islower(letra)) continue;
                if (letrasUsadas.count(letra)) continue;

                letrasUsadas.insert(letra);
                intentos++; // ? se cuenta solo si es nueva

                bool acierto = false;
                for (size_t i = 0; i < palabraOculta.size(); i++) {
                    if (palabraOculta[i] == letra && palabraEnProgreso[i] == '-') {
                        palabraEnProgreso[i] = letra;
                        acierto = true;
                    }
                }

                if (acierto) {
                    ReproducirSonido("acierto");
                    huboAcierto = true;
                } else {
                    letrasFallidas += letra;
                    vida--;
                    ReproducirSonido("fallo");
                    if (vida == 0) break;
                }
            }

            if (palabraEnProgreso == palabraOculta) {
                ReproducirSonido("victoria");
                ConfigurarColor(6);
                cout << "\t::: M U L T I J U G A D O R :::" << endl;
                ConfigurarColor(2);
                Dibujar(vida);
                ConfigurarColor(2);
                cout << "Jugador 2 GANO" << endl;
                cout << "Palabra: " << palabraOculta << endl;
                auto fin = chrono::steady_clock::now();
                auto duracion = chrono::duration_cast<chrono::seconds>(fin - inicio).count();
                cout << "Tiempo tomado: " << duracion << " segundos." << endl;
                cout << "Cantidad de intentos: " << intentos << endl;
                ConfigurarColor(7);
                system("pause");
                return;
            }
        }

        // Si pierde
        ReproducirSonido("derrota");
        ConfigurarColor(6);
        cout << "\t::: M U L T I J U G A D O R :::" << endl;
        ConfigurarColor(4);
        Dibujar(vida);
        ConfigurarColor(4);
        cout << "Perdiste Jugador 2. Jugador 1 GANO" << endl;
        cout << "La palabra correcta era: " << palabraOculta << endl;
        ConfigurarColor(7);
        system("pause");
        return;
    }
}

// --- Muestra puntajes globales ---
void MostrarPuntajes() {
    LimpiarPantalla();
    ConfigurarColor(13);
    cout << "\t:::: PUNTAJES GLOBALES ::::\n" << endl;
    ConfigurarColor(8);
    cout << "\t::: REGLAS DE CALCULO DEL RANKING (MODO SOLITARIO) :::\n";
    ConfigurarColor(11);
	cout << "- Modo Facil: +50 puntos por victoria, -20 por derrota.\n";
	cout << "- Modo Dificil: +100 puntos por victoria, -50 por derrota.\n";
	cout << "- Cada partida ganada tambien suma +10 por palabra adivinada.\n";
	cout << "- El ranking final se calcula como:\n";
	cout << "    (Total de puntos acumulados) / (Partidas jugadas)\n";
	cout << "  Muchas derrotas o jugar solo en facil puede reducir el promedio.\n";
	cout << "\n";
    struct RegistroPuntaje {
        string usuario;
        int victorias = 0;
        int derrotas = 0;
        int palabrasAdivinadas = 0;
        int partidasJugadas = 0;
        int tiempoTotal = 0;
        double rankingScore = 0.0;
    };
    vector<RegistroPuntaje> registros;
    map<string, RegistroPuntaje> resumen;
    ifstream archivo("puntajes.txt");
    if (!archivo) {
        cout << "No se encontraron puntajes registrados." << endl;
        system("pause");
        return;
    }
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string usuario, resultado, palabra, tiempoStr, dificultadStr;
        getline(ss, usuario, ';');
        getline(ss, resultado, ';');
        getline(ss, palabra, ';');
        getline(ss, tiempoStr, ';');
        getline(ss, dificultadStr, ';');
        int tiempo = stoi(tiempoStr);
        int dificultad = dificultadStr.empty() ? 1 : stoi(dificultadStr); // si está vacío, asumir fácil
        RegistroPuntaje& reg = resumen[usuario];
        reg.usuario = usuario;
        reg.partidasJugadas++;
        reg.tiempoTotal += tiempo;
        if (resultado == "victoria") {
            reg.victorias++;
            reg.palabrasAdivinadas++;
            if (dificultad == 2) {
                reg.rankingScore += 100; // ganar en difícil
            } else {
                reg.rankingScore += 50; // ganar en fácil
            }
        } else if (resultado == "derrota") {
            reg.derrotas++;
            if (dificultad == 2) {
                reg.rankingScore -= 50; // perder en difícil
            } else {
                reg.rankingScore -= 20; // perder en fácil
            }
        }
    }
    for (auto& par : resumen) {
        RegistroPuntaje reg = par.second;
        // rankingScore ya fue calculado arriba
        registros.push_back(reg);
    }
    // Ordenar de mayor a menor por rankingScore
    sort(registros.begin(), registros.end(), [](const RegistroPuntaje& a, const RegistroPuntaje& b) {
        return a.rankingScore > b.rankingScore;
    });
    // Mostrar tabla
    ConfigurarColor(2);
    cout << left << setw(4) << "#" << setw(15) << "Usuario" << setw(10) << "Puntaje" << setw(10)
         << "Jugadas" << setw(10) << "Adiv." << setw(10) << "Vict." << setw(10)
         << "Derrot." << setw(12) << "Tiempo" << endl;
    ConfigurarColor(6);
    cout << string(70, '-') << endl;
    int pos = 1;
    for (auto& reg : registros) {
    	ConfigurarColor(7);
        cout << left << setw(4) << pos++
             << setw(15) << reg.usuario
             << setw(10) << fixed << setprecision(1) << reg.rankingScore
             << setw(10) << reg.partidasJugadas
             << setw(10) << reg.palabrasAdivinadas
             << setw(10) << reg.victorias
             << setw(10) << reg.derrotas
             << setw(12) << reg.tiempoTotal << endl;
    }
    cout << endl;
    system("pause");
}
// --- Dibuja el ahorcado según la cantidad de vidas restantes ---
void Dibujar(int vida) {
    switch (vida) {
        case 6:
            cout << "  --------" << endl;
            cout << "  |      |" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << " ---" << endl;
            break;
        case 5:
            cout << "  --------" << endl;
            cout << "  |      |" << endl;
            cout << "  |      O" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << " ---" << endl;
            break;
        case 4:
            cout << "  --------" << endl;
            cout << "  |      |" << endl;
            cout << "  |      O" << endl;
            cout << "  |      |" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << " ---" << endl;
            break;
        case 3:
            cout << "  --------" << endl;
            cout << "  |      |" << endl;
            cout << "  |      O" << endl;
            cout << "  |     /|" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << " ---" << endl;
            break;
        case 2:
            cout << "  --------" << endl;
            cout << "  |      |" << endl;
            cout << "  |      O" << endl;
            cout << "  |     /|\\" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << " ---" << endl;
            break;
        case 1:
            cout << "  --------" << endl;
            cout << "  |      |" << endl;
            cout << "  |      O" << endl;
            cout << "  |     /|\\" << endl;
            cout << "  |     /" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << " ---" << endl;
            break;
        case 0:
        	ConfigurarColor(12); // Rojo
            cout << "  --------" << endl;
            cout << "  |      |" << endl;
            cout << "  |      O" << endl;
            cout << "  |     /|\\" << endl;
            cout << "  |     / \\" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << " ---" << endl;
            ConfigurarColor(7);
            break;
    }
}
// --- Limpia la pantalla (solo en Windows) ---
void LimpiarPantalla() {
    system("cls");
}
// --- Reproduce sonidos para diferentes eventos ---
void ReproducirSonido(const string& tipo) {
    if (tipo == "fallo") Beep(300, 300);
    else if (tipo == "acierto") Beep(700, 200);
    else if (tipo == "victoria") Beep(1000, 500);
    else if (tipo == "derrota") Beep(200, 500);
}
// --- Verifica si la entrada contiene solo letras minusculas ---
bool EntradaValida(const string& entrada) {
    for (char c : entrada) {
        if (!islower(c)) return false;
    }
    return true;
}
// --- Menú de Login ---
void MenuLogin() {
    while (true) {
        LimpiarPantalla();
        ConfigurarColor(3);
        cout << "\t:::: SISTEMA DE CUENTAS - JUEGO DEL AHORCADO ::::\n";
        ConfigurarColor(1);
        cout << "1) Iniciar sesion. " << endl;
        cout << "2) Registrarse. " << endl;
        cout << "3) Jugar como anonimo (no se guardaran puntajes de las partidas). " << endl;
        ConfigurarColor(7);
        cout << "\nSeleccione una opcion: ";
        cin >> eleccion;
        cin.ignore();
        if (eleccion == '1') {
            if (IniciarSesion()) break;
        } else if (eleccion == '2') {
            if (RegistrarUsuario()) {
                cout << "\nRegistro exitoso.\n";
                system("pause");
                break;
            }
            system("pause");
        } else if (eleccion == '3') {
            usuarioActivo = "Anonimo";
            esAnonimo = true;
            break;
        }
    }
}
// --- Registro de nuevo usuario ---
bool RegistrarUsuario() {
	ConfigurarColor(7);
    string usuario, contrasena;
    cout << "Ingrese nombre de usuario: ";
    getline(cin, usuario);
    cout << "Ingrese una contrasenia: ";
    getline(cin, contrasena);
    // Verificar si ya existe
    ifstream archivoLectura("usuarios.txt");
    string linea;
    while (getline(archivoLectura, linea)) {
        size_t sep = linea.find(';');
        string userExistente = linea.substr(0, sep);
        if (userExistente == usuario) {
            cout << "\nEse nombre de usuario ya existe.\n";
            return false;
        }
    }
    archivoLectura.close();
    ofstream archivo("usuarios.txt", ios::app);
    archivo << usuario << ";" << contrasena << endl;
    archivo.close();
    // Configurar la sesión como iniciada después del registro
    usuarioActivo = usuario;
    esAnonimo = false;
    return true;
}
// --- Iniciar sesión ---
bool IniciarSesion() {
	ConfigurarColor(7);
    string usuario, contrasena;
    cout << "Ingrese su nombre de usuario: ";
    getline(cin, usuario);
    cout << "Ingrese su contrasenia: ";
    getline(cin, contrasena);
    ifstream archivo("usuarios.txt");
    string linea;
    while (getline(archivo, linea)) {
        size_t sep = linea.find(';');
        string usuarioArchivo = linea.substr(0, sep);
        string contrasenaArchivo = linea.substr(sep + 1);
        if (usuarioArchivo == usuario && contrasenaArchivo == contrasena) {
            usuarioActivo = usuario;
            esAnonimo = false;
            return true;
        }
    }
    cout << "\nUsuario o contrasenia incorrectos.\n";
    system("pause");
    return false;
}
void ConfigurarColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

