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
   std::vector<ElDomino > vecDominos;
   int points;

};

struct ElTableau
{
    std::vector<ElJoueur > vecJoueurs;
    int typeJeu;
};

#endif // DEF_ENUMS
