/*
 * File:   DirectedCycle.h
 * Author: Olivier Cuisenaire
 *
 * Created on 08. octobre 2014, 10:46
 * Classe permettant la detection de cycle sur un graphe oriente
 */

#ifndef ASD2_DirectedCycle_h
#define ASD2_DirectedCycle_h

#include <list>
#include <vector>

template<typename GraphType>
class DirectedCycle {
private:
/****
*
*  AJOUTEZ ICI VOS STRUCTURES PRIVEES
*
****/

public:

    // constructeur
    DirectedCycle(const GraphType& g) : G(g) {
/****
*
*  A IMPLEMENTER
*  Nous vous conseillons de ne pas utiliser la classe DFS fournie cette détection de cycle
*
****/
    }

    // indique la presence d'un cycle
    bool HasCycle() {
/****
*
*  A IMPLEMENTER
*
****/
    }

    // liste les indexes des sommets formant une boucle
    std::list<int> Cycle() {
/****
*
*  A IMPLEMENTER
*
****/
    }
};

#endif
