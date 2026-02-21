#include "font.hpp"

#include "../../Variables.hpp"

using namespace onion::voxel;

// -------- Static Member Definitions --------

Shader Font::m_ShaderFont((GetAssetsPath() / "shaders/font.vert").string().c_str(),
						  (GetAssetsPath() / "shaders/font.frag").string().c_str());

glm::mat4 Font::s_ProjectionMatrix{1.0f};

// -------- Constructor / Destructor --------

Font::Font(const std::string& fontFilePath, int atlasCols, int atlasRows)
	: m_FontFilePath(fontFilePath), m_TextureAtlas(fontFilePath), m_AtlasCols(atlasCols), m_AtlasRows(atlasRows)
{
}

Font::~Font()
{
	Unload();
}

// -------- Public API --------

void Font::Load()
{
	m_TextureAtlas.Bind(); // Upload texture
	m_ShaderFont.Use();
	m_ShaderFont.setInt("uTexture", m_TextureAtlas.GetTextureID());
	GenerateBuffers();
}

void Font::Unload()
{
	DeleteBuffers();
}

void Font::SetProjectionMatrix(const glm::mat4& projection)
{
	s_ProjectionMatrix = projection;
	m_ShaderFont.Use();
	m_ShaderFont.setMat4("uProjection", s_ProjectionMatrix);
}

void Font::RenderText(const std::string& text, float x, float y, float scale, const glm::vec3& color)
{
	GLboolean depthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
	if (depthTestEnabled)
		glDisable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (text.empty())
		return;

	m_Vertices.clear();

	float uvStepX = 1.0f / m_AtlasCols;
	float uvStepY = 1.0f / m_AtlasRows;

	float cursorX = x;
	float cursorY = y;

	int texWidth = m_TextureAtlas.GetWidth();
	int texHeight = m_TextureAtlas.GetHeight();

	float glyphPixelWidth = texWidth / m_AtlasCols;
	float glyphPixelHeight = texHeight / m_AtlasRows;

	float glyphSizeX = glyphPixelWidth * scale;
	float glyphSizeY = glyphPixelHeight * scale;

	for (char c : text)
	{
		int ascii = static_cast<unsigned char>(c);

		int col = ascii % m_AtlasCols;
		int row = ascii / m_AtlasCols;

		float u0 = col * uvStepX;
		float v0 = row * uvStepY;
		float u1 = u0 + uvStepX;
		float v1 = v0 + uvStepY;

		float x0 = cursorX;
		float y0 = cursorY;
		float x1 = cursorX + glyphSizeX;
		float y1 = cursorY + glyphSizeY;

		// Two triangles per glyph
		m_Vertices.push_back({x0, y0, 0.f, u0, v0});
		m_Vertices.push_back({x1, y0, 0.f, u1, v0});
		m_Vertices.push_back({x1, y1, 0.f, u1, v1});

		m_Vertices.push_back({x0, y0, 0.f, u0, v0});
		m_Vertices.push_back({x1, y1, 0.f, u1, v1});
		m_Vertices.push_back({x0, y1, 0.f, u0, v1});

		cursorX += glyphSizeX;
	}

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), m_Vertices.data(), GL_DYNAMIC_DRAW);

	glActiveTexture(GL_TEXTURE0);
	m_TextureAtlas.Bind();

	m_ShaderFont.Use();
	m_ShaderFont.setVec3("uTextColor", color);
	m_ShaderFont.setInt("uTexture", 0);

	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_Vertices.size()));

	glBindVertexArray(0);

	if (depthTestEnabled)
		glEnable(GL_DEPTH_TEST);
}

glm::vec2 Font::MeasureText(const std::string& text, float scale) const
{
	if (text.empty())
		return {0.f, 0.f};

	float glyphPixelWidth = (float) m_TextureAtlas.GetWidth() / m_AtlasCols;
	float glyphPixelHeight = (float) m_TextureAtlas.GetHeight() / m_AtlasRows;

	float width = glyphPixelWidth * scale * static_cast<float>(text.length());
	float height = glyphPixelHeight * scale;

	return {width, height};
}

// -------- OpenGL Buffer Setup --------

void Font::GenerateBuffers()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, posX));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texX));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Font::DeleteBuffers()
{
	if (m_VAO)
		glDeleteVertexArrays(1, &m_VAO);

	if (m_VBO)
		glDeleteBuffers(1, &m_VBO);

	m_VAO = 0;
	m_VBO = 0;
}
