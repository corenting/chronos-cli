#include <string>
#include <vector>
#include "models/group.h"
#include "libs/json.hpp"

using json = nlohmann::json;

class GroupCache {
public:
    static void renewCache(std::string token);
    static void parseGroupsJson(json node, std::vector<Group>& groups);
};