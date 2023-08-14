/*
 *  VkPhysicalDeviceFeaturesAccessor.cpp
 *  Vulkan accessor for VkPhysicalDeviceFeatures
 *  Created by Ron June Valdoz */

#include  <includes/VkPhysicalDeviceFeaturesAccessor.h>

VkPhysicalDeviceFeaturesAccessor::VkPhysicalDeviceFeaturesAccessor(JNIEnv *env, jobject obj) {
    this->env = env;
    this->obj = env->NewGlobalRef(obj);
    clazz = (jclass) env->NewGlobalRef(env->GetObjectClass(obj));
    robustBufferAccessField = env->GetFieldID(clazz, "robustBufferAccess", "Z");
    fullDrawIndexUint32Field = env->GetFieldID(clazz, "fullDrawIndexUint32", "Z");
    imageCubeArrayField = env->GetFieldID(clazz, "imageCubeArray", "Z");
    independentBlendField = env->GetFieldID(clazz, "independentBlend", "Z");
    geometryShaderField = env->GetFieldID(clazz, "geometryShader", "Z");
    tessellationShaderField = env->GetFieldID(clazz, "tessellationShader", "Z");
    sampleRateShadingField = env->GetFieldID(clazz, "sampleRateShading", "Z");
    dualSrcBlendField = env->GetFieldID(clazz, "dualSrcBlend", "Z");
    logicOpField = env->GetFieldID(clazz, "logicOp", "Z");
    multiDrawIndirectField = env->GetFieldID(clazz, "multiDrawIndirect", "Z");
    drawIndirectFirstInstanceField = env->GetFieldID(clazz, "drawIndirectFirstInstance", "Z");
    depthClampField = env->GetFieldID(clazz, "depthClamp", "Z");
    depthBiasClampField = env->GetFieldID(clazz, "depthBiasClamp", "Z");
    fillModeNonSolidField = env->GetFieldID(clazz, "fillModeNonSolid", "Z");
    depthBoundsField = env->GetFieldID(clazz, "depthBounds", "Z");
    wideLinesField = env->GetFieldID(clazz, "wideLines", "Z");
    largePointsField = env->GetFieldID(clazz, "largePoints", "Z");
    alphaToOneField = env->GetFieldID(clazz, "alphaToOne", "Z");
    multiViewportField = env->GetFieldID(clazz, "multiViewport", "Z");
    samplerAnisotropyField = env->GetFieldID(clazz, "samplerAnisotropy", "Z");
    textureCompressionETC2Field = env->GetFieldID(clazz, "textureCompressionETC2", "Z");
    textureCompressionASTC_LDRField = env->GetFieldID(clazz, "textureCompressionASTC_LDR", "Z");
    textureCompressionBCField = env->GetFieldID(clazz, "textureCompressionBC", "Z");
    occlusionQueryPreciseField = env->GetFieldID(clazz, "occlusionQueryPrecise", "Z");
    pipelineStatisticsQueryField = env->GetFieldID(clazz, "pipelineStatisticsQuery", "Z");
    vertexPipelineStoresAndAtomicsField = env->GetFieldID(clazz, "vertexPipelineStoresAndAtomics",
                                                          "Z");
    fragmentStoresAndAtomicsField = env->GetFieldID(clazz, "fragmentStoresAndAtomics", "Z");
    shaderTessellationAndGeometryPointSizeField = env->GetFieldID(clazz,
                                                                  "shaderTessellationAndGeometryPointSize",
                                                                  "Z");
    shaderImageGatherExtendedField = env->GetFieldID(clazz, "shaderImageGatherExtended", "Z");
    shaderStorageImageExtendedFormatsField = env->GetFieldID(clazz,
                                                             "shaderStorageImageExtendedFormats",
                                                             "Z");
    shaderStorageImageMultisampleField = env->GetFieldID(clazz, "shaderStorageImageMultisample",
                                                         "Z");
    shaderStorageImageReadWithoutFormatField = env->GetFieldID(clazz,
                                                               "shaderStorageImageReadWithoutFormat",
                                                               "Z");
    shaderStorageImageWriteWithoutFormatField = env->GetFieldID(clazz,
                                                                "shaderStorageImageWriteWithoutFormat",
                                                                "Z");
    shaderUniformBufferArrayDynamicIndexingField = env->GetFieldID(clazz,
                                                                   "shaderUniformBufferArrayDynamicIndexing",
                                                                   "Z");
    shaderSampledImageArrayDynamicIndexingField = env->GetFieldID(clazz,
                                                                  "shaderSampledImageArrayDynamicIndexing",
                                                                  "Z");
    shaderStorageBufferArrayDynamicIndexingField = env->GetFieldID(clazz,
                                                                   "shaderStorageBufferArrayDynamicIndexing",
                                                                   "Z");
    shaderStorageImageArrayDynamicIndexingField = env->GetFieldID(clazz,
                                                                  "shaderStorageImageArrayDynamicIndexing",
                                                                  "Z");
    shaderClipDistanceField = env->GetFieldID(clazz, "shaderClipDistance", "Z");
    shaderCullDistanceField = env->GetFieldID(clazz, "shaderCullDistance", "Z");
    shaderFloat64Field = env->GetFieldID(clazz, "shaderFloat64", "Z");
    shaderInt64Field = env->GetFieldID(clazz, "shaderInt64", "Z");
    shaderInt16Field = env->GetFieldID(clazz, "shaderInt16", "Z");
    shaderResourceResidencyField = env->GetFieldID(clazz, "shaderResourceResidency", "Z");
    shaderResourceMinLodField = env->GetFieldID(clazz, "shaderResourceMinLod", "Z");
    sparseBindingField = env->GetFieldID(clazz, "sparseBinding", "Z");
    sparseResidencyBufferField = env->GetFieldID(clazz, "sparseResidencyBuffer", "Z");
    sparseResidencyImage2DField = env->GetFieldID(clazz, "sparseResidencyImage2D", "Z");
    sparseResidencyImage3DField = env->GetFieldID(clazz, "sparseResidencyImage3D", "Z");
    sparseResidency2SamplesField = env->GetFieldID(clazz, "sparseResidency2Samples", "Z");
    sparseResidency4SamplesField = env->GetFieldID(clazz, "sparseResidency4Samples", "Z");
    sparseResidency8SamplesField = env->GetFieldID(clazz, "sparseResidency8Samples", "Z");
    sparseResidency16SamplesField = env->GetFieldID(clazz, "sparseResidency16Samples", "Z");
    sparseResidencyAliasedField = env->GetFieldID(clazz, "sparseResidencyAliased", "Z");
    variableMultisampleRateField = env->GetFieldID(clazz, "variableMultisampleRate", "Z");
    inheritedQueriesField = env->GetFieldID(clazz, "inheritedQueries", "Z");
}

bool
VkPhysicalDeviceFeaturesAccessor::gettessellationShader() {
    return (bool) (jboolean) env->GetBooleanField(obj, tessellationShaderField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getfullDrawIndexUint32() {
    return (bool) (jboolean) env->GetBooleanField(obj, fullDrawIndexUint32Field); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getdepthBounds() {
    return (bool) (jboolean) env->GetBooleanField(obj, depthBoundsField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getsparseResidency4Samples() {
    return (bool) (jboolean) env->GetBooleanField(obj, sparseResidency4SamplesField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getpipelineStatisticsQuery() {
    return (bool) (jboolean) env->GetBooleanField(obj, pipelineStatisticsQueryField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getsparseResidencyBuffer() {
    return (bool) (jboolean) env->GetBooleanField(obj, sparseResidencyBufferField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getshaderStorageImageReadWithoutFormat() {
    return (bool) (jboolean) env->GetBooleanField(obj,
                                                  shaderStorageImageReadWithoutFormatField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getsparseResidency8Samples() {
    return (bool) (jboolean) env->GetBooleanField(obj, sparseResidency8SamplesField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getalphaToOne() {
    return (bool) (jboolean) env->GetBooleanField(obj, alphaToOneField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getshaderStorageImageMultisample() {
    return (bool) (jboolean) env->GetBooleanField(obj,
                                                  shaderStorageImageMultisampleField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getshaderStorageImageArrayDynamicIndexing() {
    return (bool) (jboolean) env->GetBooleanField(obj,
                                                  shaderStorageImageArrayDynamicIndexingField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getshaderInt64() {
    return (bool) (jboolean) env->GetBooleanField(obj, shaderInt64Field); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getwideLines() {
    return (bool) (jboolean) env->GetBooleanField(obj, wideLinesField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getshaderClipDistance() {
    return (bool) (jboolean) env->GetBooleanField(obj, shaderClipDistanceField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getshaderInt16() {
    return (bool) (jboolean) env->GetBooleanField(obj, shaderInt16Field); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getshaderUniformBufferArrayDynamicIndexing() {
    return (bool) (jboolean) env->GetBooleanField(obj,
                                                  shaderUniformBufferArrayDynamicIndexingField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getfragmentStoresAndAtomics() {
    return (bool) (jboolean) env->GetBooleanField(obj, fragmentStoresAndAtomicsField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getshaderStorageImageExtendedFormats() {
    return (bool) (jboolean) env->GetBooleanField(obj,
                                                  shaderStorageImageExtendedFormatsField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getsparseResidency2Samples() {
    return (bool) (jboolean) env->GetBooleanField(obj, sparseResidency2SamplesField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getshaderSampledImageArrayDynamicIndexing() {
    return (bool) (jboolean) env->GetBooleanField(obj,
                                                  shaderSampledImageArrayDynamicIndexingField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getlogicOp() {
    return (bool) (jboolean) env->GetBooleanField(obj, logicOpField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::gettextureCompressionASTC_LDR() {
    return (bool) (jboolean) env->GetBooleanField(obj,
                                                  textureCompressionASTC_LDRField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getfillModeNonSolid() {
    return (bool) (jboolean) env->GetBooleanField(obj, fillModeNonSolidField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getimageCubeArray() {
    return (bool) (jboolean) env->GetBooleanField(obj, imageCubeArrayField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getsparseResidencyImage2D() {
    return (bool) (jboolean) env->GetBooleanField(obj, sparseResidencyImage2DField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getdualSrcBlend() {
    return (bool) (jboolean) env->GetBooleanField(obj, dualSrcBlendField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getshaderResourceResidency() {
    return (bool) (jboolean) env->GetBooleanField(obj, shaderResourceResidencyField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getmultiViewport() {
    return (bool) (jboolean) env->GetBooleanField(obj, multiViewportField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getshaderStorageBufferArrayDynamicIndexing() {
    return (bool) (jboolean) env->GetBooleanField(obj,
                                                  shaderStorageBufferArrayDynamicIndexingField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getinheritedQueries() {
    return (bool) (jboolean) env->GetBooleanField(obj, inheritedQueriesField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getshaderTessellationAndGeometryPointSize() {
    return (bool) (jboolean) env->GetBooleanField(obj,
                                                  shaderTessellationAndGeometryPointSizeField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getshaderImageGatherExtended() {
    return (bool) (jboolean) env->GetBooleanField(obj, shaderImageGatherExtendedField); // primitive
}

void
VkPhysicalDeviceFeaturesAccessor::fromObject(VkPhysicalDeviceFeatures &clazzInfo) {
    clazzInfo.robustBufferAccess = getrobustBufferAccess(); // Object bool
    clazzInfo.fullDrawIndexUint32 = getfullDrawIndexUint32(); // Object bool
    clazzInfo.imageCubeArray = getimageCubeArray(); // Object bool
    clazzInfo.independentBlend = getindependentBlend(); // Object bool
    clazzInfo.geometryShader = getgeometryShader(); // Object bool
    clazzInfo.tessellationShader = gettessellationShader(); // Object bool
    clazzInfo.sampleRateShading = getsampleRateShading(); // Object bool
    clazzInfo.dualSrcBlend = getdualSrcBlend(); // Object bool
    clazzInfo.logicOp = getlogicOp(); // Object bool
    clazzInfo.multiDrawIndirect = getmultiDrawIndirect(); // Object bool
    clazzInfo.drawIndirectFirstInstance = getdrawIndirectFirstInstance(); // Object bool
    clazzInfo.depthClamp = getdepthClamp(); // Object bool
    clazzInfo.depthBiasClamp = getdepthBiasClamp(); // Object bool
    clazzInfo.fillModeNonSolid = getfillModeNonSolid(); // Object bool
    clazzInfo.depthBounds = getdepthBounds(); // Object bool
    clazzInfo.wideLines = getwideLines(); // Object bool
    clazzInfo.largePoints = getlargePoints(); // Object bool
    clazzInfo.alphaToOne = getalphaToOne(); // Object bool
    clazzInfo.multiViewport = getmultiViewport(); // Object bool
    clazzInfo.samplerAnisotropy = getsamplerAnisotropy(); // Object bool
    clazzInfo.textureCompressionETC2 = gettextureCompressionETC2(); // Object bool
    clazzInfo.textureCompressionASTC_LDR = gettextureCompressionASTC_LDR(); // Object bool
    clazzInfo.textureCompressionBC = gettextureCompressionBC(); // Object bool
    clazzInfo.occlusionQueryPrecise = getocclusionQueryPrecise(); // Object bool
    clazzInfo.pipelineStatisticsQuery = getpipelineStatisticsQuery(); // Object bool
    clazzInfo.vertexPipelineStoresAndAtomics = getvertexPipelineStoresAndAtomics(); // Object bool
    clazzInfo.fragmentStoresAndAtomics = getfragmentStoresAndAtomics(); // Object bool
    clazzInfo.shaderTessellationAndGeometryPointSize = getshaderTessellationAndGeometryPointSize(); // Object bool
    clazzInfo.shaderImageGatherExtended = getshaderImageGatherExtended(); // Object bool
    clazzInfo.shaderStorageImageExtendedFormats = getshaderStorageImageExtendedFormats(); // Object bool
    clazzInfo.shaderStorageImageMultisample = getshaderStorageImageMultisample(); // Object bool
    clazzInfo.shaderStorageImageReadWithoutFormat = getshaderStorageImageReadWithoutFormat(); // Object bool
    clazzInfo.shaderStorageImageWriteWithoutFormat = getshaderStorageImageWriteWithoutFormat(); // Object bool
    clazzInfo.shaderUniformBufferArrayDynamicIndexing = getshaderUniformBufferArrayDynamicIndexing(); // Object bool
    clazzInfo.shaderSampledImageArrayDynamicIndexing = getshaderSampledImageArrayDynamicIndexing(); // Object bool
    clazzInfo.shaderStorageBufferArrayDynamicIndexing = getshaderStorageBufferArrayDynamicIndexing(); // Object bool
    clazzInfo.shaderStorageImageArrayDynamicIndexing = getshaderStorageImageArrayDynamicIndexing(); // Object bool
    clazzInfo.shaderClipDistance = getshaderClipDistance(); // Object bool
    clazzInfo.shaderCullDistance = getshaderCullDistance(); // Object bool
    clazzInfo.shaderFloat64 = getshaderFloat64(); // Object bool
    clazzInfo.shaderInt64 = getshaderInt64(); // Object bool
    clazzInfo.shaderInt16 = getshaderInt16(); // Object bool
    clazzInfo.shaderResourceResidency = getshaderResourceResidency(); // Object bool
    clazzInfo.shaderResourceMinLod = getshaderResourceMinLod(); // Object bool
    clazzInfo.sparseBinding = getsparseBinding(); // Object bool
    clazzInfo.sparseResidencyBuffer = getsparseResidencyBuffer(); // Object bool
    clazzInfo.sparseResidencyImage2D = getsparseResidencyImage2D(); // Object bool
    clazzInfo.sparseResidencyImage3D = getsparseResidencyImage3D(); // Object bool
    clazzInfo.sparseResidency2Samples = getsparseResidency2Samples(); // Object bool
    clazzInfo.sparseResidency4Samples = getsparseResidency4Samples(); // Object bool
    clazzInfo.sparseResidency8Samples = getsparseResidency8Samples(); // Object bool
    clazzInfo.sparseResidency16Samples = getsparseResidency16Samples(); // Object bool
    clazzInfo.sparseResidencyAliased = getsparseResidencyAliased(); // Object bool
    clazzInfo.variableMultisampleRate = getvariableMultisampleRate(); // Object bool
    clazzInfo.inheritedQueries = getinheritedQueries(); // Object bool
}

bool
VkPhysicalDeviceFeaturesAccessor::getrobustBufferAccess() {
    return (bool) (jboolean) env->GetBooleanField(obj, robustBufferAccessField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getsparseResidencyImage3D() {
    return (bool) (jboolean) env->GetBooleanField(obj, sparseResidencyImage3DField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getsparseResidencyAliased() {
    return (bool) (jboolean) env->GetBooleanField(obj, sparseResidencyAliasedField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getocclusionQueryPrecise() {
    return (bool) (jboolean) env->GetBooleanField(obj, occlusionQueryPreciseField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getshaderStorageImageWriteWithoutFormat() {
    return (bool) (jboolean) env->GetBooleanField(obj,
                                                  shaderStorageImageWriteWithoutFormatField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getshaderResourceMinLod() {
    return (bool) (jboolean) env->GetBooleanField(obj, shaderResourceMinLodField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getvariableMultisampleRate() {
    return (bool) (jboolean) env->GetBooleanField(obj, variableMultisampleRateField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::gettextureCompressionETC2() {
    return (bool) (jboolean) env->GetBooleanField(obj, textureCompressionETC2Field); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getshaderFloat64() {
    return (bool) (jboolean) env->GetBooleanField(obj, shaderFloat64Field); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getshaderCullDistance() {
    return (bool) (jboolean) env->GetBooleanField(obj, shaderCullDistanceField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getgeometryShader() {
    return (bool) (jboolean) env->GetBooleanField(obj, geometryShaderField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getindependentBlend() {
    return (bool) (jboolean) env->GetBooleanField(obj, independentBlendField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getsampleRateShading() {
    return (bool) (jboolean) env->GetBooleanField(obj, sampleRateShadingField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getmultiDrawIndirect() {
    return (bool) (jboolean) env->GetBooleanField(obj, multiDrawIndirectField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::gettextureCompressionBC() {
    return (bool) (jboolean) env->GetBooleanField(obj, textureCompressionBCField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getdepthClamp() {
    return (bool) (jboolean) env->GetBooleanField(obj, depthClampField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getlargePoints() {
    return (bool) (jboolean) env->GetBooleanField(obj, largePointsField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getsparseBinding() {
    return (bool) (jboolean) env->GetBooleanField(obj, sparseBindingField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getsamplerAnisotropy() {
    return (bool) (jboolean) env->GetBooleanField(obj, samplerAnisotropyField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getdrawIndirectFirstInstance() {
    return (bool) (jboolean) env->GetBooleanField(obj, drawIndirectFirstInstanceField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getvertexPipelineStoresAndAtomics() {
    return (bool) (jboolean) env->GetBooleanField(obj,
                                                  vertexPipelineStoresAndAtomicsField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getdepthBiasClamp() {
    return (bool) (jboolean) env->GetBooleanField(obj, depthBiasClampField); // primitive
}

bool
VkPhysicalDeviceFeaturesAccessor::getsparseResidency16Samples() {
    return (bool) (jboolean) env->GetBooleanField(obj, sparseResidency16SamplesField); // primitive
}

VkPhysicalDeviceFeaturesAccessor::~VkPhysicalDeviceFeaturesAccessor() {
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

