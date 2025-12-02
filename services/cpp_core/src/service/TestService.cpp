//
// Created by Marat on 30.11.25.
//

#include "utils/JsonUtils.hpp"
#include "service/TestService.hpp"
#include "model/entity/TestEntity.hpp"
#include "model/entity/SubjectEntity.hpp"
#include "model/entity/QuestionEntity.hpp"
#include "model/entity/AnswerOptionEntity.hpp"
#include "model/entity/TagEntity.hpp"

#include "repository/TestRepository.hpp"
#include "repository/QuestionRepository.hpp"
#include "repository/AnswerOptionRepository.hpp"
#include "repository/TagRepository.hpp"
#include "repository/SubjectRepository.hpp"
#include "repository/UserTestProgressRepository.hpp"

#include <set>

TestService::TestService()
    : testRepository_(std::make_unique<TestRepository>())
    , questionRepository_(std::make_unique<QuestionRepository>())
    , answerOptionRepository_(std::make_unique<AnswerOptionRepository>())
    , subjectRepository_(std::make_unique<SubjectRepository>())
    , tagRepository_(std::make_unique<TagRepository>())
    , userTestProgressRepository_(std::make_unique<UserTestProgressRepository>())
    , jsonObjectMapper_(oatpp::parser::json::mapping::ObjectMapper::createShared())
{}

// ================================
// Main methods
// ================================
oatpp::Object<TestDto> TestService::getTestById(const oatpp::String& id) {
    auto& cache = CacheService::getInstance();
    auto cachedJson = cache.getTest(id->c_str());

    if (cachedJson.has_value()) {
        return JsonUtils::deserializeFromJson<TestDto>(cachedJson.value(), jsonObjectMapper_);
    }

    auto test = testRepository_->getTestById(id);
    auto subject = subjectRepository_->getSubjectById(test.subjectId);
    auto tags = tagRepository_->getTagsByTestId(id);

    auto questions = questionRepository_->getQuestionsByTestId(id);
    std::vector<std::vector<AnswerOptionEntity>> answerOptionsByQuestion;
    for (const auto& question : questions) {
        auto options = answerOptionRepository_->getAnswerOptionsByQuestionId(question.id);
        answerOptionsByQuestion.emplace_back(std::move(options));
    }

    auto dto = convertToDto(test, subject, questions, answerOptionsByQuestion, tags);
    
    std::string json = JsonUtils::serializeToJson<TestDto>(dto, jsonObjectMapper_);
    cache.setTest(id->c_str(), json, 7200);
    
    return dto;
}

std::vector<oatpp::Object<TestListDto>> TestService::getTestsBySubjectId(const oatpp::String& subjectId) {
    auto tests = testRepository_->getTestsBySubjectId(subjectId);
    auto subject = subjectRepository_->getSubjectById(subjectId);

    std::vector<oatpp::Object<TestListDto>> dtoList;
    for (const auto& test : tests) {
        auto tags = tagRepository_->getTagsByTestId(test.id);
        auto dto = convertToListDto(test, subject, tags);
        dtoList.emplace_back(std::move(dto));
    }

    return dtoList;
}

std::vector<oatpp::Object<TestListDto>> TestService::getPublishedTests() {
    auto tests = testRepository_->getPublishedTests();

    std::vector<oatpp::Object<TestListDto>> dtoList;
    for (const auto& test : tests) {
        auto subject = subjectRepository_->getSubjectById(test.subjectId);
        auto tags = tagRepository_->getTagsByTestId(test.id);

        auto dto = convertToListDto(test, subject, tags);
        dtoList.emplace_back(std::move(dto));
    }

    return dtoList;
}

oatpp::Object<TestResultDto> TestService::submitTest(
    const oatpp::String& userId,
    const oatpp::String& testId,
    const std::map<std::string, std::vector<std::string>>& userAnswers,
    int timeSpentSeconds
) {
    auto questions = questionRepository_->getQuestionsByTestId(testId);
    auto checkResult = checkAnswers(testId, userAnswers);
    auto scoreResult = calculateScore(checkResult.correctCount, checkResult.totalCount);
    std::string answersJson = JsonUtils::serializeAnswersToJson(userAnswers);

    UserTestProgressEntity progress;
    progress.userId = userId;
    progress.testId = testId;
    progress.status = "completed";
    progress.score = scoreResult.score;
    progress.percentage = scoreResult.percentage;
    progress.timeSpentSeconds = timeSpentSeconds;
    progress.startedAt = JsonUtils::getCurrentTimestamp();
    progress.completedAt = JsonUtils::getCurrentTimestamp();
    progress.answersJson = oatpp::String(answersJson.c_str());

    auto savedProgress = userTestProgressRepository_->saveProgress(progress);

    auto result = TestResultDto::createShared();
    result->testId = testId;
    result->score = scoreResult.score;
    result->percentage = scoreResult.percentage;
    result->correctAnswers = checkResult.correctCount;
    result->totalQuestions = checkResult.totalCount;
    result->timeSpentSeconds = timeSpentSeconds;
    result->completedAt = savedProgress.completedAt;

    auto questionsWithAnswers = getQuestionsWithCorrectAnswers(testId, questions);
    result->questions = questionsWithAnswers;

    return result;
}

// ================================
// Helper methods for conversion
// ================================
oatpp::Object<TestDto> TestService::convertToDto(
    const TestEntity& testEntity,
    const SubjectEntity& subjectEntity,
    const std::vector<QuestionEntity>& questions,
    const std::vector<std::vector<AnswerOptionEntity>>& answerOptionsByQuestion,
    const std::vector<TagEntity>& tags
) {
    auto dto = TestDto::createShared();

    dto->id = testEntity.id;
    dto->subjectId = testEntity.subjectId;
    dto->subjectName = subjectEntity.name;
    dto->title = testEntity.title;
    dto->description = testEntity.description;
    dto->difficulty = testEntity.difficulty;
    dto->estimatedTimeMinutes = testEntity.estimatedTimeMinutes;
    dto->maxScore = testEntity.maxScore;
    dto->passingScore = testEntity.passingScore;
    dto->isPublished = testEntity.isPublished;
    dto->publishedAt = testEntity.publishedAt;

    auto tagDtos = oatpp::Vector<oatpp::Object<TagDto>>::createShared();
    for (const auto& tag : tags) {
        auto tagDto = TagDto::createShared();
        tagDto->id = tag.id;
        tagDto->name = tag.name;
        tagDto->color = tag.color;
        tagDtos->push_back(tagDto);
    }
    dto->tags = tagDtos;

    auto questionDtos = oatpp::Vector<oatpp::Object<QuestionDto>>::createShared();
    for (size_t i = 0; i < questions.size(); ++i) {
        const auto& question = questions[i];
        auto questionDto = QuestionDto::createShared();

        questionDto->id = question.id;
        questionDto->questionText = question.questionText;
        questionDto->questionType = question.questionType;
        questionDto->explanation = question.explanation;
        questionDto->points = question.points;
        questionDto->displayOrder = question.displayOrder;
        questionDto->imageUrl = question.imageUrl;
        
        auto answerOptionDtos = oatpp::Vector<oatpp::Object<AnswerOptionDto>>::createShared();
        if (i < answerOptionsByQuestion.size()) {
            for (const auto& option : answerOptionsByQuestion[i]) {
                auto optionDto = AnswerOptionDto::createShared();
                optionDto->id = option.id;
                optionDto->optionText = option.optionText;
                optionDto->displayOrder = option.displayOrder;
                answerOptionDtos->push_back(optionDto);
            }
        }
        questionDto->answerOptions = answerOptionDtos;
        questionDtos->push_back(questionDto);
    }
    dto->questions = questionDtos;

    return dto;
}

oatpp::Object<TestListDto> TestService::convertToListDto(
    const TestEntity& testEntity,
    const SubjectEntity& subjectEntity,
    const std::vector<TagEntity>& tags
) {
    auto dto = TestListDto::createShared();

    dto->id = testEntity.id;
    dto->subjectId = testEntity.subjectId;
    dto->subjectName = subjectEntity.name;
    dto->title = testEntity.title;
    dto->description = testEntity.description;
    dto->difficulty = testEntity.difficulty;
    dto->estimatedTimeMinutes = testEntity.estimatedTimeMinutes;
    dto->maxScore = testEntity.maxScore;
    dto->passingScore = testEntity.passingScore;
    dto->publishedAt = testEntity.publishedAt;
    
    auto tagDtos = oatpp::Vector<oatpp::Object<TagDto>>::createShared();
    for (const auto& tag : tags) {
        auto tagDto = TagDto::createShared();
        tagDto->id = tag.id;
        tagDto->name = tag.name;
        tagDto->color = tag.color;
        tagDtos->push_back(tagDto);
    }
    dto->tags = tagDtos;
    
    return dto;
}

// ================================
// Helper methods for answer checking
// ================================
TestService::AnswerCheckResult TestService::checkAnswers(
    const oatpp::String& testId,
    const std::map<std::string, std::vector<std::string>>& userAnswers
) {
    auto questions = questionRepository_->getQuestionsByTestId(testId);

    AnswerCheckResult result;
    result.totalCount = questions.size();
    result.correctCount = 0;

    for (const auto& question : questions) {
        auto correctAnswerIds = answerOptionRepository_->getCorrectAnswerIds(question.id);
        std::string questionIdStr = question.id->c_str();
        auto userAnswerIt = userAnswers.find(questionIdStr);

        std::vector<oatpp::String> userAnswerIds;
        if (userAnswerIt != userAnswers.end()) {
            for (const auto& answerId : userAnswerIt->second) {
                userAnswerIds.push_back(oatpp::String(answerId.c_str()));
            }
        }

        bool isCorrect = compareAnswers(correctAnswerIds, userAnswerIds);
        result.questionResults[question.id->c_str()] = isCorrect;

        if (isCorrect) {
            ++result.correctCount;
        }
    }

    return result;
}

bool TestService::compareAnswers(
    const std::vector<oatpp::String>& correctAnswers,
    const std::vector<oatpp::String>& userAnswers
) {
    if (correctAnswers.size() != userAnswers.size()) {
        return false;
    }

    std::set<std::string> correctSet;
    for (const auto& id : correctAnswers) {
        correctSet.insert(id->c_str());
    }
    
    std::set<std::string> userSet;
    for (const auto& id : userAnswers) {
        userSet.insert(id->c_str());
    }

    return correctSet == userSet;
}

oatpp::Vector<oatpp::Object<QuestionDto>> TestService::getQuestionsWithCorrectAnswers(
    const oatpp::String& testId,
    const std::vector<QuestionEntity>& questions
) {
    auto questionDtos = oatpp::Vector<oatpp::Object<QuestionDto>>::createShared();
    
    for (const auto& question : questions) {
        auto questionDto = QuestionDto::createShared();
        questionDto->id = question.id;
        questionDto->questionText = question.questionText;
        questionDto->questionType = question.questionType;
        questionDto->explanation = question.explanation;
        questionDto->points = question.points;
        questionDto->displayOrder = question.displayOrder;
        questionDto->imageUrl = question.imageUrl;
        
        auto answerOptions = answerOptionRepository_->getAnswerOptionsByQuestionId(question.id);
        auto answerOptionDtos = oatpp::Vector<oatpp::Object<AnswerOptionDto>>::createShared();
        
        for (const auto& option : answerOptions) {
            auto optionDto = AnswerOptionDto::createShared();
            optionDto->id = option.id;
            optionDto->optionText = option.optionText;
            optionDto->displayOrder = option.displayOrder;
            optionDto->isCorrect = option.isCorrect;  
            answerOptionDtos->push_back(optionDto);
        }
        
        questionDto->answerOptions = answerOptionDtos;
        questionDtos->push_back(questionDto);
    }
    
    return questionDtos;
}

TestService::ScoreResult TestService::calculateScore(int correct, int total) {
    ScoreResult result;
    result.correctAnswers = correct;
    result.totalQuestions = total;
    result.score = correct;
    result.percentage = total > 0 ? static_cast<float>(correct) / total : 0.0f;
    return result;
}