#pragma once

#include <rm/IResource.h>
#include <qxml/Element.h>
#include <unify/Path.h>
#include <map>
#include <list>
#include <string>
#include <memory>

namespace rm
{
	class IResourceManagerRaw
	{
	public:
		typedef std::shared_ptr< IResourceManagerRaw > ptr;

		// Enable VTable...
		virtual ~IResourceManagerRaw() {}

		/// <summary>
		/// Returns the name of the resource being managed.
		/// </summary>
		virtual std::string GetName() const = 0;

		/// <summary>
		/// Add resource without return. This allows us to 
		/// add resources in bulk, regardless of type (not template at this point, so we don't have to know the resource type).
		/// </summary>
		virtual void AddResource( std::string name, unify::Path path ) = 0;

		virtual IResource* GetResource( std::string name ) = 0;

		virtual IResource* GetResource( size_t i ) = 0;

		/// <summary>
		/// Returns true if a resource exists with the specified ID.
		/// </summary>
		virtual bool Exists( std::string name ) const = 0;
										 
		/// <summary>
		/// Returns the number of resources being managed.
		/// </summary>
		virtual size_t Count() const = 0;

		/// <summary>
		/// Clean out unused resources.
		/// </summary>
		virtual void Clean() = 0;
	};

	template< typename T >
	class IResourceManager : public IResourceManagerRaw
	{
	public:
		typedef std::shared_ptr< T > ResourcePtr;

		/// <summary>
		/// Add resource with a specific ID.
		/// Throws an exception if a resource already exists with the same ID, since we are passing in an already allocated resource,
		/// this could lead to a unmanaged resource pointer.
		/// </summary>
		virtual ResourcePtr Add( std::string name, T * resource ) = 0;
	};
}
