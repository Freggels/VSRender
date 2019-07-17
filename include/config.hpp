#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <vulkan/vulkan.h>
#include <string>
#include <vector>


//#define DEBUG
#ifdef DEBUG
	//#define VERBOSE_DEBUG
	#include <iostream>
	const bool enableValidationLayers = true;
#else
	const bool enableValidationLayers = false;
#endif

const std::vector<const char *> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};
const std::vector<const char *> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

const int WIDTH = 800, HEIGHT = 600;
const char APPLICATION_NAME[] = "Vulkan Render";
const std::string SHADER_PATH = "binary/";
#endif
