#include "tarjeta.hpp"

//Set de tarjetas para comprobar num duplicados
set<Numero> Tarjeta::NumerosT{};

//Requeridas para P3
struct EsBlanco
{
    bool operator ()(char c) const { return isspace(c); }
};

struct EsDigito
{
    bool operator ()(char c) const { return isdigit(c); }
    typedef char argument_type;
};

//Clase numero

//Constructor
Numero::Numero(Cadena cad): num_{}
{	
    Cadena::iterator primero = cad.begin();
    Cadena::iterator ultimo = std::remove_if(primero, cad.end(), EsBlanco());
    size_t distancia = std::distance(primero, ultimo);

    if(std::find_if(primero, ultimo, std::not1(EsDigito())) != ultimo)
        throw Incorrecto(DIGITOS);

    if(distancia < 13 || distancia > 19)
        throw Incorrecto(LONGITUD);

    Cadena aux(distancia);
    std::copy(primero, ultimo, aux.begin());
    if(!luhn(aux))
        throw Incorrecto(NO_VALIDO);

    num_ = aux;
}

Numero::Incorrecto::Incorrecto(const Razon r): razon_{r} {}

//Clase Tarjeta

//Hacemos uso del set de tarjetas para comprobar nums duplicados

//Constructores de excepcion
Tarjeta::Num_duplicado::Num_duplicado(const Numero &num) : numeroD_{num} {}

Tarjeta::Caducada::Caducada(const Fecha& f): fecha_{f} {}

//Constructor
Tarjeta::Tarjeta(const Numero& n, Usuario& u, const Fecha& f): numeroT_{n}, titular_{&u}, caducidad_{f}, activa_{true}
{
	//Comprobaciones de caducidad, hacemos uso de nuestra clase fecha
    if(caducidad_.anno() < Fecha{}.anno())
        throw Caducada(caducidad_);
    if(caducidad_.anno() == Fecha{}.anno() && caducidad_.mes() < Fecha{}.mes())
        throw Caducada(caducidad_);
    if(caducidad_.anno() == Fecha{}.anno() && caducidad_.mes() == Fecha{}.mes() && caducidad_.dia() < Fecha{}.dia())
        throw Caducada(caducidad_);

    pair<set<Numero>::iterator, bool> p = NumerosT.insert(numeroT_);
	
	//Si se encuentra en el set, lanza excepcion
    if(!p.second)
        throw Num_duplicado(numeroT_);

	//Tipo de tarjeta, dependiendo de como empiece
    switch (numeroT_[0])
    {
    case '3': 
        if (numeroT_[1] == 4 || numeroT_[1] == 7)
        	tipo_ = AmericanExpress;
		else
			tipo_ = JCB;
    case '4': tipo_ = VISA;
        break;
    case '5': tipo_ = Mastercard;
        break;
    case '6': tipo_ = Maestro;
        break;
    //Por defecto otra
    default: tipo_ = Otro;
        break;
    }
	
	//Titular facial
    Cadena tf(u.nombre() + " " + u.apellidos());
	
	//Guardamos el titular el mayusculas
    for(int i = 0; i < tf.length(); ++i)
        tf[i] = toupper(tf[i]);
    
    titular_facial_ = tf;

	//Le asignamos al titular esta tarjeta
    titular_->es_titular_de(*this);
}

bool Tarjeta::activa(bool estado)
{
    activa_ = estado;
    return activa_;
}

void Tarjeta::anula_titular()
{
    titular_ = nullptr;
    activa_ = false;
}

//Destructor
Tarjeta::~Tarjeta()
{
	//Si no se ha anulado antes (usuario nullptr)
    if(titular_ != nullptr)
        const_cast<Usuario*>(titular_) -> no_es_titular_de(*this);
    
    //Eliminamos del set de tarjetas el numero
    NumerosT.erase(numeroT_);
}

//Sobrecarga de operador de flujo
ostream& operator <<(ostream& os, const Tarjeta& t)
{
	//Mostramos el tipo primero
    switch (t.tipo())
    {
        case Tarjeta::Tipo::VISA: os << "VISA";
                break;
        case Tarjeta::Tipo::Mastercard: os << "Mastercard";
                break;
        case Tarjeta::Tipo::Maestro: os << "Maestro";
                break;
        case Tarjeta::Tipo::AmericanExpress: os << "American Expres";
                break;
        case Tarjeta::Tipo::JCB: os << "JCB";
                break;
        case Tarjeta::Tipo::Otro: os << "Tipo indeterminado";
        default: os << "El tipo de la tarjeta no esta disponible" << endl;
    }
	
	//Para la caducidad nos quedamos con el modulo que nos devuelve los digitos que nos interesan y le añadimos un 0 delante en los meses
    os << '\n' << t.numero() << '\n' << t.titular_facial()
    << '\n' << "Caduca: " << ((t.caducidad().mes() < 10) ? '0' : ' ') <<
    t.caducidad().mes() << '/' << (t.caducidad().anno() % 100) << endl;

    return os;
}
ostream& operator << (ostream& os, const Tarjeta::Tipo& tipo)
 {
    switch(tipo)
    {
        case 0: os << "VISA"; 
			break;
        case 1: os << "Mastercard"; 
			break;
        case 2: os << "Maestro"; 
			break;
        case 3: os << "JCB"; 
			break;
        case 4: os << "AmericanExpress"; 
			break;
        case 5: os << "Tipo indeterminado"; 
			break;
        default: os << "Error";
    }
    return os;
}
