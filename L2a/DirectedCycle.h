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

   GraphType G;

   bool cycleDetected;
   std::vector<bool> marked;
   std::vector<bool> stacked;

   std::list<int> cycle;

   void Init (int v)
   {
      marked.resize(v);
      std::fill(marked.begin(), marked.end(), false);

      stacked.resize(v);
      std::fill(stacked.begin(), stacked.end(), false);

      cycleDetected = false;
   }

   void cycleDetection(int v)
   {
      marked[v] = true;
      stacked[v] = true;

      for(int w: G.adjacent(v))
      {
         if(cycleDetected)
         {
            //Checker avec si true potentiellement.
            cycle.push_front(v);
            return;
         }
         else if(!marked[w])
         {
            cycleDetection(w);
         }
         else if(stacked[w])
         {
            cycleDetected = true;
         }
      }
      stacked[v] = false;
   }

public:

   // constructeur
   DirectedCycle (const GraphType &g) : G(g)
   {
      Init(g.V());

      if(g.V()) cycleDetection(0);

   }

   /**
    * @brief Indique si un cycle a été détecté à la construction.
    * @return Vrai si un cycle a été détecté.
    */
   bool HasCycle ()
   {
      return (bool) cycle.size();
   }

   // liste les indexes des sommets formant une boucle
   std::list<int> Cycle ()
   {
      return cycle;
   }
};

#endif
