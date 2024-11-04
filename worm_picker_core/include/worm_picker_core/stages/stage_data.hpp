// stage_data.hpp
//
// Copyright (c) 2024
// SPDX-License-Identifier: Apache-2.0
//
// Author: Logan Kaising
// Additional Contributions: Fang-Yen Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");

#ifndef STAGE_DATA_HPP
#define STAGE_DATA_HPP

/**
 * @enum StageType
 * @brief Enumerates the types of stages available.
 */
enum class StageType { MOVE_TO_POINT, MOVE_TO_JOINT, MOVE_RELATIVE };

/**
 * @class StageData
 * @brief Abstract base class for different types of stage data.
 */
class StageData 
{
public:
    virtual ~StageData() = default;

    /**
     * @brief Retrieves the type of the stage.
     * @return StageType The type of the stage.
     */
    virtual StageType getType() const noexcept = 0;
};

#endif // STAGE_DATA_HPP
