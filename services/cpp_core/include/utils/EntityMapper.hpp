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
#include <oatpp/core/data/mapping/type/Any.hpp>
#include <oatpp/core/Types.hpp>
#include <memory>

/**
 * EntityMapper - utility functions for mapping database entities to DTOs
 * 
 * Purpose: Provides utility functions for mapping database entities to DTOs.
 *          Used by ProgressService to convert entities to DTOs.
 */
namespace EntityMapper {
    AnswerOptionEntity mapAnswerOption(
        const oatpp::Vector<oatpp::Fields<oatpp::Any>>& rows,
        size_t rowIndex = 0
    );

    QuestionEntity mapQuestion(
        const oatpp::Vector<oatpp::Fields<oatpp::Any>>& rows,
        size_t rowIndex = 0
    );

    SubjectEntity mapSubject(
        const oatpp::Vector<oatpp::Fields<oatpp::Any>>& rows, 
        size_t rowIndex = 0
    );

    TagEntity mapTag(
        const oatpp::Vector<oatpp::Fields<oatpp::Any>>& rows,
        size_t rowIndex = 0
    );

    TestEntity mapTest(
        const oatpp::Vector<oatpp::Fields<oatpp::Any>>& rows, 
        size_t rowIndex = 0
    );

    TestTagEntity mapTestTag(
        const oatpp::Vector<oatpp::Fields<oatpp::Any>>& rows,
        size_t rowIndex = 0
    );

    UserEntity mapUser(
        const oatpp::Vector<oatpp::Fields<oatpp::Any>>& rows, 
        size_t rowIndex = 0
    );

    UserStatisticsEntity mapUserStatistics(
        const oatpp::Vector<oatpp::Fields<oatpp::Any>>& rows,
        size_t rowIndex = 0
    );
    
    UserTestProgressEntity mapUserTestProgress(
        const oatpp::Vector<oatpp::Fields<oatpp::Any>>& rows, 
        size_t rowIndex = 0
    );
}