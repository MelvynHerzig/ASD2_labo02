/*
 * File:   TopologicalSort.h
 * Author: Olivier Cuisenaire
 *
 * Created on 08. octobre 2014, 14:07
 * Updated on 9 sept. by Antoine Rochat
 */

#ifndef ASD2_TopologicalSort_h
#define ASD2_TopologicalSort_h

#include "DirectedCycle.h"
#include "DFS.h"
#include <list>
#include <vector>
#include <exception>

template<typename GraphType>
class TopologicalSort {
private:
/****
*
*  AJOUTEZ ICI VOS STRUCTURES PRIVEES
*
****/

public:
    // constructeur
    TopologicalSort(const GraphType& g) {
/****
*
*  A IMPLEMENTER
*  Vous devez verifier la presence d'un cycle, auquel cas il faut lancer une  GraphNotDAGException
*
****/
    }

    // tableau contenant l'ordre de parcours des indexes des sommets dans le graphe
    const std::vector<int>& Order() {
/****
*
*  A IMPLEMENTER
*
****/
    }

    //exception si le graphe n'est pas un DAG (Directed Acyclic Graph)
    class GraphNotDAGException : public std::exception {

    private:
        //indexes des sommets du cycle qui empeche le tris topologique
        const std::list<int> cycle;

    public:
        GraphNotDAGException(const std::list<int> cycle) noexcept: exception(), cycle(cycle) {

        }

        virtual const char* what() const noexcept {
            return "Topological sort impossible : the graph is not a DAG";
        }

        const std::list<int>& Cycle() const noexcept {
            return cycle;
        }
    };
};

#endif
