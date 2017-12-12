#pragma once

//#pragma once

#include <stdio.h>
#include <string.h>
#include <vector>

enum shapeOfObject { Circle, Rectangle };

template <shapeOfObject objectShape>
struct ParametersOfShape {

};
template <>
struct ParametersOfShape<Circle> {
	double radius;
	double angle;
};
template <>
struct ParametersOfShape<Rectangle> {
	double width;
	double length;
};

struct PointPose {
	double x;
	double y;
	double angle;
};

const double PI = 3.1415926;

class SearchingObjectPositionGeneration
{
private:
	shapeOfObject objectShape;
	ParametersOfShape<Circle> circleCharacters;
	ParametersOfShape<Rectangle> rectangleCharacters;
	std::vector<PointPose> pointsPose;
	void generateSerchingOutlineCircle(ParametersOfShape<Circle> &circleOutline);
	void generateSerchingOutlineRectangle(ParametersOfShape<Rectangle> &rectangleOutline);
	void discretizeSerchingOutlineCircle();
	void discretizeSerchingOutlineRectangle();

public:
	static const double resolutionOfMap;
	static const double distanceBetweenPoints;
	static const double distanceOfVision;
	SearchingObjectPositionGeneration();
	SearchingObjectPositionGeneration(const shapeOfObject &objectShape, const double &param1, const double &param2);
	void setParametersOfCircle(const double &param1, const double &param2);
	void setParametersOfRectangle(const double &param1, const double &param2);
	void discretizeSerchingOutline();
	void getPointsPose(std::vector<PointPose> &pointsPose);

};