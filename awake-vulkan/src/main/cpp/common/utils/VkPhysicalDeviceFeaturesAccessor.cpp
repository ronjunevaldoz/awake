/*
 *  VkPhysicalDeviceFeaturesAccessor.h
 *  Vulkan accessor e C++ header file
 *  Created by Ron June Valdoz on Wed Aug 09 11:53:19 PST 2023
 */

#include <jni.h>
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkPhysicalDeviceFeaturesAccessor {
private:
    JNIEnv *env;
private:
    jobject obj;
private:
    jclass clazz;
private:
    jfieldID robustBufferAccessField;
private:
    jfieldID fullDrawIndexUint32Field;
private:
    jfieldID imageCubeArrayField;
private:
    jfieldID independentBlendField;
private:
    jfieldID geometryShaderField;
private:
    jfieldID tessellationShaderField;
private:
    jfieldID sampleRateShadingField;
private:
    jfieldID dualSrcBlendField;
private:
    jfieldID logicOpField;
private:
    jfieldID multiDrawIndirectField;
private:
    jfieldID drawIndirectFirstInstanceField;
private:
    jfieldID depthClampField;
private:
    jfieldID depthBiasClampField;
private:
    jfieldID fillModeNonSolidField;
private:
    jfieldID depthBoundsField;
private:
    jfieldID wideLinesField;
private:
    jfieldID largePointsField;
private:
    jfieldID alphaToOneField;
private:
    jfieldID multiViewportField;
private:
    jfieldID samplerAnisotropyField;
private:
    jfieldID textureCompressionETC2Field;
private:
    jfieldID textureCompressionASTC_LDRField;
private:
    jfieldID textureCompressionBCField;
private:
    jfieldID occlusionQueryPreciseField;
private:
    jfieldID pipelineStatisticsQueryField;
private:
    jfieldID vertexPipelineStoresAndAtomicsField;
private:
    jfieldID fragmentStoresAndAtomicsField;
private:
    jfieldID shaderTessellationAndGeometryPointSizeField;
private:
    jfieldID shaderImageGatherExtendedField;
private:
    jfieldID shaderStorageImageExtendedFormatsField;
private:
    jfieldID shaderStorageImageMultisampleField;
private:
    jfieldID shaderStorageImageReadWithoutFormatField;
private:
    jfieldID shaderStorageImageWriteWithoutFormatField;
private:
    jfieldID shaderUniformBufferArrayDynamicIndexingField;
private:
    jfieldID shaderSampledImageArrayDynamicIndexingField;
private:
    jfieldID shaderStorageBufferArrayDynamicIndexingField;
private:
    jfieldID shaderStorageImageArrayDynamicIndexingField;
private:
    jfieldID shaderClipDistanceField;
private:
    jfieldID shaderCullDistanceField;
private:
    jfieldID shaderFloat64Field;
private:
    jfieldID shaderInt64Field;
private:
    jfieldID shaderInt16Field;
private:
    jfieldID shaderResourceResidencyField;
private:
    jfieldID shaderResourceMinLodField;
private:
    jfieldID sparseBindingField;
private:
    jfieldID sparseResidencyBufferField;
private:
    jfieldID sparseResidencyImage2DField;
private:
    jfieldID sparseResidencyImage3DField;
private:
    jfieldID sparseResidency2SamplesField;
private:
    jfieldID sparseResidency4SamplesField;
private:
    jfieldID sparseResidency8SamplesField;
private:
    jfieldID sparseResidency16SamplesField;
private:
    jfieldID sparseResidencyAliasedField;
private:
    jfieldID variableMultisampleRateField;
private:
    jfieldID inheritedQueriesField;
public:
    VkPhysicalDeviceFeaturesAccessor(JNIEnv *env, jobject obj) {
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
        vertexPipelineStoresAndAtomicsField = env->GetFieldID(clazz,
                                                              "vertexPipelineStoresAndAtomics",
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

    bool getrobustBufferAccess() {
        return (bool) (jboolean) env->GetBooleanField(obj, robustBufferAccessField); // primitive
    }

    bool getfullDrawIndexUint32() {
        return (bool) (jboolean) env->GetBooleanField(obj, fullDrawIndexUint32Field); // primitive
    }

    bool getimageCubeArray() {
        return (bool) (jboolean) env->GetBooleanField(obj, imageCubeArrayField); // primitive
    }

    bool getindependentBlend() {
        return (bool) (jboolean) env->GetBooleanField(obj, independentBlendField); // primitive
    }

    bool getgeometryShader() {
        return (bool) (jboolean) env->GetBooleanField(obj, geometryShaderField); // primitive
    }

    bool gettessellationShader() {
        return (bool) (jboolean) env->GetBooleanField(obj, tessellationShaderField); // primitive
    }

    bool getsampleRateShading() {
        return (bool) (jboolean) env->GetBooleanField(obj, sampleRateShadingField); // primitive
    }

    bool getdualSrcBlend() {
        return (bool) (jboolean) env->GetBooleanField(obj, dualSrcBlendField); // primitive
    }

    bool getlogicOp() {
        return (bool) (jboolean) env->GetBooleanField(obj, logicOpField); // primitive
    }

    bool getmultiDrawIndirect() {
        return (bool) (jboolean) env->GetBooleanField(obj, multiDrawIndirectField); // primitive
    }

    bool getdrawIndirectFirstInstance() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      drawIndirectFirstInstanceField); // primitive
    }

    bool getdepthClamp() {
        return (bool) (jboolean) env->GetBooleanField(obj, depthClampField); // primitive
    }

    bool getdepthBiasClamp() {
        return (bool) (jboolean) env->GetBooleanField(obj, depthBiasClampField); // primitive
    }

    bool getfillModeNonSolid() {
        return (bool) (jboolean) env->GetBooleanField(obj, fillModeNonSolidField); // primitive
    }

    bool getdepthBounds() {
        return (bool) (jboolean) env->GetBooleanField(obj, depthBoundsField); // primitive
    }

    bool getwideLines() {
        return (bool) (jboolean) env->GetBooleanField(obj, wideLinesField); // primitive
    }

    bool getlargePoints() {
        return (bool) (jboolean) env->GetBooleanField(obj, largePointsField); // primitive
    }

    bool getalphaToOne() {
        return (bool) (jboolean) env->GetBooleanField(obj, alphaToOneField); // primitive
    }

    bool getmultiViewport() {
        return (bool) (jboolean) env->GetBooleanField(obj, multiViewportField); // primitive
    }

    bool getsamplerAnisotropy() {
        return (bool) (jboolean) env->GetBooleanField(obj, samplerAnisotropyField); // primitive
    }

    bool gettextureCompressionETC2() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      textureCompressionETC2Field); // primitive
    }

    bool gettextureCompressionASTC_LDR() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      textureCompressionASTC_LDRField); // primitive
    }

    bool gettextureCompressionBC() {
        return (bool) (jboolean) env->GetBooleanField(obj, textureCompressionBCField); // primitive
    }

    bool getocclusionQueryPrecise() {
        return (bool) (jboolean) env->GetBooleanField(obj, occlusionQueryPreciseField); // primitive
    }

    bool getpipelineStatisticsQuery() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      pipelineStatisticsQueryField); // primitive
    }

    bool getvertexPipelineStoresAndAtomics() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      vertexPipelineStoresAndAtomicsField); // primitive
    }

    bool getfragmentStoresAndAtomics() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      fragmentStoresAndAtomicsField); // primitive
    }

    bool getshaderTessellationAndGeometryPointSize() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      shaderTessellationAndGeometryPointSizeField); // primitive
    }

    bool getshaderImageGatherExtended() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      shaderImageGatherExtendedField); // primitive
    }

    bool getshaderStorageImageExtendedFormats() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      shaderStorageImageExtendedFormatsField); // primitive
    }

    bool getshaderStorageImageMultisample() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      shaderStorageImageMultisampleField); // primitive
    }

    bool getshaderStorageImageReadWithoutFormat() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      shaderStorageImageReadWithoutFormatField); // primitive
    }

    bool getshaderStorageImageWriteWithoutFormat() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      shaderStorageImageWriteWithoutFormatField); // primitive
    }

    bool getshaderUniformBufferArrayDynamicIndexing() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      shaderUniformBufferArrayDynamicIndexingField); // primitive
    }

    bool getshaderSampledImageArrayDynamicIndexing() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      shaderSampledImageArrayDynamicIndexingField); // primitive
    }

    bool getshaderStorageBufferArrayDynamicIndexing() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      shaderStorageBufferArrayDynamicIndexingField); // primitive
    }

    bool getshaderStorageImageArrayDynamicIndexing() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      shaderStorageImageArrayDynamicIndexingField); // primitive
    }

    bool getshaderClipDistance() {
        return (bool) (jboolean) env->GetBooleanField(obj, shaderClipDistanceField); // primitive
    }

    bool getshaderCullDistance() {
        return (bool) (jboolean) env->GetBooleanField(obj, shaderCullDistanceField); // primitive
    }

    bool getshaderFloat64() {
        return (bool) (jboolean) env->GetBooleanField(obj, shaderFloat64Field); // primitive
    }

    bool getshaderInt64() {
        return (bool) (jboolean) env->GetBooleanField(obj, shaderInt64Field); // primitive
    }

    bool getshaderInt16() {
        return (bool) (jboolean) env->GetBooleanField(obj, shaderInt16Field); // primitive
    }

    bool getshaderResourceResidency() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      shaderResourceResidencyField); // primitive
    }

    bool getshaderResourceMinLod() {
        return (bool) (jboolean) env->GetBooleanField(obj, shaderResourceMinLodField); // primitive
    }

    bool getsparseBinding() {
        return (bool) (jboolean) env->GetBooleanField(obj, sparseBindingField); // primitive
    }

    bool getsparseResidencyBuffer() {
        return (bool) (jboolean) env->GetBooleanField(obj, sparseResidencyBufferField); // primitive
    }

    bool getsparseResidencyImage2D() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      sparseResidencyImage2DField); // primitive
    }

    bool getsparseResidencyImage3D() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      sparseResidencyImage3DField); // primitive
    }

    bool getsparseResidency2Samples() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      sparseResidency2SamplesField); // primitive
    }

    bool getsparseResidency4Samples() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      sparseResidency4SamplesField); // primitive
    }

    bool getsparseResidency8Samples() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      sparseResidency8SamplesField); // primitive
    }

    bool getsparseResidency16Samples() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      sparseResidency16SamplesField); // primitive
    }

    bool getsparseResidencyAliased() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      sparseResidencyAliasedField); // primitive
    }

    bool getvariableMultisampleRate() {
        return (bool) (jboolean) env->GetBooleanField(obj,
                                                      variableMultisampleRateField); // primitive
    }

    bool getinheritedQueries() {
        return (bool) (jboolean) env->GetBooleanField(obj, inheritedQueriesField); // primitive
    }

    VkPhysicalDeviceFeatures fromObject() {
        VkPhysicalDeviceFeatures clazzInfo{};
        clazzInfo.robustBufferAccess = getrobustBufferAccess(); // Object
        clazzInfo.fullDrawIndexUint32 = getfullDrawIndexUint32(); // Object
        clazzInfo.imageCubeArray = getimageCubeArray(); // Object
        clazzInfo.independentBlend = getindependentBlend(); // Object
        clazzInfo.geometryShader = getgeometryShader(); // Object
        clazzInfo.tessellationShader = gettessellationShader(); // Object
        clazzInfo.sampleRateShading = getsampleRateShading(); // Object
        clazzInfo.dualSrcBlend = getdualSrcBlend(); // Object
        clazzInfo.logicOp = getlogicOp(); // Object
        clazzInfo.multiDrawIndirect = getmultiDrawIndirect(); // Object
        clazzInfo.drawIndirectFirstInstance = getdrawIndirectFirstInstance(); // Object
        clazzInfo.depthClamp = getdepthClamp(); // Object
        clazzInfo.depthBiasClamp = getdepthBiasClamp(); // Object
        clazzInfo.fillModeNonSolid = getfillModeNonSolid(); // Object
        clazzInfo.depthBounds = getdepthBounds(); // Object
        clazzInfo.wideLines = getwideLines(); // Object
        clazzInfo.largePoints = getlargePoints(); // Object
        clazzInfo.alphaToOne = getalphaToOne(); // Object
        clazzInfo.multiViewport = getmultiViewport(); // Object
        clazzInfo.samplerAnisotropy = getsamplerAnisotropy(); // Object
        clazzInfo.textureCompressionETC2 = gettextureCompressionETC2(); // Object
        clazzInfo.textureCompressionASTC_LDR = gettextureCompressionASTC_LDR(); // Object
        clazzInfo.textureCompressionBC = gettextureCompressionBC(); // Object
        clazzInfo.occlusionQueryPrecise = getocclusionQueryPrecise(); // Object
        clazzInfo.pipelineStatisticsQuery = getpipelineStatisticsQuery(); // Object
        clazzInfo.vertexPipelineStoresAndAtomics = getvertexPipelineStoresAndAtomics(); // Object
        clazzInfo.fragmentStoresAndAtomics = getfragmentStoresAndAtomics(); // Object
        clazzInfo.shaderTessellationAndGeometryPointSize = getshaderTessellationAndGeometryPointSize(); // Object
        clazzInfo.shaderImageGatherExtended = getshaderImageGatherExtended(); // Object
        clazzInfo.shaderStorageImageExtendedFormats = getshaderStorageImageExtendedFormats(); // Object
        clazzInfo.shaderStorageImageMultisample = getshaderStorageImageMultisample(); // Object
        clazzInfo.shaderStorageImageReadWithoutFormat = getshaderStorageImageReadWithoutFormat(); // Object
        clazzInfo.shaderStorageImageWriteWithoutFormat = getshaderStorageImageWriteWithoutFormat(); // Object
        clazzInfo.shaderUniformBufferArrayDynamicIndexing = getshaderUniformBufferArrayDynamicIndexing(); // Object
        clazzInfo.shaderSampledImageArrayDynamicIndexing = getshaderSampledImageArrayDynamicIndexing(); // Object
        clazzInfo.shaderStorageBufferArrayDynamicIndexing = getshaderStorageBufferArrayDynamicIndexing(); // Object
        clazzInfo.shaderStorageImageArrayDynamicIndexing = getshaderStorageImageArrayDynamicIndexing(); // Object
        clazzInfo.shaderClipDistance = getshaderClipDistance(); // Object
        clazzInfo.shaderCullDistance = getshaderCullDistance(); // Object
        clazzInfo.shaderFloat64 = getshaderFloat64(); // Object
        clazzInfo.shaderInt64 = getshaderInt64(); // Object
        clazzInfo.shaderInt16 = getshaderInt16(); // Object
        clazzInfo.shaderResourceResidency = getshaderResourceResidency(); // Object
        clazzInfo.shaderResourceMinLod = getshaderResourceMinLod(); // Object
        clazzInfo.sparseBinding = getsparseBinding(); // Object
        clazzInfo.sparseResidencyBuffer = getsparseResidencyBuffer(); // Object
        clazzInfo.sparseResidencyImage2D = getsparseResidencyImage2D(); // Object
        clazzInfo.sparseResidencyImage3D = getsparseResidencyImage3D(); // Object
        clazzInfo.sparseResidency2Samples = getsparseResidency2Samples(); // Object
        clazzInfo.sparseResidency4Samples = getsparseResidency4Samples(); // Object
        clazzInfo.sparseResidency8Samples = getsparseResidency8Samples(); // Object
        clazzInfo.sparseResidency16Samples = getsparseResidency16Samples(); // Object
        clazzInfo.sparseResidencyAliased = getsparseResidencyAliased(); // Object
        clazzInfo.variableMultisampleRate = getvariableMultisampleRate(); // Object
        clazzInfo.inheritedQueries = getinheritedQueries(); // Object
        return clazzInfo;
    }

    ~VkPhysicalDeviceFeaturesAccessor() {
        env->DeleteGlobalRef(obj);
        env->DeleteGlobalRef(clazz);
    }

};
