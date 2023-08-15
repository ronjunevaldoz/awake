/* 
 * VkExtent2DConverter.cpp
 * Created by Ron June Valdoz on Mon Aug 07 23:50:29 PST 2023
 */

#include <vector>
#include "VkExtent2DConverter.h"
#include "enum_utils.h"


VkExtent2DConverter::VkExtent2DConverter(JNIEnv *env) {
    this->env = env;
    clazz = env->FindClass("io/github/ronjunevaldoz/awake/vulkan/models/VkExtent2D");

    widthField = env->GetFieldID(clazz, "width", "I");
    heightField = env->GetFieldID(clazz, "height", "I");
}

VkExtent2D
VkExtent2DConverter::fromObject(jobject pCreateInfo) {
    if (!env->IsInstanceOf(pCreateInfo, clazz)) {
        throw std::runtime_error("Invalid object. Expected VkExtent2D.");
    }
    auto widthInt = env->GetIntField(pCreateInfo, widthField);
    auto heightInt = env->GetIntField(pCreateInfo, heightField);


    VkExtent2D createInfo;
    createInfo.width = static_cast<uint32_t>(widthInt); // primitive type int
    createInfo.height = static_cast<uint32_t>(heightInt); // primitive type int


    return createInfo;
}

jobject VkExtent2DConverter::toObject(VkExtent2D &vulkan) {
    // TODO not yet implemented
    return nullptr;
}

VkExtent2DConverter::~VkExtent2DConverter() {
    // TODO not yet implemented
    widthField = nullptr;
    heightField = nullptr;
}