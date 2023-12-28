#pragma once

class INotifier {
 public:
  virtual ~INotifier() = default;

  virtual void Notify(const std::string &message) = 0;
};