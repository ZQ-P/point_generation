#include "MoveStrategy.h"
#include <math.h>

MoveStrategy::MoveStrategy() {
	pointsGenerator = new SearchingObjectPositionGeneration;
	topicName = "global_map/costmap";
	generatePointsAroundFurnitures();
}

MoveStrategy::~MoveStrategy() {
	delete pointsGenerator;
}

void MoveStrategy::generatePointsAroundFurnitures() {
	pointsFunction func;
	func = grasp;
	generatePointsAroundFurniture("table", 1, func, 0.6, 0.4);

}

void MoveStrategy::generatePointPosesToGrasp(std::vector<PointPose> &pointPoses) {

}

void MoveStrategy::generatePointPosesToSearch(std::vector<PointPose> &pointPoses) {

}


void MoveStrategy::generatePointsAroundFurniture(const std::string &name, const int &typ, const pointsFunction &func, const float &param1, const float &param2) {
	PointsInMap furniture;
	furniture.name = name;
	furniture.func = func;
	if (typ == 1)
		pointsGenerator->setParametersOfRectangle(param1, param2);
	else if (typ == 2)
		pointsGenerator->setParametersOfCircle(param1, param2);
	pointsGenerator->getPointsPose(furniture.pointPosesAroundFurniture);
	furniture.pointPosesInMap.reserve(furniture.pointPosesAroundFurniture.size());
	furnitures.push_back(furniture);
}

void MoveStrategy::transformPointPosesFromObjectToMap() {
	for (auto furniture = furnitures.begin(); furniture != furnitures.end(); furniture++) {
		setFurniturePoseInMap(*furniture);
		transformPointPoseFromObjectToMap(*furniture);
	}

}

void MoveStrategy::transformPointPoseFromObjectToMap(PointsInMap &furniture) {
	for (auto point = furniture.pointPosesAroundFurniture.begin(); point != furniture.pointPosesAroundFurniture.end(); point++) {
		PointPose pointInMap;
		double theta = furniture.furniturePoseInMap.angle;
		pointInMap.x = -furniture.furniturePoseInMap.x + point->x*cos(theta) + point->y*sin(theta);
		pointInMap.y = -furniture.furniturePoseInMap.y + point->y*cos(theta) - point->x*sin(theta);
		pointInMap.angle = point->angle - theta;
		furniture.pointPosesInMap.push_back(pointInMap);
	}
}

void MoveStrategy::setFurniturePoseInMap(PointsInMap &furniture) {
	/*the exact position still need to subscribe from the rostopic*/
	subscribeTheTopic();
	furniture.furniturePoseInMap.x = 1;
	furniture.furniturePoseInMap.y = 1;
	furniture.furniturePoseInMap.angle = 0;
}

void MoveStrategy::improveCostmap() {
	/*use opencv to improve the map*/
}

void MoveStrategy::subscribeTheTopic() {

}

void MoveStrategy::comparePointsPosesWithCostmap() {
	std::vector<int> deleteNumbers;
	for (auto furniture = furnitures.begin(); furniture != furnitures.end(); furniture++) {
		deleteNumbers = getDeleteNumber(*furniture);
		deletePointsOutsideRoom(*furniture, deleteNumbers);
	}
}

std::vector<int> MoveStrategy::getDeleteNumber(PointsInMap &furniture) {
	int amountOfPoints = sizeof(furniture.pointPosesInMap);
	int x, y;
	std::vector<int> deleteNumbers;
	for (int i = 0; i < amountOfPoints; i++) {
		x = furniture.pointPosesInMap[i].x;
		y = furniture.pointPosesInMap[i].y;
		if (costmap[x][y] != 0)
			deleteNumbers.push_back(i);
	}
	return deleteNumbers;
}

void MoveStrategy::deletePointsOutsideRoom(PointsInMap &furniture, std::vector<int> &deleteNumbers) {
	for (auto i = deleteNumbers.size() - 1; i < 0; i--) {
		furniture.pointPosesInMap.erase(furniture.pointPosesInMap.begin() + i);
	}
}

void MoveStrategy::createMoveStrategyThroughPoints() {
	/*optimise mehtod*/
	std::vector<PointPose> allPoints;
	for (auto furniture = furnitures.begin(); furniture != furnitures.end(); furniture++) {
		allPoints.insert(allPoints.end(), furniture->pointPosesInMap.begin(), furniture->pointPosesInMap.end());
	}

}
