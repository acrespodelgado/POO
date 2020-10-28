#include "usuario.hpp"
#include <clocale>

//Comprobador de usuarios duplicados
unordered_set<Cadena> Usuario::usuarios;

//Constructor
Clave::Clave(const char* nc): clave_{}
{
	//Clave no cifrada aun, si no llega a 5 caracteres se lanza excepcion
    if(strlen(nc) < 5)
      throw Incorrecta(CORTA);
	
    //Se cifra, sacado del manual
    char salt[2];
    int r_number;
    const char *const seedchars
    {"./0123456789ABCDEFGHIJKLMNOPQRST"
    "UVWXYZabcdefghijklmnopqrstuvwxyz"};

    std::random_device r;

    std::default_random_engine el{r()};

    std::uniform_int_distribution<int> u_dist{0, (int)(strlen(seedchars)) - 1};

    for(int i = 0; i < 2; ++i )
    {
      r_number = u_dist(el);
      salt[i] = seedchars[r_number];
    }

    char* encrypted = crypt(nc, salt);

    if(nc == encrypted)
      throw Incorrecta(ERROR_CRYPT);

    clave_ = encrypted;
}

bool Clave::verifica(const char* c) const
{
    bool verificada = false;

    if(const char* const checker = crypt(c, clave_.c_str())) 
	{
		if(checker == clave_)
			verificada = true;
	}
    else
        throw Incorrecta(ERROR_CRYPT);

    return verificada;
}

//Constructor de Excepcion
Clave::Incorrecta::Incorrecta(Razon r): razon_{r} {}

//Constructor
Usuario::Usuario(const Cadena& id, const Cadena& n, const Cadena& a, const Cadena& d, const Clave& c): identificador_{id}, nombre_{n}, apellidos_{a}, direccion_{d}, clave_{c} 
{
	//Comprobacion de id no duplicado
	//Vamos añadiendo a un iterador todos los identificadores
    pair<unordered_set<Cadena>::iterator, bool> pares = usuarios.insert(identificador_);
	
	//Si second es falso está duplicado
    if (!pares.second)
        throw Id_duplicado(identificador_);
}

//Asociacion con tarjeta
void Usuario::es_titular_de(Tarjeta& t)
{
    if(identificador_ == t.titular()->id() || t.titular() == nullptr)
    {    
        pair<Tarjetas::iterator, bool> p = tarjetas_.insert(make_pair(t.numero(), &t));

        if (!p.second)
            cout << "No se ha insertado la tarjeta con numero: " << t.numero() << endl;
    }
    else
        cout << "Error en el titular." << endl;
}

void Usuario::no_es_titular_de(Tarjeta& tarjeta)
{
    tarjetas_.erase(tarjeta.numero());
}

//Asociacion con compra
void Usuario::compra(Articulo& art, unsigned cantidad)
{
	//Si viene 0 en el articulo se elimina
    if(cantidad == 0)
        carrito_.erase(&art);
    else
        carrito_[&art] = cantidad;
}

//Destructor
Usuario::~Usuario()
{
    usuarios.erase(identificador_);

    for(auto i : tarjetas_)
        i.second -> anula_titular();

    tarjetas_.erase(tarjetas_.begin(), tarjetas_.end());
}

//Constructor de clase de excepcion
Usuario::Id_duplicado::Id_duplicado(const Cadena& s): id_{s} {}

//Sobrecarga de operador de salida
ostream& operator <<(ostream& os, const Usuario& u)
{
    os << u.id() << " [" << u.clave().clave() << "] " << 
    u.nombre() << ' ' << u.apellidos() << '\n' << u.direccion()
    << "\nTarjetas:\n";

    for(auto i : u.tarjetas())
        os << *i.second << '\n';
    
    return os;
}

//Muestra el carro de la compra en flujo de salida
void mostrar_carro(ostream& os, const Usuario& u)
{
    setlocale(LC_ALL, "es_ES.UTF-8");

    os << "Carrito de compra de " << u.id() << " [ArtÃ­culos: " <<
    u.n_articulos() << ']' << endl;

    os << "\tCant. ArtÃ­culo" << endl;
    os <<
    "==========================================================="
    << endl;
	
    for (auto i : u.compra())
    {
        os << i.second << "   " << *(i.first) << endl;
    }
}
