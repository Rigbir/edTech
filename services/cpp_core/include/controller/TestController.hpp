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

/**
 * TestController - works with tests
 * 
 * Purpose: Provides access to tests. Retrieves tests by ID, by subject,
 *          and published tests. This is the main controller that combines
 *          data from other controllers (TestService, ProgressService).
 * 
 * Dependencies: Depends on TestService (test_id FK).
 *               Used by TestController to build complete test structure.
 */
#include OATPP_CODEGEN_BEGIN(ApiController)

class TestController: public oatpp::web::server::api::ApiController {
public:
    TestController(const std::shared_ptr<ObjectMapper>& objectMapper);

public:
    ENDPOINT("GET", "/api/tests/{testId}", getTestById, PATH(String, testId)) {
        return createDtoResponse(Status::CODE_200, getTestByIdImpl(testId));
    }
    ENDPOINT("GET", "/api/tests", getTestsBySubjectId, QUERY(String, subjectId)) {
        auto dtos = getTestsBySubjectIdImpl(subjectId);
        auto result = oatpp::Vector<oatpp::Object<TestListDto>>::createShared();
        for (const auto& dto : dtos) {
            result->push_back(dto);
        }
        return createDtoResponse(Status::CODE_200, result);
    }
    ENDPOINT("GET", "/api/tests/published", getPublishedTests) {
        auto dtos = getPublishedTestsImpl();
        auto result = oatpp::Vector<oatpp::Object<TestListDto>>::createShared();
        for (const auto& dto : dtos) {
            result->push_back(dto);
        }
        return createDtoResponse(Status::CODE_200, result);
    }

    ENDPOINT("POST", "/api/tests/{testId}/submit", submitTest,
        PATH(String, testId),
        BODY_DTO(Object<SubmitTestRequestDto>, body)) {
        return createDtoResponse(Status::CODE_200, submitTestImpl(testId, body));
    }

    ENDPOINT("POST", "/api/tests/{testId}/progress", saveTestProgress,
        PATH(String, testId),
        BODY_DTO(Object<SaveProgressRequestDto>, body)) {
        return createDtoResponse(Status::CODE_200, saveTestProgressImpl(testId, body));
    }
    ENDPOINT("GET", "/api/tests/{testId}/progress", getTestProgress,
        PATH(String, testId),
        QUERY(String, userId)) {
        return createDtoResponse(Status::CODE_200, getTestProgressImpl(userId, testId));
    }
    ENDPOINT("PUT", "/api/tests/{testId}/progress/{progressId}", updateTestProgress,
        PATH(String, testId),
        PATH(String, progressId),
        BODY_DTO(Object<UpdateProgressRequestDto>, body)) {
        return createDtoResponse(Status::CODE_200, updateTestProgressImpl(testId, progressId, body));
    }

private:
    // ================================
    // Test methods
    // ================================
    oatpp::Object<TestDto> getTestByIdImpl(const oatpp::String& testId);
    std::vector<oatpp::Object<TestListDto>> getTestsBySubjectIdImpl(const oatpp::String& subjectId);
    std::vector<oatpp::Object<TestListDto>> getPublishedTestsImpl();
    oatpp::Object<TestResultDto> submitTestImpl(
        const oatpp::String& testId,
        const oatpp::Object<SubmitTestRequestDto>& body
    );

    // ================================
    // Progress methods
    // ================================
    oatpp::Object<TestProgressDto> saveTestProgressImpl(
        const oatpp::String& testId,
        const oatpp::Object<SaveProgressRequestDto>& body
    );
    oatpp::Object<TestProgressDto> getTestProgressImpl(
        const oatpp::String& userId,
        const oatpp::String& testId
    );
    oatpp::Object<TestProgressDto> updateTestProgressImpl(
        const oatpp::String& testId,
        const oatpp::String& progressId,
        const oatpp::Object<UpdateProgressRequestDto>& body
    );

    std::map<std::string, std::vector<std::string>> parseAnswers(
        const oatpp::String& answersJson
    );

private:
    std::unique_ptr<TestService> testService_;
    std::unique_ptr<ProgressService> progressService_;
};

#include OATPP_CODEGEN_END(ApiController)