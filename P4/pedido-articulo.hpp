#ifndef Pedido_Articulo_hpp
#define Pedido_Articulo_hpp

#include <locale>
#include <iomanip>
#include <map>
#include <iostream>
#include "pedido.hpp"
#include "articulo.hpp"

using namespace std;

class LineaPedido;
class Pedido;
class Pedido;

class OrdenaArticulos
{
    public:
        bool operator()(Articulo*, Articulo*) const;
};

class OrdenaPedidos
{
    public:
        bool operator()(Pedido*, Pedido*) const;
};

class Pedido_Articulo
{
    public:
    	//Mapas de asociacion
        typedef map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
        typedef map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

        void pedir(Pedido&, Articulo&, const double, unsigned = 1);
        void pedir(Articulo&, Pedido&, const double, unsigned = 1);

        const ItemsPedido& detalle(Pedido&);
        Pedidos& ventas(Articulo&);

        ostream& mostrarDetallePedidos(ostream&) const;
        ostream& mostrarVentasArticulos(ostream&) const;
    private:
        typedef map<Pedido*, ItemsPedido, OrdenaPedidos> PedidosArticulos;
        typedef map<Articulo*, Pedidos, OrdenaArticulos> ArticulosPedido;
        PedidosArticulos pedidosArticulos_;
        ArticulosPedido articulosPedido_;
};


//Sobrecarga de operador de inserccion en flujo
ostream& operator <<(ostream&, const Pedido_Articulo::ItemsPedido&);
ostream& operator <<(ostream&, const Pedido_Articulo::Pedidos);

class LineaPedido
{
    public:
        //Constructor explicito para evitar conversion implicita de pedido a linea pedido
        explicit LineaPedido(const double, const unsigned int = 1);
        
        //Observadores
        inline double precio_venta() const { return precioVenta_; }
        unsigned cantidad() const { return cantidad_; }
    private:
        double precioVenta_;
        unsigned cantidad_;
};

//Sobrecarga de operador de inserccion en flujo para LineaPedido
ostream& operator <<(ostream&, const LineaPedido&);

#endif
