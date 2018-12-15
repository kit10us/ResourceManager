#include <rm/ResourceHub.h>
#include <rm/exception/FailedToCreate.h>
#include <qxml/Document.h>

using namespace rm;

ResourceHub::ResourceHub()
{
}

ResourceHub::~ResourceHub()
{
}

void ResourceHub::AddManager( std::shared_ptr< IResourceManagerRaw > manager )
{
	m_managerMap[ manager->GetName() ] = manager;
	m_managerList.push_back( manager );
}

void ResourceHub::Clear()
{
	m_managerMap.clear();
	m_managerList.clear();
}

std::vector< std::shared_ptr< IResourceManagerRaw > > m_managerList;
void ResourceHub::Clean()
{
	for( auto manager : m_managerList )
	{
		manager->Clean();
	}
}

size_t ResourceHub::GetTypeCount() const
{
	return m_managerMap.size();
}

std::string ResourceHub::GetTypeName( size_t index ) const
{
	return m_managerList[ index ]->GetName();
}

void ResourceHub::Load( std::string type, std::string name, unify::Path path )
{
	m_managerMap[type]->AddResource( name, path );
}

IResourceManagerRaw * ResourceHub::GetManagerRaw( std::string name )
{
	auto managerPairItr = m_managerMap.find( name );
	if ( managerPairItr == m_managerMap.end() )
	{
		return nullptr;
	}

	auto managerItr = managerPairItr->second;
	IResourceManagerRaw * managerRaw = managerItr.get();	
	return managerRaw;
}

IResourceManagerRaw * ResourceHub::GetManagerRaw( size_t index )
{
	IResourceManagerRaw * managerRaw = m_managerList[ index ].get();
	return managerRaw;
}
