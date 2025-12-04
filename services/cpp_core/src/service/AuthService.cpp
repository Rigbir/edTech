//
// Created by Rigbir on 04.12.25.
//

#include "service/AuthService.hpp"
#include <jwt-cpp/jwt.h>
#include <chrono>

AuthService::AuthService(const std::string& secretKey)
    : secretKey_(secretKey)
{}

std::string AuthService::generateToken(
    const oatpp::String& userId,
    const oatpp::String& email,
    const oatpp::String& role
) const {
    std::string userIdStr = userId ? userId->c_str() : "";
    std::string emailStr = email ? email->c_str() : "";
    std::string roleStr = role ? role->c_str() : "";
    
    auto token = jwt::create()
        .set_issuer("edTech")
        .set_type("JWT")
        .set_payload_claim("userId", jwt::claim(userIdStr))
        .set_payload_claim("email", jwt::claim(emailStr))
        .set_payload_claim("role", jwt::claim(roleStr))
        .set_issued_at(std::chrono::system_clock::now())
        .set_expires_at(std::chrono::system_clock::now() + std::chrono::hours{24})
        .sign(jwt::algorithm::hs256{secretKey_});

    return token;
}

oatpp::String AuthService::validateToken(const std::string& token) const {
    try {
        auto decoded = jwt::decode(token);
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{secretKey_})
            .with_issuer("edTech");
        
        verifier.verify(decoded);

        auto userId = decoded.get_payload_claim("userId").as_string();
        return oatpp::String(userId.c_str());
    } catch (const std::exception& e) {
        return nullptr;
    }
}