#include <malefica/thread/queue.hxx>

#include <catch.hpp>

#include <functional>
#include <memory>

using container_type = malefica::thread::queue<int>;

namespace
{
  constexpr int number_of_producers = 5;
  constexpr int number_of_consumers = 4;
  constexpr int items_to_produce = number_of_producers * number_of_consumers;
  constexpr int products = number_of_producers * items_to_produce;

  static int consumed_counter = 0;

  void consumed()
  {
    static std::mutex mutex;
    std::unique_lock<std::mutex> locker(mutex);
    ++consumed_counter;
  }

  static int produced_counter = 0;

  void produced()
  {
    static std::mutex mutex;
    std::unique_lock<std::mutex> locker(mutex);
    ++produced_counter;
  }

  void produce(container_type& q)
  {
    for (int i = 1; i <= items_to_produce; ++i)
    {
      produced();
      q.push(i);
    }
  }

  void consume(container_type& q)
  {
    for (int i = 0; i < products / number_of_consumers; ++i)
    {
      q.pop();
      consumed();
    }
  }
}

TEST_CASE("test concurrent queue access", "[thread]")
{
  container_type threading_queue;

  using thread_ptr = std::unique_ptr<std::thread>;
  using thread_pool = std::vector<thread_ptr>;

  produced_counter = 0;
  consumed_counter = 0;

  thread_pool consumers;
  for (int i = 0; i < number_of_consumers; ++i)
  {
    auto consumer = thread_ptr(new std::thread(std::bind(&consume, std::ref(threading_queue))));
    consumers.push_back(std::move(consumer));
  }

  thread_pool producers;
  for (int i = 0; i < number_of_producers; ++i)
  {
    auto producer = thread_ptr(new std::thread(std::bind(&produce, std::ref(threading_queue))));
    producers.push_back(std::move(producer));
  }

  for (auto& producer : producers)
  {
    producer->join();
  }

  for (auto& consumer : consumers)
  {
    consumer->join();
  }

  REQUIRE(produced_counter == products);
  REQUIRE(consumed_counter == products);
}