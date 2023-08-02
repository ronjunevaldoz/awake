# common/utils/CMakeLists.txt

# Set the source files for the common Vulkan utilities
set(COMMON_UTILS_VULKAN_UTILS_SOURCES
        vulkan_utils.cpp
        enum_utils.cpp
        VkImageViewCreateInfoConverter.cpp
        VkDeviceQueueCreateInfoConverter.cpp
        VkPhysicalDeviceFeaturesConverter.cpp
        VkShaderModuleCreateInfoConverter.cpp
        )

# Create a static library for the common utilities
add_library(common_utils_vulkan_utils STATIC ${COMMON_UTILS_VULKAN_UTILS_SOURCES})

# Add the 'include' directory for the library
target_include_directories(common_utils_vulkan_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
