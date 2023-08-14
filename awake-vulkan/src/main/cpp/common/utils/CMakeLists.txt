# common/utils/CMakeLists.txt

set(COMMON_UTILS_VULKAN_UTILS_SOURCES
        VkAttachmentDescriptionAccessor.cpp
        VkDeviceQueueCreateInfoAccessor.cpp
        vulkan_utils.cpp
        VkShaderModuleCreateInfoConverter.cpp
        VkOffset2DAccessor.cpp
        VkPhysicalDeviceFeaturesMutator.cpp
        VkRect2DAccessor.cpp
        VkDeviceCreateInfoAccessor.cpp
        VkSwapchainCreateInfoKHRConverter.cpp
        VkSpecializationMapEntryAccessor.cpp
        VkPipelineColorBlendAttachmentStateAccessor.cpp
        VkImageViewCreateInfoConverter.cpp
        VkSubpassDependencyAccessor.cpp
        VkPipelineColorBlendStateCreateInfoAccessor.cpp
        VkPhysicalDeviceFeaturesAccessor.cpp
        VkPipelineTessellationStateCreateInfoAccessor.cpp
        enum_utils.cpp
        VkSubpassDescriptionAccessor.cpp
        VkPipelineLayoutCreateInfoAccessor.cpp
        VkPipelineInputAssemblyStateCreateInfoAccessor.cpp
        VkGraphicsPipelineCreateInfoAccessor.cpp
        VkPushConstantRangeAccessor.cpp
        VkAttachmentReferenceAccessor.cpp
        VkSpecializationInfoAccessor.cpp
        VkVertexInputAttributeDescriptionAccessor.cpp
        VkPipelineShaderStageCreateInfoAccessor.cpp
        VkPipelineViewportStateCreateInfoAccessor.cpp
        VkPipelineDepthStencilStateCreateInfoAccessor.cpp
        VkPipelineCacheCreateInfoAccessor.cpp
        VkPipelineDynamicStateCreateInfoAccessor.cpp
        VkApplicationInfoAccessor.cpp
        VkVertexInputBindingDescriptionAccessor.cpp
        VkExtent2DAccessor.cpp
        VkPipelineVertexInputStateCreateInfoAccessor.cpp
        VkExtent2DConverter.cpp
        VkViewportAccessor.cpp
        VkPipelineRasterizationStateCreateInfoAccessor.cpp
        VkPipelineMultisampleStateCreateInfoAccessor.cpp
        VkStencilOpStateAccessor.cpp
        VkRenderPassCreateInfoAccessor.cpp
        )

# Set the path to your header file directory
include_directories(includes)
add_library(common_utils_vulkan_utils STATIC ${COMMON_UTILS_VULKAN_UTILS_SOURCES})

target_include_directories(common_utils_vulkan_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
