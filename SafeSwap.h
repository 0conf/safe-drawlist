#pragma once

class SafeDrawlistSwap {
public:
	void Render();
	void Swap(const ImDrawData* Data);
private:
	std::shared_mutex m_Mutex = { };
	ImDrawData m_TempData;
};
