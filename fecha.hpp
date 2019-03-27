#ifndef FECHA_CPP
#define FECHA_CPP
#include <cstring>

class Fecha{
	public:

		//Constructores
		explicit Fecha (int dia = 0, int mes = 0, int anhio = 0);	//explicit evita la conversión
		Fecha (const char *fecha);
		Fecha (const Fecha &copia);
		
		//Sobrecarga
		Fecha operator + (int dia);
		Fecha operator - (int dia);
		Fecha operator ++ (int dia);
		Fecha operator -- (int dia);
		Fecha operator ++ ();
		Fecha operator -- ();
		Fecha operator += (int dia);
		Fecha operator -= (int dia);

		bool operator == (Fecha &fecha) noexcept;	//No devuelve excepci�n
		bool operator != (Fecha &fecha) noexcept;
		bool operator < (Fecha &fecha) noexcept;
		bool operator > (Fecha &fecha) noexcept;
		bool operator <= (Fecha &fecha) noexcept;
		bool operator >= (Fecha &fecha) noexcept;
		
		//Fecha operator + (const Fecha &copia);
		//Fecha operator - (const Fecha &copia);
		//Fecha operator = (const Fecha &copia);	//No necesario a no ser que alguno de los atributos sea un puntero a direccion de memoria, el constructor de copia apunta a la misma direccion y ambas pueden modificarlo

		//Constantes
		static const int AnnoMinimo = 1902;
		static const int AnnoMaximo = 2037;

		//Observadores
		inline int dia() const { return dia_; }	//const por ser método observador
		inline int mes() const { return mes_; }
		inline int anno() const { return anno_; }
		char* a_cadena() const;

		//Subclase
		class Invalida {
			public:
				Invalida (const char *mensaje) noexcept {
					mensaje_ = new char[strlen(mensaje)];
					strcpy(mensaje_,mensaje);
				}
				~Invalida() {
					delete[] mensaje_;
				}
				char* por_que() const;	//Observador: const
			private:
				char *mensaje_;
		};

	private:
		int dia_, mes_, anno_;
		bool validar_fecha(int dia, int mes, int anno);
		void construir_fecha();
		void construir_fecha_cadena(const char *cadena);
		void reconstruir_fecha();
};

#endif
