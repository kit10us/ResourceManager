// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <unify/Path.h>
#include <unify/Parameters.h>
#include <memory>

namespace rm
{
	/// <summary>
	/// Factory from a source path.
	/// </summary>
	template< typename T >
	class ISourceFactory
	{
	public:
		typedef std::shared_ptr< ISourceFactory< T > > ptr;

		~ISourceFactory() {}
		virtual std::shared_ptr< T > Produce( unify::Path path, unify::Parameters parameters = {} ) = 0;
		virtual std::shared_ptr< T > Produce( unify::Parameters parameters ) = 0;
	};
}