// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <memory>

namespace rm
{
	class ILogger
	{
	public:
		typedef std::shared_ptr< ILogger > ptr;

		~ILogger() {}

		virtual void WriteLine( std::string section, std::string text ) = 0;
	};
}