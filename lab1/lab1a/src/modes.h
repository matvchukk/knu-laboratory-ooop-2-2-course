#pragma once

#include "logging.h"

/// Interactive mode
///
/// Here, you could test all MessageLog methods
/// \return true if work will be continued, otherwise, false
bool interactive();

/// Demo mode
///
/// Here will be shown all MessageLog functions. You mustn't enter any info.
/// \return true if work will be continued, otherwise, false
bool demonstration();

/// Benchmark mode
///
/// Here will be tested speed of processing writing, reading and searching
/// When time for work will be more than 10 sec, mode will be finished
/// \return true if work will be continued, otherwise, false
bool benchmark();