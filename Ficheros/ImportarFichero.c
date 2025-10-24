/*****************************************
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
 *****************************************/

#include "Ficheros.h"
#include <errno.h>
#define MAX_BUF 8192
void ImportarFichero(DISCO **Fichas,WINDOW *Wfichero,bool sumar)
{

    FILE *fichero;
    char ruta[50];
    char caracter;
    char **Lineas;
    int i;
    int contador;
    int numeroLineas = 0;
    char buffer[MAX_BUF];
        if(sumar==false)
        {
            if(!Estadisticas.NumeroFichas==0){
                VentanaError("Ya hay discos");
                return;
            }
            while (true) {
    touchwin(Wfichero);
    wrefresh(Wfichero);  // refresca la ventana antes de pedir texto

    nocbreak();
    echo();
    curs_set(1);  // muestra el cursor
    mvwscanw(Wfichero, 2, 22, "%255s", ruta);  // lee texto (seguro)
    cbreak();
    noecho();
    curs_set(0);

    // limpia línea por si el usuario reescribe
    wmove(Wfichero, 3, 0);
    wclrtoeol(Wfichero);
    wrefresh(Wfichero);

    if (ruta[0] != '\0') {  // si no está vacía
        break;
    }
}
            

            if ((fichero = fopen(ruta, "r")) == NULL) {
                char msg[50]= "Error 2 al abrir '%s'",ruta;
                VentanaError(msg);

            }else{
                for(contador = 0; fgets(buffer, MAX_BUF, fichero) != NULL; contador++);
                rewind(fichero);
                Lineas= malloc(contador * sizeof(char*));
                while(fgets(buffer, MAX_BUF, fichero) != NULL) {
            i = strlen(buffer);

            if(buffer == '\n') {
                buffer[i--] = 0;
                //Lineas[numeroLineas] = malloc(i);
                //srtrcy(Lineas[numeroLineas++], buffer); 
                Lineas[numeroLineas++] = strdup(buffer);
            }
        else {
            fprintf(stderr, "Buffer muy pequeño\n");
            exit(-1);
        }
    }

    fclose(fichero);
            }

        }
        else {
            if(Estadisticas.NumeroFichas==0){
                VentanaError("No hay fichas de disco");
                return;
            }
            touchwin(Wfichero);
            nocbreak();
            echo();
            curs_set(1);
            mvwscanw(Wfichero,1,22,"%d",&ruta);
            cbreak();
            noecho();
            curs_set(0);
        }

    int usados   = sumar ? Estadisticas.NumeroFichas : 0;
    int capacidad = sumar ? Estadisticas.MaxFichas : 0;

   
}
