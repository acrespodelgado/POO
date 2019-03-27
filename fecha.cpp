#include "fecha.hpp"
#include <iostream>
#include <ctime>

/*
* Constructores
*/

Fecha::Fecha(int dia, int mes, int anhio) : dia_{dia}, mes_{mes}, anno_{anhio} { construir_fecha(); }

Fecha::Fecha(const char *cadena) { construir_fecha_cadena(cadena); }

Fecha::Fecha(const Fecha &copia) : dia_{copia.dia()}, mes_{copia.mes()}, anno_{copia.anno()} { construir_fecha(); } 
//Se pasa por referencia para evitar el constructor de copia, y es const para no modificarlo

/*
* Metodos
*/

void Fecha::construir_fecha() {
	time_t tiempo_calendario = time(nullptr);
	tm* tiempo_descompuesto = localtime(&tiempo_calendario);
	if (dia_ == 0) { dia_ = tiempo_descompuesto->tm_mday; }
	if (mes_ == 0) { mes_ = tiempo_descompuesto->tm_mon + 1; }
	if (anno_ == 0) { anno_ = tiempo_descompuesto->tm_year + 1900; }
	if (!(Fecha::validar_fecha(dia_, mes_, anno_))) {
		throw Fecha::Invalida("Fecha no valida");
	}
}

void Fecha::reconstruir_fecha() {
	time_t tiempo_calendario = time(nullptr);
	tm* tiempo_descompuesto = localtime(&tiempo_calendario);	
	
	tiempo_descompuesto->tm_mday = dia_;
	tiempo_descompuesto->tm_mon = mes_ - 1;
	tiempo_descompuesto->tm_year = anno_ - 1900;
	
	mktime(tiempo_descompuesto);
	
	dia_ = tiempo_descompuesto->tm_mday;
	mes_ = tiempo_descompuesto->tm_mon + 1;
	anno_ = tiempo_descompuesto->tm_year + 1900;
	

	if (!(validar_fecha(dia_, mes_, anno_))) {
		throw Fecha::Invalida("Fecha fuera de rango");
	}
}

bool Fecha::validar_fecha(int dia, int mes, int anno) {
	bool valida = false;
	bool bisiesto = (anno % 4 == 0 && (anno % 400 == 0 || anno % 100 != 0));
	if (anno >= Fecha::AnnoMinimo && anno <= Fecha::AnnoMaximo) {
		switch(mes) {
			case 1: case 3 : case 5 : case 7: case 9: case 11: case 12:
				valida = (dia > 0 && dia < 32);
				break;
			case 2: bisiesto ? (valida = (dia > 0 && dia < 30)) : (valida = (dia > 0 && dia < 29));
				break;
			case 4: case 6: case 8: case 10:
					valida = (dia > 0 && dia < 31);
				break;
			default: Fecha::Invalida("El formato es invÃ¡lido");
		}
	}

	return valida;
}

void Fecha::construir_fecha_cadena(const char *cadena) {
	if(std::sscanf(cadena,"%i/%i/%i",&dia_,&mes_,&anno_) != 3) { //Sacado de http://www.cplusplus.com/reference/cstdio/sscanf/ , debe devolver 3, que son el nÃºmero de conversiones realizadas
		throw Fecha::Invalida("El formato es invÃ¡lido");
	} else {
		Fecha(dia_,mes_,anno_);
	}
}

/*
* Subclase
*/

char* Fecha::Invalida::por_que() const { return mensaje_; }

/*
* Sobrecarga de operadores
*/

Fecha Fecha::operator += (int dia) {
	dia_ = dia_ + dia;
	this->reconstruir_fecha();
	return *this;
}

Fecha Fecha::operator -= (int dia) { return *this += (-dia); }

Fecha Fecha::operator ++ () { return *this += 1; }

Fecha Fecha::operator -- () { return *this -= 1; }

Fecha Fecha::operator + (int dia) { return *this += dia; }

Fecha Fecha::operator - (int dia) { return *this -= dia; }

bool Fecha::operator < (Fecha &fecha) { 
	bool menor = true;
	if(this->anno() > fecha.anno()) {
		menor = false;
	}else {
		if(this->mes() > fecha.mes()) {
			 menor = false;
		} else {
			if(this->dia() > fecha.dia()) {
				menor = false;
			}
		}
	}
	return menor;
}

bool Fecha::operator > (Fecha &fecha) {
	return fecha < *this;
}

bool Fecha::operator <= (Fecha &fecha) {
	return !(fecha < *this);
}

bool Fecha::operator >= (Fecha &fecha) {
	return !(*this < fecha);
}

bool Fecha::operator == (Fecha &fecha) {
	return (this->dia() == fecha.dia() && this->mes() == fecha.mes() && this->anno() == fecha.anno());
}

bool Fecha::operator != (Fecha &fecha) {
	return !(*this == fecha);
}

/*
* Observador
*/

char* Fecha::a_cadena() const{
	//char* mes;
	//char* dia;
	char* result;
	
	time_t tiempo_calendario = time(nullptr);
	tm* tiempo_descompuesto = localtime(&tiempo_calendario);	
	
	tiempo_descompuesto->tm_mday = dia_;
	tiempo_descompuesto->tm_mon = mes_ - 1;
	tiempo_descompuesto->tm_year = anno_ - 1900;
	locale::global(std::locale("Es_es");
	mktime(tiempo_descompuesto);
	
	/*
	* Forma con arrays
	
	const char* dia[] = {"Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};
	const char* mes[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
	
	return dia[tiempo_descompuesto->tm_wday] + " " + this->dia() + " de " + mes[this->mes()] + " " + this->anno();
	*/
	
	strftime(result, 50, "%A %d de %B %G" ,tiempo_descompuesto);
	return result;
	
	/*
	* Forma con switch
	
	switch(tiempo_descompuesto->tm_wday) {
		case 0: strcpy(dia, "Domingo");
			break;
		case 1: strcpy(dia, "Lunes");
			break;
		case 2: strcpy(dia, "Martes");
			break;
		case 3: strcpy(dia, "Miércoles");
			break;
		case 4: strcpy(dia, "Jueves");
			break;
		case 5: strcpy(dia, "Viernes");
			break;
		case 6: strcpy(dia, "Sábado");
			break;
	}
	
	switch(this->mes()) {
		case 1: strcpy(mes, "Enero");
			break;
		case 2: strcpy(mes, "Febrero");
			break;
		case 3: strcpy(mes, "Marzo");
			break;
		case 4: strcpy(mes, "Abril");
			break;
		case 5: strcpy(mes, "Mayo");
			break;
		case 6: strcpy(mes, "Junio");
			break;
		case 7: strcpy(mes, "Julio");
			break;
		case 8: strcpy(mes, "Agosto");
			break;
		case 9: strcpy(mes, "Septiembre");
			break;
		case 10: strcpy(mes, "Octubre");
			break;
		case 11: strcpy(mes, "Noviembre");
			break;
		case 12: strcpy(mes, "Diciembre");
			break;
		
		return dia + " " + this->dia() + " de " + mes + " " + this->anno();
	*/
	}
}


