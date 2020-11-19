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

    PlateauJeu& getPlateauJeu();
    bool finPartie();
    void gestTextureD(int noDomino,bool visible);
    void gestTexture(int elem);

    bool collisionTS(sf::FloatRect elem);
    bool boutonSelect();
    void gestBouton();

    void gestMaj();

    void affichePartie();
    void afficheBouton();

    ~Joueur();

private:
    sf::RenderWindow* m_fenetre;
    PlateauJeu m_plateauJeu;
    sf::Texture m_tFond,m_tDominos,m_tElements;
    sf::Sprite m_sFond;

    //bouton pause
    sf::Sprite m_sbPause;


};

#endif // DEF_JOUEUR
