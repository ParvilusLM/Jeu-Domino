#include "animations.h"

Animations::Animations(Decor& decor):m_pDecor(0)
{
    m_pDecor=&decor;
    m_animDistrib=false;
    m_animJoueur1C=false;
    m_animJoueur1V=false;
    m_animJoueur2C=false;
    m_animJoueur2V=false;
    m_animPiocheC=false;
    m_animPiocheV=false;
    m_animJoueur2Coup=false;
    m_animJoueur1P=false;
    m_animJoueur2P=false;

    m_timer=0.f;
    m_delai=0.001f;


}

void Animations::gestionAnimation()
{
    if(m_animDistrib)
    {
        sf::Vector2f posReferenceJ1,posReferenceJ2;
        posReferenceJ1.x=13*20;
        posReferenceJ1.y=33*20-5;

        posReferenceJ2.x=15*20;
        posReferenceJ2.y=2*20+5;

        int elementsEnPlace=0;

        int compt=0;
        while(compt<2)
        {
            int compt2=0;
            while(compt2<7)
            {
                bool xFinal=false,yFinal=false;
                if(compt==0)
                {
                    if(m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.getPosition().x != posReferenceJ1.x +(compt2*70) )
                    {
                        if(m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.getPosition().x > posReferenceJ1.x +(compt2*70))
                        {
                            m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.move(-1.f,0);
                        }
                        else
                        {
                            m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.move(1.f,0);
                        }

                    }
                    else
                    {
                        xFinal=true;
                    }


                    if(m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.getPosition().y != posReferenceJ1.y)
                    {
                        m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.move(0.f,1.f);
                    }
                    else
                    {
                        yFinal=true;
                    }

                    if(xFinal && yFinal)
                    {
                        elementsEnPlace++;
                    }

                }
                else
                {
                    bool xFinal=false,yFinal=false;

                    if(m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.getPosition().x != posReferenceJ2.x +(compt2*50) )
                    {
                        if(m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.getPosition().x > posReferenceJ2.x +(compt2*50))
                        {
                            m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.move(-1.f,0);
                        }
                        else
                        {
                            m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.move(1.f,0);
                        }

                    }
                    else
                    {
                        xFinal=true;
                    }

                    if(m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.getPosition().y != posReferenceJ2.y)
                    {
                        m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(compt).vecDominos.at(compt2)->sDomino.move(0.f,-1.f);
                    }
                    else
                    {
                        yFinal=true;
                    }

                    if(xFinal && yFinal)
                    {
                        elementsEnPlace++;
                    }

                }
                compt2++;
            }
            compt++;
        }

        if(elementsEnPlace==14)
        {
            m_animDistrib=false;
            m_pDecor->getJoueur().retourneDominos(HUMAIN,true);
            m_pDecor->getJoueur().retourneDominos(CPU,true);
            sf::Vector2f augmenteScale;
            augmenteScale.x=0.4;
            augmenteScale.y=0.4;
            m_pDecor->getJoueur().changementEchelleD(DOMINOS_JOUEUR1,augmenteScale);
            m_pDecor->getJoueur().changementEchelleD(DOMINOS_JOUEUR2,augmenteScale);
            m_animPiocheC=true;
            std::cout<<"Fin animDistribution"<<std::endl;
        }
    }


    if(m_animJoueur1C)
    {

        if(m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(HUMAIN).sCadreJoueur.getPosition().y < 31*20+10)
        {
            m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(HUMAIN).sCadreJoueur.move(0,1.f);

            int compt=0;
            while(compt < m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(HUMAIN).vecDominos.size())
            {
                m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(HUMAIN).vecDominos.at(compt)->sDomino.move(0,1.f);
                compt++;
            }
        }
        else
        {
            attente=false;
            m_animJoueur1C=false;
            std::cout<<"Fin animJoueur1C"<<std::endl;
        }

    }


    if(m_animJoueur1V)
    {
        if(m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(HUMAIN).sCadreJoueur.getPosition().y > 31*20)
        {
            m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(HUMAIN).sCadreJoueur.move(0,-1.f);

            int compt=0;
            while(compt < m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(HUMAIN).vecDominos.size())
            {
                m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(HUMAIN).vecDominos.at(compt)->sDomino.move(0,-1.f);
                compt++;
            }
        }
        else
        {
            attente=false;
            m_animJoueur1V=false;
            std::cout<<"Fin animJoueur1V"<<std::endl;
        }
    }

    if(m_animPiocheC)
    {
        //deplacer le support et les dominos du vector vecDominosAP vers le bas
        if(m_pDecor->getJoueur().getPlateauJeu().sCadreDAP.getPosition().y < 700)
        {
            m_pDecor->getJoueur().getPlateauJeu().sCadreDAP.move(0,1.f);

            int compt=0;
            while(compt < m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.size())
            {
                m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(compt)->sDomino.move(0,1.f);
                compt++;
            }
        }
        else
        {
            attente=false;
            m_animPiocheC=false;
            std::cout<<"Fin animPiocheC"<<std::endl;
        }

    }


    if(m_animPiocheV)
    {
        if(m_pDecor->getJoueur().getPlateauJeu().sCadreDAP.getPosition().y > 25*20)
        {
            m_pDecor->getJoueur().getPlateauJeu().sCadreDAP.move(0,-1.f);

            int compt=0;
            while(compt < m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.size())
            {
                m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(compt)->sDomino.move(0,-1.f);
                compt++;
            }
        }
        else
        {
            m_animPiocheV=false;
            attente=false;

            if(piocher && m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(CPU).piocherD)
            {
                m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(CPU).piocherD=false;
                m_animJoueur2P=true;
                attente=true;
            }

            std::cout<<"Fin animPiocheV"<<std::endl;
        }
    }


    if(m_animJoueur2C)
    {
        if(m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(CPU).sCadreJoueur.getPosition().y > -10.f)
        {

            m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(CPU).sCadreJoueur.move(0,-1.f);

            int compt=0;
            while(compt < m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(CPU).vecDominos.size())
            {
                m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(CPU).vecDominos.at(compt)->sDomino.move(0,-1.f);
                compt++;
            }
        }
        else
        {
            attente=false;
            m_animJoueur2C=false;
            std::cout<<"Fin animJoueur2C"<<std::endl;
        }

    }


    if(m_animJoueur2V)
    {
        if(m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(CPU).sCadreJoueur.getPosition().y < 0)
        {
            m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(CPU).sCadreJoueur.move(0,1.f);

            int compt=0;
            while(compt < m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(CPU).vecDominos.size())
            {
                m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(CPU).vecDominos.at(compt)->sDomino.move(0,1.f);
                compt++;
            }
        }
        else
        {
            attente=false;
            m_animJoueur2V=false;
            std::cout<<"Fin animJoueur2V"<<std::endl;
        }

    }

    if(m_animJoueur2Coup)
    {
        int compt=0;
        while(compt<m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(CPU).vecDominos.size())
        {
            if(m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(CPU).vecDominos.at(compt)->selectionne)
            {

            }
            compt++;
        }
    }

    if(m_animJoueur1P)
    {
        std::cout<<"animation Pioche Joueur1"<<std::endl;
        int commpt=0;
        while(commpt<m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.size())
        {
            bool xFinal=false,yFinal=false;
            if(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->selectionne)
            {
                if(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.getPosition().x<posFinalD.x)
                {
                    m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.move(3.f,0);
                    if(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.getPosition().x>posFinalD.x)
                    {
                        m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.setPosition(posFinalD.x,m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.getPosition().y);
                    }
                }
                else if(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.getPosition().x>posFinalD.x)
                {
                    m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.move(-3.f,0);
                    if(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.getPosition().x<posFinalD.x)
                    {
                        m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.setPosition(posFinalD.x,m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.getPosition().y);
                    }
                }
                else
                {
                    xFinal=true;
                }


                if(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.getPosition().y<posFinalD.y)
                {
                    m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.move(0.f,3.f);
                    if(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.getPosition().y>posFinalD.y)
                    {
                        m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.setPosition(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.getPosition().x,posFinalD.y);
                    }
                }
                else
                {
                    yFinal=true;
                }

            }

            if(xFinal && yFinal)
            {
                piocher=false;
                attente=false;
                m_animJoueur1P=false;
                m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->selectionne=false;

                //on met le domino dans le vecteur du vecJoueurs correspondant
                m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(HUMAIN).vecDominos.push_back(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt));
                m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.erase(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.begin()+commpt);
                m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(HUMAIN).piocherD=false;
                commpt+=100;
            }
            commpt++;
        }
    }

    if(m_animJoueur2P)
    {
        std::cout<<"animation Pioche Joueur2"<<std::endl;
        int commpt=0;
        while(commpt<m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.size())
        {
            bool xFinal=false,yFinal=false;
            if(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->selectionne)
            {
                if(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.getPosition().x<posFinalD.x)
                {
                    m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.move(3.f,0);
                    if(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.getPosition().x>posFinalD.x)
                    {
                        m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.setPosition(posFinalD.x,m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.getPosition().y);
                    }
                }
                else if(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.getPosition().x>posFinalD.x)
                {
                    m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.move(-3.f,0);
                    if(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.getPosition().x<posFinalD.x)
                    {
                        m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.setPosition(posFinalD.x,m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.getPosition().y);
                    }
                }
                else
                {
                    xFinal=true;
                }

                if(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.getPosition().y>posFinalD.y)
                {
                    m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.move(0.f,-3.f);
                    if(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.getPosition().y<posFinalD.y)
                    {
                        m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.setPosition(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->sDomino.getPosition().x,posFinalD.y);
                    }
                }
                else
                {
                    yFinal=true;
                }

            }

            if(xFinal && yFinal)
            {
                piocher=false;
                attente=false;
                //laMain=true;
                //laMainBot=false;
                m_animJoueur2P=false;
                m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt)->selectionne=false;

                //on met le domino dans le vecteur du vecJoueurs correspondant
                m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(CPU).vecDominos.push_back(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.at(commpt));
                m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.erase(m_pDecor->getJoueur().getPlateauJeu().vecDominosAP.begin()+commpt);
                m_pDecor->getJoueur().getPlateauJeu().vecJoueurs.at(CPU).piocherD=false;
                commpt+=100;
            }
            commpt++;
        }

    }

}

void Animations::debuterAnim(int typeAnim)
{
    if(typeAnim==ANIM_DISTRIBUTION)
    {
        m_animDistrib=true;
    }
    else if(typeAnim==ANIM_JOUEUR1_C)
    {
        m_animJoueur1C=true;
    }
    else if(typeAnim==ANIM_JOUEUR1_V)
    {
        m_animJoueur1V=true;
    }
    else if(typeAnim==ANIM_JOUEUR2_C)
    {
        m_animJoueur2C=true;
    }
    else if(typeAnim==ANIM_JOUEUR2_V)
    {
        m_animJoueur2V=true;
    }
    else if(typeAnim==ANIM_PIOCHE_C)
    {
        m_animPiocheC=true;
    }
    else if(typeAnim==ANIM_PIOCHE_V)
    {
        m_animPiocheV=true;
    }
    else if(typeAnim==ANIM_JOUEUR2_COUP)
    {
        m_animJoueur2Coup=true;
    }
    else if(typeAnim==ANIM_JOUEUR1_P)
    {
        m_animJoueur1P=true;
    }
    else if(typeAnim==ANIM_JOUEUR2_P)
    {
        m_animJoueur2P=true;
    }
    else
    {

    }
}

void Animations::gestMaJ()
{
    float tempsEcoule =m_horlorge.getElapsedTime().asSeconds();
    m_horlorge.restart();
    m_timer+=tempsEcoule;

    if(m_animDistrib || m_animJoueur1C || m_animJoueur1V || m_animJoueur2C || m_animJoueur2V || m_animPiocheC ||
       m_animPiocheV || m_animJoueur2Coup || m_animJoueur1P || m_animJoueur2P)
    {
        if(m_timer>=m_delai)
        {
            gestionAnimation();
            m_timer=0.f;
        }
    }
}

Animations::~Animations()
{

}
