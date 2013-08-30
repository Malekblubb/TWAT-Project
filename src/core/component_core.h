/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef CORE_COMPONENT_CORE_H
#define CORE_COMPONENT_CORE_H


#include <string>
#include <map>


namespace TWAT
{

	// factory design like in tw

#define DEF_COMPONENT(name) \
public: \
	static std::string Name() {return name;}


	// base for all interfaces
	class IComponent
	{
	public:
		IComponent() {}
		virtual ~IComponent() {}
	};


	class CComponentCore
	{
		std::map<std::string, IComponent *> m_components;

	public:
		static CComponentCore *CreateComponentCore() {return new CComponentCore();}

		template<typename T> void RegisterComponent(const std::string &name)
		{	
			if(m_components.find(name) != m_components.end())
				return; // component is already registered


			// create instance
			T *tmp = new T(); // need at least one empty constructor

			// store instance
			m_components[name] = tmp;
		}

		template<typename T> T *RequestComponent()
		{
			if((!m_components.empty()) && (m_components.find(T::Name()) != m_components.end()))
				return reinterpret_cast<T *>(m_components[T::Name()]);

			return NULL;
		}
	};
}


#endif // CORE_COMPONENT_CORE_H
