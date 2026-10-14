#include "Renderer.h"
#include "Core/Win32Window.h"
#include "cstdint"
#include "d3dcompiler.h"
#include "StaticMesh.h"

namespace Craft
{
    Renderer::Renderer(const Win32Window& window)
    {
    	assert(!instance);
    	instance = this;
    	
        CreateDevices();		
    	CreateSwapChain(window);	
		CreateRenderTargetView();
    	CreateDefaultShaders();
    	CreateViewport(window.GetWidth(), window.GetHeight());
    	CreateTransformBuffer();
    }

    Renderer::~Renderer()
    {
    	instance = nullptr;
    	
    	// Resource 해제
    	SafeRelease(vertexShader);
    	SafeRelease(pixelShader);
    	SafeRelease(inputLayout);
    	
    	// Device 해제
    	SafeRelease(renderTargetView);
    	SafeRelease(swapChain);
    	SafeRelease(context);	    
    	SafeRelease(device);
    	
    	// 상수버퍼
    	SafeRelease(transformBuffer);
    }

    void Renderer::Draw(float red, float green, float blue, uint32_t vsync)
    {
    	BeginScene(red, green, blue);
    	DrawScene();
    	EndScene(vsync);
    }

    void Renderer::Submit(const std::shared_ptr<StaticMesh>& mesh, const Matrix4& worldMatrix)
    {
    	RenderCommand command;
    	command.worldMatrix = worldMatrix;
    	command.mesh = mesh;
    	
    	renderCommandList.emplace_back(command);
    }

    void Renderer::OnResize(uint32_t width, uint32_t height)
    {
    	// 기존 크기 확인
    	DXGI_SWAP_CHAIN_DESC desc = {};
    	swapChain->GetDesc(&desc);
    	
    	// 렌더 타겟 뷰 해제
    	SafeRelease(renderTargetView);
    	
    	// 백버퍼 크기 변경 
		ThrowIfFailed(swapChain->ResizeBuffers(
			2, 
			width,
			height,
			DXGI_FORMAT_UNKNOWN, 
			0
			), L"Failed to resize back buffer");
    	
    	CreateRenderTargetView();
    	
    	CreateViewport(width, height);
    }

    Renderer& Renderer::Get()
    {
    	assert(instance && "instance should not be null here.");
    	return *instance;
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
    	// 셰이더 설정
    	context->IASetInputLayout(inputLayout);
    	context->VSSetShader(vertexShader, nullptr, 0);
    	context->PSSetShader(pixelShader, nullptr, 0);
    	    	
    	// 정점 셰이더에 상수 버퍼(트랜스폼 버퍼) 바인딩
    	context->VSSetConstantBuffers(0, 1, &transformBuffer);    	
    	
    	for (const RenderCommand& command : renderCommandList)
    	{
    		DrawCommand(command);
    	}
    	renderCommandList.clear();
    }

    void Renderer::DrawCommand(const RenderCommand& command)
    {   
    	if (!command.mesh) return;
    	
    	command.mesh->Bind();
    	
    	// 트랜스폼 데이터 업데이트
    	UpdateTransformBuffer(command.worldMatrix);
    	
    	
    	    	
    	// 드로우 콜
    	context->DrawIndexed(command.mesh->GetIndexCount(), 0, 0);
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


    void Renderer::CreateDefaultShaders()
    {
    	// 셰이더 컴파일 결과 저장용 객체
    	ID3DBlob* vertexShaderObject = nullptr;

    	// 셰이더(Shader) 컴파일
    	ThrowIfFailed(D3DCompileFromFile(
			L"HLSLShaders/DefaultVS.hlsl",
			nullptr,
			nullptr,
			"main",
			"vs_5_0",
			0,
			0,
			&vertexShaderObject,
			nullptr
		), L"Failed to compile vertex shader");

    	// 정점 셰이더 객체 생성
    	ThrowIfFailed(
			device->CreateVertexShader(
				vertexShaderObject->GetBufferPointer(),
				vertexShaderObject->GetBufferSize(),
				nullptr,
				&vertexShader
			), L"Failed to create vertex shader");

    	// 정점 셰이더 입력 관련 정보 객체 생성
    	D3D11_INPUT_ELEMENT_DESC inputLayoutDesc[] =
    	{
    		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    	};

    	ThrowIfFailed(device->CreateInputLayout(
			inputLayoutDesc,
			_countof(inputLayoutDesc),
			vertexShaderObject->GetBufferPointer(),
			vertexShaderObject->GetBufferSize(),
			&inputLayout), L"failed to create input layout");


    	// 픽셀 셰이더 컴파일 결과 저장용 객체
    	ID3DBlob* pixelShaderObject = nullptr;
	
    	// 픽셀 셰이더
    	ThrowIfFailed(D3DCompileFromFile(
			L"HLSLShaders/DefaultPS.hlsl",
			nullptr,
			nullptr,
			"main",
			"ps_5_0",
			0,
			0,
			&pixelShaderObject,
			nullptr
		), L"Failed to compile pixel shader");

    	// 픽셀 셰이더 객체 생성 
    	ThrowIfFailed(
			device->CreatePixelShader(
				pixelShaderObject->GetBufferPointer(),
				pixelShaderObject->GetBufferSize(),
				nullptr,
				&pixelShader
			), L"Failed to create pixel shader");

    	// 사용한 리소스 해제
    	SafeRelease(vertexShaderObject);
    	SafeRelease(pixelShaderObject);
    }

    void Renderer::CreateViewport(uint32_t width, uint32_t height)
    {
    	// 뷰포트 설정
    	viewport.TopLeftX = 0.0f;
    	viewport.TopLeftY = 0.0f;
    	viewport.Width = static_cast<float>(width);
    	viewport.Height = static_cast<float>(height);
    	viewport.MaxDepth = 1.0f;
    	viewport.MinDepth = 0.0f;
    	
    	// 바인딩
    	context->RSSetViewports(1, &viewport);
    	
    	
    }

    void Renderer::CreateTransformBuffer()
    {
    	// 버퍼 구성 정보
    	D3D11_BUFFER_DESC vertexBufferDesc = {};
    	vertexBufferDesc.ByteWidth = sizeof(Matrix4); 
    	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC; 
    	vertexBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    	
    	D3D11_SUBRESOURCE_DATA vertexBufferData = {};
    	vertexBufferData.pSysMem = Matrix4::Identity.Data();
    	
    	/* Step 3 : device가 버퍼 생성 */
    	ThrowIfFailed(
			device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &transformBuffer),
			L"Failed to create transform buffer");
    }

    void Renderer::UpdateTransformBuffer(const Matrix4& worldMatrix)
    {
		// 버퍼와 연결할 리소스 생성
    	D3D11_MAPPED_SUBRESOURCE mapped = {};
    	
    	// 버퍼와 연동
    	ThrowIfFailed(
    		context->Map(transformBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped),
    		L"Failed to map transform buffer");
    	
    	// 업데이트 할 데이터 설정
    	std::memcpy(mapped.pData, worldMatrix.Data(), sizeof(Matrix4));
    	
    	// 버퍼와 연동 해제 
    	context->Unmap(transformBuffer, 0);
    }
}
