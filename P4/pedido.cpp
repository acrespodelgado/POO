#include "pedido.hpp"

unsigned Pedido::cantidadPedidos_ = 0;

//Pedido
//Constructor

Pedido::Pedido(Usuario_Pedido& usPed, Pedido_Articulo& pedArt, Usuario& us, const Tarjeta& t, const Fecha& f): num_{cantidadPedidos_ + 1}, tarjeta_{&t}, fecha_{f}, precioTotal_{0}
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

    for(auto i : carrito){
		if(LibroDigital *ld = dynamic_cast<LibroDigital*>(i.first)){
			if(ld->f_expir() >= fecha_){
				pedArt.pedir(*this, *i.first, i.first->precio(), i.second);
				precioTotal_ += i.first->precio() * i.second;
			}
			us.compra(*i.first, 0);
		}
		else if(ArticuloAlmacenable *aa = dynamic_cast<ArticuloAlmacenable*>(i.first)){
			if(aa->stock() < i.second){
				for(auto i : carrito)
						us.compra(*i.first, 0);
					throw SinStock(*i.first);
			}
			aa->stock() -= i.second;
			pedArt.pedir(*this, *i.first, i.first->precio(), i.second);
			precioTotal_ += i.first->precio() * i.second;
			us.compra(*i.first, 0);
		}
	}

	//Se lanza si se vacia
	if(precioTotal_ == 0)
		throw Vacio(us);

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
    return os << "Núm. pedido:\t" << p.numero() << "\nFecha:\t" << p.fecha() << "\nPagado con:\t" << *p.tarjeta() << "\nImporte:\t" << p.total() << " €"<< std::endl;
}
