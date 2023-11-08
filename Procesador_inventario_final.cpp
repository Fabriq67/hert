#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <list>


using namespace std;

//funciones
int contarPalabrasSeparadasPorComa(string texto);
void dividirPalabra(string palabras); 
void imprimirManual();
list<vector<string>>listaDatosCSV;
vector<int>stocks;
//variables globales
string palabra1,palabra2;
int n=0;
int cantidadDepositos=0;
int cantidadPalabras;
int stock=0;
int cont_reg=0;
int contarArtDif=0;
int total_art;
int main(int argc, char *argv[])
{
//Pasando el parámetro del nombre del archivo
if(argc>1){

string NOMBRE_ARCHIVO;
//validacion del numero de argumentos para el csv
if(argc==3){
	NOMBRE_ARCHIVO=string(argv[2]);
}else{
	NOMBRE_ARCHIVO=string(argv[3]);
}

//leyendo el csv
ifstream archivo(NOMBRE_ARCHIVO);
    string linea;
    int cantidad_prueba;
    int deposito;
    string argumento;

    char delimitador = ',';
    // Leemos la primer línea para descartarla, pues es el encabezado
    getline(archivo, linea);
	cantidadPalabras = contarPalabrasSeparadasPorComa(linea);
	cantidadDepositos=cantidadPalabras-3;
	
	cantidadPalabras=cantidadPalabras-1;
	
	string temp;
    // Leemos todas las líneas
    
    while (getline(archivo, linea))
    {
	
        stringstream stream(linea); // Convertir la cadena a un stream
        
        // Extraer todos los valores de esa fila
        string grupo;
        	 getline(stream,grupo, delimitador);
   		
            vector<string> elementos;
            string elemento;
			
         	
			for(int i=0;i<cantidadPalabras;i++){
        
        		getline(stream, elemento,delimitador);
        			
        		if(elemento=="" || elemento=="\""){
        		
        			elementos.push_back("null");
        			
				}else{
				
					elementos.push_back(elemento);
					
					
				
				}
        		
				
			}   
		
		
          
            listaDatosCSV.push_back(elementos);
        	
      
		n=n+1;
	
    }
    total_art=n;
	
    archivo.close();



	
   int sumaTotal = 0;

	
    //Calcular el stock por cada artículo y llevándolo a la matriz
    for (const vector<string>& vector : listaDatosCSV) {
        int suma = 0;
        size_t tamano = vector.size();
        
        	
            for (int i=2; i < cantidadPalabras; ++i) {
            	if(vector[i]!="null")
                suma += stoi(vector[i]);
                
            }
            
            stocks.push_back(suma);
            
       
    }
   for (const int& elemento : stocks) {
		sumaTotal=sumaTotal+elemento;
        
    }
    

	
	//contar los articulos diferentes
	if(string(argv[1])=="-total_art_dif"){
	
	cout<<"El total de articulos diferentes son: "<<sumaTotal<<endl;
		
	}
	//cantidad de articulos totales
	
	if(string(argv[1])=="-total_art"){
		cout<<"La cantidad de articulos son: "<<total_art<<endl;
	}
	
	//listado aquellos artículos cuyo stock es igual o supera a n
	    
    if(string(argv[1])=="-max_Stock"){
	cantidad_prueba=stoi(string(argv[2]));
	
	
	for(int i=0;i<n;i++){
		auto itLista = listaDatosCSV.begin();
    	advance(itLista,i);
		if(stocks[i]>=cantidad_prueba){
				cout<<"Nombre Producto: "<<(*itLista)[1]<<" Stock: "<<stocks[i]<<endl;
			}
		  }
		}
		
	//listado de articulos con cantidad n o menos de stock		
	 if(string(argv[1])=="-min_stock"){
	 	
	 	dividirPalabra(string(argv[2]));
	 	cantidad_prueba=stoi(palabra1);
	 	if(palabra2==""){
		for(int i=0;i<n;i++){
		auto itLista = listaDatosCSV.begin();
    	advance(itLista,i);
		if(stocks[i]<=cantidad_prueba){
				cout<<"Nombre Producto: "<<(*itLista)[1]<<" Stock: "<<stocks[i]<<endl;
			}
		  }
		}	
		 //listado de articulos con cantidad n o menos por deposito
		 else{
		deposito=stoi(palabra2);
		deposito=deposito+1;
		cantidad_prueba=stoi(palabra1);
		int j=0;
		 for (const vector<string>& vector : listaDatosCSV) {
        	
            string segundoElemento = vector[deposito];
            if(segundoElemento=="null"){
            	cout<<"Nombre Producto: "<<vector[1]<<" Stock en el deposito "<<deposito-1<<":"<<0<<endl;
            	j++;
			}else if(stoi(segundoElemento)<=cantidad_prueba){
            	cout<<"Nombre Producto: "<<vector[1]<<" Stock en el deposito "<<deposito-1<<":"<<vector[deposito]<<endl;
            	j++;
			}
		
          }
		 }
	
	 }
	 
	 
	 //stock total del articulo ingresado como argumento
	 int j=0;
	 if(string(argv[1])=="-stock"){
	 	dividirPalabra(string(argv[2]));
		 argumento=palabra1;
			if(palabra2==""){
				 for (const vector<string>& vector : listaDatosCSV) {
        	
            		string nombreElemento = vector[1];
            		if(nombreElemento==argumento){
            			cout<<"Nombre Producto: "<<nombreElemento<<" Stock: "<<stocks[j]<<endl;
            				
					}
					j++;
				}
			}
			
		//stock total del articulo ingresado como argumento por deposito
		else{
			
			deposito=stoi(palabra2);
			argumento=palabra1;
			deposito=deposito+1;
			 for (const vector<string>& vector : listaDatosCSV) {
        	
            		string nombreElemento = vector[1];
            		if(nombreElemento==argumento){
            			if(vector[deposito]=="null"){
            					cout<<"Nombre Producto: "<<nombreElemento<<" En el deposito "<<deposito-1<<" Stock: "<<0<<endl;
            					
            						
						}else{
								cout<<"Nombre Producto: "<<nombreElemento<<" En el deposito "<<deposito-1<<" Stock: "<<vector[deposito]<<endl;
									
						}
            			
            				
					}
				j++;
				}
			
		}
		}
	 
	 
	
		
	}else{
		imprimirManual();
	}
}



//Funciones
int contarPalabrasSeparadasPorComa(string texto) {
    std::stringstream ss(texto);
    std::string palabra;
    int contador = 0;

    while (std::getline(ss, palabra, ',')) {
        contador++;
    }

    return contador;
}

void imprimirManual(){

	cout<<"Manual de uso:"<<endl;
	cout<<"Procesador_inventario.exe [Argumentos] inventariofisico.csv"<<endl;
	cout<<"Argumentos posibles:"<<endl;
    cout<<"-total_art_dif: Cantidad total de articulos diferentes."<<endl;
	cout<<"-total_art: Cantidad total de articulos."<<endl;
	cout<<"-min_stock [n]:Listado de articulos con cantidad n o menos de stock."<<endl;
	cout<<"-min_stock [n],[deposito]:Listado de articulos con cantidad n o menos de stock segun un deposito."<<endl;
	cout<<"-stock [nombre_articulo]: El stock total del articulo ingresado como argumento."<<endl;
	cout<<"-stock [nombre_articulo],[deposito]:El stock del articulo en un deposito."<<endl;
	cout<<"-max_Stock [n]: Listado de aquellos articulos cuyo stock es igual o supera el numero n."<<endl;

}

void dividirPalabra(string palabras){ 

    istringstream ss(palabras); 

    getline(ss,palabra1,','); 

    getline(ss,palabra2); 

} 
