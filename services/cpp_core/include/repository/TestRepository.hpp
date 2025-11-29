//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include "repository/ITestRepository.hpp"
#include <oatpp-postgresql/Executor.hpp>
#include <memory>

/**
 * TestRepository - works with tests table
 * 
 * Purpose: Provides access to tests. Retrieves tests by ID, by subject,
 *          and published tests. This is the main repository that combines
 *          data from other repositories (Subject, Tag, Question, AnswerOption).
 * 
 * Dependencies: Depends on SubjectRepository (subject_id FK).
 *               Used by TestService to build complete test structure.
 */
class TestRepository : public ITestRepository {
public:
    TestRepository();

    TestEntity getTestById(
        const oatpp::String& id
    ) override;

    std::vector<TestEntity> getTestsBySubjectId(
        const oatpp::String& subjectId
    ) override;

    std::vector<TestEntity> getPublishedTests() override;

private:
    std::shared_ptr<oatpp::postgresql::Executor> executor_;
};