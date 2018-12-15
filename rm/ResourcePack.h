#pragma once
#include <rm/IFactoryFunctor.h>
#include <memory>

namespace rm
{
	/// <summary>
	/// Holds data for a single resource entry.
	/// </summary>
	template< typename T >
	class ResourcePack
	{
	public:
		ResourcePack() {} 

		/// <summary>
		/// Specify a resource that already has been created.
		/// </summary>
		ResourcePack( T * resource );

		/// <summary>
		/// Specify a factory for creating and re-creating this resource.
		/// </summary>
		ResourcePack( std::shared_ptr< IFactoryFunctor< T > > factory );

		/// <summary>
		///	Returns true if the resource has a factory specified.
		/// This means the resource can be freed then restored.
		/// </summary>
		bool HasFactory() const;

		/// <summary>
		/// Returns true if the resource has been created.
		/// </summary>
		bool IsCreated() const;

		/// <summary>
		/// Creates the resource from a factory, if the factory is provided and the resource isn't already created.
		/// </summary>
		void Create();

		/// <summary>
		/// Destroy resouce if it's already created. Factory is left intack, so the resource can be re-created, thus this is _not_ a destruction equivalent.
		/// </summary>
		void Destroy();

		/// <summary>
		/// Get the resource. Resource is created if it hasn't been created yet.
		/// </summary>
		std::shared_ptr< T > GetResource();

		/// <summary>
		/// Get the resource.
		/// </summary>
		const std::shared_ptr< T > GetResource() const;

	private:
		std::shared_ptr< T > m_resource;
		std::shared_ptr< IFactoryFunctor< T > > m_factory;
	};

	#include <rm/ResourcePack.inl>
}