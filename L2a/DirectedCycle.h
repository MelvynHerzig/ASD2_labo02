/*
 * File:   DirectedCycle.h
 * Author: Olivier Cuisenaire
 *
 * Created on 08. octobre 2014, 10:46
 * Classe permettant la detection de cycle sur un graphe oriente
 * Modified by Berney Alec, Forestier Quentin, Herzig Melvyn on 30 Sep. 2020
 */

#ifndef ASD2_DirectedCycle_h
#define ASD2_DirectedCycle_h

#include <list>
#include <vector>
#include <stack>

template<typename GraphType>
class DirectedCycle
{
private:

   const GraphType& G;

   int cycleDetectedAt;
   bool mustBeAdded;
   std::vector<bool> marked;
   std::vector<bool> stacked;

   std::list<int> cycle;

   /*
    * @brief Initialise les variables pour la détection de cycle.
    */
   void Init (int v)
   {
      marked.resize(v);
      std::fill(marked.begin(), marked.end(), false);

      stacked.resize(v);
      std::fill(stacked.begin(), stacked.end(), false);

      cycleDetectedAt = -1;
      mustBeAdded = true;
   }

   /*
    * @brief Lance le processus de récursion sur un sommet v pour chercher un cycle.
    */
   void cycleDetection(int v)
   {
      marked[v] = true;
      stacked[v] = true;

      for(int w: G.adjacent(v))
      {
         if(!marked[w])
         {
            cycleDetection(w);
         }
         else if(stacked[w])
         {
            cycleDetectedAt = w;
            cycle.push_back(w);
         }

         if(cycleDetectedAt >= 0)
         {
           if(mustBeAdded) cycle.push_back(v);
           if(cycleDetectedAt == v) mustBeAdded = false;

           return;
         }
      }
      stacked[v] = false;
   }

public:

   /**
    * @brief Effectue une détection de cycle sur le graphe donné.
    * @param g Graphe a effectué la détection de cycle.
    */
   DirectedCycle (const GraphType &g) : G(g)
   {
      Init(G.V());

      for(int i = 0; i < G.V() && cycleDetectedAt < 0; ++i)
      {
         cycleDetection(i);
      }

   }

   /**
    * @brief Indique si un cycle a été détecté à la construction.
    * @return Vrai si un cycle a été détecté.
    */
   bool HasCycle ()
   {
      return cycle.size() > 0;
   }

   /**
    * @brief Liste les indexes des sommets formant une boucle
    * @return La liste des indexes.
    */
   std::list<int> Cycle ()
   {
      return cycle;
   }
};

#endif
