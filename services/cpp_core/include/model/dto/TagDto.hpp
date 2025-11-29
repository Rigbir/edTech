//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class TagDto: public oatpp::DTO {
    DTO_INIT(TagDto, DTO)

    DTO_FIELD(String, id);
    DTO_FIELD(String, name);
    DTO_FIELD(String, color);  // hex color (nullable)
};

#include OATPP_CODEGEN_END(DTO)

