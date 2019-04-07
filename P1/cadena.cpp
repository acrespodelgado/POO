#include "cadena.hpp"

Cadena::Cadena(const char *cad) : tam{strlen(cad)}, s{new char[strlen(cad)+1]}
{
    strcpy(s, cad);
}

Cadena::Cadena(const Cadena &otro) : tam{otro.length()}, s{new char[otro.length()+1]}
{
    strcpy(s, otro);
}

Cadena::Cadena(sizet tam, char c) : tam(tam), s(new char[tam+1])
{
    for(unsigned i=0; i < tam; ++i)
        *(s + i) = c;
    *(s + tam) = '\0';
}

Cadena::~Cadena()
{
    delete []s;
}
char Cadena::at(sizet pos) const
{
    if(pos < 0 || pos > tam)
        throw std::out_ofrange("Se ha seleccionado una posicion de memoria no reservada");
    else
        return *(s + pos);
}

char& Cadena::at(sizet pos)
{
    if(pos < 0 || pos > tam)
        throw std::out_ofrange("Se ha seleccionado una posicion de memoria no reservada");
    else
        return *(s + pos);
}

Cadena Cadena::substr(size_t pos, sizet tam) const
{
    char c[tam+1];
    c[tam] = '\0';
    if(!(pos > tam || (pos+tam)>tam_))
    {
        for(sizet i=0; i<tam; ++i)
            c[i] = this->s[pos+i];
        return c;
    }
    else
        throw std::out_ofrange("Se ha seleccionado una posicion de memoria no reservada");
}

Cadena Cadena::operator =(const Cadena &otro)
{
    if(otro!=*this)
    {
        this->tam = otro.tam;
        delete []s;
        s = new char[tam];
        strcpy(s_, otro);
    }
    return *this;
}

Cadena Cadena::operator =(const char *cad)
{
    *this = Cadena(cad);
    return *this;
}

Cadena Cadena::operator +=(const Cadena &otro)     //A = A + B
{
    sizet tam = otro.length() + tam;
    char aux[tam+1];
    strcpy(aux, *this);
    strcat(aux, otro);
    *this = Cadena(aux);
    return this;
}

Cadena Cadena::operator +(const Cadena &otro)
{
    Cadena aux(this);
    aux += otro;
    return aux;
}
bool Cadena::operator ==(const Cadena &otro)
{
    return (strcmp(this, otro)==0);
}

bool Cadena::operator !=(const Cadena &otro)
{
    return (strcmp(this, otro)!=0);
}

bool Cadena::operator <(const Cadena &otro)
{
    return (strcmp(this, otro) < 0);
}

bool Cadena::operator >(const Cadena &otro)
{
    return (strcmp(this, otro) > 0);
}

bool Cadena::operator <=(const Cadena &otro)
{
    return (!((strcmp(this, otro)) > 0));
}

bool Cadena::operator >=(const Cadena &otor)
{
    return (!((strcmp(this, otor)) < 0));
}

Cadena Cadena::operator +=(const char *otro)     //A = A + B
{
    *this += Cadena(otro);
    return *this;
}

Cadena Cadena::operator +(const char otro)
{
    Cadena aux(this);
    aux += otro;
    return aux;
}

bool Cadena::operator ==(const char otro)
{
    return (strcmp(this, otro)==0);
}

bool Cadena::operator !=(const char otro)
{
    return (strcmp(this, otro)!=0);
}

bool Cadena::operator <(const char otro)
{
    return (strcmp(this, otro) < 0);
}

bool Cadena::operator >(const char otro)
{
    return (strcmp(this, otro) > 0);
}

bool Cadena::operator <=(const char otro)
{
    return (!((strcmp(this, otro)) > 0));
}

bool Cadena::operator >=(const char otro)
{
    return (!((strcmp(this, otro)) < 0));
}
