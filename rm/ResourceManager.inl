// Copyright (c) 2002 - 2018, Quentin S. Smith
// All Rights Reserved

template< class T >
ResourceManager< T >::ResourceManager( std::string resourceName, rm::AssetPaths * assetPaths, ILogger::ptr logger )
	: m_resourceName( resourceName )
	, m_assetPaths( assetPaths )
	, m_logger( logger )
{
}

template< class T >
ResourceManager< T >::~ResourceManager()
{
	Clear();
}

template< class T >
std::string ResourceManager< T >::GetName() const
{
	return m_resourceName;
}				  

template< class T >
void ResourceManager< T >::Clear()
{
	m_resourceMap.clear();
}

template< class T >
std::shared_ptr< T > ResourceManager< T >::Find( std::string name )
{
	for( auto resource : m_resourceMap )
	{
		if( _stricmp( resource.first.c_str(), name.c_str() ) == 0 )
		{
			return resource.second;
		}
	}

	return ResourcePtr();
}

template< class T >
std::shared_ptr< T > ResourceManager< T >::Get( size_t index )
{
	if ( index >= m_resourceList.size() )
	{
		return ResourcePtr();
	}
	return m_resourceList[ index ];
}

template< class T >
bool ResourceManager< T >::Exists( std::string name ) const
{
	std::map< std::string, ResourcePtr >::const_iterator itr = m_resourceMap.find( name );
	return !( itr == m_resourceMap.end() );
}

// Add an already created resource so the memory is taken over by the manager.
template< class T >
std::shared_ptr< T > ResourceManager< T >::Add( std::string name, T * resource )
{
	// Attempt to find the existing resource.
	ResourcePtr existingResource = Find( name );

	// Fail if we are attempting to add a new resource over an existing one.
	if( existingResource )
	{
		throw unify::Exception( "Attempted to add resource \"" + name + "\", when name is already in use by a different resource!" );
	}

	ResourcePtr resourcePtr( resource );
	m_resourceMap[ name ] = resourcePtr;
	resource->SetName( name );
	m_resourceList.push_back( resourcePtr );

	return resourcePtr;
}

template< class T >
std::shared_ptr< T > ResourceManager< T >::Add( std::string name, unify::Path source, unify::Path relativePath, void * data )
{
	// Attempt to find the existing resource.
	ResourcePtr existingResource = Find( name );

	// If exists, return the existing resource. Else create it.
	if( existingResource )
	{
		return existingResource;
	}

	std::string extension = source.ExtensionOnly();
	auto factory = m_sourceFactories.find( extension );
	if( factory == m_sourceFactories.end() )
	{
		throw std::string( GetName() + " manager: No factory found that could produce \"" + name + "\"!" );
	}

	unify::Path foundSource;
	if ( m_assetPaths != 0 )
	{
		foundSource = m_assetPaths->FindAsset( source, relativePath );
	}

	if ( foundSource.Empty() )
	{
		throw unify::Exception( "Asset file not found! (name: \"" + name + "\", source: \"" + source.ToString() + "\")" );
	}

	Log_WriteLine( "ResourceManager::Add", GetName() + " manager: adding \"" + name + "\" (" + foundSource.ToString() + ")." );


	auto product = factory->second->Produce( foundSource, data );
	if( product )
	{
		product->SetName( name );
		m_resourceMap[ name ] = product;
		m_resourceList.push_back( product );
		return product;
	}

	throw std::string( GetName() + " manager: No factory found that could produce \"" + name + "\"!" );
}

template< class T >
std::shared_ptr< T > ResourceManager< T >::Add( unify::Path source, unify::Path relativePath, void * data )
{
	std::string extension = source.ExtensionOnly();
	auto factory = m_sourceFactories.find( extension );
	if( factory == m_sourceFactories.end() )
	{
		throw std::string( GetName() + " manager: No factory found that could produce \"" + source.Filename() + "\"!" );
	}

	unify::Path foundSource;
	if( m_assetPaths != 0 )
	{
		foundSource = m_assetPaths->FindAsset( source, relativePath );
	}

	if( foundSource.Empty() )
	{
		throw unify::Exception( "Asset file not found! (\"" + source.ToString() + "\")" );
	}

	Log_WriteLine( "ResourceManager::Add", GetName() + " manager: adding \"" + foundSource.ToString() + "\"." );

	std::string name;
	auto product = factory->second->Produce( foundSource, data );
	if( product )
	{
		name = product->GetName();
		m_resourceMap[name] = product;
		m_resourceList.push_back( product );
		return product;
	}

	throw std::string( GetName() + " manager: No factory found that could produce \"" + source.Filename() + "\"!" );
}

template< typename T >
void ResourceManager< T >::AddResource( std::string name, unify::Path path )
{
	Add( name, path );
}

template< class T >
size_t ResourceManager< T >::Count() const
{
	return m_resourceMap.size();
}

template< class T >
void ResourceManager< T >::ForEach( ForEachFunctor & functor )
{
	for( std::map< std::string, ResourcePtr >::iterator itr = m_resourceMap.begin(); itr != m_resourceMap.end(); ++itr )
	{
		ResourcePtr resource = itr->second;
        functor( resource.get() );
	}
}

template< typename T >
void ResourceManager< T >::AddFactory( std::string extension, std::shared_ptr< ISourceFactory< T > > factory )
{
	m_sourceFactories[ ( ( extension[ 0 ] != '.' ) ? "." : "") + extension ] = factory;
}
								 
template< typename T >
void ResourceManager< T >::Log_Write( std::string text )
{
	if ( m_logger )
	{
		m_logger->Write( text );
	}
}

template< typename T >
void ResourceManager< T >::Log_WriteLine( std::string section, std::string text )
{
	if ( m_logger )
	{
		m_logger->WriteLine( section, text );
	}
}

template< class T >
void ResourceManager< T >::Clean()
{
	for( auto itr = m_resourceList.begin(); itr != m_resourceList.end(); )
	{
		if( !itr->get()->Owners() )
		{
			m_resourceMap.erase( itr->get()->GetName() );
			itr = m_resourceList.erase( itr );
		}
		else
		{
			itr++;
		}
	}
}
