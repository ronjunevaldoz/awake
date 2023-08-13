/*
 *  VkApplicationInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz */

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkApplicationInfoAccessor {
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
    jfieldID pApplicationNameField;
private:
    jfieldID applicationVersionField;
private:
    jfieldID pEngineNameField;
private:
    jfieldID engineVersionField;
private:
    jfieldID apiVersionField;
public:
    VkApplicationInfoAccessor(JNIEnv *env, jobject &obj) {
        this->env = env;
        this->obj = env->NewGlobalRef(obj);
        clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
        sTypeField = env->GetFieldID(clazz, "sType",
                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkStructureType;");
        pNextField = env->GetFieldID(clazz, "pNext", "Ljava/lang/Object;");
        pApplicationNameField = env->GetFieldID(clazz, "pApplicationName", "Ljava/lang/String;");
        applicationVersionField = env->GetFieldID(clazz, "applicationVersion", "I");
        pEngineNameField = env->GetFieldID(clazz, "pEngineName", "Ljava/lang/String;");
        engineVersionField = env->GetFieldID(clazz, "engineVersion", "I");
        apiVersionField = env->GetFieldID(clazz, "apiVersion", "I");
    }

    VkStructureType getsType() {
        auto sTypeEnum = (jobject) env->GetObjectField(obj, sTypeField);
        return (VkStructureType) enum_utils::getEnumFromObject(env, sTypeEnum);
    }

    void getpNext(VkApplicationInfo &clazzInfo) {
        auto ref = (void *) (jobject) env->GetObjectField(obj, pNextField); // Any Object
        clazzInfo.pNext = ref;
    }

    void getpApplicationName(VkApplicationInfo &clazzInfo) {
        auto pApplicationNameObj = (jstring) env->GetObjectField(obj, pApplicationNameField);
        auto str = (const char *) env->GetStringUTFChars(pApplicationNameObj, nullptr);
        auto result = strdup(str); // Allocate memory and copy the string
        env->ReleaseStringUTFChars(pApplicationNameObj, str); // Release the local string reference
        clazzInfo.pApplicationName = result;
    }

    uint32_t getapplicationVersion() {
        return (uint32_t) (jint) env->GetIntField(obj, applicationVersionField); // primitive
    }

    void getpEngineName(VkApplicationInfo &clazzInfo) {
        auto pEngineNameObj = (jstring) env->GetObjectField(obj, pEngineNameField);
        auto str = (const char *) env->GetStringUTFChars(pEngineNameObj, nullptr);
        auto result = strdup(str); // Allocate memory and copy the string
        env->ReleaseStringUTFChars(pEngineNameObj, str); // Release the local string reference
        clazzInfo.pEngineName = result;
    }

    uint32_t getengineVersion() {
        return (uint32_t) (jint) env->GetIntField(obj, engineVersionField); // primitive
    }

    uint32_t getapiVersion() {
        return (uint32_t) (jint) env->GetIntField(obj, apiVersionField); // primitive
    }

    void fromObject(VkApplicationInfo &clazzInfo) {
        clazzInfo.sType = getsType(); // Enum VkStructureType
        getpNext(clazzInfo); // Object void*
        getpApplicationName(clazzInfo); // Object const char*
        clazzInfo.applicationVersion = getapplicationVersion(); // Object uint32_t
        getpEngineName(clazzInfo); // Object const char*
        clazzInfo.engineVersion = getengineVersion(); // Object uint32_t
        clazzInfo.apiVersion = getapiVersion(); // Object uint32_t
    }

    ~VkApplicationInfoAccessor() {
    }

};
