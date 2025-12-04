//
// Created by Rigbir on 04.12.25.
//

#include "service/UserService.hpp"
#include "bcrypt/BCrypt.hpp"

UserService::UserService() 
    : userRepository_(std::make_unique<UserRepository>())
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