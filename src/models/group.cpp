#include "group.h"

Group::Group(int id, int parentId, std::string name, int gtype)
        : id(id), parentId(parentId), name(name) {
    if (gtype == 1)
        type = GroupType::ClassGroup;
    else if (gtype == 2)
        type = GroupType::Staff;
    else
        type = GroupType::Room;
}

int Group::GetId() {
    return id;
}

int Group::GetParentId() {
    return parentId;
}

std::string Group::GetName() {
    return name;
}

Group::GroupType Group::GetType() {
    return type;
}

int Group::GetTypeId() {
    if (type == ClassGroup)
        return 1;
    else if (type == Staff)
        return 2;
    return 3;
}
