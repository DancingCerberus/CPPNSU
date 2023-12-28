#include "INotifier.h"

class EmailNotifier final : public INotifier {
  std::string email;
 public:
  ~EmailNotifier() final = default;

  explicit EmailNotifier(std::string email);

  void SendEmail(const std::string &message);

  void Notify(const std::string &message) final;
};
