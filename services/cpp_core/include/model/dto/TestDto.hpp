//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include "model/dto/QuestionDto.hpp"
#include "model/dto/TagDto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class TestDto : public oatpp::DTO {
    DTO_INIT(TestDto, DTO)

    DTO_FIELD(String, id);
    DTO_FIELD(String, subjectId);
    DTO_FIELD(String, subjectName);  // Readable name instead of just ID
    DTO_FIELD(String, title);
    DTO_FIELD(String, description);
    DTO_FIELD(String, difficulty);  // easy, medium, hard
    DTO_FIELD(Int32, estimatedTimeMinutes);
    DTO_FIELD(Int32, maxScore);
    DTO_FIELD(Int32, passingScore);  // nullable
    DTO_FIELD(Boolean, isPublished);
    DTO_FIELD(Int64, publishedAt);  // timestamp (nullable)
    DTO_FIELD(Vector<Object<TagDto>>, tags);
    DTO_FIELD(Vector<Object<QuestionDto>>, questions);
};

#include OATPP_CODEGEN_END(DTO)

