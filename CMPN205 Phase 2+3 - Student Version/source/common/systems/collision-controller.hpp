#pragma once

#include "../ecs/world.hpp"
#include "../ecs/entity.hpp"
#include "../components/camera.hpp"
#include "../components/collider.hpp"

#include "../application.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <vector>
#include<iostream>
using namespace std;

namespace our
{

	// The free camera controller system is responsible for moving every entity which contains a FreeCameraControllerComponent.
	// This system is added as a slightly complex example for how use the ECS framework to implement logic.
	// For more information, see "common/components/free-camera-controller.hpp"
	class CollisionSystem
	{
		Application* app; // The application in which the state runs

	public:
		// When a state enters, it should call this function and give it the pointer to the application
		void enter(Application* app)
		{
			this->app = app;
		}

		void update(World* world, float deltaTime)
		{
			vector<Collider*> colliders;

			for (auto entity : world->getEntities())
			{
				if (auto collider = entity->getComponent<Collider>(); collider) {
					colliders.push_back(collider);
				}
			}
			for (auto collider1 : colliders)
			{
				for (auto collider2 : colliders)
				{
					if (collider1 != collider2)
					{
						string collider1Name = collider1->getOwner()->name;
						string collider2Name = collider2->getOwner()->name;

						auto center1 = collider1->getOwner()->getLocalToWorldMatrix() * glm::vec4(0, 0, 0, 1);
						auto center2 = collider2->getOwner()->getLocalToWorldMatrix() * glm::vec4(0, 0, 0, 1);

						auto distance = glm::distance(center1, center2);

						if (distance <= collider1->radius + collider2->radius) 
						{
							if ((collider1Name == "revolver" && collider2Name == "bug") || (collider2Name == "revolver" && collider1Name == "bug") ) {
								app->changeState("lose");
								return;
							}
							
							if ( (collider2Name == "fireball" && collider1Name == "bug") || (collider2Name == "bug" && collider1Name == "fireball") )
							{
								world->fireballsCount--;
								world->markForRemoval(collider1->getOwner());
								world->markForRemoval(collider2->getOwner());
							}

							if (collider1Name == "fireball" && collider2Name == "lamp")
							{
								world->fireballsCount--;
								world->markForRemoval(collider1->getOwner());
								cout << "Hit lamp" << endl;
							}
							else if (collider2Name == "fireball" && collider1Name == "lamp")
							{
								cout << "Hit lamp" << endl;

								world->fireballsCount--;
								world->markForRemoval(collider2->getOwner());
							}
						}
					}
				}
			}

		}
	};
}