//
//  shader.metal
//  FDTD
//
//  Created by Robbie Alexander on 18/12/2023.
//

#include <metal_stdlib>
using namespace metal;

struct vertexIn
{
    float3 position[[attribute(0)]];
    float3 color[[attribute(1)]];
};

struct vertexOut
{
   float4 position [[position]];
   half3 color;
};

vertexOut vertex vertexMain(vertexIn i [[stage_in]])
{
    vertexOut o;
    o.position = float4(i.position, 1.0 );
    o.color = half3 (i.color);
    return o;
}

half4 fragment fragmentMain( vertexOut in [[stage_in]] )
{
   return half4( in.color, 1.0 );
}

