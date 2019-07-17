#ifndef RENDER_TOOLS_HPP
#define RENDER_TOOLS_HPP

#include <config.hpp>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <set>
std::vector<const char*> getExtensions();
bool checkValidationLayerSupport();

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;
	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void *pUserData
);

VkResult CreateDebugUtilsMessengerEXT(
	VkInstance instance,
	const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
	const VkAllocationCallbacks *pAllocator,
	VkDebugUtilsMessengerEXT *pDebugMessenger
);

void DestroyDebugUtilsMessengerEXT (
	VkInstance instance,
	VkDebugUtilsMessengerEXT debugMessenger,
	const VkAllocationCallbacks *pAllocator
);

void populateDebugMessengerCreateInfo(
	VkDebugUtilsMessengerCreateInfoEXT &createInfo
);

bool checkDeviceExtensionSupport(VkPhysicalDevice device);

bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR &surface);

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR &surface);

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR &surface);

VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

VkShaderModule createShaderModule(
	VkDevice device,
	const std::string filename
);

std::vector<char> readFile(const std::string &filename);

VkFormat findDepthFormat(VkPhysicalDevice &phyDevice);

VkFormat findSupportedFormat(
	VkPhysicalDevice &phyDevice,
	const std::vector<VkFormat> &candidates,
	VkImageTiling tiling,
	VkFormatFeatureFlags features
);

void transitionImageLayout(
	VkImage image,
	VkFormat format,
	VkImageLayout oldLayout,
	VkImageLayout newLayout
);

bool hasStencilComponent(VkFormat format);

uint32_t findMemoryType(
	VkPhysicalDevice &phyDevice,
	uint32_t typeFilter,
	VkMemoryPropertyFlags properties
);

VkImageView createImageView(
	VkDevice &device,
	VkImage image,
	VkFormat format,
	VkImageAspectFlags aspectFlags
);

#endif
