//
// Created by Rigbir on 29.11.25.
//

#include "repository/TagRepository.hpp"
#include "database/DatabaseClient.hpp"
#include "utils/EntityMapper.hpp"
#include <stdexcept>

TagRepository::TagRepository()
    : executor_(DatabaseClient::getInstance().getExecutor())
{
    if (!executor_) {
        throw std::runtime_error("Failed to initialize executor");
    }
}

std::vector<TagEntity> TagRepository::getAllTags() {
    auto result = executor_->execute(
        "SELECT id, name, color, "
        "EXTRACT(EPOCH FROM created_at)::bigint as created_at "
        "FROM tags "
        "ORDER BY name ASC"
    );

    std::vector<TagEntity> entities;
    auto rows = result->fetch();

    for (size_t i = 0; i < rows->size(); ++i) {
        entities.push_back(EntityMapper::mapTag(result, i));
    }

    return entities;
}

std::vector<TagEntity> TagRepository::getTagsByTestId(
    const oatpp::String& testId
) {
    auto result = executor_->execute(
        "SELECT t.id, t.name, t.color, "
        "EXTRACT(EPOCH FROM t.created_at)::bigint as created_at "
        "FROM tags t "
        "INNER JOIN test_tags tt ON tt.tag_id = t.id "
        "WHERE tt.test_id = $1 "
        "ORDER BY t.name ASC",
        {testId}
    );

    std::vector<TagEntity> entities;
    auto rows = result->fetch();

    for (size_t i = 0; i < rows->size(); ++i) {
        entities.push_back(EntityMapper::mapTag(result, i));
    }

    return entities;
}
