#include "SafeSwap.h"

void SafeDrawlistSwap::Render()
{
	std::unique_lock<std::shared_mutex> lock(this->m_Mutex);
	ImGui_ImplDX11_RenderDrawData(&this->m_TempData);
}

void SafeDrawlistSwap::Swap(const ImDrawData* Data)
{
	std::unique_lock<std::shared_mutex> lock(this->m_Mutex);
	if (m_TempData.CmdLists != nullptr) 
	{

		for (int i = 0; i < m_TempData.CmdListsCount; i++)
		{
			delete m_TempData.CmdLists[i];
		}

		delete m_TempData.CmdLists;
		m_TempData.CmdLists = nullptr;
	}

	m_TempData.Clear();
	m_TempData = *Data;
	m_TempData.CmdLists = new ImDrawList * [Data->CmdListsCount];
	for (int i = 0; i < Data->CmdListsCount; i++) 
	{
		m_TempData.CmdLists[i] = Data->CmdLists[i]->CloneOutput();
	}
}
