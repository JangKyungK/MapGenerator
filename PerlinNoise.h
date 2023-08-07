#pragma once
#include <iostream>
#include <cmath>
#include <ctime>

static const unsigned int PERM_LENGTH = 512;

static const int iPermutationTable[PERM_LENGTH] = {151,160,137,91,90,15,
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
	190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
	135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
	129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
	151,160,137,91,90,15,
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
	190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
	135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
	129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};

typedef struct Vec2
{
	float fX;
	float fY;
}VECTOR2D;

float PerlinNoise2D(float _fX, float _fY);
float Fade(float _t);
float Lerp(float _t, float _a1, float _a2);
VECTOR2D AssignVector(int _iPermValue);
float Dot(VECTOR2D _vector1, VECTOR2D _vector2);

float Map(float _fInput, float _fStart, float _fEnd, float _fNewStart, float _fNewEnd);

float PerlinNoise2D(float _fX, float _fY)
{
	int iGlobalX = static_cast<int>(floor(_fX)) % PERM_LENGTH - 1;
	int iGlobalY = static_cast<int>(floor(_fY)) % PERM_LENGTH - 1;

	float fLocalX = _fX - floor(_fX);
	float fLocalY = _fY - floor(_fY);

	VECTOR2D topRight = { fLocalX - 1.f, fLocalY - 1.f };
	VECTOR2D topLeft = { fLocalX, fLocalY - 1.f };
	VECTOR2D bottomRight = { fLocalX - 1.f, fLocalY };
	VECTOR2D bottomLeft = { fLocalX, fLocalY };

	const int valueTopRight = iPermutationTable[iPermutationTable[iGlobalX + 1] + iGlobalY + 1];
	const int  valueTopLeft = iPermutationTable[iPermutationTable[iGlobalX] + iGlobalY + 1];
	const int  valueBottomRight = iPermutationTable[iPermutationTable[iGlobalX + 1] + iGlobalY];
	const int  valueBottomLeft = iPermutationTable[iPermutationTable[iGlobalX] + iGlobalY];

	const float dotTopRight = Dot(topRight, AssignVector(valueTopRight));
	const float dotTopLeft = Dot(topLeft, AssignVector(valueTopLeft));
	const float dotBottomRight = Dot(bottomRight, AssignVector(valueBottomRight));
	const float dotBottomLeft = Dot(bottomLeft, AssignVector(valueBottomLeft));

	const float fu = Fade(fLocalX);
	const float fv = Fade(fLocalY);

	return Lerp(fu, Lerp(fv, dotBottomLeft, dotTopLeft), Lerp(fv, dotBottomRight, dotTopRight));
}

VECTOR2D AssignVector(int _iPermValue)
{
	VECTOR2D tempVector = {};
	const int iAssign = _iPermValue % 3;
	if (iAssign == 0)
	{
		tempVector = { 1.0f, 1.0f };
		return tempVector;
	}
	else if (iAssign == 1)
	{
		tempVector = { -1.0f, 1.0f };
		return tempVector;
	}
	else if (iAssign == 2)
	{
		tempVector = { -1.0f, -1.0f };
		return tempVector;
	}
	else if (iAssign == 3)
	{
		tempVector = { 1.0f, -1.0f };
		return tempVector;
	}
	else
		return tempVector;
}

float Dot(VECTOR2D _vector1, VECTOR2D _vector2)
{
	return _vector1.fX * _vector2.fX + _vector1.fY * _vector2.fY;
}

float Fade(float _t)
{
	return ((6 * _t - 15) * _t + 10) * _t * _t * _t;
}

float Lerp(float _t, float _a1, float _a2)
{
	return _a1 + _t * (_a2 - _a1);
}

float Map(float _fInput, float _fStart, float _fEnd, float _fNewStart, float _fNewEnd)
{
	return (_fInput - _fStart ) / (_fEnd - _fStart) * (_fNewEnd - _fNewStart);
}