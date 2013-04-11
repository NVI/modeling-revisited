#ifndef SYSTEM_H
#define	SYSTEM_H

class System {
public:
    System();
    void addParty(Setup setup, int index, double distances [8]);
    Party getParty(int index);
private:
    std::map<int, Party> parties;
 };

#endif	/* SYSTEM_H */
