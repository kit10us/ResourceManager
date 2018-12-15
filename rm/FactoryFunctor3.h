#pragma once
#include <rm/IFactoryFunctor.h>

namespace rm
{
	template< typename T, typename ParameterA, typename ParameterB, typename ParameterC >
	class FactoryFunctor3 : public rm::IFactoryFunctor< T >
	{
	public:
		static std::shared_ptr< rm::IFactoryFunctor< T > >Make( ParameterA a, ParameterB b, ParameterC c )
		{
			return std::shared_ptr< rm::IFactoryFunctor< T > >( new rm::FactoryFunctor3< T, ParameterA, ParameterB, ParameterC >( a, b, c ) );
		}

		FactoryFunctor3( ParameterA parameterA, ParameterB parameterB, ParameterC parameterC )
			: m_parameterA( parameterA )
			, m_parameterB( parameterB )
			, m_parameterC( parameterC )
		{
		}

		T * operator()() override
		{
			return new T( m_parameterA, m_parameterB, m_parameterC );
		}
	private:
		ParameterA m_parameterA;
		ParameterB m_parameterB;
		ParameterC m_parameterC;
	};
}