/*Juego del ahorcado en C++. Versión Demo.
Código Original creado por: Ditecno Digital / Canal de YouTube: https://www.youtube.com/@DitecnoDigital
Adaptado y modificado por: Hernán Ariel Ortega Agüero.
NOTA IMPORTANTE: Dependiendo de la versión de su compilador, para que el juego se ejecute sin errores en devC++ 
por favor vaya a: <<Herramientas<< Opciones de compilador<< Marque la casilla que diga
"Añadir los siguientes comandos al llamar al compilador" y copie el siguiente comando abajo -std=c++11 y presione en "Aceptar"
*/
#include <iostream>		// Libreria general para leer e ingresar datos 
#include <ctime>       // Para generar números aleatorios según el tiempo
#include <cstdlib>     // Para rand() y system()
#include <chrono>      // Para medir el tiempo
using namespace std;
// Declaración de funciones
void LimpiarPantalla();
void JugarPartida();
void Dibujar();
// Variables globales
char eleccion;
string palabras[] = {"monitor", "microfono", "televisor", "telefono", "caja", "wifi", "teclado", "pc", "collar", "manzana"};
string pistas[] = {
    "Dispositivo de salida visual",         // monitor
    "Dispositivo para capturar sonido",     // microfono
    "Aparato que transmite imagen y sonido",// televisor
    "Sirve para hacer llamadas",            // telefono
    "Objeto para guardar cosas",            // caja
    "Tipo de tecnologia de red",             // wifi
    "Dispositivo de entrada con teclas",    // teclado
    "Computadora personal",                 // pc
    "Accesorio para el cuello",             // collar
    "Fruta roja o verde"                    // manzana
};
string palabra, fallidas;
int nA;              // Número aleatorio para elegir palabra
int vida;            // Intentos restantes
bool correcta, completa;
int main() {
    while (true) {
        // Reiniciar variables cada partida
        vida = 6;
        palabra = "";
        fallidas = "";
        LimpiarPantalla(); // Limpiar consola
        // Menú principal
        cout << "\t::::MENU::::" << endl;
        cout << "1) Jugar Partida." << endl;
        cout << "2) Salir." << endl;
        cout << "Eleccion: ";
        cin >> eleccion;
        // Procesar la elección del usuario
        switch (eleccion) {
            case '1':
                JugarPartida();
                break;
            case '2':
                cout << "¡Gracias por jugar!" << endl;
                return 0;
        }
    }
}
// Función principal del juego
void JugarPartida() {
    srand(static_cast<unsigned int>(time(0))); // Semilla para aleatoriedad
    nA = rand() % 10; // Seleccionar palabra al azar del array
    // Inicializar la palabra oculta con guiones
    for (int i = 0; i < (int)palabras[nA].size(); i++) {
        palabra += "-";
    }
    auto inicio = chrono::steady_clock::now(); // Guardar hora de inicio
    int intentos = 0; // Contador de letras ingresadas
    // Bucle principal del juego
    while (vida > 0) {
        LimpiarPantalla();
        cout << "\t::: A H O R C A D O :::" << endl;
        Dibujar(); // Dibujar muñeco según vidas
        // Mostrar información de ayuda
        cout << "Pista: " << pistas[nA] << endl;
        cout << "Fallos: " << fallidas << endl;
        cout << "Progreso: " << palabra << endl;
        // Ingreso de letra por el usuario
        cout << "Ingrese una letra (minuscula): ";
        cin >> eleccion;
        cin.ignore(); // Limpiar el buffer
        intentos++;   // Contar intento
        correcta = false; // Reiniciar estado
        // Verificar si la letra está en la palabra
        for (int i = 0; i < (int)palabras[nA].size(); i++) {
            if (palabras[nA][i] == eleccion) {
                palabra[i] = eleccion;
                correcta = true;
            }
        }
        // Si la letra no fue correcta, restar vida
        if (!correcta) {
            vida--;
            // Agregar a letras fallidas si no estaba ya
            if (fallidas.find(eleccion) == string::npos) {
                fallidas += eleccion;
            }
        }
        // Verificar si se completó la palabra
        completa = true;
        for (int i = 0; i < (int)palabra.size(); i++) {
            if (palabra[i] == '-') {
                completa = false;
            }
        }
        // Si el jugador ganó
        if (completa) {
            auto fin = chrono::steady_clock::now(); // Fin de tiempo
            auto duracion = chrono::duration_cast<chrono::seconds>(fin - inicio).count(); // Calcular duración en segundos
            LimpiarPantalla();
            cout << "\t::: A H O R C A D O :::" << endl;
            Dibujar();
            cout << "Palabra: " << palabras[nA] << endl;
            cout << "¡Ganaste!" << endl;
            cout << "Tiempo tomado: " << duracion << " segundos." << endl;
            cout << "Intentos realizados: " << intentos << endl;
            cout << "Ingresa un caracter para continuar: ";
            cin >> eleccion;
            cin.ignore();
            return;
        }
    }
    // Si el jugador pierde
    LimpiarPantalla();
    cout << "\t::: A H O R C A D O :::" << endl;
    Dibujar();
    cout << "Palabra: " << palabras[nA] << endl;
    cout << "Perdiste. Ingresa un caracter para continuar: ";
    cin >> eleccion;
    cin.ignore();
    return;
}
// Dibuja el ahorcado según la cantidad de vidas restantes
void Dibujar() {
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
            cout << "  --------" << endl;
            cout << "  |      |" << endl;
            cout << "  |      O" << endl;
            cout << "  |     /|\\" << endl;
            cout << "  |     / \\" << endl;
            cout << "  |" << endl;
            cout << "  |" << endl;
            cout << " ---" << endl;
            break;
    }
}
// Limpia la pantalla (solo en Windows)
void LimpiarPantalla() {
    system("cls"); // En Linux o Mac, cambiar por: system("clear");
}

