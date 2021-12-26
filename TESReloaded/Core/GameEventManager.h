#pragma once

class GameEventManager {//Never disposed
public:
	enum EventEnum {
		None = 0,
		OnHit = 1,
	};

	static void Initialize();

	void			OnHitByPlayer();
};