//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include "model/dto/TagDto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class TestListDto: public oatpp::DTO {
    DTO_INIT(TestListDto, DTO)

    DTO_FIELD(String, id);
    DTO_FIELD(String, subjectId);
    DTO_FIELD(String, subjectName);
    DTO_FIELD(String, title);
    DTO_FIELD(String, description);
    DTO_FIELD(String, difficulty);  // easy, medium, hard
    DTO_FIELD(Int32, estimatedTimeMinutes);
    DTO_FIELD(Int32, maxScore);
    DTO_FIELD(Int32, passingScore);  // nullable
    DTO_FIELD(Int64, publishedAt);  // timestamp (nullable)
    DTO_FIELD(Vector<Object<TagDto>>, tags);
    // Note: questions are NOT included to reduce payload size
};

#include OATPP_CODEGEN_END(DTO)

