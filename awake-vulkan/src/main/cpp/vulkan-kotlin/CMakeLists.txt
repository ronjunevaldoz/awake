# vulkan-kotlin/CMakeLists.txt

set(VULKAN_KOTLIN_SOURCES
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
add_library(vulkan_kotlin STATIC ${VULKAN_KOTLIN_SOURCES})

target_include_directories(vulkan_kotlin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
