#include<stdio.h>
#include<time.h>

#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>

#include<stdlib.h>
#include<unistd.h> //solo en linux
#include<wait.h>
#include<sys/types.h>

#define SHMSZ     27

#include <sys/shm.h>
#include <sys/ipc.h>


struct cliente
{
    char nombre[10]; 
    char contra[10];
    char usuario[10];
    char clave[10];
};

struct item
{
	char nombreProducto[40],productcomp[40],c;
	int productid;
	int precio;
	int cantidad;
};

struct compra
{
    int productoid;
    int clienteid;
};

int esperarCliente ();
int atenderCliente();
int recibirOpcion();


int main(int argc, char const *argv[])
{
    pid_t procesos [20];
    while (1)
    {
        esperarCliente();    
    }
    
    return 0;
}

 int esperarCliente()
{
     ///Variables
    char mensaje[18];
    int fd;
    pid_t procesoHijo;
    ///Tuberia para leer los mensajes del cliente
    if (mkfifo("salaDeEspera", 0777) == -1)
    {
       if (errno != EEXIST)
        {
            printf("Could not create fifo file\n");
            return 1;
        }
            
    }

    printf("Esperando cliente . . .\n");
    printf("Abriendo tuberias . . .\n");
    fd = open ("salaDeEspera", O_RDONLY);
    printf("Tuberias abiertas\n");
    close(fd);
    printf("Tuberias cerradas\n");
    ////fork
    procesoHijo = fork();
    if (procesoHijo == -1)  
    {
        printf("\nError al crear el proceso\n");
        exit(-1);
    }
    if (procesoHijo == 0)
    {
        printf("\nProceso numero: PId: %d, PPId: %d\n",getpid(),getppid());
        atenderCliente();
        exit(0);
    }
    //Bprintf("\n");
    //sleep(5);
    wait(NULL);

}

int atenderCliente()
{
    char opc = 1;
    printf("Atendiendo cliente . . .\n");
    recibirOpcion();
}

int recibirOpcion()
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key = 5678;

    /*
     * Create the segment.
     */
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        return(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        return(1);
    }

    /*
     * Now put some things into the memory for the
     * other process to read.
     */
    s = shm;

    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = '\0';

    /*
     * Finally, we wait until the other process 
     * changes the first character of our memory
     * to '*', indicating that it has read what 
     * we put there.
     */
    while (*shm != '*')
        sleep(1);

}

/**
 * @brief 
 * 
 * 
 *   //Tuberia para escribir mensajes al cliente
    if (mkfifo("altavozDelServidor", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("Could not create fifo file\n");
            return 1;
        }
            
    }
 * 
 *    //Hacer el proceso hijo
    int id = fork();
    int id2;
    //Neceesitamos que solo el proceso padre sea capaz de hacer procesos hijo.
    //Hacer los fifos

        //while (1)
        //{
                

            printf("Abriendo tuberias\n");
            fd = open("salaDeEspera", O_RDONLY);
            if (fd == -1)
            {
                return 1;
            }
            printf("Tuberia abierta\n");

            printf("Leyendo tuberias\n");
            if (read(fd, mensaje, sizeof(char)*18)==-1)
            {
                return 2;
            }
            
            close(fd);
            printf("Cliente esperando: %s\n",mensaje);

            if(id != 0)
            {
                id2=fork();
                if (id2 == 0 && id != 0)
                {
                    vendedor();

                }
                
            }
            else
            {
                wait(0);
            }
            wait(0);
        }
    //}
    
    
    
 * 
 */

