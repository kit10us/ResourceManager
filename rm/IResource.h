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

		void AddOwner( unify::Owner::ptr owner );

		size_t Owners() const;	

		virtual bool Reload() = 0;

		virtual std::string GetSource() const = 0;

	private:
		unify::OwnerProperty::ptr m_property;
	};
}
