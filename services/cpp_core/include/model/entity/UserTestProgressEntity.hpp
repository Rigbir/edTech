//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>

class UserTestProgressEntity {
public:
    oatpp::String id;
    oatpp::String userId;  // FK to users
    oatpp::String testId;  // FK to tests
    oatpp::String status;  // started, completed, abandoned
    oatpp::Int32 score;  // nullable
    oatpp::Float32 percentage;  // nullable, DECIMAL(5,2)
    oatpp::Int32 timeSpentSeconds;  // nullable
    oatpp::Int64 startedAt;  // timestamp
    oatpp::Int64 completedAt;  // timestamp (nullable)
    oatpp::String answersJson;  // JSONB - detailed answers
    oatpp::Int64 createdAt;  // timestamp
    oatpp::Int64 updatedAt;  // timestamp
};

