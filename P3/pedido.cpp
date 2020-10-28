#include "pedido.hpp"

unsigned Pedido::cantidadPedidos_ = 0;

//Pedido
//Constructor

Pedido::Pedido(Usuario_Pedido& usPed, Pedido_Articulo& pedArt, Usuario& us, const Tarjeta& t, const Fecha& f): num_{cantidadPedidos_ + 1}, tarjeta_{&t}, fecha_{f},
precioTotal_{0}
{
	Usuario::Articulos carrito = us.compra();
    if(carrito.empty())
        throw Vacio(us);
    if(t.titular() != &us)
        throw Impostor(us);
    if(t.caducidad() < f)
        throw Tarjeta::Caducada(t.caducidad());
    if(!t.activa())
        throw Tarjeta::Desactivada();
    Usuario::Articulos::const_iterator i = carrito.begin();
    while(i != carrito.end()){
        Articulo *actual = i->first;
        if(i->second > actual->stock()){
            while(i != carrito.end()){
                us.compra(*i->first, 0);
                ++i;
            }
            throw SinStock(*actual);
        }
        pedArt.pedir(*this, *actual, actual->precio(), i->second);
        actual->stock() -= i->second;
        precioTotal_ += i->second * actual->precio();
        us.compra(*actual, 0);
        ++i;
    }
    usPed.asocia(us, *this);
	cantidadPedidos_++;
}

//Clases de excepcion
Pedido::Vacio::Vacio(const Usuario& us): usPed_{&us} {}

Pedido::Impostor::Impostor(const Usuario& us): usPed_{&us} {}

Pedido::SinStock::SinStock(Articulo& a): art_{&a} {}

//Inserccion en flujo pedido
ostream& operator <<(ostream& os, const Pedido& p)
{
    os << "Núm. pedido:\t" << p.numero() << "\nFecha:\t\t" << p.fecha() << "\nPagado con:\t" << p.tarjeta() -> tipo() <<
    " n.º: " << p.tarjeta() -> numero() << "\nImporte:\t" << 
    setiosflags(ios::fixed) << setprecision(2) << p.total() << " €";

    return os;
}
