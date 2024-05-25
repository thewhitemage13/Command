#include <iostream>]
#include <vector>
#include <stack>
using namespace std;

__interface ICommand {
    virtual void Positive() = 0;
    virtual void Negative() = 0;
};

class Conveyor {
public:
    void On() {
        cout << "conveyor belt is up and running\n";
    }

    void Off() {
        cout << "conveyor stopped\n";
    }

    void SpeedIncrease() {
        cout << "increased conveyor speed\n";
    }

    void SpeedDecrease() {
        cout << "reduced conveyor speed\n";
    }
};

class ConveyorWorkCommand : public ICommand {
private:
    Conveyor* conveyor;
public:
    ConveyorWorkCommand(Conveyor* _conveyor) : conveyor(_conveyor){}
    void Positive() override {
        conveyor->On();
    }
    void Negative() override {
        conveyor->Off();
    }
};

class ConveyorAdjustCommand : public ICommand {
private:
    Conveyor* conveyor;
public:
    ConveyorAdjustCommand(Conveyor* _conveyor) : conveyor(_conveyor){}
    void Positive() override {
        conveyor->SpeedIncrease();
    }
    void Negative() override {
        conveyor->SpeedDecrease();
    }
};

class Multipult {
private:
    vector<ICommand*> commands;
    stack<ICommand*> history;
public:
    Multipult() {
        commands.resize(2);
    }
    void SetCommand(int button, ICommand* command) {
        commands[button] = command;
    }
    void PressOn(int button) {
        commands[button]->Positive();
        history.push(commands[button]);
    }
    void PressCancel() {
        if (!history.empty()) {
            history.top()->Negative();
            history.pop();
        }
    }
};

int main() {
    Conveyor* conveyor = new Conveyor();
    Multipult* multipult = new Multipult();
    
    multipult->SetCommand(0, new ConveyorWorkCommand(conveyor));
    multipult->SetCommand(1, new ConveyorAdjustCommand(conveyor));

    multipult->PressOn(0);
    multipult->PressOn(1);
    multipult->PressCancel();
    multipult->PressCancel();

}