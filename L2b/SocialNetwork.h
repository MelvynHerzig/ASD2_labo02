/*
 * File:   SocialNetwork.h
 * Author: Antoine Rochat
 *
 * Created on 08. sept 2020
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
class SocialNetwork : public SymbolGraph<GraphType> {

    typedef SymbolGraph<GraphType> BASE;

/****
*
*  AJOUTEZ ICI VOS EVENTUELLES STRUCTURES PRIVEES
*
****/

public:
    SocialNetwork(const std::string& filename, char delim = '/')
/****
*
*  A IMPLEMENTER
*
****/
    {}

    // retourne les personnes auxquelles la personne "name" est abonnée
    std::vector<std::string> personsSubscribedBy(const std::string& name) const {
/****
*
*  A IMPLEMENTER
*
****/
    }

    // retourne les personnes qui sont abonnées à la personne "name"
    std::vector<std::string> personsWhoFollows(const std::string& name) const {
/****
*
*  A IMPLEMENTER
*  Cette méthode doit avoir une compléxité en O(S), où S est le nombre de personnes qui sont abonnées à la personne "name"
*
****/
    }

    // determine si la personne subscriber suit la personne personFollowed
    bool isFollowing(const std::string& subscriber, const std::string& personFollowed) const {
/****
*
*  A IMPLEMENTER
*
****/
    }

    // ajoute un nouvel abonnement au réseau social, subscriber suit personToFollow
    void addSubscription(const std::string& subscriber, const std::string& personToFollow) {
/****
*
*  A IMPLEMENTER
*  Ne modifie pas notre reseau social si subscriber suit deja personToFollow
*
****/
    }

    // retourne les personnes faisant partie du cercle de relations de la personne "name"
    std::vector<std::string> relationCircle(const std::string& name) const {
/****
*
*  A IMPLEMENTER
*  Utiliser la classe KosarajuSharirCFC afin de trouver le cercle de relations d'une personne
*  (correspond aux personnes se trouvant dans la même composante fortement connexe)
*
****/
    }
};

#endif
