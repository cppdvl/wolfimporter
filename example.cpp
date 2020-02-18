#include <map>
#include <array>
#include <memory>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <filesystem>

#include "wolf/maputils.hpp"
#include "wolf/stringutils.hpp"
#include "wolf/vectorutils.hpp"
#include "wolf/filesystemutils.hpp"
#include "wolf/import/_3dformats/objfileparser.hpp"

namespace fs = std::filesystem;


int main()
{
    Wolf::_3DFormats::OBJFileParser objdata("fuhrercube.obj");
    objdata.Serialize();
	objdata.DumpFile();
	objdata.DumpCode("Cube", "FuhrerSample.mtl/Blue");
	objdata.DumpCode("Cube.001", "FuhrerSample.mtl/FuhrerGlass");
	
	auto planeMap = objdata.DumpCodeVectorMap("Cube");
	auto planeMapKeys = Wolf::MapUtils::keys(planeMap);
	std::for_each(planeMapKeys.begin(), planeMapKeys.end(), [](auto&p){std::cout << p << std::endl;});
	
	return 0;
}