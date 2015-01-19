#include "Physics.h"
#include "Circle.h"

Physics::Physics(){
	//nothing for now. 
	//will hold physics variables later
}
void Physics::HandleCollisions(){

	set<pair<int, int>> collisionsHandled;
	//put collisions into set if handled
	//to check if not 
	for(int i = 0; i < this->Collidables.size(); i++){
		Shape *me = this->Collidables[i];
		for (int j = 0; j < this->Collidables.size(); j++){
			if (i == j){
				continue;
			}
			//check set to see if these physics have been handled for these objects
			auto a = make_pair(i, j);
			auto b = make_pair(j, i);

			if (collisionsHandled.find(a) != collisionsHandled.end() || collisionsHandled.find(b) != collisionsHandled.end()){
				continue;
			}
			collisionsHandled.insert(a);
			collisionsHandled.insert(b);

			Shape *other = this->Collidables[j];
			if (me->shapeType == Shape::ShapeType::Circle){
				Circle *myCircle = dynamic_cast<Circle *>(me);
				Circle *otherCircle = dynamic_cast<Circle *>(other);
				if (myCircle->Intercepts(otherCircle)){
					Point myPoint = myCircle->GetCenterPoint();
					Point otherPoint = otherCircle->GetCenterPoint();
					vector<double> myV = myPoint.GetVelocity();
					vector<double> otherV = otherPoint.GetVelocity();

					myV[0] *= this->BounceFriction;
					myV[1] *= this->BounceFriction;
					otherV[0] *= this->BounceFriction;
					otherV[1] *= this->BounceFriction;


					myPoint.setVelocity(myV[0], myV[1]);
					otherPoint.setVelocity(otherV[0], otherV[1]);

					myCircle->setCenterPoint(myPoint);
					otherCircle->setCenterPoint(otherPoint);
				}
			}
		}
	}
}
void Physics::ApplyGravity(){
	for each(Shape *shape in Collidables){
		vector<double> myVelocity = shape->shapePoint.GetVelocity();
		myVelocity[1] -= this->Gravity;
		shape->shapePoint.setVelocity(myVelocity[0], myVelocity[1]);
	}
}
void Physics::ApplyAirFriction(){
	for each(Shape *shape in Collidables){
		vector<double> myVelocity = shape->shapePoint.GetVelocity();
		myVelocity[1] *= this->AirFriction;
		myVelocity[0] *= this->AirFriction;
		shape->shapePoint.setVelocity(myVelocity[0], myVelocity[1]);
	}
}
void Physics::UpdateObjects(){
	for each(Shape *shape in this->Collidables){
		shape->Update();
	}
}
void Physics::FindMouseCollisions(int mouseX, int mouseY, double screenX, double screenY){
	mouseX *= 1.0;
	mouseY *= 1.0;
	mouseY = screenY - mouseY;
	Point point = Point(mouseX, mouseY);
	Circle *mouse = new Circle(point, 10.0);
	for each(Shape *shape in this->Collidables){
		Circle *circle = dynamic_cast<Circle *>(shape);
		if (circle->Intercepts(mouse)){
			Point newPoint = circle->GetCenterPoint();
			vector<double> v = newPoint.GetVelocity();
			double x = newPoint.GetX();
			double y = newPoint.GetY();
			if (x > mouseX){
				v[0] += 1.0;
			}
			else{
				v[0] -= 1.0;
			}
			if (y > mouseY){
				v[1] += 1.0;
			}
			else {
				v[1] -= 1.0;
			}
			newPoint.setVelocity(v[0], v[1]);
			circle->setCenterPoint(newPoint);
			this->UpdateObjects();
		}
	}
}