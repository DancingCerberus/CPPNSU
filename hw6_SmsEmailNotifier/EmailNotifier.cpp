#include <iostream>
#include <utility>
#include "EmailNotifier.h"

EmailNotifier::EmailNotifier(std::string email) :
        email(std::move(email)) {}

void EmailNotifier::SendEmail(const std::string& message) {
  std::cout << "Send " << message << " e-mail "<< email << std::endl;
}

void EmailNotifier::Notify(const std::string &message) {
  SendEmail(message);
}