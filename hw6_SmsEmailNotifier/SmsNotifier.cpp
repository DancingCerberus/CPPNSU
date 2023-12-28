#include <iostream>
#include <utility>
#include "SmsNotifier.h"

SmsNotifier::SmsNotifier(std::string number) :
    number(std::move(number)) {}

void SmsNotifier::SendSms(const std::string &message) {
  std::cout << "Send " << message << " to number " << number << std::endl;
}

void SmsNotifier::Notify(const std::string &message) {
  SendSms(message);
}
