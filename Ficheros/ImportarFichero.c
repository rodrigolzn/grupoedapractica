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
    //ponemos mensajes de posibles casos que se puedan producir al importar
    if (!sumar && Estadisticas.NumeroFichas != 0) {
        VentanaError("Ya hay discos cargados");
        return;
    }

    while (true) {
        //actualiza la ventana 
        touchwin(Wfichero);
        wrefresh(Wfichero);

        nocbreak();
        echo();
        curs_set(1);
        //lee lo que el usuario haya escrito en la posicion 2 22
        mvwscanw(Wfichero, 2, 22, "%49s", ruta);
        cbreak();
        noecho();
        curs_set(0);
        //sale del bucle si la ruta no esta vacia 
        if (ruta[0] != '\0')
            break;
    }
      
    gettimeofday(&inicio, NULL);

    //mensaje de error
    fichero = fopen(ruta, "r");
    if (!fichero) {
        VentanaError("Fichero no encontrado");
        return;
    }

  
    if (!sumar) {
        Estadisticas.NumeroFichas = 0;
        //establece un maximo de fichas que se pueden importar
        Estadisticas.MaxFichas = 3000;  
        //da memoria al programa
        *Fichas = malloc(Estadisticas.MaxFichas * sizeof(DISCO));
        if (!(*Fichas)) {
          
            VentanaError("Error reservando memoria");
            fclose(fichero);
            return;
        }
    }

  
    fgets(buffer, 1024, fichero);
    
    //lee linea a linea el fichero
    while (fgets(buffer, 1024, fichero))
    {
        //capacidad de memoria llena, muestra un error
        if (Estadisticas.NumeroFichas >= Estadisticas.MaxFichas) {
            VentanaError("Máximo de fichas alcanzado");
            break;
        }

        buffer[strcspn(buffer, "\n")] = 0;
        // Obtiene un puntero a la siguiente posición libre
        DISCO *d = &((*Fichas)[Estadisticas.NumeroFichas]);
        //divide la linea por ; que son los separadores del archivo csv
        token = strtok(buffer, ";");
        d->Obra = strdup(token ? token : "");  //guarda info 

        token = strtok(NULL, ";");
        d->ApellAutor = strdup(token ? token : "");//guarda info 

        token = strtok(NULL, ";");
        d->NomAutor = strdup(token ? token : "");//guarda info 

        token = strtok(NULL, ";");
        d->Tonalidad = strdup(token ? token : "");//guarda info 

        token = strtok(NULL, ";");
        d->Opus = strdup(token ? token : "");//guarda info 

        token = strtok(NULL, ";");
        d->Duracion = strdup(token ? token : "");//guarda info 
        //incrementa contador para que funcione el bucle
        Estadisticas.NumeroFichas++;
        numeroImportados++;
    }

    //cierra el archivo
    fclose(fichero);

    gettimeofday(&fin, NULL);
    //calcula la dif de tiempo
    Estadisticas.TiempoCarga = DifTiempo(inicio, fin);    
    //prepara un mensaje de la cantidad de discos que han sido importados
    char msg[80];
    snprintf(msg, sizeof(msg),"%d discos importados correctamente", numeroImportados);
    VentanaError(msg);
}