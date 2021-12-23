#pragma once

class GameEventManager {//Never disposed
public:
	enum EventEnum {
		None = 0,
		OnHit = 1,
	};

	GameEventManager();

	void			OnHitByPlayer();
};

void CreateGameEventHook();