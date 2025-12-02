//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <hiredis/hiredis.h>
#include <optional>
#include <string>
#include <vector>
#include <memory>

/**
 * CacheService - Redis cache wrapper
 * 
 * Purpose: Provides caching layer for tests, correct answers, user progress,
 *          and sessions. Reduces database load and improves response times.
 * 
 * Dependencies: Requires Redis server running and configured in AppConfig.
 *               Uses hiredis library for Redis communication.
 */
class CacheService {
public:
    static CacheService& getInstance();

    // ================================
    // Work with tests
    // ================================
    std::optional<std::string> getTest(const std::string& testId) const;
    void setTest(const std::string& testId,
                 const std::string& jsonData,
                 int ttlSeconds = 7200) const;
    void invalidateTest(const std::string& testId);

    // ================================
    // Work with correct answers
    // ================================
    std::optional<std::string> getCorrectAnswer(const std::string& testId);
    void setCorrectAnswer(const std::string& testId,    
                          const std::vector<std::string>& answerIds,
                          int ttlSeconds = 86400) const;
                       
    // ================================
    // Work with user progress
    // ================================
    std::optional<std::string> getProgress(const std::string& userId, const std::string& testId);
    void setProgress(const std::string& userId,
                     const std::string& testId,
                     const std::string& jsonData,
                     int ttlSeconds = 7200) const;
    void deleteProgress(const std::string& userId, const std::string& testId);

    // ================================
    // Work with user statistics
    // ================================
    std::optional<std::string> getUserStatistics(const std::string& userId);
    void setUserStatistics(const std::string& userId,
                           const std::string& jsonData,
                           int ttlSeconds = 86400) const;
    void deleteUserStatistics(const std::string& userId);

    // ================================
    // Work with sessions
    // ================================
    std::optional<std::string> getSession(const std::string& userId);
    void setSession(const std::string& userId, 
                    const std::string& sessionData, 
                    int ttlSeconds = 86400) const;

    // ================================
    // Utilities
    // ================================
    bool isConnected() const;
    void deleteKey(const std::string& key);
    void setTTL(const std::string& key, int ttlSeconds);

private:
    CacheService();
    ~CacheService() = default;
    CacheService(const CacheService&) = delete;
    CacheService& operator=(const CacheService&) = delete;
    CacheService(CacheService&&) = delete;
    CacheService& operator=(CacheService&&) = delete;

private:
    void initialize();
    std::string buildKey(const std::string& prefix, const std::string& id) const;
    std::string buildKey(const std::string& prefix,
                         const std::string& id1,
                         const std::string& id2) const;

    // ================================
    // Helper methods for Redis operations
    // ================================
    std::optional<std::string> executeGet(const std::string& key) const;
    void executeSetEx(const std::string& key, const std::string& value, int ttlSeconds) const;
    void executeDel(const std::string& key) const;
    void executeDel(const std::string& key1, const std::string& key2) const;

private:
    // Custom deleter for hiredis context
    using RedisContextPtr = std::unique_ptr<redisContext, decltype(&redisFree)>;
    RedisContextPtr redisContext_;
};