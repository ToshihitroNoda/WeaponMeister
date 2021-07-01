#ifndef CREATERUN_H_
#define CREATERUN_H_

#include "ProductionSectionBase.h"

class CreateRun : public ProductionSectionBase
{
public:
	CreateRun()  = default;
	~CreateRun() = default;

	void Update() override;
	void Draw() override;

	bool MakeEnd = false;
private:
	const int defaultDrawCount_ = 300;
	const int defaultAngle_ = 359;
	const int animationSoundTime_ = 30;
	const int MakeOptionMenuX_ = 1100;
	const int OptionMenuY_ = 705;

	int distToCenter_ = defaultDrawCount_;
	int angle_ = 0;
	int drawCounter_ = defaultDrawCount_;
	int scrollCount_ = 0;
	int animationSoundTimer_ = 0;
	int operationDescriptionMessageNum_ = 0;
	int productAnimationSpeed_ = 1;

	bool playProductionEndSound_ = false;
	bool animationEnd_ = false;

	std::vector<int> animationX_;
	std::vector<int> animationY_;
	std::vector<int> drawItemID_;
};

#endif