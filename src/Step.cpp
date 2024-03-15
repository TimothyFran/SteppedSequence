#include "Step.h"

Step::Step() {
  conditions.setStorage(conditions_storage);
  actions.setStorage(actions_storage);
}

void Step::AddCondition(StepCondition* _condition) {
    conditions.push_back(_condition);
}

void Step::AddAction(StepAction* _action) {
    actions.push_back(_action);
}

bool Step::CanExecute() {
    for (int i = 0; i < conditions.size(); i++) {
      if(conditions[i] == nullptr) break;
      if(!conditions[i]->IsMet()) {
          return false;
      }
    }
    return true;
}

void Step::CheckCondition() {
    for (int i = 0; i < conditions.size(); i++) {
      if(conditions[i] == nullptr) break;
      conditions[i]->Check();
    }
}

void Step::Start() {
    for (int i = 0; i < actions.size(); i++) {
      if(actions[i] == nullptr) break;
        actions[i]->Start();
    }
}

void Step::Run() {
    for (int i = 0; i < actions.size(); i++) {
      if(actions[i] == nullptr) break;
        actions[i]->Run();
    }
}

bool Step::IsDone() {
    bool res = true;
    for (int i = 0; i < actions.size(); i++) {
      if(actions[i] == nullptr) break;
        if(actions[i]->ContinueOnCompleted() && actions[i]->IsCompleted()) {
          return true;
        }
        if(!actions[i]->IsCompleted()) {
            res = false;
        }
    }
    return res;
}

void Step::Reset() {
    for (int i = 0; i < conditions.size(); i++) {
        conditions[i]->Reset();
    }
    for (int i = 0; i < actions.size(); i++) {
        actions[i]->Finish();
    }
}
void Step::SetConditions() {
    for (int i = 0; i < conditions.size(); i++) {
        conditions[i]->Set();
    }
}

void Step::Begin() {
    for (int i = 0; i < actions.size(); i++) {
        actions[i]->Begin();
    }
    for (int i = 0; i < conditions.size(); i++) {
        conditions[i]->Begin();
    }
}