#include <string>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

#include "libs/json.hpp"
#include "group_cache.h"
#include "http_requests.h"

using json = nlohmann::json;

void GroupCache::renewCache() {
    // Get the list
    HttpRequest::HttpResponse groupList = HttpRequest::MakeRequest("Group/GetGroups");

    if (groupList.error)
    {
        std::cout << "Error: cannot download groups list" << std::endl;
        exit(1);
    }
    // Launch parsing function on root node
    json rootJson = json::parse(groupList.body);

    //Save json to cache file
    createCachePath();
    std::ofstream fs;
    fs.open(getCachePath());
    if(!fs.is_open())
    {
        fs.clear();
        fs.open(getCachePath(), std::ios::out);
        fs.close();
        fs.open(getCachePath());
    }

    if (!fs.is_open())
    {
        std::cout << "Error: cannot write groups cache file in " << getCachePath() << std::endl;
        exit(1);
    }
    fs << rootJson;
    fs.close();
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

std::vector<Group> GroupCache::getGroupCache() {
    // Attempt to read the file
    std::ifstream fs;
    fs.open(getCachePath());

    // Doesn't exist, create it
    if (!fs.is_open()) {
        fs.close();
        renewCache();
        return getGroupCache();
    }

    // Deserialize json
    json rootJson;
    fs >> rootJson;
    fs.close();

    // Parse it and return the list
    std::vector<Group> groups;
    parseGroupsJson(rootJson, groups);
    return groups;
}

std::string GroupCache::getCachePath() {
    std::string filePath;
    filePath += getenv("HOME");
    filePath += "/.cache/chronos-cli/groups_cache.json";
    return filePath;
}

void GroupCache::createCachePath() {
    std::string dirPath;
    dirPath += getenv("HOME");
    dirPath += "/.cache/chronos-cli/";
    boost::filesystem::path rootPath(dirPath);
    boost::system::error_code returnedError;
    boost::filesystem::create_directories(rootPath, returnedError);
    if (returnedError) {
        std::cout << "Error: cannot create directories to store " << getCachePath();
        exit(1);
    }
}

Group GroupCache::getGroupFromName(std::string name, std::vector<Group> groups) {
    for (Group g : groups) {
        if (g.GetName() == name) {
            return g;
        }
    }
    std::cout << "Error: cannot find group " << name << ". Try to renew the groups list with --renew-cache"
              << std::endl;
    exit(1);
}
