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
oatpp::Object<TestDto> TestController::getTestByIdImpl(const oatpp::String& testId) {
    return testService_->getTestById(testId);
}

std::vector<oatpp::Object<TestListDto>> TestController::getTestsBySubjectIdImpl(const oatpp::String& subjectId) {
    return testService_->getTestsBySubjectId(subjectId);
}

std::vector<oatpp::Object<TestListDto>> TestController::getPublishedTestsImpl() {
    return testService_->getPublishedTests();
}

oatpp::Object<TestResultDto> TestController::submitTestImpl(
    const oatpp::String& testId,
    const oatpp::Object<SubmitTestRequestDto>& body
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
oatpp::Object<TestProgressDto> TestController::saveTestProgressImpl(
    const oatpp::String& testId,
    const oatpp::Object<SaveProgressRequestDto>& body
) {
    auto answers = parseAnswers(body->answers);
    return progressService_->saveProgress(
        body->userId,
        testId,
        answers,
        body->timeSpentSeconds
    );
}

oatpp::Object<TestProgressDto> TestController::getTestProgressImpl(
    const oatpp::String& userId,
    const oatpp::String& testId
) {
    return progressService_->getProgress(userId, testId);
}

oatpp::Object<TestProgressDto> TestController::updateTestProgressImpl(
    const oatpp::String& testId,
    const oatpp::String& progressId,
    const oatpp::Object<UpdateProgressRequestDto>& body
) {
    auto answers = parseAnswers(body->answers);
    return progressService_->updateProgress(
        progressId,
        answers,
        body->timeSpentSeconds
    );
}

std::map<std::string, std::vector<std::string>> TestController::parseAnswers(
    const oatpp::String& answersJson
) {
    std::map<std::string, std::vector<std::string>> result;
    
    if (!answersJson || answersJson->empty()) {
        return result;
    }
    
    try {
        auto objectMapper = getDefaultObjectMapper();
        auto parsedMap = objectMapper->readFromString<oatpp::UnorderedMap<oatpp::String, oatpp::Vector<oatpp::String>>>(
            answersJson
        );
        
        if (parsedMap) {
            for (const auto& pair : *parsedMap) {
                std::vector<std::string> answerIds;
                if (pair.second) {
                    for (const auto& answerId : *pair.second) {
                        if (answerId) {
                            answerIds.push_back(answerId->c_str());
                        }
                    }
                }
                if (pair.first) {
                    result[pair.first->c_str()] = answerIds;
                }
            }
        }
    } catch (const std::exception& e) {
        return {};
    }
    
    return result;
}