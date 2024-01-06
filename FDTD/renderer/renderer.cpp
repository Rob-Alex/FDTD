
#include "renderer.hpp"

Renderer::Renderer( MTL::Device* pDevice )
: _pDevice( pDevice->retain() )
{
    _pCmdQ = _pDevice->newCommandQueue();
    buildMeshes();
    buildShaders();
    //buildBuffers();
}

Renderer::~Renderer()
{
    quadMesh.pIndexBuffer->release();
    quadMesh.pVertexBuffer->release();
    _pVertPosBuffer->release();
    _pVertColBuffer->release();
    _pPSO->release();
    _pCmdQ->release();
    _pDevice->release();
}

void Renderer::buildMeshes()
{
    quadMesh = Msh::buildQuad(_pDevice);
}

void Renderer::buildShaders()
{
    std::fstream file;
    file.open("shaders/shader.metal");
    std::stringstream reader;
    reader << file.rdbuf();
    std::string raw_string = reader.str();
    NS::String* source_code = NS::String::string(raw_string.c_str(), NS::StringEncoding::UTF8StringEncoding);

    NS::Error* pError = nullptr;
    MTL::CompileOptions* pOptions = nullptr;
    MTL::Library* pLibrary = _pDevice->newLibrary(source_code, pOptions, &pError);
       if ( !pLibrary )
       {
           __builtin_printf( "%s", pError->localizedDescription()->utf8String() );
           assert( false );
       }

    MTL::Function* pVertexFn = pLibrary->newFunction( NS::String::string("vertexMain", NS::UTF8StringEncoding) );
    MTL::Function* pFragFn = pLibrary->newFunction( NS::String::string("fragmentMain", NS::UTF8StringEncoding) );

    MTL::RenderPipelineDescriptor* pDesc = MTL::RenderPipelineDescriptor::alloc()->init();
    pDesc->setVertexFunction( pVertexFn );
    pDesc->setFragmentFunction( pFragFn );
    pDesc->colorAttachments()->object(0)->setPixelFormat( MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB );

    MTL::VertexDescriptor* pVertDesc = MTL::VertexDescriptor::alloc()->init();
    auto attributes = pVertDesc->attributes();
    //attrib 0 -> pos
    auto pPosDesc = attributes->object(0);
    pPosDesc->setFormat(MTL::VertexFormat::VertexFormatFloat3);
    pPosDesc->setOffset(0);
    pPosDesc->setBufferIndex(0);
    
    //attrib 1 -> colour
    auto pColDesc = attributes->object(1);
    pColDesc->setFormat(MTL::VertexFormat::VertexFormatFloat3);
    pColDesc->setOffset(4 * sizeof(float));
    pColDesc->setBufferIndex(0);
    
    auto layoutDesc = pVertDesc->layouts()->object(0);
    layoutDesc->setStride(8 * sizeof(float));
    
    pDesc->setVertexDescriptor(pVertDesc);
    
    _pPSO = _pDevice->newRenderPipelineState( pDesc, &pError );
    if ( !_pPSO )
    {
       __builtin_printf( "%s", pError->localizedDescription()->utf8String() );
       assert( false );
    }

    pDesc->release();
    pVertexFn->release();
    pFragFn->release();
    pLibrary->release();
    file.close();
}

/*
void Renderer::buildBuffers()
{
    const size_t NumVertices = 3;

       simd::float3 positions[NumVertices] =
       {
           { -1.0f,  1.0f, 0.0f },
           { -1.0f, -1.0f, 0.0f },
           { +1.0f,  1.0f, 0.0f }
       };

       simd::float3 colors[NumVertices] =
       {
           {  1.0, 0.3f, 0.2f },
           {  0.8f, 1.0, 0.0f },
           {  0.8f, 0.0f, 1.0 }
       };

       const size_t positionsDataSize = NumVertices * sizeof( simd::float3 );
       const size_t colorDataSize = NumVertices * sizeof( simd::float3 );

       MTL::Buffer* pVertexPositionsBuffer = _pDevice->newBuffer( positionsDataSize, MTL::ResourceStorageModeManaged );
       MTL::Buffer* pVertexColorsBuffer = _pDevice->newBuffer( colorDataSize, MTL::ResourceStorageModeManaged );

       _pVertPosBuffer = pVertexPositionsBuffer;
       _pVertColBuffer = pVertexColorsBuffer;

       memcpy( _pVertPosBuffer->contents(), positions, positionsDataSize );
       memcpy( _pVertColBuffer->contents(), colors, colorDataSize );

       _pVertPosBuffer->didModifyRange( NS::Range::Make( 0, _pVertPosBuffer->length() ) );
       _pVertColBuffer->didModifyRange( NS::Range::Make( 0, _pVertColBuffer->length() ) );

}
*/
void Renderer::draw( MTK::View* pView )
{
    NS::AutoreleasePool* pPool = NS::AutoreleasePool::alloc()->init();

    MTL::CommandBuffer* pCmd = _pCmdQ->commandBuffer();
    MTL::RenderPassDescriptor* pRpd = pView->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder* pEnc = pCmd->renderCommandEncoder( pRpd );

    
    /*
    pEnc->setRenderPipelineState( _pPSO );
    pEnc->setVertexBuffer( _pVertPosBuffer, 0, 0 );
    pEnc->setVertexBuffer( _pVertColBuffer, 0, 1 );
    pEnc->drawPrimitives( MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), NS::UInteger(3) );

    */
    
    pEnc->setRenderPipelineState( _pPSO );
    pEnc->setVertexBuffer(quadMesh.pVertexBuffer, 0, 0 );
    pEnc->drawIndexedPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(6), MTL::IndexType::IndexTypeUInt32, quadMesh.pIndexBuffer, NS::UInteger(0), NS::UInteger(1));
    
    pEnc->endEncoding();
    pCmd->presentDrawable( pView->currentDrawable() );
    pCmd->commit();

    pPool->release();
}
