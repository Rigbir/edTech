//
// Created by Rigbir on 04.12.25.
//

#pragma once

#include <oatpp/web/server/api/ApiController.hpp>
#include "model/dto/UserStatisticsDto.hpp"
#include <oatpp/core/macro/codegen.hpp>
#include "model/dto/UserProfileDto.hpp"
#include "service/UserService.hpp"
#include <memory>

/**
 * UserController - works with user
 * 
 * Purpose: Provides access to user profile and statistics.
 * 
 * Dependencies: Depends on UserService.
 */
#include OATPP_CODEGEN_BEGIN(ApiController)

class UserController: public oatpp::web::server::api::ApiController {
public:
    UserController(const std::shared_ptr<ObjectMapper>& objectMapper);

    ENDPOINT("GET", "/api/users/profile", getProfile,
        REQUEST(std::shared_ptr<IncomingRequest>, request)) {
        auto userId = request->getBundleData<oatpp::String>("userId");
        if (!userId) {
            return createResponse(Status::CODE_401, "Unauthorized");
        }
        return createDtoResponse(Status::CODE_200, getProfileImpl(userId));
    }
    
    ENDPOINT("GET", "/api/user/statistics", getStatistics,
        REQUEST(std::shared_ptr<IncomingRequest>, request)) {
        auto userId = request->getBundleData<oatpp::String>("userId");
        if (!userId) {
            return createResponse(Status::CODE_401, "Unauthorized");
        }
        return createDtoResponse(Status::CODE_200, getStatisticsImpl(userId));
    }

private:
    oatpp::Object<UserProfileDto> getProfileImpl(const oatpp::String& userId);  
    oatpp::Vector<oatpp::Object<UserStatisticsDto>> getStatisticsImpl(const oatpp::String& userId);  
    std::unique_ptr<UserService> userService_;
};

#include OATPP_CODEGEN_END(ApiController)