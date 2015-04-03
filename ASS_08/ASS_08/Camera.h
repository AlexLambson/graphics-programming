#pragma once
#include "Helpers.h"

class Camera{
public:
	Camera(double x, double y, double z);
	WorldPosition GetPosition();
	WorldPosition GetLookAt();
	void setPosition(WorldPosition position);
	void setLookAt(WorldPosition lookAt);
	void setRotation();
	double GetDX();
	double GetDY();
	double GetRotation();
	void HandleKey(Key::Type key);
	void Move(bool reverse = false);
	void LookAt();
	void ChangeSpeed(double speed);
	double getHeight(bool lookAt = false);
private:
	WorldPosition mPosition;
	WorldPosition mLookAt;
	double mRotation;
	double mSpeed;
	double mRotationSpeed;
	double minSpeed;
	double maxSpeed;
};