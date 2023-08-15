/*
 *  VkPhysicalDeviceFeaturesAccessor.h
 *  Vulkan accessor for VkPhysicalDeviceFeatures
 *  Created by Ron June Valdoz */

#ifndef VKPHYSICALDEVICEFEATURESACCESSOR_H
#define VKPHYSICALDEVICEFEATURESACCESSOR_H

#include <jni.h>
#include <vulkan/vulkan_core.h>
#include <string>
#include <vector>
#include <enum_utils.h>

class VkPhysicalDeviceFeaturesAccessor {
private:
    JNIEnv *env;
    jobject obj;
    jclass clazz;
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
    VkPhysicalDeviceFeaturesAccessor(JNIEnv *env, jobject obj);

    bool gettessellationShader();

    bool getfullDrawIndexUint32();

    bool getdepthBounds();

    bool getsparseResidency4Samples();

    bool getpipelineStatisticsQuery();

    bool getsparseResidencyBuffer();

    bool getshaderStorageImageReadWithoutFormat();

    bool getsparseResidency8Samples();

    bool getalphaToOne();

    bool getshaderStorageImageMultisample();

    bool getshaderStorageImageArrayDynamicIndexing();

    bool getshaderInt64();

    bool getwideLines();

    bool getshaderClipDistance();

    bool getshaderInt16();

    bool getshaderUniformBufferArrayDynamicIndexing();

    bool getfragmentStoresAndAtomics();

    bool getshaderStorageImageExtendedFormats();

    bool getsparseResidency2Samples();

    bool getshaderSampledImageArrayDynamicIndexing();

    bool getlogicOp();

    bool gettextureCompressionASTC_LDR();

    bool getfillModeNonSolid();

    bool getimageCubeArray();

    bool getsparseResidencyImage2D();

    bool getdualSrcBlend();

    bool getshaderResourceResidency();

    bool getmultiViewport();

    bool getshaderStorageBufferArrayDynamicIndexing();

    bool getinheritedQueries();

    bool getshaderTessellationAndGeometryPointSize();

    bool getshaderImageGatherExtended();

    void fromObject(VkPhysicalDeviceFeatures &clazzInfo);

    bool getrobustBufferAccess();

    bool getsparseResidencyImage3D();

    bool getsparseResidencyAliased();

    bool getocclusionQueryPrecise();

    bool getshaderStorageImageWriteWithoutFormat();

    bool getshaderResourceMinLod();

    bool getvariableMultisampleRate();

    bool gettextureCompressionETC2();

    bool getshaderFloat64();

    bool getshaderCullDistance();

    bool getgeometryShader();

    bool getindependentBlend();

    bool getsampleRateShading();

    bool getmultiDrawIndirect();

    bool gettextureCompressionBC();

    bool getdepthClamp();

    bool getlargePoints();

    bool getsparseBinding();

    bool getsamplerAnisotropy();

    bool getdrawIndirectFirstInstance();

    bool getvertexPipelineStoresAndAtomics();

    bool getdepthBiasClamp();

    bool getsparseResidency16Samples();

    ~VkPhysicalDeviceFeaturesAccessor();
};

#endif // VKPHYSICALDEVICEFEATURESACCESSOR_H