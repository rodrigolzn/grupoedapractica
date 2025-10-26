/*****************************************
 * Nombre: DescartarFichero
 * Argumentos: DISCO **Fichas:   Puntero al array de discos
 *             WINDOW *Wfichero: Ventana para mostrar el nombre del fichero
 * Descripción: Muestra los datos del fichero y los discos almacenados y descarta todos
 *              los discos en memoria y libera la memoria asignada.
 * Reglas de uso: 
 * Código de Retorno:
 * Programador: JMSM (Sept-24)
 *****************************************/

#include "Ficheros.h"
#include <errno.h>
#define MAX_BUF 8192

void DescartarFichero(DISCO **Fichas,WINDOW *Wfichero)
{
    FILE *fichero = NULL;
    char ruta[50];
    char buffer[MAX_BUF];
    char *token;
    char Tecla;
    int numeroLineas = 0;
    int i;

    //ponemos las posibles soluciones que se pueden producir en el programa
    if (Estadisticas.NumeroFichas == 0) {
        VentanaError("No hay discos para descartar");
        return;
    }
    
    Tecla=VentanaSN("Esta seguro de querer descartar todos los ficheros? (S/N)?");
    if (Tecla == 'S') {
        return;
    }

    // Libera el disco de memoria.
    free(Fichas);
    //mensaje final
    char msg[80];
    snprintf(msg, sizeof(msg),
             "Ficheros desccartados.");
    VentanaError(msg);
}