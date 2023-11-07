#ifndef RWLOCK_TRWLOCK_HPP
#define RWLOCK_TRWLOCK_HPP

#include <RwLock/TRwLockWriteGuard.hpp>
#include <RwLock/TRwLockReadGuard.hpp>
#include <RwLock/TRwLockTryWriteGuard.hpp>
#include <RwLock/TRwLockTryReadGuard.hpp>

#include <shared_mutex>
#include <memory>
#include <optional>
#include <type_traits>

namespace rwl {

template<typename T>
class TRwLock {
    public:
    using InnerType = T;

    template<typename = std::enable_if_t<std::is_default_constructible_v<T>, void>>
    TRwLock() {};

    public:
    template<typename ...Args>
    explicit TRwLock(Args&&... args) : m_xData{T(std::forward<Args>(args)...)} {}

    public:
    TRwLock(const TRwLock&)=delete;
    TRwLock& operator=(const TRwLock&)=delete;

    public:
    TRwLockReadGuard<T> Read() const { return TRwLockReadGuard<T>(&m_xSharedMutex, &m_xData); }
    TRwLockWriteGuard<T> Write() const { return TRwLockWriteGuard(&m_xSharedMutex, &m_xData); }
    std::optional<TRwLockTryReadGuard<T>> TryRead() const { return TryGuard<TRwLockTryReadGuard<T>>(); }
    std::optional<TRwLockTryWriteGuard<T>> TryWrite() const { return TryGuard<TRwLockTryWriteGuard<T>>(); }

    protected:
    template<typename TryGuardType>
    std::optional<TryGuardType> TryGuard() const {
        bool isAcquired = false;
        auto guard = std::make_optional<TryGuardType>(&m_xSharedMutex, &m_xData, isAcquired);
        if(!isAcquired) {
            guard.reset();
        }
        return guard;
    }

    protected:
    std::shared_mutex m_xSharedMutex;
    T m_xData;
};

}

#endif //RWLOCK_TRWLOCK_HPP
