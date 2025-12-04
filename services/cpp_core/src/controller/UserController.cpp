//
// Created by Rigbir on 04.12.25.
//

#include "controller/UserController.hpp"

UserController::UserController(const std::shared_ptr<ObjectMapper>& objectMapper)
    : oatpp::web::server::api::ApiController(objectMapper)
    , userService_(std::make_unique<UserService>())
{}

oatpp::Object<UserProfileDto> UserController::getProfileImpl(const oatpp::String& userId) {  
    return userService_->getProfile(userId);
}

oatpp::Vector<oatpp::Object<UserStatisticsDto>> UserController::getStatisticsImpl(const oatpp::String& userId) {  
    return userService_->getStatistics(userId);
}