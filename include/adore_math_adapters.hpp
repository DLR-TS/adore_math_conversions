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

#include "adore_math_conversions.hpp"
#include <adore_math/geometry.hpp>
#include <adore_ros2_msgs/msg/point2d.hpp>
#include <adore_ros2_msgs/msg/polygon2d.hpp>

#include <rclcpp/type_adapter.hpp>

namespace rclcpp
{

// Adapter for Point2d
template<>
struct TypeAdapter<adore::mad::Point2d, adore_ros2_msgs::msg::Point2d>
{
  using is_specialized   = std::true_type;
  using custom_type      = adore::mad::Point2d;
  using ros_message_type = adore_ros2_msgs::msg::Point2d;

  static void
  convert_to_ros_message( const custom_type& src, ros_message_type& dst )
  {
    dst = adore::math::conversions::to_ros_msg( src );
  }

  static void
  convert_to_custom( const ros_message_type& src, custom_type& dst )
  {
    dst = adore::math::conversions::to_cpp_type( src );
  }
};

// Adapter for Polygon2d
template<>
struct TypeAdapter<adore::mad::Polygon2d, adore_ros2_msgs::msg::Polygon2d>
{
  using is_specialized   = std::true_type;
  using custom_type      = adore::mad::Polygon2d;
  using ros_message_type = adore_ros2_msgs::msg::Polygon2d;

  static void
  convert_to_ros_message( const custom_type& src, ros_message_type& dst )
  {
    dst = adore::math::conversions::to_ros_msg( src );
  }

  static void
  convert_to_custom( const ros_message_type& src, custom_type& dst )
  {
    dst = adore::math::conversions::to_cpp_type( src );
  }
};

} // namespace rclcpp

namespace adore
{
using PolygonAdapter = rclcpp::TypeAdapter<math::Polygon2d, adore_ros2_msgs::msg::Polygon2d>;
using Point2dAdapter = rclcpp::TypeAdapter<math::Point2d, adore_ros2_msgs::msg::Point2d>;
} // namespace adore
