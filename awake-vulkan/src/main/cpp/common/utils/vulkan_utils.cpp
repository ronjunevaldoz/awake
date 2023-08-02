//
// Created by Ron June Valdoz on 7/23/23.
//

#include <algorithm>
#include <vector>
#include <android/log.h>
#include <string>
#include <android/native_window_jni.h>
#include "vulkan_utils.h"
#include "enum_utils.h"
#include "VkImageViewCreateInfoConverter.h"


std::vector<const char *>
getEnabledDeviceExtensions_fromObjectList(JNIEnv *env, jobject pListObject) {
    jclass listClass = env->GetObjectClass(pListObject);
    jmethodID getMethodID = env->GetMethodID(listClass, "get",
                                             "(I)Ljava/lang/Object;");
    jmethodID sizeMethodID = env->GetMethodID(listClass, "size", "()I");

    // Get the size of the List
    jint queueCreateInfoListSize = env->CallIntMethod(pListObject, sizeMethodID);
    std::vector<const char *> enabledExtensions;
    for (int i = 0; i < queueCreateInfoListSize; ++i) {
        // Get the element object at the specified index
        auto elementString = (jstring) env->CallObjectMethod(pListObject,
                                                             getMethodID, i);
        const char *str = env->GetStringUTFChars(elementString, nullptr);

        enabledExtensions.push_back(str);
//        env->ReleaseStringUTFChars(elementString, str); // TODO check if needed to freeup memory
//        env->DeleteLocalRef(elementString); // TODO check if needed to freeup memory
    }

    env->DeleteLocalRef(listClass);
    return enabledExtensions;
}

namespace vulkan_utils {
    class VkPhysicalDeviceFeaturesJava {
    private:
        jclass pdfClass;
        jmethodID pdfConstructor;
        jfieldID robustBufferAccessField;
        jfieldID fullDrawIndexUint32Field;
        jfieldID imageCubeArrayField;
        jfieldID independentBlendField;
        jfieldID geometryShaderField;
        jfieldID tessellationShaderField;
        jfieldID sampleRateShadingField;
        jfieldID dualSrcBlendField;
        jfieldID logicOpField;
        jfieldID multiDrawIndirectField;
        jfieldID drawIndirectFirstInstanceField;
        jfieldID depthClampField;
        jfieldID depthBiasClampField;
        jfieldID fillModeNonSolidField;
        jfieldID depthBoundsField;
        jfieldID wideLinesField;
        jfieldID largePointsField;
        jfieldID alphaToOneField;
        jfieldID multiViewportField;
        jfieldID samplerAnisotropyField;
        jfieldID textureCompressionETC2Field;
        jfieldID textureCompressionASTC_LDRField;
        jfieldID textureCompressionBCField;
        jfieldID occlusionQueryPreciseField;
        jfieldID pipelineStatisticsQueryField;
        jfieldID vertexPipelineStoresAndAtomicsField;
        jfieldID fragmentStoresAndAtomicsField;
        jfieldID shaderTessellationAndGeometryPointSizeField;
        jfieldID shaderImageGatherExtendedField;
        jfieldID shaderStorageImageExtendedFormatsField;
        jfieldID shaderStorageImageMultisampleField;
        jfieldID shaderStorageImageReadWithoutFormatField;
        jfieldID shaderStorageImageWriteWithoutFormatField;
        jfieldID shaderUniformBufferArrayDynamicIndexingField;
        jfieldID shaderSampledImageArrayDynamicIndexingField;
        jfieldID shaderStorageBufferArrayDynamicIndexingField;
        jfieldID shaderStorageImageArrayDynamicIndexingField;
        jfieldID shaderClipDistanceField;
        jfieldID shaderCullDistanceField;
        jfieldID shaderFloat64Field;
        jfieldID shaderInt64Field;
        jfieldID shaderInt16Field;
        jfieldID shaderResourceResidencyField;
        jfieldID shaderResourceMinLodField;
        jfieldID sparseBindingField;
        jfieldID sparseResidencyBufferField;
        jfieldID sparseResidencyImage2DField;
        jfieldID sparseResidencyImage3DField;
        jfieldID sparseResidency2SamplesField;
        jfieldID sparseResidency4SamplesField;
        jfieldID sparseResidency8SamplesField;
        jfieldID sparseResidency16SamplesField;
        jfieldID sparseResidencyAliasedField;
        jfieldID variableMultisampleRateField;
        jfieldID inheritedQueriesField;

    public:
        explicit VkPhysicalDeviceFeaturesJava(JNIEnv *env) {
            pdfClass = env->FindClass(
                    "io/github/ronjunevaldoz/awake/vulkan/physicaldevice/VkPhysicalDeviceFeatures");

            pdfConstructor = env->GetMethodID(pdfClass, "<init>", "()V");


            robustBufferAccessField = env->GetFieldID(pdfClass, "robustBufferAccess", "Z");
            fullDrawIndexUint32Field = env->GetFieldID(pdfClass, "fullDrawIndexUint32", "Z");
            imageCubeArrayField = env->GetFieldID(pdfClass, "imageCubeArray", "Z");
            independentBlendField = env->GetFieldID(pdfClass, "independentBlend", "Z");
            geometryShaderField = env->GetFieldID(pdfClass, "geometryShader", "Z");
            tessellationShaderField = env->GetFieldID(pdfClass, "tessellationShader", "Z");
            sampleRateShadingField = env->GetFieldID(pdfClass, "sampleRateShading", "Z");
            dualSrcBlendField = env->GetFieldID(pdfClass, "dualSrcBlend", "Z");
            logicOpField = env->GetFieldID(pdfClass, "logicOp", "Z");
            multiDrawIndirectField = env->GetFieldID(pdfClass, "multiDrawIndirect", "Z");
            drawIndirectFirstInstanceField = env->GetFieldID(pdfClass,
                                                             "drawIndirectFirstInstance",
                                                             "Z");
            depthClampField = env->GetFieldID(pdfClass, "depthClamp", "Z");
            depthBiasClampField = env->GetFieldID(pdfClass, "depthBiasClamp", "Z");
            fillModeNonSolidField = env->GetFieldID(pdfClass, "fillModeNonSolid", "Z");
            depthBoundsField = env->GetFieldID(pdfClass, "depthBounds", "Z");
            wideLinesField = env->GetFieldID(pdfClass, "wideLines", "Z");
            largePointsField = env->GetFieldID(pdfClass, "largePoints", "Z");
            alphaToOneField = env->GetFieldID(pdfClass, "alphaToOne", "Z");
            multiViewportField = env->GetFieldID(pdfClass, "multiViewport", "Z");
            samplerAnisotropyField = env->GetFieldID(pdfClass, "samplerAnisotropy", "Z");
            textureCompressionETC2Field = env->GetFieldID(pdfClass, "textureCompressionETC2",
                                                          "Z");
            textureCompressionASTC_LDRField = env->GetFieldID(pdfClass,
                                                              "textureCompressionASTC_LDR",
                                                              "Z");
            textureCompressionBCField = env->GetFieldID(pdfClass, "textureCompressionBC", "Z");
            occlusionQueryPreciseField = env->GetFieldID(pdfClass, "occlusionQueryPrecise",
                                                         "Z");
            pipelineStatisticsQueryField = env->GetFieldID(pdfClass, "pipelineStatisticsQuery",
                                                           "Z");
            vertexPipelineStoresAndAtomicsField = env->GetFieldID(pdfClass,
                                                                  "vertexPipelineStoresAndAtomics",
                                                                  "Z");
            fragmentStoresAndAtomicsField = env->GetFieldID(pdfClass,
                                                            "fragmentStoresAndAtomics",
                                                            "Z");
            shaderTessellationAndGeometryPointSizeField = env->GetFieldID(pdfClass,
                                                                          "shaderTessellationAndGeometryPointSize",
                                                                          "Z");
            shaderImageGatherExtendedField = env->GetFieldID(pdfClass,
                                                             "shaderImageGatherExtended",
                                                             "Z");
            shaderStorageImageExtendedFormatsField = env->GetFieldID(pdfClass,
                                                                     "shaderStorageImageExtendedFormats",
                                                                     "Z");
            shaderStorageImageMultisampleField = env->GetFieldID(pdfClass,
                                                                 "shaderStorageImageMultisample",
                                                                 "Z");
            shaderStorageImageReadWithoutFormatField = env->GetFieldID(pdfClass,
                                                                       "shaderStorageImageReadWithoutFormat",
                                                                       "Z");
            shaderStorageImageWriteWithoutFormatField = env->GetFieldID(pdfClass,
                                                                        "shaderStorageImageWriteWithoutFormat",
                                                                        "Z");
            shaderUniformBufferArrayDynamicIndexingField = env->GetFieldID(pdfClass,
                                                                           "shaderUniformBufferArrayDynamicIndexing",
                                                                           "Z");
            shaderSampledImageArrayDynamicIndexingField = env->GetFieldID(pdfClass,
                                                                          "shaderSampledImageArrayDynamicIndexing",
                                                                          "Z");
            shaderStorageBufferArrayDynamicIndexingField = env->GetFieldID(pdfClass,
                                                                           "shaderStorageBufferArrayDynamicIndexing",
                                                                           "Z");
            shaderStorageImageArrayDynamicIndexingField = env->GetFieldID(pdfClass,
                                                                          "shaderStorageImageArrayDynamicIndexing",
                                                                          "Z");
            shaderClipDistanceField = env->GetFieldID(pdfClass, "shaderClipDistance", "Z");
            shaderCullDistanceField = env->GetFieldID(pdfClass, "shaderCullDistance", "Z");
            shaderFloat64Field = env->GetFieldID(pdfClass, "shaderFloat64", "Z");
            shaderInt64Field = env->GetFieldID(pdfClass, "shaderInt64", "Z");
            shaderInt16Field = env->GetFieldID(pdfClass, "shaderInt16", "Z");
            shaderResourceResidencyField = env->GetFieldID(pdfClass, "shaderResourceResidency",
                                                           "Z");
            shaderResourceMinLodField = env->GetFieldID(pdfClass, "shaderResourceMinLod", "Z");
            sparseBindingField = env->GetFieldID(pdfClass, "sparseBinding", "Z");
            sparseResidencyBufferField = env->GetFieldID(pdfClass, "sparseResidencyBuffer",
                                                         "Z");
            sparseResidencyImage2DField = env->GetFieldID(pdfClass, "sparseResidencyImage2D",
                                                          "Z");
            sparseResidencyImage3DField = env->GetFieldID(pdfClass, "sparseResidencyImage3D",
                                                          "Z");
            sparseResidency2SamplesField = env->GetFieldID(pdfClass, "sparseResidency2Samples",
                                                           "Z");
            sparseResidency4SamplesField = env->GetFieldID(pdfClass, "sparseResidency4Samples",
                                                           "Z");
            sparseResidency8SamplesField = env->GetFieldID(pdfClass, "sparseResidency8Samples",
                                                           "Z");
            sparseResidency16SamplesField = env->GetFieldID(pdfClass,
                                                            "sparseResidency16Samples",
                                                            "Z");
            sparseResidencyAliasedField = env->GetFieldID(pdfClass, "sparseResidencyAliased",
                                                          "Z");
            variableMultisampleRateField = env->GetFieldID(pdfClass, "variableMultisampleRate",
                                                           "Z");
            inheritedQueriesField = env->GetFieldID(pdfClass, "inheritedQueries", "Z");
        }

        void extract(JNIEnv *env, jobject pEnabledFeaturesObj,
                     VkPhysicalDeviceFeatures &deviceFeatures) {
            jclass featureListClass = env->GetObjectClass(pEnabledFeaturesObj);
            jmethodID getMethodID = env->GetMethodID(featureListClass, "get",
                                                     "(I)Ljava/lang/Object;");
            jint listSize = env->CallIntMethod(pEnabledFeaturesObj,
                                               env->GetMethodID(featureListClass, "size", "()I"));

            // Loop through the list and set the values in the VkPhysicalDeviceFeatures structure
            for (int i = 0; i < listSize; ++i) {
                jobject featureObj = env->CallObjectMethod(pEnabledFeaturesObj, getMethodID, i);

                deviceFeatures.robustBufferAccess = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj,
                        robustBufferAccessField));
                deviceFeatures.fullDrawIndexUint32 = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj,
                        fullDrawIndexUint32Field));
                deviceFeatures.imageCubeArray = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj,
                        imageCubeArrayField));
                deviceFeatures.independentBlend = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj,
                        independentBlendField));
                deviceFeatures.geometryShader = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj,
                        geometryShaderField));
                deviceFeatures.tessellationShader = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj,
                        tessellationShaderField));
                deviceFeatures.sampleRateShading = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj,
                        sampleRateShadingField));
                deviceFeatures.dualSrcBlend = static_cast<VkBool32>(env->GetBooleanField(featureObj,
                                                                                         dualSrcBlendField));
                deviceFeatures.logicOp = static_cast<VkBool32>(env->GetBooleanField(featureObj,
                                                                                    logicOpField));
                deviceFeatures.multiDrawIndirect = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj,
                        multiDrawIndirectField));
                deviceFeatures.drawIndirectFirstInstance = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, drawIndirectFirstInstanceField));
                deviceFeatures.depthClamp = static_cast<VkBool32>(env->GetBooleanField(featureObj,
                                                                                       depthClampField));
                deviceFeatures.depthBiasClamp = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj,
                        depthBiasClampField));
                deviceFeatures.fillModeNonSolid = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj,
                        fillModeNonSolidField));
                deviceFeatures.depthBounds = static_cast<VkBool32>(env->GetBooleanField(featureObj,
                                                                                        depthBoundsField));
                deviceFeatures.wideLines = static_cast<VkBool32>(env->GetBooleanField(featureObj,
                                                                                      wideLinesField));
                deviceFeatures.largePoints = static_cast<VkBool32>(env->GetBooleanField(featureObj,
                                                                                        largePointsField));
                deviceFeatures.alphaToOne = static_cast<VkBool32>(env->GetBooleanField(featureObj,
                                                                                       alphaToOneField));
                deviceFeatures.multiViewport = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj,
                        multiViewportField));
                deviceFeatures.samplerAnisotropy = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj,
                        samplerAnisotropyField));
                deviceFeatures.textureCompressionETC2 = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, textureCompressionETC2Field));
                deviceFeatures.textureCompressionASTC_LDR = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, textureCompressionASTC_LDRField));
                deviceFeatures.textureCompressionBC = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj,
                        textureCompressionBCField));
                deviceFeatures.occlusionQueryPrecise = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, occlusionQueryPreciseField));
                deviceFeatures.pipelineStatisticsQuery = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, pipelineStatisticsQueryField));
                deviceFeatures.vertexPipelineStoresAndAtomics = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, vertexPipelineStoresAndAtomicsField));
                deviceFeatures.fragmentStoresAndAtomics = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, fragmentStoresAndAtomicsField));
                deviceFeatures.shaderTessellationAndGeometryPointSize = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, shaderTessellationAndGeometryPointSizeField));
                deviceFeatures.shaderImageGatherExtended = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, shaderImageGatherExtendedField));
                deviceFeatures.shaderStorageImageExtendedFormats = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, shaderStorageImageExtendedFormatsField));
                deviceFeatures.shaderStorageImageMultisample = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, shaderStorageImageMultisampleField));
                deviceFeatures.shaderStorageImageReadWithoutFormat = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, shaderStorageImageReadWithoutFormatField));
                deviceFeatures.shaderStorageImageWriteWithoutFormat = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, shaderStorageImageWriteWithoutFormatField));
                deviceFeatures.shaderUniformBufferArrayDynamicIndexing = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, shaderUniformBufferArrayDynamicIndexingField));
                deviceFeatures.shaderSampledImageArrayDynamicIndexing = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, shaderSampledImageArrayDynamicIndexingField));
                deviceFeatures.shaderStorageBufferArrayDynamicIndexing = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, shaderStorageBufferArrayDynamicIndexingField));
                deviceFeatures.shaderStorageImageArrayDynamicIndexing = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, shaderStorageImageArrayDynamicIndexingField));
                deviceFeatures.shaderClipDistance = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj,
                        shaderClipDistanceField));
                deviceFeatures.shaderCullDistance = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj,
                        shaderCullDistanceField));
                deviceFeatures.shaderFloat64 = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj,
                        shaderFloat64Field));
                deviceFeatures.shaderInt64 = static_cast<VkBool32>(env->GetBooleanField(featureObj,
                                                                                        shaderInt64Field));
                deviceFeatures.shaderInt16 = static_cast<VkBool32>(env->GetBooleanField(featureObj,
                                                                                        shaderInt16Field));
                deviceFeatures.shaderResourceResidency = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, shaderResourceResidencyField));
                deviceFeatures.shaderResourceMinLod = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj,
                        shaderResourceMinLodField));
                deviceFeatures.sparseBinding = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj,
                        sparseBindingField));
                deviceFeatures.sparseResidencyBuffer = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, sparseResidencyBufferField));
                deviceFeatures.sparseResidencyImage2D = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, sparseResidencyImage2DField));
                deviceFeatures.sparseResidencyImage3D = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, sparseResidencyImage3DField));
                deviceFeatures.sparseResidency2Samples = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, sparseResidency2SamplesField));
                deviceFeatures.sparseResidency4Samples = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, sparseResidency4SamplesField));
                deviceFeatures.sparseResidency8Samples = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, sparseResidency8SamplesField));
                deviceFeatures.sparseResidency16Samples = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, sparseResidency16SamplesField));
                deviceFeatures.sparseResidencyAliased = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, sparseResidencyAliasedField));
                deviceFeatures.variableMultisampleRate = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj, variableMultisampleRateField));
                deviceFeatures.inheritedQueries = static_cast<VkBool32>(env->GetBooleanField(
                        featureObj,
                        inheritedQueriesField));

                env->DeleteLocalRef(featureObj);
                env->DeleteLocalRef(pdfClass);
            }

            // Release local references if needed.
            env->DeleteLocalRef(featureListClass);
        }


        jobject toObject(JNIEnv *env, VkPhysicalDeviceFeatures &deviceFeatures) {
            jobject pdfObj = env->NewObject(pdfClass, pdfConstructor);
            if (pdfClass == nullptr) {
                return nullptr;
            }

            env->SetBooleanField(pdfObj, robustBufferAccessField,
                                 static_cast<jboolean>(deviceFeatures.robustBufferAccess));
            env->SetBooleanField(pdfObj, fullDrawIndexUint32Field,
                                 static_cast<jboolean>(deviceFeatures.fullDrawIndexUint32));
            env->SetBooleanField(pdfObj, imageCubeArrayField,
                                 static_cast<jboolean>(deviceFeatures.imageCubeArray));
            env->SetBooleanField(pdfObj, independentBlendField,
                                 static_cast<jboolean>(deviceFeatures.independentBlend));
            env->SetBooleanField(pdfObj, geometryShaderField,
                                 static_cast<jboolean>(deviceFeatures.geometryShader));
            env->SetBooleanField(pdfObj, tessellationShaderField,
                                 static_cast<jboolean>(deviceFeatures.tessellationShader));
            env->SetBooleanField(pdfObj, sampleRateShadingField,
                                 static_cast<jboolean>(deviceFeatures.sampleRateShading));
            env->SetBooleanField(pdfObj, dualSrcBlendField,
                                 static_cast<jboolean>(deviceFeatures.dualSrcBlend));
            env->SetBooleanField(pdfObj, logicOpField,
                                 static_cast<jboolean>(deviceFeatures.logicOp));
            env->SetBooleanField(pdfObj, multiDrawIndirectField,
                                 static_cast<jboolean>(deviceFeatures.multiDrawIndirect));
            env->SetBooleanField(pdfObj, drawIndirectFirstInstanceField,
                                 static_cast<jboolean>(deviceFeatures.drawIndirectFirstInstance));
            env->SetBooleanField(pdfObj, depthClampField,
                                 static_cast<jboolean>(deviceFeatures.depthClamp));
            env->SetBooleanField(pdfObj, depthBiasClampField,
                                 static_cast<jboolean>(deviceFeatures.depthBiasClamp));
            env->SetBooleanField(pdfObj, fillModeNonSolidField,
                                 static_cast<jboolean>(deviceFeatures.fillModeNonSolid));
            env->SetBooleanField(pdfObj, depthBoundsField,
                                 static_cast<jboolean>(deviceFeatures.depthBounds));
            env->SetBooleanField(pdfObj, wideLinesField,
                                 static_cast<jboolean>(deviceFeatures.wideLines));
            env->SetBooleanField(pdfObj, largePointsField,
                                 static_cast<jboolean>(deviceFeatures.largePoints));
            env->SetBooleanField(pdfObj, alphaToOneField,
                                 static_cast<jboolean>(deviceFeatures.alphaToOne));
            env->SetBooleanField(pdfObj, multiViewportField,
                                 static_cast<jboolean>(deviceFeatures.multiViewport));
            env->SetBooleanField(pdfObj, samplerAnisotropyField,
                                 static_cast<jboolean>(deviceFeatures.samplerAnisotropy));
            env->SetBooleanField(pdfObj, textureCompressionETC2Field,
                                 static_cast<jboolean>(deviceFeatures.textureCompressionETC2));
            env->SetBooleanField(pdfObj, textureCompressionASTC_LDRField,
                                 static_cast<jboolean>(deviceFeatures.textureCompressionASTC_LDR));
            env->SetBooleanField(pdfObj, textureCompressionBCField,
                                 static_cast<jboolean>(deviceFeatures.textureCompressionBC));
            env->SetBooleanField(pdfObj, occlusionQueryPreciseField,
                                 static_cast<jboolean>(deviceFeatures.occlusionQueryPrecise));
            env->SetBooleanField(pdfObj, pipelineStatisticsQueryField,
                                 static_cast<jboolean>(deviceFeatures.pipelineStatisticsQuery));
            env->SetBooleanField(pdfObj, vertexPipelineStoresAndAtomicsField,
                                 static_cast<jboolean>(deviceFeatures.vertexPipelineStoresAndAtomics));
            env->SetBooleanField(pdfObj, fragmentStoresAndAtomicsField,
                                 static_cast<jboolean>(deviceFeatures.fragmentStoresAndAtomics));
            env->SetBooleanField(pdfObj, shaderTessellationAndGeometryPointSizeField,
                                 static_cast<jboolean>(deviceFeatures.shaderTessellationAndGeometryPointSize));
            env->SetBooleanField(pdfObj, shaderImageGatherExtendedField,
                                 static_cast<jboolean>(deviceFeatures.shaderImageGatherExtended));
            env->SetBooleanField(pdfObj, shaderStorageImageExtendedFormatsField,
                                 static_cast<jboolean>(deviceFeatures.shaderStorageImageExtendedFormats));
            env->SetBooleanField(pdfObj, shaderStorageImageMultisampleField,
                                 static_cast<jboolean>(deviceFeatures.shaderStorageImageMultisample));
            env->SetBooleanField(pdfObj, shaderStorageImageReadWithoutFormatField,
                                 static_cast<jboolean>(deviceFeatures.shaderStorageImageReadWithoutFormat));
            env->SetBooleanField(pdfObj, shaderStorageImageWriteWithoutFormatField,
                                 static_cast<jboolean>(deviceFeatures.shaderStorageImageWriteWithoutFormat));
            env->SetBooleanField(pdfObj, shaderUniformBufferArrayDynamicIndexingField,
                                 static_cast<jboolean>(deviceFeatures.shaderUniformBufferArrayDynamicIndexing));
            env->SetBooleanField(pdfObj, shaderSampledImageArrayDynamicIndexingField,
                                 static_cast<jboolean>(deviceFeatures.shaderSampledImageArrayDynamicIndexing));
            env->SetBooleanField(pdfObj, shaderStorageBufferArrayDynamicIndexingField,
                                 static_cast<jboolean>(deviceFeatures.shaderStorageBufferArrayDynamicIndexing));
            env->SetBooleanField(pdfObj, shaderStorageImageArrayDynamicIndexingField,
                                 static_cast<jboolean>(deviceFeatures.shaderStorageImageArrayDynamicIndexing));
            env->SetBooleanField(pdfObj, shaderClipDistanceField,
                                 static_cast<jboolean>(deviceFeatures.shaderClipDistance));
            env->SetBooleanField(pdfObj, shaderCullDistanceField,
                                 static_cast<jboolean>(deviceFeatures.shaderCullDistance));
            env->SetBooleanField(pdfObj, shaderFloat64Field,
                                 static_cast<jboolean>(deviceFeatures.shaderFloat64));
            env->SetBooleanField(pdfObj, shaderInt64Field,
                                 static_cast<jboolean>(deviceFeatures.shaderInt64));
            env->SetBooleanField(pdfObj, shaderInt16Field,
                                 static_cast<jboolean>(deviceFeatures.shaderInt16));
            env->SetBooleanField(pdfObj, shaderResourceResidencyField,
                                 static_cast<jboolean>(deviceFeatures.shaderResourceResidency));
            env->SetBooleanField(pdfObj, shaderResourceMinLodField,
                                 static_cast<jboolean>(deviceFeatures.shaderResourceMinLod));
            env->SetBooleanField(pdfObj, sparseBindingField,
                                 static_cast<jboolean>(deviceFeatures.sparseBinding));
            env->SetBooleanField(pdfObj, sparseResidencyBufferField,
                                 static_cast<jboolean>(deviceFeatures.sparseResidencyBuffer));
            env->SetBooleanField(pdfObj, sparseResidencyImage2DField,
                                 static_cast<jboolean>(deviceFeatures.sparseResidencyImage2D));
            env->SetBooleanField(pdfObj, sparseResidencyImage3DField,
                                 static_cast<jboolean>(deviceFeatures.sparseResidencyImage3D));
            env->SetBooleanField(pdfObj, sparseResidency2SamplesField,
                                 static_cast<jboolean>(deviceFeatures.sparseResidency2Samples));
            env->SetBooleanField(pdfObj, sparseResidency4SamplesField,
                                 static_cast<jboolean>(deviceFeatures.sparseResidency4Samples));
            env->SetBooleanField(pdfObj, sparseResidency8SamplesField,
                                 static_cast<jboolean>(deviceFeatures.sparseResidency8Samples));
            env->SetBooleanField(pdfObj, sparseResidency16SamplesField,
                                 static_cast<jboolean>(deviceFeatures.sparseResidency16Samples));
            env->SetBooleanField(pdfObj, sparseResidencyAliasedField,
                                 static_cast<jboolean>(deviceFeatures.sparseResidencyAliased));
            env->SetBooleanField(pdfObj, variableMultisampleRateField,
                                 static_cast<jboolean>(deviceFeatures.variableMultisampleRate));
            env->SetBooleanField(pdfObj, inheritedQueriesField,
                                 static_cast<jboolean>(deviceFeatures.inheritedQueries));

            env->DeleteLocalRef(pdfClass);

            return pdfObj;
        }


        void destroy(JNIEnv *env) {
            pdfClass = nullptr;
            robustBufferAccessField = nullptr;
            fullDrawIndexUint32Field = nullptr;
            imageCubeArrayField = nullptr;
            independentBlendField = nullptr;
            geometryShaderField = nullptr;
            tessellationShaderField = nullptr;
            sampleRateShadingField = nullptr;
            dualSrcBlendField = nullptr;
            logicOpField = nullptr;
            multiDrawIndirectField = nullptr;
            drawIndirectFirstInstanceField = nullptr;
            depthClampField = nullptr;
            depthBiasClampField = nullptr;
            fillModeNonSolidField = nullptr;
            depthBoundsField = nullptr;
            wideLinesField = nullptr;
            largePointsField = nullptr;
            alphaToOneField = nullptr;
            multiViewportField = nullptr;
            samplerAnisotropyField = nullptr;
            textureCompressionETC2Field = nullptr;
            textureCompressionASTC_LDRField = nullptr;
            textureCompressionBCField = nullptr;
            occlusionQueryPreciseField = nullptr;
            pipelineStatisticsQueryField = nullptr;
            vertexPipelineStoresAndAtomicsField = nullptr;
            fragmentStoresAndAtomicsField = nullptr;
            shaderTessellationAndGeometryPointSizeField = nullptr;
            shaderImageGatherExtendedField = nullptr;
            shaderStorageImageExtendedFormatsField = nullptr;
            shaderStorageImageMultisampleField = nullptr;
            shaderStorageImageReadWithoutFormatField = nullptr;
            shaderStorageImageWriteWithoutFormatField = nullptr;
            shaderUniformBufferArrayDynamicIndexingField = nullptr;
            shaderSampledImageArrayDynamicIndexingField = nullptr;
            shaderStorageBufferArrayDynamicIndexingField = nullptr;
            shaderStorageImageArrayDynamicIndexingField = nullptr;
            shaderClipDistanceField = nullptr;
            shaderCullDistanceField = nullptr;
            shaderFloat64Field = nullptr;
            shaderInt64Field = nullptr;
            shaderInt16Field = nullptr;
            shaderResourceResidencyField = nullptr;
            shaderResourceMinLodField = nullptr;
            sparseBindingField = nullptr;
            sparseResidencyBufferField = nullptr;
            sparseResidencyImage2DField = nullptr;
            sparseResidencyImage3DField = nullptr;
            sparseResidency2SamplesField = nullptr;
            sparseResidency4SamplesField = nullptr;
            sparseResidency8SamplesField = nullptr;
            sparseResidency16SamplesField = nullptr;
            sparseResidencyAliasedField = nullptr;
            variableMultisampleRateField = nullptr;
            inheritedQueriesField = nullptr;
            env->DeleteLocalRef(pdfClass);
        }
    };

    class VkDeviceQueueCreateInfoJava {
    private:
        jclass clazz;
        jfieldID sTypeFieldID;
        jfieldID pNextFieldID;
        jfieldID flagsFieldID;
        jfieldID queueFamilyIndexFieldID;
        jfieldID queueCountFieldID;
        jfieldID pQueuePrioritiesFieldID;

    public:
        explicit VkDeviceQueueCreateInfoJava(JNIEnv *env) {
            // Extract the field IDs of the data class
            clazz = env->FindClass(
                    "io/github/ronjunevaldoz/awake/vulkan/models/info/VkDeviceQueueCreateInfo");
            sTypeFieldID = env->GetFieldID(clazz, "sType", "I");
            pNextFieldID = env->GetFieldID(clazz, "pNext", "J");
            flagsFieldID = env->GetFieldID(clazz, "flags", "I");
            queueFamilyIndexFieldID = env->GetFieldID(clazz, "queueFamilyIndex", "I");
            queueCountFieldID = env->GetFieldID(clazz, "queueCount", "I");
            pQueuePrioritiesFieldID = env->GetFieldID(clazz, "pQueuePriorities", "[F");
        }

        void extract(JNIEnv *env, jobject vkQueueCreateInfoObject,
                     VkDeviceQueueCreateInfo &queueCreateInfo) {
            // Extract the field values from the Java object
            jint sType = env->GetIntField(vkQueueCreateInfoObject, sTypeFieldID);
            jlong pNext = env->GetLongField(vkQueueCreateInfoObject, pNextFieldID);
            jint flags = env->GetIntField(vkQueueCreateInfoObject, flagsFieldID);
            jint queueFamilyIndex = env->GetIntField(vkQueueCreateInfoObject,
                                                     queueFamilyIndexFieldID);
            jint queueCount = env->GetIntField(vkQueueCreateInfoObject, queueCountFieldID);

            auto pQueuePrioritiesObj = (jfloatArray) (env->GetObjectField(
                    vkQueueCreateInfoObject, pQueuePrioritiesFieldID));
            auto numQueuePriorities = env->GetArrayLength(pQueuePrioritiesObj);
            float pQueuePriorities[numQueuePriorities];
            // Use GetFloatArrayRegion to directly copy the elements
            env->GetFloatArrayRegion(pQueuePrioritiesObj, 0, numQueuePriorities, pQueuePriorities);

            // Create a VkDeviceQueueCreateInfo object and add it to the vector
//            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO; // sType;
            queueCreateInfo.pNext = nullptr;
            queueCreateInfo.flags = flags; //VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT;//VkDeviceQueueCreateFlagBits// flags;
            queueCreateInfo.queueFamilyIndex = static_cast<uint32_t>(queueFamilyIndex);
            queueCreateInfo.queueCount = static_cast<uint32_t>(queueCount);
            queueCreateInfo.pQueuePriorities = pQueuePriorities;

            env->DeleteLocalRef(pQueuePrioritiesObj);
//            return queueCreateInfo;
        }

        void destroy(JNIEnv *env) {
            sTypeFieldID = nullptr;
            pNextFieldID = nullptr;
            flagsFieldID = nullptr;
            queueFamilyIndexFieldID = nullptr;
            queueCountFieldID = nullptr;
            pQueuePrioritiesFieldID = nullptr;
            env->DeleteLocalRef(clazz);
        }
    };

/**
 *
 * @param env
 * @param pQueueCreateInfosObj  list of vkDeviceQueueCreateInfo class from kotlin
 */
    void getDeviceQueueCreateInfoList(JNIEnv *env, jobject pQueueCreateInfosObj,
                                      std::vector<VkDeviceQueueCreateInfo> &queueCreateInfos) {
        jclass queueCreateInfoListClass = env->GetObjectClass(pQueueCreateInfosObj);
        jmethodID getMethodID = env->GetMethodID(queueCreateInfoListClass, "get",
                                                 "(I)Ljava/lang/Object;");
        jmethodID sizeMethodID = env->GetMethodID(queueCreateInfoListClass, "size", "()I");

        VkDeviceQueueCreateInfoJava extractor(env);
        // Get the size of the List
        jint queueCreateInfoListSize = env->CallIntMethod(pQueueCreateInfosObj, sizeMethodID);
        for (int i = 0; i < queueCreateInfoListSize; ++i) {
            // Get the VkDeviceQueueCreateInfo object at the specified index
            jobject elementObject = env->CallObjectMethod(pQueueCreateInfosObj,
                                                          getMethodID, i);
            VkDeviceQueueCreateInfo queueCreateInfo;
            extractor.extract(env, elementObject, queueCreateInfo);
            queueCreateInfos.push_back(queueCreateInfo);
//            env->DeleteLocalRef(elementObject);
        }
        extractor.destroy(env);
        env->DeleteLocalRef(queueCreateInfoListClass);
    }
    // HELPERS ABOVE

    VkApplicationInfo VkApplicationInfo_fromObject(JNIEnv *env, jobject vkApplicationInfoObject) {
        jclass clazz = env->GetObjectClass(vkApplicationInfoObject);

//    jfieldID sTypeField = env->GetFieldID(clazz, "sType", "I");
        jfieldID pNextField = env->GetFieldID(clazz, "pNext", "J");
        jfieldID pApplicationNameField = env->GetFieldID(clazz, "pApplicationName",
                                                         "Ljava/lang/String;");
        jfieldID applicationVersionField = env->GetFieldID(clazz, "applicationVersion", "I");
        jfieldID pEngineNameField = env->GetFieldID(clazz, "pEngineName", "Ljava/lang/String;");
        jfieldID engineVersionField = env->GetFieldID(clazz, "engineVersion", "I");
//    jfieldID apiVersionField = env->GetFieldID(clazz, "apiVersion", "I");

        VkApplicationInfo appInfo{};

//    jobject vkStructureTypeObj = env->GetObjectField(vkApplicationInfoObject, sTypeField);

        auto pNext = env->GetLongField(vkApplicationInfoObject,
                                       pNextField);

        auto appNameString = (jstring) (env->GetObjectField(vkApplicationInfoObject,
                                                            pApplicationNameField));
        auto engineNameString = (jstring) (env->GetObjectField(vkApplicationInfoObject,
                                                               pEngineNameField));
        const char *appNameChars = env->GetStringUTFChars(appNameString, nullptr);
        const char *engineNameChars = env->GetStringUTFChars(engineNameString, nullptr);

        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO; // GetVkStructureType(env, vkStructureTypeObj);
        appInfo.pNext = reinterpret_cast<const void *>(pNext);
        appInfo.pApplicationName = appNameChars;
        appInfo.applicationVersion = env->GetIntField(vkApplicationInfoObject,
                                                      applicationVersionField);
        appInfo.pEngineName = engineNameChars;
        appInfo.engineVersion = env->GetIntField(vkApplicationInfoObject,
                                                 engineVersionField);
        int apiLevel = android_get_device_api_level();
        if (apiLevel <= 24) {
            appInfo.apiVersion = VK_API_VERSION_1_0;
        } else if (apiLevel >= 25) {
            appInfo.apiVersion = VK_API_VERSION_1_1;
        } else if (apiLevel >= 29) {
            appInfo.apiVersion = VK_API_VERSION_1_2;
        } else if (apiLevel >= 33) {
            appInfo.apiVersion = VK_API_VERSION_1_3;
        }

        // env->GetIntField(vkApplicationInfoObject, apiVersionField);


//        env->ReleaseStringUTFChars(appNameString, appNameChars); // TODO check if not needed
//        env->ReleaseStringUTFChars(engineNameString, engineNameChars); // TODO check if not needed

        // release object
        env->DeleteLocalRef(clazz);
        env->DeleteLocalRef(vkApplicationInfoObject);
        return appInfo;
    }

    bool VkPhysicalDeviceSparseProperties_fromObject(JNIEnv *env,
                                                     jobject p_pdp_obj,
                                                     jfieldID p_sp_fid,
                                                     VkPhysicalDeviceSparseProperties sp
    ) {
        jobject spObj = env->GetObjectField(p_pdp_obj, p_sp_fid);
        jclass spClass;
        if (spObj == nullptr) {
            // create new sparse properties instance
            spClass = env->FindClass(
                    "io/github/ronjunevaldoz/awake/vulkan/physicaldevice/VkPhysicalDeviceSparseProperties");
            auto spConstructor = env->GetMethodID(spClass, "<init>", "()V");
            spObj = env->NewObject(spClass, spConstructor);
        }
        spClass = env->GetObjectClass(spObj);

        jfieldID residencyStandard2DBlockShapeFieldId = env->GetFieldID(spClass,
                                                                        "residencyStandard2DBlockShape",
                                                                        "Z");
        jfieldID residencyStandard2DMultisampleBlockShapeFieldID = env->GetFieldID(spClass,
                                                                                   "residencyStandard2DMultisampleBlockShape",
                                                                                   "Z");
        jfieldID residencyStandard3DBlockShapeFieldId = env->GetFieldID(spClass,
                                                                        "residencyStandard3DBlockShape",
                                                                        "Z");
        jfieldID residencyAlignedMipSizeFieldID = env->GetFieldID(spClass,
                                                                  "residencyAlignedMipSize", "Z");
        jfieldID residencyNonResidentStrictFieldId = env->GetFieldID(spClass,
                                                                     "residencyNonResidentStrict",
                                                                     "Z");

        env->SetBooleanField(spObj, residencyStandard2DBlockShapeFieldId,
                             static_cast<jboolean>(sp.residencyStandard2DBlockShape));
        env->SetBooleanField(spObj, residencyStandard2DMultisampleBlockShapeFieldID,
                             static_cast<jboolean>(sp.residencyStandard2DMultisampleBlockShape));
        env->SetBooleanField(spObj, residencyStandard3DBlockShapeFieldId,
                             static_cast<jboolean>(sp.residencyStandard3DBlockShape));
        env->SetBooleanField(spObj, residencyAlignedMipSizeFieldID,
                             static_cast<jboolean>(sp.residencyAlignedMipSize));
        env->SetBooleanField(spObj, residencyNonResidentStrictFieldId,
                             static_cast<jboolean>(sp.residencyNonResidentStrict));

        env->DeleteLocalRef(spClass);
        env->DeleteLocalRef(spObj);

        return true;
    }

    bool VkPhysicalDeviceLimits_fromObject(JNIEnv *env,
                                           jclass p_pdpp_class,
                                           jobject p_pdp_obj,
                                           VkPhysicalDeviceLimits pdl
    ) {
        // TODO implement VkPhysicalDeviceLimits_fromObject
        return true;
    }

    jobject
    physicalDevicePropertiesObj_fromVkPhysicalDeviceProperties(JNIEnv *env, jlong pPhysicalDevice) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(pPhysicalDevice);

        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

        // Get the class and field IDs for VkPhysicalDeviceProperties
        jclass pdpClass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/physicaldevice/VkPhysicalDeviceProperties");

        // Create an instance of the VkPhysicalDeviceProperties class using its default constructor
        jmethodID pdpConstructor = env->GetMethodID(pdpClass, "<init>", "()V");
        jobject pdpObj = env->NewObject(pdpClass, pdpConstructor);

        jfieldID apiVersionFieldID = env->GetFieldID(pdpClass, "apiVersion", "I");
        jfieldID deviceIdFieldID = env->GetFieldID(pdpClass, "deviceID", "I");
        jfieldID deviceNameFieldID = env->GetFieldID(pdpClass, "deviceName", "Ljava/lang/String;");
        jfieldID deviceTypeFieldId = env->GetFieldID(pdpClass, "deviceType", "I");
        jfieldID pipelineCacheUUIDFieldID = env->GetFieldID(pdpClass, "pipelineCacheUUID", "[B");
        jfieldID sparsePropertiesFieldId = env->GetFieldID(pdpClass, "sparseProperties",
                                                           "Lio/github/ronjunevaldoz/awake/vulkan/physicaldevice/VkPhysicalDeviceSparseProperties;");

        vulkan_utils::VkPhysicalDeviceSparseProperties_fromObject(env, pdpObj,
                                                                  sparsePropertiesFieldId,
                                                                  deviceProperties.sparseProperties);

        vulkan_utils::VkPhysicalDeviceLimits_fromObject(env, pdpClass, pdpObj,
                                                        deviceProperties.limits);

        jstring deviceNameStr = env->NewStringUTF(deviceProperties.deviceName);
        env->SetIntField(pdpObj, apiVersionFieldID,
                         static_cast<jint>(deviceProperties.apiVersion));
        env->SetIntField(pdpObj, deviceIdFieldID,
                         static_cast<jint>(deviceProperties.deviceID));
        env->SetIntField(pdpObj, deviceTypeFieldId,
                         static_cast<jint>(deviceProperties.deviceType));
        env->SetObjectField(pdpObj, deviceNameFieldID, deviceNameStr);

        // Copy pipelineCacheUUID data to pipelineCacheUUIDArray
        jbyteArray pipelineCacheUUIDArray = env->NewByteArray(VK_UUID_SIZE);
        // assign bytes to to reference
        env->SetByteArrayRegion(pipelineCacheUUIDArray, 0, VK_UUID_SIZE,
                                reinterpret_cast<const jbyte *>(deviceProperties.pipelineCacheUUID ));
        // assign array to object
        env->SetObjectField(pdpObj, pipelineCacheUUIDFieldID,
                            pipelineCacheUUIDArray);

        // Release
        env->DeleteLocalRef(deviceNameStr);
        env->DeleteLocalRef(pipelineCacheUUIDArray);
        env->DeleteLocalRef(pdpClass);

        return pdpObj;
    }

    jobject
    physicalDeviceFeaturesObj_fromVkPhysicalDeviceFeatures(JNIEnv *env, jlong pPhysicalDevice) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(pPhysicalDevice);
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);
        VkPhysicalDeviceFeaturesJava extractor(env);
        jobject obj = extractor.toObject(env, deviceFeatures);
        extractor.destroy(env);
        return obj;
    }

    jobjectArray
    queueFamilyPropertiesObj_fromVkQueueFamilyProperties(JNIEnv *env, jlong pPhysicalDevice) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(pPhysicalDevice);
        // Check if the device supports the required queue families (graphics, compute, transfer)
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount,
                                                 queueFamilies.data());

        // init class and constructors
        auto qfpClass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/queuefamily/VkQueueFamilyProperties");
        auto qfpConstructor = env->GetMethodID(qfpClass, "<init>",
                                               "(IIILio/github/ronjunevaldoz/awake/vulkan/models/VkExtent3D;)V");
        auto extent3DClass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/models/VkExtent3D");
        auto extent3DConstructor = env->GetMethodID(extent3DClass, "<init>", "(III)V");

        auto queueFamilyList = env->NewObjectArray(static_cast<jint>(queueFamilyCount), qfpClass,
                                                   nullptr);
        for (int i = 0; i < queueFamilyCount; i++) {
            auto queueFamily = queueFamilies[i];
            // create a new extend3D
            auto extent3DObj = env->NewObject(extent3DClass, extent3DConstructor,
                                              static_cast<jint>(queueFamily.minImageTransferGranularity.width),
                                              static_cast<jint>(queueFamily.minImageTransferGranularity.height),
                                              static_cast<jint>(queueFamily.minImageTransferGranularity.depth)
            );
            // Create a new VkQueueFamilyProperties object
            auto qfpObj = env->NewObject(qfpClass, qfpConstructor,
                                         static_cast<jint>(queueFamily.queueFlags),
                                         static_cast<jint>(queueFamily.queueCount),
                                         static_cast<jint>(queueFamily.timestampValidBits),
                                         extent3DObj
            );

            // Add the VkQueueFamilyProperties object to the ArrayList
            env->SetObjectArrayElement(queueFamilyList, i, qfpObj);
        }

        env->DeleteLocalRef(qfpClass);
        env->DeleteLocalRef(extent3DClass);
        return queueFamilyList;
    }

    // TODO check better to delete local ref
    _jobject *extent2DObj_fromExtend2D(JNIEnv *env, VkExtent2D &extent2D) {
        jclass extent2DClass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/models/VkExtent2D");
        jmethodID extent2DConstructor = env->GetMethodID(extent2DClass, "<init>", "(II)V");
        jobject extent2DObj = env->NewObject(extent2DClass, extent2DConstructor,
                                             static_cast<jint>(extent2D.width),
                                             static_cast<jint>(extent2D.height));
        env->DeleteLocalRef(extent2DClass);
        return extent2DObj;
    }

    // TODO check better to delete local ref
    _jobject *surfaceTransformFlagBitsKHRObj_fromVkSurfaceTransformFlagBitsKHR(JNIEnv *env,
                                                                               VkSurfaceTransformFlagBitsKHR &flagBitsKhr) {
        jclass enumClass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/enums/VkSurfaceTransformFlagBitsKHR");
        auto enumValues = (jobjectArray) (env->CallStaticObjectMethod(enumClass,
                                                                      env->GetStaticMethodID(
                                                                              enumClass,
                                                                              "values",
                                                                              "()[Lio/github/ronjunevaldoz/awake/vulkan/enums/VkSurfaceTransformFlagBitsKHR;")));

        jsize numEnumValues = env->GetArrayLength(enumValues);
        jint index = std::min(static_cast<jint>(flagBitsKhr), numEnumValues - 1);
        jobject enumObj = env->GetObjectArrayElement(enumValues, index);

        env->DeleteLocalRef(enumClass);
        env->DeleteLocalRef(enumValues);

        return enumObj;
    }

    // TODO check better to delete local ref
    _jobject *formatObj_fromVkSurfaceFormatKHR(JNIEnv *env, VkFormat &format) {
        jclass enumClass = env->FindClass("io/github/ronjunevaldoz/awake/vulkan/enums/VkFormat");
        auto enumValues = (jobjectArray) (env->CallStaticObjectMethod(enumClass,
                                                                      env->GetStaticMethodID(
                                                                              enumClass,
                                                                              "values",
                                                                              "()[Lio/github/ronjunevaldoz/awake/vulkan/enums/VkFormat;")));
        jsize numEnumValues = env->GetArrayLength(enumValues);
        jint index = std::min(static_cast<jint>(format), numEnumValues - 1);
        jobject enumObj = env->GetObjectArrayElement(enumValues, index);

        env->DeleteLocalRef(enumClass);
        env->DeleteLocalRef(enumValues);

        return enumObj;
    }


    // TODO check better to delete local ref
    _jobject *colorSpaceObj_fromVkColorSpaceKHR(JNIEnv *env, VkColorSpaceKHR &colorSpace) {
        jclass enumClass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/enums/VkColorSpaceKHR");
        auto enumValues = (jobjectArray) (env->CallStaticObjectMethod(enumClass,
                                                                      env->GetStaticMethodID(
                                                                              enumClass,
                                                                              "values",
                                                                              "()[Lio/github/ronjunevaldoz/awake/vulkan/enums/VkColorSpaceKHR;")));
        jsize numEnumValues = env->GetArrayLength(enumValues);
        jint index = std::min(static_cast<jint>(colorSpace), numEnumValues - 1);
        jobject enumObj = env->GetObjectArrayElement(enumValues, index);

        env->DeleteLocalRef(enumClass);
        env->DeleteLocalRef(enumValues);

        return enumObj;
    }

    // TODO check better to delete local ref
    _jobject *surfaceFormatKHRObj_fromVkSurfaceFormatKHR(JNIEnv *env, VkSurfaceFormatKHR &format) {
        jclass clazz = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/presentation/swapchain/VkSurfaceFormatKHR");
        jmethodID constructor = env->GetMethodID(clazz, "<init>",
                                                 "(Lio/github/ronjunevaldoz/awake/vulkan/enums/VkFormat;Lio/github/ronjunevaldoz/awake/vulkan/enums/VkColorSpaceKHR;)V");
        auto formatEnumObj = formatObj_fromVkSurfaceFormatKHR(env, format.format);
        auto colorSpaceEnumObj = colorSpaceObj_fromVkColorSpaceKHR(env, format.colorSpace);
        jobject obj = env->NewObject(clazz, constructor, formatEnumObj, colorSpaceEnumObj);
        // Cleanup: Delete local references (optional)
        env->DeleteLocalRef(clazz);
        env->DeleteLocalRef(formatEnumObj);
        env->DeleteLocalRef(colorSpaceEnumObj);
        return obj;
    }

    // TODO check better to delete local ref
    _jobject *presentModeKHRObj_fromVkPresentModeKHR(JNIEnv *env, VkPresentModeKHR &presentMode) {
        jclass enumClass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/enums/VkPresentModeKHR");
        auto enumValues = (jobjectArray) (env->CallStaticObjectMethod(enumClass,
                                                                      env->GetStaticMethodID(
                                                                              enumClass,
                                                                              "values",
                                                                              "()[Lio/github/ronjunevaldoz/awake/vulkan/enums/VkPresentModeKHR;")));
        jsize numEnumValues = env->GetArrayLength(enumValues);
        jint index = std::min(static_cast<jint>(presentMode), numEnumValues - 1);
        jobject enumObj = env->GetObjectArrayElement(enumValues, index);

        env->DeleteLocalRef(enumClass);
        env->DeleteLocalRef(enumValues);

        return enumObj;
    }

    VkExtent2D
    VkExtent2D_fromObject(JNIEnv *env, jobject vkExtentObj) {
        // Get the Class object of VkExtent2D
        jclass vkExtentClass = env->GetObjectClass(vkExtentObj);
        // Get the width and height values from the Java object
        jfieldID widthFieldID = env->GetFieldID(vkExtentClass, "width", "I");
        jfieldID heightFieldID = env->GetFieldID(vkExtentClass, "height", "I");
        jint width = env->GetIntField(vkExtentObj, widthFieldID);
        jint height = env->GetIntField(vkExtentObj, heightFieldID);
        // Release local references
        env->DeleteLocalRef(vkExtentClass);

        VkExtent2D extent{};
        extent.width = static_cast<uint32_t>(width);
        extent.height = static_cast<uint32_t>(height);
        // Return the newly created VkExtent2D object
        return extent;
    }

    std::vector<uint32_t>
    queueFamilyIndicesList_fromObject(JNIEnv *env, jobject queueFamilyIndicesList) {
        jclass listClass = env->FindClass("java/util/List");
        jclass integerClass = env->FindClass("java/lang/Integer");

// Get the size of the List
        jmethodID listSizeMethod = env->GetMethodID(listClass, "size", "()I");
        jint listSize = env->CallIntMethod(queueFamilyIndicesList, listSizeMethod);

// Iterate through the List and extract each Integer value
        std::vector<uint32_t> queueFamilyIndices;
        for (int i = 0; i < listSize; i++) {
            jmethodID listGetMethod = env->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");
            jobject integerObject = env->CallObjectMethod(queueFamilyIndicesList, listGetMethod, i);

            // Convert the Integer object to int
            jmethodID intValueMethod = env->GetMethodID(integerClass, "intValue", "()I");
            jint value = env->CallIntMethod(integerObject, intValueMethod);

            queueFamilyIndices.push_back(static_cast<uint32_t>(value));

            // Release local references for each integerObject
            env->DeleteLocalRef(integerObject);
        }

// Release local references
        env->DeleteLocalRef(listClass);
        env->DeleteLocalRef(integerClass);
        env->DeleteLocalRef(queueFamilyIndicesList);
        return queueFamilyIndices;
    }


    VkSwapchainCreateInfoKHR
    VkSwapchainCreateInfoKHR_fromObject(JNIEnv *env, jobject pSwapchainObj) {
        // Assuming you have JNI methods to access the properties of the Java object
        jclass swapchainClass = env->GetObjectClass(pSwapchainObj);
        jfieldID surfaceField = env->GetFieldID(swapchainClass, "surface",
                                                "Lio/github/ronjunevaldoz/awake/vulkan/models/VkSurfaceKHR;");
        jfieldID oldSwapchainField = env->GetFieldID(swapchainClass, "oldSwapchain",
                                                     "Lio/github/ronjunevaldoz/awake/vulkan/models/VkSwapchainKHR;");
        jfieldID minImageCountField = env->GetFieldID(swapchainClass, "minImageCount", "I");
        jfieldID imageFormatField = env->GetFieldID(swapchainClass, "imageFormat",
                                                    "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkFormat;");
        jfieldID imageColorSpaceField = env->GetFieldID(swapchainClass, "imageColorSpace",
                                                        "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkColorSpaceKHR;");
        jfieldID imageExtentField = env->GetFieldID(swapchainClass, "imageExtent",
                                                    "Lio/github/ronjunevaldoz/awake/vulkan/models/VkExtent2D;");
        jfieldID imageArrayLayersField = env->GetFieldID(swapchainClass, "imageArrayLayers", "I");
        jfieldID imageUsageField = env->GetFieldID(swapchainClass, "imageUsage", "I");
        jfieldID imageSharingModeField = env->GetFieldID(swapchainClass, "imageSharingMode",
                                                         "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkSharingMode;");
        jfieldID queueFamilyIndicesField = env->GetFieldID(swapchainClass, "queueFamilyIndices",
                                                           "Ljava/util/List;");
        jfieldID preTransformField = env->GetFieldID(swapchainClass, "preTransform",
                                                     "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkSurfaceTransformFlagBitsKHR;");
        jfieldID compositeAlphaField = env->GetFieldID(swapchainClass, "compositeAlpha",
                                                       "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkCompositeAlphaFlagBitsKHR;");
        jfieldID presentModeField = env->GetFieldID(swapchainClass, "presentMode",
                                                    "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkPresentModeKHR;");
        jfieldID clippedField = env->GetFieldID(swapchainClass, "clipped", "Z");
        // Add other fields as needed

        // Extract properties from the Java object
        // surface from object
        jobject surfaceObj = env->GetObjectField(pSwapchainObj, surfaceField);
        jclass surfaceClass = env->GetObjectClass(surfaceObj);
        jfieldID surfaceIdField = env->GetFieldID(surfaceClass, "surface", "J");
        auto surface = env->GetLongField(surfaceObj, surfaceIdField);

        jint minImageCount = env->GetIntField(pSwapchainObj, minImageCountField);
        jobject imageFormatObj = env->GetObjectField(pSwapchainObj, imageFormatField);
        jobject imageColorSpaceObj = env->GetObjectField(pSwapchainObj, imageColorSpaceField);
        jobject imageExtentObj = env->GetObjectField(pSwapchainObj, imageExtentField);
        jobject imageSharingModeObj = env->GetObjectField(pSwapchainObj, imageSharingModeField);
        jint imageArrayLayers = env->GetIntField(pSwapchainObj, imageArrayLayersField);
        jint imageUsage = env->GetIntField(pSwapchainObj, imageUsageField);
        jobject queueFamilyIndicesList = env->GetObjectField(pSwapchainObj,
                                                             queueFamilyIndicesField);
        jobject preTransformObj = env->GetObjectField(pSwapchainObj, preTransformField);
        jobject compositeAlphaObj = env->GetObjectField(pSwapchainObj, compositeAlphaField);
        jobject presentModeObj = env->GetObjectField(pSwapchainObj, presentModeField);
        jboolean clipped = env->GetBooleanField(pSwapchainObj, clippedField);

        auto pCreateInfo = VkSwapchainCreateInfoKHR{};
        pCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        pCreateInfo.pNext = nullptr;
        pCreateInfo.flags = 0;
        pCreateInfo.surface = reinterpret_cast<VkSurfaceKHR>(surface);
        pCreateInfo.minImageCount = static_cast<uint32_t>(minImageCount);
        pCreateInfo.imageFormat = static_cast<VkFormat>(enum_utils::getEnumFromObject(env,
                                                                                      imageFormatObj));
        pCreateInfo.imageColorSpace = static_cast<VkColorSpaceKHR>(enum_utils::getEnumFromObject(
                env,
                imageColorSpaceObj));
        pCreateInfo.imageExtent = VkExtent2D_fromObject(env, imageExtentObj);
        pCreateInfo.imageArrayLayers = static_cast<uint32_t>(imageArrayLayers);
        pCreateInfo.imageUsage = static_cast<VkImageUsageFlags>(imageUsage);
        pCreateInfo.imageSharingMode = static_cast<VkSharingMode>(enum_utils::getEnumFromObject(env,
                                                                                                imageSharingModeObj));;
        if (queueFamilyIndicesList != nullptr) {
            std::vector<uint32_t> queueFamilyIndices = queueFamilyIndicesList_fromObject(env,
                                                                                         queueFamilyIndicesList);
            pCreateInfo.queueFamilyIndexCount = static_cast<uint32_t>(queueFamilyIndices.size());
            pCreateInfo.pQueueFamilyIndices = queueFamilyIndices.data();
        } else {
            pCreateInfo.queueFamilyIndexCount = 0;
            pCreateInfo.pQueueFamilyIndices = nullptr;
        }
        pCreateInfo.preTransform = static_cast<VkSurfaceTransformFlagBitsKHR>(enum_utils::getEnumFromObject(
                env,
                preTransformObj));
        pCreateInfo.compositeAlpha = static_cast<VkCompositeAlphaFlagBitsKHR>(enum_utils::getEnumFromObject(
                env,
                compositeAlphaObj));
        pCreateInfo.presentMode = static_cast<VkPresentModeKHR>(enum_utils::getEnumFromObject(env,
                                                                                              presentModeObj));
        pCreateInfo.clipped = static_cast<VkBool32>(clipped);

        // oldSwapchain from object
        jobject oldSwapchainObj = env->GetObjectField(pSwapchainObj, oldSwapchainField);
        if (oldSwapchainObj != nullptr) {
            jclass oldSwapchainClass = env->GetObjectClass(oldSwapchainObj);
            jfieldID oldSwapchainIdField = env->GetFieldID(oldSwapchainClass, "swapchain", "J");
            auto oldSwapchain = env->GetLongField(oldSwapchainObj, oldSwapchainIdField);
            pCreateInfo.oldSwapchain = reinterpret_cast<VkSwapchainKHR>(oldSwapchain);
            env->DeleteLocalRef(oldSwapchainClass);
        } else {
            pCreateInfo.oldSwapchain = nullptr;
        }

        env->DeleteLocalRef(oldSwapchainObj);
        env->DeleteLocalRef(swapchainClass);
        env->DeleteLocalRef(surfaceObj);
        env->DeleteLocalRef(surfaceClass);
        env->DeleteLocalRef(imageFormatObj);
        env->DeleteLocalRef(imageColorSpaceObj);
        env->DeleteLocalRef(imageExtentObj);
        env->DeleteLocalRef(imageSharingModeObj);
        env->DeleteLocalRef(queueFamilyIndicesList);
        env->DeleteLocalRef(preTransformObj);
        env->DeleteLocalRef(compositeAlphaObj);
        env->DeleteLocalRef(presentModeObj);

        return pCreateInfo;
    }

    bool
    enumeratePhysicalDevices(JNIEnv *env, jlong vkInstance, jobject pDeviceCountDirectBufferObj,
                             jobject pPhysicalDevicesDirectBufferObj) {
        auto instance = reinterpret_cast<VkInstance>(vkInstance);

        // Call enumeratePhysicalDevices to get the number of physical devices
        if (pPhysicalDevicesDirectBufferObj == nullptr) {
            jint *intArray = reinterpret_cast<jint *>(env->GetDirectBufferAddress(
                    pDeviceCountDirectBufferObj));
            if (intArray == nullptr) {
                // possible not a direct buffer?
                return false;
            }
            uint32_t physicalDeviceCount = 0;
            vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
            intArray[0] = static_cast<jint>(physicalDeviceCount);
        } else {
            jint *intArray = reinterpret_cast<jint *>(env->GetDirectBufferAddress(
                    pDeviceCountDirectBufferObj));
            if (intArray == nullptr) {
                // possible not a direct buffer?
                return false;
            }
            auto *longArray = reinterpret_cast<jlong *>(env->GetDirectBufferAddress(
                    pPhysicalDevicesDirectBufferObj));
            if (longArray == nullptr) {
                // possible not a direct buffer?
                return false;
            }
            // Call enumeratePhysicalDevices again to fill the physical device handles in the direct ByteBuffer
            auto deviceCount = static_cast<uint32_t>(intArray[0]);
            std::vector<VkPhysicalDevice> devices(deviceCount);
            vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
            // fill the buffer
            for (int i = 0; i < deviceCount; ++i) {
                longArray[i] = reinterpret_cast<jlong>(devices[i]);
            }
        }
        return true;
    }

    jlong createInstance(JNIEnv *env, jobject app_info) {
        auto appInfo = vulkan_utils::VkApplicationInfo_fromObject(env, app_info);

        std::vector<const char *> layers{
                "VK_LAYER_KHRONOS_validation"
        };

        if (!vulkan_utils::checkValidationLayerSupported(layers)) {
            throw std::runtime_error("Validation layers are not supported.");
        }


        std::vector<const char *> enabled_inst_exts{};

        // check if androidSurfaceExtensionSupported
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        bool androidSurfaceExtensionSupported = false;
        bool surfaceExtensionSupported = false;
        bool swapChainExtensionSupported = false;
        for (const auto &extension: extensions) {
            if (strcmp(extension.extensionName, VK_KHR_ANDROID_SURFACE_EXTENSION_NAME) == 0) {
                androidSurfaceExtensionSupported = true;
            }
            if (strcmp(extension.extensionName, VK_KHR_SURFACE_EXTENSION_NAME) == 0) {
                surfaceExtensionSupported = true;
            }
            enabled_inst_exts.push_back(extension.extensionName);
        }

        if (surfaceExtensionSupported) {
            // enable presentation queue family?
            enabled_inst_exts.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
        }
        if (androidSurfaceExtensionSupported) {
            // enable surface
            enabled_inst_exts.push_back(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);
        }

        // Enable the debug utils extension if available
        if (vulkan_utils::checkDebugUtilsExtAvailable() ||
            vulkan_utils::checkDebugUtilsExtFromAvailableLayers()) {
            enabled_inst_exts.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(enabled_inst_exts.size());
        createInfo.ppEnabledExtensionNames = enabled_inst_exts.data();
        createInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
        createInfo.ppEnabledLayerNames = layers.data();

        VkInstance instance{};
        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

        if (result != VK_SUCCESS) {
            throw std::runtime_error("Instance creation failed: " + std::to_string(result));
        }

        return reinterpret_cast<jlong>(instance);
    }

// Function to enable the debug utils extension if available
    bool checkDebugUtilsExtAvailable() {
        // Get the instance extension count.
        uint32_t inst_ext_count = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &inst_ext_count, nullptr);

        // Enumerate the instance extensions.
        VkExtensionProperties inst_exts[inst_ext_count];
        vkEnumerateInstanceExtensionProperties(nullptr, &inst_ext_count, inst_exts);

        // Check for debug utils extension within the system driver or loader.
        // Check if the debug utils extension is available (in the driver).
        VkExtensionProperties *inst_exts_end = inst_exts + inst_ext_count;
        bool debugUtilsExtAvailable = inst_exts_end !=
                                      std::find_if(inst_exts, inst_exts_end,
                                                   [](VkExtensionProperties
                                                      extensionProperties) {
                                                       return strcmp(
                                                               extensionProperties.extensionName,
                                                               VK_EXT_DEBUG_UTILS_EXTENSION_NAME) ==
                                                              0;
                                                   });

        return debugUtilsExtAvailable;
    }


// Function to enable the debug utils extension if available
    bool checkDebugUtilsExtFromAvailableLayers() {
        // Also check the layers for the debug utils extension.
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        std::vector<VkLayerProperties> layer_props(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, layer_props.data());

        bool debugUtilsExtAvailable = false;

        for (const auto &layer: layer_props) {
            uint32_t layer_ext_count;
            vkEnumerateInstanceExtensionProperties(layer.layerName, &layer_ext_count, nullptr);
            if (layer_ext_count == 0) continue;

            std::vector<VkExtensionProperties> layer_exts(layer_ext_count);
            vkEnumerateInstanceExtensionProperties(layer.layerName, &layer_ext_count,
                                                   layer_exts.data());
            debugUtilsExtAvailable = std::any_of(layer_exts.begin(), layer_exts.end(),
                                                 [](const VkExtensionProperties &extension) {
                                                     return strcmp(extension.extensionName,
                                                                   VK_EXT_DEBUG_UTILS_EXTENSION_NAME) ==
                                                            0;
                                                 });

            if (debugUtilsExtAvailable) {
                // Add the including layer into the layer request list if necessary.
                break;
            }
        }
        return debugUtilsExtAvailable;
    }

    bool checkValidationLayerSupported(const std::vector<const char *> &layers) {

        // Get the layer count using a null pointer as the last parameter.
        uint32_t instance_layer_present_count = 0;
        vkEnumerateInstanceLayerProperties(&instance_layer_present_count, nullptr);

        // Enumerate layers with a valid pointer in the last parameter.
        std::vector<VkLayerProperties> layer_props(instance_layer_present_count);
        vkEnumerateInstanceLayerProperties(&instance_layer_present_count, layer_props.data());

        // Make sure selected validation layers are available.
        bool validationLayersAvailable = std::all_of(layers.begin(), layers.end(),
                                                     [&layer_props](const char *layer) {
                                                         return std::find_if(layer_props.begin(),
                                                                             layer_props.end(),
                                                                             [layer](const VkLayerProperties &layerProperties) {
                                                                                 return strcmp(
                                                                                         layerProperties.layerName,
                                                                                         layer) ==
                                                                                        0;
                                                                             }) !=
                                                                layer_props.end();
                                                     });
        return validationLayersAvailable; // or false depending on the validation layer availability
    }

    // TODO check for possible leak??
// Function to create the debug utils messenger
    VkDebugUtilsMessengerEXT createDebugUtilsMessenger(
            VkInstance instance) {
        auto pfnCreateDebugUtilsMessengerEXT =
                (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(
                        instance, "vkCreateDebugUtilsMessengerEXT");

        if (!pfnCreateDebugUtilsMessengerEXT) {
            return VK_NULL_HANDLE;
        }

        VkDebugUtilsMessengerCreateInfoEXT messengerInfo = {};
        messengerInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        messengerInfo.pNext = nullptr;
        messengerInfo.flags = 0;
        messengerInfo.messageSeverity =
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
        messengerInfo.messageType =
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        messengerInfo.pfnUserCallback = &onDebugUtilsMessage;
        messengerInfo.pUserData = nullptr; // Custom user data passed to the callback

        VkDebugUtilsMessengerEXT debugUtilsMessenger = VK_NULL_HANDLE;
        VkResult result = pfnCreateDebugUtilsMessengerEXT(
                instance, &messengerInfo, nullptr, &debugUtilsMessenger);

        if (result != VK_SUCCESS) {
            return VK_NULL_HANDLE;
        }

        return debugUtilsMessenger;
    }


    VKAPI_ATTR VkBool32 VKAPI_CALL onDebugUtilsMessage(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageTypes,
            const VkDebugUtilsMessengerCallbackDataEXT *callbackData,
            void *userData) {
        const char validation[] = "Validation";
        const char performance[] = "Performance";
        const char error[] = "ERROR";
        const char warning[] = "WARNING";
        const char unknownType[] = "UNKNOWN_TYPE";
        const char unknownSeverity[] = "UNKNOWN_SEVERITY";
        const char *typeString = unknownType;
        const char *severityString = unknownSeverity;
        const char *messageIdName = callbackData->pMessageIdName;
        int32_t messageIdNumber = callbackData->messageIdNumber;
        const char *message = callbackData->pMessage;
        android_LogPriority priority = ANDROID_LOG_UNKNOWN;

        if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
            severityString = error;
            priority = ANDROID_LOG_ERROR;
        } else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
            severityString = warning;
            priority = ANDROID_LOG_WARN;
        }
        if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) {
            typeString = validation;
        } else if (messageTypes & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) {
            typeString = performance;
        }

        __android_log_print(priority,
                            "Awake Vulkan",
                            "%s %s: \n[%s] Code %i :\n%s",
                            typeString,
                            severityString,
                            messageIdName,
                            messageIdNumber,
                            message);

        // Returning false tells the layer not to stop when the event occurs, so
        // they see the same behavior with and without validation layers enabled.
        return VK_FALSE;
    }


// Function to destroy the debug utils messenger
    void destroyDebugUtilsMessenger(
            VkInstance instance,
            VkDebugUtilsMessengerEXT debugUtilsMessenger) {
        if (!debugUtilsMessenger) {
            return;
        }

        auto pfnDestroyDebugUtilsMessengerEXT =
                (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(
                        instance, "vkDestroyDebugUtilsMessengerEXT");

        if (!pfnDestroyDebugUtilsMessengerEXT) {
            return;
        }

        pfnDestroyDebugUtilsMessengerEXT(instance, debugUtilsMessenger, nullptr);
    }

    jlong createDevice(JNIEnv *env, jlong pPhysicalDevice, jobject p_dci_obj) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(pPhysicalDevice);

        jclass deviceCreateInfoClass = env->GetObjectClass(p_dci_obj);

        jfieldID sTypeFieldID = env->GetFieldID(deviceCreateInfoClass, "sType", "I");
        jfieldID pNextFieldID = env->GetFieldID(deviceCreateInfoClass, "pNext", "J");
        jfieldID flagsFieldID = env->GetFieldID(deviceCreateInfoClass, "flags", "I");
        jfieldID queueCreateInfoCountFieldID = env->GetFieldID(deviceCreateInfoClass,
                                                               "queueCreateInfoCount", "I");
        jfieldID pQueueCreateInfosFieldID = env->GetFieldID(deviceCreateInfoClass,
                                                            "pQueueCreateInfos",
                                                            "Ljava/util/List;");
        jfieldID ppEnabledLayerNamesFieldID = env->GetFieldID(deviceCreateInfoClass,
                                                              "ppEnabledLayerNames",
                                                              "Ljava/util/List;");
        jfieldID ppEnabledExtensionNamesFieldID = env->GetFieldID(deviceCreateInfoClass,
                                                                  "ppEnabledExtensionNames",
                                                                  "Ljava/util/List;");
        jfieldID pEnabledFeaturesFieldID = env->GetFieldID(deviceCreateInfoClass,
                                                           "pEnabledFeatures", "Ljava/util/List;");

        jint sType = env->GetIntField(p_dci_obj, sTypeFieldID);
        jlong pNext = env->GetLongField(p_dci_obj, pNextFieldID);
        auto flags = env->GetIntField(p_dci_obj, flagsFieldID);
        jint queueCreateInfoCount = env->GetIntField(p_dci_obj, queueCreateInfoCountFieldID);
        jobject pQueueCreateInfosObj = env->GetObjectField(p_dci_obj, pQueueCreateInfosFieldID);
        jobject ppEnabledLayerNamesObj = env->GetObjectField(p_dci_obj,
                                                             ppEnabledLayerNamesFieldID);
        auto ppEnabledExtensionNamesObj = env->GetObjectField(p_dci_obj,
                                                              ppEnabledExtensionNamesFieldID);
        jobject pEnabledFeaturesObj = env->GetObjectField(p_dci_obj, pEnabledFeaturesFieldID);

        // Get list of device queue create infos
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        getDeviceQueueCreateInfoList(env, pQueueCreateInfosObj, queueCreateInfos);
        VkPhysicalDeviceFeaturesJava extractor(env);
        VkPhysicalDeviceFeatures deviceFeatures;
        extractor.extract(env, pEnabledFeaturesObj, deviceFeatures);
        std::vector<const char *> enabledExtensions = getEnabledDeviceExtensions_fromObjectList(env,
                                                                                                ppEnabledExtensionNamesObj);
        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.flags = static_cast<VkDeviceCreateFlags>(flags);
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.pEnabledFeatures = &deviceFeatures;
        if (ppEnabledExtensionNamesObj != nullptr) {
            createInfo.enabledExtensionCount = static_cast<uint32_t>(enabledExtensions.size());
            createInfo.ppEnabledExtensionNames = enabledExtensions.data();
        } else {
            createInfo.enabledExtensionCount = 0;
            createInfo.ppEnabledExtensionNames = nullptr;
        }
        createInfo.enabledLayerCount = 0;// static_cast<uint32_t>(enabledLayerCount);
//        if (ppEnabledLayerNames != nullptr) {
        createInfo.ppEnabledLayerNames = nullptr;// reinterpret_cast<const char *const *>(ppEnabledLayerNames);
//        }

        // Release local references if needed.
        VkDevice device{};

        VkResult result = vkCreateDevice(physicalDevice, &createInfo, nullptr, &device);

        env->DeleteLocalRef(deviceCreateInfoClass);
        env->DeleteLocalRef(pQueueCreateInfosObj);
        env->DeleteLocalRef(ppEnabledLayerNamesObj);
        env->DeleteLocalRef(ppEnabledExtensionNamesObj);
        env->DeleteLocalRef(pEnabledFeaturesObj);
        extractor.destroy(env);
        if (result != VK_SUCCESS) {
            return 0;
        }

        return reinterpret_cast<jlong>(device);
    }

    jlong createAndroidSurfaceKHR(JNIEnv *env,
                                  jlong pInstance,
                                  jobject surface_info) {
        auto instance = reinterpret_cast<VkInstance>(pInstance);
        VkSurfaceKHR surface{};

        jclass siClass = env->GetObjectClass(surface_info);
//    jfieldID  flagsField = env->GetFieldID(siClass, "flags", "I");
        jfieldID windowField = env->GetFieldID(siClass, "window", "Ljava/lang/Object;");
        auto windowObj = env->GetObjectField(surface_info, windowField);
        auto *window = ANativeWindow_fromSurface(env, windowObj);

        // Create the surface using the VK_KHR_android_surface extension
        VkAndroidSurfaceCreateInfoKHR createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
        createInfo.pNext = nullptr;
        createInfo.flags = 0;
        createInfo.window = window;

        VkResult result = vkCreateAndroidSurfaceKHR(instance, &createInfo, nullptr, &surface);

        env->DeleteLocalRef(siClass);
        env->DeleteLocalRef(windowObj);

        if (result != VK_SUCCESS) {
            // Handle surface creation failure
            return 0;
        }

        return reinterpret_cast<jlong>(surface);
    }

    void destroySurface(JNIEnv *env,
                        jlong pInstance, jlong pSurface) {
        auto instance = reinterpret_cast<VkInstance>(pInstance);
        auto surface = reinterpret_cast<VkSurfaceKHR>(pSurface);
        vkDestroySurfaceKHR(instance, surface, nullptr);
    }

    jboolean getPhysicalDeviceSurfaceSupportKHR(JNIEnv *env,
                                                jlong pDevice,
                                                jint queueFamilyIndex,
                                                jlong pSurface) {
        auto device = reinterpret_cast<VkPhysicalDevice>(pDevice);
        auto surface = reinterpret_cast<VkSurfaceKHR>(pSurface);
        if (surface == nullptr) {
            throw std::runtime_error("Invalid surface instance");
        }
        VkBool32 presentSupport = false;
        VkResult result = vkGetPhysicalDeviceSurfaceSupportKHR(device,
                                                               static_cast<uint32_t>(queueFamilyIndex),
                                                               surface, &presentSupport);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("Unable to check vkGetPhysicalDeviceSurfaceSupportKHR");
        }
        return presentSupport;
    }

    // TODO check for possible leak??
    jobject getPhysicalDeviceSurfaceCapabilitiesKHR(
            JNIEnv *env, jlong pPhysicalDevice, jlong pSurface) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(pPhysicalDevice);
        auto surface = reinterpret_cast<VkSurfaceKHR>(pSurface);

        VkSurfaceCapabilitiesKHR capabilities{};
        VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface,
                                                                    &capabilities);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("Unable to check vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
        }

        jclass scKHRclass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/presentation/swapchain/VkSurfaceCapabilitiesKHR");
        jmethodID constructor = env->GetMethodID(scKHRclass, "<init>", "()V");
        jobject scKHRobj = env->NewObject(scKHRclass, constructor);

        env->SetIntField(scKHRobj, env->GetFieldID(scKHRclass, "minImageCount", "I"),
                         static_cast<jint>(capabilities.minImageCount));
        env->SetIntField(scKHRobj, env->GetFieldID(scKHRclass, "maxImageCount", "I"),
                         static_cast<jint>(capabilities.maxImageCount));
        env->SetObjectField(scKHRobj, env->GetFieldID(scKHRclass, "currentExtent",
                                                      "Lio/github/ronjunevaldoz/awake/vulkan/models/VkExtent2D;"),
                            vulkan_utils::extent2DObj_fromExtend2D(env,
                                                                   capabilities.currentExtent));
        env->SetObjectField(scKHRobj, env->GetFieldID(scKHRclass, "minImageExtent",
                                                      "Lio/github/ronjunevaldoz/awake/vulkan/models/VkExtent2D;"),
                            vulkan_utils::extent2DObj_fromExtend2D(env,
                                                                   capabilities.minImageExtent));
        env->SetObjectField(scKHRobj, env->GetFieldID(scKHRclass, "maxImageExtent",
                                                      "Lio/github/ronjunevaldoz/awake/vulkan/models/VkExtent2D;"),
                            vulkan_utils::extent2DObj_fromExtend2D(env,
                                                                   capabilities.maxImageExtent));
        env->SetIntField(scKHRobj, env->GetFieldID(scKHRclass, "maxImageArrayLayers", "I"),
                         static_cast<jint>(capabilities.maxImageArrayLayers));
        env->SetIntField(scKHRobj, env->GetFieldID(scKHRclass, "supportedTransforms", "I"),
                         static_cast<jint>(capabilities.supportedTransforms));
        env->SetIntField(scKHRobj, env->GetFieldID(scKHRclass, "supportedCompositeAlpha", "I"),
                         static_cast<jint>(capabilities.supportedCompositeAlpha));
        env->SetIntField(scKHRobj, env->GetFieldID(scKHRclass, "supportedUsageFlags", "I"),
                         static_cast<jint>(capabilities.supportedUsageFlags));
        env->SetObjectField(scKHRobj, env->GetFieldID(scKHRclass, "currentTransform",
                                                      "Lio/github/ronjunevaldoz/awake/vulkan/enums/VkSurfaceTransformFlagBitsKHR;"),
                            vulkan_utils::surfaceTransformFlagBitsKHRObj_fromVkSurfaceTransformFlagBitsKHR(
                                    env,
                                    capabilities.currentTransform));
        return scKHRobj;
    }

    // TODO check for possible leak??
    _jobjectArray *getPhysicalDeviceSurfaceFormatsKHR(JNIEnv *env,
                                                      jlong pPhysicalDevice,
                                                      jlong pSurface) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(pPhysicalDevice);
        auto surface = reinterpret_cast<VkSurfaceKHR>(pSurface);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);

        if (formatCount != 0) {
            std::vector<VkSurfaceFormatKHR> formats;
            formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount,
                                                 formats.data());

            // Create a Java array to hold the VkSurfaceFormatKHR objects
            jclass formatClass = env->FindClass(
                    "io/github/ronjunevaldoz/awake/vulkan/presentation/swapchain/VkSurfaceFormatKHR");
            jobjectArray formatArray = env->NewObjectArray(static_cast<jint>(formatCount),
                                                           formatClass,
                                                           nullptr);

            for (uint32_t i = 0; i < formatCount; i++) {
                // Create a Java VkSurfaceFormatKHR object for each VkSurfaceFormatKHR
                jobject formatObj = vulkan_utils::surfaceFormatKHRObj_fromVkSurfaceFormatKHR(env,
                                                                                             formats[i]);
                env->SetObjectArrayElement(formatArray, static_cast<jint>(i), formatObj);
                // Cleanup: Delete local reference to formatObj (optional)
                env->DeleteLocalRef(formatObj);
            }

            env->DeleteLocalRef(formatClass);

            return formatArray;
        } else {
            return jobjectArray();
        }
    }

    // TODO check for possible leak??
    _jobjectArray *getPhysicalDeviceSurfacePresentModesKHR(
            JNIEnv *env, jlong pPhysicalDevice, jlong pSurface) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(pPhysicalDevice);
        auto surface = reinterpret_cast<VkSurfaceKHR>(pSurface);

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount,
                                                  nullptr);

        if (presentModeCount != 0) {
            std::vector<VkPresentModeKHR> presentModes;
            presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount,
                                                      presentModes.data());

            // Create a Java array to hold the VkSurfaceFormatKHR objects
            jclass presetModeClass = env->FindClass(
                    "io/github/ronjunevaldoz/awake/vulkan/enums/VkPresentModeKHR");
            jobjectArray presetModeArray = env->NewObjectArray(static_cast<jint>(presentModeCount),
                                                               presetModeClass, nullptr);

            for (uint32_t i = 0; i < presentModeCount; i++) {
                // Create a Java VkPresentModeKHR object for each VkPresentModeKHR
                jobject presetModObj = vulkan_utils::presentModeKHRObj_fromVkPresentModeKHR(env,
                                                                                            presentModes[i]);
                env->SetObjectArrayElement(presetModeArray, static_cast<jint>(i), presetModObj);
                env->DeleteLocalRef(presetModObj);
            }

            env->DeleteLocalRef(presetModeClass);

            return presetModeArray;
        } else {
            return jobjectArray();
        }
    }

    jlong createSwapchainKHR(JNIEnv *env,
                             jlong pDevice,
                             jobject create_info_khr) {
        auto device = reinterpret_cast<VkDevice>(pDevice);
        VkSwapchainKHR swapchain{};
        auto createInfo = vulkan_utils::VkSwapchainCreateInfoKHR_fromObject(env, create_info_khr);
        VkResult result = vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapchain);
        if (result != VK_SUCCESS) {
            return 0;
        }

        if (swapchain == nullptr) {
            return 0;
        }
        return reinterpret_cast<jlong>(swapchain);
    }

    void destroySwapchainKHR(JNIEnv *env, jlong pDevice,
                             jlong swapchain_khr) {
        auto device = reinterpret_cast<VkDevice>(pDevice);
        auto swapchain = reinterpret_cast<VkSwapchainKHR>(swapchain_khr);
        vkDestroySwapchainKHR(device, swapchain, nullptr);
    }

    jlong getDeviceQueue(JNIEnv *env,
                         jlong device,
                         jint queue_family_index,
                         jint queue_index) {
        auto deviceHandle = reinterpret_cast<VkDevice>(device);

        VkQueue graphicsQueue;
        vkGetDeviceQueue(deviceHandle, static_cast<uint32_t>(queue_family_index),
                         static_cast<uint32_t>(queue_index), &graphicsQueue);
        return reinterpret_cast<jlong>(graphicsQueue);
    }

    // TODO check for possible leak??
    _jobjectArray *enumerateInstanceExtensionProperties(JNIEnv *env) {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        // init class and constructors
        auto extPropClass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/models/VkExtensionProperties");
        auto extPropConstructor = env->GetMethodID(extPropClass, "<init>",
                                                   "(Ljava/lang/String;I)V");

        auto extensionList = env->NewObjectArray(static_cast<jint>(extensionCount), extPropClass,
                                                 nullptr);
        for (int i = 0; i < extensionCount; i++) {
            auto extension = extensions[i];
            auto extensionName = env->NewStringUTF(extension.extensionName);

            // Create a new VkExtensionProperties object
            auto qfpObj = env->NewObject(extPropClass, extPropConstructor,
                                         static_cast<jstring>(extensionName),
                                         static_cast<jint>(extension.specVersion)
            );

            // Add the VkExtensionProperties object to the ArrayList
            env->SetObjectArrayElement(extensionList, i, qfpObj);
            env->DeleteLocalRef(extensionName);
            env->DeleteLocalRef(qfpObj);
        }

        env->DeleteLocalRef(extPropClass);
        return extensionList;
    }

    // TODO check for possible leak??
    _jobjectArray *enumerateDeviceExtensionProperties(JNIEnv *env, jlong pPhysicalDevice) {
        auto physicalDevice = reinterpret_cast<VkPhysicalDevice>(pPhysicalDevice);

        uint32_t extensionCount = 0;
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount,
                                             extensions.data());

        // init class and constructors
        auto extPropClass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/models/VkExtensionProperties");
        auto extPropConstructor = env->GetMethodID(extPropClass, "<init>",
                                                   "(Ljava/lang/String;I)V");

        auto extensionList = env->NewObjectArray(static_cast<jint>(extensionCount), extPropClass,
                                                 nullptr);
        for (int i = 0; i < extensionCount; i++) {
            auto extension = extensions[i];
            auto extensionName = env->NewStringUTF(extension.extensionName);

            // Create a new VkExtensionProperties object
            auto qfpObj = env->NewObject(extPropClass, extPropConstructor,
                                         static_cast<jstring>(extensionName),
                                         static_cast<jint>(extension.specVersion)
            );

            // Add the VkExtensionProperties object to the ArrayList
            env->SetObjectArrayElement(extensionList, i, qfpObj);
            env->DeleteLocalRef(extensionName);
            env->DeleteLocalRef(
                    qfpObj); // TODO should not be deleted when directly passing to java??
        }

        env->DeleteLocalRef(extPropClass);
        return extensionList;
    }

    // TODO check for possible leak??
    _jobjectArray *getSwapchainImagesKHR(JNIEnv *env, jlong pDevice, jlong pSwapchain) {

        auto device = reinterpret_cast<VkDevice>(pDevice);
        auto swapChain = reinterpret_cast<VkSwapchainKHR>(pSwapchain);

        uint32_t imageCount = 0;
        vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
        std::vector<VkImage> swapChainImages(imageCount);
        vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

        // init class and constructors
        auto imgClass = env->FindClass(
                "io/github/ronjunevaldoz/awake/vulkan/models/VkImage");
        auto imgConstructor = env->GetMethodID(imgClass, "<init>",
                                               "(J)V");

        auto imageList = env->NewObjectArray(static_cast<jint>(imageCount), imgClass,
                                             nullptr);
        for (int i = 0; i < imageCount; i++) {
            auto image = swapChainImages[i];
            // Create a new VKImage object
            auto imageObj = env->NewObject(imgClass, imgConstructor,
                                           reinterpret_cast<jlong>(image));

            // Add the VkImage object to the ArrayList
            env->SetObjectArrayElement(imageList, i, imageObj);
            env->DeleteLocalRef(imageObj);
        }

        env->DeleteLocalRef(imgClass);
        return imageList;
    }

    jlong createImageView(JNIEnv *env,
                          jlong pDevice,
                          jobject p_create_nfo
    ) {
        auto device = reinterpret_cast<VkDevice>(pDevice);

        VkImageViewCreateInfoConverter converter(env);

        auto createInfo = converter.fromObject(p_create_nfo);

        VkImageView imageView;
        VkResult result = vkCreateImageView(device, &createInfo, nullptr, &imageView);

        if (result != VK_SUCCESS) {
            return 0;
        }

        return reinterpret_cast<jlong>(imageView);
    }

    void destroyImageView(JNIEnv *env,
                          jlong pDevice,
                          jlong p_image_view
    ) {
        auto device = reinterpret_cast<VkDevice>(pDevice);
        auto imageView = reinterpret_cast<VkImageView>(p_image_view);
        vkDestroyImageView(device, imageView, nullptr);
    }
}