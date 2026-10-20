#pragma once

#include <d3d11.h>  
#include <memory>
#include <Core/Core.h>
#include <cstdint>
#include <vector>

#include "Math/Matrix4.h"


namespace Craft
{
    class Shader;
    class StaticMesh;
    class Win32Window;
    
    // CPU에서 GPU로 명령을 전달
    class Renderer
    {
        struct RenderCommand
        {
            Matrix4 worldMatrix = Matrix4::Identity;
            std::shared_ptr<StaticMesh> mesh;
            std::shared_ptr<Shader> shader;
        };
        
        struct CameraBufferData
        {
            Matrix4 viewMatrix = Matrix4::Identity;
        };
        
    public:
        Renderer(const Win32Window& window);
        ~Renderer();
        
    public:
        void Draw(float red, float green, float blue, uint32_t vsync); // Draw함수
        
        void Submit(const std::shared_ptr<StaticMesh>& mesh, const std::shared_ptr<Shader>& shader, const Matrix4& worldMatrix);
        
        void SubmitCamera(const Matrix4& viewMatrix);
        
        void OnResize(uint32_t width, uint32_t height);                // 크기 변경 이벤트 함수
        
        static Renderer& Get();     // 싱글톤 전역접근
        
        ID3D11Device& GetDevice() const { return *device; }
        ID3D11DeviceContext& GetContext() const { return *context; }
        
    private:
        void BeginScene(float red, float green, float blue);    // 그리기 준비
        void DrawScene();                                       // 드로우콜 발생
        void DrawCommand(const RenderCommand& command);         // 렌더 목록 처리
        void EndScene(uint32_t vsync);                          // 그리기 정리(버퍼 교환)
        
    private:        
        void CreateDevices();                                    // 장치 생성              
        void CreateSwapChain(const Win32Window& window);         // 스왑체인 생성                 
        void CreateRenderTargetView();                           // 렌더 타겟 뷰 생성
        void CreateViewport(uint32_t width, uint32_t height);    // 뷰포트 생성
    
        void CreateTransformBuffer();                            // 트랜스폼 상수버퍼 생성        
        void UpdateTransformBuffer(const Matrix4& worldMatrix);
        
        void CreateCameraBuffer();
        void UpdateCameraBuffer();
    
        
    private:
        /* 전역접근 */
        inline static Renderer* instance = nullptr;
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
                
        ID3D11Buffer* transformBuffer = nullptr;
        
        CameraBufferData cameraData;
        
        ID3D11Buffer* cameraBuffer = nullptr; 
        
        D3D11_VIEWPORT viewport = {};
        
        std::vector<RenderCommand> renderCommandList;
    };
}
