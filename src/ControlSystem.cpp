#include "ControlSystem.hpp"

ControlSystem::ControlSystem(double dt)
 : E1("enc1"),
      E2("enc2"),
      fwKinOdom(0.15),
      timedomain("Main time domain", dt, true)
{
    // Name all blocks
    E1.setName("E1");
    E2.setName("E2");
    E.setName("E");
    Ed.setName("Ed");
    fwKinOdom.setName("fwKinOdom");

    // Name all signals
    E1.getOut().getSignal().setName("q1 [m]");
    E2.getOut().getSignal().setName("q2 [m]");
    E.getOut().getSignal().setName("q [m]");
    E.getOut().getSignal().setName("qd [m/s]");

    // Connect signals
    E.getIn(0).connect(E1.getOut());
    E.getIn(1).connect(E2.getOut());
    Ed.getIn().connect(E.getOut());
    fwKinOdom.getIn().connect(Ed.getOut());

    // Add blocks to timedomain
    timedomain.addBlock(E1);
    timedomain.addBlock(E2);
    timedomain.addBlock(E);
    timedomain.addBlock(Ed);
    timedomain.addBlock(fwKinOdom);

    // Add timedomain to executor
    eeros::Executor::instance().add(timedomain);
}

//____________________________________________________
//Sequencer exercise
//     : q1("quat1"), g(2.0), c(0.0), servo("servo1"),
//       timedomain("Main time domain", dt, true)
// {
//     // Name all blocks
//     q1.setName("q1");
//     g.setName("g");
//     c.setName("c");
//     servo.setName("servo");

//     // Name all signals
//     q1.getOut().getSignal().setName("beta/half [rad]");
//     g.getOut().getSignal().setName("beta [rad]");
//     c.getOut().getSignal().setName("Servo setpoint [rad]");

//     // Connect signals
//     g.getIn().connect(q1.getOut());
//     servo.getIn().connect(c.getOut());

//     // Add blocks to timedomain
//     timedomain.addBlock(q1);
//     timedomain.addBlock(g);
//     timedomain.addBlock(c);
//     timedomain.addBlock(servo);

//     // Add timedomain to executor
//     eeros::Executor::instance().add(timedomain);
// }