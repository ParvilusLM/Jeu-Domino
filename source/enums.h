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
    JOUEUR2_ACTIF,
    INSTRUCTIONS_ACTIF,
    SON_ACTIF,
    MENU_ACTIF,
    GRILLE1_ACTIF,
    GRILLE2_ACTIF,
    GRILLE3_ACTIF,
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
    B_JOUEUR2,
    B_OK,
    B_MENU,
    B_GRILLE1,
    B_GRILLE2,
    B_GRILLE3,
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
