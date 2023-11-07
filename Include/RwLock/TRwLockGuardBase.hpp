#ifndef RWLOCK_TRWLOCKGUARDBASE_HPP
#define RWLOCK_TRWLOCKGUARDBASE_HPP

#include <shared_mutex>
#include <memory>
#include <type_traits>

namespace rwl {

template<typename T>
class TRwLockGuardBase {
    public:
    using InnerType = T;

    public:
    TRwLockGuardBase(const std::shared_mutex* sharedMutex, const T* data)
        :   m_pSharedMutex{const_cast<std::shared_mutex*>(sharedMutex)},
            m_pData{const_cast<T*>(data)} {}
    ~TRwLockGuardBase()=default;
    TRwLockGuardBase(const TRwLockGuardBase&)=delete;
    TRwLockGuardBase& operator=(const TRwLockGuardBase&)=delete;
    TRwLockGuardBase(TRwLockGuardBase&& other) noexcept { MoveInit(std::move(other)); }
    TRwLockGuardBase& operator=(TRwLockGuardBase&& other) noexcept { MoveInit(std::move(other)); }

    public:
    inline T* operator->() const { return (T*)&this->m_pData; }
    inline T* Get() const { return (T*)&this->m_pData; }
    inline T& operator*() const { return this->m_pData; }

    protected:
    void MoveInit(TRwLockGuardBase&& other) noexcept {
        m_pSharedMutex = other.m_pSharedMutex;
        m_pData = std::move(other.m_pData);
        other.m_pSharedMutex = nullptr;
        other.m_pData = nullptr;
    }

    protected:
    std::shared_mutex* m_pSharedMutex;
    T* m_pData;
};

}

#endif //RWLOCK_TRWLOCKGUARDBASE_HPP
