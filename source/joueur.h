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
    bool selectionDomino(int joueur);
    bool coupPossible(int joueur, int noDomino=-1);
    bool placerDomino(int joueur, int noDominoP,int noDominoE); //noDominoP represente le domino sur lequel on va attacher le nouveau
    void arrangerDomino(); //pour arranger les dominos du vecDomninosPoses dans le cadre
    void retourneDominos(int joueur,bool rendreVisible);
    void changementEchelleD(int categorie,sf::Vector2f facteur);
    void glisserDeposerD(int action);

    PlateauJeu& getPlateauJeu();
    bool finPartie();
    void gestTextureD();

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
