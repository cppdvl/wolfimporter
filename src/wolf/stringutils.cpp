#include <map>
#include <regex>
#include <string>
#include <vector>

namespace Wolf::Utils::StringUtils {

    std::vector<std::string> split(const std::string& s, const std::string& delim){

        std::vector<std::string> ssplit{};
        unsigned long long tokenfound = 1;
        unsigned long long lastfound = 0;
        auto delimsize = delim.size();

        while (tokenfound != std::string::npos){
            tokenfound = s.find(delim, tokenfound);
            auto bnotfound = tokenfound == std::string::npos;
            ssplit.push_back(s.substr(lastfound, bnotfound ? s.size() - lastfound : tokenfound - lastfound));
            if (bnotfound) continue;                
            tokenfound += delimsize;
            lastfound = tokenfound;
        }
        return ssplit;

    }
    std::string join(std::vector<std::string> vs, const std::string delim, int firstindex = 0, int lastindex = 0){
        std::string acc{};
        if (firstindex < 0) {
            firstindex = vs.size() + firstindex;
            if (firstindex < 0) firstindex = 0;
        } 
        if (lastindex < 0) {
            lastindex = vs.size() + lastindex;
            if (lastindex <= 0) lastindex = vs.size() - 1; 
        } else if (lastindex == 0) {
            lastindex = vs.size() - 1;
        }
        for (auto index = firstindex; index <= lastindex; ++index){
            acc += vs[index];
            if (index < lastindex) acc+= delim;
        }
        return acc;
    }

    std::tuple<bool, int> bi_isint(const std::string& str){

        auto regex_matched = std::regex_match(str, std::regex{"^[\\s]*[\\+\\-]?[0-9]+[\\s]*$"});
        return std::make_tuple(regex_matched,regex_matched ? stoi(str) : 0);

    }

    std::tuple<bool, unsigned int> bui_isint(const std::string& str){

        auto regex_matched = std::regex_match(str, std::regex{"^[\\s]*[\\+]?[0-9]+[\\s]*$"});
        return std::make_tuple(regex_matched,regex_matched ? stoi(str) : 0);

    }

}
