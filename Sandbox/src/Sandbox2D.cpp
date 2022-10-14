#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Hazel/Core/Application.h"
#include "Hazel/Utils/PlatformUtils.h"
#include "Hazel/Audio/AudioLibrary.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f), /*m_StatsViewOpen(true), m_TreeViewOpen(true), m_WorkspaceOpen(false), m_ProjectOpen(false),*/ m_SquareColor({ 0.2f, 0.3f, 0.8f, 1.0f })
{
}

void Sandbox2D::OnAttach()
{
	HZ_PROFILE_FUNCTION();

	m_CheckerboardTexture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
	Hazel::AudioLibrary::Init();
	Hazel::AudioLibrary::CreateSoundBuffer("assets/audio/test.wav", 0);
	Hazel::AudioLibrary::CreateSoundSource(0, 0);
	Hazel::AudioLibrary::SetSourceVolume(0, 0.3f);
	Hazel::AudioLibrary::PlaySource(0);
	Hazel::Application::Get().GetImGuiLayer()->BlockEvents(false);
	/*Hazel::FileDialogs::Init();
	m_TextFileTexture = Hazel::Texture2D::Create(Hazel::Application::Get().GetSpecification().WorkingDirectory +
	"Resources/Icons/ContentBrowser/FileIcon.png");
	m_FolderTexture = Hazel::Texture2D::Create(Hazel::Application::Get().GetSpecification().WorkingDirectory +
	"Resources/Icons/ContentBrowser/DirectoryIcon.png");*/
}

void Sandbox2D::OnDetach()
{
	HZ_PROFILE_FUNCTION();
	Hazel::AudioLibrary::Shutdown();
	//Hazel::FileDialogs::Deinit();
}

void Sandbox2D::OnUpdate(Hazel::Timestep ts)
{
	HZ_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);
	if (Hazel::Input::IsKeyPressed(Hazel::Key::Space) && Hazel::AudioLibrary::GetSourceState(0) != Hazel::AudioLibrary::State::PLAYING)
	{
		Hazel::AudioLibrary::RewindSource(0);
		Hazel::AudioLibrary::PlaySource(0);
	}

	// Render
	Hazel::Renderer2D::ResetStats();
	{
		HZ_PROFILE_SCOPE("Renderer Prep");
		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hazel::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		HZ_PROFILE_SCOPE("Renderer Draw");
		Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Hazel::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		Hazel::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Hazel::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
		Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		Hazel::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 20.0f);
		Hazel::Renderer2D::EndScene();

		Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Hazel::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Hazel::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	HZ_PROFILE_FUNCTION();

	/*static bool dockspace_open = true;
	static bool opt_fullscreen_persistent = true;
	bool opt_fullscreen = opt_fullscreen_persistent;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
	{
		window_flags |= ImGuiWindowFlags_NoBackground;
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("Dockspace Test", &dockspace_open, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
	{
		ImGui::PopStyleVar(2);
	}

	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	float minWinSizeX = style.WindowMinSize.x;
	style.WindowMinSize.x = 370.0f;
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	style.WindowMinSize.x = minWinSizeX;*/

	if (m_StatsViewOpen)
	{
		if (ImGui::Begin("Stats", &m_StatsViewOpen))
		{
			auto stats = Hazel::Renderer2D::GetStats();
			ImGui::Text("Renderer2D Stats:");
			ImGui::Text("Draw Calls: %d", stats.DrawCalls);
			ImGui::Text("Quads: %d", stats.QuadCount);
			ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
			ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
			//ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
		}
		ImGui::End();
	}

	/*if (m_TreeViewOpen)
	{
		if (ImGui::Begin("Tree view", &m_TreeViewOpen))
		{
			if (m_WorkspaceOpen && m_ProjectOpen)
			{
				if (m_FolderDataList.empty())
				{
					PrecalculateFolders(m_ProjectDir, m_ProjectDir, m_FolderDataList, true);
				}
				if (m_WksFileDataList.empty())
				{
					PrecalculateFolders(m_WorkspaceDir, m_WorkspaceDir, m_WksFileDataList, false);
				}
				static float indentation = 8.0f;
				static float thumbnailSize = 32.0f;
				static bool spaceItems = false;
				static int maxID = 0;

				RenderFolderContents(m_FolderDataList, m_ProjectDir, thumbnailSize, 0.0f, spaceItems, maxID);
				ImGui::Separator();
				RenderFolderContents(m_WksFileDataList, m_WorkspaceDir, thumbnailSize, 0.0f, spaceItems, maxID, 0, false, false, maxID + 1);
			}
			else
			{
				ImGui::Text("No workspace/project currently open...");
			}
		}
		ImGui::End();
	}

	ImGui::End();*/
}
/*
void Sandbox2D::PrecalculateFolders(const std::filesystem::path& rootFolder, std::filesystem::path folder, std::vector<Sandbox2D::FolderData>& output, bool calcSubDirs, bool includeHiddenFIles)
{
	for (auto& path : std::filesystem::directory_iterator(folder))
	{
		if (!includeHiddenFIles && path.path().filename().string().at(0) == '.')
		{
			continue;
		}
		int subdirectories = 0;
		for (int i = 0; i < std::filesystem::relative(path, rootFolder).string().size(); ++i)
		{
			auto a = std::filesystem::relative(path, rootFolder);
			auto b = a.string();
			auto c = b.find('/', i);
			i = (c != std::string::npos ? c : b.size());
			subdirectories += (c != std::string::npos);
		}
		output.push_back({ path, false, std::filesystem::relative(path, rootFolder), subdirectories });
		if (path.is_directory() && calcSubDirs)
		{
			PrecalculateFolders(rootFolder, path, output, calcSubDirs);
		}
	}
	/*std::vector<std::filesystem::path> pathList;
	for (auto& path : std::filesystem::directory_iterator(folder))
	{
		pathList.push_back(path);
	}
	std::vector<int> intArray;
	for (auto& path : pathList)
	{
		int sort;
		for (int i = 0; i < path.filename().string().size(); ++i)
		{
			sort += (int)path.filename().string().at(i) * (i + 1);
		}
		intArray.push_back(sort);
	}
	int lowestIndex = -1;
	int lowestNumber = -1;
	for (int i = 0; i < intArray.size(); ++i)
	{
		if (lowestIndex == -1 || lowestNumber == -1)
		{
			lowestNumber = intArray[i];
			lowestIndex = intArray[i];
		}
		else if (intArray[i] < lowestNumber)
		{
			lowestNumber = intArray[i];
			lowestIndex = intArray[i];
		}
	}*/
/*
}

void Sandbox2D::RenderFolderContents(std::vector<Sandbox2D::FolderData>& input, std::filesystem::path folder, float thumbnailSize, float indentation, bool spaceItems, int& maxID, int subDirs, bool renderSubItems, bool includeHiddenFiles, int id)
{
	int localID = id;
	if (indentation != 0.0f)
	{
		ImGui::Indent(indentation);
	}
	for (auto& directoryEntry : std::filesystem::directory_iterator(folder))
	{
		const auto& path = directoryEntry.path();
		std::string filenameString = path.filename().string();
		if (!includeHiddenFiles && filenameString.at(0) == '.')
		{
			continue;
		}

		ImGui::PushID((filenameString + '_' + (char)(localID + 48)).c_str());
		Hazel::Ref<Hazel::Texture2D> icon = directoryEntry.is_directory() ? m_FolderTexture : m_TextFileTexture;
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

		if (subDirs > 0)
		{
			std::string s = "";
			for (int i = 0; i < subDirs; ++i)
			{
				s.append("|");
			}
			s.append(" ");
			ImGui::TextColored(ImVec4(0.4f, 0.1f, 0.6f, 1.0f), s.c_str());
			ImGui::SameLine();
		}
		
		if (directoryEntry.is_directory())
		{
			bool b = true;
			for (int i = 0; i < input.size(); ++i)
			{
				if (input.at(i).path == directoryEntry)
				{
					b = false;
					if (renderSubItems)
					{
					if (input.at(i).expanded)
					{
						ImGui::TextColored(ImVec4(0.4f, 0.1f, 0.6f, 1.0f), "^");
					}
					else
					{
						ImGui::TextColored(ImVec4(0.4f, 0.1f, 0.6f, 1.0f), ">");
					}
					ImGui::SameLine();
					if (ImGui::ImageButton((ImTextureID)icon->GetRendererID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 }))
					{
						for (int i = 0; i < input.size(); ++i)
						{
							if (input.at(i).path == directoryEntry)
							{
								input.at(i).expanded = !input.at(i).expanded;
							}
						}
					}
					}
					else
					{
					ImGui::Image((ImTextureID)icon->GetRendererID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
					}
					ImGui::PopStyleColor();
					ImGui::Text(filenameString.c_str());
					ImGui::PopID();
					if (spaceItems)
					{
						ImGui::Spacing();
					}
					if (input.at(i).expanded && renderSubItems)
					{
						localID++;
						RenderFolderContents(input, directoryEntry, thumbnailSize, 8.0f * input.at(i).subdirectories, spaceItems, localID, input.at(i).subdirectories, renderSubItems, includeHiddenFiles, localID);
					}
				}
			}
			if (b)
			{
				ImGui::PopStyleColor();
				ImGui::PopID();
			}
		}
		else
		{
			ImGui::ImageButton((ImTextureID)icon->GetRendererID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
			ImGui::PopStyleColor();
			ImGui::Text("%s", filenameString.c_str());
			ImGui::PopID();
			if (spaceItems)
				ImGui::Spacing();
		}
	}
	if (indentation != 0.0f)
	{
		ImGui::Unindent(indentation);
	}
	if (maxID < localID)
	{
		maxID = localID;
	}
}
*/
void Sandbox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
	Hazel::EventDispatcher ed(e);
	ed.Dispatch<Hazel::KeyPressedEvent>(HZ_BIND_EVENT_FN(Sandbox2D::OnKeyPressedEvent));
}

bool Sandbox2D::OnKeyPressedEvent(Hazel::KeyPressedEvent& e)
{
	switch (e.GetKeyCode())
	{
	case Hazel::Key::D0: { m_StatsViewOpen = !m_StatsViewOpen; break; }
	/*case Hazel::Key::D1: { m_TreeViewOpen = !m_TreeViewOpen; break; }
	case Hazel::Key::O:
	{
		if (Hazel::Input::IsKeyPressed(Hazel::Key::LeftControl))
		{
			if (Hazel::Input::IsKeyPressed(Hazel::Key::LeftShift))
			{
				std::string wd = Hazel::FileDialogs::PickFolder();
				m_WorkspaceDir = std::filesystem::path(wd);
				if (!m_WorkspaceDir.empty())
				{
					m_WorkspaceOpen = true;
				}
				else
				{
					m_WorkspaceOpen = false;
				}
			}
			else
			{
				m_ProjectDir = Hazel::FileDialogs::PickFolder();
				if (!m_ProjectDir.empty())
				{
					m_ProjectOpen = true;
				}
				else
				{
					m_ProjectOpen = false;
				}
			}
		}
		break;
	}
	case Hazel::Key::D9: { if (Hazel::Input::IsKeyPressed(Hazel::Key::LeftControl)) { m_WorkspaceDir.clear(); m_ProjectDir.clear(); m_WorkspaceOpen = false; m_ProjectOpen = false; m_WksFileDataList.clear(); m_FolderDataList.clear(); } break; }*/
	}
	return false;
}
