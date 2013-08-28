/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_CORE_H
#define CORE_CORE_H


#include <string>
#include <map>


namespace TWAT
{

	// factory design like in tw

#define DEF_COMPONENT(name) \
public: \
	static std::string Name() {return name;} \
private:


	// base for all interfaces
	class IComponent
	{
	public:
		IComponent() {}
		virtual ~IComponent() {}
	};

	typedef IComponent *(*ComponentCreateFnc)(void);


	class CCore
	{
		std::map<std::string, ComponentCreateFnc> m_components;

	public:
		static CCore *CreateCore() {return new CCore();}

		template<typename T> void RegisterComponent(const std::string &name)
		{
			m_components[name] = &CreateComponent<T>;
		}

		template<typename T> T *RequestComponent()
		{
			std::map<std::string, ComponentCreateFnc>::iterator i = m_components.find(T::Name());

			if(i != m_components.end())
				return reinterpret_cast<T *>(i->second());

			return NULL;
		}

	private:
		template<typename T> static IComponent *CreateComponent()
		{
			return new T;
		}
	};
}


#endif // CORE_CORE_H
