//
// Created by Rigbir on 01.12.25.
//

#include "controller/HealthController.hpp"
#include "database/DatabaseClient.hpp"
#include "service/CacheService.hpp"

HealthController::HealthController(const std::shared_ptr<ObjectMapper>& objectMapper)
    : oatpp::web::server::api::ApiController(objectMapper)
{}

oatpp::Object<HealthDto> HealthController::healthImpl() {
    auto dto = HealthDto::createShared();

    auto& dbClient = DatabaseClient::getInstance();
    bool dbConnected = dbClient.isConnected();

    auto& cacheService = CacheService::getInstance();
    bool redisConnected = cacheService.isConnected();

    if (dbConnected && redisConnected) {
        dto->status = "ok";
        dto->message = "All services are running";
    } else {
        dto->status = "error";
        dto->message = "Some services are not running";
    }

    dto->database = dbConnected ? "connected" : "disconnected";
    dto->redis = redisConnected ? "connected" : "disconnected";

    return dto;
} 