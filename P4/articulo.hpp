#ifndef Articulo_HPP_
#define Articulo_HPP_

#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
#include <ostream>
#include <set>

using namespace std;

class Autor{
    public:
        //Constructor
        Autor(Cadena, Cadena, Cadena) noexcept;

        //Observadores
        inline Cadena nombre() const noexcept { return nombre_; }
        inline Cadena apellidos() const noexcept { return apellidos_; }
        inline Cadena direccion() const noexcept { return direccion_; }
    private:
        Cadena nombre_;
        Cadena apellidos_;
        Cadena direccion_;
};

class Articulo
{
    public:
        //Sinonimo de autores
        typedef std::set<Autor*> Autores;
        class Autores_vacios;

        //Constructor
        explicit Articulo(const Autores&, const Cadena&, const Cadena&, const Fecha& , double);

        //Observadores
        inline Cadena referencia() const { return codigo_; }
        inline Cadena titulo() const { return titulo_; }
        inline Fecha f_publi() const { return fecha_; }
        inline double precio() const { return precio_; }
        inline const Autores &autores() const { return autores_; }

        //Sobrecarga para referencia
        inline double& precio() { return precio_; }
        
        //Métodos virtuales
        virtual void impresion_especifica(std::ostream&) const noexcept = 0;
	    virtual ~Articulo();

    private:
        Cadena codigo_;
        Cadena titulo_;
        Fecha fecha_;
        double precio_;
        const Autores autores_;
};

//Clases derivadas

class ArticuloAlmacenable : public Articulo{
    public:
        //Constructor
        ArticuloAlmacenable(const Autores&, const Cadena&,const Cadena&, const Fecha&, double, unsigned = 0);

        //Observadores
        inline unsigned stock() const { return stock_; }
        inline unsigned& stock() { return stock_; }

        //Metodos virtuales
        virtual void impresion_especifica(std::ostream&) const noexcept = 0;
        virtual ~ArticuloAlmacenable();
    protected:
	    unsigned stock_;
};

class Libro : public ArticuloAlmacenable{
    public:
        //Constructor
        Libro(const Autores&, const Cadena&,const Cadena&, const Fecha&, double, unsigned, unsigned = 0);

        //Observador
        inline unsigned n_pag() const noexcept { return n_pag_; }

        void impresion_especifica(std::ostream&) const noexcept;
    private:
        const unsigned n_pag_;
};

class Cederron : public ArticuloAlmacenable{
    public:
        //Constructor
        Cederron(const Autores&, const Cadena&,const Cadena&, const Fecha&, double, unsigned, unsigned = 0);
        
        //Observador
        unsigned tam() const noexcept;

        void impresion_especifica(std::ostream&) const noexcept;
    private:
        const unsigned tam_;
};

class LibroDigital : public Articulo{
    public:
        //Constructor
        LibroDigital(const Autores&, const Cadena&,const Cadena&, const Fecha&, double, const Fecha&);

        //Observador
        inline Fecha f_expir() const noexcept { return fech_expir_; }

        void impresion_especifica(std::ostream&) const noexcept;
    private:
        const Fecha fech_expir_;
};

class Articulo::Autores_vacios{};

//Sobrecarga operador flujo
ostream& operator <<(ostream&, const Articulo&);

#endif
