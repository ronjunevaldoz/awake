/*
 *  VkGraphicsPipelineCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
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
    VkGraphicsPipelineCreateInfoAccessor(JNIEnv *env, jobject obj) {
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
                                                 "Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineVertexInputStateCreateInfo;");
        pInputAssemblyStateField = env->GetFieldID(clazz, "pInputAssemblyState",
                                                   "Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineInputAssemblyStateCreateInfo;");
        pTessellationStateField = env->GetFieldID(clazz, "pTessellationState",
                                                  "Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineTessellationStateCreateInfo;");
        pViewportStateField = env->GetFieldID(clazz, "pViewportState",
                                              "Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineViewportStateCreateInfo;");
        pRasterizationStateField = env->GetFieldID(clazz, "pRasterizationState",
                                                   "Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineRasterizationStateCreateInfo;");
        pMultisampleStateField = env->GetFieldID(clazz, "pMultisampleState",
                                                 "Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineMultisampleStateCreateInfo;");
        pDepthStencilStateField = env->GetFieldID(clazz, "pDepthStencilState",
                                                  "Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineDepthStencilStateCreateInfo;");
        pColorBlendStateField = env->GetFieldID(clazz, "pColorBlendState",
                                                "Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineColorBlendStateCreateInfo;");
        pDynamicStateField = env->GetFieldID(clazz, "pDynamicState",
                                             "Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineDynamicStateCreateInfo;");
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

    void *getpNext() {
        return (void *) (jobject) env->GetObjectField(obj, pNextField); // Object??
    }

    uint32_t getflags() {
        return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
    }

    std::vector<VkPipelineShaderStageCreateInfo> getpStages() {
        auto pStagesArray = (jobjectArray) env->GetObjectField(obj, pStagesField);
        if (pStagesArray == nullptr) {
            return {};
        }
        auto size = env->GetArrayLength(pStagesArray);
        std::vector<VkPipelineShaderStageCreateInfo> array;
        for (int i = 0; i < size; ++i) {
            auto element = (jobject) env->GetObjectArrayElement(pStagesArray,
                                                                i); // actual type is VkPipelineShaderStageCreateInfo[];
            // experimental optimize accessor
            VkPipelineShaderStageCreateInfoAccessor accessor(env, element);
            array.push_back(accessor.fromObject());
        }
        return array;
    }

    VkPipelineVertexInputStateCreateInfo getpVertexInputState() {
        auto pVertexInputStateObj = (jobject) env->GetObjectField(obj, pVertexInputStateField);
        VkPipelineVertexInputStateCreateInfoAccessor accessor(env, pVertexInputStateObj);
        if (pVertexInputStateObj == nullptr) {
            return {};
        }
        return (VkPipelineVertexInputStateCreateInfo) (accessor.fromObject()); // Object is null, should be accessed by an accessor
    }

    VkPipelineInputAssemblyStateCreateInfo getpInputAssemblyState() {
        auto pInputAssemblyStateObj = (jobject) env->GetObjectField(obj, pInputAssemblyStateField);
        VkPipelineInputAssemblyStateCreateInfoAccessor accessor(env, pInputAssemblyStateObj);
        if (pInputAssemblyStateObj == nullptr) {
            return {};
        }
        return (VkPipelineInputAssemblyStateCreateInfo) (accessor.fromObject()); // Object is null, should be accessed by an accessor
    }

    VkPipelineTessellationStateCreateInfo getpTessellationState() {
        auto pTessellationStateObj = (jobject) env->GetObjectField(obj, pTessellationStateField);
        VkPipelineTessellationStateCreateInfoAccessor accessor(env, pTessellationStateObj);
        if (pTessellationStateObj == nullptr) {
            return {};
        }
        return (VkPipelineTessellationStateCreateInfo) (accessor.fromObject()); // Object is null, should be accessed by an accessor
    }

    VkPipelineViewportStateCreateInfo getpViewportState() {
        auto pViewportStateObj = (jobject) env->GetObjectField(obj, pViewportStateField);
        VkPipelineViewportStateCreateInfoAccessor accessor(env, pViewportStateObj);
        if (pViewportStateObj == nullptr) {
            return {};
        }
        return (VkPipelineViewportStateCreateInfo) (accessor.fromObject()); // Object is null, should be accessed by an accessor
    }

    VkPipelineRasterizationStateCreateInfo getpRasterizationState() {
        auto pRasterizationStateObj = (jobject) env->GetObjectField(obj, pRasterizationStateField);
        VkPipelineRasterizationStateCreateInfoAccessor accessor(env, pRasterizationStateObj);
        if (pRasterizationStateObj == nullptr) {
            return {};
        }
        return (VkPipelineRasterizationStateCreateInfo) (accessor.fromObject()); // Object is null, should be accessed by an accessor
    }

    VkPipelineMultisampleStateCreateInfo getpMultisampleState() {
        auto pMultisampleStateObj = (jobject) env->GetObjectField(obj, pMultisampleStateField);
        VkPipelineMultisampleStateCreateInfoAccessor accessor(env, pMultisampleStateObj);
        if (pMultisampleStateObj == nullptr) {
            return {};
        }
        return (VkPipelineMultisampleStateCreateInfo) (accessor.fromObject()); // Object is null, should be accessed by an accessor
    }

    VkPipelineDepthStencilStateCreateInfo getpDepthStencilState() {
        auto pDepthStencilStateObj = (jobject) env->GetObjectField(obj, pDepthStencilStateField);
        VkPipelineDepthStencilStateCreateInfoAccessor accessor(env, pDepthStencilStateObj);
        if (pDepthStencilStateObj == nullptr) {
            return {};
        }
        return (VkPipelineDepthStencilStateCreateInfo) (accessor.fromObject()); // Object is null, should be accessed by an accessor
    }

    VkPipelineColorBlendStateCreateInfo getpColorBlendState() {
        auto pColorBlendStateObj = (jobject) env->GetObjectField(obj, pColorBlendStateField);
        VkPipelineColorBlendStateCreateInfoAccessor accessor(env, pColorBlendStateObj);
        if (pColorBlendStateObj == nullptr) {
            return {};
        }
        return (VkPipelineColorBlendStateCreateInfo) (accessor.fromObject()); // Object is null, should be accessed by an accessor
    }

    VkPipelineDynamicStateCreateInfo getpDynamicState() {
        auto pDynamicStateObj = (jobject) env->GetObjectField(obj, pDynamicStateField);
        VkPipelineDynamicStateCreateInfoAccessor accessor(env, pDynamicStateObj);
        if (pDynamicStateObj == nullptr) {
            return {};
        }
        return (VkPipelineDynamicStateCreateInfo) (accessor.fromObject()); // Object is null, should be accessed by an accessor
    }

    uint64_t getlayout() {
        return (uint64_t) (jlong) env->GetLongField(obj, layoutField); // primitive
    }

    uint64_t getrenderPass() {
        return (uint64_t) (jlong) env->GetLongField(obj, renderPassField); // primitive
    }

    uint32_t getsubpass() {
        return (uint32_t) (jint) env->GetIntField(obj, subpassField); // primitive
    }

    uint64_t getbasePipelineHandle() {
        return (uint64_t) (jlong) env->GetLongField(obj, basePipelineHandleField); // primitive
    }

    int32_t getbasePipelineIndex() {
        return (int32_t) (jint) env->GetIntField(obj, basePipelineIndexField); // primitive
    }

    uint32_t getstageCount() {
        return (uint32_t) (jint) env->GetIntField(obj, stageCountField); // primitive
    }

    VkGraphicsPipelineCreateInfo fromObject() {
        VkGraphicsPipelineCreateInfo clazzInfo{};
        clazzInfo.sType = getsType(); // Object
        clazzInfo.pNext = getpNext(); // Object
        clazzInfo.flags = getflags(); // Object
        clazzInfo.pStages = getpStages().data(); // Object Array
        auto pVertexInputStatePtr = getpVertexInputState();
        clazzInfo.pVertexInputState = pVertexInputStatePtr; // Pointer
        auto pInputAssemblyStatePtr = getpInputAssemblyState();
        clazzInfo.pInputAssemblyState = pInputAssemblyStatePtr; // Pointer
        auto pTessellationStatePtr = getpTessellationState();
        clazzInfo.pTessellationState = pTessellationStatePtr; // Pointer
        auto pViewportStatePtr = getpViewportState();
        clazzInfo.pViewportState = pViewportStatePtr; // Pointer
        auto pRasterizationStatePtr = getpRasterizationState();
        clazzInfo.pRasterizationState = pRasterizationStatePtr; // Pointer
        auto pMultisampleStatePtr = getpMultisampleState();
        clazzInfo.pMultisampleState = pMultisampleStatePtr; // Pointer
        auto pDepthStencilStatePtr = getpDepthStencilState();
        clazzInfo.pDepthStencilState = &pDepthStencilStatePtr; // Pointer
        auto pColorBlendStatePtr = getpColorBlendState();
        clazzInfo.pColorBlendState = pColorBlendStatePtr; // Pointer
        auto pDynamicStatePtr = getpDynamicState();
        clazzInfo.pDynamicState = pDynamicStatePtr; // Pointer
        clazzInfo.layout = getlayout(); // Object
        clazzInfo.renderPass = getrenderPass(); // Object
        clazzInfo.subpass = getsubpass(); // Object
        clazzInfo.basePipelineHandle = getbasePipelineHandle(); // Object
        clazzInfo.basePipelineIndex = getbasePipelineIndex(); // Object
        clazzInfo.stageCount = getstageCount(); // Object
        return clazzInfo;
    }

    ~VkGraphicsPipelineCreateInfoAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
