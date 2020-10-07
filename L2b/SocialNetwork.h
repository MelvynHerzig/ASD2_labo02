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

   GraphType gReversed;

public:

   /**
    * @brief Construit le graphe à symbole du réseau social.
    * @param filename Fichier des relations.
    * @param delim Délimiteur entre les relations, par défaut ','.
    */
   SocialNetwork (const std::string &filename, char delim = '/') : BASE(filename, delim), gReversed(BASE::G().reverse())
   {}

   /**
    * @Brief Récupère les personnes auxquelles la personne "name" est abonnée.
    * @param name Nom de la personne.
    * @return Vecteur contenant les noms de ses abonnements.
    */
   std::vector<std::string> personsSubscribedBy (const std::string &name) const
   {
      return BASE::adjacent(name);
   }

   /**
    * @brief Récupère les personnes qui sont abonnées à la personne "name".
    * @param name Nom de la personne.
    * @return Vecteur contenant le nom des followers de name.
    */
   std::vector<std::string> personsWhoFollows (const std::string &name) const
   {
      std::vector<std::string> names;

      for(int id : gReversed.adjacent(BASE::index(name)))
      {
         names.push_back(BASE::symbol(id));
      }

      return names;
   }

   /**
    * @brief Determine si la personne subscriber suit la personne personFollowed.
    * @param subscriber Nom du subscriber.
    * @param personFollowed Nom de la personne suivie.
    * @return Vrai si subscriber suit personFollowed.
    */
   bool isFollowing (const std::string &subscriber, const std::string &personFollowed) const
   {
      std::vector<std::string> adjacent = BASE::adjacent(subscriber);
      return std::find(adjacent.begin(), adjacent.end(), personFollowed) != adjacent.end();
   }

   /**
    * @brief Ajoute un nouvel abonnement au réseau social, subscriber suit personToFollow
    * @param subscriber Nom du subscriber.
    * @param personToFollow Nom de la personne suivie.
    */
   void addSubscription (const std::string &subscriber, const std::string &personToFollow)
   {
      if(isFollowing(subscriber, personToFollow)) return;

      BASE::g->addEdge(BASE::index(subscriber), BASE::index(personToFollow));
      gReversed.addEdge(BASE::index(personToFollow), BASE::index(subscriber));
   }

   /**
    * @brief Retourne les personnes faisant partie du cercle de relations de la personne "name"
    * @param name Nom de la personne à chercher le cercle d'ami.
    * @return Vecteur des noms du cercle d'ami.
    */
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
