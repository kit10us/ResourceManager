
template< typename T >
ResourcePack< T >::ResourcePack( T * resource )
	: m_resource( resource )
{
}

template< typename T >
ResourcePack< T >::ResourcePack( std::shared_ptr< IFactoryFunctor< T > > factory )
	: m_factory( factory )
{
}

template< typename T >
bool ResourcePack< T >::HasFactory() const
{
	return m_factory;
}

template< typename T >
bool ResourcePack< T >::IsCreated() const
{
	return m_resource != false;
}

template< typename T >
void ResourcePack< T >::Create()
{
	if ( IsCreated() )
	{
		return;
	}

	m_resource = std::shared_ptr< T >( (*m_factory)() );
}

template< typename T >
void ResourcePack< T >::Destroy()
{
	m_resource.reset();
}

template< typename T >
std::shared_ptr< T > ResourcePack< T >::GetResource()
{
	if ( ! IsCreated() )
	{
		Create();
	}

	return m_resource;
}

template< typename T >
const std::shared_ptr< T > ResourcePack< T >::GetResource() const
{
	return m_resoruce;
}
