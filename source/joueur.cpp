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
    m_vecDominoABouger.clear();
    m_plateauJeu.vecDominos.clear();
    m_plateauJeu.vecJoueurs.clear();
    m_plateauJeu.vecDominosPoses.clear();
    m_plateauJeu.vecIndicateurs.clear();
    m_plateauJeu.vecDominosAP.clear();
    m_plateauJeu.vecDominosAuBord.clear();

    //creation et injection des dominos dans le vecteur correspondant
    int compt=0;
    while(compt<28)
    {
        ElDomino nouvDomino;
        nouvDomino.angle=0;
        nouvDomino.etat=RETOURNE;
        nouvDomino.auBord=false;
        nouvDomino.noDomino=compt;
        nouvDomino.selectionne=false;
        nouvDomino.sDomino.setTexture(m_tDominos);
        nouvDomino.sDomino.setTextureRect(sf::IntRect(22*20,27*20,80,160));
        nouvDomino.sDomino.setOrigin(40.f,80.f);
        nouvDomino.sDomino.setPosition(45.f+(compt*30),27*20);
        nouvDomino.sDomino.setScale(0.3f,0.3f);
        nouvDomino.scale=nouvDomino.sDomino.getScale();
        nouvDomino.cote1=0;
        nouvDomino.cote2=0;
        nouvDomino.attacheGP=true;
        nouvDomino.attacheDP=true;
        nouvDomino.attacheHP=true;
        nouvDomino.attacheBP=true;

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
        nouvJ.pass=false;
        nouvJ.sCadreJoueur.setTexture(m_tElements);
        if(compt3==HUMAIN)
        {
            nouvJ.sCadreJoueur.setPosition(8*20,31*20);
            nouvJ.sCadreJoueur.setTextureRect(sf::IntRect(8*20,31*20,30*20,4*20));
        }
        else
        {
            nouvJ.sCadreJoueur.setPosition(10*20,0);
            nouvJ.sCadreJoueur.setTextureRect(sf::IntRect(10*20,0,25*20,4*20));
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
            m_plateauJeu.vecDominosAP.erase(m_plateauJeu.vecDominosAP.begin()+27-indicD);

            m_plateauJeu.vecJoueurs.at(compt).vecDominos.insert(m_plateauJeu.vecJoueurs.at(compt).vecDominos.end(),pDomino);
            compt2++;
            indicD++;
        }
        compt++;
    }
}

void Joueur::piocherDomino(int joueur,int nombreD)
{

}

bool Joueur::selectionDomino(int joueur)
{
    bool dominoSelect=false;
    if(joueur==HUMAIN)
    {
        int compt=0;
        while(compt<m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.size())
        {
            if(collisionTS(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->sDomino.getGlobalBounds()))
            {
                if(m_plateauJeu.vecDominosPoses.size()==0)
                {
                    if(m_plateauJeu.typeJeu==TJ_CLASSIQUE)
                    {
                        if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->cote1 == m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->cote2 ||
                           m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->cote1 != m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->cote2 )
                        {
                            m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->selectionne=true;
                            dominoSelect=true;
                        }
                    }
                    else if(m_plateauJeu.typeJeu==TJ_5PARTOUT)
                    {
                        if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->cote1 == m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->cote2)
                        {
                            m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->selectionne=true;
                            dominoSelect=true;
                        }
                    }
                    else if(m_plateauJeu.typeJeu==TJ_MATADOR)
                    {
                        if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->cote1 + m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->cote2==7 ||
                           m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->cote1 + m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->cote2==0 )
                        {
                            m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->selectionne=true;
                            dominoSelect=true;
                        }
                    }

                }
                else
                {
                    //on va tester les dominos du vecteur vecDominosAuBord avec celui pointe par le curseur
                    if(coupPossible(HUMAIN,*m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)))
                    {
                        m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->selectionne=true;
                        dominoSelect=true;
                    }

                }

            }
            compt++;
        }

    }
    else
    {
        //on va tester chaque domino du vecteur vecJoueur(CPU) pour trouver un coup possible
        if(m_plateauJeu.vecDominosPoses.size()==0)
        {
            int compt=0;
            while(compt<m_plateauJeu.vecJoueurs.at(CPU).vecDominos.size())
            {
                if(m_plateauJeu.typeJeu==TJ_CLASSIQUE)
                {
                    if(m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->cote1 == m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->cote2 ||
                       m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->cote1 != m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->cote2 )
                    {
                        m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->selectionne=true;
                        dominoSelect=true;
                        compt=100;
                    }
                }
                else if(m_plateauJeu.typeJeu==TJ_5PARTOUT)
                {
                    if(m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->cote1 == m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->cote2 )
                    {
                        m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->selectionne=true;
                        dominoSelect=true;
                        compt=100;
                    }
                }
                else if(m_plateauJeu.typeJeu==TJ_MATADOR)
                {
                    if(m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->cote1+m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->cote2==7 ||
                       m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->cote1+m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->cote2==0 )
                    {
                        m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->selectionne=true;
                        dominoSelect=true;
                        compt=100;
                    }
                }
                else
                {

                }

                compt++;
            }
        }
        else
        {
            int comptt=0;
            while(comptt<m_plateauJeu.vecJoueurs.at(CPU).vecDominos.size())
            {
                if(coupPossible(CPU,*m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(comptt)))
                {
                    m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(comptt)->selectionne=true;
                    dominoSelect=true;
                    comptt=100;
                }
                comptt++;
            }
        }
    }
    return dominoSelect;
}

bool Joueur::coupPossible(int joueur, ElDomino& domino)
{
    bool possible=false;
    m_vecDominoABouger.clear();
    std::vector<sf::Vector2i > vecNumCoteValide;//x pour le numero du domino et y pour la valeur du cote

    //on va mettre tout les numeros des cotes valides du vecteur vecDominosAuBord dans le vecteur vecNumCoteValide
    int comp=0;
    while(comp<m_plateauJeu.vecDominosAuBord.size())
    {
        sf::Vector2i nouvDonnees;
        nouvDonnees.x=m_plateauJeu.vecDominosAuBord.at(comp)->noDomino;

        if(m_plateauJeu.vecDominosAuBord.at(comp)->angle==0)
        {
            if(m_plateauJeu.vecDominosAuBord.at(comp)->attacheGP)
            {
                nouvDonnees.y=m_plateauJeu.vecDominosAuBord.at(comp)->cote1;
                vecNumCoteValide.insert(vecNumCoteValide.end(),nouvDonnees);
            }

            if(m_plateauJeu.vecDominosAuBord.at(comp)->attacheDP)
            {
                nouvDonnees.y=m_plateauJeu.vecDominosAuBord.at(comp)->cote2;
                vecNumCoteValide.insert(vecNumCoteValide.end(),nouvDonnees);
            }

            if(m_plateauJeu.vecDominosAuBord.at(comp)->attacheHP)
            {
                nouvDonnees.y=m_plateauJeu.vecDominosAuBord.at(comp)->cote1;
                vecNumCoteValide.insert(vecNumCoteValide.end(),nouvDonnees);
            }

            if(m_plateauJeu.vecDominosAuBord.at(comp)->attacheBP)
            {
                nouvDonnees.y=m_plateauJeu.vecDominosAuBord.at(comp)->cote2;
                vecNumCoteValide.insert(vecNumCoteValide.end(),nouvDonnees);
            }

        }
        else if(m_plateauJeu.vecDominosAuBord.at(comp)->angle==-90)
        {
            if(m_plateauJeu.vecDominosAuBord.at(comp)->attacheGP)
            {
                nouvDonnees.y=m_plateauJeu.vecDominosAuBord.at(comp)->cote1;
                vecNumCoteValide.insert(vecNumCoteValide.end(),nouvDonnees);
            }

            if(m_plateauJeu.vecDominosAuBord.at(comp)->attacheDP)
            {
                nouvDonnees.y=m_plateauJeu.vecDominosAuBord.at(comp)->cote2;
                vecNumCoteValide.insert(vecNumCoteValide.end(),nouvDonnees);
            }

        }
        else if(m_plateauJeu.vecDominosAuBord.at(comp)->angle==90)
        {
            if(m_plateauJeu.vecDominosAuBord.at(comp)->attacheGP)
            {
                nouvDonnees.y=m_plateauJeu.vecDominosAuBord.at(comp)->cote2;
                vecNumCoteValide.insert(vecNumCoteValide.end(),nouvDonnees);
            }

            if(m_plateauJeu.vecDominosAuBord.at(comp)->attacheDP)
            {
                nouvDonnees.y=m_plateauJeu.vecDominosAuBord.at(comp)->cote1;
                vecNumCoteValide.insert(vecNumCoteValide.end(),nouvDonnees);
            }

        }
        else if(m_plateauJeu.vecDominosAuBord.at(comp)->angle==180)
        {
            if(m_plateauJeu.vecDominosAuBord.at(comp)->attacheHP)
            {
                nouvDonnees.y=m_plateauJeu.vecDominosAuBord.at(comp)->cote2;
                vecNumCoteValide.insert(vecNumCoteValide.end(),nouvDonnees);
            }

            if(m_plateauJeu.vecDominosAuBord.at(comp)->attacheBP)
            {
                nouvDonnees.y=m_plateauJeu.vecDominosAuBord.at(comp)->cote1;
                vecNumCoteValide.insert(vecNumCoteValide.end(),nouvDonnees);
            }
        }
        else
        {

        }

        comp++;
    }


    int noJoueur=joueur;

    if(m_plateauJeu.typeJeu==TJ_CLASSIQUE || m_plateauJeu.typeJeu==TJ_5PARTOUT)
    {
        int comptt=0;
        while(comptt<vecNumCoteValide.size())
        {
            if(domino.cote1==vecNumCoteValide.at(comptt).y || domino.cote2==vecNumCoteValide.at(comptt).y)
            {
                m_vecDominoABouger.insert(m_vecDominoABouger.end(),vecNumCoteValide.at(comptt).x);
                possible=true;
            }
            comptt++;
        }
    }
    else if(m_plateauJeu.typeJeu==TJ_MATADOR)
    {
        int compt2=0;
        while(compt2<m_plateauJeu.vecDominosAuBord.size())
        {
        if(m_plateauJeu.vecDominosAuBord.at(compt2)->angle==0)
        {
            if(m_plateauJeu.vecDominosAuBord.at(compt2)->attacheGP)
            {
                if(domino.cote1==0 || domino.cote2==0)
                {
                    m_vecDominoABouger.insert(m_vecDominoABouger.end(),m_plateauJeu.vecDominosAuBord.at(compt2)->noDomino);
                    possible=true;
                }
            }

            if(m_plateauJeu.vecDominosAuBord.at(compt2)->attacheDP)
            {
                if(domino.cote1==0 || domino.cote2==0)
                {
                    m_vecDominoABouger.insert(m_vecDominoABouger.end(),m_plateauJeu.vecDominosAuBord.at(compt2)->noDomino);
                    possible=true;
                }
            }

            if(m_plateauJeu.vecDominosAuBord.at(compt2)->attacheHP)
            {
                if(domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==7 ||
                   domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==0 ||
                   domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==7 ||
                   domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==0)
                {
                    m_vecDominoABouger.insert(m_vecDominoABouger.end(),m_plateauJeu.vecDominosAuBord.at(compt2)->noDomino);
                    possible=true;
                }
            }

            if(m_plateauJeu.vecDominosAuBord.at(compt2)->attacheBP)
            {
                if(domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==7 ||
                   domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==0 ||
                   domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==7 ||
                   domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==0)
                {
                    m_vecDominoABouger.insert(m_vecDominoABouger.end(),m_plateauJeu.vecDominosAuBord.at(compt2)->noDomino);
                    possible=true;
                }
            }

        }
        else if(m_plateauJeu.vecDominosAuBord.at(compt2)->angle==-90)
        {
            if(m_plateauJeu.vecDominosAuBord.at(compt2)->attacheGP)
            {
                if(domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==7 ||
                   domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==0 ||
                   domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==7 ||
                   domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==0)
                {
                    m_vecDominoABouger.insert(m_vecDominoABouger.end(),m_plateauJeu.vecDominosAuBord.at(compt2)->noDomino);
                    possible=true;
                }
            }

            if(m_plateauJeu.vecDominosAuBord.at(compt2)->attacheDP)
            {
                if(domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==7 ||
                   domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==0 ||
                   domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==7 ||
                   domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==0)
                {
                    m_vecDominoABouger.insert(m_vecDominoABouger.end(),m_plateauJeu.vecDominosAuBord.at(compt2)->noDomino);
                    possible=true;
                }
            }

        }
        else if(m_plateauJeu.vecDominosAuBord.at(compt2)->angle==90)
        {
            if(m_plateauJeu.vecDominosAuBord.at(compt2)->attacheGP)
            {
                if(domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==7 ||
                   domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==0 ||
                   domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==7 ||
                   domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==0)
                {
                    m_vecDominoABouger.insert(m_vecDominoABouger.end(),m_plateauJeu.vecDominosAuBord.at(compt2)->noDomino);
                    possible=true;
                }
            }

            if(m_plateauJeu.vecDominosAuBord.at(compt2)->attacheDP)
            {
                if(domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==7 ||
                   domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==0 ||
                   domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==7 ||
                   domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==0)
                {
                    m_vecDominoABouger.insert(m_vecDominoABouger.end(),m_plateauJeu.vecDominosAuBord.at(compt2)->noDomino);
                    possible=true;
                }
            }

        }
        else if(m_plateauJeu.vecDominosAuBord.at(compt2)->angle==180)
        {
            if(m_plateauJeu.vecDominosAuBord.at(compt2)->attacheHP)
            {
                if(domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==7 ||
                   domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==0 ||
                   domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==7 ||
                   domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==0)
                {
                    m_vecDominoABouger.insert(m_vecDominoABouger.end(),m_plateauJeu.vecDominosAuBord.at(compt2)->noDomino);
                    possible=true;
                }
            }

            if(m_plateauJeu.vecDominosAuBord.at(compt2)->attacheBP)
            {
                if(domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==7 ||
                   domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==0 ||
                   domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==7 ||
                   domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==0)
                {
                    m_vecDominoABouger.insert(m_vecDominoABouger.end(),m_plateauJeu.vecDominosAuBord.at(compt2)->noDomino);
                    possible=true;
                }
            }
        }
        else
        {

        }

        compt2++;
    }
    }
    else
    {

    }

    return possible;
}

bool Joueur::placerDomino(int joueur, int noDominoP,int noDominoE)
{
    std::cout<<"Fonction PlacerDomino"<<std::endl;
    bool placerDPossible=false;
    int noJoueur=joueur;

    bool coteG,coteD,coteH,coteB;

    //on determine les cotes valides du domino sur lequel on doit attacher le nouveau
    int compt=0;
    while(compt<m_plateauJeu.vecDominosPoses.size())
    {
        if(m_plateauJeu.vecDominosPoses.at(compt)->noDomino==noDominoP)
        {
            coteG=m_plateauJeu.vecDominosPoses.at(compt)->attacheGP;
            coteD=m_plateauJeu.vecDominosPoses.at(compt)->attacheDP;
            coteH=m_plateauJeu.vecDominosPoses.at(compt)->attacheHP;
            coteB=m_plateauJeu.vecDominosPoses.at(compt)->attacheBP;

        }
        compt++;
    }


    if(m_plateauJeu.typeJeu==TJ_CLASSIQUE || m_plateauJeu.typeJeu==TJ_5PARTOUT)
    {
        //on determine les cotes sur lesquels on peut attacher le nouveau domino
        int compt2=0;
        while(compt2<m_plateauJeu.vecDominosPoses.size())
        {
            if(m_plateauJeu.vecDominosPoses.at(compt2)->noDomino==noDominoP)
            {
                //pointeur sur le domino Enfant et Parent
                ElDomino* pDominoEnfant=m_plateauJeu.vecJoueurs.at(noJoueur).vecDominos.at(noDominoE);
                ElDomino* pDominoParent=m_plateauJeu.vecDominosPoses.at(compt2);


                sf::FloatRect boiteEDomP=m_plateauJeu.vecDominosPoses.at(compt2)->sDomino.getGlobalBounds();

                //on place le domino selon cote valide
                if( (coteG && (pDominoParent->cote1==pDominoEnfant->cote1 && pDominoParent->angle==-90)) ||
                    (coteG && (pDominoParent->cote1==pDominoEnfant->cote2 && pDominoParent->angle==-90)) ||
                    (coteG && (pDominoParent->cote2==pDominoEnfant->cote1 && pDominoParent->angle==90)) ||
                    (coteG && (pDominoParent->cote2==pDominoEnfant->cote2 && pDominoParent->angle==90)) ||
                    (coteG && (pDominoParent->cote1==pDominoEnfant->cote1 && pDominoParent->angle==0)) ||
                    (coteG && (pDominoParent->cote1==pDominoEnfant->cote2 && pDominoParent->angle==0)))
                {

                    if(pDominoEnfant->cote1 == pDominoEnfant->cote2) //si c'est un double
                    {
                        pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x-boiteEDomP.width+(boiteEDomP.height/2),
                                                                                                         pDominoParent->sDomino.getPosition().y);
                    }
                    else
                    {
                        if(pDominoParent->cote1 == pDominoParent->cote2)
                        {
                            if(pDominoEnfant->cote1==pDominoParent->cote1)
                            {
                                pDominoEnfant->angle=90.f;
                                pDominoEnfant->sDomino.setRotation(90.f);
                            }
                            else
                            {
                                pDominoEnfant->angle=-90.f;
                                pDominoEnfant->sDomino.setRotation(-90.f);
                            }

                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x-(boiteEDomP.width/2)-(boiteEDomP.height/2),
                                                                                                             pDominoParent->sDomino.getPosition().y);
                        }
                        else
                        {
                            if(pDominoEnfant->cote1==pDominoParent->cote1 && pDominoParent->angle==-90.f)
                            {
                                pDominoEnfant->angle=90.f;
                                pDominoEnfant->sDomino.setRotation(90.f);
                            }
                            else if(pDominoEnfant->cote1==pDominoParent->cote2 && pDominoParent->angle==90.f)
                            {
                                pDominoEnfant->angle=90.f;
                                pDominoEnfant->sDomino.setRotation(90.f);
                            }
                            else if(pDominoEnfant->cote2==pDominoParent->cote1 && pDominoParent->angle==-90.f)
                            {
                                pDominoEnfant->angle=-90.f;
                                pDominoEnfant->sDomino.setRotation(-90.f);
                            }
                            else
                            {
                                pDominoEnfant->angle=-90.f;
                                pDominoEnfant->sDomino.setRotation(-90.f);
                            }

                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x-boiteEDomP.width,
                                                                                                             pDominoParent->sDomino.getPosition().y);
                        }
                    }

                    coteG=false;
                    pDominoParent->attacheGP=false;
                    pDominoEnfant->attacheDP=false;
                    pDominoEnfant->attacheHP=false;
                    pDominoEnfant->attacheBP=false;
                    placerDPossible=true;
                }
                else if( (coteD && (pDominoParent->cote1==pDominoEnfant->cote1 && pDominoParent->angle==90)) ||
                    (coteD && (pDominoParent->cote1==pDominoEnfant->cote2 && pDominoParent->angle==90)) ||
                    (coteD && (pDominoParent->cote2==pDominoEnfant->cote1 && pDominoParent->angle==-90)) ||
                    (coteD && (pDominoParent->cote2==pDominoEnfant->cote2 && pDominoParent->angle==-90)) ||
                    (coteD && (pDominoParent->cote1==pDominoEnfant->cote1 && pDominoParent->angle==0)) ||
                    (coteD && (pDominoParent->cote1==pDominoEnfant->cote2 && pDominoParent->angle==0))  )
                {
                    if(pDominoEnfant->cote1 == pDominoEnfant->cote2) //si c'est un double
                    {
                        pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x+boiteEDomP.width-(boiteEDomP.height/2),
                                                                                                         pDominoParent->sDomino.getPosition().y);
                    }
                    else
                    {
                        if(pDominoParent->cote1 == pDominoParent->cote2)
                        {
                            if(pDominoEnfant->cote1==pDominoParent->cote1)
                            {
                                pDominoEnfant->angle=-90.f;
                                pDominoEnfant->sDomino.setRotation(-90.f);
                            }
                            else
                            {
                                pDominoEnfant->angle=90.f;
                                pDominoEnfant->sDomino.setRotation(90.f);
                            }

                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x+(boiteEDomP.width/2)+(boiteEDomP.height/2),
                                                                                                             pDominoParent->sDomino.getPosition().y);
                        }
                        else
                        {
                            if(pDominoEnfant->cote1==pDominoParent->cote1 && pDominoParent->angle==90.f)
                            {
                                pDominoEnfant->angle=-90.f;
                                pDominoEnfant->sDomino.setRotation(-90.f);
                            }
                            else if(pDominoEnfant->cote1==pDominoParent->cote2 && pDominoParent->angle==-90.f)
                            {
                                pDominoEnfant->angle=-90.f;
                                pDominoEnfant->sDomino.setRotation(-90.f);
                            }
                            else if(pDominoEnfant->cote2==pDominoParent->cote1 && pDominoParent->angle==90.f)
                            {
                                pDominoEnfant->angle=90.f;
                                pDominoEnfant->sDomino.setRotation(90.f);
                            }
                            else
                            {
                                pDominoEnfant->angle=90.f;
                                pDominoEnfant->sDomino.setRotation(90.f);
                            }

                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x+boiteEDomP.width,
                                                                                                             pDominoParent->sDomino.getPosition().y);
                        }
                    }

                    coteD=false;
                    pDominoParent->attacheDP=false;
                    pDominoEnfant->attacheGP=false;
                    pDominoEnfant->attacheHP=false;
                    pDominoEnfant->attacheBP=false;
                    placerDPossible=true;
                }
                else if((coteH && (pDominoParent->cote2==pDominoEnfant->cote1 && pDominoParent->angle==180)) ||
                    (coteH && (pDominoParent->cote2==pDominoEnfant->cote2 && pDominoParent->angle==180)) ||
                    (coteH && (pDominoParent->cote2==pDominoEnfant->cote1 && pDominoParent->angle==90)) ||
                    (coteH && (pDominoParent->cote2==pDominoEnfant->cote2 && pDominoParent->angle==90)) ||
                    (coteH && (pDominoParent->cote1==pDominoEnfant->cote1 && pDominoParent->angle==0)) ||
                    (coteH && (pDominoParent->cote1==pDominoEnfant->cote2 && pDominoParent->angle==0)))
                {
                    if(pDominoEnfant->cote1 == pDominoEnfant->cote2) //si c'est un double
                    {
                        pDominoEnfant->angle=90.f;
                        pDominoEnfant->sDomino.setRotation(90.f);

                        pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                                                         pDominoParent->sDomino.getPosition().y -(boiteEDomP.height/2)-(boiteEDomP.width/2));
                    }
                    else
                    {
                        if(pDominoParent->cote1 == pDominoParent->cote2)
                        {
                            if(pDominoEnfant->cote1==pDominoParent->cote1)
                            {
                                pDominoEnfant->angle=180.f;
                                pDominoEnfant->sDomino.setRotation(180.f);
                            }

                            if(pDominoParent->angle==0.f)
                            {
                                pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                                                             pDominoParent->sDomino.getPosition().y-boiteEDomP.height);
                            }
                            else
                            {
                                pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                                                             pDominoParent->sDomino.getPosition().y-(boiteEDomP.height/2)-(boiteEDomP.width/2) );
                            }

                        }
                        else
                        {
                            if(pDominoEnfant->cote1==pDominoParent->cote1 && pDominoParent->angle==0.f)
                            {
                                pDominoEnfant->angle=180.f;
                                pDominoEnfant->sDomino.setRotation(180.f);
                            }
                            else if(pDominoEnfant->cote2==pDominoParent->cote1 && pDominoParent->angle==0.f)
                            {
                                pDominoEnfant->angle=0.f;
                                pDominoEnfant->sDomino.setRotation(0.f);
                            }
                            else if(pDominoEnfant->cote1==pDominoParent->cote2 && pDominoParent->angle==180.f)
                            {
                                pDominoEnfant->angle=180.f;
                                pDominoEnfant->sDomino.setRotation(180.f);
                            }
                            else
                            {
                                pDominoEnfant->angle=0.f;
                                pDominoEnfant->sDomino.setRotation(0.f);
                            }

                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                                                             pDominoParent->sDomino.getPosition().y-boiteEDomP.height);
                        }
                    }
                    coteH=false;
                    pDominoParent->attacheHP=false;
                    pDominoEnfant->attacheBP=false;
                    pDominoEnfant->attacheGP=false;
                    pDominoEnfant->attacheDP=false;
                    placerDPossible=true;
                }
                else if((coteB && (pDominoParent->cote2==pDominoEnfant->cote1 && pDominoParent->angle==180)) ||
                    (coteB && (pDominoParent->cote2==pDominoEnfant->cote2 && pDominoParent->angle==180)) ||
                    (coteB && (pDominoParent->cote2==pDominoEnfant->cote1 && pDominoParent->angle==90)) ||
                    (coteB && (pDominoParent->cote2==pDominoEnfant->cote2 && pDominoParent->angle==90)) ||
                    (coteB && (pDominoParent->cote1==pDominoEnfant->cote1 && pDominoParent->angle==0)) ||
                    (coteB && (pDominoParent->cote1==pDominoEnfant->cote2 && pDominoParent->angle==0)))
                {
                    if(pDominoEnfant->cote1 == pDominoEnfant->cote2) //si c'est un double
                    {
                        pDominoEnfant->angle=90.f;
                        pDominoEnfant->sDomino.setRotation(90.f);

                        pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                                                         pDominoParent->sDomino.getPosition().y +(boiteEDomP.height/2)+(boiteEDomP.width/2));
                    }
                    else
                    {
                        if(pDominoParent->cote1 == pDominoParent->cote2)
                        {
                            if(pDominoEnfant->cote1==pDominoParent->cote1)
                            {
                                pDominoEnfant->angle=0.f;
                                pDominoEnfant->sDomino.setRotation(0.f);
                            }
                            else
                            {
                                pDominoEnfant->angle=180.f;
                                pDominoEnfant->sDomino.setRotation(180.f);
                            }

                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                                                             pDominoParent->sDomino.getPosition().y+(boiteEDomP.width/2)+(boiteEDomP.height/2));
                        }
                        else
                        {
                            if(pDominoEnfant->cote1==pDominoParent->cote2 && pDominoParent->angle==0.f)
                            {
                                pDominoEnfant->angle=0.f;
                                pDominoEnfant->sDomino.setRotation(0.f);
                            }
                            else if(pDominoEnfant->cote2==pDominoParent->cote2 && pDominoParent->angle==0.f)
                            {
                                pDominoEnfant->angle=180.f;
                                pDominoEnfant->sDomino.setRotation(180.f);
                            }
                            else if(pDominoEnfant->cote1==pDominoParent->cote1 && pDominoParent->angle==180.f)
                            {
                                pDominoEnfant->angle=0.f;
                                pDominoEnfant->sDomino.setRotation(0.f);
                            }
                            else
                            {
                                pDominoEnfant->angle=180.f;
                                pDominoEnfant->sDomino.setRotation(180.f);
                            }

                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                                                             pDominoParent->sDomino.getPosition().y+boiteEDomP.height);
                        }
                    }


                    coteB=false;
                    pDominoParent->attacheBP=false;
                    pDominoEnfant->attacheHP=false;
                    pDominoEnfant->attacheGP=false;
                    pDominoEnfant->attacheDP=false;
                    placerDPossible=true;
                }
                else
                {

                }

                //test pour savoir si on doit enlever le domino parent du vecteur vecDominosAuBord
                if(!coteG && !coteD && !coteH && !coteB)
                {

                    int indicDernEl=m_plateauJeu.vecDominosAuBord.size()-1;
                    int comp=0;
                    while(comp<m_plateauJeu.vecDominosAuBord.size())
                    {
                        if(m_plateauJeu.vecDominosAuBord.at(indicDernEl)->noDomino==noDominoP)
                        {
                            std::cout<<"on enleve un domino dans le vecteur vecDominosAuBord"<<std::endl;
                            m_plateauJeu.vecDominosAuBord.erase(m_plateauJeu.vecDominosAuBord.begin()+indicDernEl);
                        }
                        indicDernEl--;
                        comp++;
                    }
                }

            }
            compt2++;
        }

    }
    else if(m_plateauJeu.typeJeu==TJ_MATADOR)
    {

        //on determine les cotes sur lesquels on peut attacher le nouveau domino
        int compt2=0;
        while(compt2<m_plateauJeu.vecDominosPoses.size())
        {
            if(m_plateauJeu.vecDominosPoses.at(compt2)->noDomino==noDominoP)
            {
                //pointeur sur le domino Enfant et Parent
                ElDomino* pDominoEnfant=m_plateauJeu.vecJoueurs.at(noJoueur).vecDominos.at(noDominoE);
                ElDomino* pDominoParent=m_plateauJeu.vecDominosPoses.at(compt2);

                sf::FloatRect boiteEDomP=m_plateauJeu.vecDominosPoses.at(compt2)->sDomino.getGlobalBounds();

                //on place le domino selon cote valide
                if( (coteG && (pDominoParent->cote1+pDominoEnfant->cote1==7 && pDominoParent->angle==-90)) ||
                    (coteG && (pDominoParent->cote1+pDominoEnfant->cote2==7 && pDominoParent->angle==-90)) ||
                    (coteG && (pDominoParent->cote2+pDominoEnfant->cote1==7 && pDominoParent->angle==90)) ||
                    (coteG && (pDominoParent->cote2+pDominoEnfant->cote2==7 && pDominoParent->angle==90)) ||
                    (coteG && (pDominoParent->cote1+pDominoEnfant->cote1==0 && pDominoParent->angle==-90)) ||
                    (coteG && (pDominoParent->cote1+pDominoEnfant->cote2==0 && pDominoParent->angle==-90)) ||
                    (coteG && (pDominoParent->cote2+pDominoEnfant->cote1==0 && pDominoParent->angle==90)) ||
                    (coteG && (pDominoParent->cote2+pDominoEnfant->cote2==0 && pDominoParent->angle==90)) ||
                    (coteG && (pDominoEnfant->cote1==0 && pDominoParent->angle==0)) ||
                    (coteG && (pDominoEnfant->cote2==0 && pDominoParent->angle==0)) ||
                    (coteG && (pDominoEnfant->cote1+pDominoEnfant->cote2==7 && (pDominoParent->angle==90 || pDominoParent->angle==-90) )) ||
                    (coteG && (pDominoEnfant->cote1+pDominoEnfant->cote2==0 && (pDominoParent->angle==90 || pDominoParent->angle==-90) )) )
                {

                    if( (pDominoEnfant->cote1 + pDominoEnfant->cote2 ==7  ||
                       pDominoEnfant->cote1 + pDominoEnfant->cote2 ==0) &&
                       (pDominoParent->cote1+pDominoParent->cote2!=7 && pDominoParent->cote1+pDominoParent->cote2!=0)  )
                    {
                        pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x-boiteEDomP.width+(boiteEDomP.height/2),
                                                                                                         pDominoParent->sDomino.getPosition().y);
                    }
                    else
                    {
                        if(pDominoParent->cote1 + pDominoParent->cote2==7 ||
                           pDominoParent->cote1 + pDominoParent->cote2==0)
                        {
                            if(pDominoEnfant->cote1==0)
                            {
                                pDominoEnfant->angle=90.f;
                                pDominoEnfant->sDomino.setRotation(90.f);
                            }
                            else
                            {
                                pDominoEnfant->angle=-90.f;
                                pDominoEnfant->sDomino.setRotation(-90.f);
                            }

                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x-(boiteEDomP.width/2)-(boiteEDomP.height/2),
                                                                                                             pDominoParent->sDomino.getPosition().y);
                        }
                        else
                        {
                            if( (pDominoEnfant->cote1+pDominoParent->cote1==7 && pDominoParent->angle==-90.f) ||
                               (pDominoEnfant->cote1+pDominoParent->cote1==0 && pDominoParent->angle==-90.f) )
                            {
                                pDominoEnfant->angle=90.f;
                                pDominoEnfant->sDomino.setRotation(90.f);
                            }
                            else if( (pDominoEnfant->cote1+pDominoParent->cote2==7 && pDominoParent->angle==90.f) ||
                                    (pDominoEnfant->cote1+pDominoParent->cote2==0 && pDominoParent->angle==90.f) )
                            {
                                pDominoEnfant->angle=90.f;
                                pDominoEnfant->sDomino.setRotation(90.f);
                            }
                            else if( (pDominoEnfant->cote2+pDominoParent->cote1==7 && pDominoParent->angle==-90.f) ||
                                    (pDominoEnfant->cote2+pDominoParent->cote1==0 && pDominoParent->angle==-90.f) )
                            {
                                pDominoEnfant->angle=-90.f;
                                pDominoEnfant->sDomino.setRotation(-90.f);
                            }
                            else
                            {
                                pDominoEnfant->angle=-90.f;
                                pDominoEnfant->sDomino.setRotation(-90.f);
                            }

                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x-boiteEDomP.width,
                                                                                                             pDominoParent->sDomino.getPosition().y);
                        }
                    }

                    coteG=false;
                    pDominoParent->attacheGP=false;
                    pDominoEnfant->attacheDP=false;
                    pDominoEnfant->attacheHP=false;
                    pDominoEnfant->attacheBP=false;
                    placerDPossible=true;
                }
                else if( (coteD && (pDominoParent->cote1+pDominoEnfant->cote1==7 && pDominoParent->angle==90)) ||
                    (coteD && (pDominoParent->cote1+pDominoEnfant->cote2==7 && pDominoParent->angle==90)) ||
                    (coteD && (pDominoParent->cote2+pDominoEnfant->cote1==7 && pDominoParent->angle==-90)) ||
                    (coteD && (pDominoParent->cote2+pDominoEnfant->cote2==7 && pDominoParent->angle==-90)) ||
                    (coteD && (pDominoParent->cote1+pDominoEnfant->cote1==0 && pDominoParent->angle==90)) ||
                    (coteD && (pDominoParent->cote1+pDominoEnfant->cote2==0 && pDominoParent->angle==90)) ||
                    (coteD && (pDominoParent->cote2+pDominoEnfant->cote1==0 && pDominoParent->angle==-90)) ||
                    (coteD && (pDominoParent->cote2+pDominoEnfant->cote2==0 && pDominoParent->angle==-90)) ||
                    (coteD && (pDominoEnfant->cote1==0 && pDominoParent->angle==0)) ||
                    (coteD && (pDominoEnfant->cote2==0 && pDominoParent->angle==0)) ||
                    (coteD && (pDominoEnfant->cote1+pDominoEnfant->cote2==7 && (pDominoParent->angle==90 || pDominoParent->angle==-90) )) ||
                    (coteD && (pDominoEnfant->cote1+pDominoEnfant->cote2==0 && (pDominoParent->angle==90 || pDominoParent->angle==-90) ))   )
                {
                    if((pDominoEnfant->cote1 + pDominoEnfant->cote2 ==7  ||
                       pDominoEnfant->cote1 + pDominoEnfant->cote2 ==0) &&
                       (pDominoParent->cote1+pDominoParent->cote2!=7 && pDominoParent->cote1+pDominoParent->cote2!=0))
                    {
                        pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x+boiteEDomP.width-(boiteEDomP.height/2),
                                                                                                         pDominoParent->sDomino.getPosition().y);
                    }
                    else
                    {
                        if(pDominoParent->cote1 + pDominoParent->cote2==7 ||
                           pDominoParent->cote1 + pDominoParent->cote2==0)
                        {
                            if(pDominoEnfant->cote1==0)
                            {
                                pDominoEnfant->angle=-90.f;
                                pDominoEnfant->sDomino.setRotation(-90.f);
                            }
                            else
                            {
                                pDominoEnfant->angle=90.f;
                                pDominoEnfant->sDomino.setRotation(90.f);
                            }

                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x+(boiteEDomP.width/2)+(boiteEDomP.height/2),
                                                                                                             pDominoParent->sDomino.getPosition().y);
                        }
                        else
                        {
                            if( (pDominoEnfant->cote1+pDominoParent->cote1==7 && pDominoParent->angle==90.f) ||
                               (pDominoEnfant->cote1+pDominoParent->cote1==0 && pDominoParent->angle==90.f) )
                            {
                                pDominoEnfant->angle=-90.f;
                                pDominoEnfant->sDomino.setRotation(-90.f);
                            }
                            else if( (pDominoEnfant->cote2+pDominoParent->cote2==7 && pDominoParent->angle==90.f) ||
                                    (pDominoEnfant->cote2+pDominoParent->cote2==0 && pDominoParent->angle==90.f) )
                            {
                                pDominoEnfant->angle=90.f;
                                pDominoEnfant->sDomino.setRotation(90.f);
                            }
                            else if( (pDominoEnfant->cote1+pDominoParent->cote2==7 && pDominoParent->angle==-90.f) ||
                                    (pDominoEnfant->cote1+pDominoParent->cote2==0 && pDominoParent->angle==-90.f) )
                            {
                                pDominoEnfant->angle=-90.f;
                                pDominoEnfant->sDomino.setRotation(-90.f);
                            }
                            else
                            {
                                pDominoEnfant->angle=90.f;
                                pDominoEnfant->sDomino.setRotation(90.f);
                            }

                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x+boiteEDomP.width,
                                                                                                             pDominoParent->sDomino.getPosition().y);
                        }
                    }

                    coteD=false;
                    pDominoParent->attacheDP=false;
                    pDominoEnfant->attacheGP=false;
                    pDominoEnfant->attacheHP=false;
                    pDominoEnfant->attacheBP=false;
                    placerDPossible=true;
                }
                else if((coteH && (pDominoParent->cote2+pDominoEnfant->cote1==7 && pDominoParent->angle==180)) ||
                    (coteH && (pDominoParent->cote2+pDominoEnfant->cote2==7 && pDominoParent->angle==180)) ||
                    (coteH && (pDominoParent->cote1+pDominoEnfant->cote1==7 && pDominoParent->angle==0)) ||
                    (coteH && (pDominoParent->cote1+pDominoEnfant->cote2==7 && pDominoParent->angle==0)) ||
                    (coteH && (pDominoParent->cote2+pDominoEnfant->cote1==0 && pDominoParent->angle==180)) ||
                    (coteH && (pDominoParent->cote2+pDominoEnfant->cote2==0 && pDominoParent->angle==180)) ||
                    (coteH && (pDominoParent->cote1+pDominoEnfant->cote1==0 && pDominoParent->angle==0)) ||
                    (coteH && (pDominoParent->cote1+pDominoEnfant->cote2==0 && pDominoParent->angle==0)) ||
                    (coteH && (pDominoEnfant->cote1==0 && pDominoParent->angle==90)) ||
                    (coteH && (pDominoEnfant->cote2==0 && pDominoParent->angle==90)) ||
                    (coteH && (pDominoParent->cote1+pDominoEnfant->cote1==0 && pDominoParent->angle==0)) ||
                    (coteH && (pDominoParent->cote1+pDominoEnfant->cote2==0 && pDominoParent->angle==0)) ||
                    (coteH && (pDominoEnfant->cote1+pDominoEnfant->cote2==7 && (pDominoParent->angle==0 || pDominoParent->angle==180) )) ||
                    (coteH && (pDominoEnfant->cote1+pDominoEnfant->cote2==0 && (pDominoParent->angle==0 || pDominoParent->angle==180) )) )
                {
                    if((pDominoEnfant->cote1 + pDominoEnfant->cote2 ==7  ||
                       pDominoEnfant->cote1 + pDominoEnfant->cote2 ==0) &&
                       (pDominoParent->cote1+pDominoParent->angle==0.f || pDominoParent->cote1+pDominoParent->angle==180.f))
                    {
                        pDominoEnfant->angle=90.f;
                        pDominoEnfant->sDomino.setRotation(90.f);
                        pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                                                         pDominoParent->sDomino.getPosition().y - boiteEDomP.height - (boiteEDomP.width/2) );
                    }
                    else
                    {
                        if((pDominoParent->cote1 + pDominoParent->cote2==7 ||
                           pDominoParent->cote1 + pDominoParent->cote2==0) &&
                           pDominoParent->cote1 + pDominoParent->angle==90.f)
                        {
                            if(pDominoEnfant->cote1==0)
                            {
                                pDominoEnfant->angle=180.f;
                                pDominoEnfant->sDomino.setRotation(180.f);
                            }

                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                                                             pDominoParent->sDomino.getPosition().y -(boiteEDomP.width/2)-(boiteEDomP.height/2));
                        }
                        else
                        {
                            if( (pDominoEnfant->cote1+pDominoParent->cote1==7 && pDominoParent->angle==0.f) ||
                               (pDominoEnfant->cote1+pDominoParent->cote1==0 && pDominoParent->angle==0.f) )
                            {
                                pDominoEnfant->angle=180.f;
                                pDominoEnfant->sDomino.setRotation(180.f);
                            }
                            else if( (pDominoEnfant->cote2+pDominoParent->cote2==7 && pDominoParent->angle==180.f) ||
                                    (pDominoEnfant->cote2+pDominoParent->cote2==0 && pDominoParent->angle==180.f) )
                            {
                                pDominoEnfant->angle=0.f;
                                pDominoEnfant->sDomino.setRotation(0.f);
                            }
                            else if( (pDominoEnfant->cote1+pDominoParent->cote2==7 && pDominoParent->angle==180.f) ||
                                    (pDominoEnfant->cote1+pDominoParent->cote2==0 && pDominoParent->angle==180.f) )
                            {
                                pDominoEnfant->angle=180.f;
                                pDominoEnfant->sDomino.setRotation(180.f);
                            }
                            else
                            {
                                pDominoEnfant->angle=0.f;
                                pDominoEnfant->sDomino.setRotation(0.f);
                            }

                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                                                             pDominoParent->sDomino.getPosition().y-boiteEDomP.height);
                        }
                    }
                    coteH=false;
                    pDominoParent->attacheHP=false;
                    pDominoEnfant->attacheBP=false;
                    pDominoEnfant->attacheGP=false;
                    pDominoEnfant->attacheDP=false;
                    placerDPossible=true;
                }
                else if((coteB && (pDominoParent->cote2+pDominoEnfant->cote1==7 && pDominoParent->angle==180)) ||
                    (coteB && (pDominoParent->cote2+pDominoEnfant->cote2==7 && pDominoParent->angle==180)) ||
                    (coteB && (pDominoParent->cote2+pDominoEnfant->cote1==7 && pDominoParent->angle==0)) ||
                    (coteB && (pDominoParent->cote2+pDominoEnfant->cote2==7 && pDominoParent->angle==0)) ||
                    (coteB && (pDominoParent->cote2+pDominoEnfant->cote1==0 && pDominoParent->angle==180)) ||
                    (coteB && (pDominoParent->cote2+pDominoEnfant->cote2==0 && pDominoParent->angle==180)) ||
                    (coteH && (pDominoParent->cote1+pDominoEnfant->cote1==0 && pDominoParent->angle==0)) ||
                    (coteH && (pDominoParent->cote1+pDominoEnfant->cote2==0 && pDominoParent->angle==0)) ||
                    (coteB && (pDominoEnfant->cote1==0 && pDominoParent->angle==90)) ||
                    (coteB && (pDominoEnfant->cote2==0 && pDominoParent->angle==90)) ||
                    (coteB && (pDominoParent->cote2+pDominoEnfant->cote1==0 && pDominoParent->angle==0)) ||
                    (coteB && (pDominoParent->cote2+pDominoEnfant->cote2==0 && pDominoParent->angle==0)) ||
                    (coteB && (pDominoEnfant->cote1+pDominoEnfant->cote2==7 && (pDominoParent->angle==0 || pDominoParent->angle==180) )) ||
                    (coteB && (pDominoEnfant->cote1+pDominoEnfant->cote2==0 && (pDominoParent->angle==0 || pDominoParent->angle==180) )) )
                {
                    if((pDominoEnfant->cote1 + pDominoEnfant->cote2 ==7  ||
                       pDominoEnfant->cote1 + pDominoEnfant->cote2 ==0) &&
                       (pDominoParent->cote1+pDominoParent->angle==0.f || pDominoParent->cote1+pDominoParent->angle==180.f))
                    {
                        pDominoEnfant->angle=90.f;
                        pDominoEnfant->sDomino.setRotation(90.f);
                        pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                                                         pDominoParent->sDomino.getPosition().y + boiteEDomP.height + (boiteEDomP.width/2) );
                    }
                    else
                    {
                        if((pDominoParent->cote1 + pDominoParent->cote2==7 ||
                           pDominoParent->cote1 + pDominoParent->cote2==0) &&
                           pDominoParent->cote1 + pDominoParent->angle==90.f)
                        {
                            if(pDominoEnfant->cote1==0)
                            {
                                pDominoEnfant->angle=180.f;
                                pDominoEnfant->sDomino.setRotation(180.f);
                            }

                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                                                             pDominoParent->sDomino.getPosition().y +(boiteEDomP.width/2)+(boiteEDomP.height/2));
                        }
                        else
                        {
                            if( (pDominoEnfant->cote1+pDominoParent->cote1==7 && pDominoParent->angle==180.f) ||
                               (pDominoEnfant->cote1+pDominoParent->cote1==0 && pDominoParent->angle==180.f) )
                            {
                                pDominoEnfant->angle=0.f;
                                pDominoEnfant->sDomino.setRotation(0.f);
                            }
                            else if( (pDominoEnfant->cote2+pDominoParent->cote2==7 && pDominoParent->angle==0.f) ||
                                    (pDominoEnfant->cote2+pDominoParent->cote2==0 && pDominoParent->angle==0.f) )
                            {
                                pDominoEnfant->angle=180.f;
                                pDominoEnfant->sDomino.setRotation(180.f);
                            }
                            else if( (pDominoEnfant->cote1+pDominoParent->cote2==7 && pDominoParent->angle==0.f) ||
                                    (pDominoEnfant->cote1+pDominoParent->cote2==0 && pDominoParent->angle==0.f) )
                            {
                                pDominoEnfant->angle=0.f;
                                pDominoEnfant->sDomino.setRotation(0.f);
                            }
                            else
                            {
                                pDominoEnfant->angle=180.f;
                                pDominoEnfant->sDomino.setRotation(180.f);
                            }

                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                                                             pDominoParent->sDomino.getPosition().y + boiteEDomP.height);
                        }
                    }

                    coteB=false;
                    pDominoParent->attacheBP=false;
                    pDominoEnfant->attacheHP=false;
                    pDominoEnfant->attacheGP=false;
                    pDominoEnfant->attacheDP=false;
                    placerDPossible=true;
                }
                else
                {

                }

                //test pour savoir si on doit enlever le domino parent du vecteur vecDominosAuBord
                if(!coteG && !coteD && !coteH && !coteB)
                {

                    int indicDernEl=m_plateauJeu.vecDominosAuBord.size()-1;
                    int comp=0;
                    while(comp<m_plateauJeu.vecDominosAuBord.size())
                    {
                        if(m_plateauJeu.vecDominosAuBord.at(indicDernEl)->noDomino==noDominoP)
                        {
                            m_plateauJeu.vecDominosAuBord.erase(m_plateauJeu.vecDominosAuBord.begin()+indicDernEl);
                        }
                        indicDernEl--;
                        comp++;
                    }
                }

            }
            compt2++;
        }


    }
    else
    {

    }


    return placerDPossible;
}

void Joueur::arrangerDomino()
{

}

void Joueur::retourneDominos(int joueur,bool rendreVisible)
{
    if(joueur==HUMAIN)
    {
        int compt=0;
        while(compt<m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.size())
        {
            m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->etat=VISIBLE;
            compt++;
        }
    }
    else if(joueur==CPU)
    {
        int compt=0;
        while(compt<m_plateauJeu.vecJoueurs.at(CPU).vecDominos.size())
        {
            m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->etat=VISIBLE;
            compt++;
        }
    }
    else
    {

    }
    gestTextureD();
}

void Joueur::changementEchelleD(int categorie,sf::Vector2f facteur)
{
    if(categorie==DOMINOS_VECDOMINOSAP)
    {
        int compt=0;
        while(compt<m_plateauJeu.vecDominosAP.size())
        {
            m_plateauJeu.vecDominosAP.at(compt)->scale=facteur;
            m_plateauJeu.vecDominosAP.at(compt)->sDomino.setScale(facteur);
            compt++;
        }
    }
    else if(categorie==DOMINOS_JOUEUR1)
    {
        int compt=0;
        while(compt<m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.size())
        {
            m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->scale=facteur;
            m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->sDomino.setScale(facteur);
            compt++;
        }
    }
    else
    {
        int compt=0;
        while(compt<m_plateauJeu.vecJoueurs.at(CPU).vecDominos.size())
        {
            m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->scale=facteur;
            m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->sDomino.setScale(facteur);
            compt++;
        }
    }
}

void Joueur::glisserDeposerD(int action)
{
    if(action==GLISSER)
    {
        int compt=0;
        while(compt<m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.size())
        {
            if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->selectionne)
            {
                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->sDomino.setPosition(sourisX,sourisY);
            }
            compt++;
        }
    }
    else
    {
        int indicEl=m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.size()-1;
        int compt=0;
        while(compt<m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.size())
        {
            if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->selectionne)
            {
                if(m_plateauJeu.vecDominosPoses.size()==0)
                {
                    if(m_plateauJeu.typeJeu==TJ_CLASSIQUE || m_plateauJeu.typeJeu==TJ_5PARTOUT)
                    {
                        if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->cote1!=m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->cote2)
                        {
                            m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->angle=90;
                            m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->sDomino.setRotation(90.f);
                            m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->attacheHP=false;
                            m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->attacheBP=false;
                        }
                    }

                    m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->sDomino.setPosition(22.5f*20,17.5f*20);
                    m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->selectionne=false;
                    m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->auBord=true;

                    m_plateauJeu.vecDominosPoses.insert(m_plateauJeu.vecDominosPoses.end(),m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl));
                    m_plateauJeu.vecDominosAuBord.insert(m_plateauJeu.vecDominosAuBord.end(),m_plateauJeu.vecDominosPoses.at(0));
                    m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.erase(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.begin()+indicEl);

                    glisser=false;
                    deposer=false;
                }
                else
                {
                    int compt2=0;
                    while(compt2<m_plateauJeu.vecDominosAuBord.size())
                    {
                        if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->sDomino.getGlobalBounds().intersects(m_plateauJeu.vecDominosAuBord.at(compt2)->sDomino.getGlobalBounds()) )
                        {
                            if(placerDomino(HUMAIN,m_plateauJeu.vecDominosAuBord.at(compt2)->noDomino,indicEl))
                            {
                                //std::cout<<"Ouffff"<<std::endl;
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->selectionne=false;
                                m_plateauJeu.vecDominosPoses.insert(m_plateauJeu.vecDominosPoses.end(),m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl));

                                int dernEl=m_plateauJeu.vecDominosPoses.size()-1;
                                m_plateauJeu.vecDominosAuBord.insert(m_plateauJeu.vecDominosAuBord.end(),m_plateauJeu.vecDominosPoses.at(dernEl));
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.erase(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.begin()+indicEl);


                                glisser=false;
                                deposer=false;
                            }

                            compt2=100;//pour sortir de la boucle
                        }
                        compt2++;
                    }
                    //std::cout<<"Fin action deposer domino"<<std::endl;


                }

                if(glisser){
                    deposer=false;
                }
                else{
                    laMain=false;
                    laMainBot=true;
                }

            }
            indicEl--;
            compt++;
        }
    }

}

PlateauJeu& Joueur::getPlateauJeu()
{
    return m_plateauJeu;
}

bool Joueur::finPartie()
{
    bool termine=false;
    bool aucunDJ1=false,aucunDJ2=false,aucunDPioche=false;

    //on teste si les joueurs n'ont plus de dominos
    if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.size()==0)
    {
        aucunDJ1=true;
    }

    if(m_plateauJeu.vecJoueurs.at(CPU).vecDominos.size()==0)
    {
        aucunDJ2=true;
    }

    if(m_plateauJeu.vecDominosAP.size()==0)
    {
        aucunDPioche=true;
    }

    if(m_plateauJeu.typeJeu==TJ_CLASSIQUE || m_plateauJeu.typeJeu==TJ_5PARTOUT || m_plateauJeu.typeJeu==TJ_MATADOR)
    {
        if(aucunDJ1 || aucunDJ2)
        {
            termine=true;
        }
    }
    else
    {
        if(aucunDPioche)
        {
            termine=true;
        }
    }

    return termine;
}

void Joueur::gestTextureD()
{
    int comptt=0;
    while(comptt<28)
    {
        if(m_plateauJeu.vecDominos.at(comptt).etat==VISIBLE)
        {
            int pX=comptt%8;
            int pY=comptt/8;

            m_plateauJeu.vecDominos.at(comptt).sDomino.setTextureRect(sf::IntRect((pX*20)+20+(pX*80),(pY*20)+(pY*160),80,160));
        }
        else
        {
            m_plateauJeu.vecDominos.at(comptt).sDomino.setTextureRect(sf::IntRect(22*20,27*20,80,160));
        }
        comptt++;
    }

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

    if(!jeuPause && laMain && !laMainBot)
    {
        if(glisser)
        {
            glisserDeposerD(GLISSER);
        }

        if(deposer)
        {
            glisserDeposerD(DEPOSER);
        }

    }
    else if(!jeuPause && !laMain && laMainBot)
    {
        if(m_plateauJeu.typeJeu!=TJ_MEMORY)
        {
            if(selectionDomino(CPU))
            {
                std::cout<<"Domino du Bot selection"<<std::endl;
                int compt=0;
                while(compt<m_plateauJeu.vecJoueurs.at(CPU).vecDominos.size())
                {
                    if(m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->selectionne)
                    {
                        if(placerDomino(CPU,m_vecDominoABouger.at(0),compt) )
                        {
                            m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->selectionne=false;
                            m_plateauJeu.vecDominosPoses.push_back(m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt));

                            int dernEl=m_plateauJeu.vecDominosPoses.size()-1;
                            m_plateauJeu.vecDominosAuBord.push_back(m_plateauJeu.vecDominosPoses.at(dernEl));
                            m_plateauJeu.vecJoueurs.at(CPU).vecDominos.erase(m_plateauJeu.vecJoueurs.at(CPU).vecDominos.begin()+compt);

                            laMain=true;
                            laMainBot=false;
                        }
                        compt+=100;
                    }
                    compt++;
                }
            }
            else
            {
                if(m_plateauJeu.typeJeu==TJ_CLASSIQUE)
                {
                    laMain=true;
                    laMainBot=false;
                }
                else
                {
                    animAActiver=ANIM_PIOCHE_V;
                }

            }
        }
        else
        {

        }

    }
    else
    {

    }

    //...
    if(finPartie())
    {
        jeuFinPartie=true;
    }
}

void Joueur::affichePartie()
{
    m_fenetre->draw(m_sFond);

    //affiche bouton
    afficheBouton();

    //on affiche le support des dominos a piocher
    m_fenetre->draw(m_plateauJeu.sCadreDAP);

    //on va afficher les dominos par categorie : DominosPoses ,DominosAPiocher, DominosJ1, DominosJ2

    //DominosPoses
    int comptt=0;
    while(comptt<m_plateauJeu.vecDominosPoses.size())
    {
        m_fenetre->draw(m_plateauJeu.vecDominosPoses.at(comptt)->sDomino);
        comptt++;
    }

    //DominosAPiocher
    int compt=0;
    while(compt<m_plateauJeu.vecDominosAP.size())
    {
        m_fenetre->draw(m_plateauJeu.vecDominosAP.at(compt)->sDomino);
        compt++;
    }

    //affiche les supports de dominos des joueurs
    int comp=0;
    while(comp<m_plateauJeu.vecJoueurs.size())
    {
        m_fenetre->draw(m_plateauJeu.vecJoueurs.at(comp).sCadreJoueur);
        comp++;
    }

    //DominosJ1
    int compt1=0;
    while(compt1<m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.size())
    {
        m_fenetre->draw(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt1)->sDomino);
        compt1++;
    }

    //DominosJ2
    int compt2=0;
    while(compt2<m_plateauJeu.vecJoueurs.at(CPU).vecDominos.size())
    {
        m_fenetre->draw(m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt2)->sDomino);
        compt2++;
    }

}

void Joueur::afficheBouton()
{
    m_fenetre->draw(m_sbPause);
}

Joueur::~Joueur()
{

}
