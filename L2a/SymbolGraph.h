/*
 * File:   SymbolGraph.h
 * Author: Olivier Cuisenaire
 * Modified: Raphaël Racine (2018), Antoine Rochat (2020)
 *
 * Created on 26. septembre 2014, 15:08
 */
#ifndef SYMBOLGRAPH_H
#define SYMBOLGRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>

#include "Util.h"

template<typename GraphType>
class SymbolGraph {
    typedef GraphType Graph;

    std::map<std::string, int> symbolTable;
    std::vector<std::string> keys;

protected:
    Graph* g;

public:

    ~SymbolGraph() {
        delete g;
    }

    //creation du SymbolGraph a partir du fichier movies.txt
    SymbolGraph(const std::string& filename, char delim = '/') {
        std::string line;

        std::ifstream s(filename);
        int cnt = 0;

        while (std::getline(s, line)) {
            auto names = split(line, delim);
            for (const auto& name : names) {
                if (!contains(name)) {
                    symbolTable[name] = cnt++;
                }
            }
        }
        s.close();

        keys.resize(cnt);
        for (const auto& pair : symbolTable)
            keys[pair.second] = pair.first;

        g = new Graph(cnt);

        s.open(filename);
        while (std::getline(s, line)) {
            auto names = split(line, delim);

            int v = symbolTable[names[0]];
            for (size_t i = 1; i < names.size(); ++i) {
                int w = symbolTable[names[i]];
                g->addEdge(v, w);
            }
        }
        s.close();
    }

    //verifie la presence d'un symbole
    bool contains(const std::string& name) const {
        return symbolTable.find(name) != symbolTable.end();
    }

    //index du sommet correspondant au symbole
    int index(const std::string& name) const {
        return symbolTable.at(name);
    }

    //symbole correspondant au sommet
    std::string symbol(int idx) const {
        return keys[idx];
    }

    //symboles adjacents a un symbole
    std::vector<std::string> adjacent(const std::string& name) const {
        if (!contains(name)) {
            return std::vector<std::string>(0);
        }

        auto& adjIdx = g->adjacent(index(name));
        int N = adjIdx.size();
        std::vector<std::string> adjStr(N);

        std::transform(adjIdx.cbegin(), adjIdx.cend(), adjStr.begin(), [&](int i) { return this->symbol(i); });

        return adjStr;
    }

    const Graph& G() const {
        return *g;
    }


};

#endif    /* SYMBOLGRAPH_H */
