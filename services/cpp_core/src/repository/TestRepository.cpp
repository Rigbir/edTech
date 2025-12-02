//
// Created by Rigbir on 29.11.25.
//

#include "repository/TestRepository.hpp"
#include "database/DatabaseClient.hpp"
#include "utils/EntityMapper.hpp"
#include <stdexcept>

TestRepository::TestRepository()
    : dbClient_(std::make_shared<TestDb>(
          DatabaseClient::getInstance().getExecutor()
      ))
{
    if (!dbClient_) {
        throw std::runtime_error("Failed to initialize TestDb");
    }
}

TestEntity TestRepository::getTestById(
    const oatpp::String& id
) {
    auto queryResult = dbClient_->getTestById(id);
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    
    if (!rows || rows->size() == 0) {
        throw std::runtime_error("Test not found");
    }

    return EntityMapper::mapTest(rows, 0);
}

std::vector<TestEntity> TestRepository::getTestsBySubjectId(
    const oatpp::String& subjectId
) {
    auto queryResult = dbClient_->getTestsBySubjectId(subjectId);
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    
    std::vector<TestEntity> entities;
    for (size_t i = 0; i < rows->size(); ++i) {
        entities.push_back(EntityMapper::mapTest(rows, i));
    }

    return entities;
}

std::vector<TestEntity> TestRepository::getPublishedTests() {
    auto queryResult = dbClient_->getPublishedTests();
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    
    std::vector<TestEntity> entities;
    for (size_t i = 0; i < rows->size(); ++i) {
        entities.push_back(EntityMapper::mapTest(rows, i));
    }

    return entities;
}
