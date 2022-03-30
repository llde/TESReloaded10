float2 ParallaxMapping(float2 BaseUV, float3 CameraDir) {
	
	if (TESR_ParallaxData.y == -1.0f) return BaseUV.xy;
	
	float2 iParallaxOffset = CameraDir.xy / length(CameraDir.xyz) * (TESR_ParallaxData.x * 0.1f);
	float viewAngle = saturate(dot(CameraDir, float3(0.0f, 0.0f, 1.0f)));
	int nNumSteps = (int)lerp(TESR_ParallaxData.z, TESR_ParallaxData.y, viewAngle);
	float fCurrHeight = 0.0f;
	float fStepSize   = 1.0f / (float)nNumSteps;
	float fPrevHeight = 1.0f;
	float fNextHeight = 0.0f;
	int    nStepIndex = 0;
	float2 vTexOffsetPerStep = fStepSize * iParallaxOffset;
	float2 vTexCurrentOffset = BaseUV.xy;
	float  fCurrentBound     = 1.0f;
	float  fParallaxAmount   = 0.0f;
	float2 pt1 = 0.0f;
	float2 pt2 = 0.0f;

	while (nStepIndex < nNumSteps) {
	  vTexCurrentOffset -= vTexOffsetPerStep;
	  fCurrHeight = tex2Dgrad(BaseMap, vTexCurrentOffset, 0, 0).a;
	  fCurrentBound -= fStepSize;
	  if (fCurrHeight > fCurrentBound) {
		 pt1 = float2(fCurrentBound            , fCurrHeight);
		 pt2 = float2(fCurrentBound + fStepSize, fPrevHeight);
		 nStepIndex = nNumSteps + 1;
	  }
	  else {
		 fPrevHeight = fCurrHeight;
		 nStepIndex++;
	  }
	}

	float fDelta2 = pt2.x - pt2.y;
	float fDelta1 = pt1.x - pt1.y;
	float fDenominator = fDelta2 - fDelta1;

	if (fDenominator == 0.0f)
	   fParallaxAmount = 0.0f;
	else
	   fParallaxAmount = (pt1.x * fDelta2 - pt2.x * fDelta1) / fDenominator;

	return BaseUV.xy - (iParallaxOffset * (1 - fParallaxAmount));
	
}