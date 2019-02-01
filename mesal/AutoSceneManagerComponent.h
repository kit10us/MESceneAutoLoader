// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <me/scene/component/SceneManagerComponent.h>

namespace mesal
{
	/// <summary>
	/// Automatically loads assets use by a Mercury scene at OnSceneStart.
	/// </summary>
	class AutoSceneManagerComponent : public me::scene::component::SceneManagerComponent
	{
	public:
		AutoSceneManagerComponent( unify::Path autoPath );
		~AutoSceneManagerComponent();

		/// <summary>
		/// Set the path where the scene will look for its asset file.
		/// </summary>
		void SetAutoPath( unify::Path path );

		/// <summary>
		/// Get the path where the scene will looks asset file.
		/// </summary>
		unify::Path GetAutoPath() const;

	public: // ISceneComponent... 
		void OnAttach( me::scene::SceneManager * sceneManager ) override;
		void OnDetach( me::scene::SceneManager * sceneManager ) override;
		void OnSceneStart( me::scene::IScene * scene ) override;
		void OnSceneEnd( me::scene::IScene * scene ) override;

	public: // IComponent

	private:
		unify::Path m_autoPath;
	};
}
