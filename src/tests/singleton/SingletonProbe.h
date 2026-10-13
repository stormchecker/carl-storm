#pragma once

#include <cstddef>

/**
 * Interface of the probe library.
 */
extern "C" {
/// Number of singletons the probe reports.
__attribute__((visibility("default"))) std::size_t carl_probe_count();
/// Name of the i-th singleton.
__attribute__((visibility("default"))) const char* carl_probe_name(std::size_t i);
/// Address of the i-th singleton as seen from inside the probe library.
__attribute__((visibility("default"))) const void* carl_probe_address(std::size_t i);
}
