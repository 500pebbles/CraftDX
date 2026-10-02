#pragma once

#include <d3d11.h>  
#include <memory>
#include <Core/Core.h>
#include <cstdint>


namespace Craft
{
    class Win32Window;
    
    // CPU에서 GPU로 명령을 전달
    class Renderer
    {
    public:
        Renderer(const Win32Window& window);
        ~Renderer();
        
    public:
        void Draw(float red, float green, float blue, uint32_t vsync); // Draw함수
        
        void OnResize(uint32_t width, uint32_t height);                // 크기 변경 이벤트 함수
        
    private:
        void BeginScene(float red, float green, float blue);    // 그리기 준비
        void DrawScene();                                       // 드로우콜 발생
        void EndScene(uint32_t vsync);                          // 그리기 정리(버퍼 교환)
        
    private:
        
        void CreateDevices();                                    // 장치 생성              
        void CreateSwapChain(const Win32Window& window);         // 스왑체인 생성                 
        void CreateRenderTargetView();                           // 렌더 타겟 뷰 생성
        void CreateDemoBuffers();                                // 데모 버퍼 생성
        void CreateDefaultShaders();                             // 셰이더 생성
        void CreateViewport(uint32_t width, uint32_t height);    // 뷰포트 생성
        
    private:
        /* 그래픽카드 장치 제어 */
     
        // 디바이스 -> 데이터 생성
        ID3D11Device* device = nullptr;
        
        // 디바이스 컨텍스트 -> 그래픽카드에 데이터 설정(연결/바인딩)
        ID3D11DeviceContext* context = nullptr;
        
        // 버전별로 변경이 거의 없는 장치 (=DXGI)
        IDXGISwapChain* swapChain = nullptr;
        
        // 백버퍼를 대표하는 렌더 타겟 -> 그래픽카드에 그릴 대상을 선정함 (DX에서 View라는 개념은 메모리에 그릴 대상을 뜻함)
        ID3D11RenderTargetView* renderTargetView = nullptr;
        
        // VertexBuffer
        ID3D11Buffer* vertexBuffer = nullptr;
        
        ID3D11Buffer* indexBuffer = nullptr;
        
        // 셰이더 관련 변수
        ID3D11VertexShader* vertexShader = nullptr;
        
        ID3D11PixelShader* pixelShader = nullptr;
        
        ID3D11InputLayout* inputLayout = nullptr;
        
        // 뷰포트
        D3D11_VIEWPORT viewport = {};
    };
}
