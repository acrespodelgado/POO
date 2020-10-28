#ifndef Usuario_Pedido_hpp
#define Usuario_Pedido_hpp

#include <map>
#include <set>
#include <utility>
#include "usuario.hpp"
#include "pedido.hpp"

using namespace std;

class Pedido;
class Usuario;

class Usuario_Pedido
{
    public:
    	//Mapas de asociacion, diccionario de punteros
        typedef set<Pedido*> Pedidos;
        typedef map<Usuario*, Pedidos> Usuarios;
        
        //Metodos con su sobrecarga
        void asocia(Usuario&, Pedido&);
        void asocia(Pedido&, Usuario&);
        
        //Observadores
        Pedidos pedidos(Usuario&);
        const Usuario* cliente(Pedido&);
        const Usuario* cliente(const Pedido &);
        const Usuario* cliente(const Pedido &) const;
    private:
        Pedidos pedidos_;
        Usuarios usuarios_;
};

#endif
