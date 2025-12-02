//
// Created by Rigbir on 29.11.25.
//

#include "repository/SubjectRepository.hpp"
#include "database/DatabaseClient.hpp"
#include "utils/EntityMapper.hpp"
#include <stdexcept>

SubjectRepository::SubjectRepository()
    : dbClient_(std::make_shared<SubjectDb>(
          DatabaseClient::getInstance().getExecutor()
      ))
{
    if (!dbClient_) {
        throw std::runtime_error("Failed to initialize SubjectDb");
    }
}

std::vector<SubjectEntity> SubjectRepository::getSubjects() {
    auto queryResult = dbClient_->getSubjects();
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    
    std::vector<SubjectEntity> entities;
    for (size_t i = 0; i < rows->size(); ++i) {
        entities.push_back(EntityMapper::mapSubject(rows, i));
    }

    return entities;
}

SubjectEntity SubjectRepository::getSubjectById(
    const oatpp::String& id
) {
    auto queryResult = dbClient_->getSubjectById(id);
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    
    if (!rows || rows->size() == 0) {
        throw std::runtime_error("Subject not found");
    }

    return EntityMapper::mapSubject(rows, 0);
}

std::vector<SubjectEntity> SubjectRepository::getSubjectsByTestId(
    const oatpp::String& testId
) {
    auto queryResult = dbClient_->getSubjectsByTestId(testId);
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    
    std::vector<SubjectEntity> entities;
    for (size_t i = 0; i < rows->size(); ++i) {
        entities.push_back(EntityMapper::mapSubject(rows, i));
    }

    return entities;
}
