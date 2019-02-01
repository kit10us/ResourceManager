// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <rm/IResource.h>

using namespace rm;

IResource::IResource( std::string name )
	: m_property{ unify::OwnerProperty::Create( name ) }
{
}

IResource::~IResource()
{
}

std::string IResource::GetName() const
{
	return m_property->GetName();
}

void IResource::SetName( std::string name )
{
	m_property->SetName( name);
}

void IResource::AddOwner( unify::Owner::ptr owner )
{
	m_property->AddOwner( owner );
}

size_t IResource::Owners() const
{
	return m_property->Owners();
}
