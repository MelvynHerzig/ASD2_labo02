/*
 * File:   TopologicalSort.h
 * Author: Olivier Cuisenaire
 *
 * Created on 08. octobre 2014, 14:07
 * Updated on 9 sept. by Antoine Rochat
 * Modified by Berney Alec, Forestier Quentin, Herzig Melvyn on 30 Sep. 2020
 */

#ifndef ASD2_TopologicalSort_h
#define ASD2_TopologicalSort_h

#include "DirectedCycle.h"
#include "DFS.h"
#include <list>
#include <vector>
#include <exception>

template<typename GraphType>
class TopologicalSort
{
private:

   DirectedCycle<GraphType> DC;
   const GraphType& G;

   std::vector<int> order;

public:

   /**
    * @brief Constructeur, vérifie si le graphe contient un cycle.
    * @param g Graphe a trié topologiquement.
    * @throws GraphNotDAGException si le graphe contient un cycle
    */
   TopologicalSort (const GraphType &g) : DC(g), G(g)
   {
      if(DC.HasCycle()) throw GraphNotDAGException(DC.Cycle());
   }

   // tableau contenant l'ordre de parcours des indexes des sommets dans le graphe
   const std::vector<int>& Order ()
   {
      DFSIter<GraphType> dfs (G);
      dfs.visitGraph([](int v) {}, [this](int v){order.push_back(v);});
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
