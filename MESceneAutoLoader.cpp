// MELuaDLL.cpp : Defines the exported functions for the DLL application.
//

#include <MESceneAutoLoader.h>
#include <mesal/components/AutoSceneManagerComponent.h>
#include <memory.h>

extern "C" MESALDLL_API bool MELoader( me::game::IGame * gameInstance, const qxml::Element * element);

MESALDLL_API bool MELoader( me::game::IGame * gameInstance, const qxml::Element * element )
{
	// Auto-scene script scene manager component..
	unify::Path autoPath;
	if (element->HasElements("auto"))
	{
		autoPath = unify::Path( element->GetElement("auto")->GetText() );
		gameInstance->Debug()->LogLine( "Lau::MELoader", "\"auto\" node found, setting autoPath to \"" + autoPath.ToString() + "\"." );
	}
	else
	{
		gameInstance->Debug()->LogLine( "Lau::MELoader", "\"auto\" node NOT found." );
	}

	auto autoSceneManagerComponent = new mesal::component::AutoSceneManagerComponent( autoPath + unify::Path( "scene/" ) );
	auto sceneManager = gameInstance->GetComponentT< me::scene::SceneManager >();
	sceneManager->AddComponent( me::scene::ISceneManagerComponent::ptr( autoSceneManagerComponent ) );		  

	return true;
}

