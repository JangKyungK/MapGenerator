#include <iostream>
#include <fstream>
#include <ctime>

#include "PerlinNoise.h"

template <typename T>
T clip(const T& n, const T& lower, const T& upper) {
	return std::max(lower, std::min(n, upper));
}



int main() {
	//Setting
	const int iImageWidth = 512;
	const int iImageHeight = 512;

	float fXoff(0.f), fYoff(0.f);
	float fIncrement(0.02f);

	float fHoleXoff(50.f), fHoleYoff(70.f);
	float fHoleIncrement(0.02f);

	// Render

	std::ofstream  MyFile;
	MyFile.open("renderView.ppm");
	if (MyFile.is_open()) {

		MyFile << "P3\n" << iImageWidth << ' ' << iImageHeight << "\n255\n";

		int ir(0), ig(0), ib(0);
		float h(0.f), fOffset(0.f), fHoles(0.f);

		for (int j = iImageHeight - 1; j >= 0; --j) {
			fXoff = 0;
			fHoleXoff = 50;
			for (int i = 0; i < iImageWidth; ++i)
			{
				fOffset = Map(static_cast<float>(j), 0.f, iImageHeight, 70.f, 235.f);
				h = Map(PerlinNoise2D(fXoff, fYoff), -1.f, 1.f, fOffset, 255.f);
				//h = clip(h, 100.f, 255.f);		
				if (h > 90.f)
				{
					ir = 136;
					ig = 140;
					ib = 141;
				}
				else
				{
					ir = 101;
					ig = 67;
					ib = 33;

				}

				fOffset = Map(static_cast<float>(j), 0.f, iImageHeight, 160.f, 235.f);
				fHoles = Map(PerlinNoise2D(fHoleXoff, fHoleYoff), -1.f, 1.f, fOffset, 255.f);
				if (fHoles > 135.f)
				{
					ir = 0;
					ig = 0;
					ib = 0;
				}
				

		/*		int ir = static_cast<int>(h);
				int ig = static_cast<int>(h);
				int ib = static_cast<int>(h);*/

				MyFile << ir << ' '
					<< ig << ' '
					<< ib << '\n';
				fXoff += fIncrement;
				fHoleXoff += fHoleIncrement;
			}
			fYoff += fIncrement;
			fHoleYoff += fHoleIncrement;
		}
	}
	MyFile.close();
	return 0;
}
