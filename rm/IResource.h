// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Owner.h>
#include <memory>

namespace rm
{
	class IResource
	{
	public:
		typedef std::shared_ptr< IResource > ptr;

		IResource( std::string name = std::string() );

		virtual ~IResource();

		std::string GetName() const;

		void SetName( std::string  name );

		/// <summary>
		/// Add a resource owner. Makes the lifetime of the resource tied to the owner's lifetime.
		/// </summary>
		void AddOwner( unify::Owner::ptr owner );

		/// <summary>
		/// Returns the number of owners.
		/// </summary>
		size_t Owners() const;	

		/// <summary>
		/// Reload the resource.
		/// </summary>
		virtual bool Reload() = 0;

		/// <summary>
		/// Get the source of the material; what it was created from.
		/// </summary>
		virtual std::string GetSource() const = 0;

	private:
		unify::OwnerProperty::ptr m_property;
	};
}
