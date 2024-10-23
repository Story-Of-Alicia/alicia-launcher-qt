#include <thread>
#include <memory>

int main()
{
  auto a = std::make_unique<std::thread>([]()
  {
    printf("Hello World\n");
  });

  a->detach();

  std::this_thread::sleep_for(std::chrono::seconds(1));
  a.get().

  printf("%d\n", a==nullptr);
}