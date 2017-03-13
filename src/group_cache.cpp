#include <string>
#include <iostream>

#include "libs/json.hpp"
#include "group_cache.h"
#include "http_requests.h"

using json = nlohmann::json;

void GroupCache::renewCache(std::string token) {
    // Get the list
    HttpRequest::HttpResponse groupList = HttpRequest::MakeRequest("Group/GetGroups", token);

    if (groupList.error)
    {
        std::cout << "Error: cannot download groups list" << std::endl;
        exit(1);
    }
    // Launch parsing function on root node
    std::vector<Group> groups;
    json rootJson = json::parse(groupList.body);
    parseGroupsJson(rootJson, groups);
}

void GroupCache::parseGroupsJson(json node, std::vector<Group>& groups) {
    for (json arrayElement : node) {
        // There is a group, add it
        if (!arrayElement["Name"].is_null()) {
            std::string name = arrayElement["Name"].get<std::string>();
            int id = arrayElement["Id"].get<int>();
            int parentId = arrayElement["ParentId"].get<int>();
            int type = arrayElement["Type"].get<int>();
            groups.emplace_back(id, parentId, name, type);

            // Check for subgroups
            if (!arrayElement["Groups"].is_null()) {
                parseGroupsJson(arrayElement["Groups"], groups);
            }
        }
    }
}
