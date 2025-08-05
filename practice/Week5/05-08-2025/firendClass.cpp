#include <string>
#include <vector>
#include <iostream>

class Group;

class User {
private:
    std::string name;
    std::vector<User*> friends;
    std::vector<Group*> groups;
    friend class RelationshipManager;
public:
    User(const std::string& n) : name(n) {}

    const std::string& getName() { return name; }

    void showFriends();
};

class Group {
private:
    std::string groupName;
    std::vector<User*> members;
    friend class RelationshipManager;

public:
    Group(const std::string& n) : groupName(n) {}

    const std::string& getName() { return groupName; }

    void showMembers();
};

class RelationshipManager {
public:
    static void makeFriends(User& a, User& b) {
        a.friends.push_back(&b);
        b.friends.push_back(&a);
    }

    static void addUserToGroup(User& u, Group& g) {
        u.groups.push_back(&g);
        g.members.push_back(&u);
    }
};

void User::showFriends() {
    std::cout << "User: " << name << "| Friends: ";
    for (auto f : friends) std::cout << f->getName() << " ";
    std::cout << "| Groups: ";
    for (auto g : groups) std::cout << g->getName() << " ";
    std::cout << "\n";
}

void Group::showMembers() {
    std::cout << "Group: " << groupName << "| Members: ";
    for (auto m : members) std::cout << m->getName() << " ";
    std::cout << "\n";
}

int main() {
    User tarun("Tarun"), varun("Varun");
    Group group("Group1");

    RelationshipManager::makeFriends(tarun, varun);
    RelationshipManager::addUserToGroup(tarun, group);
    RelationshipManager::addUserToGroup(varun, group);

    tarun.showFriends();
    varun.showFriends();
    group.showMembers();

    return 0;
}
