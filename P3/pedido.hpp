#ifndef Pedido_hpp
#define Pedido_hpp

#include <iostream>
#include <locale>
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
#include "usuario.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"

using namespace std;

class Usuario_Pedido;
class Pedido_Articulo;

class Pedido
{
    public:
        //Constructor con parametros
        explicit Pedido(Usuario_Pedido&, Pedido_Articulo&, Usuario&, const Tarjeta&, const Fecha& = Fecha());

        //Observadores
        inline unsigned int numero() const { return num_; }
        inline const Tarjeta* tarjeta() const { return tarjeta_; }
        inline Fecha fecha() const { return fecha_; }
        inline double total() const { return precioTotal_; }
        inline static unsigned n_total_pedidos() { return cantidadPedidos_; }

        //Clases de excepcion
        class Vacio
        {
            public:
                Vacio(const Usuario&);
                //Observador
                inline const Usuario& usuario() const { return *usPed_; };
            private:
                const Usuario* usPed_;
        };

        class Impostor
        {
            public:
                Impostor(const Usuario&);
                //Observador
                inline const Usuario& usuario() const { return *usPed_; }
            private:
                const Usuario* usPed_;
        };

        class SinStock
        {
            public:
                SinStock(Articulo&);
                inline Articulo& articulo() const { return *art_; }
            private:
                Articulo* art_;
        };
        
    private:
        unsigned int num_; 
        const Tarjeta* tarjeta_;
        Fecha fecha_;
        double precioTotal_;
        static unsigned cantidadPedidos_;
};

//Sobrecarga de operador de inserccion en flujo para pedido
ostream& operator <<(ostream&, const Pedido&);

#endif
