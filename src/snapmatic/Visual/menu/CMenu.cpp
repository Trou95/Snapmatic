
#include "CMenu.h"
#include "../../CSnapmatic.h"


extern CSnapmatic *snapmatic;



CMenu::CMenu()
{
	this->bInit =
	this->bIsVisible =
	this->bIsSettingsVisible =
	this->bSampTextDraw =
	this->bSampNameTag =
	this->bFreezeTime =
	this->bFreezeWeather = false;
	this->time = 0;
	this->weather = 0;

}


bool CMenu::Init()
{
	if (bInit)
		return true;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	InitStyle();
	ImGui::GetIO().Fonts->AddFontFromFileTTF(FILE_PATH "res\\SignPainter.ttf", 18);
	ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

	InitItems();


	return true;
}


void CMenu::InitStyle()
{
	ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImColor(245, 247, 44, 237);
	ImGui::GetStyle().Colors[ImGuiCol_TitleBg] = ImColor(255, 255, 255, 255);
	ImGui::GetStyle().Colors[ImGuiCol_TitleBgActive] = ImColor(255, 255, 255, 255);
	ImGui::GetStyle().Colors[ImGuiCol_Text] = ImColor(0, 0, 0, 255);
	ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(204, 214, 221, 255);
	ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(243, 243, 242, 255);
	ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] = ImColor(255, 255, 255, 255);
	ImGui::GetStyle().Colors[ImGuiCol_CheckMark] = ImColor(255, 255, 255, 255);
	ImGui::GetStyle().Colors[ImGuiCol_SliderGrab] = ImColor(255, 255, 255, 255);
	ImGui::GetStyle().Colors[ImGuiCol_PopupBg] = ImColor(255, 255, 255, 240);
	ImGui::GetStyle().WindowBorderSize = 0;
	ImGui::GetStyle().WindowMinSize = ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT);
}



extern Weather weathers[];


void CMenu::InitItems()
{
	
	addCheckBox("Toggle Samp Textdraws");
	addCheckBox("Toggle Samp Nametags");
	addCheckBox("Toggle Game Hud");
	addTime("Freeze Time");
	addWeather("Freeze Weather", weathers);
	addCheckBox("Draw Filter");
	addButtonGroup("Toggle Freecam", "Settings");
	

}


bool CMenu::IsVisible()
{
	return bIsVisible;
}

bool CMenu::IsSettingsVisible()
{
	return bIsSettingsVisible;
}

void CMenu::ShowMenu(bool state)
{
	snapmatic->getSamp()->toggleSampCursor(state);
	bIsVisible = state;
	ImGui::GetIO().MouseDrawCursor = state;
}



void OnMenuClick(int id,bool state);


void CMenu::Render()
{
	ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	ImGui::Begin("Snapmatic", &bIsVisible, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |  ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	

	ImVec2 windowPos = ImGui::GetWindowPos();

	ImGui::PushClipRect(ImVec2(windowPos.x, windowPos.y), ImVec2(windowPos.x + WINDOW_WIDTH, windowPos.y + 30), false);
	ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(windowPos.x - 1, windowPos.y), ImVec2(windowPos.x + WINDOW_WIDTH, windowPos.y + 30), IM_COL32(255, 255, 255, 255));
	ImGui::PopClipRect();
	ImGui::SetCursorPos(ImVec2(5, 5));
	ImGui::Image((void*)mIcon, ImVec2(25, 21));
	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 25, 8));
	ImGui::Text("Snapmatic");
	ImGui::Spacing();

	for (int i = 0; i < menuItems.size(); i++)
	{
		if (menuItems[i]->render())
		{
			if (menuItems[i]->IsType<CCheckbox>())
				OnMenuClick(i, static_cast<CCheckbox*>(menuItems[i].get())->bIsSelected);
			else if (menuItems[i]->IsType<CTime>())
				OnMenuClick(i, static_cast<CTime*>(menuItems[i].get())->bIsSelected);
			else if (menuItems[i]->IsType<CWeather>())
				OnMenuClick(i, static_cast<CWeather*>(menuItems[i].get())->bIsSelected);
			else if (menuItems[i]->IsType<CButtonGroup>())
				OnMenuClick(i, static_cast<CButtonGroup*>(menuItems[i].get())->getSelectedButtonID()); // Send Button ID
			else OnMenuClick(i, false);
		}
	}

	ImGui::End();

}


extern string _keyInfo[__KEY_SIZE__];
extern Key _keys[__KEY_SIZE__];

void CMenu::RenderSettings()
{


	ImGui::Begin("Settings", &bIsSettingsVisible,ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

	ImGui::Text("General Settings");
	ImGui::Separator();
	ImGui::Checkbox("Enable sounds", &snapmatic->getSettings()->bPlaySounds);
	ImGui::Checkbox("Enable notifications", &snapmatic->getSettings()->bShowNotifications);
	ImGui::Spacing();
	ImGui::Text("Camera Speed");
	ImGui::SameLine();
	ImVec2 pos = ImGui::GetCursorPos();
	ImGui::SetCursorPos(ImVec2(pos.x,pos.y - 2));
	ImGui::SliderFloat("##", &snapmatic->cameraSpeed, 0, 100, "%.2f", 1);
	ImGui::Spacing();
	ImGui::Text("Filter Color");
	ImGui::SameLine();
	pos = ImGui::GetCursorPos();
	ImGui::SetCursorPos(ImVec2(pos.x + 5,pos.y));
	ImGui::ColorEdit4("##", snapmatic->filterColor, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);

	ImGui::Text("Key Settings");
	ImGui::Separator();
	if (ImGui::BeginTable("", 2, ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
	{
		CKeys* keys = snapmatic->getKeys();
		int keyIndex = keys->getKeyIndex();
		for (int i = 0; i < __KEY_SIZE__; i++)
		{
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Selectable(_keyInfo[i].c_str(), &keys->bIsSelect[i], ImGuiSelectableFlags_SpanAllColumns);
			if (keys->bIsSelect[i])
			{
				if (keyIndex == -1) snapmatic->getKeys()->setKeyIndex(i);
				else if (keyIndex != i) keys->bIsSelect[i] = false;
			}
			ImGui::TableNextColumn();
			ImGui::Text(!keys->bIsSelect[i] ? snapmatic->getKeys()->keyName(snapmatic->getKeys()->getKey(i)).c_str() : "Press a Key");
		}
		if (keyIndex > -1)
		{
			if (keys->bIsSelect[keyIndex] == false) snapmatic->getKeys()->setKeyIndex(-1);
		}
		ImGui::EndTable();
	}
	if (ImGui::Button("Save", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT))) snapmatic->getSettings()->SaveSettings();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::Text("Snapmatic v" VERSION " Build Date:" __DATE__);
	ImGui::Text("Author: Gorkem95");
	ImGui::SameLine();
	ImGui::TextColored(ImColor(0x1EA5E9E2), "Youtube/Gorkem95");
	ImGui::End();

}


void CMenu::addCheckBox(const char* name)
{
	menuItems.emplace_back(new CCheckbox(name));
}

void CMenu::addButton(const char* name)
{
	menuItems.emplace_back(new CButton(name));
}

void CMenu::addButtonGroup(const char* name, const char* name2)
{
	menuItems.emplace_back(new CButtonGroup(name, name2));
}

void CMenu::addTime(const char* name)
{
	menuItems.emplace_back(new CTime(name, 0, 23));
}

void CMenu::addWeather(const char* name,Weather weathers[])
{
	menuItems.emplace_back(new CWeather(name, weathers,23));
}

int CMenu::getItemSize()
{
	return menuItems.size();
}

void OnMenuClick(int id, bool state)
{
	if (id == 0)
	{
		if(state)  snapmatic->getSamp()->showTextDraws();
		snapmatic->getSamp()->SetTextDrawState(state);
	}
	else if (id == 1) snapmatic->getSamp()->toggleNameTags(state);
	else if (id == 2) snapmatic->getGame()->ToggleHud(!state);
	else if (id == 3)
	{
		if (state) snapmatic->time = static_cast<CTime*>(snapmatic->getVisual()->getMenu()->menuItems[3].get())->getValue();
		snapmatic->bFreezeTime = state;
	}
	else if (id == 4)
	{
		if (state) snapmatic->weather = static_cast<CWeather*>(snapmatic->getVisual()->getMenu()->menuItems[4].get())->getValue();
		snapmatic->bFreezeWeather = state;
	}
	else if (id == 5) snapmatic->ToggleFilter(state);
	else if (id == 6)
	{
		if (state == false) snapmatic->ToggleCam(!snapmatic->IsFreeCam());
		else snapmatic->getVisual()->getMenu()->bIsSettingsVisible = true;
	}
}