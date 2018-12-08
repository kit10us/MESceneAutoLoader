// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <me/scene/SceneManagerComponent.h>

namespace mesal
{
	namespace component
	{
		/// <summary>
		/// Attaches a SAL scene componenet to every scene.
		/// </summary>
		class AutoSceneManagerComponent : public me::scene::SceneManagerComponent
		{
		public:
			AutoSceneManagerComponent( unify::Path autoPath );
			~AutoSceneManagerComponent();

		public: // ISceneComponent... 
			void OnAttach( me::scene::SceneManager * sceneManager ) override;
			void OnDetach( me::scene::SceneManager * sceneManager ) override;
			void OnSceneStart( me::scene::IScene * scene ) override;
			void OnSceneEnd( me::scene::IScene * scene ) override;

		public: // IComponent
			int GetValueCount() const override;
			bool ValueExists( std::string ) const override;
			std::string GetValueName( int index ) const override;
			int FindValueIndex( std::string name ) const override;
			std::string GetValue( int index ) const override;
			bool SetValue( int index, std::string value ) override;

		private:
			unify::Path m_autoPath;
		};
	}
}
