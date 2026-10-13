#include "../Common.h"
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

#include <string>
#include <vector>

namespace {
template<typename T>
const void* addressOf() {
    return &T::getInstance();
}
}  // namespace

// A second shared library (built with hidden visibility) must see the same singleton instances as this executable.
TEST(SingletonUniqueness, SharedAcrossLibraries) {
    const std::vector<std::pair<std::string, const void*>> expected{
        {"carl::VariablePool", addressOf<carl::VariablePool>()},
        {"carl::MonomialPool", addressOf<carl::MonomialPool>()},
        {"carl::logging::Logger", addressOf<carl::logging::Logger>()},
        {"carl::TimingCollector", addressOf<carl::TimingCollector>()},
        {"carl::SortManager", addressOf<carl::SortManager>()},
        {"carl::SortValueManager", addressOf<carl::SortValueManager>()},
        {"carl::UFManager", addressOf<carl::UFManager>()},
        {"carl::UFInstanceManager", addressOf<carl::UFInstanceManager>()},
        {"carl::BVTermPool", addressOf<carl::BVTermPool>()},
        {"carl::BVConstraintPool", addressOf<carl::BVConstraintPool>()},
    };
    // Guards against forgetting to add a singleton to one of the two lists.
    ASSERT_EQ(expected.size(), carl_probe_count());
    for (std::size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(expected[i].first, carl_probe_name(i));
        EXPECT_EQ(expected[i].second, carl_probe_address(i)) << "Singleton " << expected[i].first << " exists twice";
    }
}
