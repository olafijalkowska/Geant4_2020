#ifndef RULETKA_H
#define	RULETKA_H
#include <vector>
#include <random>
class Ruletka
{
public:
    Ruletka(std::default_random_engine& engine);
    ~Ruletka();
    virtual int zakrec() = 0;
protected:
    std::default_random_engine myEngine;
};

class Uczciwa: public Ruletka
{
public:
    Uczciwa(std::default_random_engine& engine);
    ~Uczciwa(){};
    //zwraca liczbę losową od 1 do 36
    virtual int zakrec();    
};

class Amerykanska: public Ruletka
{
public:
    Amerykanska(std::default_random_engine& engine);
    ~Amerykanska(){};
    virtual int zakrec();    
};

class Europejska: public Ruletka
{
public:
    Europejska(std::default_random_engine& engine);
    ~Europejska(){};
    virtual int zakrec();
};

#endif
