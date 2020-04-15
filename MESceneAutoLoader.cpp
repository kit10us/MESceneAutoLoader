// MELuaDLL.cpp : Defines the exported functions for the DLL application.
//

#include <MESceneAutoLoader.h>
#include <mesal/AutoSceneManagerComponent.h>
#include <me/game/IGame.h>
#include <me/debug/Block.h>
#include <memory.h>

extern "C" MESALDLL_API bool MELoader( me::game::IGame * gameInstance, const qxml::Element * element);

MESALDLL_API bool MELoader( me::game::IGame* gameInstance, const qxml::Element* element )
{
	auto block = gameInstance->Debug()->GetLogger()->CreateBlock( "MELoader \"MESceneAutoLoader\"" );

	// Auto-scene script scene manager component..
	unify::Path autoPath;
	if (element->HasElements("auto"))
	{
		autoPath = unify::Path( element->GetElement("auto")->GetText() );
		block->Log( "auto node found, setting autoPath to \"" + autoPath.ToString() + "\"." );
	}
	else
	{
		block->Log( "auto node NOT found." );
	}

	auto autoSceneManagerComponent = new mesal::AutoSceneManagerComponent( autoPath + unify::Path( "scene/" ) );
	auto sceneManager = gameInstance->GetComponentT< me::scene::SceneManager >();
	sceneManager->AddComponent( me::scene::component::ISceneManagerComponent::ptr( autoSceneManagerComponent ) );		  

	return true;
}

