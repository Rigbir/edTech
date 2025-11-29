//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>

class TestHistoryEntity {
public:
    oatpp::String id;
    oatpp::String testId;  // FK to tests
    oatpp::Int32 version;
    oatpp::String changedBy;  // FK to users (nullable)
    oatpp::String changeType;  // created, updated, published, archived
    oatpp::String changesJson;  // JSONB - details of changes
    oatpp::Int64 createdAt;  // timestamp
};

