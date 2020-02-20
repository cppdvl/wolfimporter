#include <array>
#include <iomanip>
#include <iostream>
#include <algorithm>

#include "wolf/maputils.hpp"
#include "wolf/import/_3dformats/objfileparser.hpp"

namespace fs = std::filesystem;


int main()
{
    Wolf::_3DFormats::OBJFileParser objdata("fuhrercube.obj");
    objdata.Serialize();
	objdata.DumpFile();
	objdata.DumpCode("Cube", "fuhrercube.mtl/Blue");

	auto planeMap = objdata.DumpCodeVectorMap("Cube");
	auto planeMapKeys = Wolf::MapUtils::keys(planeMap);
	std::for_each(planeMapKeys.begin(), planeMapKeys.end(), [](auto&p){std::cout << p << std::endl;});
	
	return 0;
}