/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"
#include <base/Time.hpp>
#include <range_sensor_micro_epsilon/range_sensor_micro_epsilonTypes.hpp>

using namespace range_sensor_micro_epsilon;

Task::Task(std::string const& name)
    : TaskBase(name)
{
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine)
    : TaskBase(name, engine)
{
}

Task::~Task()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Task.hpp for more detailed
// documentation about them.

bool Task::configureHook()
{
    RangeSensor* driver = new RangeSensor();
    if (!_io_port.get().empty())
        driver->openURI(_io_port.get());
    setDriver(driver);
    mDriver = driver;

    if (! TaskBase::configureHook())
        return false;
    return true;
}

void Task::processIO()
{
    int period = mDriver->poll();
    if (period <= 0)
        return;

    RangeMeasurements sample;

    sample.ranges = mDriver->readRanges(1000);
    sample.time = base::Tine::now();
    _laser_samples.write(sample);
    _error_statistics.write(mDriver->getErrors())



}

bool Task::startHook()
{
    if (! TaskBase::startHook())
        return false;
    mDriver->clear();
    return true;
}
void Task::updateHook()
{
    TaskBase::updateHook();
}
void Task::errorHook()
{
    TaskBase::errorHook();
}
void Task::stopHook()
{
    mDriver->close();
    TaskBase::stopHook();
}
void Task::cleanupHook()
{
    TaskBase::cleanupHook();
    setDriver(nullptr);
    delete mDriver;
    mDriver = nullptr;
}
