// © 2021 NVIDIA Corporation

#pragma once

#include "SharedExternal.h"

#include "DeviceVal.h"

namespace nri {

template <typename T>
struct DeviceObjectVal {
    DeviceObjectVal(DeviceVal& device, T* object = nullptr)
        : m_Name(device.GetStdAllocator())
        , m_Device(device)
        , m_Impl(object) {
    }

    inline T* GetImpl() const {
        return m_Impl;
    }

    inline const char* GetDebugName() const {
        return m_Name.c_str();
    }

    inline DeviceVal& GetDevice() const {
        return m_Device;
    }

    inline const CoreInterface& GetCoreInterface() const {
        return m_Device.GetCoreInterface();
    }

    inline const HelperInterface& GetHelperInterface() const {
        return m_Device.GetHelperInterface();
    }

    inline const StreamerInterface& GetStreamerInterface() const {
        return m_Device.GetStreamerInterface();
    }

    inline const WrapperD3D11Interface& GetWrapperD3D11Interface() const {
        return m_Device.GetWrapperD3D11Interface();
    }

    inline const WrapperD3D12Interface& GetWrapperD3D12Interface() const {
        return m_Device.GetWrapperD3D12Interface();
    }

    inline const WrapperVKInterface& GetWrapperVKInterface() const {
        return m_Device.GetWrapperVKInterface();
    }

    inline const SwapChainInterface& GetSwapChainInterface() const {
        return m_Device.GetSwapChainInterface();
    }

    inline const RayTracingInterface& GetRayTracingInterface() const {
        return m_Device.GetRayTracingInterface();
    }

    inline const MeshShaderInterface& GetMeshShaderInterface() const {
        return m_Device.GetMeshShaderInterface();
    }

    inline const LowLatencyInterface& GetLowLatencyInterface() const {
        return m_Device.GetLowLatencyInterface();
    }

protected:
    String m_Name;
    DeviceVal& m_Device;
    T* m_Impl = nullptr;
};

#define NRI_GET_IMPL(className, object) (object ? ((className##Val*)object)->GetImpl() : nullptr)

template <typename T>
inline DeviceVal& GetDeviceVal(T& object) {
    return ((DeviceObjectVal<T>&)object).GetDevice();
}

uint64_t GetMemorySizeD3D12(const MemoryD3D12Desc& memoryD3D12Desc);

constexpr std::array<const char*, (size_t)nri::DescriptorType::MAX_NUM> DESCRIPTOR_TYPE_NAME = {
    "SAMPLER",                   // SAMPLER,
    "CONSTANT_BUFFER",           // CONSTANT_BUFFER,
    "TEXTURE",                   // TEXTURE,
    "STORAGE_TEXTURE",           // STORAGE_TEXTURE,
    "BUFFER",                    // BUFFER,
    "STORAGE_BUFFER",            // STORAGE_BUFFER,
    "STRUCTURED_BUFFER",         // STRUCTURED_BUFFER,
    "STORAGE_STRUCTURED_BUFFER", // STORAGE_STRUCTURED_BUFFER,
    "ACCELERATION_STRUCTURE",    // ACCELERATION_STRUCTURE
};

constexpr const char* GetDescriptorTypeName(nri::DescriptorType descriptorType) {
    return DESCRIPTOR_TYPE_NAME[(uint32_t)descriptorType];
}

constexpr bool IsAccessMaskSupported(BufferUsageBits usage, AccessBits accessMask) {
    BufferUsageBits requiredUsage = BufferUsageBits::NONE;

    if (accessMask & AccessBits::VERTEX_BUFFER)
        requiredUsage |= BufferUsageBits::VERTEX_BUFFER;

    if (accessMask & AccessBits::INDEX_BUFFER)
        requiredUsage |= BufferUsageBits::INDEX_BUFFER;

    if (accessMask & AccessBits::CONSTANT_BUFFER)
        requiredUsage |= BufferUsageBits::CONSTANT_BUFFER;

    if (accessMask & AccessBits::ARGUMENT_BUFFER)
        requiredUsage |= BufferUsageBits::ARGUMENT_BUFFER;

    if (accessMask & AccessBits::SHADER_RESOURCE)
        requiredUsage |= BufferUsageBits::SHADER_RESOURCE;

    if (accessMask & AccessBits::SHADER_RESOURCE_STORAGE)
        requiredUsage |= BufferUsageBits::SHADER_RESOURCE_STORAGE;

    if (accessMask & AccessBits::COLOR_ATTACHMENT)
        return false;

    if (accessMask & AccessBits::DEPTH_STENCIL_ATTACHMENT_WRITE)
        return false;

    if (accessMask & AccessBits::DEPTH_STENCIL_ATTACHMENT_READ)
        return false;

    if (accessMask & AccessBits::ACCELERATION_STRUCTURE_READ)
        return false;

    if (accessMask & AccessBits::ACCELERATION_STRUCTURE_WRITE)
        return false;

    if (accessMask & AccessBits::SHADING_RATE_ATTACHMENT)
        return false;

    return (uint32_t)(requiredUsage & usage) == (uint32_t)requiredUsage;
}

constexpr bool IsAccessMaskSupported(TextureUsageBits usage, AccessBits accessMask) {
    TextureUsageBits requiredUsage = TextureUsageBits::NONE;

    if (accessMask & AccessBits::VERTEX_BUFFER)
        return false;

    if (accessMask & AccessBits::INDEX_BUFFER)
        return false;

    if (accessMask & AccessBits::CONSTANT_BUFFER)
        return false;

    if (accessMask & AccessBits::ARGUMENT_BUFFER)
        return false;

    if (accessMask & AccessBits::SHADER_RESOURCE)
        requiredUsage |= TextureUsageBits::SHADER_RESOURCE;

    if (accessMask & AccessBits::SHADER_RESOURCE_STORAGE)
        requiredUsage |= TextureUsageBits::SHADER_RESOURCE_STORAGE;

    if (accessMask & AccessBits::COLOR_ATTACHMENT)
        requiredUsage |= TextureUsageBits::COLOR_ATTACHMENT;

    if (accessMask & AccessBits::DEPTH_STENCIL_ATTACHMENT_WRITE)
        requiredUsage |= TextureUsageBits::DEPTH_STENCIL_ATTACHMENT;

    if (accessMask & AccessBits::DEPTH_STENCIL_ATTACHMENT_READ)
        requiredUsage |= TextureUsageBits::DEPTH_STENCIL_ATTACHMENT;

    if (accessMask & AccessBits::SHADING_RATE_ATTACHMENT)
        requiredUsage |= TextureUsageBits::SHADING_RATE_ATTACHMENT;

    if (accessMask & AccessBits::ACCELERATION_STRUCTURE_READ)
        return false;

    if (accessMask & AccessBits::ACCELERATION_STRUCTURE_WRITE)
        return false;

    return (uint32_t)(requiredUsage & usage) == (uint32_t)requiredUsage;
}

constexpr std::array<TextureUsageBits, (size_t)Layout::MAX_NUM> TEXTURE_USAGE_FOR_TEXTURE_LAYOUT_TABLE = {
    TextureUsageBits::NONE,                     // UNKNOWN
    TextureUsageBits::COLOR_ATTACHMENT,         // COLOR_ATTACHMENT
    TextureUsageBits::DEPTH_STENCIL_ATTACHMENT, // DEPTH_STENCIL_ATTACHMENT
    TextureUsageBits::DEPTH_STENCIL_ATTACHMENT, // DEPTH_STENCIL_READONLY
    TextureUsageBits::SHADER_RESOURCE,          // SHADER_RESOURCE
    TextureUsageBits::SHADER_RESOURCE_STORAGE,  // SHADER_RESOURCE_STORAGE
    TextureUsageBits::NONE,                     // COPY_SOURCE
    TextureUsageBits::NONE,                     // COPY_DESTINATION
    TextureUsageBits::NONE,                     // PRESENT
    TextureUsageBits::SHADING_RATE_ATTACHMENT,  // SHADING_RATE_ATTACHMENT
};

constexpr bool IsTextureLayoutSupported(TextureUsageBits usage, Layout textureLayout) {
    const TextureUsageBits requiredMask = TEXTURE_USAGE_FOR_TEXTURE_LAYOUT_TABLE[(size_t)textureLayout];

    return (uint32_t)(requiredMask & usage) == (uint32_t)requiredMask;
}

} // namespace nri
