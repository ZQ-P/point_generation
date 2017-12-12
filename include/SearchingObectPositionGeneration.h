#pragma once

//#pragma once

#include <stdio.h>
#include <string.h>
#include <vector>

enum shapeOfObject { Circle, Rectangle };

template <shapeOfObject objectShape>
struct parametersOfShape {

};
template <>
struct parametersOfShape<Circle> {
	double radius;
	double angle;
};
template <>
struct parametersOfShape<Rectangle> {
	double width;
	double length;
};

struct pointPosition {
	double x;
	double y;
	double angle;
};

const double PI = 3.1415926;

class SearchingObectPositionGeneration
{
private:
	shapeOfObject objectShape;
	parametersOfShape<Circle> circleCharacters;
	parametersOfShape<Rectangle> rectangleCharacters;
	std::vector<pointPosition> pointsPose;
	void setParametersOfCircle(const double &param1, const double &param2);
	void setParametersOfRectangle(const double &param1, const double &param2);
	void generateSerchingOutlineCircle(parametersOfShape<Circle> &circleOutline);
	void generateSerchingOutlineRectangle(parametersOfShape<Rectangle> &rectangleOutline);
	void discretizeSerchingOutlineCircle();
	void discretizeSerchingOutlineRectangle();

public:
	static const double resolutionOfMap;
	static const double distanceBetweenPoints;
	static const double distanceOfVision;
	SearchingObectPositionGeneration(const shapeOfObject &objectShape, const double &param1, const double &param2);
	void discretizeSerchingOutline();
	void getPointsPose(std::vector<pointPosition> &pointsPose);

};