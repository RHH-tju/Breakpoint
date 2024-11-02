#pragma once

#include "../Support/WinInclude.h"
#include "../Support/ComPointer.h"
#include "../D3D/DXContext.h"

#define FRAME_COUNT 2

class Window {
public:
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	inline static Window& get() {
		static Window instance;
		return instance;
	}

	inline bool getShouldResize() const {
		return shouldResize;
	}

	inline bool getShouldClose() const {
		return shouldClose;
	}

	bool init(DXContext* context, int w, int h);
	void update();

	void present();
	void resize();

	void shutdown();

private:
	Window() = default;

	DXContext* dxContext;

	UINT width, height;

	bool shouldResize = false;

	bool shouldClose = false;

	static LRESULT CALLBACK OnWindowMessage(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
	ATOM wndClass = 0;
	HWND window = nullptr;

	ComPointer<IDXGISwapChain4> swapChain;
	ComPointer<ID3D12Resource1> swapChainBuffers[FRAME_COUNT];

	bool getBuffers();
	void releaseBuffers();

#ifdef _DEBUG
	ComPointer<ID3D12Debug3> d3d12Debug;
	ComPointer<IDXGIDebug1> dxgiDebug;
#endif
};