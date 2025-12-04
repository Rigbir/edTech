//
// Created by Rigbir on 04.12.25.
//

#pragma once

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class LoginRequestDto : public oatpp::DTO {
    DTO_INIT(LoginRequestDto, DTO)

    DTO_FIELD(String, email);
    DTO_FIELD(String, password);
};

#include OATPP_CODEGEN_END(DTO)