#include "pedido-articulo.hpp"

bool OrdenaPedidos::operator() (Pedido* p1, Pedido* p2) const
{
    return p1 -> numero() < p2 -> numero();
}

bool OrdenaArticulos::operator() (Articulo* a1, Articulo* a2) const
{
    return a1->referencia() < a2->referencia();
}

void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double precioVenta, unsigned cant)
{
    pedidosArticulos_[&p].insert(std::make_pair(&a, LineaPedido(precioVenta, cant)));
	articulosPedido_[&a].insert(std::make_pair(&p, LineaPedido(precioVenta, cant)));
}

void Pedido_Articulo::pedir(Articulo& a, Pedido& p, const double precioVenta, const unsigned cant)
{
    pedir(p, a, precioVenta, cant);
}

const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& p)
{
    return pedidosArticulos_.find(&p) -> second;
}

Pedido_Articulo::Pedidos& Pedido_Articulo::ventas(Articulo& a)
{
    
    return articulosPedido_[&a];
}

ostream& operator <<(ostream& os, const Pedido_Articulo::ItemsPedido& items)
{
    setlocale(LC_ALL, "es_ES");
    double total{0};

    os << "  PVP   Cantidad       Artículo\n" <<
    "==================================================================\n";

    for(auto it : items)
    {
        os << setiosflags(ios::fixed) << setprecision(2) <<
         it.second.precio_venta() << " € " << it.second.cantidad() <<
        setw(15-(it.second.cantidad()/10)) << "[" << 
        it.first -> referencia() << "] \"" << it.first -> titulo() << "\n";

        total += it.second.precio_venta();  
    }

    os <<
    "==================================================================\n"
    << "Total\t" << setiosflags(ios::fixed) << setprecision(2) <<
    total << " €\n";

    return os;
}

ostream& operator <<(ostream& os, Pedido_Articulo::Pedidos p)
{
    setlocale(LC_ALL, "es_ES");
    double total{0};

    os << "[Pedidos: " << p.size() << "]\n" <<
    "==================================================================\n"
    << "  PVP   Cantidad\t\t"  << "Fecha de venta\n"
    <<
    "==================================================================\n";

    for(auto it : p)
    {
        os << setiosflags(ios::fixed) << setprecision(2) << 
        it.second.precio_venta() << " € " << it.second.cantidad() <<
        "\t\t" << it.first -> fecha() << "\n";

        total += it.second.precio_venta() * it.second.cantidad();
    }

    os <<
    "==================================================================\n"
    << setiosflags(ios::fixed) << setprecision(2) << total << " €\t\t\t"
    << p.size() << '\n';

    return os;
}

ostream& Pedido_Articulo::mostrarDetallePedidos(ostream& os) const
{
    setlocale(LC_ALL, "es_ES");
    double total{0};

    for(auto it : pedidosArticulos_)
    {
        os << "Pedido num. " << it.first -> numero() << "\nCliente: "
        << it.first -> tarjeta() -> titular() -> nombre() << "\t\t" << 
        it.first -> fecha() << "\n" << it.second << "\n";

        total += it.first -> total();
    }

    os << "TOTAL VENTAS\t\t" << setiosflags(ios::fixed) << setprecision(2) << total << " €\n";

    return os;
}

ostream& Pedido_Articulo::mostrarVentasArticulos(ostream& os) const
{
    setlocale(LC_ALL, "es_ES");

    for(auto it : articulosPedido_)
        os << "Ventas de " << *it.first << "\n" << it.second << "\n\n";

    return os;
}

//LineaPedido

//Constructor
LineaPedido::LineaPedido(const double pre, const unsigned cant): precioVenta_{pre}, cantidad_{cant} {}

//Inserccion en flujo LineaPedido
ostream& operator <<(ostream& os, const LineaPedido& lp)
{
    os << setiosflags(ios::fixed) << setprecision(2) << lp.precio_venta() << " €\t" << lp.cantidad();

    return os;
}
