/*
 * File:   DirectedCycle.h
 * Author: Olivier Cuisenaire
 *
 * Created on 08. octobre 2014, 10:46
 * Classe permettant la detection de cycle sur un graphe oriente
 * Modified by Berney Alec, Forestier Quentin, Herzig Melvyn on 02 Oct. 2020
 */

#ifndef ASD2_DirectedCycle_h
#define ASD2_DirectedCycle_h

#include <list>
#include <vector>

/*
 *  Nous considérons que le graphe référencé ne change pas.
 *  C'est pourquoi nous avons implémenté les opérations de vérification de cycle dans
 *  le constructeur. Si, les graphes référencés sont susceptibles de changer,
 *  il faudrait déplacer l'implémentation du constructeur à la fonction hasCycle.
 */
template<typename GraphType>
class DirectedCycle
{
private:

   const GraphType& G;

   bool cycleDetected;
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

      cycleDetected = false;
   }

   /**
    * @brief Lance le processus de récursion sur un sommet v pour chercher un cycle.
    * @param v Sommet de départ.
    */
   void cycleDetection(int v)
   {
      marked [v] = true;
      stacked[v] = true;

      for(int w: G.adjacent(v))
      {
         if(!marked[w])
         {
            cycleDetection(w);
         }
         else if(stacked[w])
         {
            cycleDetected = true;
            cycle.push_back(w);
         }

         if(cycleDetected && cycle.front() != cycle.back() || cycle.size() == 1)
         {
           cycle.push_back(v);

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

      for(int i = 0; i < G.V() && !cycleDetected; ++i)
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
      return cycle.size() > 1;
   }

   /**
    * @brief Liste les indexes des sommets formant une boucle
    * @return La liste des indexes.
    */
   std::list<int>& Cycle ()
   {
      return cycle;
   }
};

#endif
