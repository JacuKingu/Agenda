/*****************************
 Librer�as utilizadas
*****************************/
#include <iostream>					/*Flujo de entrada y salida de datos*/
#include <string.h>					/*Funciones de manejo de cadenas*/
#include <windows.h>				/*Permite usar comandos de Windows Console*/
#include <stdio.h>

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
void lectura();				/*Lista todos los contactos existentes*/

/*Relevante e importante*/
void eliminar();		/*Elimina un contacto seleccionado en la agenda*/

int VerificarContacto(struct Agenda Contactos[], string);	/*Verifica si el contacto especificado existe*/

/*
Esta funci?n es interesante, tiene como objetivo
cargar datos (contactos) en la agenda para pruebas
r?pidas en la ejcuci?n del programa.
*/
void CargarContactos(struct Agenda Contactos[]);
bool HayContactos(struct Agenda Contactos[]);		/*Verifica si hay contactos en la agenda*/

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
						lectura();
						}break;
				case 4:{
						eliminar();
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

void Insertar(struct Agenda Contactos[]){
	int x;
	int salir =0;						/*bandera para salir*/
	
	do{ 									/*Etiqueta de Men� para insertar contactos*/
		
		/*Se verifica si hay espacio en la agenda*/
		if (ContactosRegistrados < CANTIDAD){
			cout << "\n\tN?mero de contacto: " << (ContactosRegistrados + 1) << endl;
			cout << "\tNombre:   ";
			cin >>  Contactos[ContactosRegistrados].Nombre;
			
			/*Se verifica si el contacto que est? intentando insertar, existe en la agenda*/
			if (VerificarContacto(Contactos, Contactos[ContactosRegistrados].Nombre)){
				cout << "\n\tEl contacto \"" << Contactos[ContactosRegistrados].Nombre << "\" ya existe!" << endl;
				
				Contactos[ContactosRegistrados].Nombre = " ";
				
				/*Si existe se intenta ingresar otro*/
				do {
					cout << "\n\t?Desea agregar otro contacto?" << endl;
					cout << "\t(1) S?, (2) No: ";
					cin >> x;
					
				} while(x < 1 || x > 2);
				
				switch (x){
					case 1: 
						// volvemos a InsertarMenu
						break;
					case 2:
						Detenerse();
						break;
					default:
						cout << "Up's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
						Detenerse();
						break;
				}
			}
			
			cout << "\tTel?fono: ";									
			cin >>  Contactos[ContactosRegistrados].Telefono;	/*Agregando valor a atributo Telefono*/
			
			cout << "\tCelular:  ";
			cin >>  Contactos[ContactosRegistrados].Celular;	/*Agregando valor a atributo Celular*/
			
			cout << "\tEmail:    ";
			cin >>  Contactos[ContactosRegistrados].Email;	/*Agregando valor a atributo Email*/
			
			cout << "\tFecha de Nacimiento (DD/MM/AAAA): ";
			cin >>  Contactos[ContactosRegistrados].Fecha.Nacimiento;	/*Agregando valor a atributo de Fecha*/
			
			ContactosRegistrados++;									/*Se incrementa la variable, indicando nuevo contacto*/
			
			cout << "\n\t?Agregado con ?xito!" << endl << endl;
			
		
			do {
				cout << "\n\t?Desea agregar otro contacto?" << endl;
				cout << "\t(1) S?, (2) No: ";
				cin >> x;
				
			} while(x < 1 || x > 2);
			
			switch (x){
				case 1: 
					// volvemos a InsertarMenu
					break;
				case 2:
					Detenerse();
					break;
				default:
					cout << "Up's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
					Detenerse();
					break;
			}
			
		} else {
			cout << "Lleg? al l?mite de contactos permitidos en la agenda." << endl << endl;
		}
	}
	while(salir == 0);

	Detenerse();
	return;
}

void Buscar(struct Agenda Contactos[]){
	int x;
	int salir = 0;                                      /*bandera para salir*/
	
	do{ 
		LimpiarPantalla();
	
		do {
			x = BuscarMenuCategoria();				/*Men� para buscar contactos por categor?as*/
		} while(x < 1 || x > 5);
		
		switch (x){
			case 1: 
				BuscarPorNombre(Contactos);			/*Buscar por nombre*/
				break;
			case 2:
				BuscarPorTelefono(Contactos);		/*Buscar por tel?fono*/
				break;
			case 3: 
				BuscarPorCelular(Contactos);		/*Buscar por celular*/
				break;
			case 4: 
				BuscarPorEmail(Contactos);			/*Buscar por email*/
				break;
			case 5:
				salir = Salir();
				break;
			default:
				cout << "Up's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
				system("PAUSE>NUL");
				break;
		}
	
	}
	while(salir == 1);

	Detenerse();
	return;
}

int BuscarMenuCategoria(){
	int x; 
	
	cout << endl << "\n\t\t     Realizar b�squeda por:" << endl << endl;
	cout << "(1)Nombre | (2)Tel?fono | (3)Celular | (4)Email | (5)Volver" << endl;
	cout << Regla << endl;
	
	cout << "Esperando respuesta: ";
	cin >> x;
	
	
	return x;
}

void BuscarPorNombre(struct Agenda Contactos[]){
	int i = 0; 					/*Iterador en el ciclo*/
	int c = 0;					/*Coincidencias*/
	
	string PorNombre;
	
	cout << "\n\tDigite el nombre: ";
	cin >>  PorNombre;
	cout << endl;
	
	/*Recorrer la cantidad de contactos registrados en la agenda*/
	for (i=0; i < ContactosRegistrados; i++){
		if ((Contactos[i].Nombre == PorNombre) ==0){				/*Si lo encuentra*/
			Imprimir(Contactos, i);							/*Muestra la informaci?n del contacto*/
			c++;
			break;
		}
	}
	
	if (c == 0)
		cout << "\n\tEl contacto \"" << PorNombre << "\" no se ha encontrado." << endl << endl;
	
	Detenerse();
	return;
}

void BuscarPorTelefono(struct Agenda Contactos[]){
	int i = 0; 
	int c = 0;
	
	string PorTelefono;
	
	cout << "\n\tDigite el n?mero de tel?fono: ";
	cin >>  PorTelefono;
	cout << endl;
	
	for (i = 0; i < ContactosRegistrados; i++){
		if ((Contactos[i].Telefono == PorTelefono) ==0){
			Imprimir(Contactos, i);
			c++;
			break;
		}
	}
	
	if (c == 0){
		cout << "\n\tEl contacto \"" << PorTelefono << "\" no se ha encontrado." << endl << endl;
	}
	
	Detenerse();
	return;
}

void BuscarPorCelular(struct Agenda Contactos[]){
	int i = 0; 
	int c = 0;					/*Coincidencias*/
	
	string PorCelular;
	
	cout << "\n\tDigite el n?mero de celular: ";
	cin >>  PorCelular;
	cout << endl;
	
	for (i = 0; i < ContactosRegistrados; i++){
		if ((Contactos[i].Celular == PorCelular) ==0){
			Imprimir(Contactos, i);
			c++;
			break;
		}
	}
	
	if (c == 0){
		cout << "\n\tEl contacto \"" << PorCelular << "\" no se ha encontrado." << endl << endl;
	}
	
	Detenerse();
	return;
}

void BuscarPorEmail(struct Agenda Contactos[]){
	int i = 0; 
	int c = 0;					/*Coincidencias*/
	
	string PorEmail;
	
	cout << "\n\tDigite el Email: ";
	cin >>  PorEmail;
	cout << endl;
	
	for (i = 0; i < ContactosRegistrados; i++){
		if ((Contactos[i].Email == PorEmail) ==0) {
			Imprimir(Contactos, i);
			c++;
			break;
		}
	}
	
	if (c == 0){
		cout << "\n\tEl contacto \"" << PorEmail << "\" no se ha encontrado." << endl << endl;
	}
	
	Detenerse();
	return;
}


void Listar(struct Agenda Contactos[]){
	int i = 0;									/*Iterador del ciclo*/
	int x = 0; 									/*N?mero de contacto*/
	int contactos_restantes = 0;				/*Contactos restantes*/
	
	/*Se recorren todos los contactos registrados*/
	for (; i < ContactosRegistrados; i++){
		
		/*Si se encuentran contactos registrados*/
		if (Contactos[i].Nombre != " "){
			if (i > 1){
				contactos_restantes = (ContactosRegistrados - x) - ContactosEliminados;
				Dormir(1);						/*Aplicar retraso de 1 segundo*/
				
				if (contactos_restantes > 1)
					cout << "\t-- A?n quedan " << contactos_restantes << " por visualizar --" << endl;
				else if (contactos_restantes == 1)
					cout << "\t-- S?lo queda " << contactos_restantes << " por visualizar --" << endl;
				
				Detenerse();
				cout << endl;
			}
			
			/*Impresi?n de todos los datos de los contactos resultates*/
			cout << "\n\tN?mero de contacto: " << (x+1) << endl;
			cout << "\t\tNombre:   " << Contactos[i].Nombre << endl;
			cout << "\t\tTel?fono: " << Contactos[i].Telefono << endl;
			cout << "\t\tCelular:  " << Contactos[i].Celular << endl;
			cout << "\t\tEmail:    " << Contactos[i].Email << endl;
			cout << "\t\tFecha N.: " << Contactos[i].Fecha.Nacimiento << endl << endl;
			
			x++;			/*Incremento de la variable de n?mero de contacto*/
		}
	}
	
	cout << "\t <-- Regresar" << endl;
	Detenerse();
	return;
}
void Imprimir(struct Agenda Contactos[], int posicion){
	int x;
	
	/*Imprime el contacto que est? en una posici?n espec?fica de la agenda*/
	cout << "\n\t\tNombre:   " << Contactos[posicion].Nombre << endl;
	cout << "\t\tTel�fono: " << Contactos[posicion].Telefono << endl;
	cout << "\t\tCelular:  " << Contactos[posicion].Celular << endl;
	cout << "\t\tEmail:    " << Contactos[posicion].Email << endl;
	cout << "\t\tFecha N.: " << Contactos[posicion].Fecha.Nacimiento << endl << endl;
	
	/*CENTINELA: Opciones Actualizar y Elmiminar contacto*/
	do {
		cout << "\t  Opciones del contacto \"" << Contactos[posicion].Nombre << "\"" << endl;
		cout << "\t(1) Actualizar | (2) Eliminar | (3) Volver " << endl;
		cout << Regla << endl;
		
		cout << "Esperando respuesta: ";
		cin >> x;
		
		cout << endl;
		
	} while(x < 1 || x > 3);
	
	switch (x){
	case 1: 
		Actualizar(Contactos, posicion);				/*Actualiza el contacto seleccionado*/
		break;
	case 2:
		Eliminar(Contactos, posicion);					/*Elimina el contacto seleccionado*/
		break;
	case 3: 
		if (Salir() == 1)
			return;
	default:
		cout << "\n\tUp's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
		Detenerse();
		break;
	}
	
	return;
}

void Actualizar(struct Agenda Contactos[], int posicion){
	int x; 
	string Nombre, Telefono, Celular, Email;			/*Declaraci?n de variables que almacenar?n una copia*/
	int salir = 0;                                      /*bandera para salir*/
	
	do { 												//ActualizarOtroContacto: 
		
		Nombre 	= Contactos[posicion].Nombre;
		Telefono= Contactos[posicion].Telefono;
		Celular = Contactos[posicion].Celular;
		Email 	= Contactos[posicion].Email;
		
		/*Men� para seleccionar qu? atributos desean actualizar*/
		do {
			cout << "\n\t�Qu� dato le gustar�a actualizar de este contacto?" << endl;
			cout << "  (1)Nombre | (2)Tel�fono | (3)Celular (4)Email | (5)Ninguno" << endl;
			cout << Regla << endl;
			
			cout << "Esperando respuesta: ";
			cin >> x;
			
			cout << endl;
			
		} while(x < 1 || x > 5);
		
		/*Modificaci?n para los correspondientes atributos seleccionados*/
		switch (x){
			case 1: 
				cout << "\tDigite el nuevo nombre: ";
				cin >>  Contactos[posicion].Nombre;
				cout << "   Se ha actualizado de \"" << Nombre << "\" a " << "\"" << Contactos[posicion].Nombre << "\"" << endl; 
				break;
			case 2:
				cout << "\tDigite el nuevo tel?fono: ";
				cin >>  Contactos[posicion].Telefono;
				cout << "   Se ha actualizado de \"" << Telefono << "\" a " << "\"" << Contactos[posicion].Telefono << "\"" << endl; 
				break;
			case 3: 
				cout << "\tDigite el nuevo celular: ";
				cin >>  Contactos[posicion].Celular;
				cout << "   Se ha actualizado de \"" << Celular << "\" a " << "\"" << Contactos[posicion].Celular << "\"" << endl; 
				break;
			case 4: 
				cout << "\tDigite el nuevo email: ";
				cin >>  Contactos[posicion].Email;
				cout << "   Se ha actualizado de \"" << Email << "\" a " << "\"" << Contactos[posicion].Email << "\"" << endl; 
				break;
			case 5: 
				salir = Salir();
			default:
				cout << "\n\tUp's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
				Detenerse();
				break;
		}
	}
	while(salir == 0);
	
	return;
}

void Eliminar(struct Agenda Contactos[], int posicion){
	string Nombre;
	
	Nombre = Contactos[posicion].Nombre;
	
	/*Despu?s de ejecutar la centinela, se resetean los valores de esa posici?n
	  y no se vuelven a tomar en cuenta. Este algoritmo est? trabajado para que 
	  no perjudique en ning?n momento en la ejecuci?n del programa.
	*/
	if (Salir() == 1){
		Contactos[posicion].Nombre 	= " ";
		Contactos[posicion].Telefono= "0";
		Contactos[posicion].Celular	= "0";
		Contactos[posicion].Email	= " ";
		ContactosEliminados++;
		
		cout << "\n?El ex-contacto \"" << Nombre <<  "\" ha sido eliminado con ?xito!\n\n";
	}
	
	return;
}

int VerificarContacto(struct Agenda Contactos[], string Nombre){
	int i = 0; 
	int c = 0;
	
	/*Verifica si existe un contacto en espec?fico*/
	for (; i < ContactosRegistrados; i++){
		if (Contactos[i].Nombre == Nombre){
			c++;
			break;
		}
	}
	
	if (c == 0)
		return false;
	
	return true;
}

void CargarContactos(struct Agenda Contactos[]){
	int x;
	
	/*Cargar datos por omisi?n para realizar pruebas r?pidas de las opciones
	  que presenta este programa sobre la gesti?n de contactos de la Agenda.
	*/
	do {
		LimpiarPantalla();
			
		cout << Regla << endl;
		cout << "|\tBienvenido a tu Agenda Electr?nica (Contactos)\t    |" << endl;
		cout << Regla << endl;
			
		cout << "(1) Cargar contactos previos | (2) Nueva agenda | (3) Salir |" << endl;
		cout << Regla << endl;
			
		cout << "Esperando respuesta: ";
		cin >> x;
		
			
	} while(x < 1 || x > 3);
		
	switch (x){
		case 1: 
			/*Primer contacto*/
			Contactos[ContactosRegistrados].Nombre 			= "Pedro Picapiedra";
			Contactos[ContactosRegistrados].Telefono 		= "+51 222111";
			Contactos[ContactosRegistrados].Celular 		= "+51 963852741";
			Contactos[ContactosRegistrados].Email 			= "pedropicapiedra@gmail.com";
			Contactos[ContactosRegistrados].Fecha.Nacimiento= "16/12/1986";
			ContactosRegistrados++;
			
			/*Segundo contacto*/
			Contactos[ContactosRegistrados].Nombre 			= "Pablo Marmol";
			Contactos[ContactosRegistrados].Telefono 		= "+51 221133";
			Contactos[ContactosRegistrados].Celular 		= "+51 987654321";
			Contactos[ContactosRegistrados].Email 			= "pablomarmol@gmail.com";
			Contactos[ContactosRegistrados].Fecha.Nacimiento= "22/08/1993";
			ContactosRegistrados++;
			
			/*Tercer contacto*/
			Contactos[ContactosRegistrados].Nombre 			= "Vilma Grava";
			Contactos[ContactosRegistrados].Telefono 		= "+51 223311";
			Contactos[ContactosRegistrados].Celular 		= "+51 951874236";
			Contactos[ContactosRegistrados].Email 			= "vilmagrava@gmail.com";
			Contactos[ContactosRegistrados].Fecha.Nacimiento= "06/04/1996";
			ContactosRegistrados++;
			
			/*Cuarto contacto*/
			Contactos[ContactosRegistrados].Nombre 			= "Betty Caliza";
			Contactos[ContactosRegistrados].Telefono 		= "+51 224433";
			Contactos[ContactosRegistrados].Celular 		= "+51 951632478";
			Contactos[ContactosRegistrados].Email 			= "vilmacaliza@gmail.com";
			Contactos[ContactosRegistrados].Fecha.Nacimiento= "10/07/1999";
			ContactosRegistrados++;
			break;
		case 2:
			return;
		case 3: 
			if (Salir() == 1)
				return;
		default:
			cout << "\n\tUp's, ha ocurrido algo inesperado, presione una tecla para continuar!." << endl;
			Detenerse();
			break;
	}
	
	return;
}

bool HayContactos(struct Agenda Contactos[]){
	int i = 0; 					/*Iterador*/
	int c = 0;					/*Coincidencias*/
	
	/*Verifica si hay contactos disponibles*/
	for (; i < CANTIDAD; i++)
		if (Contactos[i].Nombre != " ")
			c++;
	
	if (c > 0)
		return false; //Est� vaci�
	
	return true;
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

