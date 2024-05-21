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
#include "customBlocks/InvMotMod.hpp"
#include "customBlocks/InvKin.hpp"
#include <eeros/control/DeMux.hpp>
#include <eeros/control/PeripheralOutput.hpp>
#include <eeros/control/Saturation.hpp>

using namespace eeros::control;

class ControlSystem
{
public:
    ControlSystem(double dt);

    // Define Blocks
    
    PeripheralInput<> E1, E2;
    Mux<2> E;
    D<eeros::math::Vector2> Ed;
    FwKinOdom fwKinOdom;
    Constant<> RvRx, omegaR;
    InvKin invKin;
    //-----MotIncEx2----
    Saturation<> qdMax;
    // Gain<> cont;
    Gain<> i;
    Gain<> kM;
    // PeripheralOutput<> M1;
    //-----MotIncEx3----
    Gain<> cont;
    Saturation<> QMax;
    Gain<> iInv;
    Gain<> kMInv;
    Gain<> R;
    PeripheralOutput<> M1;


    TimeDomain timedomain;
};

#endif // CONTROLSYSTEM_HPP