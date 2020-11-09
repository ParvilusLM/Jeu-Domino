#ifndef DEF_JOUEUR
#define DEF_JOEUEUR

#include "enums.h"
#include "constantes.h"
#include "varG.h"



class Joueur
{
public:
    Joueur(sf::RenderWindow& fenetre);

    void initPlateauJeu();
    void melangeDomino();
    void distribuerDomino();
    void piocherDomino(int joueur);
    void selectionDomino(int joueur);
    void placerDomino();
    void arrangerDomino();

    bool finPartie();




    ~Joueur();


private:
    sf::RenderWindow* m_fenetre;
    PlateauJeu m_plateauJeu;


};

#endif // DEF_JOUEUR
