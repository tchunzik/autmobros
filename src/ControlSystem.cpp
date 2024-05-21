#include "ControlSystem.hpp"

ControlSystem::ControlSystem(double dt)
  : E1("enc1"),
    E2("enc2"),
    fwKinOdom(0.15),
    RvRx(1.0),
    omegaR(0.0),
    invKin(0.15),
    // cont(21.2/2.0/M_PI), 
    qdMax(21.2),
    i(3441.0/104.0),
    kM(8.44e-3),
    M1("motor1"),
    cont(0.03/2.0/M_PI),
    QMax(0.1),
    iInv(104.0/3441.0),
    kMInv(1.0/8.44e-3),
    R(8.0),
    timedomain("Main time domain", dt, true)
{
    // Name all blocks
    E1.setName("E1");
    E2.setName("E2");
    E.setName("E");
    Ed.setName("Ed");
    fwKinOdom.setName("fwKinOdom");
    invKin.setName("invKin");
    cont.setName("cont");
    qdMax.setName("qdMax");
    i.setName("i");
    kM.setName("kM");
    M1.setName("M1");
    QMax.setName("QMax");
    iInv.setName("iInv");
    kMInv.setName("kMInv");
    R.setName("R");

    // Name all signals
    E1.getOut().getSignal().setName("q1 [m]");
    // E2.getOut().getSignal().setName("q2 [m]");
    E.getOut().getSignal().setName("q [m]");
    E.getOut().getSignal().setName("qd [m/s]");

    // E2.getOut().getSignal().setName("q2[rad]");
    // cont.getOut().getSignal().setName("qd1[rad/s]");
    // qdMax.getOut().getSignal().setName("qd1[rad/s]");
    // i.getOut().getSignal().setName("om1[rad/s]");
    // kM.getOut().getSignal().setName("U[V]");
    // --
    E2.getOut().getSignal().setName("q2[rad]");
    cont.getOut().getSignal().setName("Q1[Nm]");
    QMax.getOut().getSignal().setName("Q1[Nm]");
    iInv.getOut().getSignal().setName("T1[Nm]");
    kMInv.getOut().getSignal().setName("I1[A]");
    R.getOut().getSignal().setName("U1[V]");

    // Connect signals
    E.getIn(0).connect(E1.getOut());
    E.getIn(1).connect(E2.getOut());
    Ed.getIn().connect(E.getOut());
    fwKinOdom.getIn().connect(Ed.getOut());
    invKin.getInRvRx().connect(RvRx.getOut());
    invKin.getInOmegaR().connect(omegaR.getOut());
    //--- 
    cont.getIn().connect(E2.getOut());
    // qdMax.getIn().connect(cont.getOut());
    // i.getIn().connect(qdMax.getOut());
    // kM.getIn().connect(i.getOut());
    // M1.getIn().connect(kM.getOut());
    // --
    QMax.getIn().connect(cont.getOut());
    iInv.getIn().connect(QMax.getOut());
    kMInv.getIn().connect(iInv.getOut());
    R.getIn().connect(kMInv.getOut());
    M1.getIn().connect(R.getOut());

    // Add blocks to timedomain
    timedomain.addBlock(E1);
    timedomain.addBlock(E2);
    timedomain.addBlock(E);
    timedomain.addBlock(Ed);
    timedomain.addBlock(fwKinOdom);
    timedomain.addBlock(RvRx);
    timedomain.addBlock(omegaR);
    timedomain.addBlock(invKin);
    timedomain.addBlock(cont);
    // ---
    // timedomain.addBlock(qdMax);
    // timedomain.addBlock(i);
    // timedomain.addBlock(kM);
    // timedomain.addBlock(M1);
    // ----
    timedomain.addBlock(QMax);
    timedomain.addBlock(iInv);
    timedomain.addBlock(kMInv);
    timedomain.addBlock(R);
    timedomain.addBlock(M1);

    // Add timedomain to executor
    eeros::Executor::instance().add(timedomain);
}