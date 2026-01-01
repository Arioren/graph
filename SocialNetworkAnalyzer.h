#pragma once
#include <string>
#include <list>

#include "Stage1/Graph.h"
#include "Stage1/UserData.h"
#include "Stage1/BfsRunner.h"

class SocialNetworkAnalyzer {
public:
    SocialNetworkAnalyzer(const std::string& path) {
        // TBD: complete
    }

    ~SocialNetworkAnalyzer() = default;

    int mutualFriendsCount(int userId, int candidateId) {
        // TBD: complete
        return 0;
    }

    std::list<int> suggestNewFriends(int userId, int k) {
        // TBD: complete
        return std::list<int>();
    }

    int mostRemoteUser(int userId) {
        // TBD: complete
        return -1;
    }

private:
    Graph<int, UserData> g_;
    int lastAnalyzedUserId_ = -1;
    bool hasBfs_ = false;
};
