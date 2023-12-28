#include <cassert>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <functional>

struct Email {
  std::string from;
  std::string to;
  std::string body;
};


class Worker {
 public:
  virtual ~Worker() = default;

  virtual void Process(std::unique_ptr<Email> email) = 0;

  virtual void Run() {
    throw std::logic_error("Unimplemented");
  }

 protected:
  void PassOn(std::unique_ptr<Email> email) const {
    if (next_)
      next_->Process(std::move(email));
  }

 public:
  void SetNext(std::unique_ptr<Worker> next) {
    next_ = std::move(next);
  }

  Worker *GetNext() {
    return next_.get();
  }

 private:
  std::unique_ptr<Worker> next_;
};


class Reader : public Worker {
 public:
  explicit Reader(std::istream &input) : input_(input) {}

  void Process(std::unique_ptr<Email> email) override {
    PassOn(std::move(email));
  }

  void Run() override {
    std::string line;
    while (getline(input_, line)) {
      auto email = std::make_unique<Email>();
      email->from = line;
      getline(input_, email->to);
      getline(input_, email->body);
      Process(std::move(email));
    }
  }

 private:
  std::istream &input_;
};


class Filter : public Worker {
 public:
  using Function = std::function<bool(const Email &)>;

  explicit Filter(Function filter) : filter_(std::move(filter)) {}

  void Process(std::unique_ptr<Email> email) override {
    if (filter_(*email))
      PassOn(std::move(email));
  }

 private:
  Function filter_;
};


class Copier : public Worker {
 public:
  explicit Copier(std::string send_to) : send_to_(std::move(send_to)) {}

  void Process(std::unique_ptr<Email> email) override {
    auto copy = std::make_unique<Email>(*email);
    copy->to = send_to_;
    PassOn(std::move(email));
    PassOn(std::move(copy));
  }

 private:
  std::string send_to_;
};


class Sender : public Worker {
 public:
  explicit Sender(std::ostream &output) : output_(output) {}

  void Process(std::unique_ptr<Email> email) override {
    output_ << email->from << std::endl;
    output_ << email->to << std::endl;
    output_ << email->body << std::endl;
    PassOn(std::move(email));
  }

 private:
  std::ostream &output_;
};

// реализуйте класс
class PipelineBuilder {
 public:
  explicit PipelineBuilder(std::istream &input) {
    reader_ = make_unique<Reader>(input);
    current_ = reader_.get();
  }

  PipelineBuilder &FilterBy(Filter::Function filter) {
    auto filterWorker = make_unique<Filter>(std::move(filter));
    current_->SetNext(std::move(filterWorker));
    current_ = current_->GetNext();
    return *this;
  }

  PipelineBuilder &CopyTo(std::string email) {
    auto copierWorker = make_unique<Copier>(std::move(email));
    current_->SetNext(std::move(copierWorker));
    current_ = current_->GetNext();
    return *this;
  }

  PipelineBuilder &Send(std::ostream &output) {
    auto senderWorker = make_unique<Sender>(output);
    current_->SetNext(std::move(senderWorker));
    current_ = current_->GetNext();
    return *this;
  }

  std::unique_ptr<Worker> Build() {
    return std::move(reader_);
  }

 private:
  std::unique_ptr<Reader> reader_;
  Worker *current_;
};


void TestSanity() {
  std::string input = (
      "erich@example.com\n"
      "richard@example.com\n"
      "Hello there\n"

      "erich@example.com\n"
      "ralph@example.com\n"
      "Are you sure you pressed the right button?\n"

      "ralph@example.com\n"
      "erich@example.com\n"
      "I do not make mistakes of that kind\n"
  );
  std::istringstream inStream(input);
  std::ostringstream outStream;

  PipelineBuilder builder(inStream);
  builder.FilterBy([](const Email &email) {
    return email.from == "erich@example.com";
  });
  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();

  pipeline->Run();

  std::string expectedOutput = (
      "erich@example.com\n"
      "richard@example.com\n"
      "Hello there\n"

      "erich@example.com\n"
      "ralph@example.com\n"
      "Are you sure you pressed the right button?\n"

      "erich@example.com\n"
      "richard@example.com\n"
      "Are you sure you pressed the right button?\n"
  );

  assert(expectedOutput == outStream.str());
}


int main() {
  TestSanity();
  return 0;
}
