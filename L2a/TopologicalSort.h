/*
 * File:   TopologicalSort.h
 * Author: Olivier Cuisenaire
 *
 * Created on 08. octobre 2014, 14:07
 * Updated on 9 sept. by Antoine Rochat
 * Modified on 02 Oct. 2020 by Berney Alec, Forestier Quentin, Herzig Melvyn
 */

#ifndef ASD2_TopologicalSort_h
#define ASD2_TopologicalSort_h

#include "DirectedCycle.h"
#include "DFS.h"
#include <list>
#include <vector>
#include <exception>

/*
 * Nous considérons que le graphe référencé ne change pas.
 * C'est pourquoi nous avons implémenté les opérations de tri topologique dans
 * le constructeur. Si, les graphes référencés sont susceptibles de changer,
 * il faudrait déplacer l'implémentation du constructeur à la fonction Order.
 */
template<typename GraphType>
class TopologicalSort
{
private:

   const GraphType& G;
   std::vector<int> order;

public:

   /**
    * @brief Constructeur, vérifie si le graphe contient un cycle.
    * @param g Graphe a trié topologiquement.
    * @throws GraphNotDAGException si le graphe contient un cycle
    */
   TopologicalSort (const GraphType &g) : G(g)
   {
      DirectedCycle<GraphType> DC = {G};
      if(DC.HasCycle()) throw GraphNotDAGException(DC.Cycle());

      GraphType GT = G.reverse();
      DFSIter<GraphType> dfs (GT);
      dfs.visitGraph([](int v) {}, [this](int v){order.push_back(v);});
      std::reverse(order.begin(), order.end());

      /* Peut également être écrit de cette façon. Ceci débouche sur un ordre topologique
       * mais il ne correspond pas au paterne du codecheck bien qu'il passe checkOrder.
       *
       * DFSIter<GraphType> dfs (G);
       * dfs.visitGraph([](int v) {}, [this](int v){order.push_back(v);});
       */
   }

   /**
    * @brief Retourne le tableau contenant l'ordre topologique.
    * @return Tableau d'ordre topologique.
    */
   const std::vector<int>& Order ()
   {
      return order;
   }

   //exception si le graphe n'est pas un DAG (Directed Acyclic Graph)
   class GraphNotDAGException : public std::exception
   {

   private:
      //indexes des sommets du cycle qui empeche le tris topologique
      const std::list<int> cycle;

   public:
      GraphNotDAGException (const std::list<int> cycle) noexcept: exception(), cycle(cycle)
      {}

      virtual const char *what () const noexcept
      {
         return "Topological sort impossible : the graph is not a DAG";
      }

      const std::list<int>& Cycle () const noexcept
      {
         return cycle;
      }
   };
};

#endif
