//
// Created by Rigbir on 01.12.25.
//

#include "controller/TestController.hpp"

TestController::TestController(const std::shared_ptr<ObjectMapper>& objectMapper)
    : oatpp::web::server::api::ApiController(objectMapper)
    , testService_(std::make_unique<TestService>())
    , progressService_(std::make_unique<ProgressService>())
{}

// ================================
// Test methods
// ================================
std::shared_ptr<TestDto> TestController::getTestById(const oatpp::String& testId) {
    return testService_->getTestById(testId);
}

std::vector<std::shared_ptr<TestListDto>> TestController::getTestsBySubjectId(const oatpp::String& subjectId) {
    return testService_->getTestsBySubjectId(subjectId);
}

std::vector<std::shared_ptr<TestListDto>> TestController::getPublishedTests() {
    return testService_->getPublishedTests();
}

std::shared_ptr<TestResultDto> TestController::submitTest(
    const oatpp::String& testId,
    const std::shared_ptr<SubmitTestRequestDto>& body
) {
    auto answers = parseAnswers(body->answers);
    return testService_->submitTest(
        body->userId,
        testId,
        answers,
        body->timeSpentSeconds
    );
}

// ================================
// Progress methods
// ================================
std::shared_ptr<TestProgressDto> TestController::saveTestProgress(
    const oatpp::String& testId,
    const std::shared_ptr<SaveProgressRequestDto>& body
) {
    auto answers = parseAnswers(body->answers);
    return progressService_->saveProgress(
        body->userId,
        testId,
        answers,
        body->timeSpentSeconds
    );
}

std::shared_ptr<TestProgressDto> TestController::getTestProgress(
    const oatpp::String& userId,
    const oatpp::String& testId
) {
    return progressService_->getProgress(userId, testId);
}

std::shared_ptr<TestProgressDto> TestController::updateTestProgress(
    const oatpp::String& testId,
    const oatpp::String& progressId,
    const std::shared_ptr<UpdateProgressRequestDto>& body
) {
    auto answers = parseAnswers(body->answers);
    return progressService_->updateProgress(
        progressId,
        answers,
        body->timeSpentSeconds
    );
}

std::map<oatpp::String, std::vector<oatpp::String>> TestController::parseAnswers(
    const oatpp::String& answersJson
) {
    auto objectMapper = getDefaultObjectMapper();
    
    auto json = objectMapper->readFromString<oatpp::Any>(answersJson);
    
    std::map<oatpp::String, std::vector<oatpp::String>> result;
    
    if (json.getType() == oatpp::Any::Type::MAP) {
        auto map = json.cast<oatpp::Fields<oatpp::Any>>();
        for (const auto& pair : *map) {
            oatpp::String questionId = pair.first;
            oatpp::Any answerArray = pair.second;
            
            std::vector<oatpp::String> answerIds;
            if (answerArray.getType() == oatpp::Any::Type::VECTOR) {
                auto vec = answerArray.cast<oatpp::Vector<oatpp::String>>();
                for (const auto& answerId : *vec) {
                    answerIds.push_back(answerId);
                }
            }
            result[questionId] = answerIds;
        }
    }
    
    return result;
}