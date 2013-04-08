#ifndef PERSON_H
#define	PERSON_H

class Person {
private:
    std::set<int> friends;
    int party_index;
public:
    Person();
    void switchParty(int new_party_index);
    void addFriend(int friend_id);
    int getParty();
    std::set<int> getFriends();
} ;

#endif	/* PERSON_H */
