#ifndef RWLOCK_TRWLOCKGUARDBASE_HPP
#define RWLOCK_TRWLOCKGUARDBASE_HPP

#include <shared_mutex>
#include <memory>
#include <type_traits>

namespace rwl {

template<typename T>
class TRwLockGuardBase {
    public:
    using InnerType = std::remove_const_t<T>;

    public:
    TRwLockGuardBase(std::shared_mutex* sharedMutex, std::unique_ptr<InnerType>* data)
        : m_pSharedMutex{sharedMutex}, m_pData{data} {}
    ~TRwLockGuardBase()=default;
    TRwLockGuardBase(const TRwLockGuardBase&)=delete;
    TRwLockGuardBase& operator=(const TRwLockGuardBase&)=delete;
    TRwLockGuardBase(TRwLockGuardBase&& other) noexcept { MoveInit(std::move(other)); }
    TRwLockGuardBase& operator=(TRwLockGuardBase&& other) noexcept { MoveInit(std::move(other)); }

    public:
    inline T* operator->() const { return this->m_pData->get(); }
    inline T& operator*() const { return *this->m_pData; }

    protected:
    void MoveInit(TRwLockGuardBase&& other) noexcept {
        m_pSharedMutex = other.m_pSharedMutex;
        m_pData = std::move(other.m_pData);
        other.m_pSharedMutex = nullptr;
        other.m_pData = nullptr;
    }

    protected:
    std::shared_mutex* m_pSharedMutex;
    std::unique_ptr<InnerType>* m_pData;
};

}

#endif //RWLOCK_TRWLOCKGUARDBASE_HPP
