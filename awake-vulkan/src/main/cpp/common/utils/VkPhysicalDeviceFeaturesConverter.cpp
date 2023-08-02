//
// Created by Ron June Valdoz on 8/2/23.
//

#include "VkPhysicalDeviceFeaturesConverter.h"

VkPhysicalDeviceFeaturesConverter::VkPhysicalDeviceFeaturesConverter(JNIEnv *env) {
    this->env = env;
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

void VkPhysicalDeviceFeaturesConverter::extract(jobject pEnabledFeaturesObj,
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

jobject VkPhysicalDeviceFeaturesConverter::toObject(VkPhysicalDeviceFeatures &deviceFeatures) {
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

VkPhysicalDeviceFeaturesConverter::~VkPhysicalDeviceFeaturesConverter() {
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
