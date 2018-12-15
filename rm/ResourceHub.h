#pragma once
#pragma comment(lib, "ResourceManager")
#include <rm/IResourceManager.h>
#include <unify/Cast.h>
#include <unify/String.h>
#include <map>
#include <memory>

namespace rm
{
	/// <summary>
	/// The Resource Hub is designed as a one-stop for resource management.
	/// It's job is a single point of contact to own all resource managers, 
	/// enabling "smart" loading, or cascaded loading, where an XML load for
	/// one file type and trigger the loading of another type. For example,
	/// a graphics Effect load can trigger the loading of dependant shaders,
	/// textures, etc. This also would support packaging of resources into
	/// groups via XML.
	/// </summary>
	class ResourceHub
	{
	public:
		ResourceHub();
		~ResourceHub();

		/// <summary>
		/// Add a resource manager.
		/// </summary>
		void AddManager( std::shared_ptr< IResourceManagerRaw > manager );

		/// <summary>
		/// Remove all resource managers.
		/// </summary>
		void Clear();

		/// <summary>
		/// Remove unused (not owned) resources.
		/// </summary>
		void Clean();

		/// <summary>
		/// Returns a specific manager by name.
		/// </summary>
		rm::IResourceManagerRaw * GetManagerRaw( std::string name );

		/// <summary>
		/// Returns a specific manager by name.
		/// </summary>
		rm::IResourceManagerRaw * GetManagerRaw( size_t index );

		/// <summary>
		/// Returns a specific manager by name.
		/// </summary>
		template< typename T >
		rm::IResourceManager< T > * GetManager( std::string name );

		/// <summary>
		/// Returns a specific manager by index.
		/// </summary>
		template< typename T >
		rm::IResourceManager< T > * GetManager( size_t index );

		/// <summary>
		/// Returns the number of managed types (managers).
		/// </summary>
		size_t GetTypeCount() const;

		/// <summaery>
		/// Returns the name of the type managed by a specific manager.
		/// </summary>
		std::string GetTypeName( size_t index ) const;
		
		///<summary>
		/// Load a resource file.
		///</summary>
		void Load( std::string type, std::string name, unify::Path path );

	private:
		std::map< std::string /*Resource name*/, std::shared_ptr< IResourceManagerRaw >, unify::CaseInsensitiveLessThanTest > m_managerMap;
		std::vector< std::shared_ptr< IResourceManagerRaw > > m_managerList;
	};

	template< typename T >
	IResourceManager< T > * ResourceHub::GetManager( std::string name )
	{
		IResourceManagerRaw * managerRaw = GetManagerRaw( name );
		auto resolved = unify::polymorphic_downcast< IResourceManager< T > * >( managerRaw );
		return resolved;
	}

	template< typename T >
	IResourceManager< T > * ResourceHub::GetManager( size_t index )
	{
		IResourceManagerRaw * managerRaw = GetManagerRaw( index );
		auto resolved = unify::polymorphic_downcast< IResourceManager< T > * >( managerRaw );
		return resolved;
	}
}