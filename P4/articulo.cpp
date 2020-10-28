#include "articulo.hpp"
#include <iomanip>

//Constructor
Articulo::Articulo(const Autores &a, const Cadena& cod, const Cadena& t, const Fecha& f, double p): autores_{a}, codigo_{cod}, titulo_{t}, fecha_{f}, precio_{p}
{
	if(a.empty())
		throw Autores_vacios();
}

Articulo::~Articulo(){}

//Operador flujo salida
ostream& operator << (ostream& os, const Articulo& a)
{
    //Iterador para bucle
    Articulo::Autores::const_iterator i = a.autores().begin();

	os << "[" << a.referencia() << "] " << "\"" << a.titulo() << "\", de ";

	while(i != a.autores().end()){
		os << (*i)->apellidos();
		
		if(i != a.autores().end())
			os << ", ";
        
        ++i;
	}

	os << ". "<< a.f_publi().anno() << ". "
	<< std::fixed << std::setprecision(2) << a.precio() << " €\n\t";
	a.impresion_especifica(os);

	return os;
}

//Constructores clases derivadas
ArticuloAlmacenable::ArticuloAlmacenable(const Autores &a, const Cadena &cod, const Cadena &t, const Fecha &f, double p, unsigned s) : Articulo{a, cod, t, f, p}, stock_{s} {}
ArticuloAlmacenable::~ArticuloAlmacenable(){}

Libro::Libro(const Autores &a, const Cadena &cod, const Cadena &t, const Fecha &f, double p, unsigned np, unsigned s) : ArticuloAlmacenable{a, cod, t, f, p, s}, n_pag_{np} {}

Cederron::Cederron(const Autores &a, const Cadena &cod, const Cadena &t, const Fecha &f, double p, unsigned tam, unsigned s) : ArticuloAlmacenable{a, cod, t, f, p, s}, tam_{tam} {}

LibroDigital::LibroDigital(const Autores &a, const Cadena &cod, const Cadena &t, const Fecha &f, double p, const Fecha &fe) : Articulo{a, cod, t, f, p}, f_expir_{fe} {}

Autor::Autor(Cadena n, Cadena a, Cadena d) noexcept : nombre_{n}, apellidos_{a}, direccion_{d} {}

//Insercción flujo clases derivadas
void Libro::impresion_especifica(std::ostream &os) const noexcept{
	os << n_pag_ << " págs., " << stock_ << " unidades.";
}

void Cederron::impresion_especifica(std::ostream &os) const noexcept{
	os << tam_ << " MB, " << stock_ << " unidades.";
}

void LibroDigital::impresion_especifica(std::ostream &os) const noexcept{
	os << "A la venta hasta el " << fech_expir_ << '.';
}
