#include "fecha.hpp"
#include <iostream>
#include <stdexcept>
using namespace std;


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

Fecha obtener_fecha_v1()
{
  while (true)
    try {
      cout << "Introduzca una fecha, por favor: ";
      char linea[11];
      cin.getline(linea, 11);
      Fecha f(linea);
      return f;	   // Fecha correcta: salimos.
    } catch(Fecha::Invalida) {
      cerr << "\aError. Formato: \"dd/mm/aaaa\"" 
	   << "Inténtelo de nuevo.\n" << endl;
    }
}

Fecha obtener_fecha_v2()
{ // Otra alternativa. Tomamos la fecha de hoy
  cout << "Introduzca una fecha. Primero el día del mes: ";
  int d;
  cin >> d;
  cout << "Ahora el mes (numérico): ";
  int m;
  cin >> m;
  cout << "Y por último el año (4 cifras): ";
  int a;
  cin >> a;
  try {
    Fecha f(d, m, a);
    return f;
  } catch(Fecha::Invalida) {
    cerr << "\aError. Tomamos la fecha de «hoy»." << endl;
    return Fecha();
  }
}

int main()
{
//----------------- FECHA ------------------------------------
// Pruebas de constructores
  Fecha hoy {}, copia_hoy{hoy};	// Predeterminado, de copia
  Fecha mi_nacimiento{29, 12, 1958};
  Fecha mannana = ++hoy;	// pre-incremento
  Fecha ayer = --copia_hoy;	// pre-decremento
  
  // Nota: Hay que hacerlo en sentencias separadas.
  cout << "Hoy es " << --hoy;	// Conversión a const char*
  cout << ", mañana será " << mannana;
  cout << " y ayer fue " << ayer << endl;
  
  hoy += 7;			// Prueba de suma con asignación
  cout << "Dentro de una semana será: " << hoy << endl;
  hoy += 365 * 3;
  cout << "Dentro de 3 años y 1 semana será: " << hoy << endl;
  hoy -= 365 * 3 + 7;
  cout << "Volvemos a hoy: " << hoy << endl;
  
  // Pruebas de excepciones
  try {
    Fecha("20/1/2000");
    Fecha("31/2/2000");
  } catch(Fecha::Invalida e)
  {
    cerr << "EXCEPCIÓN: " << e.por_que() << endl;
  }
  
  cout << "Yo nací: " << mi_nacimiento <<  endl;
  
  cout << "Dentro de una semana será: " << hoy + 7 << endl;
  cout << "Hoy: " << hoy << endl;
  cout << "Hace 2 semanas fue: " << hoy - 14 << endl;
  
  cout << "El día después del 28 de febrero de este año es: ";
  Fecha f(28, 2);		// prueba de constructor de 2 parámetros
  cout << ++f << endl;
  cout << "Y el de después del 28 de febrero de 2000 fue: ";
  f = Fecha(28, 2, 2000);	// prueba de asignación
  cout << ++f << endl;
  cout << "Tras Año Viejo viene: ";
  Fecha av(31,12);
  cout << ++av << endl << "Y Año Viejo es: ";
  cout << --av << endl;
  
  // Prueba de constructor "cadena de caracteres"
  cout << "20/1/2000 está mejor dicho como " << Fecha("20/1/2000") << endl;
  
  /* Pruebas de excepciones  */
  
  Fecha f1 = obtener_fecha_v1(), f2 = obtener_fecha_v2();
  cout << "La 1ª fecha fue: \"" << f1;
  cout << "\", y la 2ª: \"" << f2 << "\"." << endl; 
 return 0; 
}
