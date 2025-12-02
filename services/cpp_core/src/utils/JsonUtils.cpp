//
// Created by Rigbir on 01.12.25.
//

#include "utils/JsonUtils.hpp"
#include <chrono>

namespace JsonUtils {

std::string escapeJsonString(const std::string& str) {
    std::string escaped;
    escaped.reserve(str.size() * 2);  
    
    for (char c : str) {
        switch (c) {
            case '"':
                escaped += "\\\"";
                break;
            case '\\':
                escaped += "\\\\";
                break;
            case '\n':
                escaped += "\\n";
                break;
            case '\r':
                escaped += "\\r";
                break;
            case '\t':
                escaped += "\\t";
                break;
            default:
                escaped += c;
                break;
        }
    }
    
    return escaped;
}

std::string serializeAnswersToJson(
    const std::map<std::string, std::vector<std::string>>& userAnswers
) {
    std::string json = "{";
    bool first = true;
    
    for (const auto& [questionId, answerIds] : userAnswers) {
        if (!first) {
            json += ",";
        }
        first = false;
        
        json += "\"" + escapeJsonString(questionId) + "\":";
        
        json += "[";
        for (size_t i = 0; i < answerIds.size(); ++i) {
            if (i > 0) {
                json += ",";
            }
            json += "\"" + escapeJsonString(answerIds[i]) + "\"";
        }
        json += "]";
    }
    
    json += "}";
    return json;
}

} 