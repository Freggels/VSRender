#include <render.hpp>
#include <iostream>

Object3D test_object_1 = {
	"cube:0",
	{
		{{ -0.5f, -0.5f,  -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
		{{  0.5f, -0.5f,  -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
		{{  0.5f,  0.5f,  -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
		{{ -0.5f,  0.5f,  -0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
		{{ -0.5f, -0.5f,   0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
		{{  0.5f, -0.5f,   0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
		{{  0.5f,  0.5f,   0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
		{{ -0.5f,  0.5f,   0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}
	},
	{
		0, 1, 2, 2, 3, 0,
		3, 0, 4, 4, 7, 3,
		7, 4, 5, 5, 6, 7,
		6, 5, 1, 1, 2, 6,
		2, 3, 6, 6, 3, 7,
		0, 1, 5, 5, 4, 0
	},
	{
		{0.0f, 0.0f, 0.0f, 1.0f}/*,
		glm::rotate(
			glm::mat4(1.0f),
			glm::radians(30.0f),
			glm::vec3(0.0f, 0.0f, 1.0f)
		)*/
	}
};

Object3D test_object_2 = {
	"cube:1",
	{
		{{ -0.5f, -0.5f,  -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
		{{  0.5f, -0.5f,  -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
		{{  0.5f,  0.5f,  -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
		{{ -0.5f,  0.5f,  -0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
		{{ -0.5f, -0.5f,   0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
		{{  0.5f, -0.5f,   0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
		{{  0.5f,  0.5f,   0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
		{{ -0.5f,  0.5f,   0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}
	},
	{
		0, 1, 2, 2, 3, 0,
		3, 0, 4, 4, 7, 3,
		7, 4, 5, 5, 6, 7,
		6, 5, 1, 1, 2, 6,
		2, 3, 6, 6, 3, 7,
		0, 1, 5, 5, 4, 0
	},
	{
		{0.0f, 0.0f, 1.0f, 1.0f}
	}
};

Object3D test_object_3 = {
	"cube:2",
	{
		{{ -0.5f, -0.5f,  -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}}, // 4
		{{  0.5f, -0.5f,  -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}}, // 3
		{{  0.5f,  0.5f,  -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}}, // 2
		{{ -0.5f,  0.5f,  -0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}}, // 1
		{{ -0.5f, -0.5f,   0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}}, // 1
		{{  0.5f, -0.5f,   0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}}, // 2
		{{  0.5f,  0.5f,   0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}}, // 3
		{{ -0.5f,  0.5f,   0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}}  // 4
	},
	{
		0, 2, 1, 2, 0, 3,
		3, 0, 4, 4, 7, 3,
		7, 4, 5, 5, 6, 7,
		6, 5, 1, 1, 2, 6,
		2, 3, 6, 6, 3, 7,
		0, 1, 5, 5, 4, 0
	},
	{
		{0.0f, 0.0f, 2.0f, 1.0f},
		glm::rotate(
			glm::mat4(1.0f),
			glm::radians(60.0f),
			glm::vec3(0.0f, 0.0f, 1.0f)
		)
	}
};

Object3D plane = {
	"Plane",
	{
		{{ -2.0f, -2.0f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
		{{  2.0f, -2.0f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
		{{  2.0f,  2.0f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
		{{ -2.0f,  2.0f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}
	},
	{
		0, 1, 2, 2, 3, 0
	}
};

int main(void) {
	VRender renderObj;
	test_object_1.script_function = [](VRender *render, Object3D *obj) {
		static auto startTime = std::chrono::high_resolution_clock::now();
		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(
			currentTime - startTime
		).count();
		if (glfwGetKey(render->getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
			obj->ubo.position += glm::vec4(0.0f, 0.01f, 0.0f, 0.0f);
		}
		if (glfwGetKey(render->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
			obj->ubo.position += glm::vec4(0.0f, -0.01f, 0.0f, 0.0f);
		}
		if (glfwGetKey(render->getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
			obj->ubo.position += glm::vec4(-0.01f, 0.0f, 0.0f, 0.0f);
		}
		if (glfwGetKey(render->getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
			obj->ubo.position += glm::vec4(0.01f, 0.0f, 0.0f, 0.0f);
		}
		std::cout << obj->name << " : { " << obj->ubo.position.x << " : " << obj->ubo.position.y << " : " << obj->ubo.position.z << " }" << std::endl;
		//obj->ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	};
	try {
		renderObj.init();
		renderObj.pushObject(plane);
		renderObj.pushObject(test_object_1);
		renderObj.pushObject(test_object_2);
		renderObj.pushObject(test_object_3);
		renderObj.startRender();
		renderObj.destroy();
	} catch (const std::exception& e) {
		std::cerr << "[Error] " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
