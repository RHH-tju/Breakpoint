#include "RootSignature.hlsl"

cbuffer CameraMatrices : register(b0) {
    float4x4 viewMatrix;        // 16 floats
    float4x4 projectionMatrix;  // 16 floats
};

// Max array size is 64KB
// Not applicable to particles, just for other instanced meshes
// Can also make more CBV's if we want
#define MAX_MODEL_MATRIX_SIZE 1000

// Model Matrices for each instance
// Model matrices for instances in CBV at register b1
cbuffer ModelMatrices : register(b1) {
    float4x4 modelMatrices[MAX_MODEL_MATRIX_SIZE]; // Array of model matrices
};

struct VSInput
{
    float3 Position : POSITION;      // Input position from vertex buffer
    uint InstanceID : SV_InstanceID; // Instance ID for indexing into model matrices
};

[RootSignature(ROOTSIG)]
float4 main(VSInput input) : SV_Position
{
    // Retrieve the model matrix for the current instance using the InstanceID
    float4x4 modelMatrix = modelMatrices[input.InstanceID];

    // Apply the model, view, and projection transformations
    float4 worldPos = mul(modelMatrix, float4(input.Position, 1.0));
    float4 viewPos = mul(viewMatrix, worldPos);
    return mul(projectionMatrix, viewPos);
}