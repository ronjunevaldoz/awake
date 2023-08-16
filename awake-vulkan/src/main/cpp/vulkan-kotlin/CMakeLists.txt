# vulkan-kotlin/CMakeLists.txt

set(VULKAN_KOTLIN_SOURCES
        VkAttachmentDescriptionAccessor.cpp
        VkExtent2DMutator.cpp
        VkDeviceQueueCreateInfoAccessor.cpp
        vulkan_utils.cpp
        VkPhysicalDeviceSparsePropertiesMutator.cpp
        VkOffset2DAccessor.cpp
        VkPhysicalDeviceFeaturesMutator.cpp
        VkImageSubresourceRangeAccessor.cpp
        VkPhysicalDevicePropertiesAccessor.cpp
        VkRect2DAccessor.cpp
        VkDeviceCreateInfoAccessor.cpp
        VkPhysicalDeviceSparsePropertiesAccessor.cpp
        VkDebugUtilsMessengerCallbackDataEXTMutator.cpp
        VkSpecializationMapEntryAccessor.cpp
        VkPipelineColorBlendAttachmentStateAccessor.cpp
        VkDebugUtilsObjectNameInfoEXTAccessor.cpp
        VkDebugUtilsLabelEXTAccessor.cpp
        VkSubpassDependencyAccessor.cpp
        VkPipelineColorBlendStateCreateInfoAccessor.cpp
        VkPhysicalDeviceFeaturesAccessor.cpp
        VkPipelineTessellationStateCreateInfoAccessor.cpp
        VkDebugUtilsMessengerCallbackDataEXTAccessor.cpp
        enum_utils.cpp
        VkSubpassDescriptionAccessor.cpp
        VkPhysicalDeviceLimitsAccessor.cpp
        VkDebugUtilsMessengerCreateInfoEXTAccessor.cpp
        VkPhysicalDeviceLimitsMutator.cpp
        VkPipelineLayoutCreateInfoAccessor.cpp
        VkShaderModuleCreateInfoAccessor.cpp
        VkPipelineInputAssemblyStateCreateInfoAccessor.cpp
        VkSwapchainCreateInfoKHRAccessor.cpp
        VkGraphicsPipelineCreateInfoAccessor.cpp
        VkComponentMappingAccessor.cpp
        VkPushConstantRangeAccessor.cpp
        VkAttachmentReferenceAccessor.cpp
        VkSpecializationInfoAccessor.cpp
        VkVertexInputAttributeDescriptionAccessor.cpp
        VkPipelineShaderStageCreateInfoAccessor.cpp
        VkPipelineViewportStateCreateInfoAccessor.cpp
        VkPipelineDepthStencilStateCreateInfoAccessor.cpp
        VkExtent3DMutator.cpp
        VkPipelineCacheCreateInfoAccessor.cpp
        VkPipelineDynamicStateCreateInfoAccessor.cpp
        VkApplicationInfoAccessor.cpp
        VkVertexInputBindingDescriptionAccessor.cpp
        VkExtent2DAccessor.cpp
        VkPipelineVertexInputStateCreateInfoAccessor.cpp
        VkQueueFamilyPropertiesAccessor.cpp
        VkSurfaceCapabilitiesKHRAccessor.cpp
        VkSurfaceCapabilitiesKHRMutator.cpp
        VkQueueFamilyPropertiesMutator.cpp
        VkViewportAccessor.cpp
        VkExtent3DAccessor.cpp
        VkPipelineRasterizationStateCreateInfoAccessor.cpp
        VkPipelineMultisampleStateCreateInfoAccessor.cpp
        VkStencilOpStateAccessor.cpp
        VkRenderPassCreateInfoAccessor.cpp
        VkPhysicalDevicePropertiesMutator.cpp
        VkImageViewCreateInfoAccessor.cpp
        )

# Set the path to your header file directory
include_directories(includes)
add_library(vulkan_kotlin STATIC ${VULKAN_KOTLIN_SOURCES})

target_include_directories(vulkan_kotlin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
