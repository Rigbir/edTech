//
// Created by Rigbir on 29.11.25.
//

#include "service/CacheService.hpp"
#include "config/AppConfig.hpp"
#include "utils/JsonUtils.hpp"
#include <stdexcept>

CacheService::CacheService()
    : redisContext_(nullptr, redisFree)
{
    initialize();
}

CacheService& CacheService::getInstance() {
    static CacheService instance;
    return instance;
}

void CacheService::initialize() {
    auto& config = AppConfig::getInstance();

    redisContext* ctx = redisConnect(
        config.getRedisHost().c_str(), 
        config.getRedisPort()
    );

    if (!ctx || ctx->err) {
        throw std::runtime_error(
            "Failed to connect to Redis: " + 
            std::string(ctx ? ctx->errstr : "Unknown error")
        );
    }

    if (!config.getRedisPassword().empty()) {
        redisReply* reply = static_cast<redisReply*>(
            redisCommand(ctx, "AUTH %s", config.getRedisPassword().c_str())
        );
        if (reply) {
            freeReplyObject(reply);
        }
    }

    redisContext_.reset(ctx);
}

std::string CacheService::buildKey(const std::string& prefix, const std::string& id) const {
    return prefix + ":" + id;
}

std::string CacheService::buildKey(const std::string& prefix,
                                   const std::string& id1,
                                   const std::string& id2) const {
    return prefix + ":" + id1 + ":" + id2;
}

// ================================
// Helper methods for Redis operations
// ================================
std::optional<std::string> CacheService::executeGet(const std::string& key) const {
    if (!isConnected()) {
        return std::nullopt;
    }

    redisReply* reply = static_cast<redisReply*>(
        redisCommand(redisContext_.get(), "GET %s", key.c_str())
    );

    if (!reply) {
        return std::nullopt;
    }
    
    std::optional<std::string> result;
    
    if (reply->type == REDIS_REPLY_STRING) {
        result = std::string(reply->str, reply->len);
    } else if (reply->type == REDIS_REPLY_NIL) {
        result = std::nullopt;
    } else {
        result = std::nullopt;
    }
    
    freeReplyObject(reply);
    
    return result;
}

void CacheService::executeSetEx(const std::string& key,
                                const std::string& value,
                                int ttlSeconds) const {
    if (!isConnected()) {
        return;
    }

    redisReply *reply = static_cast<redisReply *>(
        redisCommand(redisContext_.get(), "SETEX %s %d %s", key.c_str(), ttlSeconds, value.c_str())
    );

    if (!reply) {
        return;
    }

    if (reply->type == REDIS_REPLY_ERROR) {
        freeReplyObject(reply);
        return;
    }

    freeReplyObject(reply);
}

void CacheService::executeDel(const std::string& key) const {
    if (!isConnected()) {
        return;
    }
    
    redisReply* reply = static_cast<redisReply*>(
        redisCommand(redisContext_.get(), "DEL %s", key.c_str())
    );
    
    if (!reply) {
        return;
    }
    
    if (reply->type == REDIS_REPLY_ERROR) {
        freeReplyObject(reply);
        return;
    }
    
    freeReplyObject(reply);
}

void CacheService::executeDel(const std::string& key1, const std::string& key2) const {
    if (!isConnected()) {
        return;
    }
    
    redisReply* reply = static_cast<redisReply*>(
        redisCommand(redisContext_.get(), "DEL %s %s", key1.c_str(), key2.c_str())
    );
    
    if (!reply) {
        return;
    }
    
    if (reply->type == REDIS_REPLY_ERROR) {
        freeReplyObject(reply);
        return;
    }
    
    freeReplyObject(reply);
}

// ================================
// Work with tests
// ================================
std::optional<std::string> CacheService::getTest(const std::string& testId) const {
    std::string key = buildKey("test", testId) + ":full";
    return executeGet(key);
}

void CacheService::setTest(const std::string& testId,
                           const std::string& jsonData,
                           int ttlSeconds) const {
    std::string key = buildKey("test", testId) + ":full";
    executeSetEx(key, jsonData, ttlSeconds);
}

void CacheService::invalidateTest(const std::string& testId) {
    std::string keyFull = buildKey("test", testId) + ":full";
    std::string keyAnswers = buildKey("test", testId) + ":correct_answers";
    executeDel(keyFull, keyAnswers);
}

// ================================
// Work with correct answers
// ================================
std::optional<std::string> CacheService::getCorrectAnswer(const std::string& testId) {
    std::string key = buildKey("test", testId) + ":correct_answers";
    return executeGet(key);
}

void CacheService::setCorrectAnswer(const std::string& testId,
                                    const std::vector<std::string>& answerIds,
                                    int ttlSeconds) const {
    std::string key = buildKey("test", testId) + ":correct_answers";

    std::string jsonData = "[";
    for (std::vector<std::string>::size_type i = 0; i < answerIds.size(); ++i) {
        if (i > 0) {
            jsonData += ",";
        }
        jsonData += "\"" + JsonUtils::escapeJsonString(answerIds[i]) + "\"";
    }
    jsonData += "]";

    executeSetEx(key, jsonData, ttlSeconds);
}

// ================================
// Work with user progress
// ================================
std::optional<std::string> CacheService::getProgress(const std::string& userId, const std::string& testId) {
    std::string key = buildKey("user", userId) + ":test:" + testId + ":progress";
    return executeGet(key);
}

void CacheService::setProgress(const std::string& userId,
                               const std::string& testId,
                               const std::string& jsonData,
                               int ttlSeconds) const {
    std::string key = buildKey("user", userId) + ":test:" + testId + ":progress";
    executeSetEx(key, jsonData, ttlSeconds);
}

void CacheService::deleteProgress(const std::string& userId, const std::string& testId) {
    std::string key = buildKey("user", userId) + ":test:" + testId + ":progress";
    executeDel(key);
}

// ================================
// Work with user statistics
// ================================
std::optional<std::string> CacheService::getUserStatistics(const std::string& userId) {
    std::string key = buildKey("user", userId) + ":statistics";
    return executeGet(key);
}

void CacheService::setUserStatistics(const std::string& userId,
                                     const std::string& jsonData,
                                     int ttlSeconds) const {
    std::string key = buildKey("user", userId) + ":statistics";
    executeSetEx(key, jsonData, ttlSeconds);                            
}

void CacheService::deleteUserStatistics(const std::string& userId) {
    std::string key = buildKey("user", userId) + ":statistics";
    executeDel(key);
}

// ================================
// Work with sessions
// ================================
std::optional<std::string> CacheService::getSession(const std::string& userId) {
    std::string key = buildKey("user", userId) + ":session";
    return executeGet(key);
}

void CacheService::setSession(const std::string& userId,
                              const std::string& sessionData,
                              int ttlSeconds) const {
    std::string key = buildKey("user", userId) + ":session";
    executeSetEx(key, sessionData, ttlSeconds);
}

// ================================
// Utilities
// ================================
bool CacheService::isConnected() const {
    return redisContext_ && !redisContext_->err;
}

void CacheService::deleteKey(const std::string& key) {
    executeDel(key);
}

void CacheService::setTTL(const std::string& key, int ttlSeconds) {
    if (!isConnected()) {
        return;
    }

    redisReply* reply = static_cast<redisReply*>(
        redisCommand(redisContext_.get(), "EXPIRE %s %d", key.c_str(), ttlSeconds)
    );

    if (!reply) {
        return;
    }

    if (reply->type == REDIS_REPLY_ERROR) { 
        freeReplyObject(reply);
        return;
    }

    freeReplyObject(reply);
}