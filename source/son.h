#ifndef DEF_SON
#define DEF_SON

#include <SFML/Audio.hpp>
#include "enums.h"
#include "constantes.h"
#include "varG.h"

class Son
{
public:
    Son();
    void jouerSon(int type);
    void stopMusique();
    ~Son();

private:
    sf::Sound m_sonBClic, m_sonAutorise,m_sonInterdit;
    sf::Music m_musique;

    sf::SoundBuffer m_bufBClic,m_bufAutorise,m_bufInterdit;
};

#endif // DEF_SON
