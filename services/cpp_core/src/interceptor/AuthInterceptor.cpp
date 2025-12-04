//
// Created by Rigbir on 02.12.25.
//

#include <oatpp/web/protocol/http/outgoing/ResponseFactory.hpp>
#include "interceptor/AuthInterceptor.hpp"
#include "config/AppConfig.hpp"
#include <jwt-cpp/jwt.h>

AuthInterceptor::AuthInterceptor()
    : authService_(std::make_unique<AuthService>(
        AppConfig::getInstance().getJwtSecretKey()
    ))
{
    publicEndpoints_.insert("/health");
    publicEndpoints_.insert("/api/auth/login");
    publicEndpoints_.insert("/api/tests/published");
    publicEndpoints_.insert("/api/tests");
}

std::shared_ptr<oatpp::web::server::interceptor::RequestInterceptor::OutgoingResponse>
AuthInterceptor::intercept(const std::shared_ptr<IncomingRequest>& request) {
    if (isPublicEndpoint(request->getPathTail())) {
        return nullptr;
    }

    auto token = extractToken(request);
    if (!token) {
        auto response = oatpp::web::protocol::http::outgoing::ResponseFactory::createResponse(
            oatpp::web::protocol::http::Status::CODE_401,
            "Missing or invalid Authorization header"
        );
        return response;
    }

    auto userId = validateToken(token);
    if (!userId) {
        auto response = oatpp::web::protocol::http::outgoing::ResponseFactory::createResponse(
            oatpp::web::protocol::http::Status::CODE_401,
            "Invalid or expired token"
        );
        return response;
    }

    request->putBundleData("userId", userId);
    request->putBundleData("token", token);

    return nullptr;
}

bool AuthInterceptor::isPublicEndpoint(const oatpp::String& path) const {
    std::string pathStr = path->c_str();
    return publicEndpoints_.contains(pathStr);
}

oatpp::String AuthInterceptor::extractToken(
    const std::shared_ptr<oatpp::web::protocol::http::incoming::Request>& request
) const {
    auto authHeader = request->getHeader("Authorization");
    if (!authHeader) {
        return nullptr;
    }

    std::string authStr = authHeader->c_str();
    if (authStr.find("Bearer ") != 0) {
        return nullptr;
    }

    return oatpp::String(authStr.substr(7).c_str());
}

oatpp::String AuthInterceptor::validateToken(const oatpp::String& token) const {
    return authService_->validateToken(token->c_str());
}
