#ifndef RWLOCK_TRWLOCKREADGUARD_HPP
#define RWLOCK_TRWLOCKREADGUARD_HPP

#include <RwLock/TRwLockGuardBase.hpp>

namespace rwl {

template<typename T>
class TRwLockReadGuard : public TRwLockGuardBase<const T> {
    public:
    TRwLockReadGuard(const std::shared_mutex* sharedMutex, const std::unique_ptr<T>* data)
        : TRwLockGuardBase<const T>(sharedMutex, data) {
        this->m_pSharedMutex->lock_shared();
    }
    ~TRwLockReadGuard() { this->m_pSharedMutex->unlock_shared();}
    TRwLockReadGuard(TRwLockReadGuard&& other) noexcept
        : TRwLockGuardBase<T>(std::move(other)) {}

};

}

#endif //XSYNC_TRWLOCKREADGUARD_HPP
