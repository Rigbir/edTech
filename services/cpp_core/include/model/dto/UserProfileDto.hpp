//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class UserProfileDto: public oatpp::DTO {
    DTO_INIT(UserProfileDto, DTO)

    DTO_FIELD(String, id);
    DTO_FIELD(String, username);
    DTO_FIELD(String, firstName);
    DTO_FIELD(String, lastName);
    DTO_FIELD(String, avatarUrl);
    DTO_FIELD(String, role);  // student, teacher, admin, moderator
    DTO_FIELD(String, email);  // Only included for own profile
};

#include OATPP_CODEGEN_END(DTO)

