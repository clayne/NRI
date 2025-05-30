// © 2021 NVIDIA Corporation

#pragma once

#define NRI_MESH_SHADER 1

NriNamespaceBegin

NriStruct(DrawMeshTasksDesc) {
    uint32_t x, y, z;
};

// Threadsafe: no
NriStruct(MeshShaderInterface) {
    // Command buffer
    // {
            // Draw
            void    (NRI_CALL *CmdDrawMeshTasks)            (NriRef(CommandBuffer) commandBuffer, const NriRef(DrawMeshTasksDesc) drawMeshTasksDesc);
            void    (NRI_CALL *CmdDrawMeshTasksIndirect)    (NriRef(CommandBuffer) commandBuffer, const NriRef(Buffer) buffer, uint64_t offset, uint32_t drawNum, uint32_t stride,
                                                            const NriPtr(Buffer) countBuffer, uint64_t countBufferOffset); // buffer contains "DrawMeshTasksDesc" commands
    // }
};

NriNamespaceEnd
