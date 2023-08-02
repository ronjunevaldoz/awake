//
// Created by Ron June Valdoz on 8/2/23.
//

#ifndef AWAKE_VKPHYSICALDEVICEFEATURESCONVERTER_H
#define AWAKE_VKPHYSICALDEVICEFEATURESCONVERTER_H


#include <jni.h>
#include <vulkan/vulkan.h>

class VkPhysicalDeviceFeaturesConverter {
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
    JNIEnv *env;

public:
    explicit VkPhysicalDeviceFeaturesConverter(JNIEnv *env);

    void extract(jobject pEnabledFeaturesObj,
                 VkPhysicalDeviceFeatures &deviceFeatures);

    jobject toObject(VkPhysicalDeviceFeatures &deviceFeatures);

    ~VkPhysicalDeviceFeaturesConverter();
};


#endif //AWAKE_VKPHYSICALDEVICEFEATURESCONVERTER_H
