#define threadAmount (30)
struct lock_t{
  int lock[threadAmount]; //0 available, 1 hold
  int lockState;        //lock[currentLock] = 0 means no lock now
};
