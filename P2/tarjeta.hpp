#ifndef Tarjeta__HPP__
#define Tarjeta__HPP__

#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
#include "usuario.hpp"
#include <cctype>
#include <algorithm>
#include <set>

using namespace std;
bool luhn(const Cadena& numero);
//Predefino Usuario para el compilador, si no lanza error
class Usuario; 


class Numero
{
    public:
        //Constructor
        Numero(const Cadena&);

        //Operador conversion a cadena
        inline operator const char*() const { return num_.c_str(); }

        //enum de Excepcion
        enum Razon{LONGITUD, DIGITOS, NO_VALIDO};

		//Subclase de excepcion
        class Incorrecto
        {
            public:
                Incorrecto(const Numero::Razon);
                //Observador
                inline Numero::Razon razon() const { return razon_; };
            private:
                Numero::Razon razon_;
        };
    private:
        Cadena num_;
};

//Sobrecarga de operador menor que
inline bool operator < (const Numero& num1, const Numero& num2) 
{
	//Llamamos a cadena para que realice una conversion
	return Cadena(num1) < Cadena(num2);	
}

class Tarjeta
{
    public:
    	
    	//Clase amiga usuario para llamar a anula tarjeta
    	friend class Usuario;
    	//Enum de tipos de tarjetas
        enum Tipo{Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};

        //Constructor sin conversiones explicitas
        explicit Tarjeta(const Numero &, Usuario &, const Fecha &);
        
        //Eliminamos constructor de copia
        Tarjeta(const Tarjeta&) = delete;
        Tarjeta& operator =(const Tarjeta&) = delete;

        //Observadores
        inline const Numero numero() const { return numeroT_; }
        inline const Usuario* titular() const { return titular_; }
        inline const Fecha caducidad() const { return caducidad_; }
        inline const bool activa() const { return activa_; }
        
        inline const Tipo tipo() const { return tipo_; }
        
        //Nombre y apellidos del titular en mayusculas
        inline const Cadena titular_facial() const { return titular_facial_; }
        

        //Modificadores
        //Sobrecarga del modificador activa con true por defecto
        bool activa(const bool = true);
        
        //Subclase de excepcion para uso posterior
    	class Desactivada {};

        //Destructor
        ~Tarjeta();
		
		//Subclase de excepcion duplicado
        class Num_duplicado
        {
            public:
                Num_duplicado(const Numero &);
                inline Numero que() const { return numeroD_; }
            private:
                Numero numeroD_;
        };
		
        //Subclase de excepcion caducada
        class Caducada
        {
            public:
                Caducada(const Fecha&);
                inline Fecha cuando() const { return fecha_; }
            private:
                Fecha fecha_;
        };
    private:
    	//Atributos
        Tipo tipo_;
        Numero numeroT_;
        Usuario* titular_;
        Fecha caducidad_;
        bool activa_;
        
        Cadena titular_facial_;
        
        //Puntero a titular nulo y desactiva tarjeta. Privado
        void anula_titular();
        
        static set<Numero> NumerosT;
};

//Sobrecarga de operadores de flujo de salida
ostream& operator << (ostream&, const Tarjeta&);

//Sobrecarga de operador menor que
inline bool operator < (const Tarjeta& t1, const Tarjeta& t2)
{
	return t1.numero() < t2.numero();
}

#endif
