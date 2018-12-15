// Copyright (c) 2006 - 2014 Evil Quail LLC
// All Rights Reserved

#pragma once

#include <string>
#include <exception>

namespace rm
{
	namespace exception
	{
		class ResourceNotFound : public std::exception
		{
		public:
			ResourceNotFound( std::string name )
				: std::exception( std::string( "Resource \"" + name + "\" not found!" ).c_str() )
			{
			}
			ResourceNotFound( std::string name, std::string type )
				: std::exception( std::string( "Resource \"" + name + "\" of type \"" + type + "\" not found!" ).c_str() )
			{
			}
		};
	}
}