#include "Renderer.h"
#include "Core/Win32Window.h"
#include "cstdint"

namespace Craft
{
    Renderer::Renderer(const Win32Window& window)
    {
        CreateDevices();
    	CreateSwapChain(window);
		CreateRenderTargetView();
    	CreateDemoBuffers();
    	CreateDefaultShaders();
    }

    Renderer::~Renderer()
    {
    	SafeRelease(device);
    	SafeRelease(context);
    	SafeRelease(swapChain);
		SafeRelease(renderTargetView);
    	SafeRelease(vertexBuffer);
    	SafeRelease(indexBuffer);
    	SafeRelease(vertexShader);
    	SafeRelease(pixelShader);
    }

    void Renderer::Draw(float red, float green, float blue, uint32_t vsync)
    {
    	BeginScene(red, green, blue);
    	DrawScene();
    	EndScene(vsync);
    }

    void Renderer::BeginScene(float red, float green, float blue)
    {
    	// 그리기 대상 설정
    	context->OMSetRenderTargets(1, &renderTargetView, nullptr);
    	
    	// 배경 지우기
    	const float backgroundColor[4] = {red, green, blue, 1.0f};
    	context->ClearRenderTargetView(renderTargetView, backgroundColor);
    }

    void Renderer::DrawScene()
    {
    }

    void Renderer::EndScene(uint32_t vsync)
    {
    	// Front - Back 버퍼 교환
    	swapChain->Present(0, vsync);
    }

    void Renderer::CreateDevices()
    {
        uint32_t flag = 0;
        
#if _DEBUG
        flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif
        
        // 그래픽스 API 버전
        D3D_FEATURE_LEVEL featureLevels[] =
        {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,            
        };
        
        // 장치 생성
        ThrowIfFailed(D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			flag,
			featureLevels,
			_countof(featureLevels),
			D3D11_SDK_VERSION,
			&device,
			nullptr,
			&context
		), L"");
    }

    void Renderer::CreateSwapChain(const Win32Window& window)
    {
    	// 스왑체인 생성을 위한 객체 생성 
    	IDXGIFactory* factory = nullptr;    	
    	auto result = CreateDXGIFactory(IID_PPV_ARGS(&factory));
    	
    	// 예외처리
    	if (FAILED(result))
    	{
    		__debugbreak();
    		return;
    	}    	    	
    	
    	// 스왑체인 생성
    	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    	swapChainDesc.BufferDesc.Width = window.GetWidth();
    	swapChainDesc.BufferDesc.Height = window.GetHeight();
    	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    	swapChainDesc.SampleDesc.Count = 1;
    	swapChainDesc.SampleDesc.Quality = 0;
    	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    	swapChainDesc.BufferCount = 2;
    	swapChainDesc.OutputWindow = window.GetHandle();
    	swapChainDesc.Windowed = true;
    	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    	
    	 result = factory->CreateSwapChain(device, &swapChainDesc, &swapChain);
    	
    	if (FAILED(result))
    	{
    		
    	}
    	// 해제
    	if (!factory)
    	{
    		factory->Release();
    		factory = nullptr;
    	}
    }

    void Renderer::CreateRenderTargetView()
    {
    	// 백버퍼(2차원 배열-텍스처) 정보 가져오기
    	ID3D11Texture2D* backBuffer = nullptr;
		ThrowIfFailed(
			swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer)),
			L"Failed to get back buffer from swap chain");
    	
    	// 렌더타겟뷰 생성
    	ThrowIfFailed(
    		device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView),
    		L"Failed to create RTV");
    	
    	// 사용후 메모리 해제
    	SafeRelease(backBuffer);
    }

    void Renderer::CreateDemoBuffers()
    {
    	// 참고 : 이게 스태틱 메쉬임
    	
    	/* Step 1 : 삼각형을 이루는 원시데이터 준비 */
    	struct Vector3
    	{
    		float x, y, z = 0.f;
    	};
    	
    	Vector3 vertices[] = 
    	{
    		// 좌표계 기준은 Normalized Display Coordinates
    		// 인덱스 순서에따라 내적 결과 바라보는 방향이 카메라
    		Vector3 { 0.0f, 0.5f, 0.5f },
    		Vector3 { 0.5f, -0.5f, 0.5f },
    		Vector3 { -0.5f, -0.5f, 0.5f }
    	};
    	
    	/* Step 2 : 원시데이터를 GPU가 읽을수 있도록 버퍼로 포장해서 전달 */
    	D3D11_BUFFER_DESC vertexBufferDesc = {};
    	vertexBufferDesc.ByteWidth = sizeof(Vector3) * 3; 
    	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT; 
    	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    	
    	D3D11_SUBRESOURCE_DATA vertexBufferData = {};	
    	vertexBufferData.pSysMem = vertices;
    	
    	/* Step 3 : device가 버퍼 생성 */
    	ThrowIfFailed(
    		device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &vertexBuffer),
    		L"Failed to create vertex buffer");
    	
    	/* Step 1 : 인덱스를 이루는 원시데이터 준비 */
    	uint32_t indices[] = { 0, 1, 2};
    	
    	/* Step 2 : 원시데이터를 GPU가 읽을수 있도록 버퍼로 포장해서 전달 */
    	D3D11_BUFFER_DESC indexBufferDesc = {};
    	indexBufferDesc.ByteWidth = sizeof(uint32_t) * 3; 
    	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT; 
    	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    	
    	D3D11_SUBRESOURCE_DATA indexBufferData = {};	
    	indexBufferData.pSysMem = indices;
    	
    	/* Step 3 : device가 버퍼 생성 */
    	ThrowIfFailed(
			device->CreateBuffer(&indexBufferDesc, &indexBufferData, &indexBuffer),
			L"Failed to create vertex buffer");
    }

    void Renderer::CreateDefaultShaders()
    {
    	
    }
}
