// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <string>
#include <exception>

namespace rm
{
	namespace exception
	{
		class FailedToCreate : public std::exception
		{
		public:
			FailedToCreate( std::string error )
				: std::exception( error.c_str() )
			{
			}
		};
	}
}