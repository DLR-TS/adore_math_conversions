#include <gtest/gtest.h>

#include "adore_math_conversions.hpp"
#include <adore_ros2_msgs/msg/point2d.hpp>
#include <adore_ros2_msgs/msg/polygon2d.hpp>

using adore::math::Point2d;
using adore::math::Polygon2d;
namespace conv = adore::math::conversions;

// Helper to compare two Point2d instances
static void
expect_point_equal( const Point2d& a, const Point2d& b )
{
  EXPECT_DOUBLE_EQ( a.x, b.x );
  EXPECT_DOUBLE_EQ( a.y, b.y );
}

// Helper to compare two ROS Point2d messages
static void
expect_point_msg_equal( const adore_ros2_msgs::msg::Point2d& a, const adore_ros2_msgs::msg::Point2d& b )
{
  EXPECT_DOUBLE_EQ( a.x, b.x );
  EXPECT_DOUBLE_EQ( a.y, b.y );
}

// Helper to compare two Polygon2d instances
static void
expect_polygon_equal( const Polygon2d& a, const Polygon2d& b )
{
  ASSERT_EQ( a.points.size(), b.points.size() );
  for( std::size_t i = 0; i < a.points.size(); ++i )
  {
    expect_point_equal( a.points[i], b.points[i] );
  }
}

// Helper to compare two ROS Polygon2d messages
static void
expect_polygon_msg_equal( const adore_ros2_msgs::msg::Polygon2d& a, const adore_ros2_msgs::msg::Polygon2d& b )
{
  ASSERT_EQ( a.points.size(), b.points.size() );
  for( std::size_t i = 0; i < a.points.size(); ++i )
  {
    expect_point_msg_equal( a.points[i], b.points[i] );
  }
}

TEST( AdoreMathConversions, point2d_ros_to_cpp_round_trip )
{
  adore_ros2_msgs::msg::Point2d ros_point;
  ros_point.x = 1.23;
  ros_point.y = -4.56;

  const Point2d cpp_point      = conv::to_cpp_type( ros_point );
  const auto    ros_point_back = conv::to_ros_msg( cpp_point );

  // Check both intermediate cpp value and final round-trip ROS value
  EXPECT_DOUBLE_EQ( ros_point.x, cpp_point.x );
  EXPECT_DOUBLE_EQ( ros_point.y, cpp_point.y );
  expect_point_msg_equal( ros_point, ros_point_back );
}

TEST( AdoreMathConversions, point2d_cpp_to_ros_round_trip )
{
  Point2d cpp_point;
  cpp_point.x = -10.0;
  cpp_point.y = 42.5;

  const auto    ros_point      = conv::to_ros_msg( cpp_point );
  const Point2d cpp_point_back = conv::to_cpp_type( ros_point );

  // Check both intermediate ROS value and final round-trip C++ value
  EXPECT_DOUBLE_EQ( cpp_point.x, ros_point.x );
  EXPECT_DOUBLE_EQ( cpp_point.y, ros_point.y );
  expect_point_equal( cpp_point, cpp_point_back );
}

TEST( AdoreMathConversions, polygon2d_ros_to_cpp_round_trip_non_empty )
{
  adore_ros2_msgs::msg::Polygon2d ros_polygon;

  adore_ros2_msgs::msg::Point2d p0;
  p0.x = 0.0;
  p0.y = 0.0;
  ros_polygon.points.push_back( p0 );

  adore_ros2_msgs::msg::Point2d p1;
  p1.x = 1.0;
  p1.y = 2.0;
  ros_polygon.points.push_back( p1 );

  adore_ros2_msgs::msg::Point2d p2;
  p2.x = -3.5;
  p2.y = 4.5;
  ros_polygon.points.push_back( p2 );

  const Polygon2d cpp_polygon      = conv::to_cpp_type( ros_polygon );
  const auto      ros_polygon_back = conv::to_ros_msg( cpp_polygon );

  // Size must be preserved
  ASSERT_EQ( ros_polygon.points.size(), cpp_polygon.points.size() );
  ASSERT_EQ( ros_polygon.points.size(), ros_polygon_back.points.size() );

  // Round-trip equality
  expect_polygon_msg_equal( ros_polygon, ros_polygon_back );
}

TEST( AdoreMathConversions, polygon2d_cpp_to_ros_round_trip_non_empty )
{
  Polygon2d cpp_polygon;
  cpp_polygon.points.reserve( 3 );

  Point2d p0;
  p0.x = 10.0;
  p0.y = 20.0;
  cpp_polygon.points.push_back( p0 );

  Point2d p1;
  p1.x = -1.0;
  p1.y = -2.0;
  cpp_polygon.points.push_back( p1 );

  Point2d p2;
  p2.x = 3.14;
  p2.y = -3.14;
  cpp_polygon.points.push_back( p2 );

  const auto      ros_polygon      = conv::to_ros_msg( cpp_polygon );
  const Polygon2d cpp_polygon_back = conv::to_cpp_type( ros_polygon );

  // Size must be preserved
  ASSERT_EQ( cpp_polygon.points.size(), ros_polygon.points.size() );
  ASSERT_EQ( cpp_polygon.points.size(), cpp_polygon_back.points.size() );

  // Round-trip equality
  expect_polygon_equal( cpp_polygon, cpp_polygon_back );
}

TEST( AdoreMathConversions, polygon2d_round_trip_empty )
{
  // Empty ROS polygon
  adore_ros2_msgs::msg::Polygon2d ros_polygon;
  const Polygon2d                 cpp_polygon      = conv::to_cpp_type( ros_polygon );
  const auto                      ros_polygon_back = conv::to_ros_msg( cpp_polygon );

  EXPECT_TRUE( ros_polygon.points.empty() );
  EXPECT_TRUE( cpp_polygon.points.empty() );
  EXPECT_TRUE( ros_polygon_back.points.empty() );
}