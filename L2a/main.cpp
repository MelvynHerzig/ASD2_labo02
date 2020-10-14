/*
 * File:   main.cpp
 * Author: Olivier Cuisenaire
 *
 * Created on 3. novembre 2014, 08:23
 * Updated on 9. sept 2020 by Antoine Rochat
 * Modified on 02 Oct. 2020 by Berney Alec, Forestier Quentin, Herzig Melvyn
 */

#include <cstdlib>
#include <iostream>
#include "DiGraph.h"
#include "SymbolGraph.h"
#include "TopologicalSort.h"

using namespace std;

/**
 * @brief Pour les entiers entre begin et end, affiche le symbole associé dans g
 * @tparam RandomAccessIterator Itérateur.
 * @tparam grapheType Type du graphe.
 * @param begin Itérateur de début.
 * @param end Itérateur de fin.
 * @param g Graphe.
 * @return String concaténée avec les symboles
 */
template < typename RandomAccessIterator, typename grapheType >
string symbolContained(RandomAccessIterator begin, RandomAccessIterator end,const SymbolGraph<grapheType>& g)
{
   string result = "";

   for(auto i = begin; i != end; ++i)
   {
      result +=  g.symbol(*i) + " ";
   }
   return result;
}

bool checkOrder (const std::vector<int> &order,
                 const SymbolGraph<DiGraph> &SG,
                 const std::string &filename,
                 char delim)
{

   std::vector<int> positionInOrder(order.size());
   for (size_t i = 0; i < order.size(); ++i)
   {
      positionInOrder[order[i]] = int(i);
   }

   bool ok = true;

   std::string line;

   std::ifstream s(filename);
   while (std::getline(s, line))
   {
      auto names = split(line, delim);

      for (size_t i = 1; i < names.size(); ++i)
      {

         int v = SG.index(names[0]);
         int w = SG.index(names[i]);

         if (positionInOrder[v] < positionInOrder[w])
         {
            cout << "Erreur d'ordre : " << names[0] << " avant " << names[i] << endl;
            ok = false;
         }
      }
   }
   s.close();

   return ok;
}

//ARGS prerequis.txt
//ARGS prerequis2.txt
int main (int argc, const char *argv[])
{

   if (argc < 2)
   {
      cerr << "Aucun fichier fourni en argument" << endl;
      return EXIT_FAILURE;
   }


   char delim = ',';

   for (int i = 1; i < argc; ++i)
   {
      string filename(argv[i]);

      SymbolGraph<DiGraph>   G  = {filename, delim};
      DirectedCycle<DiGraph> DC = {G.G()};

      try
      {
         TopologicalSort<DiGraph> TS = {G.G()};

         cout << filename << " est un DAG" << endl
              << "Ordre topologique:" << endl;

         const vector<int> &listnum = TS.Order();
         cout << symbolContained(listnum.begin(), listnum.end(), G) << endl;

         if (checkOrder(listnum, G, filename, delim))
         {
            cout << "Vérification réussie" << endl;
         } else
         {
            cout << "Vérification échouée" << endl;
         }
      }
      catch (TopologicalSort<DiGraph>::GraphNotDAGException e)
      {
         cout << filename << " n'est pas un DAG" << endl
              << "Cycle trouvé:"                 << endl;

         std::list<int>& cycles = DC.Cycle();
         cout << symbolContained(cycles.begin(), cycles.end(), G) << endl;
      }
   }
   return EXIT_SUCCESS;
}
