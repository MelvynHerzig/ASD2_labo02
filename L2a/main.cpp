/*
 * File:   main.cpp
 * Author: Olivier Cuisenaire
 *
 * Created on 3. novembre 2014, 08:23
 * Updated on 9. sept 2020 by Antoine Rochat
 * Modified by Berney Alec, Forestier Quentin, Herzig Melvyn on 30 Sep. 2020
 */

#include <cstdlib>
#include <iostream>
#include "DiGraph.h"
#include "SymbolGraph.h"

//vous pouvez reutiliser celui du labo 1, ex 2
#include "TopologicalSort.h"

using namespace std;

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

      SymbolGraph<DiGraph> G = {filename, delim};
      DirectedCycle<DiGraph> DC = {G.G()};

      if(DC.HasCycle())
      {
         cout << filename << " n'est pas un DAG" << endl;
         cout << "Cycle trouvé:"                 << endl;
         std::list<int> cycles = DC.Cycle();
         for (list<int>::iterator i = cycles.begin(); i != cycles.end(); ++i)
         {
            cout << G.symbol(*i);
            if(i != cycles.end()) cout << " ";
         }
      }
      else
      {
         TopologicalSort<DiGraph> TS = {G.G()};
         cout << filename << " est un DAG" << endl;
         cout << "Ordre topologique:" << endl;
         const vector<int>& listnum = TS.Order();
         for(int i : listnum)
         {
            cout << G.symbol(i) << " ";
         }
         cout << endl;
         if(checkOrder(listnum, G, filename, delim))
         {
            cout << "Vérification réussie" << endl;
         }
      }

   }


   return EXIT_SUCCESS;
}
