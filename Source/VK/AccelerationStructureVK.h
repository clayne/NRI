// © 2021 NVIDIA Corporation

#pragma once

namespace nri {

struct DeviceVK;
struct BufferVK;

struct AccelerationStructureVK {
    inline AccelerationStructureVK(DeviceVK& device)
        : m_Device(device) {
    }

    inline VkAccelerationStructureKHR GetHandle() const {
        return m_Handle;
    }

    inline DeviceVK& GetDevice() const {
        return m_Device;
    }

    inline BufferVK* GetBuffer() const {
        return m_Buffer;
    }

    ~AccelerationStructureVK();

    Result Create(const AccelerationStructureDesc& accelerationStructureDesc);
    Result Create(const AccelerationStructureVKDesc& accelerationStructureDesc);
    Result Create(const AllocateAccelerationStructureDesc& accelerationStructureDesc);
    Result FinishCreation();

    //================================================================================================================
    // NRI
    //================================================================================================================

    inline uint64_t GetUpdateScratchBufferSize() const {
        return m_UpdateScratchSize;
    }

    inline uint64_t GetBuildScratchBufferSize() const {
        return m_BuildScratchSize;
    }

    inline VkDeviceAddress GetDeviceAddress() const {
        return m_DeviceAddress;
    }

    void SetDebugName(const char* name);
    Result CreateDescriptor(Descriptor*& descriptor) const;

private:
    DeviceVK& m_Device;
    VkAccelerationStructureKHR m_Handle = VK_NULL_HANDLE;
    VkDeviceAddress m_DeviceAddress = 0;
    BufferVK* m_Buffer = nullptr;
    uint64_t m_BuildScratchSize = 0;
    uint64_t m_UpdateScratchSize = 0;
    uint64_t m_AccelerationStructureSize = 0;                                  // needed only for FinishCreation
    VkAccelerationStructureTypeKHR m_Type = (VkAccelerationStructureTypeKHR)0; // needed only for FinishCreation
    bool m_OwnsNativeObjects = true;
};

} // namespace nri