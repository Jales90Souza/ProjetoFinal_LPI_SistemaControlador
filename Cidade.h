#ifndef CIDADE_H_INCLUDED
#define CIDADE_H_INCLUDED

#include <string>

class Cidade {
    private:
        std::string nome;
    public:
        Cidade(std::string nome);
        std::string getNome();
};

#endif // CIDADE_H_INCLUDED
