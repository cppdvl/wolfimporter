#include "wolf/stringutils.hpp"
#include "wolf/vectorutils.hpp"
#include "wolf/import/_3dformats/mtlfileparser.hpp"


bool Wolf::_3DFormats::MTLFileParser::Serialize() {

    enum wavefrontstate {
        none, newmtl, Ns, Ka, Kd, Ks, Ke, Ni, d, illum
    };
    auto state = none;
    std::string nameofthematerial{};
    std::string nameofthetexture{};
    std::map<std::string, wavefrontstate> linetype_state{
        std::make_pair("newmtrl", newmtl),
        std::make_pair("Ns", Ns),
        std::make_pair("Ka", Ka),
        std::make_pair("Kd", Kd),
        std::make_pair("Ks", Ks),
        std::make_pair("Ke", Ke),
        std::make_pair("Ni", Ni),
        std::make_pair("d", d),
        std::make_pair("illum", illum)
    };

    for (auto&line:lines){
        if (line.empty())continue;
        auto commandStringVector = Wolf::StringUtils::split(line, ' ');
        state = linetype_state[commandStringVector[0]];
        auto commandString = Wolf::StringUtils::join(commandStringVector, ' ', 1);
        if ( state == newmtl){
            nameofthematerial = commandStringVector[1];
            materialname_material[nameofthematerial] = _3DMaterial{};
            continue;
        } 
        auto& rMaterial = materialname_material[nameofthematerial];

        if (state == Ns){
            rMaterial.specularExponent = Wolf::StringUtils::parse<float>(commandStringVector[1]);
        } else if ( state == Ka){
            Wolf::VectorUtils::pushvectorf(rMaterial.ka, commandString, 3);
        } else if ( state == Kd){
            Wolf::VectorUtils::pushvectorf(rMaterial.kd, commandString, 3);
        } else if ( state == Ks){
            Wolf::VectorUtils::pushvectorf(rMaterial.ks, commandString, 3);
        } else if ( state == Ke){
            Wolf::VectorUtils::pushvectorf(rMaterial.ke, commandString, 3);
        } else if ( state == Ni){
            rMaterial.opticalDensity = Wolf::StringUtils::parse<float>(commandStringVector[1]);
        } else if ( state == d){
            rMaterial.opacity = Wolf::StringUtils::parse<float>(commandStringVector[1]);
        } else if ( state == illum){
            continue;
        }
    }
	return true;
}