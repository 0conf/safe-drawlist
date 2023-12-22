#pragma once

#include <shared_mutex>

class SafeDrawlistSwap {
public:
	void Render();
	void Swap(const ImDrawData* data);
private:
	std::shared_mutex m_Mutex = { };
	ImDrawData m_TempData;
};
