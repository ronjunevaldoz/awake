/*
 *  VkPipelineInputAssemblyStateCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkPipelineInputAssemblyStateCreateInfoAccessor {
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
    jfieldID topologyField;
private:
    jfieldID primitiveRestartEnableField;
public:
    VkPipelineInputAssemblyStateCreateInfoAccessor(JNIEnv *env, jobject &obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        sTypeField = env->GetFieldID(clazz, "sType",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
        pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
        flagsField = env->GetFieldID(clazz, "flags", "I");
        topologyField = env->GetFieldID(clazz, "topology",
                                        "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkPrimitiveTopology;");
        primitiveRestartEnableField = env->GetFieldID(clazz, "primitiveRestartEnable", "Z");
    }

    VkStructureType getsType() {
        auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
        return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
    }

    void getpNext(VkPipelineInputAssemblyStateCreateInfo &clazzInfo) {
        auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
        clazzInfo.pNext = ref;
    }

    uint32_t getflags() {
        return (uint32_t) (jint) env->GetIntField(obj, flagsField); // primitive
    }

    VkPrimitiveTopology gettopology() {
        auto topologyEnum = (jobject) env->GetObjectField(obj, topologyField);
        return (VkPrimitiveTopology) enum_utils::getEnumFromObject(env, topologyEnum);
    }

    bool getprimitiveRestartEnable() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      primitiveRestartEnableField); // primitive
    }

    void fromObject(VkPipelineInputAssemblyStateCreateInfo &clazzInfo) {
        clazzInfo.sType = getsType(); // Enum VkStructureType
        getpNext(clazzInfo); // Object void*
        clazzInfo.flags = getflags(); // Object uint32_t
        clazzInfo.topology = gettopology(); // Enum VkPrimitiveTopology
        clazzInfo.primitiveRestartEnable = getprimitiveRestartEnable(); // Object bool
    }

    ~VkPipelineInputAssemblyStateCreateInfoAccessor() {
    }

};
