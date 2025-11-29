//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class AnswerOptionDto : public oatpp::DTO {
    DTO_INIT(AnswerOptionDto, DTO)

    DTO_FIELD(String, id);
    DTO_FIELD(String, optionText);
    DTO_FIELD(Int32, displayOrder);
    DTO_FIELD(Boolean, isCorrect);  // Optional - only included after test completion
};

#include OATPP_CODEGEN_END(DTO)

