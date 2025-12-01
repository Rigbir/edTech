//
// Created by Rigbir on 01.12.25.
//

#pragma once

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class SaveProgressRequestDto : public oatpp::DTO {
    DTO_INIT(SaveProgressRequestDto, DTO)

    DTO_FIELD(String, userId);
    DTO_FIELD(String, answers);  
    DTO_FIELD(Int32, timeSpentSeconds);
};

#include OATPP_CODEGEN_END(DTO)