// Compiled into a separate shared library with hidden visibility, mimicking a downstream
// library (such as stormpy) that includes carl headers and is linked against libcarl.
// getInstance() is called here, so if it were inline, this library would hold its own copy.
#include "SingletonProbe.h"

#include <carl/core/MonomialPool.h>
#include <carl/core/VariablePool.h>
#include <carl/core/carlLogging.h>
#include <carl/formula/SortManager.h>
#include <carl/formula/bitvector/BVConstraintPool.h>
#include <carl/formula/bitvector/BVTermPool.h>
#include <carl/formula/model/uninterpreted/SortValueManager.h>
#include <carl/formula/uninterpreted/UFInstanceManager.h>
#include <carl/formula/uninterpreted/UFManager.h>
#include <carl/util/TimingCollector.h>

#include <array>

namespace {
struct Entry {
    const char* name;
    const void* (*address)();
};

template<typename T>
const void* addressOf() {
    return &T::getInstance();
}

#define CARL_PROBE_ENTRY(T) \
    Entry {                 \
        #T, &addressOf<T>   \
    }

const std::array entries{
    CARL_PROBE_ENTRY(carl::VariablePool),     CARL_PROBE_ENTRY(carl::MonomialPool),      CARL_PROBE_ENTRY(carl::logging::Logger),
    CARL_PROBE_ENTRY(carl::TimingCollector),  CARL_PROBE_ENTRY(carl::SortManager),       CARL_PROBE_ENTRY(carl::SortValueManager),
    CARL_PROBE_ENTRY(carl::UFManager),        CARL_PROBE_ENTRY(carl::UFInstanceManager), CARL_PROBE_ENTRY(carl::BVTermPool),
    CARL_PROBE_ENTRY(carl::BVConstraintPool),
};
}  // namespace

extern "C" {
std::size_t carl_probe_count() {
    return entries.size();
}
const char* carl_probe_name(std::size_t i) {
    return entries.at(i).name;
}
const void* carl_probe_address(std::size_t i) {
    return entries.at(i).address();
}
}
