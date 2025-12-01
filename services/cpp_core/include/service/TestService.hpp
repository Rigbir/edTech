//
// Created by Rigbir on 30.11.25.
//

#pragma once

#include "repository/IUserTestProgressRepository.hpp"
#include "repository/IAnswerOptionRepository.hpp"
#include "repository/IQuestionRepository.hpp"
#include "repository/ISubjectRepository.hpp"
#include "repository/ITestRepository.hpp"
#include "repository/ITagRepository.hpp"
#include "model/dto/TestResultDto.hpp"
#include "model/dto/TestListDto.hpp"
#include "model/dto/TestDto.hpp"

#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include "service/CacheService.hpp"
#include "utils/EntityMapper.hpp"
#include <oatpp/core/Types.hpp>
#include <memory>
#include <vector>
#include <string>
#include <map>

/** 
 * TestService - works with tests
 * 
 * Purpose: Provides access to tests. Retrieves tests by ID, by subject,
 *          and published tests. This is the main service that combines
 *          data from other services (Subject, Tag, Question, AnswerOption).
 * 
 * Dependencies: Depends on SubjectService (subject_id FK).
 *               Used by TestController to build complete test structure.
 */
class TestService {
public:
    TestService();
    ~TestService() = default;

    // ================================
    // Main methods
    // ================================
    std::shared_ptr<TestDto> getTestById(const oatpp::String& id);
    std::vector<std::shared_ptr<TestListDto>> getTestsBySubjectId(const oatpp::String& subjectId);
    std::vector<std::shared_ptr<TestListDto>> getPublishedTests();

    std::shared_ptr<TestResultDto> submitTest(
        const oatpp::String& userId,
        const oatpp::String& testId,
        const std::map<oatpp::String, std::vector<oatpp::String>>& userAnswers,
        int timeSpentSeconds
    );

private:
    // ================================
    // Helper methods for conversion
    // ================================
    std::shared_ptr<TestDto> convertToDto(
        const TestEntity& testEntity,
        const SubjectEntity& subjectEntity,
        const std::vector<QuestionEntity>& questions,
        const std::vector<std::vector<AnswerOptionEntity>>& answerOptionsByQuestion,
        const std::vector<TagEntity>& tags
    );
    
    std::shared_ptr<TestListDto> convertToListDto(
        const TestEntity& testEntity,
        const SubjectEntity& subjectEntity,
        const std::vector<TagEntity>& tags
    );

    // ================================
    // Helper methods for answer checking
    // ================================
    struct AnswerCheckResult {
        int correctCount;
        int totalCount;
        std::map<oatpp::String, bool> questionResults;  // questionId -> isCorrect
    };
    
    AnswerCheckResult checkAnswers(
        const oatpp::String& testId,
        const std::map<oatpp::String, std::vector<oatpp::String>>& userAnswers
    );

    bool compareAnswers(
        const std::vector<oatpp::String>& correctAnswers,
        const std::vector<oatpp::String>& userAnswers
    );

    oatpp::Vector<oatpp::Object<QuestionDto>> getQuestionsWithCorrectAnswers(
        const oatpp::String& testId,
        const std::vector<QuestionEntity>& questions
    );
    
    struct ScoreResult {
        int score;
        float percentage;
        int correctAnswers;
        int totalQuestions;
    };
    
    ScoreResult calculateScore(int correct, int total);
    
private:
    // ================================
    // Dependencies
    // ================================
    std::unique_ptr<ITestRepository> testRepository_;
    std::unique_ptr<IQuestionRepository> questionRepository_;
    std::unique_ptr<IAnswerOptionRepository> answerOptionRepository_;
    std::unique_ptr<ISubjectRepository> subjectRepository_;
    std::unique_ptr<ITagRepository> tagRepository_;
    std::unique_ptr<IUserTestProgressRepository> userTestProgressRepository_;
    
    // JSON mapper for serialization/deserialization
    std::shared_ptr<oatpp::parser::json::mapping::ObjectMapper> jsonObjectMapper_;
};