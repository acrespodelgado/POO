#ifndef Usuario_HPP_
#define Usuario_HPP_

#include "../P1/cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include "unistd.h"
#include <map>
#include <utility>
#include <random>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Tarjeta;
class Numero;

//Clave
class Clave
{
    public:
        //Constructor cadena bajo nivel
        Clave(const char*);

        //Observadores
        inline Cadena clave() const { return clave_; }
        
        //Metodos
        bool verifica(const char*) const;        
		
		//Enum de razones incorrecta
        enum Razon{CORTA, ERROR_CRYPT};
		
		//Subclase
        class Incorrecta
        {
            public:
                Incorrecta(Razon);
                //Observador
                inline Razon razon() const { return razon_; };
            private:
                Razon razon_;      
        };
        
    private:
        Cadena clave_;
};

class Usuario
{
    public:
    	//Constructor
        Usuario(const Cadena&, const Cadena&, const Cadena&, const Cadena&, const Clave&);
        //Eliminamos constructor de copia
        Usuario(const Usuario&) = delete;
        Usuario& operator =(const Usuario&) = delete;
        
        //Destructor
        ~Usuario();
        
        //Atributo de enlace a asociacion clase Tarjeta y sinonimo publico Tarjetas
        typedef map<Numero, Tarjeta*> Tarjetas;
        
        //Atributo de enlace a asociacion clase articulo y sinonimo publico Articulos
        typedef unordered_map<Articulo*, unsigned> Articulos;
        
        //Set de usuarios repetidos
        static unordered_set<Cadena> usuarios;

        //Observadores
        inline Cadena id() const { return identificador_; }
        inline Cadena nombre() const { return nombre_; }
        inline Cadena apellidos() const { return apellidos_; }
        inline Cadena direccion() const { return direccion_; }
        //Lo necesito para devolver la clave en el os
        inline Clave clave() const { return clave_; }
        
        inline const Tarjetas& tarjetas() const { return tarjetas_; }
        inline Articulos compra() const { return carrito_; }
        
        //Mostrar  articulos diferentes carrito
        inline unsigned n_articulos() const { return carrito_.size(); }

        //Asociacion con tarjeta
        void es_titular_de(Tarjeta&);
        void no_es_titular_de(Tarjeta&);
        
        //Asociacion con Articulo
        void compra(Articulo&, unsigned = 1);

//Operadores de salida
friend ostream& operator <<(ostream& os, const Usuario& u);

        //Subclase de excepcion
        class Id_duplicado
        {
            public:
            	//Recibe una cadena
                Id_duplicado(const Cadena&);
                //Observador
                inline Cadena idd() const { return id_; }
            private:
                Cadena id_;
        };
    private:
    	//Atributos cadenas
        Cadena identificador_, nombre_, apellidos_, direccion_;
        Clave clave_;
        Tarjetas tarjetas_;
        Articulos carrito_;
};

void mostrar_carro(ostream&, const Usuario&);

#endif
