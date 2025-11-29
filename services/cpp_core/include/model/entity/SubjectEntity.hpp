//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>

class SubjectEntity {
public:
    oatpp::String id;
    oatpp::String name;
    oatpp::String description;
    oatpp::String iconUrl;
    oatpp::String color;  // hex color
    oatpp::Int32 displayOrder;
    oatpp::Boolean isActive;
    oatpp::Int64 createdAt;  // timestamp
    oatpp::Int64 updatedAt;  // timestamp
};

