#ifndef ALIEN_H
#define ALIEN_H

class Alien {
    public:
	Alien();
	int getInput();

    protected:
	int trait[9];
	int encounter[2];
};

#endif //!ALIEN_H
