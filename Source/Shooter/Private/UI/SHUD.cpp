// Shooter Games DEV


//#include "UI/SHUD.h"
//#include "..\..\Public\UI\SHUD.h"
#include "UI/SHUD.h"
#include "Engine/Canvas.h"

void ASHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawCrossHair();
}

void ASHUD::DrawCrossHair()
{
	int32 SizeX = Canvas->SizeX;
	int32 SizeY = Canvas->SizeY;
	const TInterval<float> Centre(SizeX*0.5f, SizeY*0.5f);

	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Green;
	DrawLine(Centre.Min - HalfLineSize, Centre.Max, Centre.Min + HalfLineSize, Centre.Max, LineColor, LineThickness);
	DrawLine(Centre.Min, Centre.Max - HalfLineSize, Centre.Min, Centre.Max + HalfLineSize, LineColor, LineThickness);
}
