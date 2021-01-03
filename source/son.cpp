#include "son.h"

Son::Son()
{
    m_bufBClic.loadFromFile("donnees/select-granted.wav");
    m_bufAutorise.loadFromFile("donnees/correct.wav");
    m_bufInterdit.loadFromFile("donnees/error.wav");

    //pour la musique
    if(!m_musique.openFromFile("donnees/musique.mp3"))
    {

    }

    m_musique.setVolume(60);
    m_musique.setLoop(true);
    //m_musique.play();


    //...
    m_sonBClic.setBuffer(m_bufBClic);
    m_sonAutorise.setBuffer(m_bufAutorise);
    m_sonInterdit.setBuffer(m_bufInterdit);
}

void Son::jouerSon(int type)
{
    if(type==SON_BCLIK)
    {
        m_sonBClic.play();
    }
    else if(type==SON_AUTORISE)
    {
        m_sonAutorise.play();
    }
    else if(type==SON_INTERDIT)
    {
        m_sonInterdit.play();
    }
    else if(type==SON_MUSIQUE)
    {
        m_musique.play();
    }
    else{}
}

Son::~Son()
{

}
