#ifndef _PANEL_H
#define _PANEL_H
#include "engine/Zigine.h"
#include "engine/Renderer.h"

class Panel
{
public:
	Panel(Panel* parent = nullptr);

	virtual void Update() {}
	virtual void Draw();

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const vector2& position);
	virtual void SetOrigin(float x, float y);
	virtual void SetSize(float x, float y);
	virtual void SetSize(const vector2& size);
	virtual void SetScale(float x, float y);
	virtual void SetScale(const vector2& scale);
	virtual void SetFillColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
	virtual void SetFillColor(const sf::Color& color);
	virtual void SetVisible(bool state);

	virtual void SetParent(Panel* parent);

	virtual void LoadTexture(const std::string& key, const sf::IntRect& area = sf::IntRect());
	virtual void LoadTexture(const std::string& key, const std::string& path, const sf::IntRect& area = sf::IntRect());
	virtual void LoadTexture(const sf::Texture* texture);

	virtual void OnWindowResized(float width, float height);

	virtual inline bool IsVisible() const { return m_IsVisible; }
	virtual inline vector2 GetPosition() const { return m_Shape.getPosition(); }
	virtual inline vector2 GetOrigin() const { return m_Shape.getOrigin(); }
	virtual inline vector2 GetSize() const { return m_Shape.getSize(); }
	virtual inline vector2 GetScale() const { return m_Shape.getScale(); }
	virtual inline Panel* GetParent() const { return m_Parent; }
	virtual inline const sf::Texture* GetTexture() const { return m_Shape.getTexture(); }
	virtual inline int GetId() const { return m_Id; }
private:
	Panel(const Panel&) = delete;
	Panel(const Panel&&) = delete;

	void Setup();
protected:
	int m_Id;
	bool m_IsVisible = true;

	Panel* m_Parent;
	std::vector<Panel*> m_Childs;

	sf::RectangleShape m_Shape;
}; 

#endif // !_PANEL_H
