#include "SearchingObjectPositionGeneration.h"
#include <iostream>
#include <math.h>


const double SearchingObjectPositionGeneration::resolutionOfMap = 0.05;
const double SearchingObjectPositionGeneration::distanceBetweenPoints = 0.2;
const double SearchingObjectPositionGeneration::distanceOfVision = 0.6;

SearchingObjectPositionGeneration::SearchingObjectPositionGeneration() {

};

SearchingObjectPositionGeneration::SearchingObjectPositionGeneration(const shapeOfObject &objectShape, const double &param1, const double &param2) {
	switch (objectShape) {
	case 0:
		setParametersOfCircle(param1, param2);
		break;
	case 1:
		setParametersOfRectangle(param1, param2);
		break;
	default:
		std::cout << "there is no such object";
		exit(0);
		break;
	}
};

void SearchingObjectPositionGeneration::setParametersOfCircle(const double &param1, const double &param2) {
	pointsPose.clear();
	this->objectShape = Circle;
	circleCharacters.radius = param1;
	circleCharacters.angle = param2;
};
void SearchingObjectPositionGeneration::setParametersOfRectangle(const double &param1, const double &param2) {
	pointsPose.clear();
	this->objectShape = Rectangle;
	rectangleCharacters.width = param1;
	rectangleCharacters.length = param2;
};

void SearchingObjectPositionGeneration::generateSerchingOutlineCircle(ParametersOfShape<Circle> &circleOutline) {
	circleOutline.radius = circleCharacters.radius + distanceOfVision;
	circleOutline.angle = circleCharacters.angle;
};

void SearchingObjectPositionGeneration::generateSerchingOutlineRectangle(ParametersOfShape<Rectangle> &rectangleOutline) {
	rectangleOutline.width = rectangleCharacters.width + 2 * distanceOfVision;
	rectangleOutline.length = rectangleCharacters.length + 2 * distanceOfVision;
};

void SearchingObjectPositionGeneration::discretizeSerchingOutline() {
	switch (objectShape) {
	case 0:
		discretizeSerchingOutlineCircle();
		break;
	case 1:
		discretizeSerchingOutlineRectangle();
		break;
	default:
		std::cout << "there is no such object";
		exit(0);
		break;
	}
};

void SearchingObjectPositionGeneration::discretizeSerchingOutlineCircle() {
	ParametersOfShape<Circle> circleOutline;
	generateSerchingOutlineCircle(circleOutline);
	double discretizedAngle = distanceBetweenPoints / circleOutline.radius;
	int numberOfPoints = int(circleOutline.angle / discretizedAngle) + 1;
	for (int i = 0; i <= numberOfPoints; i++) {
		float angle = i*discretizedAngle;
		PointPose pointPose;
		pointPose.x = circleOutline.radius*sin(angle);
		pointPose.y = circleOutline.radius*cos(angle);
		pointPose.angle = angle - PI;
		pointsPose.push_back(pointPose);
	}
};

void SearchingObjectPositionGeneration::discretizeSerchingOutlineRectangle() {
	ParametersOfShape<Rectangle> rectangleOutline;
	generateSerchingOutlineRectangle(rectangleOutline);
	int numberXOfRectangleOutline = int(rectangleOutline.length / (2 * distanceBetweenPoints)) + 1;
	int numberYOfRectangleOutline = int(rectangleOutline.width / (2 * distanceBetweenPoints)) + 1;
	PointPose pointPose;
	for (int i = 0; i <= numberXOfRectangleOutline; i++) {
		pointPose.x = i*distanceBetweenPoints;
		pointPose.y = rectangleOutline.width / 2;
		pointPose.angle = -PI / 2;
		pointsPose.push_back(pointPose);
	}
	for (int i = numberYOfRectangleOutline; i > 0; i--) {
		pointPose.x = rectangleOutline.length / 2;
		pointPose.y = i*distanceBetweenPoints;
		pointPose.angle = PI;
		pointsPose.push_back(pointPose);
	}
	for (int i = 0; i <= numberYOfRectangleOutline; i++) {
		pointPose.x = rectangleOutline.length / 2;
		pointPose.y = -i*distanceBetweenPoints;
		pointPose.angle = -PI;
		pointsPose.push_back(pointPose);
	}
	for (int i = numberXOfRectangleOutline; i > 0; i--) {
		pointPose.x = i*distanceBetweenPoints;
		pointPose.y = -rectangleOutline.width / 2;
		pointPose.angle = PI / 2;
		pointsPose.push_back(pointPose);
	}
	for (int i = 0; i <= numberXOfRectangleOutline; i++) {
		pointPose.x = -i*distanceBetweenPoints;
		pointPose.y = -rectangleOutline.width / 2;
		pointPose.angle = PI / 2;
		pointsPose.push_back(pointPose);
	}
	for (int i = numberYOfRectangleOutline; i > 0; i--) {
		pointPose.x = -rectangleOutline.length / 2;
		pointPose.y = -i*distanceBetweenPoints;
		pointPose.angle = 0;
		pointsPose.push_back(pointPose);
	}
	for (int i = 0; i <= numberYOfRectangleOutline; i++) {
		pointPose.x = -rectangleOutline.length / 2;
		pointPose.y = i*distanceBetweenPoints;
		pointPose.angle = 0;
		pointsPose.push_back(pointPose);
	}
	for (int i = numberXOfRectangleOutline; i > 0; i--) {
		pointPose.x = -i*distanceBetweenPoints;
		pointPose.y = rectangleOutline.width / 2;
		pointPose.angle = PI / 2;
		pointsPose.push_back(pointPose);
	}

};

void SearchingObjectPositionGeneration::getPointsPose(std::vector<PointPose> &pointsPose) {
	discretizeSerchingOutline();
	pointsPose = this->pointsPose;
};
