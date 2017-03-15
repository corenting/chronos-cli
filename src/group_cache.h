#include <string>
#include <vector>
#include "models/group.h"
#include "libs/json.hpp"

using json = nlohmann::json;

class GroupCache {
public:
    static void renewCache();

    static void parseGroupsJson(json node, std::vector<Group> &groups);

    static std::vector<Group> getGroupCache();

    static Group getGroupFromName(std::string name, std::vector<Group>);

private:
    static std::string getCachePath();

    static void createCachePath();
};