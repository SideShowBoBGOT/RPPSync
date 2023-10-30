#ifndef RWLOCK_TRWLOCK_HPP
#define RWLOCK_TRWLOCK_HPP

#include <RwLock/TRwLockWriteGuard.hpp>
#include <RwLock/TRwLockReadGuard.hpp>
#include <RwLock/TRwLockTryWriteGuard.hpp>
#include <RwLock/TRwLockTryReadGuard.hpp>

#include <shared_mutex>
#include <memory>
#include <optional>

namespace rwl {

template<typename T>
class TRwLock {
    public:
    using InnerType = T;

    public:
    template<typename ...Args>
    explicit TRwLock(Args... args)
        : m_pData{std::make_unique<T>(args...)} {}
    TRwLock(const TRwLock&)=delete;
    TRwLock& operator=(const TRwLock&)=delete;

    public:
    TRwLockReadGuard<T> Read() { return TRwLockReadGuard<T>(&m_xSharedMutex, &m_pData); }
    TRwLockWriteGuard<T> Write() { return TRwLockWriteGuard(&m_xSharedMutex, &m_pData); }
    std::optional<TRwLockTryReadGuard<T>> TryRead() { return TryGuard<TRwLockTryReadGuard<T>>(); }
    std::optional<TRwLockTryWriteGuard<T>> TryWrite() { return TryGuard<TRwLockTryWriteGuard<T>>(); }

    protected:
    template<typename TryGuardType>
    std::optional<TryGuardType> TryGuard() {
        bool isAcquired = false;
        auto guard = std::make_optional<TryGuardType>(&m_xSharedMutex, &m_pData, isAcquired);
        if(!isAcquired) {
            guard.reset();
        }
        return guard;
    }

    protected:
    std::shared_mutex m_xSharedMutex;
    std::unique_ptr<T> m_pData;
};

}

#endif //RWLOCK_TRWLOCK_HPP
