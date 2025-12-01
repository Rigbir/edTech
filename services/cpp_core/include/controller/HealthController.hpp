//
// Created by Rigbir on 01.12.25.
//

#pragma once

#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include "model/dto/HealthDto.hpp"
#include <memory>

/**
 * HealthController - controller for health check
 * 
 * Purpose: Provides a health check endpoint to verify the status of the application.
 * 
 * Dependencies: Depends on DatabaseClient and CacheService.
 *               Used by load balancer to check the status of the application.
 */
#include OATPP_CODEGEN_BEGIN(ApiController)

class HealthController: public oatpp::web::server::api::ApiController {
public:
    HealthController(const std::shared_ptr<ObjectMapper>& objectMapper);

public:
    ENDPOINT("GET", "/health", health);

private:
    std::shared_ptr<HealthDto> health();
};

#include OATPP_CODEGEN_END(ApiController)