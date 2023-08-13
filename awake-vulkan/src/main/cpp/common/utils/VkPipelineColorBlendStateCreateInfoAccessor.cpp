/*
 *  VkPipelineColorBlendStateCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
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
    VkPipelineColorBlendStateCreateInfoAccessor(JNIEnv *env, jobject &obj) {
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

    void getpNext(VkPipelineColorBlendStateCreateInfo &clazzInfo) {
        auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
        clazzInfo.pNext = ref;
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

    void getpAttachments(VkPipelineColorBlendStateCreateInfo &clazzInfo) {
        auto pAttachmentsObj = (jobject) env->GetObjectField(obj, pAttachmentsField);
        if (pAttachmentsObj == nullptr) {
            return;
        }
        VkPipelineColorBlendAttachmentStateAccessor accessor(env, pAttachmentsObj);
        VkPipelineColorBlendAttachmentState ref{};
        accessor.fromObject(ref);
        clazzInfo.pAttachments = &ref;
    }

    void getblendConstants(VkPipelineColorBlendStateCreateInfo &clazzInfo) {
        auto blendConstantsArray = (jfloatArray) env->GetObjectField(obj, blendConstantsField);
        if (blendConstantsArray == nullptr) {
            return;
        }
        auto size = env->GetArrayLength(blendConstantsArray);
        // primitive array?
        std::vector<float> blendConstants(size);
        env->GetFloatArrayRegion(blendConstantsArray, 0, size,
                                 reinterpret_cast<jfloat *>(blendConstants.data()));
        // processing
        std::copy(blendConstants.begin(), blendConstants.end(),
                  clazzInfo.blendConstants); // fixed array size
    }

    void fromObject(VkPipelineColorBlendStateCreateInfo &clazzInfo) {
        clazzInfo.sType = getsType(); // Enum VkStructureType
        getpNext(clazzInfo); // Object void*
        clazzInfo.flags = getflags(); // Object uint32_t
        clazzInfo.logicOpEnable = getlogicOpEnable(); // Object bool
        clazzInfo.logicOp = getlogicOp(); // Enum VkLogicOp
        clazzInfo.attachmentCount = getattachmentCount(); // Object uint32_t
        getpAttachments(clazzInfo); // Pointer
        getblendConstants(clazzInfo);  // float Object Array
    }

    ~VkPipelineColorBlendStateCreateInfoAccessor() {
    }

};
