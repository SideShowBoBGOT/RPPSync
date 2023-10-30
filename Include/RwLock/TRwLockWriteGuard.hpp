#ifndef RWLOCK_TRWLOCKWRITEGUARD_HPP
#define RWLOCK_TRWLOCKWRITEGUARD_HPP

#include <RwLock/TRwLockGuardBase.hpp>

namespace rwl {

template<typename T>
class TRwLockWriteGuard : public TRwLockGuardBase<T> {
    public:
    TRwLockWriteGuard(std::shared_mutex* sharedMutex, std::unique_ptr<T>* data)
        : TRwLockGuardBase<T>(sharedMutex, data) {
        this->m_pSharedMutex->lock();
    }
    ~TRwLockWriteGuard() { this->m_pSharedMutex->unlock(); }
    TRwLockWriteGuard(TRwLockWriteGuard&& other) noexcept
        : TRwLockGuardBase<T>(std::move(other)) {}
};

}

#endif //RWLOCK_TRWLOCKWRITEGUARD_HPP
