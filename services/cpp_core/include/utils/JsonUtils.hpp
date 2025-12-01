//
// Created by Rigbir on 01.12.25.
//

#pragma once

#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/core/Types.hpp>
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <map>

/**
 * JsonUtils - utility functions for working with JSON
 * 
 * Purpose: Provides utility functions for escaping JSON strings and
 *          serializing user answers to JSON.
 */
namespace JsonUtils {
    // ================================
    // JSON string operations
    // ================================
    std::string escapeJsonString(const std::string& str);
    
    std::string serializeAnswersToJson(
        const std::map<oatpp::String, std::vector<oatpp::String>>& userAnswers
    );

    // ================================
    // DTO serialization (templates)
    // ================================
    template<typename T>
    std::string serializeToJson(
        const std::shared_ptr<T>& dto,
        const std::shared_ptr<oatpp::parser::json::mapping::ObjectMapper>& objectMapper
    ) {
        return objectMapper->writeToString(dto)->c_str();
    }

    template<typename T>
    std::shared_ptr<T> deserializeFromJson(
        const std::string& json,
        const std::shared_ptr<oatpp::parser::json::mapping::ObjectMapper>& objectMapper
    ) {
        return objectMapper->readFromString<oatpp::Object<T>>(
            oatpp::String(json.c_str())
        );
    }

    // ================================
    // Timestamp utilities
    // ================================
    inline oatpp::Int64 getCurrentTimestamp() {
        return std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();
    }
}