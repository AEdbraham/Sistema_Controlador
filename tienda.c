#include<stdio.h>

#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<time.h>

#include<termios.h>
#include<stdio_ext.h>


#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>

#include<stdio.h>
#include<stdlib.h>
#include<wait.h>
#include<unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>


#define ENTER 13
#define BKSP 8
#define SPACE 32
#define TAB 9

static struct termios old, current; 

struct item
{
	char nombreProducto[40],productcomp[40],c;
	int productid;
	int precio;
	int cantidad;
}st;

int salaEspera();
///Funciones para emular getch
char getch(void);
void initTermios(int echo);
void resetTermios(void);
char getch_(int echo);

//funcion de aplicacion
int pedirPass(char contra[]); //Pedir contrasena

//void //gotoxy(short x, short y);
void imprimirMargenes(){
	for(int i=0;i<100;i++){
			printf("\\");
	}
}
void bienvenida(void);
void login();
void menu();
void mostrar();
void insumos();
void total_factura();
void add_item();
void comprar();
int editar();
int editarEncontrado(struct item st);
int guardarEditado(struct item st,struct item original, FILE * archivo);
void clearBuffer() {
	char c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
}
void bienvenida(void)
{
	time_t t;
	time(&t);
	printf("                                                                                                         \n");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\xbd\t     Bienvenido a  \t \xbd\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\xbd\tSISTEMA ESCOMPRAS\t \xbd\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t          TU TIENDA DE CONFIANZA      \t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t      \"SISTEMAS OPERATIVOS-PROYECTO\"\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\n");
		printf("\t\t\t\t\t%s",ctime(&t));
	printf("\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\n");	
	printf("\n\t\t\tpresiona un boton para continuar.........\t\t\t\t\t\t\t\t\t\t\n");
	getchar();
}

void login()
{

    int a=0,i=0;
    char nombre[10],c=' '; 
    char contra[10];
    char usuario[10]="escom";
    char clave[10]="1234";
    do
{
	
    printf("\n /////////////////////|||||||||||||||||| LOGIN ||||||||||||||||||||||||||//////////////////  ");
    printf(" \n                        Usuario:-");
	scanf("%[^\n]", nombre); 
	__fpurge(stdin);
	printf(" \n                        Contrasenia:-");
	pedirPass(contra);
	//scanf("%s",&pword); 
		if(strcmp(nombre,"escom")==0 && strcmp(contra,"1234")==0)
	{
	printf("  \n\n\n\t       Las contrasenias han sido correctas. Esta dentro!!");
	printf("\n\n\t programa cargando, espere unos segundos... \n");
    for(i=0; i<5; i++)
    {
        printf(".");
        //sleep(500);
    }
	printf("\n\n\n\t\t\t\tPesione lo que sea para continuar...");
	clearBuffer();
	getchar();//holds the screen
	menu();
	break;
	}
	else
	{
		printf("\n        Error, sus credenciales son incorrectas");
		a++;
		
		getchar();//holds the screen
		
	}
}
	while(a<=2);
	if (a>2)
	{
		printf("\nha conolado el nombre mas de 4 veces. Adios!!!");
		
		getchar();
		exit(0);
		}
			
}


int pedirPass(char contra[])
{
    char c;
    int i=0;
    //printf("\nEnter pass: ");
    
    while(i<10)
    //pword <- contra ,   uname<- nombre,   user<- usuario,    pass<- clave,   code[10]<-codigo

	{
	    contra[i]=getch();
	    c=contra[i];

	    if(c !='\n')
	    printf("*");
        else
        break;
	    i++;
	}
	contra[i]='\0';
    return 0;
}

/* Read 1 character without echo */ 
char getch(void) 
{ 
    return getch_(0); 
}

/* Initialize new terminal i/o settings */ 
void initTermios(int echo)
{
     tcgetattr(0, &old); /* grab old terminal i/o settings */ 
     current = old; /* make new settings same as old settings */ 
     current.c_lflag &= ~ICANON; /* disable buffered i/o */ 
    if (echo) 
    { 
         current.c_lflag |= ECHO; /* set echo mode */ 
    } 
    else 
    { 
    current.c_lflag &= ~ECHO; /* set no echo mode */ 
    } 
    tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */ 
} 
/* Restore old terminal i/o settings */ 
void resetTermios(void) 
{ 
    tcsetattr(0, TCSANOW, &old); 
} 

/* Read 1 character - echo defines echo mode */ 

char getch_(int echo) 
{ 
    char ch; initTermios(echo); 
    ch = getchar(); 
    resetTermios(); 
    return ch; 
}

void menu(void)
{
while(1){
	int choice;
	main:
	printf("\n**************************************** Systema de compras en linea ***********************************************");
	printf("                                                                                          ");
	printf("                                                                                          ");
	printf("\n\t\t[1] Mostrar el almacen");
	printf("\n\t\t[2] comprar insumos");
	printf("\n\t\t[3] buscar insumos");
	printf("\n\t\t[4] aniadir nuevos elementos");
	printf("\n\t\t[5] editar los insumos");
	printf("\n\t\t[6] facturar");
    printf("\n\t\t[7] seccion de favoritos");
	printf("\n\t\t[>8] To salir");	
	
	printf("\n\n\t\tescribe tu respuesta: ");
	scanf("%i", &choice);
	
	switch(choice)	
	{
		case 1://mostrar almacen
			mostrar();
			break;
		case 2://comprar insumos
			comprar();
			break;
		case 3://buscar insumos
			insumos();
			break;
		case 4://adicionar insumos
			add_item();
			break;	
		case 5://editar insumos
			editar();
			break;
		case 6: //facturar
			total_factura();
			break;
        case 7:
			
			break;
		case 8:
		printf("saliendo");
		exit(0);
		break;
			
		
		default:
		printf("escribe solo numeros\n");
		getchar();
	}
	}
	
}
/* void gotoxy(short x, short y)/
{
	COORD pos ={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
} */

void mostrar()
{
	FILE *f;
	int i, q;
	if((f=fopen("productos.dat","r"))==NULL)
	{
	
		//gotoxy(10,3);
		printf("EN INEXISTENCIA");
		printf("\n\t\tPRESIONA ALGUNA TECLA PARA REGRESAR.");
		getchar();
		menu();


	}
	else
	{
	
		//gotoxy(0,5);
			for(i=0;i<100;i++)
		{
			printf("\xdb");
		}
		//gotoxy(5,6);
		printf("\nNombre \t");
		//gotoxy(25,6);
		printf("precio   \t");
		//gotoxy(40,6);
		printf("marca    \t");
		//gotoxy(60,6);
		printf("ID        \t");
		//gotoxy(80,6);
		printf("Canitidad\n");
		
		for(i=0;i<100;i++)
		{
			printf("\\");
		}
		q=8;
		while(fscanf(f,"%s %s %i %i %i\n", st.nombreProducto,st.productcomp, &st.precio, &st.productid,&st.cantidad)!=EOF)
		{
			printf("\n");
			//gotoxy(5,q);
			printf("%s \t",st.nombreProducto);
			//gotoxy(25,q);
			printf("%i \t",st.precio);
			//gotoxy(40,q);
			printf("%-15s \t",st.productcomp);
			//gotoxy(60,q);
			printf("%i \t",st.productid);
			//gotoxy(80,q);
			printf("%i",st.cantidad);
			printf("\n");
			q++;
		}
		printf("\n");
	imprimirMargenes();
	fclose(f);
	clearBuffer();
	printf("\npresiona algun boton para regresar al menu");
	getchar();
	menu();
}
}


void insumos(){
	char str[51];
	FILE *archivo;
	int bandera=0;
	archivo= fopen("productos.dat", "r");
	if(archivo == NULL)
		printf("Error de apertura del archivo.\n\n");
	rewind(archivo);
	printf("Ingresa el nombre del producto que desea buscar.\nProducto: ");
	clearBuffer();
	scanf("%50[^\n]", str);
	clearBuffer();
	for(int i=0;i<100;i++)
		printf("\\");
	while(fscanf(archivo,"%s %s %i %i %i\n", st.nombreProducto,st.productcomp, &st.precio,&st.productid,&st.cantidad)!=EOF){
		if(strcmp(str,st.nombreProducto)==0){
			//Descripción producto
			printf("\n");
			printf("Nombre: %s \t",st.nombreProducto);
			printf("Precio: %i \t",st.precio);
			printf("Marca: %-15s \t",st.productcomp);
			printf("ID: %i \t",st.productid);
			printf("Cantidad disponible: %i",st.cantidad);
			printf("\n");
			bandera = 1;
		}
	}
	if(bandera==0)
		printf("\nEl producto no se encuentra en el catalogo.");
	printf("\n");
	fclose(archivo);
	for(int i=0;i<100;i++)
		printf("\\");
}

void total_factura()
{ 
  float camtidad_total, monto, sub_total, descuento_total, total_impuesto, cantidad, presio, descuento, impuesto; 
 
  printf("\nIngresa la canditdad del producto vendido: "); 
  scanf ("%f", &cantidad) ; 
  printf("\n introduce el presio y kuanto kuesta: "); 
  scanf("%f", &presio); 
  printf("\n descuento?... :) : "); 
  scanf("%f", &descuento); 
  printf (" \n porcentaje de  impuesto: ") ; 
  scanf ("%f", &impuesto) ; 
  monto = cantidad * presio; 
  descuento_total = (monto* descuento)/100.0; 
  sub_total =monto - descuento_total; 
  total_impuesto= (sub_total*impuesto) /100.0; 
  camtidad_total =sub_total+ total_impuesto; 
  printf (" \n\n\n \xdb\xdb\xdb\xdb\xdb factura \xdb\xdb\xdb\xdb\xdb ") ; 
  printf("\ncantidad vendida: %f", cantidad); 
  printf("\nPrecio por unidad: %f", presio); 
  printf (" \n -------------") ; 
  printf ("\nmonto: %f", monto); 
  printf (" \n descuento: - %f", descuento_total) ; 
  printf ("\n descuentoed Total: %f", sub_total) ; 
  printf ("\n impuesto:+ %f", total_impuesto); 
  printf("\n-------------"); 
  printf ("\n monto total %f", camtidad_total); 
  getch(); 
  menu();
}

void add_item()
{
	int indice, valido;
	char c;
	int a=0;

	FILE *fp;
	

	do
	{
		
        
        //system("cls");
		printf("------detalles del producto----- \n");
		int ID;
		fp = fopen("productos.dat","a+");
		
		if((fp = fopen("productos.dat","a+"))!=NULL)//if condition to check file is NULL or not
		{
			I:
			printf("\nID del producto\t :");
			scanf("%i",&ID);
			while(fscanf(fp,"%s %s %i %i %i", st.nombreProducto, st.productcomp, &st.precio, &st.productid,&st.cantidad)!=EOF)
			{
				
				if(ID == st.productid)
				{
					printf("\n\tEL CODIGO DEL PRODUCTO YA EXISTE.\n");
					goto I;
				}
			}
			st.productid = ID;
		}
		else//CORRE SI EL ARCHIVO ESTA VACIO
		{
			printf("\nID del producto\t :");
			scanf("%i",&st.productid);
		}
		
	//add product name
		do
		{
		
			clearBuffer(); 
			printf("\nnombre del producto\t :");
			scanf("%[^\n]",st.nombreProducto);
			clearBuffer(); 
			st.nombreProducto[0]=toupper(st.nombreProducto[0]); 
			//iterando
			for (indice=0; indice<strlen(st.nombreProducto); ++indice)
			{	//revisa si el caracter es valido o no
				if(isalpha(st.nombreProducto[indice]))
					valido = 1;
				else
				{
					valido = 0;
					break;
				}
			}
			if (!valido)
			{
				printf("\n el nombre contiene un caracter invalido. presiona el 'Enter' again bro!");
				getch(); 
			
				
			}
		}while(!valido);	
		

		
			do
		{
			char productcomp[40];
			clearBuffer();
			printf("\nMarca del producto\t :");
			scanf("%[^\n]",st.productcomp); // 
			clearBuffer();
			st.productcomp[0]=toupper(st.productcomp[0]);
			
			for (indice=0; indice<strlen(st.productcomp); ++indice)
			{	
				if(isalpha(st.productcomp[indice]))
					valido = 1;
				else
				{
					valido = 0;
					break;
				}
			}
			if (!valido)
			{
				printf("\n Tienes un caracter que no es permitido, presiona enter de nuevo.");
				getch();
			
				
			}
		}while(!valido);
		
		//productid
		do
			{
				printf("\nprecio :");
				scanf("%i",&st.precio);
				if(st.precio<5 || st.precio>5000)
				{
					printf("\n\tEl limite es de [5-5000] pesos .");
				}
			}while(st.precio<10 || st.precio>5000);
			
				do
			{
				printf("\ncantidad ,no mas de 500 y mas de 1\t:");
				scanf("%i",&st.cantidad);
				if(st.cantidad<1 || st.cantidad>500)
				{
					printf("\n\tEnter cantidad[1-500] Enter.");
				}
			}while(st.cantidad<1 || st.cantidad>500);
	
	
		fp=fopen("productos.dat","a+");
		fprintf(fp,"\n%s %s %i %i %i", st.nombreProducto, st.productcomp,st.precio, st.productid,st.cantidad);
		fclose(fp);
		printf("\nPresiona enter para añadir y cualquier otra tecla para ir al menu");
		
	}
	while((c = getch()) =='\r'); 
	menu();
}

void comprar(){
	int str;
	FILE *archivo;
	int bandera=0;
	int cantidad;
	archivo= fopen("productos.dat", "r+");
	if(archivo == NULL)
		printf("Error de apertura del archivo.\n\n");
	rewind(archivo);
	printf("Ingresa el id del producto .\nProducto: ");
	clearBuffer();
	scanf("%d",&str);
	clearBuffer();
	printf("Ingrese la cantidad a comprar: ");
	scanf("%d",&cantidad);
	for(int i=0;i<100;i++)
		printf("\\");
	while(fscanf(archivo,"%s %s %i %i %i\n", st.nombreProducto,st.productcomp, &st.precio,&st.productid,&st.cantidad)!=EOF){
		if(str == st.productid){
			fclose(archivo);
			archivo = fopen("productos.dat","r+");
			fseek(archivo,st.productid,SEEK_SET);
			fprintf(archivo,"%s %s %i %i %i\n", st.nombreProducto, st.productcomp,st.precio, st.productid,st.cantidad-cantidad);
			break;
		}
	}
	fclose(archivo);
}


int editar()
{
	char str[51];
	struct item original = st;
	FILE *archivo;
	int bandera=0;
	archivo= fopen("productos.dat", "r");
	if(archivo == NULL)
		printf("Error de apertura del archivo.\n\n");
	rewind(archivo);
	printf("Ingresa el nombre del producto que desea buscar.\nProducto: ");
	clearBuffer();
	scanf("%50[^\n]", str);
	clearBuffer();
	for(int i=0;i<100;i++)
		printf("\\");
	while(fscanf(archivo,"%s %s %i %i %i\n", st.nombreProducto,st.productcomp, &st.precio,&st.productid,&st.cantidad)!=EOF){
		if(strcmp(str,st.nombreProducto)==0){
			//Descripción producto
			printf("\n");
			printf("Nombre: %s \t",st.nombreProducto);
			printf("Precio: %i \t",st.precio);
			printf("Marca: %-15s \t",st.productcomp);
			printf("ID: %i \t",st.productid);
			printf("Cantidad disponible: %i",st.cantidad);
			printf("\n");
			bandera = 1;

			editarEncontrado(st);
			printf("\nFuera de la funcion tenemos %s",st.nombreProducto);
		}
	}
	if(bandera==0)
		printf("\nEl producto no se encuentra en el catalogo.");
	printf("\n");
	fclose(archivo);
	for(int i=0;i<100;i++)
		printf("\\");
}

int editarEncontrado(struct item st)
{
	int indice, valido;
	char c;
	int a=0;
	int opc;

	printf("\n\nIngrese lo que dese editar: ");
	printf("\n1.Nombre \n2.Marca \n3.Precio \n4.Cantidad");
	scanf("%d",&opc);

	switch (opc)
	{
	case 1:
		do
		{
		
			clearBuffer(); 
			printf("\nNombre del producto\t :");
			scanf("%[^\n]",st.nombreProducto);
			clearBuffer(); 
			st.nombreProducto[0]=toupper(st.nombreProducto[0]); 
			//iterando
			for (indice=0; indice<strlen(st.nombreProducto); ++indice)
			{	//revisa si el caracter es valido o no
				if(isalpha(st.nombreProducto[indice]))
					valido = 1;
				else
				{
					valido = 0;
					break;
				}
			}
			if (!valido)
			{
				printf("\n el nombre contiene un caracter invalido. presiona el 'Enter' again bro!");
				getch(); 
			
				
			}
		}while(!valido);
		//printf("\nSe guardo %s",st.nombreProducto);	
		break;
	case 2:
			do
		{
			char productcomp[40];
			clearBuffer();
			printf("\nMarca del producto\t :");
			scanf("%[^\n]",st.productcomp); // 
			clearBuffer();
			st.productcomp[0]=toupper(st.productcomp[0]);
			
			for (indice=0; indice<strlen(st.productcomp); ++indice)
			{	
				if(isalpha(st.productcomp[indice]))
					valido = 1;
				else
				{
					valido = 0;
					break;
				}
			}
			if (!valido)
			{
				printf("\n Tienes un caracter que no es permitido, presiona enter de nuevo.");
				getch();
			
				
			}
		}while(!valido);
		break;
	case 3:
		do
			{
				printf("\nprecio :");
				scanf("%i",&st.precio);
				if(st.precio<5 || st.precio>5000)
				{
					printf("\n\tEl limite es de [5-5000] pesos .");
				}
			}while(st.precio<10 || st.precio>5000);
		break;
	case 4:
		do
			{
				printf("\ncantidad ,no mas de 500 y mas de 1\t:");
				scanf("%i",&st.cantidad);
				if(st.cantidad<1 || st.cantidad>500)
				{
					printf("\n\tEnter cantidad[1-500] Enter.");
				}
			}while(st.cantidad<1 || st.cantidad>500);
		break;
	
	default:
		editarEncontrado(st);
		break;
	}
}

int guardarEditado(struct item st,struct item original, FILE * archivo)
{
	printf("\n%s\n%s",st.nombreProducto,original.nombreProducto);
	int bandera =0;
	struct item aux;
	printf("\nGuardando datos. . .");
	
	rewind(archivo);
	
	/*
	while (fscanf(archivo,"%s %s %i %i %i\n", aux.nombreProducto,aux.productcomp, &aux.precio,&aux.productid,&aux.cantidad)!=EOF)
	{
		if(strcmp(original.nombreProducto,aux.nombreProducto)==0){
			printf("urra");
			bandera = 1;
			
		}

		
		
	}*/
	printf("\n");
	
}

int salaEspera()
{
    char mensaje[]="\nCliente esperando";
    int fd = open("salaDeEspera", O_WRONLY);
    if (fd == -1)
    {
        return 1;
    }

    if (write(fd,mensaje,sizeof(char)*18) == -1)
    {
        return 2;
    }
    printf("Hemos enviado al servidor el siguiente mensaje: %s\n",mensaje);
    close(fd);
    getchar();
}

int main(){
	salaEspera();
    bienvenida();
    login();


    return 0;
}




/*

			
		
			
				do
			{
				printf("\ncantidad ,no mas de 500 y mas de 1\t:");
				scanf("%i",&st.cantidad);
				if(st.cantidad<1 || st.cantidad>500)
				{
					printf("\n\tEnter cantidad[1-500] Enter.");
				}
			}while(st.cantidad<1 || st.cantidad>500);
*/