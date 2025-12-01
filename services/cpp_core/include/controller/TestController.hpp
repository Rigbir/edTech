//
// Created by Rigbir on 01.12.25.
//

#pragma once

#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/api/ApiController.hpp>
#include "model/dto/UpdateProgressRequestDto.hpp"
#include "model/dto/SaveProgressRequestDto.hpp"
#include "model/dto/SubmitTestRequestDto.hpp"
#include "model/dto/TestProgressDto.hpp"
#include <oatpp/core/macro/codegen.hpp>
#include "service/ProgressService.hpp"
#include "model/dto/TestResultDto.hpp"
#include "model/dto/TestListDto.hpp"
#include "service/TestService.hpp"
#include "model/dto/TestDto.hpp"
#include <oatpp/core/Types.hpp>
#include <memory>
#include <vector>
#include <map>

#include OATPP_CODEGEN_BEGIN(ApiController)

class TestController: public oatpp::web::server::api::ApiController {
public:
    TestController(const std::shared_ptr<ObjectMapper>& objectMapper);

public:
    ENDPOINT("GET", "/api/tests/{testId}", getTestById, PATH(String, testId));
    ENDPOINT("GET", "/api/tests", getTestsBySubjectId, QUERY(String, subjectId));
    ENDPOINT("GET", "/api/tests/published", getPublishedTests);

    ENDPOINT("POST", "/api/tests/{testId}/submit", submitTest,
        PATH(String, testId),
        BODY_DTO(Object<SubmitTestRequestDto>, body));

    ENDPOINT("POST", "/api/tests/{testId}/progress", saveTestProgress,
        PATH(String, testId),
        BODY_DTO(Object<SaveProgressRequestDto>, body));
    ENDPOINT("GET", "/api/tests/{testId}/progress", getTestProgress,
        PATH(String, testId),
        QUERY(String, userId));
    ENDPOINT("PUT", "/api/tests/{testId}/progress/{progressId}", updateTestProgress,
        PATH(String, testId),
        PATH(String, progressId),
        BODY_DTO(Object<UpdateProgressRequestDto>, body));

private:
    // ================================
    // Test methods
    // ================================
    std::shared_ptr<TestDto> getTestById(const oatpp::String& testId);
    std::vector<std::shared_ptr<TestListDto>> getTestsBySubjectId(const oatpp::String& subjectId);
    std::vector<std::shared_ptr<TestListDto>> getPublishedTests();
    std::shared_ptr<TestResultDto> submitTest(
        const oatpp::String& testId,
        const std::shared_ptr<SubmitTestRequestDto>& body
    );

    // ================================
    // Progress methods
    // ================================
    std::shared_ptr<TestProgressDto> saveTestProgress(
        const oatpp::String& testId,
        const std::shared_ptr<SaveProgressRequestDto>& body
    );
    std::shared_ptr<TestProgressDto> getTestProgress(
        const oatpp::String& userId,
        const oatpp::String& testId
    );
    std::shared_ptr<TestProgressDto> updateTestProgress(
        const oatpp::String& testId,
        const oatpp::String& progressId,
        const std::shared_ptr<UpdateProgressRequestDto>& body
    );

    std::map<oatpp::String, std::vector<oatpp::String>> parseAnswers(
        const oatpp::String& answersJson
    );

private:
    std::unique_ptr<TestService> testService_;
    std::unique_ptr<ProgressService> progressService_;
};

#include OATPP_CODEGEN_END(ApiController)