#pragma once

#include "Hazel.h"

class Sandbox2D : public Hazel::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Hazel::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Hazel::Event& e) override;
private:
	Hazel::OrthographicCameraController m_CameraController;
	
	// Temp
	Hazel::Ref<Hazel::VertexArray> m_SquareVA;
	Hazel::Ref<Hazel::Shader> m_FlatColorShader;

	Hazel::Ref<Hazel::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	bool /*m_TreeViewOpen, */m_StatsViewOpen;
	bool OnKeyPressedEvent(Hazel::KeyPressedEvent& e);
	/*Hazel::Ref<Hazel::Texture2D> m_TextFileTexture;
	Hazel::Ref<Hazel::Texture2D> m_FolderTexture;
	bool m_WorkspaceOpen, m_ProjectOpen;
	std::filesystem::path m_WorkspaceDir, m_ProjectDir, m_CurrentDir;
	struct FolderData
	{
		std::filesystem::path path;
		bool expanded;
		std::filesystem::path pathRelFromPrjDir;
		int subdirectories;
	};
	std::vector<FolderData> m_FolderDataList;
	std::vector<FolderData> m_WksFileDataList;
	void RenderFolderContents(std::vector<FolderData>& input, std::filesystem::path folder, float thumbnailSize, float indentation, bool spaceItems, int& maxID, int subDirs = 0, bool renderSubItems = true, bool includeHiddenFiles = false, int id = 0);
	void PrecalculateFolders(const std::filesystem::path& rootFolder, std::filesystem::path folder, std::vector<FolderData>& output, bool calcSubDirs = true, bool includeHiddenFiles = false);*/
};
