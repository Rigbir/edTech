//
// Created by Rigbir on 04.12.25.
//

#pragma once

#include <string>
#include <oatpp/core/Types.hpp>

class AuthService {
public:
    AuthService(const std::string& secretKey);

    std::string generateToken(
        const oatpp::String& userId,
        const oatpp::String& email,
        const oatpp::String& role
    ) const;

    oatpp::String validateToken(const std::string& token) const;

private:
    std::string secretKey_;
};