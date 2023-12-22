# Safe Swap
Swap an ImGui drawlist safely from one thread to another. Such as the Unreal Engine 4 game thread and the RHI (Rendering Hardware Interface) thread. I've uploaded this to github as I tend to get questions often on how I do this with ImGui. 


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

### Rendering Thread (via function hook)
Call ``SafeDrawlistSwap::Render()`` at the end of the rendering thread frame (such as your PresentScene hook...). 

```c++
ImGui_ImplDX11_NewFrame(); // Make sure you create a new frame BEFORE you render the draw-list.
g_Swapper->Render();

return oPresent(pSwapChain, syncInterval, flags);
```
