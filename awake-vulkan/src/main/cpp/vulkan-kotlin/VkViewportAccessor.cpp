/*
 *  VkViewportAccessor.cpp
 *  Vulkan accessor for VkViewport
 *  Created by Ron June Valdoz */

#include  <includes/VkViewportAccessor.h>

VkViewportAccessor::VkViewportAccessor(JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    xField = env->GetFieldID(clazz, "x", "F");
    yField = env->GetFieldID(clazz, "y", "F");
    widthField = env->GetFieldID(clazz, "width", "F");
    heightField = env->GetFieldID(clazz, "height", "F");
    minDepthField = env->GetFieldID(clazz, "minDepth", "F");
    maxDepthField = env->GetFieldID(clazz, "maxDepth", "F");
}

float
VkViewportAccessor::getminDepth() {
    return (float) (jfloat) env->GetFloatField(obj, minDepthField); // primitive
}

float
VkViewportAccessor::getheight() {
    return (float) (jfloat) env->GetFloatField(obj, heightField); // primitive
}

float
VkViewportAccessor::getx() {
    return (float) (jfloat) env->GetFloatField(obj, xField); // primitive
}

void
VkViewportAccessor::fromObject(VkViewport &clazzInfo) {
    clazzInfo.x = getx(); // Object float
    clazzInfo.y = gety(); // Object float
    clazzInfo.width = getwidth(); // Object float
    clazzInfo.height = getheight(); // Object float
    clazzInfo.minDepth = getminDepth(); // Object float
    clazzInfo.maxDepth = getmaxDepth(); // Object float
}

float
VkViewportAccessor::gety() {
    return (float) (jfloat) env->GetFloatField(obj, yField); // primitive
}

float
VkViewportAccessor::getwidth() {
    return (float) (jfloat) env->GetFloatField(obj, widthField); // primitive
}

float
VkViewportAccessor::getmaxDepth() {
    return (float) (jfloat) env->GetFloatField(obj, maxDepthField); // primitive
}

VkViewportAccessor::~VkViewportAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

