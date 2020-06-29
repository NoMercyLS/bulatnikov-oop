#pragma once
#include <string>

const std::string INIT_MESSAGE = "Enter this commands to create shapes : \nLineSegment <x1> <y1> <x2> <y2> ( <outline color> )\nTriangle <x1> <y1> <x2> <y2> <x3> <y3>( <outline color> <fill color> )\nCircle <x> <y> <radius> ( <outline color> <fill color> )\nRectangle <x> <y> <width> <height> ( <outline color> <fill color> )\nExample: Rectangle 10.3 20.15 30.7 40.4 ff0000 00ff00\n";
const std::string MARKER = ">";
const std::string UNKNOWN_COMMAND = "Unknown command!\n";
const uint32_t DEFAULT_OUTLINE_COLOR = 0x000000;
const uint32_t DEFAULT_FILL_COLOR = 0xFFFFFF;
const std::string ALL_SHAPES_MESSAGE = "All shapes:\n";
const std::string FAIL_LINE_CREATE_MESSAGE = "Failed to create a line segment.\nUsage: LineSegment <x1> <y1> <x2> <y2> ( <outline color> )\n";
const std::string FAIL_TRIANGLE_CREATE_MESSAGE = "Failed to create a triangle.\nUsage: Triangle <x1> <y1> <x2> <y2> <x3> <y3>( <outline color> <fill color> )\n";
const std::string FAIL_CIRCLE_CREATE_MESSAGE = "Failed to create a circle.\nUsage: Circle <x> <y> <radius> ( <outline color> <fill color> )\n";
const std::string FAIL_RECTANGLE_CREATE_MESSAGE = "Failed to create a rectangle.\nUsage: Rectangle <x> <y> <width> <height> ( <outline color> <fill color> )\n";
const std::string SHAPE_MIN_PERIMETER = "Shape with min perimeter is ";
const std::string MIN_PERIMETER_FAIL = "Failed to get the shape with min perimeter. Shapes list is empty.\n";
const std::string SHAPE_MAX_AREA = "Shape with max area is ";
const std::string MAX_AREA_FAIL = "Failed to get the shape with max area. Shapes list is empty.\n";