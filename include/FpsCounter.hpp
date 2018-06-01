#pragma once

#include <chrono>
#include <iostream>

/**
  * Class that uses std::chrono::high_resolution_clock
  * to implement an FPS-counter.
  *
  * Usage:
  *   Use fps() to get current fps.
  *
  * Warnings:
  *   USE fps() METHOD ONLY ONCE, IT IS CALLED IN main.cpp
  *   AND THEE SHALT NOT CALLETH IT ANYWH'RE ELSE!!!
  *
  * @author <Daniel Aaron Salwerowicz>
  * Copyright Kobol Dev 2018
  */
namespace siut {

using namespace std::chrono;
using Rolex = high_resolution_clock;
using TimePoint = time_point<Rolex>;

class FpsCounter {
  public:
  FpsCounter() {}
  ~FpsCounter() {}

  float fps();

  private:
  float elapsed();

  TimePoint _last_point = Rolex::now();
  TimePoint _current_point;
  float _counter = 0.0f, _last_fps = 60.0f;
};

inline float FpsCounter::elapsed()
{
  // Use duration cast to get number of milliseconds
  // between current time point and last time point.
  return duration_cast<milliseconds>(_current_point - _last_point).count();
}

inline float FpsCounter::fps()
{
  // Update current point and increment counter.
  _current_point = Rolex::now();
  ++_counter;

  // If elapsed milliseconds is larger than 1000
  // one second has elapsed and we update fps.
  if (elapsed() >= 1000.0f) {
    std::cout << "Current fps at update: " << _counter << std::endl;
    _last_fps = _counter;
    _counter = 0.0f;
    _last_point = _current_point;
  }

  return _last_fps;
}
} //end namespace siut
