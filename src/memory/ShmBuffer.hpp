/*
 * Shared memory consumer, storing and updating pointer to shared memory
 *
 * User program must attach before detaching
 */

#ifndef SHM_BUFFER_HPP
#define SHM_BUFFER_HPP

#include <future>

#include "SemManager.hpp"

struct ptr_with_size {
    void *ptr;
    size_t  size;
};

class ShmBuffer {

	SemManager sems;
	size_t size[NKEYS]; // buffer size in bytes allocated against given key number

	bool verbose;

	// bool used[NKEYS];   // whether each key is currently used (allocated and not yet deleted, incl. not released by consumer)

	int current_key;    // takes values 0 or 1; most recent memory read from keys[current_key]
	int shmid;          // the shared memory id used for current key (-1 if not used)
	void *ptrs[NKEYS];  // pointers to shared memory, NULL if not allocated

	std::future<void> out;

	// void loop(); // event loop // this should be implemented in Kotlin

	void find_active(); // find key used by producer and set current_key to it; if no key found set it to -1

public:

	ShmBuffer(std::string pname, int rank, bool verbose = true);
	~ShmBuffer();

	ptr_with_size attach(); // attach to current memory
	void detach(bool current = true); // detach from current memory (true) or old memory (false)

	void update_key(bool wait = true); // find new key to attach to, call before attaching

	// below should be implemented in Kotlin

	// void reattach(bool wait); // wait to attach to next memory, or simply check synchronously without blocking

	// void init(); // initiate event loop
	// void term(); // terminate event loop

};

 #endif