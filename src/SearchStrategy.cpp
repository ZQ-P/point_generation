#include "searchingObjectPositionGeneration.h"
#include <memory>


int main()
{
	shapeOfObject objectShape = Circle;
	std::unique_ptr<SearchingObjectPositionGeneration> objectOutline(new SearchingObjectPositionGeneration(objectShape, 1, PI));
	std::vector<PointPose> pointsPose;
	objectOutline->getPointsPose(pointsPose);
	system("pause");
	return 0;
};