/********************************************************************************
 * Copyright (c) 2025 Contributors to the Eclipse Foundation
 *
 * See the NOTICE file(s) distributed with this work for additional
 * information regarding copyright ownership.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * https://www.eclipse.org/legal/epl-2.0
 *
 * SPDX-License-Identifier: EPL-2.0
 ********************************************************************************/

#pragma once

#include "adore_math/polygon.h"
#include "adore_ros2_msgs/msg/point2d.hpp"
#include "adore_ros2_msgs/msg/polygon2d.hpp"

namespace adore
{
namespace math

{
namespace conversions
{
Point2d to_cpp_type( const adore_ros2_msgs::msg::Point2d& msg );

adore_ros2_msgs::msg::Point2d to_ros_msg( const Point2d& msg );

Polygon2d to_cpp_type( const adore_ros2_msgs::msg::Polygon2d& msg );

adore_ros2_msgs::msg::Polygon2d to_ros_msg( const Polygon2d& msg );

std::vector<Point2d> to_cpp_type( const std::vector<adore_ros2_msgs::msg::Point2d>& msg );

} // namespace conversions
} // namespace math
} // namespace adore