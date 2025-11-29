//
// Created by Rigbir on 29.11.25.
//

#include "repository/TestRepository.hpp"
#include "database/DatabaseClient.hpp"
#include "utils/EntityMapper.hpp"
#include <stdexcept>

TestRepository::TestRepository()
    : executor_(DatabaseClient::getInstance().getExecutor()) 
{
    if (!executor_) {
        throw std::runtime_error("Failed to initialize executor");
    }
}

TestEntity TestRepository::getTestById(
    const oatpp::String& id
) {
    auto result = executor_->execute(
        "SELECT id, subject_id, title, description, difficulty, "
        "estimated_time_minutes, max_score, passing_score, "
        "is_published, is_archived, author_id, moderator_id, "
        "moderation_status, moderation_comment, version, "
        "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
        "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at, "
        "EXTRACT(EPOCH FROM published_at)::bigint as published_at "
        "FROM tests WHERE id = $1",
        {id}
    );

    auto rows = result->fetch();
    if (!rows || rows->size() == 0) {
        throw std::runtime_error("Test not found");
    }

    return EntityMapper::mapTest(result, 0);
}

std::vector<TestEntity> TestRepository::getTestsBySubjectId(
    const oatpp::String& subjectId
) {
    auto result = executor_->execute(
        "SELECT id, subject_id, title, description, difficulty, "
        "estimated_time_minutes, max_score, passing_score, "
        "is_published, is_archived, author_id, moderator_id, "
        "moderation_status, moderation_comment, version, "
        "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
        "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at, "
        "EXTRACT(EPOCH FROM published_at)::bigint as published_at "
        "FROM tests "
        "WHERE subject_id = $1 AND is_published = true AND is_archived = false "
        "ORDER BY created_at DESC",
        {subjectId}
    );

    std::vector<TestEntity> entities;
    auto rows = result->fetch();

    for (size_t i = 0; i < rows->size(); ++i) {
        entities.push_back(EntityMapper::mapTest(result, i));
    }

    return entities;
}

std::vector<TestEntity> TestRepository::getPublishedTests() {
    auto result = executor_->execute(
        "SELECT id, subject_id, title, description, difficulty, "
        "estimated_time_minutes, max_score, passing_score, "
        "is_published, is_archived, author_id, moderator_id, "
        "moderation_status, moderation_comment, version, "
        "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
        "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at, "
        "EXTRACT(EPOCH FROM published_at)::bigint as published_at "
        "FROM tests "
        "WHERE is_published = true AND is_archived = false "
        "ORDER BY published_at DESC"
    );

    std::vector<TestEntity> entities;
    auto rows = result->fetch();

    for (size_t i = 0; i < rows->size(); ++i) {
        entities.push_back(EntityMapper::mapTest(result, i));
    }

    return entities;
}