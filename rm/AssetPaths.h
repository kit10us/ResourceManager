// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Path.h>
#include <list>

namespace rm
{
	class AssetPaths
	{
	public:
		AssetPaths();

		void AddSource( unify::Path source );
		
		unify::Path FindAsset( unify::Path path, unify::Path firstPlace = unify::Path() );

		std::string GetPaths( unify::Path root = unify::Path() ) const;

	private:
		std::list< unify::Path > m_paths;
	};
}
