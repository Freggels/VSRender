#ifndef RENDER_HPP
#define RENDER_HPP

#include <config.hpp>
#include <render_tools.hpp>
#include <render_font.hpp>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include <array>
#include <map>
#include <chrono>
#include <functional>
#include <math.h>

struct Vertex {
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 texCoord;
	glm::vec3 normal;

	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);
		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);
		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, texCoord);
		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 3;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, normal);
		return attributeDescriptions;
	}
	bool operator==(const Vertex& other) const {
	        return pos == other.pos && color == other.color && texCoord == other.texCoord;
	}
};
struct Scene_UBO {
	alignas(16) glm::mat4 view = glm::mat4(1.0f);
	alignas(16) glm::mat4 proj = glm::mat4(1.0f);
	alignas(16) glm::vec4 light_point = glm::vec4(1.0f);
};

struct Object3D_UBO {
	alignas(16) glm::vec4 position = {0.0f, 0.0f, 0.0f, 1.0f};
	alignas(16) glm::mat4 model = glm::mat4(1.0f);
};

class VRender;

struct Camera3D {
		Scene_UBO subo = {};
		glm::vec3 camera_position = glm::vec3(0.0f, 2.0f, 1.7f);
		glm::vec2 angles = glm::vec2(0.0f, 1.570f);
		glm::vec2 y_area = glm::vec2(1.1344f, 2.7925f);
		int mouse_speed = 10;
		std::function<void(VRender*,Camera3D*)> script_function = nullptr;

		void mouseDtoLocalAngle(glm::vec2 moMove) {
			float cX = 0.0f;
			if (moMove.x < 0.0f) {
				cX = -1.0f * std::fmod(((-moMove.x) / 100) * mouse_speed, 360.0f);
				angles.x += static_cast<float>((cX) * M_PI / 180.0);
			} else {
				cX = std::fmod((moMove.x / 100) * mouse_speed, 360.0f);
				angles.x += static_cast<float>((cX) * M_PI / 180.0);
			}
			float cY = 0.0f;
			if (moMove.y < 0) {
				if (y_area.x > angles.y) {
					angles.y = y_area.x;
				} else {
					cY = -1.0f * std::fmod(((-moMove.y) / 100) * mouse_speed, 360.0f);
					angles.y += static_cast<float>((cY) * M_PI / 180.0);
				}
			} else {
				if (y_area.y < angles.y) {
					angles.y = y_area.y;
				} else {
					cY = std::fmod((moMove.y / 100) * mouse_speed, 360.0f);
					angles.y += static_cast<float>((cY) * M_PI / 180.0);
				}
			}
			if (moMove != glm::vec2(0.0f)) {
				std::cout << "moMove: {" << moMove.x << ":" << moMove.y << "} ";
				std::cout << "; angles (x,y): {" << angles.x << ":"  << angles.y << "} ";
				std::cout << "; currentDegrees (x,y): {" << cX << ":" << cY << "} " << std::endl;
			}
		}

		void execute_script(VRender *render) {
			if (script_function != nullptr) {
				script_function(render, this);
			}
		}
};

struct Object3D {
	std::string name;
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	Object3D_UBO ubo;
	std::function<void(VRender*, Object3D*)> script_function = nullptr;
	int32_t vertex_offset = 0;
	uint32_t first_index = 0;
	std::vector<VkBuffer> ubuf;
	std::vector<VkDeviceMemory> ubufmem;
	std::vector<VkDescriptorSet> descriptorSets;

	void execute_script(VRender *render) {
		if (script_function != nullptr) {
			script_function(render, this);
		}
	}
};

void framebufferResizeCallback(GLFWwindow* window, int width, int height);

void keyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

class VRender {
	public:
		void init();
		void startRender();
		void destroy();
		void framebufferResizedSet(bool new_state);
		void pushObject(Object3D obj3d);
		GLFWwindow *getWindow();
		glm::vec2 getMouseMovement();
		Camera3D main_cam = {};
	private:
		GLFWwindow* window;
		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;
		VkPhysicalDevice phyDevice = VK_NULL_HANDLE;
		VkSurfaceKHR surface;
		VkQueue presentQueue;
		VkQueue graphicsQueue;
		VkDevice device;
		std::vector<VkImage> swapChainImages;
		std::vector<VkImageView> swapChainImageViews;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
		VkSwapchainKHR swapChain;
		VkDescriptorSetLayout descriptorSetLayout;
		VkPipelineLayout pipelineLayout;
		VkRenderPass renderPass;
		VkPipeline graphicsPipeline;
		VkCommandPool commandPool;
		VkImage depthImage;
		VkDeviceMemory depthImageMemory;
		VkImageView depthImageView;
		std::vector<VkFramebuffer> swapChainFramebuffers;
		std::vector<VkCommandBuffer> commandBuffers;
		VkDescriptorPool descriptorPool = VK_NULL_HANDLE;
		std::vector<VkDescriptorSet> descriptorSets;
		VkDeviceMemory indexBufferMemory;
		VkBuffer indexBuffer = VK_NULL_HANDLE;
		VkDeviceMemory vertexBufferMemory;
		VkBuffer vertexBuffer = VK_NULL_HANDLE;
		VkImage textureImage;
		VkDeviceMemory textureImageMemory;
		VkImageView textureImageView;
		VkSampler textureSampler;/*
		std::vector<VkDeviceMemory> uniformBuffersMemory;
		std::vector<VkBuffer> uniformBuffers;*/
		std::vector<VkDeviceMemory> sceneUniformBuffersMemory;
		std::vector<VkBuffer> sceneUniformBuffers;
		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;
		size_t currentFrame = 0;
		const int MAX_FRAMES_IN_FLIGHT = 2;
		bool framebufferResized = false;
		std::vector<Object3D> objects;
		std::map<std::string, uint32_t> objectIDs;
		glm::vec4 light_point = glm::vec4(0.0f, 0.0f, 2.0f, 0.0f);
		glm::vec2 oldMousePos = glm::vec2(0.0f);
		glm::vec2 mouseMovement = glm::vec2(0.0f);
		// Init
		void renderFrame();
		void prepareWindow();
		void createInctance();
		void setupDebugMessenger();
		void createSurface();
		void pickPhysicalDevice();
		void createLogicalDevice();
		void createSwapChain();
		void destroySwapChain();
		void createImageViews();
		void createRenderPass();
		void createDescriptorSetLayout();
		void createGraphicsPipeline();
		void createCommandPool();
		void createDepthResources();
		void createFramebuffers();
		void createTextureResouces();
		void createVertexBuffer();
		void createIndexBuffer();
		void createSceneUniformBuffers();
		void createDescriptorPool();
		void createCommandBuffers();
		void recordCommandBuffers();
		//void createDescriptorSets();
		void createSyncObjects();
		void recreateSwapChain();
		void executeScripts();
		// Tools
		VkCommandBuffer beginSingleTimeCommands();
		void endSingleTimeCommands(VkCommandBuffer commandBuffer);
		void copyBuffer(
			VkBuffer srcBuffer,
			VkBuffer dstBuffer,
			VkDeviceSize size
		);
		void createImage(
			uint32_t width,
			uint32_t height,
			VkFormat format,
			VkImageTiling tiling,
			VkImageUsageFlags usage,
			VkMemoryPropertyFlags properties,
			VkImage &image,
			VkDeviceMemory &imageMemory
		);
		void createBuffer(
			VkDeviceSize size,
			VkBufferUsageFlags usage,
			VkMemoryPropertyFlags properties,
			VkBuffer &buffer,
			VkDeviceMemory &bufferMemory
		);
		void transitionImageLayout(
			VkImage image,
			VkFormat format,
			VkImageLayout oldLayout,
			VkImageLayout newLayout
		);
		void copyBufferToImage(
			VkBuffer buffer,
			VkImage image,
			uint32_t width,
			uint32_t height
		);
		void updateUniformBuffer(uint32_t currentImage);
		void createObjectDescriptorSets(Object3D &obj3d);
		void createObjectUniformBuffers(Object3D &obj3d);
		void recreateDescriptorSets();
		void updateMouse();
};

#endif
