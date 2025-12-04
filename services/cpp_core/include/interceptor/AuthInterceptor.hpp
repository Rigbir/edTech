//
// Created by Rigbir on 02.12.25.
//

#pragma once

#include <oatpp/web/server/interceptor/RequestInterceptor.hpp>
#include "service/AuthService.hpp"
#include <oatpp/core/Types.hpp>
#include <unordered_set>
#include <string>
#include <memory>

/**
 * AuthInterceptor - interceptor for authentication
 * 
 * Purpose: Intercepts requests and checks if the user is authenticated.
 *          If not, returns a 401 Unauthorized response.
 * 
 * Dependencies: Depends on UserService (user_id FK).
 *               Used by AuthInterceptor to check if the user is authenticated.
 */
class AuthInterceptor: public oatpp::web::server::interceptor::RequestInterceptor {
public:
    AuthInterceptor();

    std::shared_ptr<OutgoingResponse> intercept(
        const std::shared_ptr<IncomingRequest>& request
    ) override;

private:
    std::unordered_set<std::string> publicEndpoints_;

    bool isPublicEndpoint(const oatpp::String& path) const;
    oatpp::String extractToken(
        const std::shared_ptr<oatpp::web::protocol::http::incoming::Request>& request
    ) const;
    oatpp::String validateToken(const oatpp::String& token) const;

private:
    std::unique_ptr<AuthService> authService_;
};