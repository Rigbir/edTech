//
// Created by Rigbir on 04.12.25.
//

#pragma once

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class LoginResponseDto : public oatpp::DTO {
    DTO_INIT(LoginResponseDto, DTO)

    DTO_FIELD(Boolean, success);
    DTO_FIELD(String, token);
    DTO_FIELD(String, userId);
    DTO_FIELD(String, email);
    DTO_FIELD(String, role);
    DTO_FIELD(String, message);  
};

#include OATPP_CODEGEN_END(DTO)