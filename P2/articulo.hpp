#ifndef Articulo_HPP_
#define Articulo_HPP_

#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"

using namespace std;

class Articulo
{
    public:
        //Constructor
        explicit Articulo(const Cadena&, const Cadena&, const Fecha& , 
        double, unsigned = 0);

        //Observadores
        inline Cadena referencia() const { return codigo_; }
        inline Cadena titulo() const { return titulo_; }
        inline Fecha f_publi() const { return fecha_; }
        inline double precio() const { return precio_; }
        inline unsigned stock() const { return stock_; }

        //Sobrecarga para referencia
        inline double& precio() { return precio_; }
        inline unsigned& stock() { return stock_; }

    private:
        Cadena codigo_;
        Cadena titulo_;
        Fecha fecha_;
        double precio_;
        unsigned stock_;
};


//Sobrecarga operador flujo
ostream& operator <<(ostream&, const Articulo&);

#endif
