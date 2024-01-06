//
//  config.h
//  FDTD
//
//  Created by Robbie Alexander on 18/12/2023.
//

#ifndef config_hpp
#define config_hpp

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>

#include <simd/simd.h>
#include <fstream>
#include <sstream>

struct Vertex {
    simd::float3 pos;   //3d coord
    simd::float3 color; //R G B 
};

#endif /* config_h */
