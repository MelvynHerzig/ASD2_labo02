/*
 * File:   SocialNetwork.h
 * Author: Antoine Rochat
 *
 * Created on 08. sept 2020
 * Modified on 07. aug 2020 by Berney Alec, Forestier Quentin, Herzig Melvyn
 */

#ifndef ASD2_SocialNetwork_h
#define ASD2_SocialNetwork_h

#include <list>
#include <vector>
#include <exception>
#include "SymbolGraph.h"
#include "CFC.h"
#include "DiGraph.h"

template<typename GraphType>
class SocialNetwork : public SymbolGraph<GraphType>
{

   typedef SymbolGraph<GraphType> BASE;

public:
   SocialNetwork (const std::string &filename, char delim = '/') : BASE(filename, delim)
   {}

   // retourne les personnes auxquelles la personne "name" est abonnée
   std::vector<std::string> personsSubscribedBy (const std::string &name) const
   {
      return BASE::adjacent(name);
   }

   // retourne les personnes qui sont abonnées à la personne "name"
   std::vector<std::string> personsWhoFollows (const std::string &name) const
   {
      std::vector<std::string> v;
      return v;
      //return grapheTranspose.adjacent(name);
   }

   // determine si la personne subscriber suit la personne personFollowed
   bool isFollowing (const std::string &subscriber, const std::string &personFollowed) const
   {
      std::vector<std::string> adjacent = BASE::adjacent(subscriber);
      return std::find(adjacent.begin(), adjacent.end(), personFollowed) != adjacent.end();
   }

   // ajoute un nouvel abonnement au réseau social, subscriber suit personToFollow
   void addSubscription (const std::string &subscriber, const std::string &personToFollow)
   {
      if(isFollowing(subscriber, personToFollow)) return;

      BASE::g->addEdge(BASE::index(subscriber), BASE::index(personToFollow));
      //grapheTranspose.addEgde(graphe.index(personToFollow), graphe.index(subscriber));
   }

   // retourne les personnes faisant partie du cercle de relations de la personne "name"
   std::vector<std::string> relationCircle (const std::string &name) const
   {
      KosarajuSharirCFC<GraphType> cfc = {*BASE::g, BASE::g->reverse()};
      int idBase = BASE::index(name);
      std::vector<std::string> amitie;

      for(size_t i = 0; i < BASE::g->V(); ++i)
      {
         if(i != idBase && cfc.Connected(i, idBase))
         {
            amitie.push_back(BASE::symbol(i));
         }
      }

      return amitie;
   }
};

#endif
