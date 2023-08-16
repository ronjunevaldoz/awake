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

            // Add the VkQueueFamilyProperties object to the ArrayList
            env->SetObjectArrayElement(queueFamilyList, i, queueFamilyObj);
        }

        env->DeleteLocalRef(qfpClass);

        return queueFamilyList;
    }

    // TODO check better to delete local ref
    _jobject *extent2DObj_fromExtend2D(JNIEnv *env, VkExtent2D &extent2D) {
        jclass extent2DClass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/models/VkExtent2D");
        jmethodID extent2DConstructor = env->GetMethodID(extent2DClass, "<init>", "(II)V");
        jobject extent2DObj = env->NewObject(extent2DClass, extent2DConstructor,
                                             static_cast<jint>(extent2D.width),
                                             static_cast<jint>(extent2D.height));
        env->DeleteLocalRef(extent2DClass);
        return extent2DObj;
    }

    // TODO check better to delete local ref
    _jobject *surfaceTransformFlagBitsKHRObj_fromVkSurfaceTransformFlagBitsKHR(JNIEnv *env,
                                                                               VkSurfaceTransformFlagBitsKHR &flagBitsKhr) {
        jclass enumClass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/enums/VkSurfaceTransformFlagBitsKHR");
        auto enumValues = (jobjectArray) (env->CallStaticObjectMethod(enumClass,
                                                                      env->GetStaticMethodID(
                                                                              enumClass,
                                                                              "values",
                                                                              "()[Lio/github/ronjunevaldoz/awake/vulkan/enums/VkSurfaceTransformFlagBitsKHR;")));

        jsize numEnumValues = env->GetArrayLength(enumValues);
        jint index = std::min(static_cast<jint>(flagBitsKhr), numEnumValues - 1);
        jobject enumObj = env->GetObjectArrayElement(enumValues, index);

        env->DeleteLocalRef(enumClass);
        env->DeleteLocalRef(enumValues);

        return enumObj;
    }

    // TODO check better to delete local ref
    _jobject *formatObj_fromVkSurfaceFormatKHR(JNIEnv *env, VkFormat &format) {
        jclass enumClass = env->FindClass("io/github/ronjunevaldoz/awake/vulkan/enums/VkFormat");
        auto enumValues = (jobjectArray) (env->CallStaticObjectMethod(enumClass,
                                                                      env->GetStaticMethodID(
                                                                              enumClass,
                                                                              "values",
                                                                              "()[Lio/github/ronjunevaldoz/awake/vulkan/enums/VkFormat;")));
        jsize numEnumValues = env->GetArrayLength(enumValues);
        jint index = std::min(static_cast<jint>(format), numEnumValues - 1);
        jobject enumObj = env->GetObjectArrayElement(enumValues, index);

        env->DeleteLocalRef(enumClass);
        env->DeleteLocalRef(enumValues);

        return enumObj;
    }


    // TODO check better to delete local ref
    _jobject *colorSpaceObj_fromVkColorSpaceKHR(JNIEnv *env, VkColorSpaceKHR &colorSpace) {
        jclass enumClass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/enums/VkColorSpaceKHR");
        auto enumValues = (jobjectArray) (env->CallStaticObjectMethod(enumClass,
                                                                      env->GetStaticMethodID(
                                                                              enumClass,
                                                                              "values",
                                                                              "()[Lio/github/ronjunevaldoz/awake/vulkan/enums/VkColorSpaceKHR;")));
        jsize numEnumValues = env->GetArrayLength(enumValues);
        jint index = std::min(static_cast<jint>(colorSpace), numEnumValues - 1);
        jobject enumObj = env->GetObjectArrayElement(enumValues, index);

        env->DeleteLocalRef(enumClass);
        env->DeleteLocalRef(enumValues);

        return enumObj;
    }

    // TODO check better to delete local ref
    _jobject *surfaceFormatKHRObj_fromVkSurfaceFormatKHR(JNIEnv *env, VkSurfaceFormatKHR &format) {
        jclass clazz = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/presentation/swapchain/VkSurfaceFormatKHR");
        jmethodID constructor = env->GetMethodID(clazz, "<init>",
                                                 "(Lio/github/ronjunevaldoz/awake/vulkan/enums/VkFormat;Lio/github/ronjunevaldoz/awake/vulkan/enums/VkColorSpaceKHR;)V");
        auto formatEnumObj = formatObj_fromVkSurfaceFormatKHR(env, format.format);
        auto colorSpaceEnumObj = colorSpaceObj_fromVkColorSpaceKHR(env, format.colorSpace);
        jobject obj = env->NewObject(clazz, constructor, formatEnumObj, colorSpaceEnumObj);
        // Cleanup: Delete local references (optional)
        env->DeleteLocalRef(clazz);
        env->DeleteLocalRef(formatEnumObj);
        env->DeleteLocalRef(colorSpaceEnumObj);
        return obj;
    }

    // TODO check better to delete local ref
    _jobject *presentModeKHRObj_fromVkPresentModeKHR(JNIEnv *env, VkPresentModeKHR &presentMode) {
        jclass enumClass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/enums/VkPresentModeKHR");
        auto enumValues = (jobjectArray) (env->CallStaticObjectMethod(enumClass,
                                                                      env->GetStaticMethodID(
                                                                              enumClass,
                                                                              "values",
                                                                              "()[Lio/github/ronjunevaldoz/awake/vulkan/enums/VkPresentModeKHR;")));
        jsize numEnumValues = env->GetArrayLength(enumValues);
        jint index = std::min(static_cast<jint>(presentMode), numEnumValues - 1);
        jobject enumObj = env->GetObjectArrayElement(enumValues, index);

        env->DeleteLocalRef(enumClass);
        env->DeleteLocalRef(enumValues);

        return enumObj;
    }

    VkSwapchainCreateInfoKHR
    VkSwapchainCreateInfoKHR_fromObject(JNIEnv *env, jobject pSwapchainObj) {
        VkSwapchainCreateInfoKHR createInfo{};
        VkSwapchainCreateInfoKHRAccessor(env, pSwapchainObj).fromObject(createInfo);
        return createInfo;
    }

    bool
    enumeratePhysicalDevices(JNIEnv *env, jlong vkInstance, jobject pDeviceCountDirectBufferObj,
                             jobject pPhysicalDevicesDirectBufferObj) {
        auto instance = reinterpret_cast<VkInstance>(vkInstance);

        // Call enumeratePhysicalDevices to get the number of physical devices
        if (pPhysicalDevicesDirectBufferObj == nullptr) {
            jint *intArray = reinterpret_cast<jint *>(env->GetDirectBufferAddress(
                    pDeviceCountDirectBufferObj));
            if (intArray == nullptr) {
                // possible not a direct buffer?
                return false;
            }
            uint32_t physicalDeviceCount = 0;
            vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
            intArray[0] = static_cast<jint>(physicalDeviceCount);
        } else {
            jint *intArray = reinterpret_cast<jint *>(env->GetDirectBufferAddress(
                    pDeviceCountDirectBufferObj));
            if (intArray == nullptr) {
                // possible not a direct buffer?
                return false;
            }
            auto *longArray = reinterpret_cast<jlong *>(env->GetDirectBufferAddress(
                    pPhysicalDevicesDirectBufferObj));
            if (longArray == nullptr) {
                // possible not a direct buffer?
                return false;
            }
            // Call enumeratePhysicalDevices again to fill the physical device handles in the direct ByteBuffer
            auto deviceCount = static_cast<uint32_t>(intArray[0]);
            std::vector<VkPhysicalDevice> devices(deviceCount);
            vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
            // fill the buffer
            for (int i = 0; i < deviceCount; ++i) {
                longArray[i] = reinterpret_cast<jlong>(devices[i]);
            }
        }
        return true;
    }

    jlong createInstance(JNIEnv *env, jobject app_info) {
        VkApplicationInfoAccessor accessor(env, app_info);
        VkApplicationInfo appInfo{};
        accessor.fromObject(appInfo);

        std::vector<const char *> layers{
                "VK_LAYER_KHRONOS_validation"
        };

        if (!vulkan_utils::checkValidationLayerSupported(layers)) {
            throw std::runtime_error("Validation layers are not supported.");
        }


        std::vector<const char *> enabled_inst_exts;

        // check if androidSurfaceExtensionSupported
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        bool androidSurfaceExtensionSupported = false;
        bool surfaceExtensionSupported = false;
        bool swapChainExtensionSupported = false;
        for (const auto &extension: extensions) {
            if (strcmp(extension.extensionName, VK_KHR_ANDROID_SURFACE_EXTENSION_NAME) == 0) {
                androidSurfaceExtensionSupported = true;
            }
            if (strcmp(extension.extensionName, VK_KHR_SURFACE_EXTENSION_NAME) == 0) {
                surfaceExtensionSupported = true;
            }
            enabled_inst_exts.push_back(extension.extensionName);
        }

        if (surfaceExtensionSupported) {
            // enable presentation queue family?
            enabled_inst_exts.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
        }
        if (androidSurfaceExtensionSupported) {
            // enable surface
            enabled_inst_exts.push_back(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);
        }

        // Enable the debug utils extension if available
        if (vulkan_utils::checkDebugUtilsExtAvailable() ||
            vulkan_utils::checkDebugUtilsExtFromAvailableLayers()) {
            enabled_inst_exts.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(enabled_inst_exts.size());
        createInfo.ppEnabledExtensionNames = enabled_inst_exts.data();
        createInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
        createInfo.ppEnabledLayerNames = layers.data();

        VkInstance instance{};
        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

        if (result != VK_SUCCESS) {
            throw std::runtime_error("Instance creation failed: " + std::to_string(result));
        }

        return reinterpret_cast<jlong>(instance);
    }

// Function to enable the debug utils extension if available
    bool checkDebugUtilsExtAvailable() {
        // Get the instance extension count.
        uint32_t inst_ext_count = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &inst_ext_count, nullptr);

        // Enumerate the instance extensions.
        VkExtensionProperties inst_exts[inst_ext_count];
        vkEnumerateInstanceExtensionProperties(nullptr, &inst_ext_count, inst_exts);

        // Check for debug utils extension within the system driver or loader.
        // Check if the debug utils extension is available (in the driver).
        VkExtensionProperties *inst_exts_end = inst_exts + inst_ext_count;
        bool debugUtilsExtAvailable = inst_exts_end !=
                                      std::find_if(inst_exts, inst_exts_end,
                                                   [](VkExtensionProperties
                                                      extensionProperties) {
                                                       return strcmp(
                                                               extensionProperties.extensionName,
                                                               VK_EXT_DEBUG_UTILS_EXTENSION_NAME) ==
                                                              0;
                                                   });

        return debugUtilsExtAvailable;
    }


// Function to enable the debug utils extension if available
    bool checkDebugUtilsExtFromAvailableLayers() {
        // Also check the layers for the debug utils extension.
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        std::vector<VkLayerProperties> layer_props(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, layer_props.data());

        bool debugUtilsExtAvailable = false;

        for (const auto &layer: layer_props) {
            uint32_t layer_ext_count;
            vkEnumerateInstanceExtensionProperties(layer.layerName, &layer_ext_count, nullptr);
            if (layer_ext_count == 0) continue;

            std::vector<VkExtensionProperties> layer_exts(layer_ext_count);
            vkEnumerateInstanceExtensionProperties(layer.layerName, &layer_ext_count,
                                                   layer_exts.data());
            debugUtilsExtAvailable = std::any_of(layer_exts.begin(), layer_exts.end(),
                                                 [](const VkExtensionProperties &extension) {
                                                     return strcmp(extension.extensionName,
                                                                   VK_EXT_DEBUG_UTILS_EXTENSION_NAME) ==
                                                            0;
                                                 });

            if (debugUtilsExtAvailable) {
                // Add the including layer into the layer request list if necessary.
                break;
            }
        }
        return debugUtilsExtAvailable;
    }

    bool checkValidationLayerSupported(const std::vector<const char *> &layers) {

        // Get the layer count using a null pointer as the last parameter.
        uint32_t instance_layer_present_count = 0;
        vkEnumerateInstanceLayerProperties(&instance_layer_present_count, nullptr);

        // Enumerate layers with a valid pointer in the last parameter.
        std::vector<VkLayerProperties> layer_props(instance_layer_present_count);
        vkEnumerateInstanceLayerProperties(&instance_layer_present_count, layer_props.data());

        // Make sure selected validation layers are available.
        bool validationLayersAvailable = std::all_of(layers.begin(), layers.end(),
                                                     [&layer_props](const char *layer) {
                                                         return std::find_if(layer_props.begin(),
                                                                             layer_props.end(),
                                                                             [layer](const VkLayerProperties &layerProperties) {
                                                                                 return strcmp(
                                                                                         layerProperties.layerName,
                                                                                         layer) ==
                                                                                        0;
                                                                             }) !=
                                                                layer_props.end();
                                                     });
        return validationLayersAvailable; // or false depending on the validation layer availability
    }

    // TODO check for possible leak??
// Function to create the debug utils messenger
    VkDebugUtilsMessengerEXT createDebugUtilsMessenger(
            VkInstance instance) {
        auto pfnCreateDebugUtilsMessengerEXT =
                (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(
                        instance, "vkCreateDebugUtilsMessengerEXT");

        if (!pfnCreateDebugUtilsMessengerEXT) {
            return VK_NULL_HANDLE;
        }

        VkDebugUtilsMessengerCreateInfoEXT messengerInfo = {};
        messengerInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        messengerInfo.pNext = nullptr;
        messengerInfo.flags = 0;
        messengerInfo.messageSeverity =
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
        messengerInfo.messageType =
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        messengerInfo.pfnUserCallback = &onDebugUtilsMessage;
        messengerInfo.pUserData = nullptr; // Custom user data passed to the callback

        VkDebugUtilsMessengerEXT debugUtilsMessenger = VK_NULL_HANDLE;
        VkResult result = pfnCreateDebugUtilsMessengerEXT(
                instance, &messengerInfo, nullptr, &debugUtilsMessenger);

        if (result != VK_SUCCESS) {
            return VK_NULL_HANDLE;
        }

        return debugUtilsMessenger;
    }


    VKAPI_ATTR VkBool32

    VKAPI_CALL onDebugUtilsMessage(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageTypes,
            const VkDebugUtilsMessengerCallbackDataEXT *callbackData,
            void *userData) {
        const char validation[] = "Validation";
        const char performance[] = "Performance";
        const char error[] = "ERROR";
        const char warning[] = "WARNING";
        const char unknownType[] = "UNKNOWN_TYPE";
        const char unknownSeverity[] = "UNKNOWN_SEVERITY";
        const char *typeString = unknownType;
        const char *severityString = unknownSeverity;
        const char *messageIdName = callbackData->pMessageIdName;
        int32_t messageIdNumber = callbackData->messageIdNumber;
        const char *message = callbackData->pMessage;
        android_LogPriority priority = ANDROID_LOG_UNKNOWN;

        if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
            severityString = error;
            priority = ANDROID_LOG_ERROR;
        } else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
            severityString = warning;
            priority = ANDROID_LOG_WARN;
        }
        if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) {
            typeString = validation;
        } else if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) {
            typeString = performance;
        }

        __android_log_print(priority,
                            "Awake Vulkan",
                            "%s %s: \n[%s] Code %i :\n%s",
                            typeString,
                            severityString,
                            messageIdName,
                            messageIdNumber,
                            message);

        // Returning false tells the layer not to stop when the event occurs, so
        // they see the same behavior with and without validation layers enabled.
        return VK_FALSE;
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
                jobject formatObj = vulkan_utils::surfaceFormatKHRObj_fromVkSurfaceFormatKHR(env,
                                                                                             formats[i]);
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
                jobject presetModObj = vulkan_utils::presentModeKHRObj_fromVkPresentModeKHR(env,
                                                                                            presentModes[i]);
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
        auto createInfo = vulkan_utils::VkSwapchainCreateInfoKHR_fromObject(env, create_info_khr);
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

    // TODO check for possible leak??
    _jobjectArray *enumerateInstanceExtensionProperties(JNIEnv *env) {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

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

    // TODO check for possible leak??
    _jobjectArray *enumerateDeviceExtensionProperties(JNIEnv *env, jlong pPhysicalDevice) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(pPhysicalDevice);

        uint32_t extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount,
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
}