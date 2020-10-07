/*
 * Author: Antoine Rochat
 * Created on 09 sep 2020
 * Modified on 07. aug 2020 by Berney Alec, Forestier Quentin, Herzig Melvyn
 */

#ifndef CFC_H
#define CFC_H

#include <vector>
#include <algorithm>
#include "DFS.h"

// Classe mettant en oeuvre les composantes fortement connexes
template<typename GraphType>
class CFC
{
protected:
   // numéro de la CFC à laquelle appartient chaque sommet (-1 si pas encore assigné)
   std::vector<int> id;

   // nombre de composantes connexes
   int count;

public:

   /**
    * @brief Définit si deux sommets sont connectés.
    * @param v Premier sommet.
    * @param w Second sommet.
    * @return Vrai si les deux sommets appartienent à la même compsante fortement connexe.
    */
   bool Connected (int v, int w)
   {
      return Id(v) == Id(w);
   }


   /**
    * @brief Cherche le numéro de composante fortement connexe du sommet.
    * @param v Sommet.
    * @return Retourne le numéro de la composante fortement connexe associé à v.
    */
   int Id (int v)
   {
      return id.at(v);
   }

   /**
    * @brief Retourne le nombre de composantes fortement connexes du graphe.
    * @return Le nombre de composantes fortement connexes.
    */
   int Count ()
   {
      return count;
   }
};

template<typename GraphType>
class KosarajuSharirCFC : public CFC<GraphType>
{

public:

   /**
    * @brief Définit les conposantes fortement connexes pour le graphe g et son transposé.
    * @param g Graphe.
    * @param gReverse Graphe transposé de g.
    */
   KosarajuSharirCFC (const GraphType &g, const GraphType &gReverse): CFC<GraphType>()
   {
      std::vector<int> postOrdre;
      CFC<GraphType>::id.resize(g.V());
      std::fill_n(CFC<GraphType>::id.begin(), g.V(), -1);
      unsigned noCFC = 0;

      DFSIter<GraphType> DFS  {g};
      DFSIter<GraphType> DFST {gReverse};

      DFST.visitGraph([](int v) {}, [&postOrdre](int v){postOrdre.push_back(v);});
      std::reverse(postOrdre.begin(), postOrdre.end());

      for(int i = 0; i < postOrdre.size(); ++i)
      {
         if(CFC<GraphType>::Id(postOrdre[i]) == -1)
         {
            DFS.visit(postOrdre[i],[this, &noCFC](int v){this->id[v] = noCFC;}, [](int v) {});
            ++noCFC;
         }
      }

      this->count = noCFC;
   }
};

#endif

