# Safe Swap
Swap an ImGui drawlist safely from one thread to another. Such as the Unreal Engine 4 game thread and the RHI (Rendering Hardware Interface) thread. I've uploaded this to github as I tend to get questions often on how I do this with ImGui. 

### Now why would we want to do this?
A common approach to internals is having all your logic inside a DirectX function hook. While this is easy, it's a very poor approach. The main reason being is that both the rendering thread (D3D) and the game thread are not in sync with each other. This leads to many issues such as accessing pointers that may no longer be valid. The engine may decide to free memory while your rendering thread is executing your logic which will lead to a crash.

## How to use (Unreal Engine 4)
1. Create an instance of ``SafeDrawlistSwap``

### Game Thread
Call ``SafeDrawlistSwap::Swap(const ImDrawData* data)`` with the draw data from ImGui. For example in this case we'll use ``ImGui::GetDrawData()``.
Make sure this is called **last** and/or when you've done your drawing (at the end of the frame).
```c++
ImGui_ImplWin32_NewFrame();
ImGui::NewFrame();

// Drawing ...

ImGui::EndFrame();
ImGui::Render();

g_Swapper->Swap(ImGui::GetDrawData());
```

### Rendering Thread
Call ``SafeDrawlistSwap::Render()`` at the end of the rendering thread frame (such as your PresentScene hook). 

```c++
ImGui_ImplDX11_NewFrame(); // Make sure you create a new frame BEFORE you render the draw-list.
g_Swapper->Render();

return oPresent(pSwapChain, syncInterval, flags);
```
