//
// Created by Rigbir on 01.12.25.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class HealthDto : public oatpp::DTO {
    DTO_INIT(HealthDto, DTO)

    DTO_FIELD(String, status);           
    DTO_FIELD(String, database);        
    DTO_FIELD(String, redis);          
    DTO_FIELD(String, message);         
};

#include OATPP_CODEGEN_END(DTO)