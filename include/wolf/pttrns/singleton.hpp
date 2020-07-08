#ifndef __WOLF_SINGLETON__
#define __WOLF_SINGLETON__

#include <mutex>
#include <memory>


namespace Wolf::Pttrn {

    template <typename T>
    class Singleton { 
        inline static std::shared_ptr<T> spInstance {nullptr};
        inline static std::once_flag xInstanceOnceAllocationFlag;
    public:
        static auto spGetInstance(){
            std::call_once(xInstanceOnceAllocationFlag, [&](){
                spInstance = std::make_shared<T>();
            });
            return spInstance;
        }
    };

}

#endif //__WOLF_SINGLETON__