#include "WindowsInclude.h"
#include "Window.h"
#include <d3d11.h>
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")

using namespace D3dSb;

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd)
{
	int width = 1280;
	int height = 720;

	// Set up window
	Window window(width, height, L"Direct3D SandBox");

	// Set up GFX

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferDesc.Width = 0;
	swapChainDesc.BufferDesc.Height = 0;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = window.GetHwnd();
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr <ID3D11RenderTargetView> pRenderTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSView;


	HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, 
		deviceFlags, featureLevels, ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION, &swapChainDesc, &pSwapChain, &pDevice, nullptr, &pContext);

	if (FAILED(hr))
	{
		//handle device interface creation failure if it occurs.
	}

	// Get back buffer

	Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;

	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), (void**)&pBackBuffer);

	if (FAILED(hr))
	{
		//handle get back buffer failure if it occurs.
	}

	// Create render target view
	hr = pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pRenderTarget);

	if (FAILED(hr))
	{
		//handle create render target view failure if it occurs.
	}

	//Todo: depth stensil 

	D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc = {};
	depthStencilStateDesc.DepthEnable = true;
	depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDSState;

	hr = pDevice->CreateDepthStencilState(&depthStencilStateDesc, &pDSState);

	if (FAILED(hr))
	{
		//handle create depth stensil state failure if it occurs.
	}

	pContext->OMSetDepthStencilState(pDSState.Get(), 1u);

	// Create depth stensil texture
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStensil;

	CD3D11_TEXTURE2D_DESC depthStencilDesc(DXGI_FORMAT_D24_UNORM_S8_UINT,
		static_cast<UINT>(width), static_cast<UINT>(height), 
		1u, 1u, D3D11_BIND_DEPTH_STENCIL);

	hr = pDevice->CreateTexture2D(&depthStencilDesc, nullptr, &pDepthStensil);

	if (FAILED(hr))
	{
		//handle create depth stensil texture failure if it occurs.
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0u;

	hr = pDevice->CreateDepthStencilView(pDepthStensil.Get(), &dsvDesc, &pDSView);
	
	if (FAILED(hr))
	{
		//handle create depth stensil view failure if it occurs.
	}

	pContext->OMSetRenderTargets(1u, pRenderTarget.GetAddressOf(), pDSView.Get());

	//Todo: viewport

	D3D11_VIEWPORT viewport = {};
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	pContext->RSSetViewports(1u, &viewport);


	while (true)
	{
		if (const auto errorCode = Window::ProcessMessages())
		{
			return *errorCode;
		}

		//update
		
		//render
		
		//present
		
	}

	return 0;
}