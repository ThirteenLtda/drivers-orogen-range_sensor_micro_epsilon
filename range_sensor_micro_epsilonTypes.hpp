#ifndef range_sensor_micro_epsilon_TYPES_HPP
#define range_sensor_micro_epsilon_TYPES_HPP
#include <base/Time.hpp>
#include <vector>

/* If you need to define types specific to your oroGen components, define them
 * here. Required headers must be included explicitly
 *
 * However, it is common that you will only import types from your library, in
 * which case you do not need this file
 */

namespace range_sensor_micro_epsilon {

    struct RangeMeasurements{
        base::Time time;
        std::vector<double> ranges;
    };
}

#endif
