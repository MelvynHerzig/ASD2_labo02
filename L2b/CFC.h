/*
 * Author: Antoine Rochat
 * Created on 09 sep 2020
 */

#ifndef CFC_H
#define CFC_H

#include <vector>
#include <algorithm>
#include "DFS.h"

// Classe mettant en oeuvre les composantes fortement connexes
template<typename GraphType>
class CFC {
protected:
    // numéro de la CFC à laquelle appartient chaque sommet (-1 si pas encore assigné)
    std::vector<int> id;

    // nombre de composantes connexes
    int count;

public:
    // v et w sont-ils connectés ?
    bool Connected(int v, int w) {
        return Id(v) == Id(w);
    }

    // à quelle CFC appartient v ?
    int Id(int v) {
        return id.at(v);
    }

    // combien y a-t-il de CC ?
    int Count() {
        return count;
    }
};

template<typename GraphType>
class KosarajuSharirCFC : public CFC<GraphType> {

public:

    // Constructeur a partir du graphe g et du graphe inverse de g
    KosarajuSharirCFC(const GraphType& g, const GraphType& gReverse) {
/****
*
*  A IMPLEMENTER
*  Implémenter l'algorithme de KosarajuSharir en utilisant le parcours en profondeur fourni
*
****/
    }
};

#endif

