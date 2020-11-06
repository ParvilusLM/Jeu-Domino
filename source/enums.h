#ifndef DEF_ENUMS
#define DEF_ENUMS

#include <SFML/Graphics.hpp>

struct ElDomino
{
    sf::Sprite sDomino;
    int cote1,cote2;
    int angle;
    bool debord;
};

struct ElJoueur
{
   std::vector<ElDomino& > vecDominos;
   int points;

};

struct PlateauJeu
{
    std::vector<ElJoueur > vecJoueurs;
    std::vector<ElDomino > vecDominos;
    int typeJeu;
};

enum
{
    CPU,
    HUMAIN
};

enum
{
    D_CLASSIQUE,
    D_5PARTOUT,
    D_MATADOR,
    D_MEMORY
};



#endif // DEF_ENUMS
