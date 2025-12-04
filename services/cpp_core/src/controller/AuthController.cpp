//
// Created by Rigbir on 04.12.25.
//

#include "controller/AuthController.hpp"
#include "config/AppConfig.hpp"

AuthController::AuthController(const std::shared_ptr<ObjectMapper>& objectMapper)
    : oatpp::web::server::api::ApiController(objectMapper)
    , authService_(std::make_unique<AuthService>(
        AppConfig::getInstance().getJwtSecretKey()
    ))
    , userService_(std::make_unique<UserService>())
{}

oatpp::Object<LoginResponseDto> AuthController::loginImpl(const oatpp::Object<LoginRequestDto>& body) {
    auto response = LoginResponseDto::createShared();

    if (!body->email || body->email->empty()) {
        response->success = false;
        response->message = "Email is required";
        return response;
    }

    if (!body->password || body->password->empty()) {
        response->success = false;
        response->message = "Password is required";
        return response;
    }

    auto user = userService_->authenticate(body->email, body->password);
    if (!user) {
        response->success = false;
        response->message = "Invalid email or password";
        return response;
    }

    std::string token = authService_->generateToken(
        user->id,
        user->email,
        user->role
    );

    response->success = true;
    response->token = oatpp::String(token.c_str());
    response->userId = user->id;
    response->email = user->email;
    response->role = user->role;
    response->message = "Login successful";
    
    return response;
}