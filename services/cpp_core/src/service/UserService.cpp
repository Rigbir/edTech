//
// Created by Rigbir on 04.12.25.
//

#include "service/UserService.hpp"
#include "bcrypt/BCrypt.hpp"

UserService::UserService() 
    : userRepository_(std::make_unique<UserRepository>())
    , userStatisticsRepository_(std::make_unique<UserStatisticsRepository>())
    , subjectRepository_(std::make_unique<SubjectRepository>())
{}

std::shared_ptr<UserEntity> UserService::authenticate(
    const oatpp::String& email,
    const oatpp::String& password
) const {
    auto user = userRepository_->getUserByEmail(email);
    if (!user) {
        return nullptr; 
    }
    
    if (!user->isActive) {
        return nullptr;  
    }
    
    if (!verifyPassword(password, user->passwordHash)) {
        return nullptr;  
    }

    return user;
}

oatpp::Object<UserProfileDto> UserService::getProfile(const oatpp::String& userId) {
    auto user = userRepository_->getUserById(userId);
    if (!user) {
        return nullptr;  
    }
    
    return convertToProfileDto(*user);
}

oatpp::Vector<oatpp::Object<UserStatisticsDto>> UserService::getStatistics(const oatpp::String& userId) {
    auto statsEntities = userStatisticsRepository_->getStatisticsByUserId(userId);
    
    auto result = oatpp::Vector<oatpp::Object<UserStatisticsDto>>::createShared();
    
    for (const auto& entity : statsEntities) {
        oatpp::String subjectName = nullptr;
        
        if (entity->subjectId) {
            auto subject = subjectRepository_->getSubjectById(entity->subjectId);
            if (subject) {
                subjectName = subject->name;
            }
        }
        
        result->push_back(convertToStatisticsDto(*entity, subjectName));
    }
    
    return result;
}

bool UserService::verifyPassword(
    const oatpp::String& password,
    const oatpp::String& passwordHash
) const {
    if (!password || !passwordHash) {
        return false;
    }
    
    return BCrypt::validatePassword(
        password->c_str(),
        passwordHash->c_str()
    );
}

oatpp::Object<UserProfileDto> UserService::convertToProfileDto(const UserEntity& entity) {
    auto dto = UserProfileDto::createShared();
    dto->id = entity.id;
    dto->username = entity.username;
    dto->firstName = entity.firstName;
    dto->lastName = entity.lastName;
    dto->avatarUrl = entity.avatarUrl;
    dto->role = entity.role;
    dto->email = entity.email;  
    return dto;
}

oatpp::Object<UserStatisticsDto> UserService::convertToStatisticsDto(
    const UserStatisticsEntity& entity,
    const oatpp::String& subjectName
) {
    auto dto = UserStatisticsDto::createShared();
    dto->subjectId = entity.subjectId;
    dto->subjectName = subjectName;
    dto->testsCompleted = entity.testsCompleted;
    dto->testsStarted = entity.testsStarted;
    dto->averageScore = entity.averageScore;
    dto->bestScore = entity.bestScore;
    dto->totalTimeSpentSeconds = entity.totalTimeSpentSeconds;
    dto->lastActivityAt = entity.lastActivityAt;
    return dto;
}