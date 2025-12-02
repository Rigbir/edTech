//
// Created by Rigbir on 29.11.25.
//

#include "repository/TagRepository.hpp"
#include "database/DatabaseClient.hpp"
#include "utils/EntityMapper.hpp"
#include <stdexcept>

TagRepository::TagRepository()
    : dbClient_(std::make_shared<TagDb>(
          DatabaseClient::getInstance().getExecutor()
      ))
{
    if (!dbClient_) {
        throw std::runtime_error("Failed to initialize TagDb");
    }
}

std::vector<TagEntity> TagRepository::getAllTags() {
    auto queryResult = dbClient_->getAllTags();
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    
    std::vector<TagEntity> entities;
    for (size_t i = 0; i < rows->size(); ++i) {
        entities.push_back(EntityMapper::mapTag(rows, i));
    }

    return entities;
}

std::vector<TagEntity> TagRepository::getTagsByTestId(
    const oatpp::String& testId
) {
    auto queryResult = dbClient_->getTagsByTestId(testId);
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    
    std::vector<TagEntity> entities;
    for (size_t i = 0; i < rows->size(); ++i) {
        entities.push_back(EntityMapper::mapTag(rows, i));
    }

    return entities;
}
