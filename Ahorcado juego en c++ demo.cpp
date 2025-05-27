#include <iostream>
#include <string>

using namespace std;

// Prototipos de funciones
void mostrarMenu();
void jugarAhorcado();
void mostrarAhorcado(int intentos);

// Función principal
int main() {
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                jugarAhorcado();
                break;
            case 2:
                cout << "Gracias por jugar. Hasta pronto." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente." << endl;
        }

    } while (opcion != 2);

    return 0;
}

// ================================
// Muestra el menú principal del juego
// ================================
void mostrarMenu() {
    cout << "\n==============================" << endl;
    cout << "      JUEGO DEL AHORCADO      " << endl;
    cout << "==============================" << endl;
    cout << "1. Iniciar juego" << endl;
    cout << "2. Salir" << endl;
    cout << "------------------------------" << endl;
    cout << "Seleccione una opcion: ";
}

// ================================
// Dibuja la figura del ahorcado según los intentos restantes
// ================================
void mostrarAhorcado(int intentos) {
    cout << "\n +----+" << endl;
    cout << " |    |" << endl;

    // Cabeza
    if (intentos <= 5)
        cout << " O    |" << endl;
    else
        cout << "      |" << endl;

    // Cuerpo y brazos
    if (intentos <= 4 && intentos > 3)
        cout << " |    |" << endl;
    else if (intentos <= 3 && intentos > 2)
        cout << "/|    |" << endl;
    else if (intentos <= 2)
        cout << "/|\\   |" << endl;
    else
        cout << "      |" << endl;

    // Piernas
    if (intentos == 1)
        cout << "/     |" << endl;
    else if (intentos == 0)
        cout << "/ \\   |" << endl;
    else
        cout << "      |" << endl;

    cout << "      |" << endl;
    cout << "=========" << endl;
}

// ================================
// Lógica del juego del ahorcado
// ================================
void jugarAhorcado() {
    string palabra = "programa"; // Palabra secreta fija para esta demo
    string adivinada = "";       // Representa la palabra con guiones bajos
    int intentosRestantes = 6;   // Máximo de intentos permitidos
    char letra;
    bool acierto;

    // Inicializa la palabra adivinada con guiones bajos
    for (int i = 0; i < palabra.length(); i++) {
        adivinada += '_';
    }

    cout << "\n¡Comienza el juego del ahorcado!" << endl;

    // Bucle principal del juego
    while (intentosRestantes > 0 && adivinada != palabra) {
        // Muestra el estado actual de la palabra
        cout << "\nPalabra: ";
        for (int i = 0; i < adivinada.length(); i++) {
            cout << adivinada[i] << " ";
        }

        // Muestra la cantidad de intentos y el dibujo del ahorcado
        cout << "\nIntentos restantes: " << intentosRestantes << endl;
        mostrarAhorcado(intentosRestantes);

        // Pide una letra al usuario
        cout << "Ingrese una letra: ";
        cin >> letra;

        acierto = false;

        // Verifica si la letra está en la palabra
        for (int i = 0; i < palabra.length(); i++) {
            if (palabra[i] == letra && adivinada[i] != letra) {
                adivinada[i] = letra; // Reemplaza guión por letra adivinada
                acierto = true;
            }
        }

        // Mensaje según si acertó o no
        if (acierto) {
            cout << "¡Bien hecho! La letra '" << letra << "' esta en la palabra." << endl;
        } else {
            cout << "La letra '" << letra << "' no esta en la palabra." << endl;
            intentosRestantes--; // Reduce un intento si falló
        }
    }

    // Resultado del juego
    if (adivinada == palabra) {
        cout << "\n¡Felicidades! Has adivinado la palabra: " << palabra << endl;
    } else {
        mostrarAhorcado(0); // Muestra el ahorcado completo
        cout << "\n¡Has perdido! La palabra correcta era: " << palabra << endl;
    }
}
