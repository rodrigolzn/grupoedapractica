/***************
 * Nombre: ImortarFichero
 * Argumentos: DISCO **Fichas:   Puntero al array de discos
 *             WINDOW *Wfichero: Ventana para capturar el nombre del fichero
 *             bool sumar:       Si es true las fichas de discos se añaden a las existentes,
 *                               si es false la lista de discos tiene que estar vacía.
 * Descripción: Lee el nombre del fichero que contendrá los datos a importar. Carga los discos del fichero
 *              en el array de discos, dimensionándolo si es necesario y descartando los que no tengan título o autor.
 * Reglas de uso: 
 * Código de Retorno:
 * Programador: JMSM (Sept-24)
 ***************/

#include "Ficheros.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUF 1024

void ImportarFichero(DISCO **Fichas, WINDOW *Wfichero, bool sumar)
{
    FILE *fichero = NULL;
    char ruta[50];
    char buffer[1024];
    char *token;
    int numeroImportados = 0;
    struct timeval inicio, fin;

    if (!sumar && Estadisticas.NumeroFichas != 0) {
        VentanaError("Ya hay discos cargados");
        return;
    }

    while (true) {
        touchwin(Wfichero);
        wrefresh(Wfichero);

        nocbreak();
        echo();
        curs_set(1);
        mvwscanw(Wfichero, 2, 22, "%49s", ruta);
        cbreak();
        noecho();
        curs_set(0);

        if (ruta[0] != '\0')
            break;
    }
      
    gettimeofday(&inicio, NULL);


    fichero = fopen(ruta, "r");
    if (!fichero) {
        VentanaError("Fichero no encontrado");
        return;
    }

  
    if (!sumar) {
        Estadisticas.NumeroFichas = 0;
        Estadisticas.MaxFichas = 3000;  
        *Fichas = malloc(Estadisticas.MaxFichas * sizeof(DISCO));
        if (!(*Fichas)) {
            VentanaError("Error reservando memoria");
            fclose(fichero);
            return;
        }
    }

  
    fgets(buffer, 1024, fichero);

    while (fgets(buffer, 1024, fichero))
    {
        if (Estadisticas.NumeroFichas >= Estadisticas.MaxFichas) {
            VentanaError("Máximo de fichas alcanzado");
            break;
        }

        buffer[strcspn(buffer, "\n")] = 0;

        DISCO *d = &((*Fichas)[Estadisticas.NumeroFichas]);

        token = strtok(buffer, ";");
        d->Obra = strdup(token ? token : "");

        token = strtok(NULL, ";");
        d->ApellAutor = strdup(token ? token : "");

        token = strtok(NULL, ";");
        d->NomAutor = strdup(token ? token : "");

        token = strtok(NULL, ";");
        d->Tonalidad = strdup(token ? token : "");

        token = strtok(NULL, ";");
        d->Opus = strdup(token ? token : "");

        token = strtok(NULL, ";");
        d->Duracion = strdup(token ? token : "");

        Estadisticas.NumeroFichas++;
        numeroImportados++;
    }


    fclose(fichero);

    gettimeofday(&fin, NULL);

    Estadisticas.TiempoCarga = DifTiempo(inicio, fin);    

    char msg[80];
    snprintf(msg, sizeof(msg),
             "%d discos importados correctamente", numeroImportados);
    VentanaError(msg);
}