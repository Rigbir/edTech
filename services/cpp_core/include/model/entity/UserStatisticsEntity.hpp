//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>

class UserStatisticsEntity {
public:
    oatpp::String id;
    oatpp::String userId;  // FK to users
    oatpp::String subjectId;  // FK to subjects (nullable)
    oatpp::Int32 testsCompleted;
    oatpp::Int32 testsStarted;
    oatpp::Int32 totalScore;
    oatpp::Float32 averageScore;  // nullable, DECIMAL(5,2)
    oatpp::Int32 bestScore;  // nullable
    oatpp::Int32 totalTimeSpentSeconds;
    oatpp::Int64 lastActivityAt;  // timestamp (nullable)
    oatpp::Int64 createdAt;  // timestamp
    oatpp::Int64 updatedAt;  // timestamp
};

