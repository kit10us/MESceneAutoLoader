// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <mesal/components/AutoSceneManagerComponent.h>
#include <me/interop/MyThing.h>
#include <me/game/IGame.h>
#include <qxml/Document.h>

using namespace mesal;
using namespace component;
using namespace me;
using namespace scene;

AutoSceneManagerComponent::AutoSceneManagerComponent( unify::Path autoPath )
	: me::scene::SceneManagerComponent( "SALAutoSceneManagerComponent" )
	, m_autoPath{ autoPath }
{
	{
		me::interop::Getter< const scene::ISceneManagerComponent * > autoPathGetter =
			[&]( const scene::ISceneManagerComponent * component ) -> std::string {
			return dynamic_cast< const AutoSceneManagerComponent * >(component)->GetAutoPath().ToString();
		};
		me::interop::Setter< scene::ISceneManagerComponent * > autoPathSetter =
			[&]( scene::ISceneManagerComponent * component, std::string value ) {
			return dynamic_cast< AutoSceneManagerComponent * >(component)->SetAutoPath( unify::Path( value ) );
		};

		GetLookup()->Add( "autoPath", interop::IValue::ptr{
			new interop::MyThing< scene::ISceneManagerComponent * >( this, autoPathGetter, autoPathSetter )
		} );
	}
}

void AutoSceneManagerComponent::SetAutoPath( unify::Path path )
{
	m_autoPath = path;
}


unify::Path AutoSceneManagerComponent::GetAutoPath() const
{
	return m_autoPath;
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

		for (auto & itr = doc.GetRoot()->Children( "asset" ).begin(); itr != doc.GetRoot()->Children().end(); ++itr)
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
