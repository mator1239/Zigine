#include "PanelManager.h"
#include "Panel.h"

#include "engine/managers/TextureManager.h"

static int m_GlobalPanelId = 0;

Panel::Panel(Panel* parent)
{
	Setup();
	SetParent(parent);
}

void Panel::Draw()
{
	if (!m_IsVisible)
		return;

	Renderer::drawPrimitive(m_Shape);
}

void Panel::SetPosition(float x, float y)
{
	vector2 newPosition = { x, y };
	SetPosition(newPosition);
}

void Panel::SetPosition(const vector2& position)
{
	vector2 panelPosition = position;

	if (m_Parent)
		panelPosition += m_Parent->GetPosition();

	m_Shape.setPosition(panelPosition);
}

void Panel::SetOrigin(float x, float y)
{
	m_Shape.setOrigin(x, y);
}

void Panel::SetSize(float x, float y)
{
	vector2 newSize = { x, y };
	SetSize(newSize);
}

void Panel::SetSize(const vector2& size)
{
	m_Shape.setSize(size);
}

void Panel::SetScale(float x, float y)
{
	vector2 newScale = { x, y };
	vector2 size = GetSize();

	vector2 newSize = vector2(size.x * newScale.x - 5.0f, 
		size.y * newScale.y - 3.0f);

	SetSize(newSize);
	SetScale(newScale);
}

void Panel::SetScale(const vector2& scale)
{
	m_Shape.setScale(scale);
}

void Panel::SetFillColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	sf::Color color(r, g, b, a);
	SetFillColor(color);
}

void Panel::SetFillColor(const sf::Color& color)
{
	m_Shape.setFillColor(color);
}

void Panel::SetVisible(bool state)
{
	m_IsVisible = state;
}

void Panel::SetParent(Panel* parent)
{
	if (parent == this || m_Parent == parent)
		return;

	m_Parent = parent;

	const vector2 parentPosition = m_Parent->GetPosition();
	SetPosition(parentPosition);
}

void Panel::LoadTexture(const std::string& key, const sf::IntRect& area)
{
	const sf::Texture* texture = Textures()->Get(key);
	LoadTexture(texture);
}

void Panel::LoadTexture(const std::string& key, const std::string& path, const sf::IntRect& area)
{
	const sf::Texture* texture = Textures()->Load(key, path);
	LoadTexture(texture);
}

void Panel::LoadTexture(const sf::Texture* texture)
{
	m_Shape.setTexture(texture);

	const vector2 size = (vector2)texture->getSize();
	m_Shape.setSize(size);
}

void Panel::OnWindowResized(float width, float height)
{
	Panel* panel = Panels()->GetBasePanel();
	const vector2 oldSize = panel->GetSize();
	const vector2 currentSize = GetSize();

	const vector2 newSize = vector2(width / oldSize.x * currentSize.x,
		height / oldSize.y * currentSize.y);

	SetSize(newSize);
}

void Panel::Setup()
{
	m_Id = m_GlobalPanelId;
	m_GlobalPanelId++;

	Panels()->Add(this);
}
