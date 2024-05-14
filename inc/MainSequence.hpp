#ifndef MAINSEQUENCE_HPP_
#define MAINSEQUENCE_HPP_

#include <eeros/sequencer/Sequencer.hpp>
#include <eeros/sequencer/Sequence.hpp>
#include <eeros/safety/SafetySystem.hpp>
#include "MyRobotSafetyProperties.hpp"
#include "ControlSystem.hpp"
#include <eeros/sequencer/Wait.hpp>
#include "customSteps/moveServoTo.hpp"
#include "customSequences/orientationException.hpp"
#include <eeros/sequencer/Monitor.hpp>

class MainSequence : public eeros::sequencer::Sequence
{
public:
    MainSequence(std::string name, eeros::sequencer::Sequencer &seq,
                 eeros::safety::SafetySystem &ss,
                 MyRobotSafetyProperties &sp, ControlSystem &cs)
        : eeros::sequencer::Sequence(name, seq),
          ss(ss),
          sp(sp),
          cs(cs),

          sleep("Sleep", this)
    {
          log.info() << "Sequence created: " << name;
    }

    //       moveServoTo("moveServoTo", this, cs),

    //       checkOrientation(0.1, cs),
    //       orientationException("Orientation exception", this, cs, checkOrientation),
    //       orientationMonitor("Orientation monitor", this, checkOrientation, eeros::sequencer::SequenceProp::resume, &orientationException)
    // {
    //     addMonitor(&orientationMonitor);
    //     log.info() << "Sequence created: " << name;
    // }

    int action()
    {
        while (eeros::sequencer::Sequencer::running)
        {
            sleep(1.0);
            log.info() << cs.fwKinOdom.getOutGrR().getSignal();
            log.info() << cs.fwKinOdom.getOutPhi().getSignal();
        }
        return 0;
        //Sequnecer exercise
        // while (eeros::sequencer::Sequencer::running)
        // {
        //     moveServoTo(-1.5);
        //     sleep(1.0);
        //     moveServoTo(1.5);
        //     sleep(1.0);
        // }
        // return 0;
        //--------------
    }

private:
    eeros::safety::SafetySystem &ss;
    ControlSystem &cs;
    MyRobotSafetyProperties &sp;

    eeros::sequencer::Wait sleep;

    //
    // //sequnecer exercise
    // eeros::safety::SafetySystem &ss;
    // ControlSystem &cs;
    // MyRobotSafetyProperties &sp;

    // eeros::sequencer::Wait sleep;
    // MoveServoTo moveServoTo;
    // CheckOrientation checkOrientation;
    // OrientationException orientationException;
    // eeros::sequencer::Monitor orientationMonitor;


};

#endif // MAINSEQUENCE_HPP_