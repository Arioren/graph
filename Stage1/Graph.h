#pragma once
#include "Vertex.h"
#include <unordered_map>
#include <stdexcept>

template <typename K, typename T>
class Graph {
public:
    Graph() {}

    ~Graph() {
        for (auto v : vertices_) {
            delete v;
        }
    }

    void addVertex(const K& key, const T& data) {
        if (index_.find(key) != index_.end()) {
            throw std::invalid_argument("Vertex with this key already exists");
        }
        Vertex<K, T>* v = new Vertex<K, T>(key, data);
        vertices_.push_back(v);
        index_[key] = v;
    }

    void addEdge(Vertex<K, T>* from, Vertex<K, T>* to) {
        if (!from || !to) return;
        from->addNeighbor(to);
    }

    void addEdgeByKey(const K& fromKey, const K& toKey) {
        if (index_.find(fromKey) == index_.end() || index_.find(toKey) == index_.end()) {
            throw std::invalid_argument("One or both keys do not exist");
        }
        addEdge(index_[fromKey], index_[toKey]);
    }

    const std::list<Vertex<K, T>*>& getVertices() const { return vertices_; }
    Vertex<K, T>* getVertexByKey(const K& key) {
        auto it = index_.find(key);
        if (it == index_.end()) return nullptr;
        return it->second;
    }

private:
    std::list<Vertex<K, T>*> vertices_;
    std::unordered_map<K, Vertex<K, T>*> index_;
};
