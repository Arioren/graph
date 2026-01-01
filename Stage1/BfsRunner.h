#pragma once
#include "Graph.h"
#include "Vertex.h"

#include <queue>
#include <iostream>

class BfsRunner {
public:
    template <typename K, typename T>
    static void BFS(Graph<K, T>& g, Vertex<K, T>* source) {
        if (!source) return;

        // Reset graph state
        for (auto v : g.getVertices()) {
            v->setColor(WHITE);
            v->setDist(-1);
            v->setParent(nullptr);
        }

        source->setColor(GRAY);
        source->setDist(0);
        source->setParent(nullptr);

        std::queue<Vertex<K, T>*> q;
        q.push(source);

        while (!q.empty()) {
            Vertex<K, T>* u = q.front();
            q.pop();

            for (auto v : u->neighbors()) {
                if (v->getColor() == WHITE) {
                    v->setColor(GRAY);
                    v->setDist(u->getDist() + 1);
                    v->setParent(u);
                    q.push(v);
                }
            }
            u->setColor(BLACK);
        }
        std::cout << "BFS completed" << std::endl;
    }
};
