/*****************************************
 * Nombre: ExportarFichero
 * Argumentos: DISCO **Fichas:   Puntero al array de discos
 *             WINDOW *Wfichero: Ventana para capturar el nombre del fichero
 * Descripción: Lee el nombre del fichero que contendrá los datos a exportar. Exporta los datos de la estructura
 *              de todos los discos en el fichero.
 * Reglas de uso: 
 * Código de Retorno:
 * Programador: JMSM (Sept-24)
 *****************************************/

#include "Ficheros.h"

#include <errno.h>
#define MAX_BUF 8192

void ExportarFichero(DISCO **Fichas, WINDOW *Wfichero)
{
    FILE *fichero;
    char ruta[50];
    int i;
    //pasamos a consola las posibles soluciones que puede ocurrir en el programa

    if(Estadisticas.NumeroFichas == 0) {
        VentanaError("No hay fichas de discos que exportar");
        return;
    }
    //refrescamos 
    touchwin(Wfichero);
    wrefresh(Wfichero);
    //pedimos la ruta
    while(true) {

        nocbreak();
        echo();
        curs_set(1);
        //pide la ruta en la posicion 2 22
        mvwscanw(Wfichero, 2, 22, "%49s", ruta);

        cbreak();
        noecho();
        curs_set(0);
        
        wmove(Wfichero, 3, 0);
        wclrtoeol(Wfichero);
        wrefresh(Wfichero);

        if(ruta[0] != '\0')
            break;
        //si no se ingreso una ruta correcta salta un error
        VentanaError("Introduzca un nombre de fichero");
        touchwin(Wfichero);
        wrefresh(Wfichero);
    }
    //ponemos mensajes a posibles errores
    if ((fichero = fopen(ruta, "w")) == NULL) {
        VentanaError("No se pudo crear el fichero");
        return;
    }
    //cabecera
    fprintf(fichero, "ID;Obra;ApellAutor;NomAutor;Tonalidad;Opus;Duracion\n");
    //recorre el fichero y escribe una a una
    for(i = 0; i < Estadisticas.NumeroFichas; i++) {
        fprintf(fichero,
                "%d;%s;%s;%s;%s;%s;%s\n",
                i + 1,
                (*Fichas)[i].Obra,
                (*Fichas)[i].ApellAutor,
                (*Fichas)[i].NomAutor ? (*Fichas)[i].NomAutor : "",
                (*Fichas)[i].Tonalidad ? (*Fichas)[i].Tonalidad : "",
                (*Fichas)[i].Opus ? (*Fichas)[i].Opus : "",
                (*Fichas)[i].Duracion ? (*Fichas)[i].Duracion : "");
    }

    fclose(fichero);
    //mensaje final
    char msg[100];
    sprintf(msg,"%d discos exportados correctamente",Estadisticas.NumeroFichas);
    VentanaError(msg);
}
