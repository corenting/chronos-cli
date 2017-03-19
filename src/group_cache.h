#include <string>
#include <vector>
#include "models/group.h"
#include "libs/json.hpp"

using json = nlohmann::json;

class GroupCache {
public:
    static void RenewCache();

    static void ParseGroupsJson(json node, std::vector<Group> &groups);

    static std::vector<Group> GetGroupeCache();

    static Group GetGroupeName(std::string name, std::vector<Group>);

private:
    static std::string GetCachePath();

    static void CreateCachePath();
};