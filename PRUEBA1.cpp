#include <iostream>
#include <mysql.h>
#include <cctype>
#include <vector>
#include <string>

//FUNCION MENU DE BIENVENIDA//
//void Alumnos(NodoPila *&, string &);
//FUNCION DEL MENU DE ALUMNOS//

void CargarRegistros();
void AgregarAlumno();
void BuscarAlumno();
void ModificarAlumno();
void ListarAlumno();
void EliminarAlumno();
void DeshacerUltimosCambios();
void RehacerCambios();
void ListarCambiosRealizados();
     
//FUNCION DEL MENU LISTAR//
void ListarGrado();
void ListarSeccion();

using namespace std;
using std::vector;

void InsertAlumno(string,string,string,string,string,string,string);

struct NodoPila{
	std::string origen;
	std::string alumno_nombre;
	std::string alumno_carnet;
	std::string alumno_grado;
	std::string alumno_correo;
	std::string alumno_fecha;
	std::string alumno_telefono;
	std::string alumno_direccion;
	NodoPila *sig;
};

void Alumnos(NodoPila *&, string);
void GuardarCambios(NodoPila *&, string); 

void agregarPila(NodoPila *&pila, string origen, string nombre, string carnet,string grado, string correo,string fecha,string telefono,string direccion){
	NodoPila *nuevo_nodo = new NodoPila();
	nuevo_nodo->origen = origen;
	nuevo_nodo->alumno_nombre = nombre;
	nuevo_nodo->alumno_carnet = carnet;
	nuevo_nodo->alumno_grado = grado;
	nuevo_nodo->alumno_correo = correo;
	nuevo_nodo->alumno_fecha = fecha;
	nuevo_nodo->alumno_telefono = telefono;
	nuevo_nodo->alumno_direccion = direccion;
	nuevo_nodo->sig = pila;
	pila = nuevo_nodo;
	cout<<"\tElemento "<<origen<<" "<<nombre<<" "<<carnet<<" "<<grado<<" "<<" ha sido agregado a PILA correctamente";
}

void sacarPila(NodoPila *&pila, string &datos_estudiante){
	NodoPila *aux = pila;
	datos_estudiante = aux->origen.append(" ").append(aux->alumno_nombre).append(" ").append(aux->alumno_carnet).append(" ").append(aux->alumno_grado).append(" ").append(aux->alumno_correo).append(" ").append(aux->alumno_fecha).append(" ").append(aux->alumno_direccion).append(" ").append(aux->alumno_telefono).append(" ").append("\n\n");
	pila = aux->sig;
	delete aux;
}

void dividirCadena(string cadena_estudiante){

    string delimitador = " ";
    vector<string> obtener;

    size_t resultado = 0;
    while ((resultado = cadena_estudiante.find(delimitador)) != string::npos) {
        obtener.push_back(cadena_estudiante.substr(0, resultado));
        cadena_estudiante.erase(0, resultado + delimitador.length());
    }
    
    int limite = 8;
    string arrayEstudiante[limite];
    int contador = 0;
    for (const auto &str : obtener) {
    	
    	arrayEstudiante[contador] = str;
    	
		if(((str == "I")&&(contador > 0))||((str == "U")&&(contador > 0))||((str == "D")&&(contador > 0))){
			contador = 0;
		}
    	
		contador++;
    	
    }
    if((arrayEstudiante[0] == "I")){
		cout<<"Es es un insert";
		InsertAlumno(arrayEstudiante[1], arrayEstudiante[2], arrayEstudiante[3],arrayEstudiante[4],arrayEstudiante[5],arrayEstudiante[6],arrayEstudiante[7]);
		cout<<arrayEstudiante[1]<<" -- "<< arrayEstudiante[2]<<" -- "<< arrayEstudiante[3]<<" -- "<<arrayEstudiante[4]<<" -- "<<arrayEstudiante[5]<<" -- "<<arrayEstudiante[6]<<" -- "<<arrayEstudiante[7]<<endl;
		//cout << arrayEstudiante[1] <<  "  " << arrayEstudiante[3]  << endl;
	}else if((arrayEstudiante[0] == "D")){
		cout<<"Es es un Delete";
		//cout << arrayEstudiante[1] <<  "  " << arrayEstudiante[3]  << endl;
	}else if((arrayEstudiante[0] == "U")){
		cout<<"Es es un update";
		//cout << arrayEstudiante[1] <<  "  " << arrayEstudiante[3]  << endl;
	}
    //cout<< "posicion [0]: " << arrayEstudiante[0] << "  " << arrayEstudiante[1] <<  "  " << arrayEstudiante[3] << " \n";
}

char serverdb[] = "localhost";
char userdb[] = "Alan";
char passworddb[] = "4571";
char databasedb[] = "proyecto_3";


int main() {
	int opcion;
	char opc = 's';
	while (opc == 's')
	{
    system("cls");
	cout<<"------Bienvenido al menu de Escuela ingrese una opcion------"<<endl;
	cout<<"1. Registros Alumnos"<<endl;
	cout<<"2. Salir de Aplicacion"<<endl;
	cin>>opcion;
	if(opcion>2 && opcion <= 0)
	    {
            cout<<"\n \t\t\tOpcion invalida!!!"<<endl;
            cout<<"\n \t\t\tIngrese la Opcion Correcta: ";
            cin>>opcion;
    }
    NodoPila *pila = NULL;
	
	std::string origen = "I";

	switch(opcion)
	{
			
		case 1:
		
         		Alumnos(pila, origen);
        case 2:
        	cout<<"Desea salir de la aplicacion S/N ?\n"<<endl;
			cin>>opc;
			if (opc == 's'){
				return 0;
			}
			else	
        	{
        		return main();
			}
		}
	system("Pause()");
	}
	
}

void Alumnos(NodoPila *&pila, std::string origen){
	int opcion;
	char opc = 's';
	while (opc == 's')
	{
    system("cls");
	int opcion;
	cout<<"Ingrese una de las siguientes ocpiones"<<endl;
	cout<<"1-Cargar Registros"<<endl;
	cout<<"2-Agregar Alumno"<<endl; 
	cout<<"3-Buscar a un Alumno"<<endl;
	cout<<"4-Modificar los datos de un Alumno"<<endl;
	cout<<"5-Listar los Alumnos"<<endl;
	cout<<"6-Eliminar alumno"<<endl;
	cout<<"7-Deshacer ultimos cambios"<<endl;
	cout<<"8-Rehacer Cambios"<<endl;
	cout<<"9-Listar cambios realizados"<<endl;
	cout<<"10-Guardar cambios"<<endl;
	cout<<"11-Salir"<<endl;
	cin>>opcion;
switch (opcion)
	{
	
		case 1: 
         		CargarRegistros();
        break;
        case 2: 
         		AgregarAlumno();
        break;
        case 3: 
         		BuscarAlumno();
        break;
        case 4: 
         		ModificarAlumno();
		break;
        case 5: 
         		ListarAlumno();
        break;
        case 6: 
         		EliminarAlumno();
        break;
        case 7: 
         		DeshacerUltimosCambios();
        break;
        case 8: 
         		RehacerCambios();		
        break;
        case 9: 
         		ListarCambiosRealizados();
        break;
        case 10: 
         		GuardarCambios(pila, origen);
        break;
        case 11: 
         		cout<<"Desea Salir sin guardar cambios S/N ?\n"<<endl;
                fflush(stdin);
				cin>>opc;
		break;
		}
	system("Pause()");
	}
}
void CargarRegistros(){
}
//////////////////////AGREGAR ALUMNO///////////////////
void AgregarAlumno(){
	MYSQL* connection;
	long alumno_id;
	string alumno_nombre;
	string alumno_carnet;
	string alumno_grado;
	string alumno_correo;
	string alumno_fecha;
	string alumno_telefono;
	string alumno_direccion;
	string sql;
	string sql2;
	
	NodoPila *pila = NULL;
	std::string origen = "I";
	char respuesta;
	
	int result;
	const char* query;
	connection = mysql_init(0);
	if (connection)
	{
		cout<< "La libreria MySQL se ha iniciado correctamente"<<endl;
		connection = mysql_real_connect(connection,serverdb, userdb, passworddb,databasedb, 3306, NULL,0);
		if(connection)
	{
		cout<<"Conexion exitosa a la base de datos "<<endl;
	    fflush(stdin);
	    cout<<endl;
	    
	    do{
	    	
		cout << "Ingrese el carnet del alumno para su validacion: " << endl ;
		//getline(cin, alumno_carnet);
		cin>>alumno_carnet;
		
			do{

			MYSQL_ROW row;
			MYSQL_RES* data;
			/*if(alumno_carnet != ""){
				
			}else{
				
			}*/
			sql2 = "SELECT * FROM alumnos where alumno_carnet='" + alumno_carnet + "'";
			query = sql2.c_str();
			result = mysql_query(connection, query);
			if (result == 0)
			{
				cout << "Se han obtenido los datos del alumno" << endl;	
				cout<<endl;
				data = mysql_store_result(connection);
				int countColumns = mysql_num_fields(data);
				while(row = mysql_fetch_row(data))
				{
					for (int i = 7; i < countColumns; i++)
					{
						cout << "Id: " << row[0] << endl;
     					cout << "Nombre: " << row[1] << endl;      
      					cout << "Carnet: " << row[2] << endl;      
      					cout << "Grado: " << row[3] << endl;
      					cout << "Correo: " << row[4] << endl;
						cout << "Fecha de Nacimiento: " << row[5] << endl;
						cout << "Telefono: " << row[6] << endl;
						cout << "Direccion Domiciliar del Alumno: " << row[7] << endl;  
					}
					cout << endl;
					if (alumno_carnet == alumno_carnet)
    			{
    			cout<<"El Registro ya fue ingresado"<<endl;
    			}	
				}
			} 
			}
			while(alumno_carnet != alumno_carnet);
		
		
		cout<<"ingrese de nuevo el carnet del alumno:";
		
		getline(cin, alumno_carnet);
		cout<<endl;
		cout << "Ingrese el nombre del alumno: ";
		getline(cin, alumno_nombre);
		cout << "Ingrese el grado del alumno: ";
		getline(cin, alumno_grado);
		cout << "Ingrese el correo del alumno: ";
		getline(cin, alumno_correo);
		cout << "Ingrese la fecha de nacimiento del alumno: "; 
		getline(cin, alumno_fecha);
		cout << "Ingrese el telefono del alumno: "; 
		getline(cin, alumno_telefono);
		cout << "Ingrese la direccion domiciliar del alumno: "; 
		getline(cin, alumno_direccion);
		//Declaracion SQL
		agregarPila(pila, origen, alumno_nombre, alumno_carnet, alumno_grado, alumno_correo, alumno_fecha, alumno_telefono, alumno_direccion);
		
		cout<< "\nDesea agregar otro alumno a PILA (s/n)";
		cin>>respuesta;
			
	}while(tolower(respuesta) == 's');
	if(tolower(respuesta) == 'n'){
		Alumnos(pila, origen);
	}
	/*while(pila != NULL){
		sacarPila(pila, origen);
		cout<< "\n=================" << origen << endl;
		
		dividirCadena(origen);
	}
	
		/*
		sql = "INSERT INTO alumnos(alumno_nombre,alumno_carnet,alumno_grado,alumno_correo,alumno_fecha,alumno_telefono,alumno_direccion) VALUES ('" + alumno_nombre + "','" + alumno_carnet + "','" + alumno_grado + "','" + alumno_correo + "','" + alumno_fecha + "','" + alumno_telefono + "','" + alumno_direccion + "')";
		query = sql.c_str();
		result = mysql_query(connection, query);
		if(result == 0)
		{
			cout<<"Datos de alumno guardado"<<endl;
			cout<<endl;
		}	
		else
		{
			cout<<"no fue posible guardar dato de alumno"<<mysql_error(connection)<<endl;
		}		
		}
		else 
		{
			cout << "No fue posible conectarse a la base de datos: " << mysql_error(connection) << endl;
		}
	}
	else 
	{
		cout << "No es posible iniciar la biblioteca de MySQL" << endl;
	}*/
		}
	}
}
void InsertAlumno(string alumno_nombre,string alumno_carnet,string alumno_grado,string alumno_correo,string alumno_fecha,string alumno_telefono,string alumno_direccion){
	MYSQL* connection;
	string sql;
	int result;
	const char* query;
	connection = mysql_init(0);
	if (connection)
	{
		cout<< "La libreria MySQL se ha iniciado correctamente"<<endl;
		connection = mysql_real_connect(connection,serverdb, userdb, passworddb,databasedb, 3306, NULL,0);
		if(connection)
	{
		cout<<"Conexion exitosa a la base de datos "<<endl;
	    cout<<endl;
	    
		sql = "INSERT INTO alumnos(alumno_nombre,alumno_carnet,alumno_grado,alumno_correo,alumno_fecha,alumno_telefono,alumno_direccion) VALUES ('" + alumno_nombre + "','" + alumno_carnet + "','" + alumno_grado + "','" + alumno_correo + "','" + alumno_fecha + "','" + alumno_telefono + "','" + alumno_direccion + "')";
		query = sql.c_str();
		result = mysql_query(connection, query);
		if(result == 0)
		{
			cout<<"Datos de alumno guardado"<<endl;
			cout<<endl;
		}	
		else
		{
			cout<<"no fue posible guardar dato de alumno"<<mysql_error(connection)<<endl;
		}		
		}
		else 
		{
			cout << "No fue posible conectarse a la base de datos: " << mysql_error(connection) << endl;
		}
	}
	else 
	{
		cout << "No es posible iniciar la biblioteca de MySQL" << endl;
	}
}
////////////////////BUSCAR ALUMNO///////////////////////////////
void BuscarAlumno(){
	MYSQL* connection;
	long alumno_id;
	string alumno_nombre;
	string sql;
	int result;
	const char* query;
	connection = mysql_init(0);
	if (connection)
	{
		cout<< "La libreria MySQL se ha iniciado correctamente"<<endl;
		connection = mysql_real_connect(connection,serverdb, userdb, passworddb,databasedb, 3306, NULL,0);
		if(connection)
	{
		cout<<"Conexion exitosa a la base de datos "<<endl;
	    fflush(stdin);
	    cout<<endl;
		cout << "Ingrese el nombre del alumno a buscar: ";
		cin>>alumno_nombre; 
		//pendiente de obtener
			MYSQL_ROW row;
			MYSQL_RES* data;
			sql = "SELECT * FROM alumnos where alumno_nombre='" + alumno_nombre + "'";
			query = sql.c_str();
			result = mysql_query(connection, query);
			if (result == 0)
			{
				cout << "Se han obtenido los datos del alumno" << endl;	
				cout<<endl;
				data = mysql_store_result(connection);
				int countColumns = mysql_num_fields(data);
				while(row = mysql_fetch_row(data))
				{
					for (int i = 7; i < countColumns; i++)
					{
						cout << "Id: " << row[0] << endl;
     					cout << "Nombre: " << row[1] << endl;      
      					cout << "Carnet: " << row[2] << endl;      
      					cout << "Grado: " << row[3] << endl;
      					cout << "Correo: " << row[4] << endl;
						cout << "Fecha de Nacimiento: " << row[5] << endl;
						cout << "Direccion Domiciliar del Alumno: " << row[6] << endl;
						cout << "Telefono: " << row[7] << endl;  
					}
					cout << endl;
				}
			}
			else
			{
      		cout << "No se han obtenido los datos del alumno, aun no existe" << endl;
      		}
		}
		else
		{
			cout << "No fue posible conectarse a la base de datos: " << mysql_error(connection) << endl;
		}
	}
	else 
	{
		cout << "No es posible iniciar la biblioteca de MySQL" << endl;
	}
}

///////////////////MODIFICAR ALUMNO/////////////////////////////
void ModificarAlumno(){
	MYSQL* connection;
	string alumno_id;
	string alumno_nombre;
	string alumno_carnet;
	string alumno_grado;
	string alumno_correo;
	string alumno_fecha;
	string alumno_telefono;
	string alumno_direccion;
	string sql;
	string sql3;
	string modify;
	int result;
	MYSQL_RES* data;
	MYSQL_ROW row;
	const char* query;
	connection = mysql_init(0);
	if (connection)
	{
		cout<< "La libreria MySQL se ha iniciado correctamente"<<endl;
		connection = mysql_real_connect(connection,serverdb, userdb, passworddb,databasedb, 3306, NULL,0);
		if(connection)
	{	
			sql3 = "SELECT * FROM alumnos ";
			query = sql3.c_str();
			result = mysql_query(connection, query);
			if (result == 0) 
			{
				cout << "Se han obtenido los datos de alumnos" << endl;
				cout<<endl;	
				cout<<"Registros de Alumnos Ingresados para Modificar:"<<endl;
				cout<<endl;
				cout<<"Id"<<"\t"<<"Nombres "<<"\t"<<"Carnets"<<"\t"<<"Correos"<<"\t"<<"Fechas de Nacimiento"<<"\t\t"<<"Telefonos"<<"\t\t"<<"Direcciones"<<endl;
				data = mysql_store_result(connection);
				int countColumns = mysql_num_fields(data);
				while(row = mysql_fetch_row(data))
				{
					for (int i = 0; i < countColumns; i++)
					{
						cout << row[i] << "\t";
					}
					cout << endl;
				}
			}
			cout<<endl;	
		cout<<"Conexion exitosa a la base de datos "<<endl;
	    fflush(stdin);
	    cout<<endl;
		cout << "Ingrese el nombre del alumno a modificar: ";
		cin>>alumno_nombre; 
		cout << "Ingrese el id del alumno a modificar: ";
		cin>>alumno_id;
		//pendiente de obtener
			MYSQL_ROW row;
			MYSQL_RES* data;
			sql = "SELECT * FROM alumnos where alumno_nombre='" + alumno_nombre + "'";
			query = sql.c_str();
			result = mysql_query(connection, query);
			if (result == 0)
			{
				cout << "Se han obtenido los datos del alumno" << endl;	
				cout<<endl;
				data = mysql_store_result(connection);
				int countColumns = mysql_num_fields(data);
				while(row = mysql_fetch_row(data))
				{
					for (int i = 7; i < countColumns; i++)
					{
						cout << "Id: " << row[0] << endl;
     					cout << "Nombre: " << row[1] << endl;      
      					cout << "Carnet: " << row[2] << endl;      
      					cout << "Grado: " << row[3] << endl;
      					cout << "Correo: " << row[4] << endl;
						cout << "Fecha de Nacimiento: " << row[5] << endl;
						cout << "Direccion Domiciliar del Alumno: " << row[6] << endl;
						cout << "Telefono: " << row[7] << endl;   
					}
					cout << endl;
				}
			}
			fflush(stdin);
	    	cout<<endl;
			cout << "Ingrese el nuevo nombre del alumno: ";
			getline(cin, alumno_nombre); 
			cout << "Ingrese el nuevo carnet del alumno: ";
			getline(cin, alumno_carnet);
			cout << "Ingrese el nuevo grado del alumno: ";
			getline(cin, alumno_grado);
			cout << "Ingrese el nuevo correo del alumno: ";
			getline(cin, alumno_correo);
			cout << "Ingrese la nueva fecha de nacimiento del alumno: "; 
			getline(cin, alumno_fecha);
			cout << "Ingrese el nuevo telefono del alumno: "; 
			getline(cin, alumno_telefono);
			cout << "Ingrese la nueva direccion domiciliar del alumno: "; 
			getline(cin, alumno_fecha);
			modify = "UPDATE alumnos SET alumno_nombre='" + alumno_nombre + "',alumno_carnet='" + alumno_carnet + "',alumno_grado='" + alumno_grado + "',alumno_correo='" + alumno_correo + "',alumno_fecha='" + alumno_fecha + "',alumno_direccion='" + alumno_direccion + "' WHERE alumno_id='" + alumno_id + "'";
			query = modify.c_str();
			result = mysql_query(connection, query);
			if(result == 0)
		{
			fflush(stdin);
	    	cout<<endl;
			cout<<"Datos de alumno actualizado"<<endl;
			cout<<"Nuevo nombre del alumno:"<< alumno_nombre<<endl;
			cout<<"Nuevo carnet del alumno:"<< alumno_carnet<<endl;
			cout<<"Nuevo grado del alumno:"<< alumno_grado<<endl;
			cout<<"Nuevo correo del alumno:"<< alumno_correo<<endl;
			cout<<"Nueva fecha de nacimiento del alumno:"<< alumno_fecha<<endl;
			cout<<"Nuevo telefono del alumno:"<< alumno_telefono<<endl;
			cout<<"Nueva direccion domiciliar del alumno:"<< alumno_direccion<<endl;
			cout<<endl;
		}	
			else
			{
      		cout << "No se han obtenido los datos del alumno, aun no existe" << endl;
      		}
		}
		else
		{
			cout << "No fue posible conectarse a la base de datos: " << mysql_error(connection) << endl;
		}
	}
	else 
	{
		cout << "No es posible iniciar la biblioteca de MySQL" << endl;
	}
}
/////////////////////////////LISTAR LOS ALUMNOS/////////////////////////////////
void ListarAlumno(){
}
/////////////////////////////ELIMINAR ALUMNO/////////////////////////////
void EliminarAlumno(){
	MYSQL* connection;
	string alumno_id;
	string alumno_nombre;
	int result;
	string sql2;
	string sql3;
	string sql4;
	string delete1;
	string delete3;
	const char* query;
	MYSQL_ROW row;
	MYSQL_RES* res;
	MYSQL_RES* data;
	connection = mysql_init(0);
	if (connection)
	{
		cout<< "La libreria MySQL se ha iniciado correctamente"<<endl;
		connection = mysql_real_connect(connection,serverdb, userdb, passworddb,databasedb, 3306, NULL,0);
		if(connection)
	{
			
			sql3 = "SELECT * FROM alumnos ";
			query = sql3.c_str();
			result = mysql_query(connection, query);
			if (result == 0) 
			{
				cout << "Se han obtenido los datos del alumno" << endl;
				cout<<endl;	
				cout<<"Registros de Alumnos Ingresados para Eliminar:"<<endl;
				cout<<"Id"<<"\t"<<"Nombres "<<"\t"<<"Carnets"<<"\t"<<"Correos"<<"\t"<<"Fechas de Nacimiento"<<"\t\t"<<"Telefonos"<<"\t\t"<<"Direcciones"<<endl;
				cout<<endl;
				data = mysql_store_result(connection);
				int countColumns = mysql_num_fields(data);
				while(row = mysql_fetch_row(data))
				{
					for (int i = 0; i < countColumns; i++)
					{
						cout << row[i] << "\t";
     				    
					}
					cout << endl;
				}
			}
	cout<<"Conexion exitosa a la base de datos "<<endl;
	cout<<endl;
	cout<<"Ingrese el nombre del Alumno a Eliminar:";
	cin>>alumno_nombre;
	cout<<"Ingrese el id del Alumno a Borrar:";
	cin>>alumno_id;
	
	sql2 = "SELECT * FROM alumnos WHERE alumno_nombre = '"+ alumno_nombre +"' ";
	string query1 = sql2.c_str();
	const char* q1 = query1.c_str();
	mysql_query(connection, q1);
	res = mysql_store_result(connection);
	int count1 = mysql_num_fields(res);
	my_ulonglong i = mysql_num_rows(res);
	
	sql4 = "SELECT * FROM alumnos WHERE alumno_id = '"+ alumno_id +"' ";
	string query2 = sql4.c_str();
	const char* q2 = query2.c_str();
	mysql_query(connection, q2);
	res = mysql_store_result(connection);
	int count2 = mysql_num_fields(res);
	my_ulonglong x = mysql_num_rows(res);
		
	if(x>0)
	{
		delete3 = "DELETE FROM alumnos WHERE alumno_id = '"+ alumno_id +"' ";
		string query2 = delete3.c_str();
		const char* q2 = query2.c_str();	
		mysql_query(connection, q2);
		cout<< x <<" "<<alumno_id<<" "<<""<<endl;
		cout<<endl;		
	}
	else
	{
		cout<<"No se encontro el alumno"<<endl;
	}
	if(i>0)
	{
		delete1 = "DELETE FROM alumnos WHERE alumno_nombre = '"+ alumno_nombre +"' ","aleter table alumnos auto_increment ='"+ alumno_id +"' ";;
		string query1 = delete1.c_str();
		const char* q1 = query1.c_str();	
		mysql_query(connection, q1);
		cout<< i <<" "<<alumno_nombre<<" "<<"Alumno encontrado y Borrado"<<endl;
		cout<<endl;			
	}
	if(i > 0){

	delete1 = "alter table alumnos auto_increment=1";
	}
	else
	{
		cout<<"No se encontro el alumno"<<endl;
	}
	}
		else 
		{
			cout << "No fue posible conectarse a la base de datos: " << mysql_error(connection) << endl;
		}
	}
	else 
	{
		cout << "No es posible iniciar la biblioteca de MySQL" << endl;
	}		
}
////////////////////////////DESHACER ULTIMOS CAMBIOS////////////////////////
void DeshacerUltimosCambios(){
}
///////////////////////////////REHACER CAMBIOS////////////////////////////
void RehacerCambios(){
}
///////////////////////////////LISTAR CAMBIOS REALIZADOS///////////////////////////////
void ListarCambiosRealizados(){
}
//////////////////////////////GUARDAR CAMBIOS////////////////////////////
void GuardarCambios(NodoPila *&pila, std::string origen){
	cout<< "\nholaaaaaaaaa" << origen << endl;
	while(pila != NULL){
		cout<< "\nholaaaaaaaaa" << origen << endl;
				

		sacarPila(pila, origen);
		
						cout<< "\n=================" << origen << endl;

		
		dividirCadena(origen);
	}
	/*NodoPila pila;
	string origen = "I";
	cout<<"El nombre de Alumno es:"<<pila.alumno_nombre<<endl;
	while(pila != NULL){
		sacarPila(pila, origen);
		
		dividirCadena(origen);
	}*/
}
/*///////////////////////LISTAR ALUMNO GRADO Y SECCION//////////////////
void Listaralumnogradoyseccion(){
	int opcion;
	char opc = 's';
	while (opc == 's')
	{
    system("cls");
	int opcion;
	cout<<"Ingrese una de las siguientes ocpiones"<<endl;
	cout<<"1-Listar Los Alumnos de un Grado"<<endl; 
	cout<<"2-Listar Los Alumnos de una Seccion"<<endl;
	cout<<"3-Regresar al menu"<<endl;
	cin>>opcion;
switch (opcion)
	{
	
		case 1: 
         		ListarGrado();
        break;
        case 2: 
         		ListarSeccion();
        break;
        case 3: 
         		cout<<"Desea regresar al menu de listar alumnos S/N ?\n"<<endl;
                fflush(stdin);
				cin>>opc;
		break;
		}
	}
}
////////////////////////LISTAR GRADO//////////////////////////
void ListarGrado(){
	MYSQL* connection;
	long asignado_id;
	string grado_nombre;
	string sql;
	string sql2;
	int result;
	MYSQL_ROW row;
	MYSQL_RES* data;
	const char* query;
	connection = mysql_init(0);
	if (connection)
	{
		cout<< "La libreria MySQL se ha iniciado correctamente"<<endl;
		connection = mysql_real_connect(connection,serverdb, userdb, passworddb,databasedb, 3306, NULL,0);
		if(connection)
	{
		cout<<endl;
			sql2 = "SELECT * FROM grado ";
			query = sql2.c_str();
			result = mysql_query(connection, query);
			if (result == 0) 
			{
				cout<<"Registros de Grados Ingresados para Listar:"<<endl;
				cout<<"Id"<<"\t"<<"Nombres"<<" "<<"Codigo"<<endl;
				data = mysql_store_result(connection);
				int countColumns = mysql_num_fields(data);
				while(row = mysql_fetch_row(data))
				{
					for (int i = 0; i < countColumns; i++)
					{
						cout << row[i] << "\t";
     				    
					}
					cout << endl;
				}
			}
			cout<<endl;
		cout<<"Conexion exitosa a la base de datos "<<endl;
	    fflush(stdin);
	    cout<<endl;
		cout << "Ingrese el nombre del grado para Listar a los alumnos asignados: ";
		cin>>grado_nombre; 
		//pendiente de obtener
			MYSQL_ROW row;
			MYSQL_RES* data;
			sql = "SELECT grado.grado_nombre, alumno.alumno_nombre, alumno.alumno_clave , alumno.alumno_correo , alumno.alumno_promedio FROM asignado inner join alumno on asignado.alumno_id = alumno.alumno_id  inner join grado on asignado.grado_id = grado.grado_id where grado.grado_nombre = '" + grado_nombre + "'";
			query = sql.c_str();
			result = mysql_query(connection, query);
			if (result == 0)
			{
				cout << "Se han obtenido los alumnos asignados al grado"<<" "<<grado_nombre<< endl;	
				cout<<endl;
				cout<<"Grado"<<"\t\t"<<"Nombres de Alumnos"<<"\t"<<"Clave"<<"\t\t"<<"Correo"<<"\t\t\t"<<"Promedio nota"<<endl;
				data = mysql_store_result(connection);
				int countColumns = mysql_num_fields(data);
				while(row = mysql_fetch_row(data))
				{
					for (int i = 0; i < countColumns; i++)
					{
						cout << row[i] <<"\t\t";
					}
					cout << endl;
				}
			}
			else
			{
      		cout << "No se han obtenido los datos del grado" << endl;
      		}
		}
		else
		{
			cout << "No fue posible conectarse a la base de datos: " << mysql_error(connection) << endl;
		}
	}
	else 
	{
		cout << "No es posible iniciar la biblioteca de MySQL" << endl;
	}
	cout<<endl;
	system("Pause()");
}
void ListarSeccion(){
	MYSQL* connection;
	long asignado_id;
	string seccion_nombre;
	string sql;
	string sql2;
	int result;
	MYSQL_ROW row;
	MYSQL_RES* data;
	const char* query;
	connection = mysql_init(0);
	if (connection)
	{
		cout<< "La libreria MySQL se ha iniciado correctamente"<<endl;
		cout<<endl;
		connection = mysql_real_connect(connection,serverdb, userdb, passworddb,databasedb, 3306, NULL,0);
		if(connection)
	{
		sql2 = "SELECT * FROM seccion ";
			query = sql2.c_str();
			result = mysql_query(connection, query);
			if (result == 0) 
			{
				cout<<"Registros de Seccion Ingresados para Asignar:"<<endl;
				cout<<"Id"<<"\t"<<"Nombres"<<endl;
				data = mysql_store_result(connection);
				int countColumns = mysql_num_fields(data);
				while(row = mysql_fetch_row(data))
				{
					for (int i = 0; i < countColumns; i++)
					{
						cout << row[i] << "\t";
     				    
					}
					cout << endl;
				}
			}
			cout<<endl;	
		cout<<"Conexion exitosa a la base de datos "<<endl;
	    fflush(stdin);
	    cout<<endl;
		cout << "Ingrese el nombre de la seccion para Listar a los alumnos asignados: ";
		cin>>seccion_nombre; 
		//pendiente de obtener
			MYSQL_ROW row;
			MYSQL_RES* data;
			sql = "SELECT seccion.seccion_nombre, alumno.alumno_nombre, alumno.alumno_clave , alumno.alumno_correo , alumno.alumno_promedio FROM asignado inner join alumno on asignado.alumno_id = alumno.alumno_id  inner join seccion on asignado.seccion_id = seccion.seccion_id where seccion.seccion_nombre = '" + seccion_nombre + "'";
			query = sql.c_str();
			result = mysql_query(connection, query);
			if (result == 0)
			{
				cout << "Se han obtenido los alumnos asignados a la seccion"<<" "<<seccion_nombre<< endl;	
				cout<<endl;
				cout<<"Seccion"<<"\t\t"<<"Nombres de Alumnos"<<"\t"<<"Clave"<<"\t\t"<<"Correo"<<"\t\t\t"<<"Promedio nota"<<endl;
				data = mysql_store_result(connection);
				int countColumns = mysql_num_fields(data);
				while(row = mysql_fetch_row(data))
				{
					for (int i = 0; i < countColumns; i++)
					{
						cout << row[i] <<"\t\t";
					}
					cout << endl;
				}
			}
			else
			{
      		cout << "No se han obtenido los datos de la seccion" << endl;
      		}
		}
		else
		{
			cout << "No fue posible conectarse a la base de datos: " << mysql_error(connection) << endl;
		}
	}
	else 
	{
		cout << "No es posible iniciar la biblioteca de MySQL" << endl;
	}
	cout << endl;
	system("Pause()");
}*/
