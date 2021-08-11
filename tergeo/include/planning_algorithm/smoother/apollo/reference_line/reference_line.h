/******************************************************************************
 * Copyright 2017 The tergeo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file reference_line.h
 **/

#pragma once

#include <string>
#include <utility>
#include <vector>

#include "planner_plugins/planner_common/math/common/vec2d.h"
#include "planner_plugins/planner_common/reference_line/pnc_types.h"

namespace tergeo {
namespace planning {

class ReferenceLine {
 public:
  ReferenceLine() = default;
  explicit ReferenceLine(const ReferenceLine& reference_line, bool smoothed);
  explicit ReferenceLine(const std::vector<tergeo::common::PathPoint>& reference_points, bool smoothed);

  const std::vector<tergeo::common::PathPoint>& reference_points() const;
  //注意SL与XY之间的转换在转弯处可能存在一对多的情况,如何确保转换唯一?
  bool SLToXY(const common::SLPoint& sl_point,common::math::Vec2d* const xy_point);
  bool XYToSL(const common::math::Vec2d& xy_point,common::SLPoint* const sl_point);
  double Length() const;

  void SetSmoothed(bool is_smoothed){is_smoothed_ = is_smoothed;}

private:
  size_t findPrecursorIndex(const double s);
private:
  std::vector<tergeo::common::PathPoint> reference_points_;
  bool is_smoothed_ = false;
};

}  // namespace planning
}  // namespace tergeo
