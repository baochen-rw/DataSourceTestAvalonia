/**
* \file
* Threading support.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_THREAD_H
#define KZS_THREAD_H


#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>

#if !defined WIN32
#define KZ_USE_PTHREAD
#endif

#if defined KZ_USE_PTHREAD
#include <pthread.h>
#endif

/**
 * \struct KzsThread
 * An operating system thread that allows concurrent execution of code.
 * The code is supplied as a callback of type KzsThreadRunner.
 */
struct KzsThread;


/** Key type to use when storing thread specific global data. */
#if defined KZ_USE_PTHREAD
typedef pthread_key_t KzsThreadLocalStorageKey;
#else
typedef unsigned long KzsThreadLocalStorageKey;
#endif


/** Thread identifier. */
#if defined KZ_USE_PTHREAD
typedef pthread_t KzsThreadId;
#else
typedef unsigned long KzsThreadId;
#endif

/**
 * \struct KzsThreadLock
 * Lock object for synchronizing threads. This object can be used to prevent multiple threads from accessing data
 * concurrently and to signal between threads. Use kzsThreadLockAcquire and kzsThreadLockRelease to protect data from
 * concurrent access. Use kzsThreadLockWait and kzsThreadLockSet to communicate between threads.
 */
struct KzsThreadLock;


/** Thread execution function type. */
typedef kzsError (*KzsThreadRunner)(void* userData);


/**
 * Creates a thread using the given runner function and arbitrary user data. This function also starts the thread.
 * If deleteAutomatically is KZ_TRUE, the thread object is deleted when the thread finishes execution.
 * \param out_thread Resulting thread, KZ_NULL if not required.
 */
KANZI_API kzsError kzsThreadCreate(KzsThreadRunner threadRunner, void* userData, kzBool deleteAutomatically, struct KzsThread** out_thread);

/** Deletes a thread. It is an error to delete a running thread. */
KANZI_API kzsError kzsThreadDelete(struct KzsThread* thread);

/** Waits until the given thread is terminated. */
KANZI_API kzsError kzsThreadJoin(struct KzsThread* thread);

/**
 * Returns the error result of the thread. Also returns error if the thread has not yet finished execution.
 * Use kzsThreadJoin to make sure the thread is finished.
 */
KANZI_API kzsError kzsThreadGetExitResult(const struct KzsThread* thread);

/** Gets the current thread id. */
KANZI_API KzsThreadId kzsThreadGetCurrent(void);

/** Checks if the given thread is the thread that is executing this function. */
KANZI_API kzBool kzsThreadIsCurrent(const struct KzsThread* thread);

/** Sleeps the thread that is executing this function by given amount of milliseconds. */
KANZI_API kzsError kzsThreadSleep(kzUint milliseconds);


/** Creates a thread synchronization lock object. */
KANZI_API kzsError kzsThreadLockCreate(struct KzsThreadLock** out_threadLock);

/** Deletes a thread synchronization lock object. */
KANZI_API kzsError kzsThreadLockDelete(struct KzsThreadLock* threadLock);

/** Starts a synchronized code section by acquiring a thread lock. This call must be paired with kzsThreadLockRelease in all code paths. */
KANZI_API kzsError kzsThreadLockAcquire(struct KzsThreadLock* threadLock);

/** Ends a synchronized code section by releasing a thread lock. This call must be paired with kzsThreadLockAcquire in all code paths. */
KANZI_API kzsError kzsThreadLockRelease(struct KzsThreadLock* threadLock);

/**
 * Waits for a given thread lock to become true. If the lock is already true, this function will not wait.
 * If autoLock is KZ_TRUE, the lock must not be acquired by the thread.
 * If autoLock is KZ_FALSE, the lock must be acquired by the thread exactly once.
 */
KANZI_API kzsError kzsThreadLockWait(struct KzsThreadLock* threadLock, kzBool autoLock);

/**
 * Waits for a given thread lock to become true. If the lock is already true, this function will not wait.
 * After the wait is finished, the lock will be set to KZ_FALSE before any other thread wokes up.
 * If autoLock is KZ_TRUE, the lock must not be acquired by the thread.
 * If autoLock is KZ_FALSE, the lock must be acquired by the thread exactly once.
 */
KANZI_API kzsError kzsThreadLockWaitAndReset(struct KzsThreadLock* threadLock, kzBool autoLock);

/** 
 * Sets the value of the given thread lock to true or false. If the value is true, any thread waiting for it can wake up.
 * If autoLock is KZ_TRUE, the lock must not be acquired by the thread.
 * If autoLock is KZ_FALSE, the lock must be acquired by the thread exactly once.
 */
KANZI_API kzsError kzsThreadLockSet(struct KzsThreadLock* threadLock, kzBool value, kzBool autoLock);

/** 
 * Returns the value of the given thread lock (true or false).
 * If autoLock is KZ_TRUE, the lock must not be acquired by the thread.
 * If autoLock is KZ_FALSE, the lock must be acquired by the thread exactly once.
 */
KANZI_API kzsError kzsThreadLockIsSet(struct KzsThreadLock* threadLock, kzBool autoLock, kzBool* out_isSet);

/** Gets number of processor cores in system. Throws KZS_EXCEPTION_UNDEFINED_THREAD_OPERATION if processor count cannot be queried from system. */
KANZI_API kzsException kzsThreadGetProcessorCount(kzUint* out_processorCount);

/** Initializes thread local storage key. */
KANZI_API kzsError kzsThreadLocalStorageKeyInitialize(KzsThreadLocalStorageKey* key);
/** Uninitializes thread local storage key. */
KANZI_API kzsError kzsThreadLocalStorageKeyUninitialize(KzsThreadLocalStorageKey* key);
/** Sets thread specific global data using the given key. This data is unique between different threads and can be retrieved with GetData. */
KANZI_API kzsError kzsThreadLocalStoragePutData(const KzsThreadLocalStorageKey* key, void* data);
/** Gets thread specific global data using the given key. */
KANZI_API kzsError kzsThreadLocalStorageGetData(const KzsThreadLocalStorageKey* key, void** out_data);


#endif
