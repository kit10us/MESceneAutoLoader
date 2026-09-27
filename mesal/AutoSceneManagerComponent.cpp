// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <mesal/AutoSceneManagerComponent.h>
#include <me/interop/MyThing.h>
#include <me/game/IGame.h>
#include <qxml/Document.h>

using namespace mesal;
using namespace me;
using namespace scene;

AutoSceneManagerComponent::AutoSceneManagerComponent( unify::Path autoPath )
	: me::scene::component::SceneManagerComponent( "SALAutoSceneManagerComponent" )
	, m_autoPath{ autoPath }
{
	{
		me::interop::Getter< const scene::component::ISceneManagerComponent * > autoPathGetter =
			[&]( const scene::component::ISceneManagerComponent * component ) -> std::string {
			return dynamic_cast< const AutoSceneManagerComponent * >(component)->GetAutoPath().ToString();
		};
		me::interop::Setter< scene::component::ISceneManagerComponent * > autoPathSetter =
			[&]( scene::component::ISceneManagerComponent * component, std::string value ) {
			return dynamic_cast< AutoSceneManagerComponent * >(component)->SetAutoPath( unify::Path( value ) );
		};

		GetLookup()->Add( "autoPath", interop::IValue::ptr{
			new interop::MyThing< scene::component::ISceneManagerComponent * >( this, autoPathGetter, autoPathSetter )
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

unify::Result<> AutoSceneManagerComponent::OnAttach( SceneManager * sceneManager )
{
	return {};
}

unify::Result<> AutoSceneManagerComponent::OnDetach( SceneManager * sceneManager )
{
	return {};
}

unify::Result<> AutoSceneManagerComponent::OnSceneStart( IScene * scene )
{
	std::string name = scene->GetName();
	unify::Path path( m_autoPath + unify::Path(name + ".xml"));
	if ( path.Exists() )
	{
		auto result = scene->AddResources( path );
		if (!result)
		{
			return result;
		}
	}
	return {};
}

unify::Result<> AutoSceneManagerComponent::OnSceneEnd( IScene * scene )
{
	return {};
}
