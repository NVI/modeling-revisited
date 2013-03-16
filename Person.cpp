#include <set>
#include "def.h"

class Person {
private:
    set friends; // set of friendly nodes
    int party_index; // political party
public:
    Person(){
        friends;
        party_index = -1;
    }
    void switchParty(int new_party_index){
        party_index = new_party_index;
    }
    void addFriend(int friend_id){
        friends.insert(friend_id);
    }
    int getParty(){
        return party_index;
    }
    set getFriends(){
        return friends; 
    }
} ;
