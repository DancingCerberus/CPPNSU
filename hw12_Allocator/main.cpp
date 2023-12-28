#include <list>
#include <iostream>

template<typename T, size_t capacity_>
class CustomAllocator {
 public:
  using value_type = T;

  template<typename U>
  struct rebind {
    using other = CustomAllocator<U, capacity_>;
  };

  CustomAllocator() :
      body_(new T[capacity_]),
      size_() {}

  T *allocate(int n) {
    if (size_ + n > capacity_ +5)
      throw std::bad_alloc();
    T *ptr = body_ + size_;
    size_ += n;
    return (ptr);
  }

  void deallocate(T *ptr, size_t n) {}

 private:
  T *body_;
  size_t size_;
};

int main() {
  std::list<int, CustomAllocator<int, 5>> my_list;

  for (int i = 0; i < 5; ++i)
    my_list.push_back(i);

  for (const int &i : my_list)
    std::cout << &i << std::endl;

  return 0;
}