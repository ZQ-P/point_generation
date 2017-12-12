#pragma once

#include <stdio.h>
#include <vector>
#include <string.h>
#include "SearchingObjectPositionGeneration.h"
#include <memory>
#include "nav_msgs/OccupancyGrid.h"


enum pointsFunction { grasp, search };

struct PointsInMap {
	std::string name;
	pointsFunction func;
	PointPose furniturePoseInMap;
	std::vector<PointPose> pointPosesAroundFurniture;
	std::vector<PointPose> pointPosesInMap;
};

class MoveStrategy {
private:
	std::vector<PointsInMap> furnitures;
	nav_msgs::OccupancyGrid costmap;
	std::string topicName;
	std::vector<PointPose> pointPoses;
	SearchingObjectPositionGeneration* pointsGenerator;
	void generatePointsAroundFurniture(const std::string &name, const int &typ, const pointsFunction &func, const float &param1, const float &param2);
	void transformPointPosesFromObjectToMap();
	void transformPointPoseFromObjectToMap(PointsInMap &furniture);
	void setFurniturePoseInMap(PointsInMap &furniture);
	void improveCostmap();
	void subscribeTheTopic();
	void comparePointsPosesWithCostmap();
	std::vector<int> getDeleteNumber(PointsInMap &furniture);
	void deletePointsOutsideRoom(PointsInMap &furniture, std::vector<int> &deleteNumbers);
	void createMoveStrategyThroughPoints();

public:
	MoveStrategy();
	~MoveStrategy();
	void generatePointsAroundFurnitures();
	void generatePointPosesToGrasp(std::vector<PointPose> &pointPoses);
	void generatePointPosesToSearch(std::vector<PointPose> &pointPoses);
};
