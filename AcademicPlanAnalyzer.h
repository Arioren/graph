#pragma once
#include <string>
#include "Stage1/Graph.h"
#include "Stage1/DfsResult.h"
#include "Stage1/CourseData.h"

class AcademicPlanAnalyzer {
public:
    AcademicPlanAnalyzer(const std::string& path) {
        // TBD: complete
    }

    ~AcademicPlanAnalyzer() = default;

    bool hasCycle() {
        // TBD: complete
        return false;
    }

    int minimalSemesters() {
        // TBD: complete
        return 0;
    }

private:
    Graph<std::string, CourseData> g_;
    bool hasDfs_ = false;
    DfsResult<std::string, CourseData> dfsResult_;
};
