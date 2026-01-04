#pragma once
#include "Graph.h"
#include "Vertex.h"
#include "DfsResult.h"

#include <iostream>

class DfsRunner {
public:
    template <typename K, typename T>
    static DfsResult<K, T> DFS(Graph<K, T>& g) {
        DfsResult<K, T> res;
        int time = 0;

        // Reset
        for (auto v : g.getVertices()) {
            v->setColor(WHITE);
            v->setParent(nullptr);
            v->setDiscoverTime(-1);
            v->setFinishTime(-1);
        }

        int treeCount = 0;
        for (auto v : g.getVertices()) {
            if (v->getColor() == WHITE) {
                treeCount++;
                DFS_Visit(v, time, res);
            }
        }

        std::cout << "DFS completed, found " << treeCount << " trees, "
                  << res.treeEdges() << " tree edges, "
                  << res.backEdges() << " back edges, "
                  << res.forwardEdges() << " forward edges, "
                  << res.crossEdges() << " cross edges" << std::endl;

        return res;
    }

private:
    template <typename K, typename T>
    static void DFS_Visit(Vertex<K, T>* u, int& time, DfsResult<K, T>& res) {
        u->setDiscoverTime(++time);
        u->setColor(GRAY);

        for (auto v : u->neighbors()) {
            if (v->getColor() == WHITE) {
                res.incTree();
                v->setParent(u);
                DFS_Visit(v, time, res);
            } else if (v->getColor() == GRAY) {
                res.incBack();
            } else if (v->getColor() == BLACK) {
                if (u->getDiscoverTime() < v->getDiscoverTime()) {
                    res.incForward();
                } else {
                    res.incCross();
                }
            }
        }

        u->setColor(BLACK);
        u->setFinishTime(++time);
        res.onFinish(u);
    }
};
