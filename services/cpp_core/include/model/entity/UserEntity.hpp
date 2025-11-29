//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>

class UserEntity {
public:
    oatpp::String id;
    oatpp::String email;
    oatpp::String passwordHash;
    oatpp::String username;
    oatpp::String role;  // student, teacher, admin, moderator
    oatpp::String firstName;
    oatpp::String lastName;
    oatpp::String avatarUrl;
    oatpp::Boolean isActive;
    oatpp::Boolean emailVerified;
    oatpp::Int64 createdAt;  // timestamp
    oatpp::Int64 updatedAt;  // timestamp
    oatpp::Int64 lastLoginAt;  // timestamp (nullable)
};

