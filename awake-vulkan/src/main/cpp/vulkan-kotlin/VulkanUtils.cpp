/*
 *  VulkanUtils.cpp
 *  Vulkan utils for Vulkan
 *  Created by Ron June Valdoz */

#include <includes/VulkanUtils.h>

namespace awake {
jobjectArray
getPhysicalDeviceQueueFamilyProperties(JNIEnv *env, jlong arg0) {
    auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(arg0);
    uint32_t count;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, nullptr);
    std::vector<VkQueueFamilyProperties> vkArray(count);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, vkArray.data());
    jclass clazz = env->FindClass(
            "io/github/ronjunevaldoz/awake/vulkan/models/VkQueueFamilyProperties");
    auto jArray = env->NewObjectArray(static_cast<jsize>(count), clazz, nullptr);
    for (int i = 0; i < count; ++i) {
        jobject obj = VkQueueFamilyPropertiesMutator(env).toObject(vkArray[i]);
        env->SetObjectArrayElement(jArray, (jint) i, obj);
        env->DeleteLocalRef(obj);
    }
    return jArray;
}

    void
    destroyFramebuffer(jlong arg0, jlong arg1) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        auto framebuffer = reinterpret_cast<VkFramebuffer>(arg1);
        vkDestroyFramebuffer(device, framebuffer, nullptr);
        // void
    }

    void
    destroySurfaceKHR(jlong arg0, jlong arg1) {
        auto instance = reinterpret_cast<VkInstance>(arg0);
        auto surfaceKHR = reinterpret_cast<VkSurfaceKHR>(arg1);
        vkDestroySurfaceKHR(instance, surfaceKHR, nullptr);
        // void
    }

    jlongArray
    createGraphicsPipelines(JNIEnv *env, jlong arg0, jlong arg1, jobjectArray arg2) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        auto pipelineCache = reinterpret_cast<VkPipelineCache>(arg1);
        // process array
        auto size = env->GetArrayLength(arg2);
        std::vector<VkGraphicsPipelineCreateInfo> vkArray;
        for (int i = 0; i < size; ++i) {
            VkGraphicsPipelineCreateInfo info{};
            auto element = (jobject) env->GetObjectArrayElement(arg2, i);
            VkGraphicsPipelineCreateInfoAccessor(env, element).fromObject(info);
            vkArray.push_back(info);
            env->DeleteLocalRef(element);
        }
        // handle
        std::vector<VkPipeline> handle(size);
        VkResult result = vkCreateGraphicsPipelines(device, pipelineCache,
                                                    static_cast<uint32_t>(vkArray.size()),
                                                    vkArray.data(), nullptr, handle.data());
        if (result != VK_SUCCESS) {
            throw std::runtime_error("There was a problem executing vkCreateGraphicsPipelines");
        }
        auto jArray = env->NewLongArray(static_cast<jsize>(vkArray.size()));
        for (int i = 0; i < size; ++i) {
            auto value = reinterpret_cast<jlong>(handle[i]);
            env->SetLongArrayRegion(jArray, i, 1, &value);
        }
        return jArray;
    }

    jlong
    createDebugUtilsMessengerEXT(JNIEnv *env, jlong arg0, jobject arg1) {
        auto instance = reinterpret_cast<VkInstance>(arg0);
        // object accessor?
        VkDebugUtilsMessengerCreateInfoEXT info{};
        // process singleton
        VkDebugUtilsMessengerCreateInfoEXTAccessor::init(env, arg1);
        VkDebugUtilsMessengerCreateInfoEXTAccessor::getInstance().fromObject(info);
        // handle
        VkDebugUtilsMessengerEXT handle;
        auto pfnvkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(
                instance, "vkCreateDebugUtilsMessengerEXT");
        VkResult result = pfnvkCreateDebugUtilsMessengerEXT(instance, &info, nullptr, &handle);
        if (result != VK_SUCCESS) {
            throw std::runtime_error(
                    "There was a problem executing vkCreateDebugUtilsMessengerEXT");
        }
        return reinterpret_cast<jlong>(handle);
    }

    void
    cmdEndRenderPass(JNIEnv *env, jlong arg0) {
        auto commandBuffer = reinterpret_cast<VkCommandBuffer>(arg0);
        vkCmdEndRenderPass(commandBuffer);
        // void
    }

    void
    cmdBeginRenderPass(JNIEnv *env, jlong arg0, jobject arg1, jobject arg2) {
        auto commandBuffer = reinterpret_cast<VkCommandBuffer>(arg0);
        // object accessor?
        VkRenderPassBeginInfo info{};
        VkRenderPassBeginInfoAccessor(env, arg1).fromObject(info);
        // enum
        auto vkarg2 = enum_utils::getEnumFromObject(env, arg2);
        vkCmdBeginRenderPass(commandBuffer, &info, static_cast<VkSubpassContents>(vkarg2));
        // void
    }

    jlongArray
    getSwapchainImagesKHR(JNIEnv *env, jlong arg0, jlong arg1) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        auto swapchainKHR = reinterpret_cast<VkSwapchainKHR>(arg1);
        uint32_t count;
        vkGetSwapchainImagesKHR(device, swapchainKHR, &count, nullptr);
        std::vector<VkImage> vkArray(count);
        vkGetSwapchainImagesKHR(device, swapchainKHR, &count, vkArray.data());
        auto jArray = env->NewLongArray(static_cast<jsize>(count));
        for (int i = 0; i < count; ++i) {
            auto value = reinterpret_cast<jlong>(vkArray[i]);
            env->SetLongArrayRegion(jArray, i, 1, &value);
        }
        return jArray;
    }

    void
    destroyShaderModule(jlong arg0, jlong arg1) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        auto shaderModule = reinterpret_cast<VkShaderModule>(arg1);
        vkDestroyShaderModule(device, shaderModule, nullptr);
        // void
    }

    jlong
    createPipelineLayout(JNIEnv *env, jlong arg0, jobject arg1) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        // object accessor?
        VkPipelineLayoutCreateInfo info{};
        VkPipelineLayoutCreateInfoAccessor(env, arg1).fromObject(info);
        // handle
        VkPipelineLayout handle;
        VkResult result = vkCreatePipelineLayout(device, &info, nullptr, &handle);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("There was a problem executing vkCreatePipelineLayout");
        }
        return reinterpret_cast<jlong>(handle);
    }

    jlong
    allocateCommandBuffers(JNIEnv *env, jlong arg0, jobject arg1) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        // object accessor?
        VkCommandBufferAllocateInfo info{};
        VkCommandBufferAllocateInfoAccessor(env, arg1).fromObject(info);
        VkCommandBuffer handle;
        vkAllocateCommandBuffers(device, &info, &handle);
        return reinterpret_cast<jlong>(handle);
    }

    jlong
    getDeviceQueue(JNIEnv *env, jlong arg0, jint arg1, jint arg2) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        // default??
        uint32_t vkarg1 = arg1;
        // default??
        uint32_t vkarg2 = arg2;
        VkQueue handle;
        vkGetDeviceQueue(device, vkarg1, vkarg2, &handle);
        return reinterpret_cast<jlong>(handle);
    }

    jlong
    createAndroidSurfaceKHR(JNIEnv *env, jlong arg0, jobject arg1) {
        auto instance = reinterpret_cast<VkInstance>(arg0);
        // object accessor?
        VkAndroidSurfaceCreateInfoKHR info{};
        VkAndroidSurfaceCreateInfoKHRAccessor(env, arg1).fromObject(info);
        // handle
        VkSurfaceKHR handle;
        VkResult result = vkCreateAndroidSurfaceKHR(instance, &info, nullptr, &handle);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("There was a problem executing vkCreateAndroidSurfaceKHR");
        }
        return reinterpret_cast<jlong>(handle);
    }

    jobject
    getPhysicalDeviceSurfaceCapabilitiesKHR(JNIEnv *env, jlong arg0, jlong arg1) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(arg0);
        auto surfaceKHR = reinterpret_cast<VkSurfaceKHR>(arg1);
        VkSurfaceCapabilitiesKHR handle;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surfaceKHR, &handle);
        return VkSurfaceCapabilitiesKHRMutator(env).toObject(handle);
    }

    jobjectArray
    enumerateInstanceLayerProperties(JNIEnv *env) {
        uint32_t count;
        vkEnumerateInstanceLayerProperties(&count, nullptr);
        std::vector<VkLayerProperties> vkArray(count);
        vkEnumerateInstanceLayerProperties(&count, vkArray.data());
        jclass clazz = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/models/VkLayerProperties");
        auto jArray = env->NewObjectArray(static_cast<jsize>(count), clazz, nullptr);
        for (int i = 0; i < count; ++i) {
            jobject obj = VkLayerPropertiesMutator(env).toObject(vkArray[i]);
            env->SetObjectArrayElement(jArray, (jint) i, obj);
            env->DeleteLocalRef(obj);
        }
        return jArray;
    }

    jlong
    createInstance(JNIEnv *env, jobject arg0) {
        // object accessor?
        VkInstanceCreateInfo info{};
        VkInstanceCreateInfoAccessor(env, arg0).fromObject(info);
        // handle
        VkInstance handle;
        VkResult result = vkCreateInstance(&info, nullptr, &handle);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("There was a problem executing vkCreateInstance");
        }
        return reinterpret_cast<jlong>(handle);
    }

    jobject
    getPhysicalDeviceProperties(JNIEnv *env, jlong arg0) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(arg0);
        VkPhysicalDeviceProperties handle;
        vkGetPhysicalDeviceProperties(physicalDevice, &handle);
        return VkPhysicalDevicePropertiesMutator(env).toObject(handle);
    }

    void
    destroyPipelineCache(jlong arg0, jlong arg1) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        auto pipelineCache = reinterpret_cast<VkPipelineCache>(arg1);
        vkDestroyPipelineCache(device, pipelineCache, nullptr);
        // void
    }

    void
    cmdBindPipeline(JNIEnv *env, jlong arg0, jobject arg1, jlong arg2) {
        auto commandBuffer = reinterpret_cast<VkCommandBuffer>(arg0);
        // enum
        auto vkarg1 = enum_utils::getEnumFromObject(env, arg1);
        auto pipeline = reinterpret_cast<VkPipeline>(arg2);
        vkCmdBindPipeline(commandBuffer, static_cast<VkPipelineBindPoint>(vkarg1), pipeline);
        // void
    }

    void
    cmdSetScissor(JNIEnv *env, jlong arg0, jint arg1, jobjectArray arg2) {
        auto commandBuffer = reinterpret_cast<VkCommandBuffer>(arg0);
        // default??
        uint32_t vkarg1 = arg1;
        // process array
        auto size = env->GetArrayLength(arg2);
        std::vector<VkRect2D> vkArray;
        for (int i = 0; i < size; ++i) {
            VkRect2D info{};
            auto element = (jobject) env->GetObjectArrayElement(arg2, i);
            VkRect2DAccessor(env, element).fromObject(info);
            vkArray.push_back(info);
            env->DeleteLocalRef(element);
        }
        vkCmdSetScissor(commandBuffer, vkarg1, static_cast<uint32_t>(vkArray.size()),
                        vkArray.data());
        // void
    }

    jobjectArray
    enumerateDeviceExtensionProperties(JNIEnv *env, jlong arg0, jstring arg1) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(arg0);
        const char *vkarg1 = nullptr;
        if (arg1 != nullptr) {
            vkarg1 = env->GetStringUTFChars(arg1, nullptr);
            env->ReleaseStringUTFChars(arg1, vkarg1);
        }
        uint32_t count;
        vkEnumerateDeviceExtensionProperties(physicalDevice, vkarg1, &count, nullptr);
        std::vector<VkExtensionProperties> vkArray(count);
        vkEnumerateDeviceExtensionProperties(physicalDevice, vkarg1, &count, vkArray.data());
        jclass clazz = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/models/VkExtensionProperties");
        auto jArray = env->NewObjectArray(static_cast<jsize>(count), clazz, nullptr);
        for (int i = 0; i < count; ++i) {
            jobject obj = VkExtensionPropertiesMutator(env).toObject(vkArray[i]);
            env->SetObjectArrayElement(jArray, (jint) i, obj);
            env->DeleteLocalRef(obj);
        }
        return jArray;
    }

    void
    destroyPipelineLayout(jlong arg0, jlong arg1) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        auto pipelineLayout = reinterpret_cast<VkPipelineLayout>(arg1);
        vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
        // void
    }

    void
    beginCommandBuffer(JNIEnv *env, jlong arg0, jobject arg1) {
        auto commandBuffer = reinterpret_cast<VkCommandBuffer>(arg0);
        // object accessor?
        VkCommandBufferBeginInfo info{};
        VkCommandBufferBeginInfoAccessor(env, arg1).fromObject(info);
        vkBeginCommandBuffer(commandBuffer, &info);
        // void
    }

    jobject
    getPhysicalDeviceFeatures(JNIEnv *env, jlong arg0) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(arg0);
        VkPhysicalDeviceFeatures handle;
        vkGetPhysicalDeviceFeatures(physicalDevice, &handle);
        return VkPhysicalDeviceFeaturesMutator(env).toObject(handle);
    }

    void
    destroyRenderPass(jlong arg0, jlong arg1) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        auto renderPass = reinterpret_cast<VkRenderPass>(arg1);
        vkDestroyRenderPass(device, renderPass, nullptr);
        // void
    }

    void
    destroyImageView(jlong arg0, jlong arg1) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        auto imageView = reinterpret_cast<VkImageView>(arg1);
        vkDestroyImageView(device, imageView, nullptr);
        // void
    }

    jlong
    createFramebuffer(JNIEnv *env, jlong arg0, jobject arg1) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        // object accessor?
        VkFramebufferCreateInfo info{};
        VkFramebufferCreateInfoAccessor(env, arg1).fromObject(info);
        // handle
        VkFramebuffer handle;
        VkResult result = vkCreateFramebuffer(device, &info, nullptr, &handle);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("There was a problem executing vkCreateFramebuffer");
        }
        return reinterpret_cast<jlong>(handle);
    }

    jlong
    createRenderPass(JNIEnv *env, jlong arg0, jobject arg1) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        // object accessor?
        VkRenderPassCreateInfo info{};
        VkRenderPassCreateInfoAccessor(env, arg1).fromObject(info);
        // handle
        VkRenderPass handle;
        VkResult result = vkCreateRenderPass(device, &info, nullptr, &handle);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("There was a problem executing vkCreateRenderPass");
        }
        return reinterpret_cast<jlong>(handle);
    }

    jlongArray
    enumeratePhysicalDevices(JNIEnv *env, jlong arg0) {
        auto instance = reinterpret_cast<VkInstance>(arg0);
        uint32_t count;
        vkEnumeratePhysicalDevices(instance, &count, nullptr);
        std::vector<VkPhysicalDevice> vkArray(count);
        vkEnumeratePhysicalDevices(instance, &count, vkArray.data());
        auto jArray = env->NewLongArray(static_cast<jsize>(count));
        for (int i = 0; i < count; ++i) {
            auto value = reinterpret_cast<jlong>(vkArray[i]);
            env->SetLongArrayRegion(jArray, i, 1, &value);
        }
        return jArray;
    }

    jlong
    createShaderModule(JNIEnv *env, jlong arg0, jobject arg1) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        // object accessor?
        VkShaderModuleCreateInfo info{};
        VkShaderModuleCreateInfoAccessor(env, arg1).fromObject(info);
        // handle
        VkShaderModule handle;
        VkResult result = vkCreateShaderModule(device, &info, nullptr, &handle);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("There was a problem executing vkCreateShaderModule");
        }
        return reinterpret_cast<jlong>(handle);
    }

    jboolean
    getPhysicalDeviceSurfaceSupportKHR(JNIEnv *env, jlong arg0, jint arg1, jlong arg2) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(arg0);
        // default??
        uint32_t vkarg1 = arg1;
        auto surfaceKHR = reinterpret_cast<VkSurfaceKHR>(arg2);
        VkBool32 handle;
        vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, vkarg1, surfaceKHR, &handle);
        return handle;
    }

    jlong
    createDevice(JNIEnv *env, jlong arg0, jobject arg1) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(arg0);
        // object accessor?
        VkDeviceCreateInfo info{};
        VkDeviceCreateInfoAccessor(env, arg1).fromObject(info);
        // handle
        VkDevice handle;
        VkResult result = vkCreateDevice(physicalDevice, &info, nullptr, &handle);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("There was a problem executing vkCreateDevice");
        }
        return reinterpret_cast<jlong>(handle);
    }

    jlong
    createPipelineCache(JNIEnv *env, jlong arg0, jobject arg1) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        // object accessor?
        VkPipelineCacheCreateInfo info{};
        VkPipelineCacheCreateInfoAccessor(env, arg1).fromObject(info);
        // handle
        VkPipelineCache handle;
        VkResult result = vkCreatePipelineCache(device, &info, nullptr, &handle);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("There was a problem executing vkCreatePipelineCache");
        }
        return reinterpret_cast<jlong>(handle);
    }

    void
    destroySwapchainKHR(jlong arg0, jlong arg1) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        auto swapchainKHR = reinterpret_cast<VkSwapchainKHR>(arg1);
        vkDestroySwapchainKHR(device, swapchainKHR, nullptr);
        // void
    }

    jobjectArray
    getPhysicalDeviceSurfacePresentModesKHR(JNIEnv *env, jlong arg0, jlong arg1) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(arg0);
        auto surfaceKHR = reinterpret_cast<VkSurfaceKHR>(arg1);
        uint32_t count;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surfaceKHR, &count, nullptr);
        std::vector<VkPresentModeKHR> vkArray(count);
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surfaceKHR, &count,
                                                  vkArray.data());
        jclass clazz = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/enums/VkPresentModeKHR");
        auto jArray = env->NewObjectArray(static_cast<jsize>(count), clazz, nullptr);
        for (int i = 0; i < count; ++i) {
            jobject obj = enum_utils::setEnumFromVulkan(env, vkArray[i],
                                                        "io/github/ronjunevaldoz/awake/vulkan/enums/VkPresentModeKHR");
            env->SetObjectArrayElement(jArray, (jint) i, obj);
            env->DeleteLocalRef(obj);
        }
        return jArray;
    }

    jobjectArray
    enumerateInstanceExtensionProperties(JNIEnv *env, jstring arg0) {
        const char *vkarg0 = nullptr;
        if (arg0 != nullptr) {
            vkarg0 = env->GetStringUTFChars(arg0, nullptr);
            env->ReleaseStringUTFChars(arg0, vkarg0);
        }
        uint32_t count;
        vkEnumerateInstanceExtensionProperties(vkarg0, &count, nullptr);
        std::vector<VkExtensionProperties> vkArray(count);
        vkEnumerateInstanceExtensionProperties(vkarg0, &count, vkArray.data());
        jclass clazz = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/models/VkExtensionProperties");
        auto jArray = env->NewObjectArray(static_cast<jsize>(count), clazz, nullptr);
        for (int i = 0; i < count; ++i) {
            jobject obj = VkExtensionPropertiesMutator(env).toObject(vkArray[i]);
            env->SetObjectArrayElement(jArray, (jint) i, obj);
            env->DeleteLocalRef(obj);
        }
        return jArray;
    }

    void
    destroyCommandPool(jlong arg0, jlong arg1) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        auto commandPool = reinterpret_cast<VkCommandPool>(arg1);
        vkDestroyCommandPool(device, commandPool, nullptr);
        // void
    }

    void
    cmdDraw(JNIEnv *env, jlong arg0, jint arg1, jint arg2, jint arg3, jint arg4) {
        auto commandBuffer = reinterpret_cast<VkCommandBuffer>(arg0);
        // default??
        uint32_t vkarg1 = arg1;
        // default??
        uint32_t vkarg2 = arg2;
        // default??
        uint32_t vkarg3 = arg3;
        // default??
        uint32_t vkarg4 = arg4;
        vkCmdDraw(commandBuffer, vkarg1, vkarg2, vkarg3, vkarg4);
        // void
    }

    void
    destroyPipeline(jlong arg0, jlong arg1) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        auto pipeline = reinterpret_cast<VkPipeline>(arg1);
        vkDestroyPipeline(device, pipeline, nullptr);
        // void
    }

    jlong
    createSwapchainKHR(JNIEnv *env, jlong arg0, jobject arg1) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        // object accessor?
        VkSwapchainCreateInfoKHR info{};
        VkSwapchainCreateInfoKHRAccessor(env, arg1).fromObject(info);
        // handle
        VkSwapchainKHR handle;
        VkResult result = vkCreateSwapchainKHR(device, &info, nullptr, &handle);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("There was a problem executing vkCreateSwapchainKHR");
        }
        return reinterpret_cast<jlong>(handle);
    }

    void
    endCommandBuffer(JNIEnv *env, jlong arg0) {
        auto commandBuffer = reinterpret_cast<VkCommandBuffer>(arg0);
        vkEndCommandBuffer(commandBuffer);
        // void
    }

    void
    destroyDebugUtilsMessengerEXT(jlong arg0, jlong arg1) {
        auto instance = reinterpret_cast<VkInstance>(arg0);
        auto debugUtilsMessengerEXT = reinterpret_cast<VkDebugUtilsMessengerEXT>(arg1);
        auto pfnvkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(
                instance, "vkDestroyDebugUtilsMessengerEXT");
        pfnvkDestroyDebugUtilsMessengerEXT(instance, debugUtilsMessengerEXT, nullptr);
        // void
    }

    void
    destroyDevice(jlong arg0) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        vkDestroyDevice(device, nullptr);
        // void
    }

    void
    cmdSetViewport(JNIEnv *env, jlong arg0, jint arg1, jobjectArray arg2) {
        auto commandBuffer = reinterpret_cast<VkCommandBuffer>(arg0);
        // default??
        uint32_t vkarg1 = arg1;
        // process array
        auto size = env->GetArrayLength(arg2);
        std::vector<VkViewport> vkArray;
        for (int i = 0; i < size; ++i) {
            VkViewport info{};
            auto element = (jobject) env->GetObjectArrayElement(arg2, i);
            VkViewportAccessor(env, element).fromObject(info);
            vkArray.push_back(info);
            env->DeleteLocalRef(element);
        }
        vkCmdSetViewport(commandBuffer, vkarg1, static_cast<uint32_t>(vkArray.size()),
                         vkArray.data());
        // void
    }

    void
    destroyInstance(jlong arg0) {
        auto instance = reinterpret_cast<VkInstance>(arg0);
        vkDestroyInstance(instance, nullptr);
        // void
    }

    jlong
    createImageView(JNIEnv *env, jlong arg0, jobject arg1) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        // object accessor?
        VkImageViewCreateInfo info{};
        VkImageViewCreateInfoAccessor(env, arg1).fromObject(info);
        // handle
        VkImageView handle;
        VkResult result = vkCreateImageView(device, &info, nullptr, &handle);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("There was a problem executing vkCreateImageView");
        }
        return reinterpret_cast<jlong>(handle);
    }

    jlong
    createCommandPool(JNIEnv *env, jlong arg0, jobject arg1) {
        auto device = reinterpret_cast<VkDevice>(arg0);
        // object accessor?
        VkCommandPoolCreateInfo info{};
        VkCommandPoolCreateInfoAccessor(env, arg1).fromObject(info);
        // handle
        VkCommandPool handle;
        VkResult result = vkCreateCommandPool(device, &info, nullptr, &handle);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("There was a problem executing vkCreateCommandPool");
        }
        return reinterpret_cast<jlong>(handle);
    }

    jobjectArray
    getPhysicalDeviceSurfaceFormatsKHR(JNIEnv *env, jlong arg0, jlong arg1) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(arg0);
        auto surfaceKHR = reinterpret_cast<VkSurfaceKHR>(arg1);
        uint32_t count;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surfaceKHR, &count, nullptr);
        std::vector<VkSurfaceFormatKHR> vkArray(count);
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surfaceKHR, &count, vkArray.data());
        jclass clazz = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/models/VkSurfaceFormatKHR");
        auto jArray = env->NewObjectArray(static_cast<jsize>(count), clazz, nullptr);
        for (int i = 0; i < count; ++i) {
            jobject obj = VkSurfaceFormatKHRMutator(env).toObject(vkArray[i]);
            env->SetObjectArrayElement(jArray, (jint) i, obj);
            env->DeleteLocalRef(obj);
        }
        return jArray;
    }

}
