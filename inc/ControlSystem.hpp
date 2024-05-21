#ifndef CONTROLSYSTEM_HPP_
#define CONTROLSYSTEM_HPP_

#include <eeros/control/TimeDomain.hpp>
#include <eeros/core/Executor.hpp>
#include <eeros/control/PeripheralInput.hpp>
#include <eeros/control/Gain.hpp>
#include <eeros/control/Constant.hpp>
#include <eeros/control/Mux.hpp>
#include <eeros/control/D.hpp>
#include "customBlocks/FwKinOdom.hpp"
#include "customBlocks/Controller.hpp"
#include "customBlocks/ControllerPI.hpp"
#include "customBlocks/InvMotMod.hpp"
#include "customBlocks/InvKin.hpp"
#include <eeros/control/DeMux.hpp>
#include <eeros/control/Sum.hpp>
#include <eeros/control/PeripheralOutput.hpp>
#include <eeros/control/Saturation.hpp>

using namespace eeros::control;

class ControlSystem
{
public:
    ControlSystem(double dt);

    // Define Blocks
    
    // Define Blocks
    PeripheralInput<> E1, E2;
    Mux<2> E;
    Mux<2> E_d;
    Controller<eeros::math::Vector2> cont;
    InvMotMod<eeros::math::Vector2> invMotMod;
    DeMux<2> U;
    PeripheralOutput<> M1;
    PeripheralOutput<> M2;

    TimeDomain timedomain;
};

#endif // CONTROLSYSTEM_HPP