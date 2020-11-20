#include "joueur.h"

Joueur::Joueur(sf::RenderWindow& fenetre):m_fenetre(0)
{
    m_fenetre=&fenetre;

    m_tFond.loadFromFile("donnees/jeuEnCours.png");
    m_tDominos.loadFromFile("donnees/dominos.png");
    m_tElements.loadFromFile("donnees/bJeuEnCours.png");

    m_sFond.setTexture(m_tFond);

    m_sbPause.setTexture(m_tElements);
    m_sbPause.setPosition(0.5f*20,0.5f*20);
    m_sbPause.setTextureRect(sf::IntRect(0.5*20,0.5*20,3*20,3*20));


}

void Joueur::initPlateauJeu()
{
    m_plateauJeu.vecDominos.clear();
    m_plateauJeu.vecJoueurs.clear();
    m_plateauJeu.vecDominosPoses.clear();
    m_plateauJeu.vecIndicateurs.clear();
    m_plateauJeu.vecDominosAP.clear();

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
        nouvDomino.sDomino.setPosition(45.f+(compt*30),27*20);
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
        if(compt3==CPU)
        {
            nouvJ.sCadreJoueur.setPosition(10*20,0);
            nouvJ.sCadreJoueur.setTextureRect(sf::IntRect(10*20,0,25*20,4*20));
        }
        else
        {
            nouvJ.sCadreJoueur.setPosition(8*20,31*20);
            nouvJ.sCadreJoueur.setTextureRect(sf::IntRect(8*20,31*20,30*20,4*20));
        }

        m_plateauJeu.vecJoueurs.insert(m_plateauJeu.vecJoueurs.end(),nouvJ);

        compt3++;
    }


    //mettre les dominos dans le vecteur correspondant pour piocher
    int comptt=0;
    while(comptt<28)
    {
        ElDomino* pDomino=&m_plateauJeu.vecDominos.at(comptt);
        m_plateauJeu.vecDominosAP.insert(m_plateauJeu.vecDominosAP.end(),pDomino);
        comptt++;
    }

    //on melange les dominos
    melangeDomino();

    //gest support des dominos a piocher
    m_plateauJeu.sCadreDAP.setTexture(m_tElements);
    m_plateauJeu.sCadreDAP.setPosition(1*20,25*20);
    m_plateauJeu.sCadreDAP.setTextureRect(sf::IntRect(1*20,25*20,43*20,4*20));

    //distribuer les dominos
    distribuerDomino();

    //affiche les dominos
    int compt4=0;
    while(compt4<m_plateauJeu.vecDominosAP.size())
    {
        std::cout<<"Domino "<<compt4<<" :   "<<m_plateauJeu.vecDominosAP.at(compt4)->cote1<<" , "<<m_plateauJeu.vecDominosAP.at(compt4)->cote2<<std::endl;
        compt4++;
    }



}

void Joueur::melangeDomino()
{
    int compt=0;
    while(compt<197)
    {
        int nombrAleatoire=rand()%28;
        m_plateauJeu.vecDominosAP.insert(m_plateauJeu.vecDominosAP.end(),m_plateauJeu.vecDominosAP.at(nombrAleatoire));
        m_plateauJeu.vecDominosAP.erase(m_plateauJeu.vecDominosAP.begin()+nombrAleatoire);
        compt++;
    }
}

void Joueur::distribuerDomino()
{
    int indicD=0;
    int compt=0;
    while(compt<2)
    {
        int compt2=0;
        while(compt2<7)
        {
            ElDomino* pDomino=m_plateauJeu.vecDominosAP.at(27-indicD);
            //m_plateauJeu.vecDominosAP.erase(m_plateauJeu.vecDominosAP.begin()+27-indicD);

            m_plateauJeu.vecJoueurs.at(compt).vecDominos.insert(m_plateauJeu.vecJoueurs.at(compt).vecDominos.end(),pDomino);
            compt2++;
            indicD++;
        }
        compt++;
    }

    //std::cout<<"Pointeur reference :  "<<m_plateauJeu.vecJoueurs.at(0).vecDominos.size()<<std::endl;
    //std::cout<<"Pointeur reference :  "<<m_plateauJeu.vecJoueurs.at(1).vecDominos.size()<<std::endl;
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

void Joueur::retourneDominos(int joueur,bool rendreVisible)
{
    if(joueur==HUMAIN)
    {
        int compt=0;
        while(compt<m_plateauJeu.vecJoueurs.at(0).vecDominos.size())
        {
            m_plateauJeu.vecJoueurs.at(0).vecDominos.at(compt)->etat=VISIBLE;
            gestTextureD(m_plateauJeu.vecJoueurs.at(0).vecDominos.at(compt)->noDomino,true);
            compt++;
        }
    }
    else if(joueur==CPU)
    {

    }
    else
    {

    }
}

PlateauJeu& Joueur::getPlateauJeu()
{
    return m_plateauJeu;
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

bool Joueur::collisionTS(sf::FloatRect elem)
{
    bool collision=false;
    if((elem.left<sourisX && elem.left+elem.width>sourisX) &&
       (elem.top<sourisY && elem.top+elem.height>sourisY))
    {
        collision=true;
    }
    return collision;
}

bool Joueur::boutonSelect()
{
    bool select=false;
    if(collisionTS(m_sbPause.getGlobalBounds()))
    {
        select=true;

    }

    return select;
}

void Joueur::gestBouton()
{
    if(!jeuPause)
    {
        if(collisionTS(m_sbPause.getGlobalBounds()))
        {
            m_sbPause.setTextureRect(sf::IntRect(0.5*20,4*20,3*20,3*20));
        }
        else
        {
            m_sbPause.setTextureRect(sf::IntRect(0.5*20,0.5*20,3*20,3*20));
        }
    }
}

void Joueur::gestMaj()
{
    gestBouton();
}

void Joueur::affichePartie()
{
    m_fenetre->draw(m_sFond);

    //affiche bouton
    afficheBouton();

    //on affiche les supports des dominos
    int comp=0;
    while(comp<m_plateauJeu.vecJoueurs.size())
    {
        m_fenetre->draw(m_plateauJeu.vecJoueurs.at(comp).sCadreJoueur);
        comp++;
    }
    m_fenetre->draw(m_plateauJeu.sCadreDAP);

    //on affiche les dominos
    int compt=0;
    while(compt<m_plateauJeu.vecDominos.size())
    {
        m_fenetre->draw(m_plateauJeu.vecDominos.at(compt).sDomino);
        compt++;
    }



}

void Joueur::afficheBouton()
{
    m_fenetre->draw(m_sbPause);
}

Joueur::~Joueur()
{

}
