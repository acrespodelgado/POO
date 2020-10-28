#include "usuario-pedido.hpp"

//Observadores
Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(Usuario& us)
{   
    return usuarios_.find(&us)->second;
}

const Usuario* Usuario_Pedido::cliente(Pedido& p)
{
    return p.tarjeta() -> titular();
}

const Usuario* Usuario_Pedido::cliente(const Pedido &p)
{
    return p.tarjeta()->titular();
}

const Usuario *Usuario_Pedido::cliente(const Pedido &p) const
{
    return p.tarjeta()->titular();
}

//Metodos y sobrecarga

void Usuario_Pedido::asocia(Usuario& us, Pedido& p)
{
    pedidos_.insert(&p);
    Usuarios::iterator it = usuarios_.find(&us);

    if(it != usuarios_.end())
        it -> second.insert(&p);
    else
    {   Pedidos pedidos;
        pedidos.insert(&p);
        usuarios_.insert(make_pair(&us, pedidos));
    }
}

void Usuario_Pedido::asocia(Pedido& p, Usuario& us)
{
    asocia(us, p);
}
