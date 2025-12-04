//
// Created by Rigbir on 04.12.25.
//

#pragma once

#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include "model/dto/LoginRequestDto.hpp"
#include "model/dto/LoginResponseDto.hpp"
#include "service/AuthService.hpp"
#include "service/UserService.hpp"
#include <oatpp/core/Types.hpp>
#include <memory>

/**
 * AuthController - handles authentication
 * 
 * Purpose: Provides authentication endpoints (login, logout, etc.)
 * 
 * Dependencies: Depends on AuthService and UserService.
 */
#include OATPP_CODEGEN_BEGIN(ApiController)

class AuthController: public oatpp::web::server::api::ApiController {
public:
    AuthController(const std::shared_ptr<ObjectMapper>& objectMapper);

    ENDPOINT("POST", "/api/auth/login", login,
        BODY_DTO(Object<LoginRequestDto>, body)) {
            return createDtoResponse(Status::CODE_200, loginImpl(body));
    }

private:
    oatpp::Object<LoginResponseDto> loginImpl(
        const oatpp::Object<LoginRequestDto>& body
    );

private:
    std::unique_ptr<AuthService> authService_;
    std::unique_ptr<UserService> userService_;
};

#include OATPP_CODEGEN_END(ApiController)