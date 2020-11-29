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
            m_plateauJeu.vecDominosAP.erase(m_plateauJeu.vecDominosAP.begin()+27-indicD);

            m_plateauJeu.vecJoueurs.at(compt).vecDominos.insert(m_plateauJeu.vecJoueurs.at(compt).vecDominos.end(),pDomino);
            compt2++;
            indicD++;
        }
        compt++;
    }

    std::cout<<"Pointeur reference :  "<<m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.size()<<std::endl;
    std::cout<<"Pointeur reference :  "<<m_plateauJeu.vecJoueurs.at(CPU).vecDominos.size()<<std::endl;
}

void Joueur::piocherDomino(int joueur)
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
                if(m_plateauJeu.typeJeu==TJ_CLASSIQUE) //Jeu Classique
                {
                    if(m_plateauJeu.vecDominosPoses.size()==0)
                    {
                        m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->selectionne=true;
                        dominoSelect=true;
                    }
                    else
                    {
                        //on va tester les dominos du vecteur vecDominosAuBord avec celui pointe par le curseur
                        if(coupPossible(HUMAIN,compt))
                        {
                            m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(compt)->selectionne=true;
                            dominoSelect=true;
                        }

                    }

                }
                else if(m_plateauJeu.typeJeu==TJ_5PARTOUT) //Jeu 5Partout
                {

                }
                else if(m_plateauJeu.typeJeu==TJ_MATADOR) //Jeu Matador
                {

                }
                else //Jeu Memory
                {

                }

            }
            compt++;
        }

    }
    return dominoSelect;
}

bool Joueur::coupPossible(int joueur, int noDomino)
{
    bool possible=false;

    if(joueur==HUMAIN && noDomino!=-1)
    {
        //on parcout le vecteur vecDominosAuBord pour savoir sil y a correspondance
        int compt=0;
        while(compt<m_plateauJeu.vecDominosAuBord.size())
        {
            if(m_plateauJeu.vecDominosAuBord.at(compt)->cote1==m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDomino)->cote1 ||
               m_plateauJeu.vecDominosAuBord.at(compt)->cote1==m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDomino)->cote2 ||
               m_plateauJeu.vecDominosAuBord.at(compt)->cote2==m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDomino)->cote1 ||
               m_plateauJeu.vecDominosAuBord.at(compt)->cote2==m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDomino)->cote2)
            {
                possible=true;
            }
            compt++;
        }
    }
    else if(joueur==CPU && noDomino!=-1)
    {

    }
    else
    {

    }

    return possible;
}

bool Joueur::placerDomino(int joueur, int noDominoP,int noDominoE)
{
    bool placerDPossible=false;
    std::cout<<"Entree fonction placerDomino"<<std::endl;
    if(joueur==HUMAIN)
    {
        int rotation=0;
        bool coteG,coteD,coteH,coteB;

        //on determine la rotation du domino sur lequel on doit attacher
        int compt=0;
        while(compt<m_plateauJeu.vecDominosPoses.size())
        {
            if(m_plateauJeu.vecDominosPoses.at(compt)->noDomino==noDominoP)
            {
                rotation=m_plateauJeu.vecDominosPoses.at(compt)->angle;
                coteG=m_plateauJeu.vecDominosPoses.at(compt)->attacheGP;
                coteD=m_plateauJeu.vecDominosPoses.at(compt)->attacheDP;
                coteH=m_plateauJeu.vecDominosPoses.at(compt)->attacheHP;
                coteB=m_plateauJeu.vecDominosPoses.at(compt)->attacheBP;

            }
            compt++;
        }

        //on determine la taille du vecteur vecDominosPoses pour savoir si c'est le premier double pose
        int tailleVecDomPoses=m_plateauJeu.vecDominosPoses.size();


        //on determine les cotes sur lesquels on peut attacher le nouveau domino
        int compt2=0;
        while(compt2<m_plateauJeu.vecDominosPoses.size())
        {
            if(m_plateauJeu.vecDominosPoses.at(compt2)->noDomino==noDominoP)
            {
                sf::FloatRect boiteEDomP=m_plateauJeu.vecDominosPoses.at(compt2)->sDomino.getGlobalBounds();

                //on place le domino selon cote valide
                if( (coteG && (m_plateauJeu.vecDominosPoses.at(compt2)->cote1==m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote1 && m_plateauJeu.vecDominosPoses.at(compt2)->angle==-90)) ||
                    (coteG && (m_plateauJeu.vecDominosPoses.at(compt2)->cote1==m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote2 && m_plateauJeu.vecDominosPoses.at(compt2)->angle==-90)) ||
                    (coteG && (m_plateauJeu.vecDominosPoses.at(compt2)->cote2==m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote1 && m_plateauJeu.vecDominosPoses.at(compt2)->angle==90)) ||
                    (coteG && (m_plateauJeu.vecDominosPoses.at(compt2)->cote2==m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote2 && m_plateauJeu.vecDominosPoses.at(compt2)->angle==90)) ||
                    (coteG && (m_plateauJeu.vecDominosPoses.at(compt2)->cote1==m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote1 && m_plateauJeu.vecDominosPoses.at(compt2)->angle==0)) ||
                    (coteG && (m_plateauJeu.vecDominosPoses.at(compt2)->cote1==m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote2 && m_plateauJeu.vecDominosPoses.at(compt2)->angle==0)))
                {

                    if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote1 == m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote2) //si c'est un double
                    {
                        m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->sDomino.setPosition(m_plateauJeu.vecDominosPoses.at(compt2)->sDomino.getPosition().x-boiteEDomP.width+(boiteEDomP.height/2),
                                                                                                         m_plateauJeu.vecDominosPoses.at(compt2)->sDomino.getPosition().y);
                    }
                    else
                    {
                        if(m_plateauJeu.vecDominosPoses.at(compt2)->cote1 == m_plateauJeu.vecDominosPoses.at(compt2)->cote2)
                        {
                            if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote1==m_plateauJeu.vecDominosPoses.at(compt2)->cote1)
                            {
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->angle=90.f;
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->sDomino.setRotation(90.f);
                            }
                            else
                            {
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->angle=-90.f;
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->sDomino.setRotation(-90.f);
                            }

                            m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->sDomino.setPosition(m_plateauJeu.vecDominosPoses.at(compt2)->sDomino.getPosition().x-(boiteEDomP.width/2)-(boiteEDomP.height/2),
                                                                                                             m_plateauJeu.vecDominosPoses.at(compt2)->sDomino.getPosition().y);
                        }
                        else
                        {
                            if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote1==m_plateauJeu.vecDominosPoses.at(compt2)->cote1 && m_plateauJeu.vecDominosPoses.at(compt2)->angle==-90.f)
                            {
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->angle=90.f;
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->sDomino.setRotation(90.f);
                            }
                            else if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote1==m_plateauJeu.vecDominosPoses.at(compt2)->cote2 && m_plateauJeu.vecDominosPoses.at(compt2)->angle==90.f)
                            {
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->angle=90.f;
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->sDomino.setRotation(90.f);
                            }
                            else if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote2==m_plateauJeu.vecDominosPoses.at(compt2)->cote1 && m_plateauJeu.vecDominosPoses.at(compt2)->angle==-90.f)
                            {
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->angle=-90.f;
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->sDomino.setRotation(-90.f);
                            }
                            else
                            {
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->angle=-90.f;
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->sDomino.setRotation(-90.f);
                            }

                            m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->sDomino.setPosition(m_plateauJeu.vecDominosPoses.at(compt2)->sDomino.getPosition().x-boiteEDomP.width,
                                                                                                             m_plateauJeu.vecDominosPoses.at(compt2)->sDomino.getPosition().y);
                        }
                    }

                    coteG=false;
                    m_plateauJeu.vecDominosPoses.at(compt2)->attacheGP=false;
                    m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->attacheDP=false;
                    m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->attacheHP=false;
                    m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->attacheBP=false;
                    placerDPossible=true;
                }
                else if( (coteD && (m_plateauJeu.vecDominosPoses.at(compt2)->cote1==m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote1 && m_plateauJeu.vecDominosPoses.at(compt2)->angle==90)) ||
                    (coteD && (m_plateauJeu.vecDominosPoses.at(compt2)->cote1==m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote2 && m_plateauJeu.vecDominosPoses.at(compt2)->angle==90)) ||
                    (coteD && (m_plateauJeu.vecDominosPoses.at(compt2)->cote2==m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote1 && m_plateauJeu.vecDominosPoses.at(compt2)->angle==-90)) ||
                    (coteD && (m_plateauJeu.vecDominosPoses.at(compt2)->cote2==m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote2 && m_plateauJeu.vecDominosPoses.at(compt2)->angle==-90)) ||
                    (coteD && (m_plateauJeu.vecDominosPoses.at(compt2)->cote1==m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote1 && m_plateauJeu.vecDominosPoses.at(compt2)->angle==0)) ||
                    (coteD && (m_plateauJeu.vecDominosPoses.at(compt2)->cote1==m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote2 && m_plateauJeu.vecDominosPoses.at(compt2)->angle==0))  )
                {
                    if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote1 == m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote2) //si c'est un double
                    {
                        m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->sDomino.setPosition(m_plateauJeu.vecDominosPoses.at(compt2)->sDomino.getPosition().x+boiteEDomP.width-(boiteEDomP.height/2),
                                                                                                         m_plateauJeu.vecDominosPoses.at(compt2)->sDomino.getPosition().y);
                    }
                    else
                    {
                        if(m_plateauJeu.vecDominosPoses.at(compt2)->cote1 == m_plateauJeu.vecDominosPoses.at(compt2)->cote2)
                        {
                            if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote1==m_plateauJeu.vecDominosPoses.at(compt2)->cote1)
                            {
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->angle=-90.f;
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->sDomino.setRotation(-90.f);
                            }
                            else
                            {
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->angle=90.f;
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->sDomino.setRotation(90.f);
                            }

                            m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->sDomino.setPosition(m_plateauJeu.vecDominosPoses.at(compt2)->sDomino.getPosition().x+(boiteEDomP.width/2)+(boiteEDomP.height/2),
                                                                                                             m_plateauJeu.vecDominosPoses.at(compt2)->sDomino.getPosition().y);
                        }
                        else
                        {
                            if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote1==m_plateauJeu.vecDominosPoses.at(compt2)->cote1 && m_plateauJeu.vecDominosPoses.at(compt2)->angle==90.f)
                            {
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->angle=-90.f;
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->sDomino.setRotation(-90.f);
                            }
                            else if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote1==m_plateauJeu.vecDominosPoses.at(compt2)->cote2 && m_plateauJeu.vecDominosPoses.at(compt2)->angle==90.f)
                            {
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->angle=90.f;
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->sDomino.setRotation(90.f);
                            }
                            else if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->cote2==m_plateauJeu.vecDominosPoses.at(compt2)->cote1 && m_plateauJeu.vecDominosPoses.at(compt2)->angle==-90.f)
                            {
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->angle=-90.f;
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->sDomino.setRotation(-90.f);
                            }
                            else
                            {
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->angle=90.f;
                                m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->sDomino.setRotation(90.f);
                            }

                            m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->sDomino.setPosition(m_plateauJeu.vecDominosPoses.at(compt2)->sDomino.getPosition().x+boiteEDomP.width,
                                                                                                             m_plateauJeu.vecDominosPoses.at(compt2)->sDomino.getPosition().y);
                        }
                    }

                    coteD=false;
                    m_plateauJeu.vecDominosPoses.at(compt2)->attacheDP=false;
                    m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->attacheGP=false;
                    m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->attacheHP=false;
                    m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->attacheBP=false;
                    placerDPossible=true;
                }
                else if(coteH)
                {
                    coteH=false;
                    m_plateauJeu.vecDominosPoses.at(compt2)->attacheHP=false;
                    m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->attacheBP=false;
                    m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->attacheGP=false;
                    m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->attacheDP=false;
                    placerDPossible=true;
                }
                else if(coteB)
                {
                    coteB=false;
                    m_plateauJeu.vecDominosPoses.at(compt2)->attacheBP=false;
                    m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->attacheHP=false;
                    m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->attacheGP=false;
                    m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(noDominoE)->attacheDP=false;
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
    else
    {

    }
    return placerDPossible;

    std::cout<<"Sortie fonction placerDomino"<<std::endl;
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
                    if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->cote1!=m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->cote2)
                    {
                        m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->angle=90;
                        m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->sDomino.setRotation(90.f);

                        m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->attacheHP=false;
                        m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->attacheBP=false;

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
                    //std::cout<<"Debut action deposer domino"<<std::endl;
                    int compt2=0;
                    while(compt2<m_plateauJeu.vecDominosAuBord.size())
                    {
                        if(m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->sDomino.getGlobalBounds().intersects(m_plateauJeu.vecDominosAuBord.at(compt2)->sDomino.getGlobalBounds()) &&
                           (m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->cote1==m_plateauJeu.vecDominosAuBord.at(compt2)->cote1  ||
                            m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->cote1==m_plateauJeu.vecDominosAuBord.at(compt2)->cote2 ||
                            m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->cote2==m_plateauJeu.vecDominosAuBord.at(compt2)->cote1 ||
                            m_plateauJeu.vecJoueurs.at(HUMAIN).vecDominos.at(indicEl)->cote2==m_plateauJeu.vecDominosAuBord.at(compt2)->cote2 ))
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
                    if(glisser)
                    {
                        deposer=false;
                    }

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
            int pX=comptt%8;
            int pY=comptt/8;

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

    if(!jeuPause)
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
