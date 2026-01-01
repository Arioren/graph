#pragma once
#include <list>

#include "Vertex.h"

template <typename K, typename T>
class Graph {
public:
    Graph() {}

    ~Graph() {
        // TBD: complete
    }

    void addVertex(const K& key, const T& data) {
        // TBD: complete
    }



    void addEdge(Vertex<K, T>* from, Vertex<K, T>* to) {
        // TBD: complete
    }

    void addEdgeByKey(const K& fromKey, const K& toKey) {
        // TBD: complete
    }

private:
    std::list<Vertex<K, T>*> vertices_;
    std::unordered_map<K, Vertex<K, T>*> index_;
};
