#include "joueur.h"

Joueur::Joueur(sf::RenderWindow& fenetre):m_fenetre(0)
{
    m_fenetre=&fenetre;

    m_tFond.loadFromFile("donnees/jeuEnCours.png");
    m_tDominos.loadFromFile("donnees/dominos.png");
    m_tElements.loadFromFile("donnees/bJeuEnCours.png");

    m_sFond.setTexture(m_tFond);


}

void Joueur::initPlateauJeu()
{
    m_plateauJeu.vecDominos.clear();
    m_plateauJeu.vecJoueurs.clear();
    m_plateauJeu.vecDominosPoses.clear();
    m_plateauJeu.vecIndicateurs.clear();

    //creation et injection des dominos dans le vecteur correspondant
    int compt=0;
    while(compt<28)
    {
        ElDomino nouvDomino;
        nouvDomino.angle=0;
        nouvDomino.etat=RETOURNE;
        nouvDomino.noDomino=compt;
        nouvDomino.sDomino.setTexture(m_tDominos);
        nouvDomino.sDomino.setTextureRect(sf::IntRect(22*20,27*20,80,160));
        nouvDomino.sDomino.setOrigin(40.f,80.f);
        nouvDomino.sDomino.setPosition(40.f+(compt*30),80.f);
        nouvDomino.sDomino.setScale(0.3f,0.3f);
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

    //gest des joueurs
    int compt3=0;
    while(compt3<2)
    {
        ElJoueur nouvJ;
        nouvJ.points=0;
        nouvJ.sCadreJoueur.setTexture(m_tElements);
        if(compt3==0)
        {

        }

        m_plateauJeu.vecJoueurs.insert(m_plateauJeu.vecJoueurs.end(),nouvJ);

        compt3++;
    }

    //positionner les dominos


    //affiche les dominos
    int compt4=0;
    while(compt4<m_plateauJeu.vecDominos.size())
    {
        std::cout<<"Domino "<<compt4<<" :   "<<m_plateauJeu.vecDominos.at(compt4).cote1<<" , "<<m_plateauJeu.vecDominos.at(compt4).cote2<<std::endl;
        compt4++;
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

void Joueur::gestTextureD(int noDomino,bool visible)
{
    if(visible)
    {
        int pX=noDomino%8;
        int pY=noDomino/8;

        m_plateauJeu.vecDominos.at(noDomino).sDomino.setTextureRect(sf::IntRect((pX*20)+20+(pX*80),(pY*20)+(pY*160),80,160));
    }
    else
    {
        int pX=noDomino%8;
        int pY=noDomino/8;

        m_plateauJeu.vecDominos.at(noDomino).sDomino.setTextureRect(sf::IntRect(22*20,27*20,80,160));
    }

}

void Joueur::gestTexture(int elem)
{

}

void Joueur::affichePartie()
{
    m_fenetre->draw(m_sFond);

    //on affiche les dominos
    int compt=0;
    while(compt<m_plateauJeu.vecDominos.size())
    {
        m_fenetre->draw(m_plateauJeu.vecDominos.at(compt).sDomino);
        compt++;
    }
}

Joueur::~Joueur()
{

}
