// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

///
/// Resource management: Interfaces to simplify the management of resource files. There would be a main management interface with associated
/// individual -item- resource lists. For instance, sound, textures/surfaces, geometry will all have resource lists. They can be interdependant.
///

#pragma once

#include <unify/Result.h>
#include <rm/ILogger.h>
#include <rm/ISourceFactory.h>
#include <rm/IResourceManager.h>
#include <rm/AssetPaths.h>
#include <map>
#include <memory>

namespace rm
{
	// A base for a resource list...
	template< typename T >
	class ResourceManager	: public IResourceManager< T >
	{
	private:
		ResourceManager( const ResourceManager& ) {}
		ResourceManager& operator=( const ResourceManager& ) {}

	public:
        class ForEachFunctor 
        {
        public:
            virtual ~ForEachFunctor() {}
            virtual void operator()( T & resource ) = 0;    
        };

		typedef std::shared_ptr< T > ResourcePtr;

        ResourceManager( std::string resourceName, rm::AssetPaths::ptr assetPaths, ILogger::ptr = ILogger::ptr() );
		~ResourceManager();	

		void Clear();

		// Add an entry for a resource.
		unify::Result<ResourcePtr> Add(std::string name, T* resource) override;

		unify::Result<ResourcePtr> Add(std::string name, unify::Path source, unify::Path relativePath = unify::Path(), unify::Parameters parameters = {});

		/// <summary>
		/// Find an existing resource by name.
		/// </summary>
		ResourcePtr Find( std::string name );

		/// <summary>
		/// Get an existing resource by index.
		/// </summary>
		ResourcePtr Get( size_t index );

		IResource* GetResource( std::string name )
		{
			return Find( name ).get();
		}

		IResource* GetResource( size_t i )
		{
			return Get( i ).get();
		}
		
		void ForEach( ForEachFunctor & functor );

		void AddFactory( std::string extension, typename ISourceFactory< T >::ptr factory );

		typename ISourceFactory< T > * GetFactory( std::string extension );

		void Log_Write( std::string text );

		void Log_WriteLine( std::string section, std::string text );

	public: // IResourceManagerRaw...
		std::string GetName() const override;
		unify::Result<> AddResource( std::string name, unify::Path path ) override;
		bool Exists( std::string name ) const override;
		size_t Count() const override;
		void Clean() override;

	protected:
		std::string m_resourceName;
		rm::AssetPaths::ptr m_assetPaths;
		ILogger::ptr m_logger;
		std::map< std::string, ResourcePtr > m_resourceMap;
		std::vector< ResourcePtr > m_resourceList;
		std::map< std::string, std::shared_ptr< ISourceFactory< T > >, unify::string::CaseInsensitiveLessThanEqualTest > m_sourceFactories;
	};

	#include <rm/ResourceManager.inl>
}