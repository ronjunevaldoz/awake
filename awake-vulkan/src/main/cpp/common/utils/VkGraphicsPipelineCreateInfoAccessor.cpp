/*
 *  VkGraphicsPipelineCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>
#include <VkPipelineShaderStageCreateInfoAccessor.cpp>
#include <VkPipelineVertexInputStateCreateInfoAccessor.cpp>
#include <VkPipelineInputAssemblyStateCreateInfoAccessor.cpp>
#include <VkPipelineTessellationStateCreateInfoAccessor.cpp>
#include <VkPipelineViewportStateCreateInfoAccessor.cpp>
#include <VkPipelineRasterizationStateCreateInfoAccessor.cpp>
#include <VkPipelineMultisampleStateCreateInfoAccessor.cpp>
#include <VkPipelineDepthStencilStateCreateInfoAccessor.cpp>
#include <VkPipelineColorBlendStateCreateInfoAccessor.cpp>
#include <VkPipelineDynamicStateCreateInfoAccessor.cpp>

class VkGraphicsPipelineCreateInfoAccessor {
private:
    JNIEnv *env;
private:
    jobject obj;
private:
    jclass clazz;
private:
    jfieldID sTypeField;
private:
    jfieldID pNextField;
private:
    jfieldID flagsField;
private:
    jfieldID pStagesField;
private:
    jfieldID pVertexInputStateField;
private:
    jfieldID pInputAssemblyStateField;
private:
    jfieldID pTessellationStateField;
private:
    jfieldID pViewportStateField;
private:
    jfieldID pRasterizationStateField;
private:
    jfieldID pMultisampleStateField;
private:
    jfieldID pDepthStencilStateField;
private:
    jfieldID pColorBlendStateField;
private:
    jfieldID pDynamicStateField;
private:
    jfieldID layoutField;
private:
    jfieldID renderPassField;
private:
    jfieldID subpassField;
private:
    jfieldID basePipelineHandleField;
private:
    jfieldID basePipelineIndexField;
private:
    jfieldID stageCountField;
public:
    VkGraphicsPipelineCreateInfoAccessor(JNIEnv *env, jobject &obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        sTypeField = env->GetFieldID(clazz, "sType",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
        pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
        flagsField = env->GetFieldID(clazz, "flags", "I");
        pStagesField = env->GetFieldID(clazz, "pStages",
                                       "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineShaderStageCreateInfo;");
        pVertexInputStateField = env->GetFieldID(clazz, "pVertexInputState",
                                                 "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineVertexInputStateCreateInfo;");
        pInputAssemblyStateField = env->GetFieldID(clazz, "pInputAssemblyState",
                                                   "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineInputAssemblyStateCreateInfo;");
        pTessellationStateField = env->GetFieldID(clazz, "pTessellationState",
                                                  "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineTessellationStateCreateInfo;");
        pViewportStateField = env->GetFieldID(clazz, "pViewportState",
                                              "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineViewportStateCreateInfo;");
        pRasterizationStateField = env->GetFieldID(clazz, "pRasterizationState",
                                                   "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineRasterizationStateCreateInfo;");
        pMultisampleStateField = env->GetFieldID(clazz, "pMultisampleState",
                                                 "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineMultisampleStateCreateInfo;");
        pDepthStencilStateField = env->GetFieldID(clazz, "pDepthStencilState",
                                                  "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineDepthStencilStateCreateInfo;");
        pColorBlendStateField = env->GetFieldID(clazz, "pColorBlendState",
                                                "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineColorBlendStateCreateInfo;");
        pDynamicStateField = env->GetFieldID(clazz, "pDynamicState",
                                             "[Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineDynamicStateCreateInfo;");
        layoutField = env->GetFieldID(clazz, "layout", "J");
        renderPassField = env->GetFieldID(clazz, "renderPass", "J");
        subpassField = env->GetFieldID(clazz, "subpass", "I");
        basePipelineHandleField = env->GetFieldID(clazz, "basePipelineHandle", "J");
        basePipelineIndexField = env->GetFieldID(clazz, "basePipelineIndex", "I");
        stageCountField = env->GetFieldID(clazz, "stageCount", "I");
    }

    VkStructureType getsType() {
        auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
        return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
    }

    void getpNext(VkGraphicsPipelineCreateInfo &clazzInfo) {
        auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
        clazzInfo.pNext = ref;
    }

    uint32_t getflags() {
        return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
    }

    void getpStages(VkGraphicsPipelineCreateInfo &clazzInfo) {
        auto pStagesArray = (jobjectArray) env->GetObjectField(obj, pStagesField);
        if (pStagesArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pStagesArray);
        std::vector<VkPipelineShaderStageCreateInfo> pStages;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pStagesArray,
                                                                i); // actual type is VkPipelineShaderStageCreateInfo[];
            // experimental optimize accessor
            VkPipelineShaderStageCreateInfoAccessor accessor(env, element);
            VkPipelineShaderStageCreateInfo ref{};
            accessor.fromObject(ref);
            pStages.push_back(ref);
        }
        // processing
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkPipelineShaderStageCreateInfo[size];
        std::copy(pStages.begin(), pStages.end(), copy);
        clazzInfo.pStages = copy;
    }

    void getpVertexInputState(VkGraphicsPipelineCreateInfo &clazzInfo) {
        auto pVertexInputStateArray = (jobjectArray) env->GetObjectField(obj,
                                                                         pVertexInputStateField);
        if (pVertexInputStateArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pVertexInputStateArray);
        std::vector<VkPipelineVertexInputStateCreateInfo> pVertexInputState;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pVertexInputStateArray,
                                                                i); // actual type is VkPipelineVertexInputStateCreateInfo[];
            // experimental optimize accessor
            VkPipelineVertexInputStateCreateInfoAccessor accessor(env, element);
            VkPipelineVertexInputStateCreateInfo ref{};
            accessor.fromObject(ref);
            pVertexInputState.push_back(ref);
        }
        // processing
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkPipelineVertexInputStateCreateInfo[size];
        std::copy(pVertexInputState.begin(), pVertexInputState.end(), copy);
        clazzInfo.pVertexInputState = copy;
    }

    void getpInputAssemblyState(VkGraphicsPipelineCreateInfo &clazzInfo) {
        auto pInputAssemblyStateArray = (jobjectArray) env->GetObjectField(obj,
                                                                           pInputAssemblyStateField);
        if (pInputAssemblyStateArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pInputAssemblyStateArray);
        std::vector<VkPipelineInputAssemblyStateCreateInfo> pInputAssemblyState;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pInputAssemblyStateArray,
                                                                i); // actual type is VkPipelineInputAssemblyStateCreateInfo[];
            // experimental optimize accessor
            VkPipelineInputAssemblyStateCreateInfoAccessor accessor(env, element);
            VkPipelineInputAssemblyStateCreateInfo ref{};
            accessor.fromObject(ref);
            pInputAssemblyState.push_back(ref);
        }
        // processing
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkPipelineInputAssemblyStateCreateInfo[size];
        std::copy(pInputAssemblyState.begin(), pInputAssemblyState.end(), copy);
        clazzInfo.pInputAssemblyState = copy;
    }

    void getpTessellationState(VkGraphicsPipelineCreateInfo &clazzInfo) {
        auto pTessellationStateArray = (jobjectArray) env->GetObjectField(obj,
                                                                          pTessellationStateField);
        if (pTessellationStateArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pTessellationStateArray);
        std::vector<VkPipelineTessellationStateCreateInfo> pTessellationState;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pTessellationStateArray,
                                                                i); // actual type is VkPipelineTessellationStateCreateInfo[];
            // experimental optimize accessor
            VkPipelineTessellationStateCreateInfoAccessor accessor(env, element);
            VkPipelineTessellationStateCreateInfo ref{};
            accessor.fromObject(ref);
            pTessellationState.push_back(ref);
        }
        // processing
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkPipelineTessellationStateCreateInfo[size];
        std::copy(pTessellationState.begin(), pTessellationState.end(), copy);
        clazzInfo.pTessellationState = copy;
    }

    void getpViewportState(VkGraphicsPipelineCreateInfo &clazzInfo) {
        auto pViewportStateArray = (jobjectArray) env->GetObjectField(obj, pViewportStateField);
        if (pViewportStateArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pViewportStateArray);
        std::vector<VkPipelineViewportStateCreateInfo> pViewportState;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pViewportStateArray,
                                                                i); // actual type is VkPipelineViewportStateCreateInfo[];
            // experimental optimize accessor
            VkPipelineViewportStateCreateInfoAccessor accessor(env, element);
            VkPipelineViewportStateCreateInfo ref{};
            accessor.fromObject(ref);
            pViewportState.push_back(ref);
        }
        // processing
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkPipelineViewportStateCreateInfo[size];
        std::copy(pViewportState.begin(), pViewportState.end(), copy);
        clazzInfo.pViewportState = copy;
    }

    void getpRasterizationState(VkGraphicsPipelineCreateInfo &clazzInfo) {
        auto pRasterizationStateArray = (jobjectArray) env->GetObjectField(obj,
                                                                           pRasterizationStateField);
        if (pRasterizationStateArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pRasterizationStateArray);
        std::vector<VkPipelineRasterizationStateCreateInfo> pRasterizationState;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pRasterizationStateArray,
                                                                i); // actual type is VkPipelineRasterizationStateCreateInfo[];
            // experimental optimize accessor
            VkPipelineRasterizationStateCreateInfoAccessor accessor(env, element);
            VkPipelineRasterizationStateCreateInfo ref{};
            accessor.fromObject(ref);
            pRasterizationState.push_back(ref);
        }
        // processing
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkPipelineRasterizationStateCreateInfo[size];
        std::copy(pRasterizationState.begin(), pRasterizationState.end(), copy);
        clazzInfo.pRasterizationState = copy;
    }

    void getpMultisampleState(VkGraphicsPipelineCreateInfo &clazzInfo) {
        auto pMultisampleStateArray = (jobjectArray) env->GetObjectField(obj,
                                                                         pMultisampleStateField);
        if (pMultisampleStateArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pMultisampleStateArray);
        std::vector<VkPipelineMultisampleStateCreateInfo> pMultisampleState;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pMultisampleStateArray,
                                                                i); // actual type is VkPipelineMultisampleStateCreateInfo[];
            // experimental optimize accessor
            VkPipelineMultisampleStateCreateInfoAccessor accessor(env, element);
            VkPipelineMultisampleStateCreateInfo ref{};
            accessor.fromObject(ref);
            pMultisampleState.push_back(ref);
        }
        // processing
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkPipelineMultisampleStateCreateInfo[size];
        std::copy(pMultisampleState.begin(), pMultisampleState.end(), copy);
        clazzInfo.pMultisampleState = copy;
    }

    void getpDepthStencilState(VkGraphicsPipelineCreateInfo &clazzInfo) {
        auto pDepthStencilStateArray = (jobjectArray) env->GetObjectField(obj,
                                                                          pDepthStencilStateField);
        if (pDepthStencilStateArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pDepthStencilStateArray);
        std::vector<VkPipelineDepthStencilStateCreateInfo> pDepthStencilState;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pDepthStencilStateArray,
                                                                i); // actual type is VkPipelineDepthStencilStateCreateInfo[];
            // experimental optimize accessor
            VkPipelineDepthStencilStateCreateInfoAccessor accessor(env, element);
            VkPipelineDepthStencilStateCreateInfo ref{};
            accessor.fromObject(ref);
            pDepthStencilState.push_back(ref);
        }
        // processing
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkPipelineDepthStencilStateCreateInfo[size];
        std::copy(pDepthStencilState.begin(), pDepthStencilState.end(), copy);
        clazzInfo.pDepthStencilState = copy;
    }

    void getpColorBlendState(VkGraphicsPipelineCreateInfo &clazzInfo) {
        auto pColorBlendStateArray = (jobjectArray) env->GetObjectField(obj, pColorBlendStateField);
        if (pColorBlendStateArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pColorBlendStateArray);
        std::vector<VkPipelineColorBlendStateCreateInfo> pColorBlendState;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pColorBlendStateArray,
                                                                i); // actual type is VkPipelineColorBlendStateCreateInfo[];
            // experimental optimize accessor
            VkPipelineColorBlendStateCreateInfoAccessor accessor(env, element);
            VkPipelineColorBlendStateCreateInfo ref{};
            accessor.fromObject(ref);
            pColorBlendState.push_back(ref);
        }
        // processing
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkPipelineColorBlendStateCreateInfo[size];
        std::copy(pColorBlendState.begin(), pColorBlendState.end(), copy);
        clazzInfo.pColorBlendState = copy;
    }

    void getpDynamicState(VkGraphicsPipelineCreateInfo &clazzInfo) {
        auto pDynamicStateArray = (jobjectArray) env->GetObjectField(obj, pDynamicStateField);
        if (pDynamicStateArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(pDynamicStateArray);
        std::vector<VkPipelineDynamicStateCreateInfo> pDynamicState;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pDynamicStateArray,
                                                                i); // actual type is VkPipelineDynamicStateCreateInfo[];
            // experimental optimize accessor
            VkPipelineDynamicStateCreateInfoAccessor accessor(env, element);
            VkPipelineDynamicStateCreateInfo ref{};
            accessor.fromObject(ref);
            pDynamicState.push_back(ref);
        }
        // processing
        // Make a copy of the object to ensure proper memory management;
        auto copy = new VkPipelineDynamicStateCreateInfo[size];
        std::copy(pDynamicState.begin(), pDynamicState.end(), copy);
        clazzInfo.pDynamicState = copy;
    }

    VkPipelineLayout getlayout() {
        return reinterpret_cast<VkPipelineLayout>(env->GetLongField(obj, layoutField)); // VkHandle
    }

    VkRenderPass getrenderPass() {
        return reinterpret_cast<VkRenderPass>(env->GetLongField(obj, renderPassField)); // VkHandle
    }

    uint32_t getsubpass() {
        return (uint32_t) (jint) env->GetIntField(obj, subpassField); // primitive
    }

    VkPipeline getbasePipelineHandle() {
        return reinterpret_cast<VkPipeline>(env->GetLongField(obj,
                                                              basePipelineHandleField)); // VkHandle
    }

    int32_t getbasePipelineIndex() {
        return (int32_t) (jint) env->GetIntField(obj, basePipelineIndexField); // primitive
    }

    uint32_t getstageCount() {
        return (uint32_t) (jint) env->GetIntField(obj, stageCountField); // primitive
    }

    void fromObject(VkGraphicsPipelineCreateInfo &clazzInfo) {
        clazzInfo.sType = getsType(); // Enum VkStructureType
        getpNext(clazzInfo); // Object void*
        clazzInfo.flags = getflags(); // Object uint32_t
        getpStages(clazzInfo);  // VkPipelineShaderStageCreateInfo Object Array
        getpVertexInputState(clazzInfo);  // VkPipelineVertexInputStateCreateInfo Object Array
        getpInputAssemblyState(clazzInfo);  // VkPipelineInputAssemblyStateCreateInfo Object Array
        getpTessellationState(clazzInfo);  // VkPipelineTessellationStateCreateInfo Object Array
        getpViewportState(clazzInfo);  // VkPipelineViewportStateCreateInfo Object Array
        getpRasterizationState(clazzInfo);  // VkPipelineRasterizationStateCreateInfo Object Array
        getpMultisampleState(clazzInfo);  // VkPipelineMultisampleStateCreateInfo Object Array
        getpDepthStencilState(clazzInfo);  // VkPipelineDepthStencilStateCreateInfo Object Array
        getpColorBlendState(clazzInfo);  // VkPipelineColorBlendStateCreateInfo Object Array
        getpDynamicState(clazzInfo);  // VkPipelineDynamicStateCreateInfo Object Array
        clazzInfo.layout = getlayout(); // VkHandle
        clazzInfo.renderPass = getrenderPass(); // VkHandle
        clazzInfo.subpass = getsubpass(); // Object uint32_t
        clazzInfo.basePipelineHandle = getbasePipelineHandle(); // VkHandle
        clazzInfo.basePipelineIndex = getbasePipelineIndex(); // Object int32_t
        clazzInfo.stageCount = getstageCount(); // Object uint32_t
    }

    ~VkGraphicsPipelineCreateInfoAccessor() {
    }

};
