#include "INotifier.h"

class SmsNotifier final : public INotifier {
  std::string number;
 public:
  ~SmsNotifier() final = default;

  explicit SmsNotifier(std::string number);

  void Notify(const std::string &message) final;

  void SendSms(const std::string &message);
};