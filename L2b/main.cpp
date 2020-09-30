/*
 * File:   DFSOrder.h
 * Author: Cuisenaire
 *
 * Created on 3. novembre 2014, 08:23
 * Updated on 9. sept 2020 by Antoine Rochat
 */

#include <cstdlib>
#include <iostream>
#include "DiGraph.h"
#include "CFC.h"

#include "SocialNetwork.h"

using namespace std;

//ARGS followers.txt
int main(int argc, const char* argv[]) {

    if (argc != 2) {
        cerr << "Le programme attend un seul fichier en argument" << endl;
        return EXIT_FAILURE;
    }

    string filename(argv[1]);
    char delim = ',';

    SocialNetwork<DiGraph> SN(filename, delim);

    cout << "Personnes suivies par Jules : " << endl;
    for (const string& person : SN.personsSubscribedBy("Jules")) {
        cout << person << endl;
    }

    cout << "\nPersonnes qui suivent Jean : " << endl;
    for (const string& person : SN.personsWhoFollows("Jean")) {
        cout << person << endl;
    }

    cout << "\nCercle de relation de Paul : " << endl;

    vector<string> relationCircleStr = SN.relationCircle("Paul");

    // Tri par ordre alphabétique (pour le codecheck)
    std::sort(relationCircleStr.begin(), relationCircleStr.end());

    for (const string& person : relationCircleStr) {
        cout << person << endl;
    }

    cout << "\nEmma " << (SN.isFollowing("Emma", "Hugo") ? "suit" : "ne suit pas") << " Hugo." << endl;
    SN.addSubscription("Emma", "Hugo");
    cout << "\nEmma " << (SN.isFollowing("Emma", "Hugo") ? "suit" : "ne suit pas") << " Hugo." << endl;

    cout << "\nPersonnes suivies par Emma : " << endl;
    for (const string& person : SN.personsSubscribedBy("Emma")) {
        cout << person << endl;
    }

    cout << "\nPersonnes qui suivent Hugo : " << endl;
    for (const string& person : SN.personsWhoFollows("Hugo")) {
        cout << person << endl;
    }

    cout << "\nCercle de relation de Elise : " << endl;

    relationCircleStr = SN.relationCircle("Elise");

    // Tri par ordre alphabétique (pour le codecheck)
    std::sort(relationCircleStr.begin(), relationCircleStr.end());

    for (const string& person : relationCircleStr) {
        cout << person << endl;
    }

    return EXIT_SUCCESS;
}
