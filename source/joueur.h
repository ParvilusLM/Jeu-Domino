#ifndef DEF_JOUEUR
#define DEF_JOEUEUR

#include <iostream>
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
    void gestTextureD(int noDomino,bool visible);
    void gestTexture(int elem);

    void affichePartie();

    ~Joueur();

private:
    sf::RenderWindow* m_fenetre;
    PlateauJeu m_plateauJeu;
    sf::Texture m_tFond,m_tDominos,m_tElements;
    sf::Sprite m_sFond;


};

#endif // DEF_JOUEUR
