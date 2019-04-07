#ifndef CADENA_HPP 
#define CADENA_HPP 

#include <cstring> 
#include <stdexcept> 
#include <iostream>  

class Cadena { 
	public:     
		Cadena(const char s);
		explicit Cadena(size_t tam=0, char c=' ');
		Cadena(const Cadena &otra);
		inline sizet length() const{ return tam; }
		char at(size_t pos) const;
		char& at(size_t pos);
		Cadena substr(size_t pos, size_t tam) const;
		inline operator const char() const{ return s_; }
		Cadena operator =(const Cadena &otro);
		Cadena operator =(const char *cad);
		inline char operator [](sizet pos) const{return *(s + pos);}
		inline char& operator [](sizet pos) {return *(s + pos);}
		Cadena operator +=(const Cadena &otro);
		Cadena operator +(const Cadena &otro);
		bool operator ==(const Cadena &otro);     
		bool operator !=(const Cadena &otro);     
		bool operator >(const Cadena &otro);     
		bool operator <(const Cadena &otro);     
		bool operator <=(const Cadena &otro);     
		bool operator >=(const Cadena &otor);     
		Cadena operator +=(const char *otro);     
		Cadena operator +(const char *otro);     
		bool operator ==(const char *otro);     
		bool operator !=(const char *otro);     
		bool operator >(const char *otro);     
		bool operator <(const char *otro);     
		bool operator <=(const char *otro);     
		bool operator >=(const char *otro);     
		~Cadena();
		
	private:     
		//size_t tam;
		unsigned long tam;     
		char s_; 
	};
	  
#endif CADENA_HPP
