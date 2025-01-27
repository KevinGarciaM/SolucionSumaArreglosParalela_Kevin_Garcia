// SolucionSumaArreglosParalela_Kevin_Garcia.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <omp.h>

#define N 500       //Define el tamaño de los arreglos como 1000 elementos.   
#define chunk 200   //Establece el tamaño de las "tareas" en que se divide el trabajo en paralelo.
#define mostrar 5   //Define cuántos elementos se mostrarán al imprimir los arreglos.

void imprimeArreglo(float* d);  

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";
    float a[N], b[N], c[N];     // Define a, b y c del tamaño de los arreglos
    int i;                      // Define i como integer

    for (i = 0; i < N; i++)     //Suma de los arreglos en paralelo utilizando OpenMP.
    {
        a[i] = i * 10;
        b[i] = (i + 3) * 3.7;
    }

    //shared(a, b, c, pedazos): Estas variables son compartidas entre todos los hilos. 
    // Todos los hilos tienen acceso a los arreglos a, b, c y al valor de pedazos.
    int pedazos = chunk;
    #pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)
    //schedule(static, pedazos): Indica cómo dividir el trabajo entre los hilos:
    //static: Asigna bloques de iteraciones de forma fija a los hilos.
    //pedazos : Define el tamaño del bloque asignado a cada hilo, que en este caso es de 100 iteraciones.

    // Cada hilo ejecuta un subconjunto de las iteraciones, calculando una porción del arreglo c. 
    // Si hay 4 hilos, con chunk = 100, el trabajo se dividirá en bloques de 100 iteraciones, y cada hilo procesará varios bloques.
    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    //Imprime los resultados en la consola
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);

}
//Esta función recibe un arreglo (d) y muestra los primeros mostrar elementos en la consola, 
// separados por -. Se usa para verificar los resultados de los cálculos.
void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
