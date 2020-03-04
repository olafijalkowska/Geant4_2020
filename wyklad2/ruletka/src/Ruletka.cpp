#include "Ruletka.h"

Ruletka::Ruletka(std::default_random_engine& engine)
{
    myEngine = engine;
}

Ruletka::~Ruletka() {}

Uczciwa::Uczciwa(std::default_random_engine& engine): Ruletka(engine) {}

Europejska::Europejska(std::default_random_engine& engine): Ruletka(engine) {}

Amerykanska::Amerykanska(std::default_random_engine& engine): Ruletka(engine) {}

int Uczciwa::zakrec()
{

}

int Europejska::zakrec()
{

}

int Amerykanska::zakrec()
{

}



