//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class UserStatisticsDto : public oatpp::DTO {
    DTO_INIT(UserStatisticsDto, DTO)

    DTO_FIELD(String, subjectId);  // nullable (null = overall statistics)
    DTO_FIELD(String, subjectName);  // nullable
    DTO_FIELD(Int32, testsCompleted);
    DTO_FIELD(Int32, testsStarted);
    DTO_FIELD(Float32, averageScore);  // nullable
    DTO_FIELD(Int32, bestScore);  // nullable
    DTO_FIELD(Int32, totalTimeSpentSeconds);
    DTO_FIELD(Int64, lastActivityAt);  // timestamp (nullable)
};

#include OATPP_CODEGEN_END(DTO)

