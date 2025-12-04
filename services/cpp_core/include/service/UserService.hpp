//
// Created by Rigbir on 04.12.25.
//

#pragma once

#include "repository/UserStatisticsRepository.hpp"
#include "repository/SubjectRepository.hpp"
#include "model/dto/UserStatisticsDto.hpp"
#include "repository/UserRepository.hpp"
#include "model/dto/UserProfileDto.hpp"
#include "model/entity/UserEntity.hpp"
#include <oatpp/core/Types.hpp>
#include <memory>
#include <vector>

/**
 * UserService - works with user
 * 
 * Purpose: Provides user authentication and statistics.
 * 
 * Dependencies: Depends on UserRepository and UserStatisticsRepository.
 */
class UserService {
public:
    UserService();

    std::shared_ptr<UserEntity> authenticate(
        const oatpp::String& email,
        const oatpp::String& password
    ) const;

    oatpp::Object<UserProfileDto> getProfile(const oatpp::String& userId) const;
    oatpp::Vector<oatpp::Object<UserStatisticsDto>> getStatistics(
        const oatpp::String& userId
    ) const;

private:
    bool verifyPassword(
        const oatpp::String& password,
        const oatpp::String& passwordHash
    ) const;

    oatpp::Object<UserProfileDto> convertToProfileDto(const UserEntity& entity);
    oatpp::Object<UserStatisticsDto> convertToStatisticsDto(
        const UserStatisticsEntity& entity,
        const oatpp::String& subjectName = nullptr
    );

private:
    std::unique_ptr<UserRepository> userRepository_;
    std::unique_ptr<UserStatisticsRepository> userStatisticsRepository_;
    std::unique_ptr<SubjectRepository> subjectRepository_; 
};