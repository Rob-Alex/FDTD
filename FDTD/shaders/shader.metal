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
    float4 position;
    float3 color;
};

struct vertexOut
{
   float4 position [[position]];
   half3 color;
};

vertexOut vertex vertexMain( uint vertexId [[vertex_id]],
                      device const float3* positions [[buffer(0)]],
                      device const float3* colors [[buffer(1)]] )
{
   vertexOut o;
   o.position = float4( positions[ vertexId ], 1.0 );
   o.color = half3 ( colors[ vertexId ] );
   return o;
}

half4 fragment fragmentMain( vertexOut in [[stage_in]] )
{
   return half4( in.color, 1.0 );
}

