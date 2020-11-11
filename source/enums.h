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
   std::vector<ElDomino& > *vecDominos;
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

enum TypeMenu
{
    MenuPrincipal,
    MenuSelectTypeJ,
    MenuInstructions,
    MenuPause,
    MenuFinPartie
};

enum
{
    AUCUN_EL_ACT,
    JOUEUR1_ACTIF,
    INSTRUCTIONS_ACTIF,
    SON_ACTIF,
    MENU_ACTIF,
    TYPE1_ACTIF,
    TYPE2_ACTIF,
    TYPE3_ACTIF,
    TYPE4_ACTIF,
    NIVEAU1_ACTIF,
    NIVEAU2_ACTIF,
    NIVEAU3_ACTIF,
    JOUER_ACTIF,
    OK_ACTIF,
    PAUSER_ACTIF,
    PAUSEREJ_ACTIF,
    PAUSEI_ACTIF,
    PAUSEQ_ACTIF,
    FINPQ_ACTIF,
    FINPR_ACTIF
};

enum
{
    AUCUN_B_PRESSE,
    B_INFO,
    B_SON,
    B_JOUEUR1,
    B_OK,
    B_MENU,
    B_TYPE1,
    B_TYPE2,
    B_TYPE3,
    B_TYPE4,
    B_NIVEAU1,
    B_NIVEAU2,
    B_NIVEAU3,
    B_JOUER,
    B_PAUSER,
    B_PAUSEREJ,
    B_PAUSEI,
    B_PAUSEQ,
    B_FINPQ,
    B_FINPR
};

enum
{
    SON_BCLIK,
    SON_AUTORISE,
    SON_INTERDIT
};



#endif // DEF_ENUMS
