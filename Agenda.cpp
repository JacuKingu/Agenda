/*****************************
 Librer�as utilizadas
*****************************/
#include <iostream>					/*Flujo de entrada y salida de datos*/
#include <string.h>					/*Funciones de manejo de cadenas*/
#include <windows.h>				/*Permite usar comandos de Windows Console*/
#include <stdio.h>
#include<stdlib.h>
#include<fstream>					/*permite el trabajo con documentos de texto*/

#define CANTIDAD 500 				/*Cantidad m�xima de contactos: 500*/

using namespace std;

/*
	Variables globales que representan 
	contactos registrados, eliminados y
	una variable Regla que presentara una
	mejor vista en el programa.
*/
int ContactosRegistrados = 0;
int ContactosEliminados  = 0;
string Regla = "=============================================================";

/*****************************
Estructura de fecha y Agenda
*****************************/
/*Estructura de fecha de nacimiento*/
struct Cumple {
	string Nacimiento;
};

/*Estructura de Agenda, contiene todos los atributos*/
struct Agenda {
	int    Codigo;
	string Nombre;
	string Telefono;
	string Celular;
	string Email;
	Cumple Fecha;					/*Referencia a la estructura Cumple*/
	Agenda();  						/*Declaraci?n del constructor*/
};

/*****************************
	FUNCIONES PRINCIPALES 
*****************************/

int MenuPrimario();					//menú que muestra las obciones existentes

/*Relevante e importante*/
void Agregar(struct Agenda Contactos[]);			/*Inserta contactos en la agenda*/

/*Relevante e importante*/ //modulos de busqueda
void BuscarPorCodigo();//buscara contactos basado en el codigo que se proporcione
void BuscarPorCelular();//buscara contactos basado en el celular que se proporcione
void BuscarPorNombre();//buscara contactos basado en el nombre que se proporcione
void BuscarPorEmail();//buscara contactos basado en el email que se proporcione
void BuscarPorTelefono();//buscara contactos basado en el telefono que se proporcione

/*Relevante e importante*/
void Lectura();				/*Lista todos los contactos existentes*/

/*Relevante e importante*/
void Eliminar();		/*Elimina un contacto seleccionado en la agenda*/


int VerificarContactoPorCodigo(int g);// e asegura de que no se inserten dos codigos iguales
int VerificarContactoPorNumero(string s);//valida la existencia de un número para evitar duplicidad

/*****************************
	FUNCIONES SECUNDARIAS
*****************************/
void Detenerse();									/*Detiene la ejecuci?n, hasta que se presione una tecla*/
void LimpiarPantalla();								/*Limpia la pantalla para mostrar un nuevo Men�*/
void Dormir(int);									/*Aplica un retraso temporal*/
int Salir();										/*Centinela que pregunta por la salida de los Men�es*/

/*****************************
 DEFINICI?N DEL CONSTRUCTOR
-----------------------------
Inicializando la estructura.
*****************************/
Agenda::Agenda() {
	Codigo      = 0 ;
	Nombre 		= " ";								/*Para nombre, dejar un espacio en blanco*/
	Telefono 	= "0";								/*Para tel?fono, dejar 0 como contenido*/
	Celular 	= "0";								/*Para celular, dejar 0 como contenido*/
	Email 		= " ";								/*Para email, dejar un espacio en blanco*/
	Fecha.Nacimiento = " ";							/*Para fecha, dejar un espacio en blanco*/
}

/*****************************
	  FUNCIÓN PRINCIPAL
*****************************/
int main(int argc, char *argv[]) {
	setlocale(LC_CTYPE, "spanish");
	int x;											/*Almacena las opciones seleccionadas*/                                /*bandera para salir*/
	Agenda Contactos[CANTIDAD]; 					/*Definici?n de la variable Contactos con la cantidad*/
	
	do{											/*Etiqueta para retornar al Menu recursivamente*/
		
			do {
				x = MenuPrimario();					
			} while(x < 1 || x > 5);
			
			switch (x){								/*En este Men� se validan 2 opciones*/
				case 1: {
						Agregar(Contactos);			/*Men� para insertar datos*/
						}break;
				case 2:{
							int op;
							do{
								cout<<"Menú de selección de busqueda";
								cout<<"1)Busqueda por codigo.\n2)Busqueda por número de celular.\n3)Busqueda por nombre.\n4)Busqueda por Email.\n5)Busqueda por número de telefono.\n6)Salir.";
								do{//esta parte se puede reemplazar por un capturador de errores como try ya que aun con las restricciones planteadas daria error si se introdujera un string
									cout<<"Ingrese su elección: ";
									cin>>op;
									if (op!=1 && op!=2 && op!=3 && op!=4 && op!=5 && op!=6){
										cout<<"ERROR buelba a ingresar";
									}
								} while (op!=1 && op!=2 && op!=3 && op!=4 && op!=5 && op!=6);
								
							} while (op!=6);
							switch (op)
							{
							case 1:
								BuscarPorCodigo();//buscara contactos basado en el codigo que se proporcione
								break;
							case 2:
								BuscarPorCelular();//buscara contactos basado en el celular que se proporcione
								break;
							case 3:
								BuscarPorNombre();//buscara contactos basado en el nombre que se proporcione
								break;
							case 4:
								BuscarPorEmail();//buscara contactos basado en el email que se proporcione
								break;
							case 5:
								BuscarPorTelefono();//buscara contactos basado en el telefono que se proporcione
								break;
							case 6:
								cout<<"Saliendo del menú de busqueda....";
								break;
							}
							system("pause");
							system("cls"); 
						}break;
				case 3:{
						Lectura();
						}break;
				case 4:{
						Eliminar();
						}break;
				case 5:{/*Centinela para Salir*/
					cout<<"Saliendo del menú principal";
						}break;
				default:
					cout << "Up's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
					system("PAUSE>NUL");
					break;
			}
	}
	while (x!=5);						/*Se retorna al Men� principal en caso de que no haya seleccionado Salir*/
	
	return 0;
}

int MenuPrimario(){
	int x;
	
	cout << Regla << endl;
	cout << "|\tBienvenido a tu Agenda Electr?nica (Contactos)\t    |" << endl;
	cout << Regla << endl;
		
	cout << Regla << endl;
	cout << "| (1) Agregar Nuevo contacto   | (2) Obsiones de busqueda   |  (3) Listar   | (4) Eliminar contacto  |  (5) Salir   |" << endl;
	cout << Regla << endl;
	
	cout << "Esperando respuesta: ";
	cin >> x;
	return x;
}

//###################LECTURA O IMPRESIÓN DE DATOS #################
void Lectura(){//imprime la lista completa de contactos
    ifstream archivo;
    string texto;

    archivo.open("programacion.txt",ios::in);//abrimos en modo lectura

    if (archivo.fail())
    {
        cout<<"no se pudo abrir el archivo";
        exit(1);
    }
    while (!archivo.eof()){//miesntras no sea el final del archivo
        getline(archivo,texto);
        cout<<texto<<endl;
    }
    archivo.close();//cerramos el archivo
}

//##################ELIMINACIÓN DE CONTACTOS###############
void Eliminar(){
    ifstream Lec;
    string Nombre, NoAux, Telefono, Celular, Email, Fecha;
    int Codigo, CoAux;
    Lec.open("programacion.txt",ios::in);//abrimos en modo lectura
    ofstream Aux("auxiliar.txt",ios::out);//archivo para sobre escrivir los registros modificados
    if(Lec.is_open()){
        cout<<"Codigo de contacto que desea eliminar: ";
        cin>>CoAux;
        Lec>>Nombre;
        while (!Lec.eof()){
            Lec>>Telefono;
            Lec>>Celular;
            Lec>>Email;
            Lec>>Fecha;
            Lec>>Codigo;
            if (Codigo==CoAux)
            {
                cout<<"Se elimino ";
            }else{
                Aux<<Nombre<<" "<<Telefono<<" "<<Celular<<" "<<Email<<" "<<Fecha<<" "<<Codigo<<endl;
            }            
            Lec>>Nombre;
        }
        Lec.close();
        Aux.close();        
    }else
        cout<<"Error"<<endl;
    remove("programacion.txt");
    rename("auxiliar.txt","programacion.txt");
}

//################  busquedas #######################
void BuscarPorCodigo(){//busca a un contacto basado en un codigo
    ifstream Lec;
    Lec.open("programacion.txt",ios::in);
    string Nombre, Telefono, Celular, Email, Fecha;
    int Codigo, codaux;
    bool encontrado = false;
    cout<<"ingrese el codigo del contacto que desea buscar: ";
    cin>>codaux;
    Lec>>Nombre;
    while (!Lec.eof() && !encontrado){
        Lec>>Telefono;
        Lec>>Celular;
        Lec>>Email;
        Lec>>Fecha;
        Lec>>Codigo;
        if (codaux==Codigo){
            cout<<"\nNombre del contacto: "<<Nombre<<endl;
            cout<<"Telefono del contacto: "<<Telefono<<endl;
            cout<<"Celular del contacto: "<<Celular<<endl;
            cout<<"Email del contacto: "<<Email<<endl;
            cout<<"Fecha de nacimiento del contacto: "<<Fecha<<endl;
            cout<<"Codigo del contacto: "<<Codigo<<endl;
            encontrado==true;
        }
        Lec>>Nombre;
    }
    Lec.close();
}

void BuscarPorCelular(){
    ifstream Lec;
    Lec.open("programacion.txt",ios::in);
    string Nombre, Telefono, CelAux, Celular, Email, Fecha;
    int Codigo;
    bool encontrado = false;
    cout<<"ingrese el Celular del contacto que desea buscar: ";
    cin>>CelAux;
    Lec>>Nombre;
    while (!Lec.eof() && !encontrado){
        Lec>>Telefono;
        Lec>>Celular;
        Lec>>Email;
        Lec>>Fecha;
        Lec>>Codigo;
        if (CelAux==Celular){
            cout<<"\nNombre del contacto: "<<Nombre<<endl;
            cout<<"Telefono del contacto: "<<Telefono<<endl;
            cout<<"Celular del contacto: "<<Celular<<endl;
            cout<<"Email del contacto: "<<Email<<endl;
            cout<<"Fecha de nacimiento del contacto: "<<Fecha<<endl;
            cout<<"Codigo del contacto: "<<Codigo<<endl;
            encontrado==true;
        }
        Lec>>Nombre;
    }
    Lec.close();
}

void BuscarPorNombre(){//busca a contactos basado en el nombre que se ingrese
    ifstream Lec;
    Lec.open("programacion.txt",ios::in);
    string Nombre, NoAux, Telefono, Celular, Email, Fecha;
    int Codigo;
    bool encontrado = false;
    cout<<"ingrese el nombre del contacto que desea buscar: ";
    cin>>NoAux;
    Lec>>Nombre;
    while (!Lec.eof() && !encontrado){
        Lec>>Telefono;
        Lec>>Celular;
        Lec>>Email;
        Lec>>Fecha;
        Lec>>Codigo;
        if (NoAux==Nombre){
            cout<<"\nNombre del contacto: "<<Nombre<<endl;
            cout<<"Telefono del contacto: "<<Telefono<<endl;
            cout<<"Celular del contacto: "<<Celular<<endl;
            cout<<"Email del contacto: "<<Email<<endl;
            cout<<"Fecha de nacimiento del contacto: "<<Fecha<<endl;
            cout<<"Codigo del contacto: "<<Codigo<<endl;
            encontrado==true;
        }
        Lec>>Nombre;
    }
    Lec.close();
}

void BuscarPorEmail(){
    ifstream Lec;
    Lec.open("programacion.txt",ios::in);
    string Nombre, Telefono, Celular, Email, EmAux, Fecha;
    int Codigo;
    bool encontrado = false;
    cout<<"ingrese el Email del contacto que desea buscar: ";
    cin>>EmAux;
    Lec>>Nombre;
    while (!Lec.eof() && !encontrado){
        Lec>>Telefono;
        Lec>>Celular;
        Lec>>Email;
        Lec>>Fecha;
        Lec>>Codigo;
        if (EmAux==Email){
            cout<<"\nNombre del contacto: "<<Nombre<<endl;
            cout<<"Telefono del contacto: "<<Telefono<<endl;
            cout<<"Celular del contacto: "<<Celular<<endl;
            cout<<"Email del contacto: "<<Email<<endl;
            cout<<"Fecha de nacimiento del contacto: "<<Fecha<<endl;
            cout<<"Codigo del contacto: "<<Codigo<<endl;
            encontrado==true;
        }
        Lec>>Nombre;
    }
    Lec.close();
}

void BuscarPorTelefono(){
    ifstream Lec;
    Lec.open("programacion.txt",ios::in);
    string Nombre, TelAux, Telefono, Celular, Email, Fecha;
    int Codigo;
    bool encontrado = false;
    cout<<"ingrese el Telefono del contacto que desea buscar: ";
    cin>>TelAux;
    Lec>>Nombre;
    while (!Lec.eof() && !encontrado){
        Lec>>Telefono;
        Lec>>Celular;
        Lec>>Email;
        Lec>>Fecha;
        Lec>>Codigo;
        if (TelAux==Telefono){
            cout<<"\nNombre del contacto: "<<Nombre<<endl;
            cout<<"Telefono del contacto: "<<Telefono<<endl;
            cout<<"Celular del contacto: "<<Celular<<endl;
            cout<<"Email del contacto: "<<Email<<endl;
            cout<<"Fecha de nacimiento del contacto: "<<Fecha<<endl;
            cout<<"Codigo del contacto: "<<Codigo<<endl;
            encontrado==true;
        }
        Lec>>Nombre;
    }
    Lec.close();
}

int VerificarContactoPorCodigo(int g){
	ifstream leer("programacion.txt", ios::in);
    string Nombre, Telefono, Celular, Email, Fecha;;
    int Codigo;

    leer>>Nombre;
    while (!leer.eof())
    {
        leer>>Telefono;
        leer>>Celular;
        leer>>Email;
        leer>>Fecha;
        leer>>Codigo;
        if (Codigo==g){
            leer.close();
            return false;
        }
        break;
    }
    leer.close();
    return true;    
}

int VerificarContactoPorNumero(string s){//valida la existencia de un número para evitar duplicidad
    ifstream leer("programacion.txt", ios::in);
    string Nombre, Telefono, Celular, Email, Fecha;;
    int Codigo;

    leer>>Nombre;
    while (!leer.eof())//el bucle continuara hasta hasta que no se finalice con la lectura del doc
    {
        leer>>Telefono;
        leer>>Celular;
        if (Celular==s){
            leer.close();
            return false;
        }
        break;
        leer>>Email;
        leer>>Fecha;
        leer>>Codigo;
    }
    leer.close();
    return true;
}

void Agregar(struct Agenda Contactos[]){//agregara un nuevo contacto a la lista de contactos
    ofstream Escr;//variable iniciado como variable de escritura
    int i=0;
    Escr.open("programacion.txt",ios::app);//apertura del archivo en modo
    cout<<"ingrese nombre: ";
    cin>>Contactos[i].Nombre;//almacena nombre
    cout<<"ingrese Telefono: ";
    cin>>Contactos[i].Telefono;//almacena telefono
    cout<<"ingrese celular: ";
    cin>>Contactos[i].Celular;//almacena celular
    if (VerificarContactoPorNumero(Contactos[i].Celular)){

        cout<<"ingrese email: ";
        cin>>Contactos[i].Email;//almacena Email
        cout<<"ingrese Fecha de nacimiento: ";
        cin>>Contactos[i].Fecha.Nacimiento;//almacena Fecha de nacimiento
        cout<<"ingrese codigo de contacto: ";
        cin>>Contactos[i].Codigo;//almacena Codigo
        if(VerificarContactoPorCodigo(Contactos[i].Codigo)){//valida que el codigo insertado por el usuario no se repita
            Escr<<Contactos[i].Nombre<<" "<<Contactos[i].Telefono<<" "<<Contactos[i].Celular<<" "<<Contactos[i].Email<<" "<<Contactos[i].Fecha.Nacimiento<<" "<<Contactos[i].Codigo<<"\n";
        }
    }
    Escr.close();
}









void Detenerse(){
	cout << "\t�Presione una tecla para continuar!";
	system("PAUSE");								/*Pausar la aplicaci�n sin mensaje de salida*/
}

void LimpiarPantalla(){
	system("CLS");									/*Limpiar pantalla*/
}

void Dormir(int x){
	Sleep(x * 1000);							/*Dormir el programa*/
}

int Salir(){
	int x;
	
	/*Centinela general*/
	do {
		cout << "\n\tEstá seguro(a) de querer hacerlo?" << endl;
		cout << "\t(1) Sí, (2) No: ";
		cin >> x;
		
	} while(x < 1 || x > 2);
	switch (x)
	{
	case 1:
		return 1;
	case 2:
		return 2;
	}
}

