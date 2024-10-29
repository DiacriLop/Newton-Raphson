#include <stdio.h>
#include <math.h>

// Función 1: f(x) = x^3 - x - 1
double f1(double x) {
    return pow(x, 3) - x - 1;
}

double f1_prime(double x) {
    return 3 * pow(x, 2) - 1;
}

// Función 2: f(x) = sin(x) - x^2
double f2(double x) {
    return sin(x) - pow(x, 2);
}

double f2_prime(double x) {
    return cos(x) - 2 * x;
}

// Función 3: f(x) = ln(x) - 1 (solo para x > 0)
double f3(double x) {
    return log(x) - 1;
}

double f3_prime(double x) {
    return 1 / x;
}

// Método de Newton-Raphson
void newton_raphson(double (*f)(double), double (*f_prime)(double), double x0, double tol, int max_iter) {
    double x = x0;
    int iter = 0;
    
    // Iterar hasta que se alcance la tolerancia o el número máximo de iteraciones
    while (iter < max_iter) {
        double fx = f(x);
        double fpx = f_prime(x);
        
        // Comprobamos si la derivada es cero para evitar división por cero
        if (fabs(fpx) < 1e-6) {
            printf("La derivada es cero. No se puede continuar.\n");
            return;
        }
        
        // Actualización del valor de x
        double x_new = x - fx / fpx;
        
        printf("Iteración %d: x = %.6f, f(x) = %.6f\n", iter, x, fx);
        
        // Verificación de la tolerancia
        if (fabs(x_new - x) < tol) {
            printf("Convergencia alcanzada en %d iteraciones.\n", iter);
            printf("La raíz aproximada es: %.6f\n", x_new);
            return;
        }
        
        x = x_new;
        iter++;
    }
    
    printf("Se alcanzó el número máximo de iteraciones sin convergencia.\n");
}

int main() {
    int opcion;
    double x0;
    int max_iter;
    double tol = 1e-6; // Tolerancia fija

    // Menú de selección de función
    printf("Seleccione la función para resolver con el método de Newton-Raphson:\n");
    printf("1. f(x) = x^3 - x - 1\n");
    printf("2. f(x) = sin(x) - x^2\n");
    printf("3. f(x) = ln(x) - 1\n");
    printf("Ingrese su opción: ");
    scanf("%d", &opcion);
    
    // Ingresar el valor inicial y número máximo de iteraciones
    printf("Ingrese el valor inicial x0: ");
    scanf("%lf", &x0);
    printf("Ingrese el número máximo de iteraciones: ");
    scanf("%d", &max_iter);
    
    // Selección de la función según la opción del usuario
    switch (opcion) {
        case 1:
            newton_raphson(f1, f1_prime, x0, tol, max_iter);
            break;
        case 2:
            newton_raphson(f2, f2_prime, x0, tol, max_iter);
            break;
        case 3:
            // Verificar que el valor inicial sea mayor que 0 para logaritmo natural
            if (x0 <= 0) {
                printf("Error: el valor inicial para ln(x) debe ser mayor que 0.\n");
            } else {
                newton_raphson(f3, f3_prime, x0, tol, max_iter);
            }
            break;
        default:
            printf("Opción no válida.\n");
    }

    return 0;
}
