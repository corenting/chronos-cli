#pragma once

#include <string>

class Group {
public:
    Group(int id, int parentId, std::string name, int gtype);

    enum GroupType {
        ClassGroup = 1,
        Staff = 2,
        Room = 3,
    };

    int GetId();

    int GetParentId();

    std::string GetName();

    GroupType GetType();

    int GetTypeId();

private:
    int id;
    int parentId;
    std::string name;
    GroupType type;
};