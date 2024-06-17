// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <unify/Path.h>
#include <memory>
#include <list>

namespace rm
{
	class AssetPaths
	{
	public:
		typedef std::shared_ptr< AssetPaths > ptr;

		AssetPaths();
		
		AssetPaths( const AssetPaths & assetPaths );

		~AssetPaths(){}

		// <summary>
		// Find a pass to an asset.
		// </summary>
		// <return>
		// Returns the path to the asset if found, else it returns an empty path.
		// </return>
		void AddSource( unify::Path source );
		
		/// <summary>
		/// Find and return the first path to an asset.
		/// </summary>
		/// <returns></returns>
		unify::Path FindAsset( unify::Path path, unify::Path firstPlace = unify::Path() );

		/// <summary>
		/// Returns a list of all possible paths.
		/// </summary>
		/// <returns></returns>
		std::string GetPaths( unify::Path root = unify::Path() ) const;

	private:
		std::list< unify::Path > m_paths;
	};
}
