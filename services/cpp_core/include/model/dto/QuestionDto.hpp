//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include "model/dto/AnswerOptionDto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class QuestionDto: public oatpp::DTO {
    DTO_INIT(QuestionDto, DTO)

    DTO_FIELD(String, id);
    DTO_FIELD(String, questionText);
    DTO_FIELD(String, questionType);  // single_choice, multiple_choice, text, number, ordering, matching
    DTO_FIELD(String, explanation);  // nullable
    DTO_FIELD(Int32, points);
    DTO_FIELD(Int32, displayOrder);
    DTO_FIELD(String, imageUrl);  // nullable
    DTO_FIELD(Vector<Object<AnswerOptionDto>>, answerOptions);
};

#include OATPP_CODEGEN_END(DTO)

