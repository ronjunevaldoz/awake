/*
 *  VkPipelineInputAssemblyStateCreateInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
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
    VkPipelineInputAssemblyStateCreateInfoAccessor(JNIEnv *env, jobject obj) {
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

    void *getpNext() {
        return (void *) (jobject) env->GetObjectField(obj, pNextField); // Object??
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

    VkPipelineInputAssemblyStateCreateInfo fromObject() {
        VkPipelineInputAssemblyStateCreateInfo clazzInfo{};
        clazzInfo.sType = getsType(); // Object
        clazzInfo.pNext = getpNext(); // Object
        clazzInfo.flags = getflags(); // Object
        clazzInfo.topology = gettopology(); // Object
        clazzInfo.primitiveRestartEnable = getprimitiveRestartEnable(); // Object
        return clazzInfo;
    }

    ~VkPipelineInputAssemblyStateCreateInfoAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
