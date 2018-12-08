// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <mesal/components/AutoSceneManagerComponent.h>

using namespace mesal;
using namespace component;
using namespace me;
using namespace scene;

namespace {
	std::map< std::string, int, unify::CaseInsensitiveLessThanTest > g_ValuesMap
	{
		// Name, Index into value.
		{ "autoPath", 0 },
	};

	std::vector< std::string > g_ValuesList
	{
		{ "autoPath" },
	};
}

AutoSceneManagerComponent::AutoSceneManagerComponent( unify::Path autoPath )
	: me::scene::SceneManagerComponent( "SALAutoSceneManagerComponent" )
	, m_autoPath{ autoPath }
{
}

AutoSceneManagerComponent::~AutoSceneManagerComponent()
{
}

void AutoSceneManagerComponent::OnAttach( SceneManager * sceneManager )
{
}

void AutoSceneManagerComponent::OnDetach( SceneManager * sceneManager )
{
}

void AutoSceneManagerComponent::OnSceneStart( IScene * scene )
{
	std::string name = scene->GetName();
	unify::Path path( m_autoPath + unify::Path(name + ".xml"));
	if ( path.Exists() )
	{
		qxml::Document doc( path );

		for (auto & itr = doc.GetRoot()->Children( "assets" ).begin(); itr != doc.GetRoot()->Children().end(); ++itr)
		{
			auto type = (*itr).GetAttribute< std::string >( "type" );
			auto name = (*itr).GetAttributeElse< std::string >( "name", std::string() );
			unify::Path source{ (*itr).GetAttribute< std::string >( "source" ) };

			scene->GetGame()->GetResourceHub().GetManagerRaw( type )->AddResource( name, source );
		}
	}

}

void AutoSceneManagerComponent::OnSceneEnd( IScene * scene )
{
}

int AutoSceneManagerComponent::GetValueCount() const
{
	return SceneManagerComponent::GetValueCount() + (int)g_ValuesList.size();
}

bool AutoSceneManagerComponent::ValueExists( std::string name ) const
{
	auto && itr = g_ValuesMap.find( name );
	if( itr != g_ValuesMap.end() )
	{
		return true;
	}
	return SceneManagerComponent::ValueExists( name );
}

std::string AutoSceneManagerComponent::GetValueName( int index ) const
{
	if( index < SceneManagerComponent::GetValueCount() )
	{
		return SceneManagerComponent::GetValueName( index );
	}
	
	int localIndex = index - SceneManagerComponent::GetValueCount();
	if( localIndex < (int)g_ValuesList.size() )
	{
		return g_ValuesList[ localIndex ];
	}

	return std::string();
}

int AutoSceneManagerComponent::FindValueIndex( std::string name ) const
{
	auto && itr = g_ValuesMap.find( name );
	if( itr != g_ValuesMap.end() )
	{
		return itr->second;
	}

	return SceneManagerComponent::FindValueIndex( name );
}

bool AutoSceneManagerComponent::SetValue( int index, std::string value )
{
	if( index < SceneManagerComponent::GetValueCount() )
	{
		return SceneManagerComponent::SetValue( index, value );
	}

	int localIndex = index - SceneManagerComponent::GetValueCount();
	switch( localIndex )
	{
	case 0:
		m_autoPath = unify::Path( value );
		return true;

	default:
		return false;
	}
}

std::string AutoSceneManagerComponent::GetValue( int index ) const
{
	if( index < SceneManagerComponent::GetValueCount() )
	{
		return SceneManagerComponent::GetValue( index );
	}

	int localIndex = index - SceneManagerComponent::GetValueCount();
	switch( localIndex )
	{
	case 0:
		return m_autoPath.ToString();

	default:
		return std::string();
	}
}
