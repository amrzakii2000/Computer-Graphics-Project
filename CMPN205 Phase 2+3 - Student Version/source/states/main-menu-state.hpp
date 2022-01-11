#pragma once

#include <application.hpp>

#include <ecs/world.hpp>
#include <systems/forward-renderer.hpp>
#include <systems/free-camera-controller.hpp>
#include <systems/movement.hpp>
#include <asset-loader.hpp>
#include <systems/shooting.hpp>

class MenuState : public our::State
{
	void onImmediateGui() override
	{
		ImGuiStyle& style = ImGui::GetStyle();
		style.FramePadding = ImVec2(15, 12);
		style.ItemSpacing = ImVec2(10, 50);

		auto windowSize = getApp()->getFrameBufferSize();
		ImGui::SetNextWindowSize(ImVec2(windowSize.x, windowSize.y));
		ImGui::SetNextWindowPos(ImVec2(0, 0));

		//Begin ImGUI menu
		ImGui::Begin("Bugs Squasher", NULL, ImGuiWindowFlags_NoCollapse);
		
		if (ImGui::BeginTabBar("Welcome !"))
		{
			if (ImGui::BeginTabItem("Home"))
			{
                if(ImGui::Button("New Game"))
                {
					//Begin new game
                    getApp()->changeState("game");
                }
                ImGui::EndTabItem();
			}
		}
		ImGui::EndTabBar();

		ImGui::End();
	}
};