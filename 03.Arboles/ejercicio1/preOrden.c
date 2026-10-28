#include <stdio.h>
#include <stdlib.h>

/*
 * Barrido pre-orden de un árbol r-ario representado en un arreglo.
 * 
 * En representación por niveles (0-indexado):
 * Para un nodo en posición 'pos', sus hijos están en:
 * hijo_i = grado * pos + i  (con 1 <= i <= grado)
 */
void preOrden(int arbol[], int n, int grado, int pos)
{
    int i;
    int hijo;

    if (pos >= n)
        return;

    printf("%d\n", arbol[pos]);

    for (i = 1; i <= grado; i++)
    {
        hijo = grado * pos + i;
        if (hijo < n)
            preOrden(arbol, n, grado, hijo);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Uso: %s <grado> <archivo-origen>\n", argv[0]);
        return 1;
    }

    int grado = atoi(argv[1]);
    if (grado < 1)
    {
        fprintf(stderr, "Error: el grado debe ser mayor o igual a 1.\n");
        return 1;
    }

    FILE *f = fopen(argv[2], "r");
    if (!f)
    {
        fprintf(stderr, "Error: no se pudo abrir el archivo %s\n", argv[2]);
        return 1;
    }

    int capacidad = 1024;
    int n = 0;
    int *arbol = (int *)malloc(capacidad * sizeof(int));
    if (!arbol)
    {
        fclose(f);
        fprintf(stderr, "Error: fallo al asignar memoria.\n");
        return 1;
    }

    int valor;
    while (fscanf(f, "%d", &valor) == 1)
    {
        if (n >= capacidad)
        {
            capacidad *= 2;
            int *temp = (int *)realloc(arbol, capacidad * sizeof(int));
            if (!temp)
            {
                free(arbol);
                fclose(f);
                fprintf(stderr, "Error: fallo al reasignar memoria.\n");
                return 1;
            }
            arbol = temp;
        }
        arbol[n++] = valor;
    }
    fclose(f);

    if (n > 0)
    {
        preOrden(arbol, n, grado, 0);
    }

    free(arbol);
    return 0;
}
