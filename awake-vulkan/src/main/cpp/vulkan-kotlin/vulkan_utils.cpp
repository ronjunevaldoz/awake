//
// Created by Ron June Valdoz on 7/23/23.
//

#include <algorithm>
#include <vector>
#include <android/log.h>
#include <string>
#include <android/native_window_jni.h>
#include "vulkan_utils.h"
#include "enum_utils.h"
#include "includes/VkPhysicalDeviceFeaturesMutator.h"
#include "includes/VkGraphicsPipelineCreateInfoAccessor.h"
#include "includes/VkPipelineCacheCreateInfoAccessor.h"
#include "includes/VkApplicationInfoAccessor.h"
#include "includes/VkDeviceCreateInfoAccessor.h"
#include "includes/VkPipelineLayoutCreateInfoAccessor.h"
#include "includes/VkRenderPassCreateInfoAccessor.h"
#include "VkPhysicalDevicePropertiesAccessor.h"
#include "VkPhysicalDevicePropertiesMutator.h"
#include "VkQueueFamilyPropertiesMutator.h"
#include "VkSurfaceCapabilitiesKHRMutator.h"
#include "VkSwapchainCreateInfoKHRAccessor.h"
#include "VkImageViewCreateInfoAccessor.h"
#include "VkShaderModuleCreateInfoAccessor.h"
#include "VkDebugUtilsMessengerCreateInfoEXTAccessor.h"
#include "VkSurfaceFormatKHRMutator.h"
#include "VkInstanceCreateInfoAccessor.h"
#include "VkFramebufferCreateInfoAccessor.h"

namespace vulkan_utils {

    jobject
    physicalDevicePropertiesObj_fromVkPhysicalDeviceProperties(JNIEnv *env, jlong pPhysicalDevice) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(pPhysicalDevice);

        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

        return VkPhysicalDevicePropertiesMutator(env).toObject(deviceProperties);
    }

    jobject
    physicalDeviceFeaturesObj_fromVkPhysicalDeviceFeatures(JNIEnv *env, jlong pPhysicalDevice) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(pPhysicalDevice);
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);
        return VkPhysicalDeviceFeaturesMutator(env).toObject(deviceFeatures);
    }

    jobjectArray
    queueFamilyPropertiesObj_fromVkQueueFamilyProperties(JNIEnv *env, jlong pPhysicalDevice) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(pPhysicalDevice);
        // Check if the device supports the required queue families (graphics, compute, transfer)
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount,
                                                 queueFamilies.data());

        // init class and constructors
        auto qfpClass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/queuefamily/VkQueueFamilyProperties");

        auto queueFamilyList = env->NewObjectArray(static_cast<jint>(queueFamilyCount), qfpClass,
                                                   nullptr);
        for (int i = 0; i < queueFamilyCount; i++) {
            auto queueFamily = queueFamilies[i];
            auto queueFamilyObj = VkQueueFamilyPropertiesMutator(env).toObject(queueFamily);
            env->SetObjectArrayElement(queueFamilyList, i, queueFamilyObj);
            env->DeleteLocalRef(queueFamilyObj);
        }

        env->DeleteLocalRef(qfpClass);

        return queueFamilyList;
    }

    jlongArray
    enumeratePhysicalDevices(JNIEnv *env, jlong vkInstance) {
        auto instance = reinterpret_cast<VkInstance>(vkInstance);

        uint32_t deviceCount;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
        jlongArray deviceHandles = env->NewLongArray((jsize) deviceCount);
        for (int i = 0; i < deviceCount; ++i) {
            auto handle = reinterpret_cast<jlong>(devices[i]);
            env->SetLongArrayRegion(deviceHandles, i, 1, &handle);
        }
        return deviceHandles;
    }

    jlong createInstance(JNIEnv *env, jobject pCreateInfo) {
        VkInstanceCreateInfo createInfo{};
        VkInstanceCreateInfoAccessor(env, pCreateInfo).fromObject(createInfo);
        VkInstance instance{};
        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

        if (result != VK_SUCCESS) {
            throw std::runtime_error("Instance creation failed: " + std::to_string(result));
        }

        return reinterpret_cast<jlong>(instance);
    }

// Function to create the debug utils messenger
    VkDebugUtilsMessengerEXT createDebugUtilsMessenger(
            JNIEnv *env,
            VkInstance instance,
            jobject pCreateInfo) {
        auto pfnCreateDebugUtilsMessengerEXT =
                (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(
                        instance, "vkCreateDebugUtilsMessengerEXT");

        if (!pfnCreateDebugUtilsMessengerEXT) {
            return VK_NULL_HANDLE;
        }

        VkDebugUtilsMessengerCreateInfoEXT messengerInfo = {};

        VkDebugUtilsMessengerCreateInfoEXTAccessor::init(env, pCreateInfo);
        VkDebugUtilsMessengerCreateInfoEXTAccessor::getInstance().fromObject(messengerInfo);

        VkDebugUtilsMessengerEXT debugUtilsMessenger = VK_NULL_HANDLE;
        VkResult result = pfnCreateDebugUtilsMessengerEXT(
                instance, &messengerInfo, nullptr, &debugUtilsMessenger);

        if (result != VK_SUCCESS) {
            return VK_NULL_HANDLE;
        }

        return debugUtilsMessenger;
    }

// Function to destroy the debug utils messenger
    void destroyDebugUtilsMessenger(
            VkInstance instance,
            VkDebugUtilsMessengerEXT debugUtilsMessenger) {
        if (!debugUtilsMessenger) {
            return;
        }

        auto pfnDestroyDebugUtilsMessengerEXT =
                (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(
                        instance, "vkDestroyDebugUtilsMessengerEXT");

        if (!pfnDestroyDebugUtilsMessengerEXT) {
            return;
        }

        pfnDestroyDebugUtilsMessengerEXT(instance, debugUtilsMessenger, nullptr);
    }

    jlong createDevice(JNIEnv *env, jlong pPhysicalDevice, jobject p_dci_obj) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(pPhysicalDevice);
        VkDeviceCreateInfo createInfo{};
        VkDeviceCreateInfoAccessor accessor(env, p_dci_obj);
        accessor.fromObject(createInfo);
        VkDevice device{};
        VkResult result = vkCreateDevice(physicalDevice, &createInfo, nullptr, &device);
        if (result != VK_SUCCESS) {
            return 0;
        }

        return reinterpret_cast<jlong>(device);
    }

    jlong createAndroidSurfaceKHR(JNIEnv *env,
                                  jlong pInstance,
                                  jobject surface_info) {
        auto instance = reinterpret_cast<VkInstance>(pInstance);
        VkSurfaceKHR surface{};

        jclass siClass = env->GetObjectClass(surface_info);
//    jfieldID  flagsField = env->GetFieldID(siClass, "flags", "I");
        jfieldID windowField = env->GetFieldID(siClass, "window", "Ljava/lang/Object;");
        auto windowObj = env->GetObjectField(surface_info, windowField);
        auto *window = ANativeWindow_fromSurface(env, windowObj);

        // Create the surface using the VK_KHR_android_surface extension
        VkAndroidSurfaceCreateInfoKHR createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
        createInfo.pNext = nullptr;
        createInfo.flags = 0;
        createInfo.window = window;

        VkResult result = vkCreateAndroidSurfaceKHR(instance, &createInfo, nullptr, &surface);

        env->DeleteLocalRef(siClass);
        env->DeleteLocalRef(windowObj);

        if (result != VK_SUCCESS) {
            // Handle surface creation failure
            return 0;
        }

        return reinterpret_cast<jlong>(surface);
    }

    void destroySurface(JNIEnv *env,
                        jlong pInstance, jlong pSurface) {
        auto instance = reinterpret_cast<VkInstance>(pInstance);
        auto surface = reinterpret_cast<VkSurfaceKHR>(pSurface);
        vkDestroySurfaceKHR(instance, surface, nullptr);
    }

    jboolean getPhysicalDeviceSurfaceSupportKHR(JNIEnv *env,
                                                jlong pDevice,
                                                jint queueFamilyIndex,
                                                jlong pSurface) {
        auto device = reinterpret_cast<VkPhysicalDevice>(pDevice);
        auto surface = reinterpret_cast<VkSurfaceKHR>(pSurface);
        if (surface == nullptr) {
            throw std::runtime_error("Invalid surface instance");
        }
        VkBool32 presentSupport = false;
        VkResult result = vkGetPhysicalDeviceSurfaceSupportKHR(device,
                                                               static_cast<uint32_t>(queueFamilyIndex),
                                                               surface, &presentSupport);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("Unable to check vkGetPhysicalDeviceSurfaceSupportKHR");
        }
        return presentSupport;
    }

    // TODO check for possible leak??
    jobject getPhysicalDeviceSurfaceCapabilitiesKHR(
            JNIEnv *env, jlong pPhysicalDevice, jlong pSurface) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(pPhysicalDevice);
        auto surface = reinterpret_cast<VkSurfaceKHR>(pSurface);

        VkSurfaceCapabilitiesKHR capabilities{};
        VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface,
                                                                    &capabilities);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("Unable to check vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
        }
        return VkSurfaceCapabilitiesKHRMutator(env).toObject(capabilities);
    }

    // TODO check for possible leak??
    _jobjectArray *getPhysicalDeviceSurfaceFormatsKHR(JNIEnv *env,
                                                      jlong pPhysicalDevice,
                                                      jlong pSurface) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(pPhysicalDevice);
        auto surface = reinterpret_cast<VkSurfaceKHR>(pSurface);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);

        if (formatCount != 0) {
            std::vector<VkSurfaceFormatKHR> formats;
            formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount,
                                                 formats.data());

            // Create a Java array to hold the VkSurfaceFormatKHR objects
            jclass formatClass = env->FindClass(
                    "io/github/ronjunevaldoz/awake/vulkan/presentation/swapchain/VkSurfaceFormatKHR");
            jobjectArray formatArray = env->NewObjectArray(static_cast<jint>(formatCount),
                                                           formatClass,
                                                           nullptr);

            for (uint32_t i = 0; i < formatCount; i++) {
                // Create a Java VkSurfaceFormatKHR object for each VkSurfaceFormatKHR
                jobject formatObj = VkSurfaceFormatKHRMutator(env).toObject(formats[i]);
                env->SetObjectArrayElement(formatArray, static_cast<jint>(i), formatObj);
                // Cleanup: Delete local reference to formatObj (optional)
                env->DeleteLocalRef(formatObj);
            }

            env->DeleteLocalRef(formatClass);

            return formatArray;
        } else {
            return jobjectArray();
        }
    }

    // TODO check for possible leak??
    _jobjectArray *getPhysicalDeviceSurfacePresentModesKHR(
            JNIEnv *env, jlong pPhysicalDevice, jlong pSurface) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(pPhysicalDevice);
        auto surface = reinterpret_cast<VkSurfaceKHR>(pSurface);

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount,
                                                  nullptr);

        if (presentModeCount != 0) {
            std::vector<VkPresentModeKHR> presentModes;
            presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount,
                                                      presentModes.data());

            // Create a Java array to hold the VkSurfaceFormatKHR objects
            jclass presetModeClass = env->FindClass(
                    "io/github/ronjunevaldoz/awake/vulkan/enums/VkPresentModeKHR");
            jobjectArray presetModeArray = env->NewObjectArray(static_cast<jint>(presentModeCount),
                                                               presetModeClass, nullptr);

            for (uint32_t i = 0; i < presentModeCount; i++) {
                // Create a Java VkPresentModeKHR object for each VkPresentModeKHR
                jobject presetModObj = enum_utils::setEnumFromVulkan(env, presentModes[i],
                                                                     "io/github/ronjunevaldoz/awake/vulkan/enums/VkPresentModeKHR");
                env->SetObjectArrayElement(presetModeArray, static_cast<jint>(i), presetModObj);
                env->DeleteLocalRef(presetModObj);
            }

            env->DeleteLocalRef(presetModeClass);

            return presetModeArray;
        } else {
            return jobjectArray();
        }
    }

    jlong createSwapchainKHR(JNIEnv *env,
                             jlong pDevice,
                             jobject create_info_khr) {
        auto device = reinterpret_cast<VkDevice>(pDevice);
        VkSwapchainKHR swapchain{};
        VkSwapchainCreateInfoKHR createInfo{};
        VkSwapchainCreateInfoKHRAccessor(env, create_info_khr).fromObject(createInfo);
//        auto createInfo = vulkan_utils::VkSwapchainCreateInfoKHR_fromObject(env, create_info_khr);
        VkResult result = vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapchain);
        if (result != VK_SUCCESS) {
            return 0;
        }

        if (swapchain == nullptr) {
            return 0;
        }
        return reinterpret_cast<jlong>(swapchain);
    }

    void destroySwapchainKHR(JNIEnv *env, jlong pDevice,
                             jlong swapchain_khr) {
        auto device = reinterpret_cast<VkDevice>(pDevice);
        auto swapchain = reinterpret_cast<VkSwapchainKHR>(swapchain_khr);
        vkDestroySwapchainKHR(device, swapchain, nullptr);
    }

    jlong getDeviceQueue(JNIEnv *env,
                         jlong device,
                         jint queue_family_index,
                         jint queue_index) {
        auto deviceHandle = reinterpret_cast<VkDevice>(device);

        VkQueue graphicsQueue;
        vkGetDeviceQueue(deviceHandle, static_cast<uint32_t>(queue_family_index),
                         static_cast<uint32_t>(queue_index), &graphicsQueue);
        return reinterpret_cast<jlong>(graphicsQueue);
    }


    jobjectArray enumerateInstanceLayerProperties(JNIEnv *env) {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        std::vector<VkLayerProperties> layers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

        // init class and constructors
        auto layerPropClass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/models/VkLayerProperties");
        auto layerPropConstructor = env->GetMethodID(layerPropClass, "<init>",
                                                     "(Ljava/lang/String;IILjava/lang/String;)V");

        auto extensionList = env->NewObjectArray(static_cast<jint>(layerCount), layerPropClass,
                                                 nullptr);
        for (int i = 0; i < layerCount; i++) {
            auto layer = layers[i];
            auto layerName = env->NewStringUTF(layer.layerName);
            auto layerDesc = env->NewStringUTF(layer.description);

            // Create a new VkExtensionProperties object
            auto qfpObj = env->NewObject(layerPropClass, layerPropConstructor,
                                         static_cast<jstring>(layerName),
                                         static_cast<jint>(layer.specVersion),
                                         static_cast<jint>(layer.implementationVersion),
                                         static_cast<jstring>(layerDesc)
            );

            // Add the VkExtensionProperties object to the ArrayList
            env->SetObjectArrayElement(extensionList, i, qfpObj);
            env->DeleteLocalRef(layerName);
            env->DeleteLocalRef(layerDesc);
            env->DeleteLocalRef(qfpObj);
        }

        env->DeleteLocalRef(layerPropClass);
        return extensionList;
    }

    jobjectArray enumerateInstanceExtensionProperties(JNIEnv *env, jstring jlayer_name) {
        uint32_t extensionCount = 0;
        const char *layerName = nullptr;
        if (jlayer_name != nullptr) {
            layerName = env->GetStringUTFChars(jlayer_name, nullptr);
            env->ReleaseStringUTFChars(jlayer_name, layerName);
        }
        vkEnumerateInstanceExtensionProperties(layerName, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(layerName, &extensionCount, extensions.data());

        // init class and constructors
        auto extPropClass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/models/VkExtensionProperties");
        auto extPropConstructor = env->GetMethodID(extPropClass, "<init>",
                                                   "(Ljava/lang/String;I)V");

        auto extensionList = env->NewObjectArray(static_cast<jint>(extensionCount), extPropClass,
                                                 nullptr);
        for (int i = 0; i < extensionCount; i++) {
            auto extension = extensions[i];
            auto extensionName = env->NewStringUTF(extension.extensionName);

            // Create a new VkExtensionProperties object
            auto qfpObj = env->NewObject(extPropClass, extPropConstructor,
                                         static_cast<jstring>(extensionName),
                                         static_cast<jint>(extension.specVersion)
            );

            // Add the VkExtensionProperties object to the ArrayList
            env->SetObjectArrayElement(extensionList, i, qfpObj);
            env->DeleteLocalRef(extensionName);
            env->DeleteLocalRef(qfpObj);
        }

        env->DeleteLocalRef(extPropClass);
        return extensionList;
    }

    jobjectArray
    enumerateDeviceExtensionProperties(JNIEnv *env, jlong pPhysicalDevice, jstring jlayer_name) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(pPhysicalDevice);

        const char *layerName = nullptr;
        if (jlayer_name != nullptr) {
            layerName = env->GetStringUTFChars(jlayer_name, nullptr);
            env->ReleaseStringUTFChars(jlayer_name, layerName);
        }
        uint32_t extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(physicalDevice, layerName, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(physicalDevice, layerName, &extensionCount,
                                             extensions.data());

        // init class and constructors
        auto extPropClass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/models/VkExtensionProperties");
        auto extPropConstructor = env->GetMethodID(extPropClass, "<init>",
                                                   "(Ljava/lang/String;I)V");

        auto extensionList = env->NewObjectArray(static_cast<jint>(extensionCount), extPropClass,
                                                 nullptr);
        for (int i = 0; i < extensionCount; i++) {
            auto extension = extensions[i];
            auto extensionName = env->NewStringUTF(extension.extensionName);

            // Create a new VkExtensionProperties object
            auto qfpObj = env->NewObject(extPropClass, extPropConstructor,
                                         static_cast<jstring>(extensionName),
                                         static_cast<jint>(extension.specVersion)
            );

            // Add the VkExtensionProperties object to the ArrayList
            env->SetObjectArrayElement(extensionList, i, qfpObj);
            env->DeleteLocalRef(extensionName);
            env->DeleteLocalRef(
                    qfpObj); // TODO should not be deleted when directly passing to java??
        }

        env->DeleteLocalRef(extPropClass);
        return extensionList;
    }

    // TODO check for possible leak??
    _jobjectArray *getSwapchainImagesKHR(JNIEnv *env, jlong pDevice, jlong pSwapchain) {

        auto device = reinterpret_cast<VkDevice>(pDevice);
        auto swapChain = reinterpret_cast<VkSwapchainKHR>(pSwapchain);

        uint32_t imageCount = 0;
        vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
        std::vector<VkImage> swapChainImages(imageCount);
        vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

        // init class and constructors
        auto imgClass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/models/VkImage");
        auto imgConstructor = env->GetMethodID(imgClass, "<init>",
                                               "(J)V");

        auto imageList = env->NewObjectArray(static_cast<jint>(imageCount), imgClass,
                                             nullptr);
        for (int i = 0; i < imageCount; i++) {
            auto image = swapChainImages[i];
            // Create a new VKImage object
            auto imageObj = env->NewObject(imgClass, imgConstructor,
                                           reinterpret_cast<jlong>(image));

            // Add the VkImage object to the ArrayList
            env->SetObjectArrayElement(imageList, i, imageObj);
            env->DeleteLocalRef(imageObj);
        }

        swapChainImages.clear(); // TODO check if needed to clear
        env->DeleteLocalRef(imgClass);
        return imageList;
    }

    jlong createImageView(JNIEnv *env,
                          jlong pDevice,
                          jobject p_create_nfo
    ) {
        auto device = reinterpret_cast<VkDevice>(pDevice);

        VkImageViewCreateInfo createInfo{};
        VkImageViewCreateInfoAccessor(env, p_create_nfo).fromObject(createInfo);

        VkImageView imageView;
        VkResult result = vkCreateImageView(device, &createInfo, nullptr, &imageView);

        if (result != VK_SUCCESS) {
            return 0;
        }

        return reinterpret_cast<jlong>(imageView);
    }

    void destroyImageView(JNIEnv *env,
                          jlong pDevice,
                          jlong p_image_view
    ) {
        auto device = reinterpret_cast<VkDevice>(pDevice);
        auto imageView = reinterpret_cast<VkImageView>(p_image_view);
        vkDestroyImageView(device, imageView, nullptr);
    }

    jlong createShaderModule(JNIEnv *env, jlong pDevice, jobject pCreateInfo) {
        VkShaderModuleCreateInfo createInfo{};
        VkShaderModuleCreateInfoAccessor(env, pCreateInfo).fromObject(createInfo);
        auto device = reinterpret_cast<VkDevice>(pDevice);
        VkShaderModule shaderModule;
        VkResult result = vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule);

        if (result != VK_SUCCESS) {
            return 0;
        }

        return reinterpret_cast<jlong>(shaderModule);
    }

    void destroyShaderModule(jlong pDevice, jlong pShaderModule) {
        auto device = reinterpret_cast<VkDevice>(pDevice);
        auto shaderModule = reinterpret_cast<VkShaderModule>(pShaderModule);
        vkDestroyShaderModule(device, shaderModule, nullptr);
    }

    jlong createPipelineCache(JNIEnv *env, jlong pDevice, jobject pCreateInfo) {
        auto device = reinterpret_cast<VkDevice>(pDevice);

        VkPipelineCacheCreateInfo createInfo{};
        VkPipelineCacheCreateInfoAccessor(env, pCreateInfo).fromObject(createInfo);

        VkPipelineCache pipelineCache;
        VkResult result = vkCreatePipelineCache(device, &createInfo, nullptr, &pipelineCache);
        if (result != VK_SUCCESS) {
            return 0;
        }
        return reinterpret_cast<jlong>(pipelineCache);
    }

    void destroyPipelineCache(jlong pDevice, jlong pPipelineCache) {
        auto device = reinterpret_cast<VkDevice>(pDevice);
        auto pipelineCache = reinterpret_cast<VkPipelineCache>(pPipelineCache);
        vkDestroyPipelineCache(device, pipelineCache, nullptr);
    }

    jlongArray createGraphicsPipeline(JNIEnv *env, jlong pDevice, jlong pPipelineCache,
                                      jobjectArray createInfosObj
    ) {
        auto device = reinterpret_cast<VkDevice>(pDevice);
        auto pipelineCache = reinterpret_cast<VkPipelineCache>(pPipelineCache);
        auto createInfoSize = env->GetArrayLength(createInfosObj);
        std::vector<VkGraphicsPipelineCreateInfo> createInfos;
        for (int i = 0; i < createInfoSize; ++i) {
            auto createInfoObj = env->GetObjectArrayElement(createInfosObj, i);
            VkGraphicsPipelineCreateInfoAccessor accessor(env, createInfoObj);
            VkGraphicsPipelineCreateInfo createInfo{};
            accessor.fromObject(createInfo);
            createInfos.push_back(createInfo);
            env->DeleteLocalRef(createInfoObj);
        }
        std::vector<VkPipeline> pipelines(createInfoSize);
        VkResult result = vkCreateGraphicsPipelines(device, pipelineCache,
                                                    static_cast<uint32_t>(createInfos.size()),
                                                    createInfos.data(), nullptr, pipelines.data());
        if (result != VK_SUCCESS) {
            return jlongArray();
        }
        jlongArray pipelineHandles = env->NewLongArray((jsize) pipelines.size());
        for (int i = 0; i < pipelines.size(); ++i) {
            auto pipeline = reinterpret_cast<jlong>(pipelines[i]);
            env->SetLongArrayRegion(pipelineHandles, i, 1, &pipeline);
        }
        return pipelineHandles;
    }

    void destroyPipeline(jlong pDevice, jlong pPipeline) {
        auto device = reinterpret_cast<VkDevice>(pDevice);
        auto pipeline = reinterpret_cast<VkPipeline>(pPipeline);
        vkDestroyPipeline(device, pipeline, nullptr);
    }

    jlong createPipelineLayout(JNIEnv *env, jlong pDevice, jobject pCreateInfo) {
        auto device = reinterpret_cast<VkDevice>(pDevice);
        VkPipelineLayoutCreateInfoAccessor accessor(env, pCreateInfo);
        VkPipelineLayoutCreateInfo createInfo;
        accessor.fromObject(createInfo);
        VkPipelineLayout layout;
        VkResult result = vkCreatePipelineLayout(device, &createInfo, nullptr, &layout);

        if (result != VK_SUCCESS) {
            return 0;
        }
        return reinterpret_cast<jlong>(layout);
    }

    void destroyPipelineLayout(jlong pDevice, jlong pPiplineLayout) {
        auto device = reinterpret_cast<VkDevice>(pDevice);
        auto piplineLayout = reinterpret_cast<VkPipelineLayout>(pPiplineLayout);
        vkDestroyPipelineLayout(device, piplineLayout, nullptr);
    }

    jlong createRenderPass(JNIEnv *env, jlong pDevice, jobject pCreateInfo) {
        auto device = reinterpret_cast<VkDevice>(pDevice);
        VkRenderPassCreateInfoAccessor accessor(env, pCreateInfo);
        VkRenderPassCreateInfo createInfo;
        accessor.fromObject(createInfo);
        VkRenderPass handle;
        VkResult result = vkCreateRenderPass(device, &createInfo, nullptr, &handle);

        if (result != VK_SUCCESS) {
            return 0;
        }
        return reinterpret_cast<jlong>(handle);
    }

    void destroyRenderPass(jlong pDevice, jlong pRenderPass) {
        auto device = reinterpret_cast<VkDevice>(pDevice);
        auto renderPass = reinterpret_cast<VkRenderPass>(pRenderPass);
        vkDestroyRenderPass(device, renderPass, nullptr);
    }


    jlong createFramebuffer(JNIEnv *env, jlong pDevice, jobject pCreateInfo) {
        auto device = reinterpret_cast<VkDevice>(pDevice);
        VkFramebufferCreateInfoAccessor accessor(env, pCreateInfo);
        VkFramebufferCreateInfo createInfo;
        accessor.fromObject(createInfo);
        VkFramebuffer handle;
        VkResult result = vkCreateFramebuffer(device, &createInfo, nullptr, &handle);

        if (result != VK_SUCCESS) {
            return 0;
        }
        return reinterpret_cast<jlong>(handle);
    }

    void destroyFramebuffer(jlong pDevice, jlong pFrameBuffer) {
        auto device = reinterpret_cast<VkDevice>(pDevice);
        auto frameBuffer = reinterpret_cast<VkFramebuffer>(pFrameBuffer);
        vkDestroyFramebuffer(device, frameBuffer, nullptr);
    }
}