//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include "model/entity/AnswerOptionEntity.hpp"
#include "model/entity/QuestionEntity.hpp"
#include "model/entity/SubjectEntity.hpp"
#include "model/entity/TagEntity.hpp"
#include "model/entity/TestEntity.hpp"
#include "model/entity/TestTagEntity.hpp"
#include "model/entity/UserEntity.hpp"
#include "model/entity/UserStatisticsEntity.hpp"
#include "model/entity/UserTestProgressEntity.hpp"
#include <oatpp-postgresql/ResultSet.hpp>
#include <memory>

/**
 * EntityMapper - utility functions for mapping database entities to DTOs
 * 
 * Purpose: Provides utility functions for mapping database entities to DTOs.
 *          Used by ProgressService to convert entities to DTOs.
 */
namespace EntityMapper {
    AnswerOptionEntity mapAnswerOption(
        const std::shared_ptr<oatpp::postgresql::ResultSet>& result, 
        size_t rowIndex = 0
    );

    QuestionEntity mapQuestion(
        const std::shared_ptr<oatpp::postgresql::ResultSet>& result,
        size_t rowIndex = 0
    );

    SubjectEntity mapSubject(
        const std::shared_ptr<oatpp::postgresql::ResultSet>& result, 
        size_t rowIndex = 0
    );

    TagEntity mapTag(
        const std::shared_ptr<oatpp::postgresql::ResultSet>& result,
        size_t rowIndex = 0
    );

    TestEntity mapTest(
        const std::shared_ptr<oatpp::postgresql::ResultSet>& result, 
        size_t rowIndex = 0
    );

    TestTagEntity mapTestTag(
        const std::shared_ptr<oatpp::postgresql::ResultSet>& result,
        size_t rowIndex = 0
    );

    UserEntity mapUser(
        const std::shared_ptr<oatpp::postgresql::ResultSet>& result, 
        size_t rowIndex = 0
    );

    UserStatisticsEntity mapUserStatistics(
        const std::shared_ptr<oatpp::postgresql::ResultSet>& result,
        size_t rowIndex = 0
    );
    
    UserTestProgressEntity mapUserTestProgress(
        const std::shared_ptr<oatpp::postgresql::ResultSet>& result, 
        size_t rowIndex = 0
    );
}