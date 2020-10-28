#include "articulo.hpp"
#include <iomanip>

//Constructor
Articulo::Articulo(const Cadena& cod, const Cadena& t, const Fecha& f, double p, unsigned s): codigo_{cod}, titulo_{t}, fecha_{f}, precio_{p}, stock_{s} {}

//Operador flujo salida
ostream& operator << (ostream& os, const Articulo& a)
{
    os << '[' << a.referencia() << "] \"" << a.titulo() << "\", " << std::fixed << std::setprecision(2) <<
    a.f_publi().anno() << ". "  << a.precio() << " €";

    return os;
}
