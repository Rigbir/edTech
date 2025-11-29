//
// Created by Rigbir on 29.11.25.
//

#include "utils/EntityMapper.hpp"

AnswerOptionEntity EntityMapper::mapAnswerOption(
    const std::shared_ptr<oatpp::postgresql::ResultSet>& result,
    size_t rowIndex
) {
    auto row = result->getRow(rowIndex);
    AnswerOptionEntity entity;

    entity.id = row->get(0)->toString();
    entity.questionId = row->get(1)->toString();
    entity.optionText = row->get(2)->toString();
    entity.isCorrect = row->get(3)->toBool();
    entity.displayOrder = row->get(4)->toInt32();
    entity.createdAt = row->get(5)->toInt64();

    return entity;
}

