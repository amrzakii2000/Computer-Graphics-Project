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
                    getApp()->changeState("game");
                }
                ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Game Controls"))
			{
                // Making a grid
                ImGui::Columns(4, "mycolumns");

				ImGui::AlignTextToFramePadding();
                ImGui::Text(" Movements");
                ImGui::AlignTextToFramePadding();
                ImGui::Text("Camera");

				ImGui::NextColumn();
				ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(ImColor(200, 155, 120)));
				ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(ImColor(200, 155, 120)));


				ImGui::Text("Hold your Left Mouse button  and move around");
				ImGui::PopStyleColor(2);
				ImGui::EndTabItem();
			}

		}
		ImGui::EndTabBar();

		ImGui::End();
	}
};