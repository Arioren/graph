#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include "Stage1/Graph.h"
#include "Stage1/DfsResult.h"
#include "Stage1/DfsRunner.h"
#include "Stage1/CourseData.h"

class AcademicPlanAnalyzer {
public:
    AcademicPlanAnalyzer(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) return;

        int n;
        if (!(file >> n)) return;
        for (int i = 0; i < n; ++i) {
            std::string code, name;
            double credits;
            file >> code >> name >> credits;
            g_.addVertex(code, CourseData(name, credits));
        }

        int m;
        if (!(file >> m)) return;
        for (int i = 0; i < m; ++i) {
            std::string prereq, course;
            file >> prereq >> course;
            try {
                g_.addEdgeByKey(prereq, course);
            } catch (...) {}
        }
    }

    ~AcademicPlanAnalyzer() = default;

    bool hasCycle() {
        runDfsIfNeeded();
        return dfsResult_.hasCycle();
    }

    int minimalSemesters() {
        if (hasCycle()) return 0;
        
        std::list<Vertex<std::string, CourseData>*> topo = dfsResult_.topologicalOrderOrEmpty();
        std::map<Vertex<std::string, CourseData>*, int> semester;
        
        int maxSemesters = 0;
        for (auto v : g_.getVertices()) semester[v] = 1;

        for (auto u : topo) {
            for (auto v : u->neighbors()) {
                if (semester[v] < semester[u] + 1) {
                    semester[v] = semester[u] + 1;
                }
            }
        }

        for (auto const& [v, s] : semester) {
            if (s > maxSemesters) maxSemesters = s;
        }

        return maxSemesters;
    }

private:
    void runDfsIfNeeded() {
        if (!hasDfs_) {
            dfsResult_ = DfsRunner::DFS(g_);
            hasDfs_ = true;
        }
    }

    Graph<std::string, CourseData> g_;
    bool hasDfs_ = false;
    DfsResult<std::string, CourseData> dfsResult_;
};
