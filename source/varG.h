#ifndef DEF_VARG
#define DEF_VARG
#include <SFML/Graphics.hpp>

extern bool jeuEnCours;
extern bool jeuPause;
extern bool jeuDebut;
extern bool jeuRejouer;
extern bool jeuFinPartie;
extern bool boutonPresse;
extern bool laMain, laMainBot;
extern int sourisX,sourisY;
extern bool glisser,deposer,piocher;
extern sf::Vector2f posFinalD;
extern std::vector<int > animAActiver;
extern bool attente;
#endif // DEF_VARG
