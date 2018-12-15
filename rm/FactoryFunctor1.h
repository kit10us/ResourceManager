#pragma once
#include <rm/IFactoryFunctor.h>

namespace rm
{
	template< typename T, typename ParameterA >
	class FactoryFunctor1 : public rm::IFactoryFunctor< T >
	{
	public:
		static std::shared_ptr< rm::IFactoryFunctor< T > >Make( ParameterA a )
		{
			return std::shared_ptr< rm::IFactoryFunctor< T > >( new rm::FactoryFunctor3< T, ParameterA >( a, b, c ) );
		}


		FactoryFunctor1( ParameterA a )
			: m_a( a )
		{
		}

		T * operator()() override
		{
			return new T( m_a );
		}
	private:
		ParameterA m_a;
	};
}