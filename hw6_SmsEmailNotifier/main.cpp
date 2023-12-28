#include <iostream>
#include <vector>
#include "SmsNotifier.h"
#include "EmailNotifier.h"

int main() {
  std::vector<INotifier*> notifiers;
  notifiers.push_back(new SmsNotifier("+7-923-228-38-72"));
  notifiers.push_back(new EmailNotifier("m.filippov@g.nsu.ru"));

  for (auto &notifier : notifiers)
    notifier->Notify("Hello");

  for (auto &notifier : notifiers)
    delete notifier;
  return 0;
}
