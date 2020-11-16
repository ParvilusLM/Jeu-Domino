#include "joueur.h"

Joueur::Joueur(sf::RenderWindow& fenetre):m_fenetre(0)
{
    m_fenetre=&fenetre;

    m_tFond.loadFromFile("donnees/jeuEnCours.png");
    m_tElements.loadFromFile("donnees/bJeuEnCours.png");

    initPlateauJeu();
}

void Joueur::initPlateauJeu()
{
    //creation et injection des dominos dans le vecteur correspondant
    int compt=0;
    while(compt<28)
    {
        ElDomino nouvDomino;
        nouvDomino.angle=0;
        nouvDomino.etat=RETOURNE;
        nouvDomino.noDomino=compt;
        nouvDomino.sDomino.setTexture(m_tElements);
        nouvDomino.cote1=0;
        nouvDomino.cote2=0;

        m_plateauJeu.vecDominos.insert(m_plateauJeu.vecDominos.end(),nouvDomino);

        compt++;
    }

    //mettre les points sur les dominos
    int decompt=7;
    int valeur=0,valeur2=0;

    int indicDomino=0;

    int compt2=0;
    while(compt2<1)
    {
        int compt3=0;
        while(compt3<decompt)
        {
            m_plateauJeu.vecDominos.at(indicDomino).cote1=valeur;
            m_plateauJeu.vecDominos.at(indicDomino).cote2=valeur2;

            indicDomino++;
            valeur2++;
            compt3++;
        }
        valeur++;
        valeur2=valeur;
        decompt--;
        if(decompt<1)
        {
            compt2++;
        }
    }

    //positionner les dominos


    //affiche les dominos
    int compt3=0;
    while(compt3<m_plateauJeu.vecDominos.size())
    {
        std::cout<<"Domino "<<compt3<<" :   "<<m_plateauJeu.vecDominos.at(compt3).cote1<<" , "<<m_plateauJeu.vecDominos.at(compt3).cote2<<std::endl;
        compt3++;
    }


}

void Joueur::melangeDomino()
{

}

void Joueur::distribuerDomino()
{

}

void Joueur::piocherDomino(int joueur)
{

}

void Joueur::selectionDomino(int joueur)
{

}

void Joueur::placerDomino()
{

}

void Joueur::arrangerDomino()
{

}

bool Joueur::finPartie()
{

}

void Joueur::gestTextureD(int noDomino)
{

}

void Joueur::affichePartie()
{

}

Joueur::~Joueur()
{

}
