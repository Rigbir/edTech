//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>

class TestEntity {
public:
    oatpp::String id;
    oatpp::String subjectId;  // FK to subjects
    oatpp::String title;
    oatpp::String description;
    oatpp::String difficulty;  // easy, medium, hard
    oatpp::Int32 estimatedTimeMinutes;
    oatpp::Int32 maxScore;
    oatpp::Int32 passingScore;  // nullable
    oatpp::Boolean isPublished;
    oatpp::Boolean isArchived;
    oatpp::String authorId;  // FK to users (nullable)
    oatpp::String moderatorId;  // FK to users (nullable)
    oatpp::String moderationStatus;  // pending, approved, rejected
    oatpp::String moderationComment;  // nullable
    oatpp::Int32 version;
    oatpp::Int64 createdAt;  // timestamp
    oatpp::Int64 updatedAt;  // timestamp
    oatpp::Int64 publishedAt;  // timestamp (nullable)
};

