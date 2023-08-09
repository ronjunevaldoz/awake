/*
 *  VkApplicationInfoAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
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
    VkApplicationInfoAccessor(JNIEnv *env, jobject obj) {
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

    void *getpNext() {
        return (void *) (jobject) env->GetObjectField(obj, pNextField); // Object??
    }

    const char *getpApplicationName() {
        auto pApplicationNameObj = (jstring) env->GetObjectField(obj, pApplicationNameField);
        auto str = (const char *) env->GetStringUTFChars(pApplicationNameObj, nullptr);
        auto result = strdup(str); // Allocate memory and copy the string
        env->ReleaseStringUTFChars(pApplicationNameObj, str); // Release the local string reference
        return result;
    }

    uint32_t getapplicationVersion() {
        return (uint32_t) (jint) env->GetIntField(obj, applicationVersionField); // primitive
    }

    const char *getpEngineName() {
        auto pEngineNameObj = (jstring) env->GetObjectField(obj, pEngineNameField);
        auto str = (const char *) env->GetStringUTFChars(pEngineNameObj, nullptr);
        auto result = strdup(str); // Allocate memory and copy the string
        env->ReleaseStringUTFChars(pEngineNameObj, str); // Release the local string reference
        return result;
    }

    uint32_t getengineVersion() {
        return (uint32_t) (jint) env->GetIntField(obj, engineVersionField); // primitive
    }

    uint32_t getapiVersion() {
        return (uint32_t) (jint) env->GetIntField(obj, apiVersionField); // primitive
    }

    VkApplicationInfo fromObject() {
        VkApplicationInfo clazzInfo{};
        clazzInfo.sType = getsType(); // Object
        clazzInfo.pNext = getpNext(); // Object
        clazzInfo.pApplicationName = getpApplicationName(); // Object
        clazzInfo.applicationVersion = getapplicationVersion(); // Object
        clazzInfo.pEngineName = getpEngineName(); // Object
        clazzInfo.engineVersion = getengineVersion(); // Object
        clazzInfo.apiVersion = getapiVersion(); // Object
        return clazzInfo;
    }

    ~VkApplicationInfoAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
