#ifndef SYSTEM_H
#define	SYSTEM_H

class System {
private:
    std::map<int, Party> parties;
public:
    System();
    void addParty(Setup setup, int index, double distances [8]);
    Party getParty(int index);
 };

#endif	/* SYSTEM_H */
