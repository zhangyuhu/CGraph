/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: GParam.h
@Time: 2021/6/11 6:32 下午
@Desc: 
***************************/

#ifndef CGRAPH_GPARAM_H
#define CGRAPH_GPARAM_H

#include <string>
#include <set>

    #if __cplusplus >= 201703L
#include <shared_mutex>
    #else
#include <mutex>
    #endif

#include "GParamObject.h"

CGRAPH_NAMESPACE_BEGIN

class GParam : public GParamObject {
public:
#if __cplusplus >= 201703L
    std::shared_mutex _param_shared_lock_;    // 用于参数互斥的锁信息
#else
    std::mutex _param_shared_lock_;
#endif

    /**
     * 保存参数信息
     * @param path 位置路径
     * @return
     */
    virtual CStatus dump(const std::string& path);

    /**
     * 加载参数信息
     * @param path 位置路径
     * @return
     */
    virtual CStatus load(const std::string& path);

    /**
     * 获取参数的调用栈信息
     * @param backtrace
     * @return
     */
    CStatus getBacktrace(std::set<std::string>& backtrace);

    /**
     * 添加回溯信息
     * @param name
     * @param session
     * @return
     */
    CVoid addBacktrace(const std::string& name, const std::string& session);

    /**
     * 获取对应的key信息
     * @return
     */
    const std::string& getKey() const;

protected:
    /**
     * 每次pipeline执行结束，会调用一次reset
     * @return
     */
    virtual CVoid reset() = 0;

    /**
     * 每次pipeline执行前，会调用一次setup，可以不实现
     * @return
     */
    virtual CStatus setup() {
        CGRAPH_EMPTY_FUNCTION
    }


private:
    std::string key_;                        // 对应的key信息
    std::set<std::string> backtrace_;        // 记录参数的调用栈信息，仅记录get 此参数的地方。不包括 create和remove的地方。
    CBool backtrace_enable_ = false;         // 是否使能backtrace功能

    friend class GParamManager;
};

using GParamPtr = GParam *;

CGRAPH_NAMESPACE_END

#endif //CGRAPH_GPARAM_H
