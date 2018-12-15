#pragma once
#include <memory>

namespace rm
{
	/// <summary>
	/// A functor that creates a product. It is used to delay the creation of assets. Ideally it's constructor
	/// would take the necessary parameters (paths, flags, etc.) that explain how to create the asset.
	/// Then, upon request, the procut can be created. This lets us define all assets upfront, and manage the
	/// creation order as needed.
	/// </summary>
	template< typename T >
	class IFactoryFunctor
	{
	public:
		virtual ~IFactoryFunctor() {}
		virtual T * operator()() = 0;
	};
}

#include <rm/FactoryFunctor1.h>
#include <rm/FactoryFunctor2.h>
#include <rm/FactoryFunctor3.h>
