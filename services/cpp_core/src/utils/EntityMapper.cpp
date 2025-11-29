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

SubjectEntity EntityMapper::mapSubject(
    const std::shared_ptr<oatpp::postgresql::ResultSet>& result,
    size_t rowIndex
) {
    auto row = result->getRow(rowIndex);
    SubjectEntity entity;

    entity.id = row->get(0)->toString();
    entity.name = row->get(1)->toString();
    entity.description = row->get(2)->toString();
    entity.iconUrl = row->get(3)->toString();
    entity.color = row->get(4)->toString();
    entity.displayOrder = row->get(5)->toInt32();
    entity.isActive = row->get(6)->toBool();
    entity.createdAt = row->get(7)->toInt64();
    entity.updatedAt = row->get(8)->toInt64();

    return entity;
}

TagEntity EntityMapper::mapTag(
    const std::shared_ptr<oatpp::postgresql::ResultSet>& result,
    size_t rowIndex
) {
    auto row = result->getRow(rowIndex);
    TagEntity entity;

    entity.id = row->get(0)->toString();
    entity.name = row->get(1)->toString();
    entity.color = row->get(2)->toString();
    entity.createdAt = row->get(3)->toInt64();

    return entity;
}

