#include "joueur.h"

// ### CONSTRUCTEUR ###
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

    retardTraitement=false;
}

// ### FONCTION ###

void Joueur::initPlateauJeu()
{
    m_vecDominoABouger.clear();
    m_plateauJeu.vecDominos.clear();
    m_plateauJeu.vecJoueurs.clear();
    m_plateauJeu.vecDominosPoses.clear();
    m_plateauJeu.vecIndicateurs.clear();
    m_plateauJeu.vecDominosAP.clear();
    m_plateauJeu.vecDominosAuBord.clear();

    retardTraitement=false;

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
        nouvJ.piocherD=false;
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


    //on melange les dominos
    melangeDomino();

    //mettre les dominos dans le vecteur correspondant pour piocher
    int comptt=0;
    while(comptt<28)
    {
        ElDomino* pDomino=&m_plateauJeu.vecDominos.at(comptt);
        m_plateauJeu.vecDominosAP.insert(m_plateauJeu.vecDominosAP.end(),pDomino);
        comptt++;
    }


    //gest support des dominos a piocher
    m_plateauJeu.sCadreDAP.setTexture(m_tElements);
    m_plateauJeu.sCadreDAP.setPosition(1*20,25*20);
    m_plateauJeu.sCadreDAP.setTextureRect(sf::IntRect(1*20,25*20,43*20,4*20));

    //distribuer les dominos
    if(m_plateauJeu.typeJeu != TJ_MEMORY)
    {
        distribuerDomino();
    }

    //initialisation des detecteurs
    m_plateauJeu.detecteurG.left=2.f*20;
    m_plateauJeu.detecteurG.top=1.f*20;
    m_plateauJeu.detecteurG.width=0.5f*20;
    m_plateauJeu.detecteurG.height=30.f*20;

    m_plateauJeu.detecteurD.left=42.5f*20;
    m_plateauJeu.detecteurD.top=1.f*20;
    m_plateauJeu.detecteurD.width=0.5f*20;
    m_plateauJeu.detecteurD.height=30.f*20;

    m_plateauJeu.detecteurH.left=1.f*20;
    m_plateauJeu.detecteurH.top=4.f*20;
    m_plateauJeu.detecteurH.width=43.f*20;
    m_plateauJeu.detecteurH.height=0.5f*20;

    m_plateauJeu.detecteurB.left=1.f*20;
    m_plateauJeu.detecteurB.top=30.5f*20;
    m_plateauJeu.detecteurB.width=43.f*20;
    m_plateauJeu.detecteurB.height=0.5*20;

    //...indicateurs prem domino pose
    m_plateauJeu.sIndicPremDom.setTexture(m_tDominos);
    m_plateauJeu.sIndicPremDom.setOrigin(4.1f*20,2.1f*20);
    m_plateauJeu.sIndicPremDom.setPosition(450.f,350.f);
    sf::IntRect placement;
    placement.left=32.f*20;
    placement.top=27.f*20;
    placement.width=8.2f*20;
    placement.height=4.2f*20;
    m_plateauJeu.sIndicPremDom.setTextureRect(placement);
    m_plateauJeu.sIndicPremDom.setScale(0.45f,0.45f);



}

// ### FONCTION ###

void Joueur::melangeDomino()
{
    //on va creer un vecteur avec les positions X que doivent prendre les dominos
    std::vector<float > ensemblePosX;

    for(int comptt=0;comptt<28;comptt++)
    {
        float nouvPosX=45.f+(comptt*30);
        ensemblePosX.push_back(nouvPosX);
    }

    //on va attribuer au hasard des positions aux dominos dans le vecteur vecDominos
    for(int comptt2=0;comptt2<28;comptt2++)
    {
        int nombrAleatoire=rand()%ensemblePosX.size();
        m_plateauJeu.vecDominos.at(comptt2).sDomino.setPosition(ensemblePosX.at(nombrAleatoire),27*20);
        ensemblePosX.erase(ensemblePosX.begin()+nombrAleatoire);

    }


    /*
    int compt=0;
    while(compt<197)
    {
        int nombrAleatoire=rand()%28;
        //on decale les dominos dans la chaine apres celui qu'on va enlever
        for(int compt2=0;compt2<28;compt2++)
        {
            if(compt2>nombrAleatoire)
            {
                m_plateauJeu.vecDominos.at(compt2).sDomino.move(-30.f,0.f);
            }
        }

        m_plateauJeu.vecDominos.at(nombrAleatoire).sDomino.setPosition(45.f+(27*30),27*20);
        m_plateauJeu.vecDominos.push_back(m_plateauJeu.vecDominos.at(nombrAleatoire));
        m_plateauJeu.vecDominos.erase(m_plateauJeu.vecDominos.begin()+nombrAleatoire);
        compt++;
    }

    */
}

// ### FONCTION ###

void Joueur::distribuerDomino()
{

    //on va creer un vecteur de positions des dominos du vecteur vecDominosAP
    std::vector<int > ensemblePos;

    for(int comptt=0;comptt<28;comptt++)
    {
        int nouvPos=comptt;
        ensemblePos.push_back(nouvPos);
    }

    int compt=0;
    while(compt<2)
    {
        int compt2=0;
        while(compt2<7)
        {
            int posAleatoire=rand()%ensemblePos.size();

            ElDomino* pDomino=m_plateauJeu.vecDominosAP.at(posAleatoire);
            m_plateauJeu.vecDominosAP.erase(m_plateauJeu.vecDominosAP.begin()+posAleatoire);
            ensemblePos.erase(ensemblePos.begin()+posAleatoire);

            m_plateauJeu.vecJoueurs.at(compt).vecDominos.push_back(pDomino);
            compt2++;

        }
        compt++;
    }
}

// ### FONCTION ###

void Joueur::piocherDomino(int joueur)
{
    if(joueur==HUMAIN)
    {
        int compt=0;
        while(compt<m_plateauJeu.vecDominosAP.size())
        {
            if(collisionTS(m_plateauJeu.vecDominosAP.at(compt)->sDomino.getGlobalBounds()))
            {
                m_plateauJeu.vecDominosAP.at(compt)->selectionne=true;
                m_plateauJeu.vecDominosAP.at(compt)->etat=VISIBLE;

                gestTextureD();

                //on determine la position que doit prendre le domino dans le cadre du joueur
                int indicDernEl=m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.size()-1;

                m_positionFinal.x=m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicDernEl)->sDomino.getPosition().x +
                                (m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicDernEl)->sDomino.getGlobalBounds().width +30.f);
                m_positionFinal.y=m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicDernEl)->sDomino.getPosition().y;
                posFinalD=m_positionFinal;

                m_plateauJeu.vecDominosAP.at(compt)->scale=m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicDernEl)->scale;
                m_plateauJeu.vecDominosAP.at(compt)->sDomino.setScale(m_plateauJeu.vecDominosAP.at(compt)->scale);

                animAActiver.push_back(ANIM_JOUEUR1_P);
                attente=true;

            }
            compt++;
        }

    }
    else
    {
        //on  choisit un domino au hasard dans le vecteur vecDominosAP
        int tailleVec=m_plateauJeu.vecDominosAP.size();
        int dominoChoisit=rand()%tailleVec;

        m_plateauJeu.vecDominosAP.at(dominoChoisit)->selectionne=true;
        m_plateauJeu.vecDominosAP.at(dominoChoisit)->etat=VISIBLE;


        //on determine la position que doit prendre le domino dans le cadre du joueur
        int indicDernEl=m_plateauJeu.vecJoueurs.at(CPU).vecDominos.size()-1;

        m_positionFinal.x=m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(indicDernEl)->sDomino.getPosition().x +
                        (m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(indicDernEl)->sDomino.getGlobalBounds().width +30.f);
        m_positionFinal.y=m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(indicDernEl)->sDomino.getPosition().y;
        posFinalD=m_positionFinal;

        m_plateauJeu.vecDominosAP.at(dominoChoisit)->scale=m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(indicDernEl)->scale;
        m_plateauJeu.vecDominosAP.at(dominoChoisit)->sDomino.setScale(m_plateauJeu.vecDominosAP.at(dominoChoisit)->scale);

    }
}

// ### FONCTION ###

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

// ### FONCTION ###

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

            if(m_plateauJeu.vecDominosAuBord.at(comp)->attacheHP)
            {
                nouvDonnees.y=m_plateauJeu.vecDominosAuBord.at(comp)->cote1;
                vecNumCoteValide.insert(vecNumCoteValide.end(),nouvDonnees);
            }

            if(m_plateauJeu.vecDominosAuBord.at(comp)->attacheBP)
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
                       domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==7 ||
                       domino.cote1+domino.cote2==7 ||
                       domino.cote1+domino.cote2==0)
                    {
                        m_vecDominoABouger.insert(m_vecDominoABouger.end(),m_plateauJeu.vecDominosAuBord.at(compt2)->noDomino);
                        possible=true;
                    }
                }

                if(m_plateauJeu.vecDominosAuBord.at(compt2)->attacheBP)
                {
                    if(domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==7 ||
                       domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==7 ||
                       domino.cote1+domino.cote2==7 ||
                       domino.cote1+domino.cote2==0)
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
                       domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==7 ||
                       domino.cote1+domino.cote2==7 ||
                       domino.cote1+domino.cote2==0)
                    {
                        m_vecDominoABouger.insert(m_vecDominoABouger.end(),m_plateauJeu.vecDominosAuBord.at(compt2)->noDomino);
                        possible=true;
                    }
                }

                if(m_plateauJeu.vecDominosAuBord.at(compt2)->attacheDP)
                {
                    if(domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==7 ||
                       domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==7 ||
                       domino.cote1+domino.cote2==7 ||
                       domino.cote1+domino.cote2==0)
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
                       domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==7 ||
                       domino.cote1+domino.cote2==7 ||
                       domino.cote1+domino.cote2==0)
                    {
                        m_vecDominoABouger.insert(m_vecDominoABouger.end(),m_plateauJeu.vecDominosAuBord.at(compt2)->noDomino);
                        possible=true;
                    }
                }

                if(m_plateauJeu.vecDominosAuBord.at(compt2)->attacheDP)
                {
                    if(domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==7 ||
                       domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==7 ||
                       domino.cote1+domino.cote2==7 ||
                       domino.cote1+domino.cote2==0)
                    {
                        m_vecDominoABouger.insert(m_vecDominoABouger.end(),m_plateauJeu.vecDominosAuBord.at(compt2)->noDomino);
                        possible=true;
                    }
                }

                if(m_plateauJeu.vecDominosAuBord.at(compt2)->attacheHP)
                {
                    if(domino.cote1==0 || domino.cote2==0)
                    {
                        m_vecDominoABouger.insert(m_vecDominoABouger.end(),m_plateauJeu.vecDominosAuBord.at(compt2)->noDomino);
                        possible=true;
                    }
                }

                if(m_plateauJeu.vecDominosAuBord.at(compt2)->attacheBP)
                {
                    if(domino.cote1==0 || domino.cote2==0)
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
                       domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote2==7 ||
                       domino.cote1+domino.cote2==7 ||
                       domino.cote1+domino.cote2==0)
                    {
                        m_vecDominoABouger.insert(m_vecDominoABouger.end(),m_plateauJeu.vecDominosAuBord.at(compt2)->noDomino);
                        possible=true;
                    }
                }

                if(m_plateauJeu.vecDominosAuBord.at(compt2)->attacheBP)
                {
                    if(domino.cote1+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==7 ||
                       domino.cote2+m_plateauJeu.vecDominosAuBord.at(compt2)->cote1==7 ||
                       domino.cote1+domino.cote2==7 ||
                       domino.cote1+domino.cote2==0)
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

// ### FONCTION ###

bool Joueur::placerDomino(int joueur, int noDominoP,int noDominoE)
{
    bool placerDPossible=false;
    int noJoueur=joueur;
    posFinalD2.x=-20;
    posFinalD2.y=-20;


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
                        if(noJoueur==HUMAIN)
                        {
                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x-boiteEDomP.width+(boiteEDomP.height/2),
                                                            pDominoParent->sDomino.getPosition().y);
                        }
                        else
                        {
                            posFinalD2.x=pDominoParent->sDomino.getPosition().x-boiteEDomP.width+(boiteEDomP.height/2);
                            posFinalD2.y=pDominoParent->sDomino.getPosition().y;
                        }


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

                            //.
                            if(noJoueur==HUMAIN)
                            {
                                pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x-(boiteEDomP.width/2)-(boiteEDomP.height/2),
                                                                    pDominoParent->sDomino.getPosition().y);
                            }
                            else
                            {
                                posFinalD2.x=pDominoParent->sDomino.getPosition().x-(boiteEDomP.width/2)-(boiteEDomP.height/2);
                                posFinalD2.y=pDominoParent->sDomino.getPosition().y;
                            }


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

                            //.
                            if(noJoueur==HUMAIN)
                            {
                                pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x-boiteEDomP.width,
                                                                    pDominoParent->sDomino.getPosition().y);
                            }
                            else
                            {
                                posFinalD2.x=pDominoParent->sDomino.getPosition().x-boiteEDomP.width;
                                posFinalD2.y=pDominoParent->sDomino.getPosition().y;
                            }


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
                        if(noJoueur==HUMAIN)
                        {
                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x+boiteEDomP.width-(boiteEDomP.height/2),
                                                                pDominoParent->sDomino.getPosition().y);
                        }
                        else
                        {
                            posFinalD2.x=pDominoParent->sDomino.getPosition().x+boiteEDomP.width-(boiteEDomP.height/2);
                            posFinalD2.y=pDominoParent->sDomino.getPosition().y;
                        }


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

                            if(noJoueur==HUMAIN)
                            {
                                pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x+(boiteEDomP.width/2)+(boiteEDomP.height/2),
                                                                    pDominoParent->sDomino.getPosition().y);
                            }
                            else
                            {
                                posFinalD2.x=pDominoParent->sDomino.getPosition().x+(boiteEDomP.width/2)+(boiteEDomP.height/2);
                                posFinalD2.y=pDominoParent->sDomino.getPosition().y;
                            }


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

                            if(noJoueur==HUMAIN)
                            {
                                pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x+boiteEDomP.width,
                                                                    pDominoParent->sDomino.getPosition().y);
                            }
                            else
                            {
                                posFinalD2.x=pDominoParent->sDomino.getPosition().x+boiteEDomP.width;
                                posFinalD2.y=pDominoParent->sDomino.getPosition().y;
                            }


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

                        if(noJoueur==HUMAIN)
                        {
                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                            pDominoParent->sDomino.getPosition().y -(boiteEDomP.height/2)-(boiteEDomP.width/2));
                        }
                        else
                        {
                            posFinalD2.x=pDominoParent->sDomino.getPosition().x;
                            posFinalD2.y=pDominoParent->sDomino.getPosition().y -(boiteEDomP.height/2)-(boiteEDomP.width/2);
                        }


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
                                if(noJoueur==HUMAIN)
                                {
                                    pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                    pDominoParent->sDomino.getPosition().y-boiteEDomP.height);
                                }
                                else
                                {
                                    posFinalD2.x=pDominoParent->sDomino.getPosition().x;
                                    posFinalD2.y=pDominoParent->sDomino.getPosition().y-boiteEDomP.height;
                                }


                            }
                            else
                            {
                                if(noJoueur==HUMAIN)
                                {
                                    pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                    pDominoParent->sDomino.getPosition().y-(boiteEDomP.height/2)-(boiteEDomP.width/2) );
                                }
                                else
                                {
                                    posFinalD2.x=pDominoParent->sDomino.getPosition().x;
                                    posFinalD2.y=pDominoParent->sDomino.getPosition().y-(boiteEDomP.height/2)-(boiteEDomP.width/2);
                                }


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

                            if(noJoueur==HUMAIN)
                            {
                                pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                pDominoParent->sDomino.getPosition().y-boiteEDomP.height);
                            }
                            else
                            {
                                posFinalD2.x=pDominoParent->sDomino.getPosition().x;
                                posFinalD2.y=pDominoParent->sDomino.getPosition().y-boiteEDomP.height;
                            }


                        }
                    }
                    coteH=false;
                    pDominoParent->attacheHP=false;
                    pDominoEnfant->attacheBP=false;
                    pDominoEnfant->attacheGP=false;
                    pDominoEnfant->attacheDP=false;
                    placerDPossible=true;
                }
                else if((coteB && (pDominoParent->cote2==pDominoEnfant->cote1 && pDominoParent->angle==0)) ||
                    (coteB && (pDominoParent->cote2==pDominoEnfant->cote2 && pDominoParent->angle==0)) ||
                    (coteB && (pDominoParent->cote2==pDominoEnfant->cote1 && pDominoParent->angle==90)) ||
                    (coteB && (pDominoParent->cote2==pDominoEnfant->cote2 && pDominoParent->angle==90)) ||
                    (coteB && (pDominoParent->cote1==pDominoEnfant->cote1 && pDominoParent->angle==180)) ||
                    (coteB && (pDominoParent->cote1==pDominoEnfant->cote2 && pDominoParent->angle==180)))
                {
                    if(pDominoEnfant->cote1 == pDominoEnfant->cote2) //si c'est un double
                    {
                        pDominoEnfant->angle=90.f;
                        pDominoEnfant->sDomino.setRotation(90.f);

                        if(noJoueur==HUMAIN)
                        {
                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                            pDominoParent->sDomino.getPosition().y +(boiteEDomP.height/2)+(boiteEDomP.width/2));
                        }
                        else
                        {
                            posFinalD2.x=pDominoParent->sDomino.getPosition().x;
                            posFinalD2.y=pDominoParent->sDomino.getPosition().y +(boiteEDomP.height/2)+(boiteEDomP.width/2);
                        }


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

                            if(pDominoParent->angle==0 || pDominoParent->angle==180)
                            {
                                if(noJoueur==HUMAIN)
                                {
                                    pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                pDominoParent->sDomino.getPosition().y + boiteEDomP.height);
                                }
                                else
                                {
                                    posFinalD2.x=pDominoParent->sDomino.getPosition().x;
                                    posFinalD2.y=pDominoParent->sDomino.getPosition().y + boiteEDomP.height;
                                }


                            }
                            else
                            {
                                if(noJoueur==HUMAIN)
                                {
                                    pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                pDominoParent->sDomino.getPosition().y+(boiteEDomP.width/2)+(boiteEDomP.height/2));
                                }
                                else
                                {
                                    posFinalD2.x=pDominoParent->sDomino.getPosition().x;
                                    posFinalD2.y=pDominoParent->sDomino.getPosition().y+(boiteEDomP.width/2)+(boiteEDomP.height/2);
                                }


                            }

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

                            if(noJoueur==HUMAIN)
                            {
                                pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                pDominoParent->sDomino.getPosition().y+boiteEDomP.height);
                            }
                            else
                            {
                                posFinalD2.x=pDominoParent->sDomino.getPosition().x;
                                posFinalD2.y=pDominoParent->sDomino.getPosition().y+boiteEDomP.height;
                            }


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
                    (coteG && (pDominoEnfant->cote1==0 && pDominoParent->angle==0)) ||
                    (coteG && (pDominoEnfant->cote2==0 && pDominoParent->angle==0)) ||
                    (coteG && (pDominoEnfant->cote1+pDominoEnfant->cote2==7 && (pDominoParent->angle==90 || pDominoParent->angle==-90) )) ||
                    (coteG && (pDominoEnfant->cote1+pDominoEnfant->cote2==0 && (pDominoParent->angle==90 || pDominoParent->angle==-90) )) )
                {

                    if( (pDominoEnfant->cote1 + pDominoEnfant->cote2 ==7  ||
                       pDominoEnfant->cote1 + pDominoEnfant->cote2 ==0) &&
                       (pDominoParent->angle==90 || pDominoParent->angle==-90)  )
                    {
                        if(noJoueur==HUMAIN)
                        {
                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x-boiteEDomP.width+(boiteEDomP.height/2),
                                                            pDominoParent->sDomino.getPosition().y);
                        }
                        else
                        {
                            posFinalD2.x=pDominoParent->sDomino.getPosition().x-boiteEDomP.width+(boiteEDomP.height/2);
                            posFinalD2.y=pDominoParent->sDomino.getPosition().y;
                        }


                    }
                    else
                    {
                        if((pDominoParent->cote1 + pDominoParent->cote2==7 ||
                           pDominoParent->cote1 + pDominoParent->cote2==0) && pDominoParent->angle==0.f )
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

                            //.
                            if(noJoueur==HUMAIN)
                            {
                                pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x-(boiteEDomP.width/2)-(boiteEDomP.height/2),
                                                                pDominoParent->sDomino.getPosition().y);
                            }
                            else
                            {
                                posFinalD2.x=pDominoParent->sDomino.getPosition().x-(boiteEDomP.width/2)-(boiteEDomP.height/2);
                                posFinalD2.y=pDominoParent->sDomino.getPosition().y;
                            }


                        }
                        else
                        {
                            if( (pDominoEnfant->cote1+pDominoParent->cote1==7 && pDominoParent->angle==-90.f) )
                            {
                                pDominoEnfant->angle=90.f;
                                pDominoEnfant->sDomino.setRotation(90.f);
                            }
                            else if( (pDominoEnfant->cote1+pDominoParent->cote2==7 && pDominoParent->angle==90.f) )
                            {
                                pDominoEnfant->angle=90.f;
                                pDominoEnfant->sDomino.setRotation(90.f);
                            }
                            else if( (pDominoEnfant->cote2+pDominoParent->cote1==7 && pDominoParent->angle==-90.f) )
                            {
                                pDominoEnfant->angle=-90.f;
                                pDominoEnfant->sDomino.setRotation(-90.f);
                            }
                            else
                            {
                                pDominoEnfant->angle=-90.f;
                                pDominoEnfant->sDomino.setRotation(-90.f);
                            }

                            //.
                            if(noJoueur==HUMAIN)
                            {
                                pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x-boiteEDomP.width,
                                                                pDominoParent->sDomino.getPosition().y);
                            }
                            else
                            {
                                posFinalD2.x=pDominoParent->sDomino.getPosition().x-boiteEDomP.width;
                                posFinalD2.y=pDominoParent->sDomino.getPosition().y;
                            }


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
                    (coteD && (pDominoEnfant->cote1==0 && pDominoParent->angle==0)) ||
                    (coteD && (pDominoEnfant->cote2==0 && pDominoParent->angle==0)) ||
                    (coteD && (pDominoEnfant->cote1+pDominoEnfant->cote2==7 && (pDominoParent->angle==90 || pDominoParent->angle==-90) )) ||
                    (coteD && (pDominoEnfant->cote1+pDominoEnfant->cote2==0 && (pDominoParent->angle==90 || pDominoParent->angle==-90) ))   )
                {
                    if((pDominoEnfant->cote1 + pDominoEnfant->cote2 ==7  ||
                       pDominoEnfant->cote1 + pDominoEnfant->cote2 ==0) &&
                       (pDominoParent->angle==90 || pDominoParent->angle==-90))
                    {
                        if(noJoueur==HUMAIN)
                        {
                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x+boiteEDomP.width-(boiteEDomP.height/2),
                                                            pDominoParent->sDomino.getPosition().y);
                        }
                        else
                        {
                            posFinalD2.x=pDominoParent->sDomino.getPosition().x+boiteEDomP.width-(boiteEDomP.height/2);
                            posFinalD2.y=pDominoParent->sDomino.getPosition().y;
                        }


                    }
                    else
                    {
                        if((pDominoParent->cote1 + pDominoParent->cote2==7 ||
                           pDominoParent->cote1 + pDominoParent->cote2==0) && pDominoParent->angle==0.f )
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

                            //.
                            if(noJoueur==HUMAIN)
                            {
                                pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x+(boiteEDomP.width/2)+(boiteEDomP.height/2),
                                                                pDominoParent->sDomino.getPosition().y);
                            }
                            else
                            {
                                posFinalD2.x=pDominoParent->sDomino.getPosition().x+(boiteEDomP.width/2)+(boiteEDomP.height/2);
                                posFinalD2.y=pDominoParent->sDomino.getPosition().y;
                            }


                        }
                        else
                        {
                            if( (pDominoEnfant->cote1+pDominoParent->cote1==7 && pDominoParent->angle==90.f) )
                            {
                                pDominoEnfant->angle=-90.f;
                                pDominoEnfant->sDomino.setRotation(-90.f);
                            }
                            else if( (pDominoEnfant->cote2+pDominoParent->cote2==7 && pDominoParent->angle==90.f) )
                            {
                                pDominoEnfant->angle=90.f;
                                pDominoEnfant->sDomino.setRotation(90.f);
                            }
                            else if( (pDominoEnfant->cote1+pDominoParent->cote2==7 && pDominoParent->angle==-90.f) )
                            {
                                pDominoEnfant->angle=-90.f;
                                pDominoEnfant->sDomino.setRotation(-90.f);
                            }
                            else
                            {
                                pDominoEnfant->angle=90.f;
                                pDominoEnfant->sDomino.setRotation(90.f);
                            }

                            //.
                            if(noJoueur==HUMAIN)
                            {
                                pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x+boiteEDomP.width,
                                                                pDominoParent->sDomino.getPosition().y);
                            }
                            else
                            {
                                posFinalD2.x=pDominoParent->sDomino.getPosition().x+boiteEDomP.width;
                                posFinalD2.y=pDominoParent->sDomino.getPosition().y;
                            }


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
                    (coteH && (pDominoEnfant->cote1==0 && pDominoParent->angle==90)) ||
                    (coteH && (pDominoEnfant->cote2==0 && pDominoParent->angle==90)) ||
                    (coteH && (pDominoEnfant->cote1+pDominoEnfant->cote2==7 && (pDominoParent->angle==0 || pDominoParent->angle==180) )) ||
                    (coteH && (pDominoEnfant->cote1+pDominoEnfant->cote2==0 && (pDominoParent->angle==0 || pDominoParent->angle==180) )) )
                {
                    if((pDominoEnfant->cote1 + pDominoEnfant->cote2 ==7  ||
                       pDominoEnfant->cote1 + pDominoEnfant->cote2 ==0) &&
                       (pDominoParent->angle==0.f || pDominoParent->angle==180.f))
                    {
                        pDominoEnfant->angle=90.f;
                        pDominoEnfant->sDomino.setRotation(90.f);

                        //.
                        if(noJoueur==HUMAIN)
                        {
                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                            pDominoParent->sDomino.getPosition().y - (boiteEDomP.height/2) - (boiteEDomP.width/2) );
                        }
                        else
                        {
                            posFinalD2.x=pDominoParent->sDomino.getPosition().x;
                            posFinalD2.y=pDominoParent->sDomino.getPosition().y - (boiteEDomP.height/2) - (boiteEDomP.width/2);
                        }


                    }
                    else
                    {
                        if((pDominoParent->cote1 + pDominoParent->cote2==7 ||
                           pDominoParent->cote1 + pDominoParent->cote2==0) && pDominoParent->angle==90.f)
                        {
                            if(pDominoEnfant->cote1==0)
                            {
                                pDominoEnfant->angle=180.f;
                                pDominoEnfant->sDomino.setRotation(180.f);
                            }

                            //.
                            if(noJoueur==HUMAIN)
                            {
                                pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                pDominoParent->sDomino.getPosition().y -(boiteEDomP.width/2)-(boiteEDomP.height/2));
                            }
                            else
                            {
                                posFinalD2.x=pDominoParent->sDomino.getPosition().x;
                                posFinalD2.y=pDominoParent->sDomino.getPosition().y -(boiteEDomP.width/2)-(boiteEDomP.height/2);
                            }


                        }
                        else
                        {
                            if( (pDominoEnfant->cote1+pDominoParent->cote1==7 && pDominoParent->angle==0.f) )
                            {
                                pDominoEnfant->angle=180.f;
                                pDominoEnfant->sDomino.setRotation(180.f);
                            }
                            else if( (pDominoEnfant->cote2+pDominoParent->cote2==7 && pDominoParent->angle==180.f) )
                            {
                                pDominoEnfant->angle=0.f;
                                pDominoEnfant->sDomino.setRotation(0.f);
                            }
                            else if( (pDominoEnfant->cote1+pDominoParent->cote2==7 && pDominoParent->angle==180.f) )
                            {
                                pDominoEnfant->angle=180.f;
                                pDominoEnfant->sDomino.setRotation(180.f);
                            }
                            else
                            {
                                pDominoEnfant->angle=0.f;
                                pDominoEnfant->sDomino.setRotation(0.f);
                            }

                            //.
                            if(noJoueur==HUMAIN)
                            {
                                pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                pDominoParent->sDomino.getPosition().y-boiteEDomP.height);
                            }
                            else
                            {
                                posFinalD2.x=pDominoParent->sDomino.getPosition().x;
                                posFinalD2.y=pDominoParent->sDomino.getPosition().y-boiteEDomP.height;
                            }


                        }
                    }
                    coteH=false;
                    pDominoParent->attacheHP=false;
                    pDominoEnfant->attacheBP=false;
                    pDominoEnfant->attacheGP=false;
                    pDominoEnfant->attacheDP=false;
                    placerDPossible=true;
                }
                else if((coteB && (pDominoParent->cote1+pDominoEnfant->cote1==7 && pDominoParent->angle==180)) ||
                    (coteB && (pDominoParent->cote1+pDominoEnfant->cote2==7 && pDominoParent->angle==180)) ||
                    (coteB && (pDominoParent->cote2+pDominoEnfant->cote1==7 && pDominoParent->angle==0)) ||
                    (coteB && (pDominoParent->cote2+pDominoEnfant->cote2==7 && pDominoParent->angle==0)) ||
                    (coteB && (pDominoEnfant->cote1==0 && pDominoParent->angle==90)) ||
                    (coteB && (pDominoEnfant->cote2==0 && pDominoParent->angle==90)) ||
                    (coteB && (pDominoEnfant->cote1+pDominoEnfant->cote2==7 && (pDominoParent->angle==0 || pDominoParent->angle==180) )) ||
                    (coteB && (pDominoEnfant->cote1+pDominoEnfant->cote2==0 && (pDominoParent->angle==0 || pDominoParent->angle==180) )) )
                {

                    if((pDominoEnfant->cote1 + pDominoEnfant->cote2 ==7  ||
                       pDominoEnfant->cote1 + pDominoEnfant->cote2 ==0) &&
                       (pDominoParent->angle==0.f || pDominoParent->angle==180.f))
                    {
                        pDominoEnfant->angle=90.f;
                        pDominoEnfant->sDomino.setRotation(90.f);

                        //.
                        if(noJoueur==HUMAIN)
                        {
                            pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                            pDominoParent->sDomino.getPosition().y + (boiteEDomP.height/2) + (boiteEDomP.width/2) );
                        }
                        else
                        {
                            posFinalD2.x=pDominoParent->sDomino.getPosition().x;
                            posFinalD2.y=pDominoParent->sDomino.getPosition().y + (boiteEDomP.height/2) + (boiteEDomP.width/2);
                        }


                    }
                    else
                    {
                        if((pDominoParent->cote1 + pDominoParent->cote2==7 ||
                           pDominoParent->cote1 + pDominoParent->cote2==0) && pDominoParent->angle==90.f)
                        {
                            if(pDominoEnfant->cote1==0)
                            {
                                pDominoEnfant->angle=0.f;
                                pDominoEnfant->sDomino.setRotation(0.f);
                            }
                            else
                            {
                                pDominoEnfant->angle=180.f;
                                pDominoEnfant->sDomino.setRotation(180.f);
                            }

                            //.
                            if(noJoueur==HUMAIN)
                            {
                                pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                pDominoParent->sDomino.getPosition().y +(boiteEDomP.width/2)+(boiteEDomP.height/2));
                            }
                            else
                            {
                                posFinalD2.x=pDominoParent->sDomino.getPosition().x;
                                posFinalD2.y=pDominoParent->sDomino.getPosition().y +(boiteEDomP.width/2)+(boiteEDomP.height/2);
                            }


                        }
                        else
                        {
                            if( (pDominoEnfant->cote1+pDominoParent->cote1==7 && pDominoParent->angle==180.f) )
                            {
                                pDominoEnfant->angle=0.f;
                                pDominoEnfant->sDomino.setRotation(0.f);
                            }
                            else if( (pDominoEnfant->cote2+pDominoParent->cote2==7 && pDominoParent->angle==0.f) )
                            {
                                pDominoEnfant->angle=180.f;
                                pDominoEnfant->sDomino.setRotation(180.f);
                            }
                            else if( (pDominoEnfant->cote1+pDominoParent->cote2==7 && pDominoParent->angle==0.f) )
                            {
                                pDominoEnfant->angle=0.f;
                                pDominoEnfant->sDomino.setRotation(0.f);
                            }
                            else
                            {
                                pDominoEnfant->angle=180.f;
                                pDominoEnfant->sDomino.setRotation(180.f);
                            }

                            //.
                            if(noJoueur==HUMAIN)
                            {
                                pDominoEnfant->sDomino.setPosition(pDominoParent->sDomino.getPosition().x,
                                                                pDominoParent->sDomino.getPosition().y + boiteEDomP.height);
                            }
                            else
                            {

                                posFinalD2.x=pDominoParent->sDomino.getPosition().x;
                                posFinalD2.y=pDominoParent->sDomino.getPosition().y + boiteEDomP.height;
                            }


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

    //...replacer le domino qu'on vient d'attacher aux autres s'il atteigne les cotes...//

    int angleDominoP=0;
    for(int commp=0;commp<m_plateauJeu.vecDominosPoses.size();commp++)
    {
        if(m_plateauJeu.vecDominosPoses.at(commp)->noDomino==noDominoP)
        {
            angleDominoP=m_plateauJeu.vecDominosPoses.at(commp)->angle;
        }
    }

    ElDomino* pDominoE=m_plateauJeu.vecJoueurs.at(noJoueur).vecDominos.at(noDominoE);

    if(placerDPossible)
    {
        sf::FloatRect dominoFinal;
        dominoFinal.left=posFinalD2.x;
        dominoFinal.top=posFinalD2.y;
        dominoFinal.width=pDominoE->sDomino.getLocalBounds().width;
        dominoFinal.height=pDominoE->sDomino.getLocalBounds().height;

        bool collisionG=false,collisionD=false,collisionH=false,collisionB=false;

        if(noJoueur==HUMAIN)
        {
            collisionG=m_plateauJeu.detecteurG.intersects(pDominoE->sDomino.getGlobalBounds());
            collisionD=m_plateauJeu.detecteurD.intersects(pDominoE->sDomino.getGlobalBounds());
            collisionH=m_plateauJeu.detecteurH.intersects(pDominoE->sDomino.getGlobalBounds());
            collisionB=m_plateauJeu.detecteurB.intersects(pDominoE->sDomino.getGlobalBounds());
        }
        else
        {
            collisionG=m_plateauJeu.detecteurG.intersects(dominoFinal);
            collisionD=m_plateauJeu.detecteurD.intersects(dominoFinal);
            collisionH=m_plateauJeu.detecteurH.intersects(dominoFinal);
            collisionB=m_plateauJeu.detecteurB.intersects(dominoFinal);
        }


        if(collisionG)
        {
            std::cout<<"Collision G "<<std::endl;
            if(pDominoE->angle==0)
            {
                if(m_plateauJeu.typeJeu==TJ_MATADOR)
                {
                    pDominoE->angle=90;
                    pDominoE->sDomino.setRotation(pDominoE->angle);

                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(pDominoE->sDomino.getGlobalBounds().height+(pDominoE->sDomino.getGlobalBounds().height/2),
                                       -pDominoE->sDomino.getGlobalBounds().height );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x + pDominoE->sDomino.getGlobalBounds().height+(pDominoE->sDomino.getGlobalBounds().height/2);
                        posFinalD2.y=posFinalD2.y -pDominoE->sDomino.getGlobalBounds().height;
                    }


                }
                else
                {

                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(pDominoE->sDomino.getGlobalBounds().width,
                                       -(pDominoE->sDomino.getGlobalBounds().height/2)-(pDominoE->sDomino.getGlobalBounds().width/2) );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x + pDominoE->sDomino.getGlobalBounds().width;
                        posFinalD2.y=posFinalD2.y - (pDominoE->sDomino.getGlobalBounds().height/2)-(pDominoE->sDomino.getGlobalBounds().width/2);
                    }


                }


                pDominoE->attacheGP=false;
                pDominoE->attacheHP=true;
            }
            else if(pDominoE->angle==90)
            {
                pDominoE->angle=180;
                pDominoE->sDomino.setRotation(pDominoE->angle);

                if(angleDominoP==0)
                {
                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(pDominoE->sDomino.getGlobalBounds().width+(pDominoE->sDomino.getGlobalBounds().width/2),
                                           -(pDominoE->sDomino.getGlobalBounds().height) );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x + pDominoE->sDomino.getGlobalBounds().width+(pDominoE->sDomino.getGlobalBounds().width/2);
                        posFinalD2.y=posFinalD2.y  -(pDominoE->sDomino.getGlobalBounds().height);
                    }


                }
                else
                {
                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(pDominoE->sDomino.getGlobalBounds().width+(pDominoE->sDomino.getGlobalBounds().width/2),
                                           -pDominoE->sDomino.getGlobalBounds().width-(pDominoE->sDomino.getGlobalBounds().width/2) );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x +  pDominoE->sDomino.getGlobalBounds().width+(pDominoE->sDomino.getGlobalBounds().width/2);
                        posFinalD2.y=posFinalD2.y  -pDominoE->sDomino.getGlobalBounds().width-(pDominoE->sDomino.getGlobalBounds().width/2);
                    }


                }


                pDominoE->attacheGP=false;
                pDominoE->attacheHP=true;

            }
            else if(pDominoE->angle==-90)
            {
                pDominoE->angle=0;
                pDominoE->sDomino.setRotation(pDominoE->angle);

                if(angleDominoP==0)
                {
                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(pDominoE->sDomino.getGlobalBounds().width+(pDominoE->sDomino.getGlobalBounds().width/2),
                                           -(pDominoE->sDomino.getGlobalBounds().height) );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x + pDominoE->sDomino.getGlobalBounds().width+(pDominoE->sDomino.getGlobalBounds().width/2);
                        posFinalD2.y=posFinalD2.y -(pDominoE->sDomino.getGlobalBounds().height);
                    }


                }
                else
                {
                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(pDominoE->sDomino.getGlobalBounds().width+(pDominoE->sDomino.getGlobalBounds().width/2),
                                           -pDominoE->sDomino.getGlobalBounds().width-(pDominoE->sDomino.getGlobalBounds().width/2) );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x + pDominoE->sDomino.getGlobalBounds().width+(pDominoE->sDomino.getGlobalBounds().width/2);
                        posFinalD2.y=posFinalD2.y -pDominoE->sDomino.getGlobalBounds().width-(pDominoE->sDomino.getGlobalBounds().width/2);
                    }


                }

                pDominoE->attacheGP=false;
                pDominoE->attacheHP=true;
            }
            else{}

        }
        else if(collisionD)
        {
            std::cout<<"Collision D "<<std::endl;
            if(pDominoE->angle==0)
            {
                if(m_plateauJeu.typeJeu==TJ_MATADOR)
                {
                    pDominoE->angle=90;
                    pDominoE->sDomino.setRotation(pDominoE->angle);

                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(-pDominoE->sDomino.getGlobalBounds().height-(pDominoE->sDomino.getGlobalBounds().height/2),
                                       +pDominoE->sDomino.getGlobalBounds().height );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x -pDominoE->sDomino.getGlobalBounds().height-(pDominoE->sDomino.getGlobalBounds().height/2);
                        posFinalD2.y=posFinalD2.y +pDominoE->sDomino.getGlobalBounds().height;
                    }


                }
                else
                {
                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(-pDominoE->sDomino.getGlobalBounds().width,
                                       +(pDominoE->sDomino.getGlobalBounds().height/2)+(pDominoE->sDomino.getGlobalBounds().width/2) );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x -pDominoE->sDomino.getGlobalBounds().width;
                        posFinalD2.y=posFinalD2.y +(pDominoE->sDomino.getGlobalBounds().height/2)+(pDominoE->sDomino.getGlobalBounds().width/2);
                    }


                }

                pDominoE->attacheDP=false;
                pDominoE->attacheBP=true;
            }
            else if(pDominoE->angle==90)
            {
                pDominoE->angle=180;
                pDominoE->sDomino.setRotation(pDominoE->angle);

                if(angleDominoP==0)
                {
                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(-pDominoE->sDomino.getGlobalBounds().width-(pDominoE->sDomino.getGlobalBounds().width/2),
                                           +pDominoE->sDomino.getGlobalBounds().height );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x -pDominoE->sDomino.getGlobalBounds().width-(pDominoE->sDomino.getGlobalBounds().width/2);
                        posFinalD2.y=posFinalD2.y +pDominoE->sDomino.getGlobalBounds().height;
                    }


                }
                else
                {
                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(-pDominoE->sDomino.getGlobalBounds().width-(pDominoE->sDomino.getGlobalBounds().width/2),
                                           +pDominoE->sDomino.getGlobalBounds().width+(pDominoE->sDomino.getGlobalBounds().width/2) );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x -pDominoE->sDomino.getGlobalBounds().width-(pDominoE->sDomino.getGlobalBounds().width/2);
                        posFinalD2.y=posFinalD2.y +pDominoE->sDomino.getGlobalBounds().width+(pDominoE->sDomino.getGlobalBounds().width/2);
                    }


                }


                pDominoE->attacheDP=false;
                pDominoE->attacheBP=true;

            }
            else if(pDominoE->angle==-90)
            {
                pDominoE->angle=0;
                pDominoE->sDomino.setRotation(pDominoE->angle);

                if(angleDominoP==0)
                {
                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(-pDominoE->sDomino.getGlobalBounds().width-(pDominoE->sDomino.getGlobalBounds().width/2),
                                           +pDominoE->sDomino.getGlobalBounds().height );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x -pDominoE->sDomino.getGlobalBounds().width-(pDominoE->sDomino.getGlobalBounds().width/2);
                        posFinalD2.y=posFinalD2.y +pDominoE->sDomino.getGlobalBounds().height;
                    }


                }
                else
                {
                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(-pDominoE->sDomino.getGlobalBounds().width-(pDominoE->sDomino.getGlobalBounds().width/2),
                                           +pDominoE->sDomino.getGlobalBounds().width+(pDominoE->sDomino.getGlobalBounds().width/2) );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x -pDominoE->sDomino.getGlobalBounds().width-(pDominoE->sDomino.getGlobalBounds().width/2);
                        posFinalD2.y=posFinalD2.y +pDominoE->sDomino.getGlobalBounds().width+(pDominoE->sDomino.getGlobalBounds().width/2);
                    }


                }

                pDominoE->attacheDP=false;
                pDominoE->attacheBP=true;
            }
            else{}

        }
        else if(collisionH)
        {
            std::cout<<"Collision H "<<std::endl;
            if(pDominoE->angle==0)
            {
                pDominoE->angle=90;
                pDominoE->sDomino.setRotation(pDominoE->angle);

                if(angleDominoP==90)
                {
                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(pDominoE->sDomino.getGlobalBounds().width,
                                           +pDominoE->sDomino.getGlobalBounds().height+(pDominoE->sDomino.getGlobalBounds().height/2) );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x + pDominoE->sDomino.getGlobalBounds().width;
                        posFinalD2.y=posFinalD2.y +pDominoE->sDomino.getGlobalBounds().height+(pDominoE->sDomino.getGlobalBounds().height/2);
                    }


                }
                else
                {
                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(pDominoE->sDomino.getGlobalBounds().height+(pDominoE->sDomino.getGlobalBounds().height/2),
                                           +pDominoE->sDomino.getGlobalBounds().height+(pDominoE->sDomino.getGlobalBounds().height/2));
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x + pDominoE->sDomino.getGlobalBounds().height+(pDominoE->sDomino.getGlobalBounds().height/2);
                        posFinalD2.y=posFinalD2.y +pDominoE->sDomino.getGlobalBounds().height+(pDominoE->sDomino.getGlobalBounds().height/2);
                    }


                }

                pDominoE->attacheHP=false;
                pDominoE->attacheDP=true;

            }
            else if(pDominoE->angle==180)
            {
                pDominoE->angle=-90;
                pDominoE->sDomino.setRotation(pDominoE->angle);

                if(angleDominoP==90)
                {
                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(pDominoE->sDomino.getGlobalBounds().width,
                                           +pDominoE->sDomino.getGlobalBounds().height+(pDominoE->sDomino.getGlobalBounds().height/2) );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x + pDominoE->sDomino.getGlobalBounds().width;
                        posFinalD2.y=posFinalD2.y +pDominoE->sDomino.getGlobalBounds().height+(pDominoE->sDomino.getGlobalBounds().height/2);
                    }


                }
                else
                {
                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(pDominoE->sDomino.getGlobalBounds().height+(pDominoE->sDomino.getGlobalBounds().height/2),
                                           pDominoE->sDomino.getGlobalBounds().height+(pDominoE->sDomino.getGlobalBounds().height/2) );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x + pDominoE->sDomino.getGlobalBounds().height+(pDominoE->sDomino.getGlobalBounds().height/2);
                        posFinalD2.y=posFinalD2.y + pDominoE->sDomino.getGlobalBounds().height+(pDominoE->sDomino.getGlobalBounds().height/2);
                    }


                }

                pDominoE->attacheHP=false;
                pDominoE->attacheDP=true;
            }
            else if(pDominoE->angle==90)
            {
                if(m_plateauJeu.typeJeu==TJ_MATADOR)
                {
                    pDominoE->angle=0;
                    pDominoE->sDomino.setRotation(pDominoE->angle);

                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(pDominoE->sDomino.getGlobalBounds().width,
                                        +pDominoE->sDomino.getGlobalBounds().width+(pDominoE->sDomino.getGlobalBounds().width/2) );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x + pDominoE->sDomino.getGlobalBounds().width;
                        posFinalD2.y=posFinalD2.y +pDominoE->sDomino.getGlobalBounds().width+(pDominoE->sDomino.getGlobalBounds().width/2);
                    }


                }
                else
                {
                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(pDominoE->sDomino.getGlobalBounds().height+(pDominoE->sDomino.getGlobalBounds().height/2),
                                        +pDominoE->sDomino.getGlobalBounds().height );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x + pDominoE->sDomino.getGlobalBounds().height+(pDominoE->sDomino.getGlobalBounds().height/2);
                        posFinalD2.y=posFinalD2.y +pDominoE->sDomino.getGlobalBounds().height;
                    }


                }


                pDominoE->attacheHP=false;
                pDominoE->attacheDP=true;
            }
            else{}
        }
        else if(collisionB)
        {
            std::cout<<"Collision B "<<std::endl;
            if(pDominoE->angle==0)
            {
                pDominoE->angle=90;
                pDominoE->sDomino.setRotation(pDominoE->angle);

                if(angleDominoP==90)
                {
                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(-pDominoE->sDomino.getGlobalBounds().width,
                                           -pDominoE->sDomino.getGlobalBounds().height-(pDominoE->sDomino.getGlobalBounds().height/2) );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x -pDominoE->sDomino.getGlobalBounds().width;
                        posFinalD2.y=posFinalD2.y -pDominoE->sDomino.getGlobalBounds().height-(pDominoE->sDomino.getGlobalBounds().height/2);
                    }


                }
                else
                {
                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(-pDominoE->sDomino.getGlobalBounds().height-(pDominoE->sDomino.getGlobalBounds().height/2),
                                           -pDominoE->sDomino.getGlobalBounds().height-(pDominoE->sDomino.getGlobalBounds().height/2));
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x -pDominoE->sDomino.getGlobalBounds().height-(pDominoE->sDomino.getGlobalBounds().height/2);
                        posFinalD2.y=posFinalD2.y -pDominoE->sDomino.getGlobalBounds().height-(pDominoE->sDomino.getGlobalBounds().height/2);
                    }


                }

                pDominoE->attacheBP=false;
                pDominoE->attacheGP=true;

            }
            else if(pDominoE->angle==180)
            {
                pDominoE->angle=-90;
                pDominoE->sDomino.setRotation(pDominoE->angle);

                if(angleDominoP==90)
                {
                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(-pDominoE->sDomino.getGlobalBounds().width,
                                           -pDominoE->sDomino.getGlobalBounds().height-(pDominoE->sDomino.getGlobalBounds().height/2) );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x -pDominoE->sDomino.getGlobalBounds().width;
                        posFinalD2.y=posFinalD2.y -pDominoE->sDomino.getGlobalBounds().height-(pDominoE->sDomino.getGlobalBounds().height/2);
                    }


                }
                else
                {
                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(-pDominoE->sDomino.getGlobalBounds().height-(pDominoE->sDomino.getGlobalBounds().height/2),
                                           -pDominoE->sDomino.getGlobalBounds().height-(pDominoE->sDomino.getGlobalBounds().height/2) );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x -pDominoE->sDomino.getGlobalBounds().height-(pDominoE->sDomino.getGlobalBounds().height/2);
                        posFinalD2.y=posFinalD2.y -pDominoE->sDomino.getGlobalBounds().height-(pDominoE->sDomino.getGlobalBounds().height/2);
                    }


                }

                pDominoE->attacheBP=false;
                pDominoE->attacheGP=true;
            }
            else if(pDominoE->angle==90)
            {
                if(m_plateauJeu.typeJeu==TJ_MATADOR)
                {
                    pDominoE->angle=0;
                    pDominoE->sDomino.setRotation(pDominoE->angle);

                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(-pDominoE->sDomino.getGlobalBounds().width,
                                        -pDominoE->sDomino.getGlobalBounds().width-(pDominoE->sDomino.getGlobalBounds().width/2) );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x -pDominoE->sDomino.getGlobalBounds().width;
                        posFinalD2.y=posFinalD2.y -pDominoE->sDomino.getGlobalBounds().width-(pDominoE->sDomino.getGlobalBounds().width/2);
                    }


                }
                else
                {
                    if(noJoueur==HUMAIN)
                    {
                        pDominoE->sDomino.move(-pDominoE->sDomino.getGlobalBounds().height-(pDominoE->sDomino.getGlobalBounds().height/2),
                                        -pDominoE->sDomino.getGlobalBounds().height );
                    }
                    else
                    {
                        posFinalD2.x=posFinalD2.x -pDominoE->sDomino.getGlobalBounds().height-(pDominoE->sDomino.getGlobalBounds().height/2);
                        posFinalD2.y=posFinalD2.y -pDominoE->sDomino.getGlobalBounds().height;
                    }


                }


                pDominoE->attacheBP=false;
                pDominoE->attacheGP=true;
            }
            else{}
        }
        else{}
    }


    return placerDPossible;
}

// ### FONCTION ###

void Joueur::arrangerDomino(int noCadre)
{
    sf::Vector2f posReferenceJ1,posReferenceJ2;
    posReferenceJ1.x=13*20;
    posReferenceJ1.y=33*20-5;

    posReferenceJ2.x=15*20;
    posReferenceJ2.y=2*20+5;

    if(noCadre==CADRE_G)
    {
        bool detectionCG=false,detectionCD=false,detectionCH=false,detectionCB=false;

        /*
        on va tester s'il y a collisions dans plusieurs detecteurs afin de determiner si c'est une remise a echelle qu'il faut ou
        juste des translations
        -par exemple
        */

        int compt=0;
    }
    else if(noCadre==CADRE_J1)
    {
        int compt=0;
        while(compt<m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.size())
        {
            int interval=0;
            if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.size()<=7)
            {
                interval=10;
            }
            else if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.size()>=12)
            {
                interval=15;
            }
            else
            {
                interval=20;
            }

            float xPos=posReferenceJ1.x + (compt*(70-interval));
            float yPos=posReferenceJ1.y;
            m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->sDomino.setPosition(xPos,yPos);
            compt++;
        }
    }
    else if(noCadre==CADRE_J2)
    {
        int compt=0;
        while(compt<m_plateauJeu.vecJoueurs.at(CPU).vecDominos.size())
        {
            int interval=0;
            if(m_plateauJeu.vecJoueurs.at(CPU).vecDominos.size()<=7)
            {
                interval=10;
            }
            else if(m_plateauJeu.vecJoueurs.at(CPU).vecDominos.size()>=12)
            {
                interval=15;
            }
            else
            {
                interval=20;
            }

            float xPos=posReferenceJ2.x + (compt*(70-interval));
            float yPos=posReferenceJ2.y;
            m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->sDomino.setPosition(xPos,yPos);
            compt++;
        }
    }
    else
    {

    }
}

// ### FONCTION ###

void Joueur::retourneDominos(int joueur,bool rendreVisible)
{
    if(joueur==HUMAIN)
    {
        int compt=0;
        while(compt<m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.size())
        {
            if(rendreVisible)
            {
                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->etat=VISIBLE;
            }
            else
            {
                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->etat=RETOURNE;
            }

            compt++;
        }
    }
    else if(joueur==CPU)
    {
        int compt=0;
        while(compt<m_plateauJeu.vecJoueurs.at(CPU).vecDominos.size())
        {
            if(rendreVisible)
            {
                m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->etat=VISIBLE;
            }
            else
            {
                m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->etat=RETOURNE;
            }

            compt++;
        }
    }
    else
    {

    }
    gestTextureD();
}

// ### FONCTION ###

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

// ### FONCTION ###

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


                if(!glisser && !deposer)
                {
                    laMain=false;
                    laMainBot=true;
                }
                else
                {
                    deposer=false;
                }


            }
            indicEl--;
            compt++;
        }


    }

}

// ### FONCTION ###

PlateauJeu& Joueur::getPlateauJeu()
{
    return m_plateauJeu;
}

// ### FONCTION ###

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

        if(m_plateauJeu.vecJoueurs.at(HUMAIN).pass && m_plateauJeu.vecJoueurs.at(HUMAIN).pass)
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

    //on teste si les deux joueurs ont passe leur tour
    if(m_plateauJeu.vecJoueurs.at(HUMAIN).pass && m_plateauJeu.vecJoueurs.at(CPU).pass)
    {
        termine=true;
    }

    return termine;
}

// ### FONCTION ###

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

// ### FONCTION ###

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

// ### FONCTION ###

bool Joueur::boutonSelect()
{
    bool select=false;
    if(collisionTS(m_sbPause.getGlobalBounds()))
    {
        select=true;

    }

    return select;
}

// ### FONCTION ###

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

// ### FONCTION ###
//....gestion type de jeu Memory....
void Joueur::selectionDominoTMem(int joueur)
{
    if(joueur==HUMAIN && !attente && laMain)
    {
        int compt=0;
        while(compt<m_plateauJeu.vecDominosAP.size())
        {
            if(collisionTS(m_plateauJeu.vecDominosAP.at(compt)->sDomino.getGlobalBounds()))
            {
                m_plateauJeu.vecDominosAP.at(compt)->selectionne=true;
                m_plateauJeu.vecDominosAP.at(compt)->etat=VISIBLE;
            }
            compt++;
        }


    }
    else if(joueur==CPU && !attente && laMainBot)
    {
        //selection
        int compt=0;
        while(compt==0)
        {
            int choix=rand()%m_plateauJeu.vecDominosAP.size();
            if(!m_plateauJeu.vecDominosAP.at(choix)->selectionne)
            {
                m_plateauJeu.vecDominosAP.at(choix)->selectionne=true;
                m_plateauJeu.vecDominosAP.at(choix)->etat=VISIBLE;
                compt++;
            }
        }


    }
}

// ### FONCTION ###

void Joueur::gestionSelectionDom()
{
    int nbreDominoSelectionne=0;

    for(int compt=0;compt<m_plateauJeu.vecDominosAP.size();compt++)
    {
        if(m_plateauJeu.vecDominosAP.at(compt)->selectionne)
        {
            nbreDominoSelectionne++;
        }
    }

    if(nbreDominoSelectionne==2)
    {
        if(!retardTraitement)
        {
            retardTraitement=true;
        }
        else
        {
            retardTraitement=false;
        }
    }

    if(nbreDominoSelectionne==2 && !retardTraitement)
    {
        sf::Time t1=sf::seconds(3.f);
        sf::sleep(t1);
        int tailleVec=m_plateauJeu.vecDominosAP.size();

        //
        bool cotesIdentiques=false;
        int indicEl1=-1;
        int indicEl2=-1;


        int commpt=0;
        while(commpt<tailleVec)
        {
            if(m_plateauJeu.vecDominosAP.at(commpt)->selectionne)
            {
                if(indicEl1==-1)
                {
                    indicEl1=commpt;
                }
                else
                {
                    indicEl2=commpt;
                }
            }
            commpt++;
        }
        std::cout<<"Position 1: "<<indicEl1<<"    Position 2: "<<indicEl2<<std::endl;
        std::cout<<"Domino 1:  "<<m_plateauJeu.vecDominosAP.at(indicEl1)->cote1<<" ; "<<m_plateauJeu.vecDominosAP.at(indicEl1)->cote2<<std::endl;
        std::cout<<"Domino 2:  "<<m_plateauJeu.vecDominosAP.at(indicEl2)->cote1<<" ; "<<m_plateauJeu.vecDominosAP.at(indicEl2)->cote2<<std::endl;

        if(m_plateauJeu.vecDominosAP.at(indicEl1)->cote1==m_plateauJeu.vecDominosAP.at(indicEl2)->cote1 ||
           m_plateauJeu.vecDominosAP.at(indicEl1)->cote1==m_plateauJeu.vecDominosAP.at(indicEl2)->cote2 ||
            m_plateauJeu.vecDominosAP.at(indicEl1)->cote2==m_plateauJeu.vecDominosAP.at(indicEl2)->cote1 ||
           m_plateauJeu.vecDominosAP.at(indicEl1)->cote2==m_plateauJeu.vecDominosAP.at(indicEl2)->cote2)
        {
            cotesIdentiques=true;
        }

        //
        if(cotesIdentiques)
        {
            int indicPos=tailleVec-1;
            int compt2=0;
            while(compt2<tailleVec)
            {
                if(m_plateauJeu.vecDominosAP.at(indicPos)->selectionne)
                {
                if(laMain)
                {
                    m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.push_back(m_plateauJeu.vecDominosAP.at(indicPos));

                }
                else
                {
                    m_plateauJeu.vecJoueurs.at(CPU).vecDominos.push_back(m_plateauJeu.vecDominosAP.at(indicPos));
                }
                m_plateauJeu.vecDominosAP.erase(m_plateauJeu.vecDominosAP.begin()+indicPos);
                }
                indicPos--;
                compt2++;
            }

        }
        else
        {
            m_plateauJeu.vecDominosAP.at(indicEl1)->selectionne=false;
            m_plateauJeu.vecDominosAP.at(indicEl2)->selectionne=false;

            m_plateauJeu.vecDominosAP.at(indicEl1)->etat=RETOURNE;
            m_plateauJeu.vecDominosAP.at(indicEl2)->etat=RETOURNE;
        }


        if(laMain)
        {
            laMain=false;
            laMainBot=true;
            attente=true;

            if(cotesIdentiques)
            {

                animAActiver.push_back(ANIM_JOUEUR1_P2);

                if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.size()==2)
                {
                    posFinalD.x=13*20;
                    posFinalD.y=33*20-5;

                    posFinalD2.x=14*20;
                    posFinalD2.y=33*20-5;
                }
                else
                {
                    int dernEl=m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.size()-1;
                    posFinalD.x=m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(dernEl-2)->sDomino.getPosition().x+20;
                    posFinalD.y=33*20-5;

                    posFinalD2.x=posFinalD.x+20;
                    posFinalD2.y=33*20-5;
                }
            }
            else
            {
                animAActiver.push_back(ANIM_JOUEUR1_C);
                animAActiver.push_back(ANIM_JOUEUR2_V);
            }

        }
        else
        {
            laMain=true;
            laMainBot=false;
            attente=true;

            if(cotesIdentiques)
            {

                animAActiver.push_back(ANIM_JOUEUR2_P2);

                if(m_plateauJeu.vecJoueurs.at(CPU).vecDominos.size()==2)
                {
                    posFinalD.x=15*20;
                    posFinalD.y=2*20+5;

                    posFinalD2.x=16*20;
                    posFinalD2.y=2*20+5;
                }
                else
                {
                    int dernEl=m_plateauJeu.vecJoueurs.at(CPU).vecDominos.size()-1;
                    posFinalD.x=m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(dernEl-2)->sDomino.getPosition().x+20;
                    posFinalD.y=2*20+5;

                    posFinalD2.x=posFinalD.x+20;
                    posFinalD2.y=2*20+5;
                }
            }
            else
            {
                animAActiver.push_back(ANIM_JOUEUR2_C);
                animAActiver.push_back(ANIM_JOUEUR1_V);

            }


        }

    }


}

// ### FONCTION ###

void Joueur::gestMaj()
{
    //...
    if(finPartie())
    {
        jeuFinPartie=true;
        sf::Time t1=sf::seconds(3.f);
        sf::sleep(t1);
    }

    gestBouton();

    //...
    if(!jeuFinPartie)
    {
        //determiner qui doit jouer avant
        if(!laMain && !laMainBot && !attente && m_plateauJeu.typeJeu!=TJ_MEMORY)
        {
            std::cout<<"Entree zone de determination qui va jouer avant"<<std::endl;
            bool aucun=true;

            int compt=0;
            while(compt<2 && aucun)
            {
                int compt2=0;
                while(compt2<m_plateauJeu.vecJoueurs.at(compt).vecDominos.size() && aucun)
                {
                    if(m_plateauJeu.typeJeu==TJ_CLASSIQUE)
                    {
                        aucun=false;
                        laMain=true;
                        attente=true;
                        animAActiver.push_back(ANIM_JOUEUR1_V);
                        animAActiver.push_back(ANIM_JOUEUR2_C);
                    }
                    else if(m_plateauJeu.typeJeu==TJ_5PARTOUT)
                    {
                        if(m_plateauJeu.vecJoueurs.at(compt).vecDominos.at(compt2)->cote1==
                           m_plateauJeu.vecJoueurs.at(compt).vecDominos.at(compt2)->cote2)
                        {
                            aucun=false;
                            if(compt==HUMAIN)
                            {
                                laMain=true;
                                attente=true;
                                animAActiver.push_back(ANIM_JOUEUR1_V);
                                animAActiver.push_back(ANIM_JOUEUR2_C);
                            }
                            else
                            {
                                laMainBot=true;
                                attente=true;
                                animAActiver.push_back(ANIM_JOUEUR2_V);
                                animAActiver.push_back(ANIM_JOUEUR1_C);
                            }
                        }

                    }
                    else if(m_plateauJeu.typeJeu==TJ_MATADOR)
                    {
                        if(m_plateauJeu.vecJoueurs.at(compt).vecDominos.at(compt2)->cote1+m_plateauJeu.vecJoueurs.at(compt).vecDominos.at(compt2)->cote2==0 ||
                           m_plateauJeu.vecJoueurs.at(compt).vecDominos.at(compt2)->cote1+m_plateauJeu.vecJoueurs.at(compt).vecDominos.at(compt2)->cote2==7)
                        {
                            aucun=false;
                            attente=true;
                            if(compt==HUMAIN)
                            {
                                laMain=true;

                                animAActiver.push_back(ANIM_JOUEUR1_V);
                                animAActiver.push_back(ANIM_JOUEUR2_C);
                            }
                            else
                            {
                                laMainBot=true;
                                animAActiver.push_back(ANIM_JOUEUR2_V);
                                animAActiver.push_back(ANIM_JOUEUR1_C);
                            }

                        }

                    }
                    else
                    {

                    }

                    compt2++;
                }
                compt++;
            }

            if(aucun)
            {
                std::cout<<"Bow bow"<<std::endl;
                laMain=true;
                attente=true;
                animAActiver.push_back(ANIM_JOUEUR1_V);
                animAActiver.push_back(ANIM_JOUEUR2_C);
            }
            std::cout<<"Sortie zone de determination qui va jouer avant"<<std::endl;

        }
        else if(!laMain && !laMainBot && !attente && m_plateauJeu.typeJeu==TJ_MEMORY)
        {
            laMain=true;
            attente=true;
            animAActiver.push_back(ANIM_JOUEUR1_V);
            animAActiver.push_back(ANIM_JOUEUR2_C);
        }
        else{}


        //...gestion coups des joueurs
        if(m_plateauJeu.typeJeu!=TJ_MEMORY)
        {
            if(!jeuPause && laMain && !laMainBot && !attente && !piocher)
            {
                if(glisser)
                {
                    glisserDeposerD(GLISSER);
                }

                if(deposer)
                {
                    glisserDeposerD(DEPOSER);
                    arrangerDomino(CADRE_J1);
                    attente=true;
                    if(laMainBot)
                    {
                        animAActiver.push_back(ANIM_JOUEUR1_C);
                        animAActiver.push_back(ANIM_JOUEUR2_V);
                    }

                }

            }
            else if(!jeuPause && !laMain && laMainBot && !attente && !piocher)
            {
                if(m_plateauJeu.typeJeu!=TJ_MEMORY)
                {
                    if(selectionDomino(CPU))
                    {
                        std::cout<<"Domino du Bot selection"<<std::endl;
                        if(m_plateauJeu.vecDominosPoses.size()!=0)
                        {
                            int compt=0;
                            while(compt<m_plateauJeu.vecJoueurs.at(CPU).vecDominos.size())
                            {
                                if(m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->selectionne)
                                {
                                    if(placerDomino(CPU,m_vecDominoABouger.at(0),compt) )
                                    {
                                        //attente=true;
                                        animAActiver.push_back(ANIM_JOUEUR2_COUP);
                                        m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(compt)->etat=VISIBLE;
                                    }
                                    compt+=100;
                                }
                                compt++;
                            }

                        }
                        else
                        {
                            int indicEl=0;
                            int comppt=0;
                            while(comppt<m_plateauJeu.vecJoueurs.at(CPU).vecDominos.size())
                            {
                                if(m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(comppt)->selectionne)
                                {
                                    indicEl=comppt;
                                }

                                comppt++;
                            }


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

                            m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(indicEl)->sDomino.setPosition(22.5f*20,17.5f*20);
                            m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(indicEl)->selectionne=false;
                            m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(indicEl)->auBord=true;

                            m_plateauJeu.vecDominosPoses.insert(m_plateauJeu.vecDominosPoses.end(),m_plateauJeu.vecJoueurs.at(CPU).vecDominos.at(indicEl));
                            m_plateauJeu.vecDominosAuBord.insert(m_plateauJeu.vecDominosAuBord.end(),m_plateauJeu.vecDominosPoses.at(0));
                            m_plateauJeu.vecJoueurs.at(CPU).vecDominos.erase(m_plateauJeu.vecJoueurs.at(CPU).vecDominos.begin()+indicEl);


                            animAActiver.push_back(ANIM_JOUEUR2_C);
                            animAActiver.push_back(ANIM_JOUEUR1_V);
                        }

                        arrangerDomino(CADRE_J2);
                        attente=true;
                        laMain=true;
                        laMainBot=false;
                    }
                    else
                    {
                        if(m_plateauJeu.typeJeu==TJ_CLASSIQUE)
                        {
                            laMain=true;
                            laMainBot=false;
                            m_plateauJeu.vecJoueurs.at(CPU).pass=true;
                            animAActiver.push_back(ANIM_JOUEUR2_C);
                            animAActiver.push_back(ANIM_JOUEUR1_V);
                        }
                        else
                        {
                            if(m_plateauJeu.vecDominosAP.size()==0)
                            {
                                laMain=true;
                                laMainBot=false;
                                m_plateauJeu.vecJoueurs.at(CPU).pass=true;
                            }
                            else
                            {
                                piocher=true;
                                animAActiver.push_back(ANIM_PIOCHE_V);
                                m_plateauJeu.vecJoueurs.at(CPU).piocherD=true;
                                piocherDomino(CPU);
                                attente=true;
                            }

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
        }
        else
        {
            //
            gestionSelectionDom();

            if(!jeuPause && !laMain && laMainBot && !attente && !retardTraitement)
            {
                selectionDominoTMem(CPU);
            }

        }

    }


    //gestion texture
    gestTextureD();
}

// ### FONCTION ###

void Joueur::affichePartie()
{
    m_fenetre->draw(m_sFond);

    //affiche bouton
    afficheBouton();

    //on va afficher les dominos par categorie : DominosPoses ,DominosAPiocher, DominosJ1, DominosJ2

    //indicateur premier domino pose
    if(m_plateauJeu.vecDominosPoses.size()!=0)
    {
        if(m_plateauJeu.vecDominosPoses.at(0)->angle==0)
        {
            m_plateauJeu.sIndicPremDom.setRotation(-90);
            m_fenetre->draw(m_plateauJeu.sIndicPremDom);
        }
        else
        {
            m_fenetre->draw(m_plateauJeu.sIndicPremDom);
        }
    }

    //DominosPoses
    int comptt=0;
    while(comptt<m_plateauJeu.vecDominosPoses.size())
    {
        m_fenetre->draw(m_plateauJeu.vecDominosPoses.at(comptt)->sDomino);
        comptt++;
    }

    //on affiche le support des dominos a piocher
    m_fenetre->draw(m_plateauJeu.sCadreDAP);

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

// ### FONCTION ###

void Joueur::afficheBouton()
{
    m_fenetre->draw(m_sbPause);
}

// ### DESTRUCTEUR ###

Joueur::~Joueur()
{

}
