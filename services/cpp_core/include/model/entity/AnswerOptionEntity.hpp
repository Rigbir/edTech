//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>

class AnswerOptionEntity {
public:
    oatpp::String id;
    oatpp::String questionId;  
    oatpp::String optionText;
    oatpp::Boolean isCorrect;
    oatpp::Int32 displayOrder;
    oatpp::Int64 createdAt;  
};

