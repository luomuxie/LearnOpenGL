
#include "normal_mapping.h"
#include "Eff/water_ripple_eff.h"
#include "Deferred.h"
int main() {        

	//point_shadows ps;
	//ps.run();
	//normal_mapping nm;
	//nm.run();
	//water_ripple_eff w;
	//w.run();
	Deferred d;
	d.Run();

	//create a array to store the model' pos
	glm::vec3 objectPositions[] = {
		glm::vec3(-3.0, -3.0, -3.0),
		glm::vec3(0.0, -3.0, -3.0),
		glm::vec3(3.0, -3.0, -3.0),
		glm::vec3(-3.0, -3.0, 0.0),
		glm::vec3(0.0, -3.0, 0.0),
		glm::vec3(3.0, -3.0, 0.0),
		glm::vec3(-3.0, -3.0, 3.0),
		glm::vec3(0.0, -3.0, 3.0),
		glm::vec3(3.0, -3.0, 3.0),
	};
	

	return 0;
}


