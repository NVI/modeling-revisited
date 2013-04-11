#ifndef PROJECT_H
#define	PROJECT_H

class Project {
public:
    Project(const std::string filenames [4], const Setup setup, System system, Bundle bundle);
    int getIterations();
    void inputPolitics();
    void inputNetwork();
    void outputPolitics();
    void outputNetwork();
    void iterateBundle(int rand);
    Project(const Project& orig);
    virtual ~Project();
private:
    const std::string filenames [4];
    const Setup setup;
    System system;
    Bundle bundle;
};

#endif	/* PROJECT_H */
