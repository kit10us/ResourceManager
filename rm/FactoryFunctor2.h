#pragma once
#include <rm/IFactoryFunctor.h>

namespace rm
{
	template< typename T, typename ParameterA, typename ParameterB >
	class FactoryFunctor2 : public rm::IFactoryFunctor< T >
	{
	public:
		static std::shared_ptr< rm::IFactoryFunctor< T > >Make( ParameterA a, ParameterB b )
		{
			return std::shared_ptr< rm::IFactoryFunctor< T > >( new rm::FactoryFunctor2< T, ParameterA, ParameterB >( a, b ) );
		}

		FactoryFunctor2( ParameterA a, ParameterB b )
			: m_a( a )
			, m_b( b )
		{
		}

		T * operator()() override
		{
			return new T( m_a, m_b );
		}
	private:
		ParameterA m_a;
		ParameterB m_b;
	};
}