// © 2021 NVIDIA Corporation

#pragma region[  Core  ]

static void NRI_CALL SetBufferDebugName(Buffer& buffer, const char* name) {
    ((BufferD3D12&)buffer).SetDebugName(name);
}

static uint64_t NRI_CALL GetBufferNativeObject(const Buffer& buffer) {
    if (!(&buffer))
        return 0;

    return uint64_t((ID3D12Resource*)((BufferD3D12&)buffer));
}

static void* NRI_CALL MapBuffer(Buffer& buffer, uint64_t offset, uint64_t size) {
    return ((BufferD3D12&)buffer).Map(offset, size);
}

static void NRI_CALL UnmapBuffer(Buffer& buffer) {
    ((BufferD3D12&)buffer).Unmap();
}

#pragma endregion

Define_Core_Buffer_PartiallyFillFunctionTable(D3D12);
