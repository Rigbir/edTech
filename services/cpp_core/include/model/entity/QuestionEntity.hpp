//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>

class QuestionEntity {
public:
    oatpp::String id;
    oatpp::String testId;  // FK to tests
    oatpp::String questionText;
    oatpp::String questionType;  // single_choice, multiple_choice, text, number, ordering, matching
    oatpp::String explanation;  // nullable
    oatpp::Int32 points;
    oatpp::Int32 displayOrder;
    oatpp::String imageUrl;  // nullable
    oatpp::Int64 createdAt;  // timestamp
    oatpp::Int64 updatedAt;  // timestamp
};

