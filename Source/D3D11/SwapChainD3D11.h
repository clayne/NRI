// © 2021 NVIDIA Corporation

#pragma once

struct IDXGISwapChain4;
typedef IDXGISwapChain4 IDXGISwapChainBest;

namespace nri {

struct TextureD3D11;

struct SwapChainD3D11 final : public DisplayDescHelper, DebugNameBase {
    inline SwapChainD3D11(DeviceD3D11& device)
        : m_Device(device)
        , m_Textures(device.GetStdAllocator()) {
    }

    inline DeviceD3D11& GetDevice() const {
        return m_Device;
    }

    ~SwapChainD3D11();

    Result Create(const SwapChainDesc& swapChainDesc);

    //================================================================================================================
    // DebugNameBase
    //================================================================================================================

    void SetDebugName(const char* name) DEBUG_NAME_OVERRIDE {
        SET_D3D_DEBUG_OBJECT_NAME(m_SwapChain, name);
    }

    //================================================================================================================
    // NRI
    //================================================================================================================

    inline Result GetDisplayDesc(DisplayDesc& displayDesc) {
        return DisplayDescHelper::GetDisplayDesc(m_Desc.window.windows.hwnd, displayDesc);
    }

    Texture* const* GetTextures(uint32_t& textureNum) const;
    uint32_t AcquireNextTexture();
    Result WaitForPresent();
    Result Present();

    Result SetLatencySleepMode(const LatencySleepMode& latencySleepMode);
    Result SetLatencyMarker(LatencyMarker latencyMarker);
    Result LatencySleep();
    Result GetLatencyReport(LatencyReport& latencyReport);

private:
    DeviceD3D11& m_Device;
    ComPtr<IDXGISwapChainBest> m_SwapChain;
    Vector<TextureD3D11*> m_Textures;
    SwapChainDesc m_Desc = {};
    DisplayDescHelper m_DisplayDescHelper;
    HANDLE m_FrameLatencyWaitableObject = nullptr;
    uint64_t m_PresentId = 0;
    UINT m_Flags = 0;
    uint8_t m_Version = 0;
};

} // namespace nri
