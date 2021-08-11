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
 * @file
 **/

#pragma once

#include <vector>

#include "reference_line.h"
#include "planner_plugins/planner_common/reference_line/pnc_types.h"

namespace tergeo {
namespace planning {
//wz:每一个anchor需要给定x,y,theta以及对应的bound.
struct AnchorPoint {
  tergeo::common::PathPoint path_point;
  double lateral_bound = 0.0;
  double longitudinal_bound = 0.0;
  // enforce smoother to strictly follow this reference point
  bool enforced = false;
};

class ReferenceLineSmoother {
 public:
  explicit ReferenceLineSmoother() {}

  /**
   * Smoothing constraints
   */
  virtual void SetAnchorPoints(
      const std::vector<AnchorPoint>& achor_points) = 0;

  /**
   * Smooth a given reference line
   */
  virtual bool Smooth(ReferenceLine* const) = 0;
  virtual ~ReferenceLineSmoother() = default;
};

}  // namespace planning
}  // namespace tergeo
