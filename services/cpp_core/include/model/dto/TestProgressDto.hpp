//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class TestProgressDto: public oatpp::DTO {
    DTO_INIT(TestProgressDto, DTO)

    DTO_FIELD(String, id);
    DTO_FIELD(String, testId);
    DTO_FIELD(String, status);  // started, completed, abandoned
    DTO_FIELD(Int32, score);  // nullable
    DTO_FIELD(Float32, percentage);  // nullable
    DTO_FIELD(Int32, timeSpentSeconds);  // nullable
    DTO_FIELD(Int64, startedAt);  // timestamp
    DTO_FIELD(Int64, completedAt);  // timestamp (nullable)
};

#include OATPP_CODEGEN_END(DTO)

