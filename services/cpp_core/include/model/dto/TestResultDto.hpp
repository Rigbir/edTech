//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include "model/dto/QuestionDto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class TestResultDto: public oatpp::DTO {
    DTO_INIT(TestResultDto, DTO)

    DTO_FIELD(String, testId);
    DTO_FIELD(Int32, score);
    DTO_FIELD(Float32, percentage);
    DTO_FIELD(Int32, correctAnswers);
    DTO_FIELD(Int32, totalQuestions);
    DTO_FIELD(Int32, timeSpentSeconds);
    DTO_FIELD(Int64, completedAt);  // timestamp
    DTO_FIELD(Vector<Object<QuestionDto>>, questions);  // Questions with correct answers shown
};

#include OATPP_CODEGEN_END(DTO)

