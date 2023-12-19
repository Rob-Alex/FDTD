
#include "renderer.hpp"
#include "config.hpp"

Renderer::Renderer( MTL::Device* pDevice )
: _pDevice( pDevice->retain() )
{
    _pCmdQ = _pDevice->newCommandQueue();
    buildShaders();
    buildBuffers();
}

Renderer::~Renderer()
{
    _pVertPosBuffer->release();
    _pVertColBuffer->release();
    _pPSO->release();
    _pCmdQ->release();
    _pDevice->release();
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
}

void Renderer::buildBuffers()
{
    const size_t NumVertices = 3;

       simd::float3 positions[NumVertices] =
       {
           { -0.8f,  0.8f, 0.0f },
           {  0.0f, -0.8f, 0.0f },
           { +0.8f,  0.8f, 0.0f }
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

void Renderer::draw( MTK::View* pView )
{
    NS::AutoreleasePool* pPool = NS::AutoreleasePool::alloc()->init();

    MTL::CommandBuffer* pCmd = _pCmdQ->commandBuffer();
    MTL::RenderPassDescriptor* pRpd = pView->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder* pEnc = pCmd->renderCommandEncoder( pRpd );

    pEnc->setRenderPipelineState( _pPSO );
    pEnc->setVertexBuffer( _pVertPosBuffer, 0, 0 );
    pEnc->setVertexBuffer( _pVertColBuffer, 0, 1 );
    pEnc->drawPrimitives( MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), NS::UInteger(3) );

    pEnc->endEncoding();
    pCmd->presentDrawable( pView->currentDrawable() );
    pCmd->commit();

    pPool->release();
}
