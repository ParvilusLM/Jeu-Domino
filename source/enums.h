#ifndef DEF_ENUMS
#define DEF_ENUMS

#include <SFML/Graphics.hpp>

struct ElDomino
{
    sf::Sprite sDomino;
    int cote1,cote2;
    int angle;
    bool debord;
    int etat;
    int noDomino;

};

struct ElJoueur
{
   std::vector<ElDomino* > vecDominos;
   sf::Sprite sCadreJoueur;
   int points;

};

struct PlateauJeu
{
    std::vector<ElJoueur > vecJoueurs;
    std::vector<ElDomino > vecDominos;
    std::vector<ElDomino* > vecDominosPoses;
    std::vector<sf::Sprite > vecIndicateurs;//pour montrer ou on peut placer le domino selectionne
    sf::Sprite sCadreDAP;//support dominos a piocher
    int typeJeu;
    int niveauJeu;


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
    PREC_ACTIF,
    SUIV_ACTIF,
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
    B_PREC,
    B_SUIV,
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

enum TypeJeuChoisi
{
    AUCUN_TJ,
    TJ_CLASSIQUE,
    TJ_5PARTOUT,
    TJ_MATADOR,
    TJ_MEMORY
};

enum NiveauChoisi
{
    AUCUN_NIV,
    NIV_FACILE,
    NIV_MOYEN,
    NIV_DIFFICILE
};

enum
{
    RETOURNE,
    VISIBLE
};



#endif // DEF_ENUMS
