void GameEventManager::Initialize() {

	Logger::Log("Starting the event manager...");
	TheGameEventManager = new GameEventManager();

}

void GameEventManager::OnHitByPlayer() {

	float RandomPercent = 0.0f;

	if (TheShaderManager->ShaderConst.BloodLens.Percent == 0) {
		RandomPercent = (double)rand() / (RAND_MAX + 1) * (100 - 1) + 1;
		if (RandomPercent <= TheSettingManager->SettingsBloodLens.Chance) TheShaderManager->ShaderConst.BloodLens.Percent = 1;
	}

}