#ifndef _IMGUILAYER_H
#define _IMGUILAYER_H
#include "Layer.h"

class ImguiLayer : public Layer
{
public:
	ImguiLayer();
	~ImguiLayer() = default;

	virtual void OnAttach();
	virtual void OnDetach();

	void Begin();
	void End();
private:
	sf::RenderWindow* m_Window;
};

#endif // !_IMGUILAYER_H
