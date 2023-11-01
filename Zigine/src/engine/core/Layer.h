#ifndef _LAYER_H
#define _LAYER_H
#include "engine/Zigine.h"

class Layer
{
public:
	Layer(const std::string& name = "")
		: m_Name(name)
	{}

	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void OnUpdate() {}
	virtual void OnImguiRender() {}

	const std::string& GetName() const { return m_Name; }
private:
	std::string m_Name;
};

#endif // !_LAYER_H
