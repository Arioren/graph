#pragma once
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include "Graph.h"
#include "UserData.h"
#include "BfsRunner.h"

class SocialNetworkAnalyzer {
public:
    SocialNetworkAnalyzer(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) return;

        int n;
        if (!(file >> n)) return;
        for (int i = 0; i < n; ++i) {
            int id;
            std::string name;
            int age;
            char gender;
            file >> id >> name >> age >> gender;
            g_.addVertex(id, UserData(name, age, gender));
        }

        int m;
        if (!(file >> m)) return;
        for (int i = 0; i < m; ++i) {
            int id1, id2;
            file >> id1 >> id2;
            try {
                g_.addEdgeByKey(id1, id2);
                g_.addEdgeByKey(id2, id1);
            } catch (...) {}
        }
    }

    ~SocialNetworkAnalyzer() = default;

    int mutualFriendsCount(int userId, int candidateId) {
        runBfsIfNeeded(userId);
        
        Vertex<int, UserData>* u = g_.getVertexByKey(userId);
        Vertex<int, UserData>* v = g_.getVertexByKey(candidateId);
        
        if (!u || !v || userId == candidateId) return 0;
        
        if (v->getDist() > 2 || v->getDist() == -1) return 0;
        
        int count = 0;
        for (auto neighbor : v->neighbors()) {
            if (neighbor->getDist() == 1) {
                count++;
            }
        }
        return count;
    }

    std::list<int> suggestNewFriends(int userId, int k) {
        runBfsIfNeeded(userId);
        std::list<int> suggestions;
        int callCount = 0;
        
        Vertex<int, UserData>* source = g_.getVertexByKey(userId);
        if (!source) return suggestions;

        for (auto v : g_.getVertices()) {
            int candidateId = v->getKey();
            if (candidateId == userId) continue;
            
            if (v->getDist() == 2) {
                callCount++;
                if (mutualFriendsCount(userId, candidateId) >= k) {
                    suggestions.push_back(candidateId);
                }
            }
        }
        
        std::cout << "Called mutualFriendsCount " << callCount << " times." << std::endl;
        return suggestions;
    }

    int mostRemoteUser(int userId) {
        runBfsIfNeeded(userId);
        int maxDist = -1;
        int remoteId = -1;

        for (auto v : g_.getVertices()) {
            int d = v->getDist();
            if (d > maxDist) {
                maxDist = d;
                remoteId = v->getKey();
            } else if (d == maxDist && remoteId == -1) {
                remoteId = v->getKey(); // Should not happen with maxDist = -1 initial
            }
        }
        return remoteId;
    }

private:
    void runBfsIfNeeded(int userId) {
        if (!hasBfs_ || lastAnalyzedUserId_ != userId) {
            Vertex<int, UserData>* source = g_.getVertexByKey(userId);
            if (source) {
                BfsRunner::BFS(g_, source);
                lastAnalyzedUserId_ = userId;
                hasBfs_ = true;
            }
        }
    }

    Graph<int, UserData> g_;
    int lastAnalyzedUserId_ = -1;
    bool hasBfs_ = false;
};
