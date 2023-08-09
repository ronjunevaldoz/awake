/*
 *  VkPipelineColorBlendStateCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <enum_utils.h>
#include <VkPipelineColorBlendAttachmentStateAccessor.cpp>

class VkPipelineColorBlendStateCreateInfoAccessor {
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
    jfieldID logicOpEnableField;
private:
    jfieldID logicOpField;
private:
    jfieldID attachmentCountField;
private:
    jfieldID pAttachmentsField;
private:
    jfieldID blendConstantsField;
public:
    VkPipelineColorBlendStateCreateInfoAccessor(JNIEnv *env, jobject obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        sTypeField = env->GetFieldID(clazz, "sType",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
        pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
        flagsField = env->GetFieldID(clazz, "flags", "I");
        logicOpEnableField = env->GetFieldID(clazz, "logicOpEnable", "Z");
        logicOpField = env->GetFieldID(clazz, "logicOp",
                                       "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkLogicOp;");
        attachmentCountField = env->GetFieldID(clazz, "attachmentCount", "I");
        pAttachmentsField = env->GetFieldID(clazz, "pAttachments",
                                            "Lio/github/ronjunevaldoz/awake/vulkan/models/info/pipeline/VkPipelineColorBlendAttachmentState;");
        blendConstantsField = env->GetFieldID(clazz, "blendConstants", "[F");
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

    bool getlogicOpEnable() {
        return (bool) (jboolean) env->GetBooleanField(obj, logicOpEnableField); // primitive
    }

    VkLogicOp getlogicOp() {
        auto logicOpEnum = (jobject) env->GetObjectField(obj, logicOpField);
        return (VkLogicOp) enum_utils::getEnumFromObject(env, logicOpEnum);
    }

    uint32_t getattachmentCount() {
        return (uint32_t) (jint) env->GetIntField(obj, attachmentCountField); // primitive
    }

    VkPipelineColorBlendAttachmentState getpAttachments() {
        auto pAttachmentsObj = (jobject) env->GetObjectField(obj, pAttachmentsField);
        VkPipelineColorBlendAttachmentStateAccessor accessor(env, pAttachmentsObj);
        if (pAttachmentsObj == nullptr) {
            return {};
        }
        return (VkPipelineColorBlendAttachmentState) (accessor.fromObject()); // Object is null, should be accessed by an accessor
    }

    std::vector<float> getblendConstants() {
        auto blendConstantsArray = (jfloatArray) env->GetObjectField(obj, blendConstantsField);
        if (blendConstantsArray == nullptr) {
            return {};
        }
        auto size = env->GetArrayLength(blendConstantsArray);
        std::vector<float> array(size);
        env->GetFloatArrayRegion(blendConstantsArray, 0, size,
                                 reinterpret_cast<jfloat *>(array.data()));
        return array;
    }

    VkPipelineColorBlendStateCreateInfo fromObject() {
        VkPipelineColorBlendStateCreateInfo clazzInfo{};
        clazzInfo.sType = getsType(); // Object
        clazzInfo.pNext = getpNext(); // Object
        clazzInfo.flags = getflags(); // Object
        clazzInfo.logicOpEnable = getlogicOpEnable(); // Object
        clazzInfo.logicOp = getlogicOp(); // Object
        clazzInfo.attachmentCount = getattachmentCount(); // Object
        auto pAttachmentsPtr = getpAttachments();
        clazzInfo.pAttachments = pAttachmentsPtr; // Pointer
        auto blendConstants = getblendConstants();  // float Primitive Array
        std::copy(blendConstants.begin(), blendConstants.end(), clazzInfo.blendConstants);
        return clazzInfo;
    }

    ~VkPipelineColorBlendStateCreateInfoAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
