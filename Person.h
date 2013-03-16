#ifndef PERSON_H
#define	PERSON_H

class Person {
private:
    set friends;
    int party_index;
public:
    Person();
    void switchParty(int new_party_index);
    void addFriend(int friend_id);
    int getParty();
    set getFriends();
} ;

#endif	/* PERSON_H */
