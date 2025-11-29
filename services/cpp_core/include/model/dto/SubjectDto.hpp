//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class SubjectDto: public oatpp::DTO {
    DTO_INIT(SubjectDto, DTO)

    DTO_FIELD(String, id);
    DTO_FIELD(String, name);
    DTO_FIELD(String, description);
    DTO_FIELD(String, iconUrl);
    DTO_FIELD(String, color);  // hex color
    DTO_FIELD(Int32, displayOrder);
};

#include OATPP_CODEGEN_END(DTO)

